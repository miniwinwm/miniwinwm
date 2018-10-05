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

//#include <stdint.h>
//#include <stdbool.h>
#include "miniwin.h"
#include "ui/ui_common.h"
#include "dialogs/dialog_common.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef struct
{
	uint16_t circle_x;			/**< x coordinate of where to draw circle */
	uint16_t circle_y;			/**< y coordinate of where to draw circle */
	bool draw_circle;			/**< if to draw circle */
	char transfer_buffer[10];	/**< buffer to send data to label */
} window_simple_data_t;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern uint8_t button_id;
extern uint8_t label_id;

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

void window_simple_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_ref).width,
			mw_get_window_client_rect(window_ref).height);

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	if(window_simple_data.draw_circle)
	{
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_circle(draw_info, window_simple_data.circle_x, window_simple_data.circle_y, 25);
	}
}

void window_simple_message_function(const mw_message_t *message)
{
	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_simple_data.draw_circle = false;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		window_simple_data.circle_x = message->message_data >> 16;
		window_simple_data.circle_y = message->message_data;
		window_simple_data.draw_circle = true;
		mw_paint_window_client(message->recipient_id);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_id == button_id)
		{
			mw_create_window_dialog_one_button(20,
					50,
					150,
					"Title",
					"This is a message",
					"Yep",
					false,
					message->recipient_id);
		}
		break;

	case MW_DIALOG_ONE_BUTTON_DISMISSED_MESSAGE:
		mw_ui_common_post_pointer_to_control(label_id, "Hello world!");
		mw_paint_control(label_id);
		break;

	default:
		break;
	}
}
