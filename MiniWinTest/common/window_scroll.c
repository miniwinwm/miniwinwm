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
	uint16_t scroll_x;				/**< X scroll percentage */
	uint16_t scroll_y;				/**< Y scroll percentage */
} window_scroll_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

#define LINES 80
#define COLUMNS 80
#define DATA_WIDTH (COLUMNS * (mw_gl_get_font_width() + 1))

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_scroll_data_t window_scroll_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_scroll_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	int16_t column;
	int16_t line;
	int16_t column_x;
	int16_t line_y;
	int16_t scroll_offset_x;
	int16_t scroll_offset_y;
	uint8_t c;
	char buf[4];

	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fg_colour(MW_HAL_LCD_YELLOW);
	mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
	mw_gl_set_font(MW_GL_FONT_9);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	for (line = 0; line < LINES; line++)
	{
		line_y = line * (mw_gl_get_font_height() + 1);
		scroll_offset_y = (((LINES * (mw_gl_get_font_height() + 1)) - mw_get_window_client_rect(window_handle).height) * window_scroll_data.scroll_y) /
				UINT8_MAX;

		/* ignore text above client area */
		if (line_y - scroll_offset_y + mw_gl_get_font_height() + 1 < 0)
		{
			continue;
		}

		/* ignore text below client area */
		if (line_y - scroll_offset_y > mw_get_window_client_rect(window_handle).height)
		{
			break;
		}

		for (column = 3; column < COLUMNS; column++)
		{
			column_x = column * (mw_gl_get_font_width() + 1);
			scroll_offset_x = (((COLUMNS * (mw_gl_get_font_width() + 1)) - mw_get_window_client_rect(window_handle).width) * window_scroll_data.scroll_x) /
					UINT8_MAX;

			/* ignore text left of client area */
			if (column_x - scroll_offset_x + mw_gl_get_font_width() + 1 < 0)
			{
				continue;
			}

			/* ignore text right of client area */
			if (column_x - scroll_offset_x > mw_get_window_client_rect(window_handle).width)
			{
				break;
			}

			c = (line * 80 + column) % ('~' - ' ') + ' ';

			mw_gl_character(draw_info,
					column_x - scroll_offset_x,
					line_y - scroll_offset_y,
					c);
			c++;
			if (c > '~')
			{
				c = ' ';
			}
		}
		sprintf(buf, "%2d ", line);
		mw_gl_string(draw_info,
				0,
				line_y - scroll_offset_y,
				buf);
	}
}

void window_scroll_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_scroll_data.scroll_x = 0;
		window_scroll_data.scroll_y = 0;
		break;

	case MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		window_scroll_data.scroll_y = message->message_data;
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:
		window_scroll_data.scroll_x = message->message_data;
		mw_paint_window_client(message->recipient_handle);
		break;

	default:
		break;
	}
}
