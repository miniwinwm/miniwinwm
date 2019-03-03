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

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void get_file_dimensions(text_window_data_t* text_window_data);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Get the maximum line width in characters and number of text lines.
 */
static void get_file_dimensions(text_window_data_t* text_window_data)
{
	uint8_t c;
	uint32_t file_size;
	uint32_t i;
	int16_t this_line_width;

	/* scan file to find number of lines and maximum width */
	if (app_file_open(text_window_data->path_and_filename_text))
	{
		/* get file size, number of chars */
		file_size = app_file_size();

		/* going to get maximum width and height of text so initialize to start values */
		text_window_data->max_line_width = 0;
		text_window_data->number_of_lines = 1;
		this_line_width = 0;

		/* loop through the whole file */
		for (i = 0; i < file_size; i++)
		{
			/* get next character */
			c = app_file_getc();

			/* check for line end */
			if (c == (uint8_t)'\n')
			{
				/* got a line end so check how long this line is compared to previous max line length */
				if (this_line_width > text_window_data->max_line_width)
				{
					/* it's longer so save this line length */
					text_window_data->max_line_width = this_line_width;
				}

				/* reset line length counter */
				this_line_width = 0;
				text_window_data->number_of_lines++;
			}
			else
			{
				/* not got a line end so increase width counter for this line */
				this_line_width++;
			}
		}

		/* got to end of file so check how long this line is compared to previous max line length */
		if (this_line_width > text_window_data->max_line_width)
		{
			/* it's longer so save this line length */
			text_window_data->max_line_width = this_line_width;
		}
		app_file_close();
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_text_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	uint32_t file_size;
	int16_t x_pos;
	int16_t y_pos;
	int16_t char_box_x_start;
	int16_t char_box_y_start;
	int16_t char_box_x_end;
	int16_t char_box_y_end;
	int16_t client_width;
	int16_t client_height;
	char c;
	uint32_t i;
	text_window_data_t *text_window_data;

	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

	/* get this window instance data pointer and check for not null */
	text_window_data = (text_window_data_t *)mw_get_window_instance_data(window_handle);
	if (text_window_data == (void*)0)
	{
		MW_ASSERT((bool)false, "Couldn't find window instance data");
		return;
	}

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

	/* get client are dimensions from current window size */
	client_width = mw_get_window_client_rect(window_handle).width;
	client_height = mw_get_window_client_rect(window_handle).height;

	/* load text from file and render it */
	x_pos = 0;
	y_pos = 0;

	/* call app layer to open file */
	if (app_file_open(text_window_data->path_and_filename_text))
	{
		/* get file size, number of chars */
		file_size = app_file_size();

		/* loop through the whole file */
		for (i = 0; i < file_size; i++)
		{
			/* get next character */
			c = (char)app_file_getc();

			/* need to check if next drawing position is on screen so get bounds of next character */
			char_box_x_start = (int16_t)(x_pos - text_window_data->x_scroll_pos);
			char_box_x_end = (int16_t)((x_pos - text_window_data->x_scroll_pos) + mw_gl_get_font_width());
			char_box_y_start = (int16_t)(y_pos - text_window_data->y_scroll_pos);
			char_box_y_end = (int16_t)((y_pos - text_window_data->y_scroll_pos) + mw_gl_get_font_width());

			/* check if any of this character is on client area */
			if (char_box_x_start < client_width && char_box_x_end >= 0 &&
					char_box_y_start < client_height && char_box_y_end >= 0)
			{
				/* it is so render this character */
				mw_gl_character(draw_info, char_box_x_start, char_box_y_start, c);
			}

			/* move on x position */
			x_pos += mw_gl_get_font_width() + 1;

			/* check for line end */
			if (c == '\n')
			{
				/* reset x and y positions for next line */
				x_pos = 0;
				y_pos += mw_gl_get_font_height() + 1;
			}
		}

		app_file_close();
	}
}

void window_text_message_function(const mw_message_t *message)
{
	text_window_data_t *text_window_data;
	uint32_t temp_uint32;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	/* get this window instance data pointer and check for not null */
	text_window_data = (text_window_data_t *)mw_get_window_instance_data(message->recipient_handle);
	if (text_window_data == (void*)0)
	{
		MW_ASSERT((bool)false, "Couldn't find window instance data");
		return;
	}

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		/* get maximum line width and number of lines of text */
		get_file_dimensions(text_window_data);
		break;

	case MW_WINDOW_RESIZED_MESSAGE:
		get_file_dimensions(text_window_data);
		text_window_data->x_scroll_pos = 0;
		text_window_data->y_scroll_pos = 0;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		temp_uint32 = message->message_data >> 16;
		text_window_data->last_drag_x = (int16_t)temp_uint32;
		temp_uint32 = message->message_data & 0xffffU;
		text_window_data->last_drag_y = (int16_t)temp_uint32;
		break;

	case MW_TOUCH_DRAG_MESSAGE:
		{
			/* allows the text to be dragged around and updates the window scroll bars */
			int16_t pixels_to_move;
			bool window_paint_required = false;

			/* needed for getting character dimensions */
			mw_gl_set_font(MW_GL_FONT_9);

			/* ignore if client width is bigger than text max width */
			if (mw_get_window_client_rect(message->recipient_handle).width < text_window_data->max_line_width * (mw_gl_get_font_width() + 1))
			{
				/* calculate the number of pixels dragged in x dimension */
				temp_uint32 = message->message_data >> 16;
				pixels_to_move = text_window_data->last_drag_x - (int16_t)temp_uint32;
				temp_uint32 = message->message_data >> 16;
				text_window_data->last_drag_x = (int16_t)temp_uint32;

				text_window_data->x_scroll_pos += pixels_to_move;

				if (text_window_data->x_scroll_pos < 0)
				{
					text_window_data->x_scroll_pos = 0;
				}
				if (text_window_data->x_scroll_pos > text_window_data->max_line_width * (mw_gl_get_font_width() + 1) -
						mw_get_window_client_rect(message->recipient_handle).width)
				{
					text_window_data->x_scroll_pos = text_window_data->max_line_width * (mw_gl_get_font_width() + 1) -
							mw_get_window_client_rect(message->recipient_handle).width;
				}

				/* drag of image happened so indicate that window repaint required */
				window_paint_required = true;
			}

			/* ignore if client height is bigger than text height */
			if (mw_get_window_client_rect(message->recipient_handle).height < text_window_data->number_of_lines * (mw_gl_get_font_height() + 1))
			{
				/* calculate the number of pixels dragged in y dimension */
				temp_uint32 = message->message_data & 0xffffU;
				pixels_to_move = text_window_data->last_drag_y - (int16_t)temp_uint32;
				text_window_data->last_drag_y = (int16_t)temp_uint32;

				text_window_data->y_scroll_pos += pixels_to_move;

				if (text_window_data->y_scroll_pos < 0)
				{
					text_window_data->y_scroll_pos = 0;
				}
				if (text_window_data->y_scroll_pos > text_window_data->number_of_lines * (mw_gl_get_font_height() + 1) -
						mw_get_window_client_rect(message->recipient_handle).height)
				{
					text_window_data->y_scroll_pos = text_window_data->number_of_lines * (mw_gl_get_font_height() + 1) -
							mw_get_window_client_rect(message->recipient_handle).height;
				}

				/* drag of image happened so indicate that window repaint required */
				window_paint_required = true;
			}

			/* only repaint image if needed */
			if (window_paint_required)
			{
				mw_paint_window_client(message->recipient_handle);
			}
		}
		break;


	case MW_WINDOW_REMOVED_MESSAGE:
		mw_post_message(MW_WINDOW_EXTERNAL_WINDOW_REMOVED_MESSAGE,
				message->recipient_handle,
				window_file_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				NULL,
				MW_WINDOW_MESSAGE);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
