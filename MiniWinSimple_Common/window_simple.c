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
#include "window_simple.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef struct
{
	int16_t circle_x;			/**< X coordinate of where to draw circle */
	int16_t circle_y;			/**< Y coordinate of where to draw circle */
	bool draw_circle;			/**< If to draw circle */
} window_simple_data_t;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_simple_data_t window_simple_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_simple_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
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

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	if (window_simple_data.draw_circle)
	{
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_circle(draw_info, window_simple_data.circle_x, window_simple_data.circle_y, 25);
	}
}

void window_simple_message_function(const mw_message_t *message)
{
	uint32_t misra_temp;

	MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_simple_data.draw_circle = false;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		misra_temp = message->message_data >> 16U;
		window_simple_data.circle_x = (int16_t)misra_temp;
		window_simple_data.circle_y = (int16_t)message->message_data;
		window_simple_data.draw_circle = true;
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_handle == button_handle)
		{
			(void)mw_create_window_dialog_one_button(20,
					50,
					150,
					"Title",
					"This is a message",
					"Yep",
					false,
					message->recipient_handle);
		}
		break;

	case MW_DIALOG_ONE_BUTTON_DISMISSED_MESSAGE:
		mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
				message->recipient_handle,
				label_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				(void *)"Hello world!",
				MW_CONTROL_MESSAGE);
		mw_paint_control(label_handle);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
