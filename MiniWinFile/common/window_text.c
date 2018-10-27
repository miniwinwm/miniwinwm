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
#include <stdio.h>
#include "app.h"
#include "window_text.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern mw_handle_t window_file_handle;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_text_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info, "Null pointer parameter");

	uint32_t file_size;
	uint16_t x_pos;
	uint16_t y_pos;
	uint16_t client_width;
	uint16_t client_height;
	char c;
	uint32_t i;
	text_window_data_t *text_window_data;

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	mw_gl_set_fg_colour(MW_HAL_LCD_BLUE);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_font(MW_GL_FONT_9);

	/* get this window instance data pointer and check for not null */
	text_window_data = (text_window_data_t *)mw_get_window_instance_data(window_handle);
	if (text_window_data == NULL)
	{
		MW_ASSERT(false, "Couldn't find window instance data");
		return;
	}

	x_pos = 1;
	y_pos = 1;
	if (app_file_open(text_window_data->path_and_filename_text))
	{
		file_size = app_file_size();
		client_width = mw_get_window_client_rect(window_handle).width;
		client_height = mw_get_window_client_rect(window_handle).height;

		for (i = 0; i < file_size; i++)
		{
			c = app_file_getc();
			if (x_pos < client_width)
			{
				mw_gl_character(draw_info, x_pos, y_pos, c);
			}
			x_pos += mw_gl_get_font_width() + 1;
			if (c == '\n')
			{
				x_pos = 0;
				y_pos += mw_gl_get_font_height() + 1;
				if (y_pos >= client_height)
				{
					break;
				}
			}
		}

		app_file_close();
	}
}

void window_text_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_REMOVED_MESSAGE:
		mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
				message->recipient_handle,
				window_file_handle,
				0,
				MW_WINDOW_MESSAGE);
		break;

	default:
		break;
	}
}
