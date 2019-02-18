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

#include <stdint.h>
#include <stdbool.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_settings.h"

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
	uint8_t lines_to_scroll;		/**< Number of lines list box is scrolled */
	uint16_t max_scrollable_lines;		/**< Maximum number of lines list box can be scrolled */
} settings_data_t;

/**********************
*** LOCAL VARIABLES ***
**********************/

static settings_data_t settings_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_settings_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	/* blue title bar */
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLUE);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			18);
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_font(MW_GL_TITLE_FONT);
	mw_gl_string(draw_info, 2, 2, "Logging Settings");
}

void window_settings_message_function(const mw_message_t *message)
{
	uint8_t list_box_item_chosen;

	MW_ASSERT(message, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		settings_data.lines_to_scroll = 0;
		mw_set_control_enabled(arrow_settings_up, false);
		break;

	case MW_LIST_BOX_SCROLLING_REQUIRED_MESSAGE:
		mw_set_control_enabled(arrow_settings_down, message->message_data >> 16);
		settings_data.max_scrollable_lines = message->message_data & 0xffff;
		mw_paint_control(arrow_settings_down);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
	    /* set window invisible */
		mw_set_window_visible(message->recipient_handle, false);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		/* list box item pressed */
		list_box_item_chosen = message->message_data;
		mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
				message->recipient_handle,
				label_settings_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				(void *)list_box_settings_entries[list_box_item_chosen].label,
				MW_CONTROL_MESSAGE);
		mw_paint_control(label_settings_handle);
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if (message->message_data == MW_UI_ARROW_UP && settings_data.lines_to_scroll > 0)
		{
			/* up arrow, scroll list box up is ok to do so */
			settings_data.lines_to_scroll--;

			if (settings_data.lines_to_scroll == 0)
			{
				mw_set_control_enabled(arrow_settings_up, false);
				mw_paint_control(arrow_settings_up);
			}

			mw_set_control_enabled(arrow_settings_down, true);
			mw_paint_control(arrow_settings_down);

			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					list_box_settings_handle,
					settings_data.lines_to_scroll,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_settings_handle);
		}
		else if (message->message_data == MW_UI_ARROW_DOWN &&
					settings_data.lines_to_scroll < settings_data.max_scrollable_lines)
		{
			/* down arrow, scroll list box down if ok to do so */
			settings_data.lines_to_scroll++;

			if (settings_data.lines_to_scroll == settings_data.max_scrollable_lines)
			{
				mw_set_control_enabled(arrow_settings_down, false);
				mw_paint_control(arrow_settings_down);
			}

			mw_set_control_enabled(arrow_settings_up, true);
			mw_paint_control(arrow_settings_up);

			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					list_box_settings_handle,
					settings_data.lines_to_scroll,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_settings_handle);
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
