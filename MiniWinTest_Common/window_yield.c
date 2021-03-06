/*

MIT License

Copyright (c) John Blaiklock 2019 miniwin Embedded Window Manager

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

#include <stdlib.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_yield.h"

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
	mw_handle_t timer_handle;			/**< Timer used to drive breaking up of task this time  */
	uint16_t progress;					/**< How far through the task this time  */
	int16_t x[10];						/**< X coordinate of all circle positions this time  */
	int16_t y[10];						/**< Y coordinate of all circle positions this time  */
	int8_t r[10];						/**< Radius of all circles this time  */
	bool timer_running;					/**< If the animation timer is running */
	mw_hal_lcd_colour_t c[10];			/**< Colour of all circles this time */
} window_yield_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_yield_data_t window_yield_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_yield_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	uint8_t i;

	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_OFF);

	for (i = 0U; i < 10U; i++)
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
	long temp_long;
	uint64_t temp_uint64;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_yield_data.timer_running = false;
		break;

	case MW_WINDOW_RESTORED_MESSAGE:
	case MW_WINDOW_MOVED_MESSAGE:
	case MW_WINDOW_RESIZED_MESSAGE:
		window_yield_data.progress = 0;
		if (window_yield_data.timer_running)
		{
			mw_cancel_timer(window_yield_data.timer_handle);
		}
		window_yield_data.timer_handle = mw_set_timer(mw_tick_counter + 5U, message->recipient_handle, MW_WINDOW_MESSAGE);
		window_yield_data.timer_running = true;
		break;

	case MW_WINDOW_MINIMISED_MESSAGE:
		if (window_yield_data.timer_running)
		{
			mw_cancel_timer(window_yield_data.timer_handle);
			window_yield_data.timer_running = false;
		}
		break;

	case MW_TIMER_MESSAGE:
		window_yield_data.timer_running = false;
		mw_paint_window_client(message->recipient_handle);
		for (i = 0U; i < 10U; i++)
		{
			temp_long = rand() / (RAND_MAX / (long)mw_get_window_client_rect(message->recipient_handle).width);
			window_yield_data.x[i] = (int16_t)temp_long;
			temp_long = rand() / (RAND_MAX / (long)mw_get_window_client_rect(message->recipient_handle).height);
			window_yield_data.y[i] = (int16_t)temp_long;
			temp_long = 10 + rand() / (RAND_MAX / 50);
			window_yield_data.r[i] = (int8_t)temp_long;
			temp_uint64 = (uint64_t)rand() * (uint64_t)MW_HAL_LCD_WHITE / (uint64_t)RAND_MAX;
			window_yield_data.c[i] = (mw_hal_lcd_colour_t)temp_uint64;
		}

		window_yield_data.progress += 10U;
		if (window_yield_data.progress < 1000U)
		{
			window_yield_data.timer_handle = mw_set_timer(mw_tick_counter + 10U, message->recipient_handle, MW_WINDOW_MESSAGE);
			window_yield_data.timer_running = true;
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
