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
#define DATA_HEIGHT (LINES * MW_GL_STANDARD_CHARACTER_HEIGHT)
#define COLUMNS 80
#define DATA_WIDTH (COLUMNS * MW_GL_STANDARD_CHARACTER_WIDTH)

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern mw_window_t mw_all_windows[MW_MAX_WINDOW_COUNT];

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

void window_scroll_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	int16_t column;
	int16_t line;
	int16_t column_x;
	int16_t line_y;
	int16_t scroll_offset_x;
	int16_t scroll_offset_y;
	uint8_t c;
	char buf[4];

	mw_gl_set_fg_colour(MW_HAL_LCD_YELLOW);
	mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);

	for (line = 0; line < LINES; line++)
	{
		line_y = line * MW_GL_STANDARD_CHARACTER_HEIGHT;
		scroll_offset_y = ((DATA_HEIGHT - mw_all_windows[window_ref].client_rect.height) * window_scroll_data.scroll_y) /
				UINT8_MAX;

		/* ignore text above client area */
		if (line_y - scroll_offset_y + MW_GL_STANDARD_CHARACTER_HEIGHT < 0)
		{
			continue;
		}

		/* ignore text below client area */
		if (line_y - scroll_offset_y > mw_all_windows[window_ref].client_rect.height)
		{
			break;
		}

		for (column = 3; column < COLUMNS; column++)
		{
			column_x = column * MW_GL_STANDARD_CHARACTER_WIDTH;
			scroll_offset_x = ((DATA_WIDTH - mw_all_windows[window_ref].client_rect.width) * window_scroll_data.scroll_x) /
					UINT8_MAX;

			/* ignore text left of client area */
			if (column_x - scroll_offset_x + MW_GL_STANDARD_CHARACTER_WIDTH < 0)
			{
				continue;
			}

			/* ignore text right of client area */
			if (column_x - scroll_offset_x > mw_all_windows[window_ref].client_rect.width)
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
	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_scroll_data.scroll_x = 0;
		window_scroll_data.scroll_y = 0;
		break;

	case MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		window_scroll_data.scroll_y = message->message_data;
		mw_paint_window_client(message->recipient_id);
		break;

	case MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:
		window_scroll_data.scroll_x = message->message_data;
		mw_paint_window_client(message->recipient_id);
		break;

	default:
		break;
	}
}
