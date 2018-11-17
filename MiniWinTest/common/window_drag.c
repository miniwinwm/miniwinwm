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

#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

#define POINTS_COUNT_MAX 	15

/************
*** TYPES ***
************/

/**
 * Window data structure 
 */
typedef struct 
{
	uint8_t points_count;								/**< Number of points recorded */
	uint16_t points[2][POINTS_COUNT_MAX];				/**< The recorded points */
	uint8_t next_point;									/**< Next location in array to save a drag point */
} window_drag_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_drag_data_t window_drag_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_drag_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	uint8_t p;
	uint8_t i;
	uint16_t previous_x;
	uint16_t previous_y;

	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	if (window_drag_data.next_point == 0)
	{
		p = POINTS_COUNT_MAX - 1;
	}
	else
	{
		p = window_drag_data.next_point - 1;
	}

	mw_gl_set_fg_colour(MW_HAL_LCD_RED);
	mw_gl_set_line(MW_GL_SOLID_LINE);

	for (i = 0; i < window_drag_data.points_count -1 ; i++)
	{
		previous_x = window_drag_data.points[0][p];
		previous_y = window_drag_data.points[1][p];

		if (p == 0)
		{
			p = POINTS_COUNT_MAX - 1;
		}
		else
		{
			p--;
		}

		mw_gl_line(draw_info,
				previous_x,
				previous_y,
				window_drag_data.points[0][p],
				window_drag_data.points[1][p]);
	}
}

void window_drag_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_TOUCH_DOWN_MESSAGE:
		window_drag_data.points_count = 0;
		window_drag_data.next_point = 0;
		break;

	case MW_TOUCH_DRAG_MESSAGE:
		window_drag_data.points_count++;
		if (window_drag_data.points_count > POINTS_COUNT_MAX)
		{
			window_drag_data.points_count = POINTS_COUNT_MAX;
		}

		window_drag_data.points[0][window_drag_data.next_point] = (int16_t)(message->message_data >> 16);
		window_drag_data.points[1][window_drag_data.next_point] = (int16_t)(message->message_data & 0xffff);
		window_drag_data.next_point++;
		if (window_drag_data.next_point == POINTS_COUNT_MAX)
		{
			window_drag_data.next_point = 0;
		}
		mw_paint_window_client(message->recipient_handle);
		break;

	default:
		break;
	}
}
