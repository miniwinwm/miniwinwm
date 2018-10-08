/*

MIT License

Copyright (c) John Blaiklock 2018 miniwin Embedded Window Manager

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/***************
*** INCLUDES ***
***************/

#include <miniwin.h>
#include <stdlib.h>

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Window data structure 
 */
typedef struct 
{
	uint8_t timer_id;					/**< Timer used to drive breaking up of task this time  */
	uint16_t progress;					/**< How far through the task this time  */
	uint16_t x[10];						/**< X coordinate of all circle positions this time  */
	uint16_t y[10];						/**< Y coordinate of all circle positions this time  */
	uint8_t r[10];						/**< Radius of all circles this time  */
	mw_hal_lcd_colour_t c[10];			/**< Colour of all circles this time */
	bool timer_running;
} window_yield_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

window_yield_data_t window_yield_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_yield_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	uint8_t i;

	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_ref).width,
			mw_get_window_client_rect(window_ref).height);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_OFF);

	for (i = 0; i < 10; i++)
	{
		mw_gl_set_solid_fill_colour(window_yield_data.c[i]);
		mw_gl_circle(draw_info,
				window_yield_data.x[i],
				window_yield_data.y[i],
				window_yield_data.r[i]);
	}
}

void window_yield_message_function(const mw_message_t *message)
{
	uint8_t i;

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_yield_data.timer_running = false;
		break;

	case MW_WINDOW_RESTORED:
	case MW_WINDOW_MOVED:
	case MW_WINDOW_RESIZED:
		window_yield_data.progress = 0;
		if (window_yield_data.timer_running)
		{
			mw_cancel_timer(window_yield_data.timer_id);
		}
		window_yield_data.timer_id = mw_set_timer(mw_tick_counter + 5, message->recipient_id, MW_WINDOW_MESSAGE);
		window_yield_data.timer_running = true;
		break;

	case MW_WINDOW_MINIMISED:
		if (window_yield_data.timer_running)
		{
			mw_cancel_timer(window_yield_data.timer_id);
			window_yield_data.timer_running = false;
		}
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		window_yield_data.timer_running = false;
		mw_paint_window_client(message->recipient_id);
		for (i = 0; i < 10; i++)
		{
			window_yield_data.x[i] = rand() / (RAND_MAX / mw_get_window_client_rect(message->recipient_id).width);
			window_yield_data.y[i] = rand() / (RAND_MAX / mw_get_window_client_rect(message->recipient_id).height);
			window_yield_data.r[i] = 10 + rand() / (RAND_MAX / 50);
#if (RAND_MAX < 0xffff)
			window_yield_data.c[i] = rand() * 0xffff / RAND_MAX;
#else
			window_yield_data.c[i] = rand() / (RAND_MAX / 0xffff);
#endif
		}

		window_yield_data.progress += 10;
		if (window_yield_data.progress < 1000)
		{
			window_yield_data.timer_id = mw_set_timer(mw_tick_counter + 10, message->recipient_id, MW_WINDOW_MESSAGE);
			window_yield_data.timer_running = true;
		}
		break;

	default:
		break;
	}
}
