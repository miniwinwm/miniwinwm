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

#include "miniwin.h"
#include "miniwin_user.h"
#include "window_drag.h"

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
	int8_t points_count;								/**< Number of points recorded */
	int16_t points[2][POINTS_COUNT_MAX];				/**< The recorded points */
	int8_t next_point;									/**< Next location in array to save a drag point */
	uint8_t scroll_h;									/**< Horizontal window horizontal scroll bar position */
	uint8_t scroll_v;									/**< Vertical window vertical scroll position */
	char event_text_buffer[10];							/**< Buffer for text of event */
	int16_t touch_x;									/**< Latest touch x position */
	int16_t touch_y;									/**< Latest touch y position */
	uint8_t scroll_control;								/**< Control scroll bar position */
} window_drag_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

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
	int8_t p;
	int8_t i;
	int16_t previous_x;
	int16_t previous_y;
	char text_buffer[5];

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

    /* draw the scroll positions text */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_font(MW_GL_FONT_9);

	(void)mw_util_safe_itoa((int32_t)window_drag_data.touch_x, text_buffer, (size_t)5, 10, false, 0U, ' ');
	mw_gl_string(draw_info, 1, 1, text_buffer);
	(void)mw_util_safe_itoa((int32_t)window_drag_data.touch_y, text_buffer, (size_t)5, 10, false, 0U, ' ');
	mw_gl_string(draw_info, 22, 1, text_buffer);
	mw_gl_string(draw_info, 43, 1, window_drag_data.event_text_buffer);
	(void)mw_util_safe_itoa((int32_t)window_drag_data.scroll_h, text_buffer, (size_t)5, 10, false, 0U, ' ');
	mw_gl_string(draw_info, 72, 1, text_buffer);
	(void)mw_util_safe_itoa((int32_t)window_drag_data.scroll_v, text_buffer, (size_t)5, 10, false, 0U, ' ');
	mw_gl_string(draw_info, 93, 1, text_buffer);
	(void)mw_util_safe_itoa((int32_t)window_drag_data.scroll_control, text_buffer, (size_t)5, 10, false, 0U, ' ');
	mw_gl_string(draw_info, 114, 1, text_buffer);

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

	for (i = 0; i < window_drag_data.points_count - 1 ; i++)
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
	uint32_t temp_uint32;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_drag_data.scroll_h = 0;
		window_drag_data.scroll_v = 0;
		window_drag_data.touch_x = 0;
		window_drag_data.touch_y = 0;
		window_drag_data.scroll_control = 0;
		window_drag_data.points_count = 0;
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, sizeof(window_drag_data.event_text_buffer), "NONE");
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, sizeof(window_drag_data.event_text_buffer), "DOWN");
		window_drag_data.points_count = 0;
		window_drag_data.next_point = 0;
		temp_uint32 = message->message_data >> 16;
		window_drag_data.touch_x = (int16_t)temp_uint32;
		temp_uint32 = message->message_data & 0xffffU;
		window_drag_data.touch_y = (int16_t)temp_uint32;
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		window_drag_data.scroll_control = (uint8_t)message->message_data;
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, sizeof(window_drag_data.event_text_buffer), "CSCR");
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_TOUCH_HOLD_DOWN_MESSAGE:
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, sizeof(window_drag_data.event_text_buffer), "HOLD");
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_TOUCH_UP_MESSAGE:
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, sizeof(window_drag_data.event_text_buffer), "UP");
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, sizeof(window_drag_data.event_text_buffer), "VSCR");
		window_drag_data.scroll_v = (uint8_t)message->message_data;
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, sizeof(window_drag_data.event_text_buffer), "HSCR");
		window_drag_data.scroll_h = (uint8_t)message->message_data;
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_TOUCH_DRAG_MESSAGE:
		temp_uint32 = message->message_data >> 16;
		window_drag_data.touch_x = (int16_t)temp_uint32;
		temp_uint32 = message->message_data & 0xffffU;
		window_drag_data.touch_y = (int16_t)temp_uint32;
		(void)mw_util_safe_strcpy(window_drag_data.event_text_buffer, 5, "DRAG");
		window_drag_data.points_count++;
		if (window_drag_data.points_count > POINTS_COUNT_MAX)
		{
			window_drag_data.points_count = POINTS_COUNT_MAX;
		}

		window_drag_data.points[0][window_drag_data.next_point] = window_drag_data.touch_x;
		window_drag_data.points[1][window_drag_data.next_point] = window_drag_data.touch_y;
		window_drag_data.next_point++;
		if (window_drag_data.next_point == POINTS_COUNT_MAX)
		{
			window_drag_data.next_point = 0;
		}
		mw_paint_window_client(message->recipient_handle);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
