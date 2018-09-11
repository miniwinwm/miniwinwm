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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "miniwin.h"
#include "ui/ui_common.h"

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
	uint8_t lines_to_scroll;		/**< number of lines list box is scrolled */
} settings_data_t;


/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern uint8_t list_box_settings_id;
extern uint8_t label_settings_id;
extern uint8_t arrow_settings_up;
extern uint8_t arrow_settings_down;
extern mw_ui_list_box_data_t list_box_settings_data;
extern mw_ui_list_box_entry list_box_settings_entries[];
extern mw_window_t mw_all_windows[MW_MAX_WINDOW_COUNT];

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

void window_settings_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_all_windows[window_ref].client_rect.width,
			mw_all_windows[window_ref].client_rect.height);

	/* blue title bar */
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLUE);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_all_windows[window_ref].client_rect.width,
			18);
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_large_string(draw_info, 2, 2, "Logging Settings");
}

void window_settings_message_function(const mw_message_t *message)
{
	uint8_t list_box_item_chosen;

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		settings_data.lines_to_scroll = 0;
		mw_set_control_enabled(arrow_settings_up, false);
		mw_set_control_enabled(arrow_settings_down, true);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
	    /* set window invisible */
		mw_set_window_visible(message->recipient_id, false);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		/* list box item pressed */
		list_box_item_chosen = message->message_data;
		mw_ui_common_post_pointer_to_control(label_settings_id, list_box_settings_entries[list_box_item_chosen].label);
		mw_paint_control(label_settings_id);
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

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					list_box_settings_id,
					settings_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_settings_id);
		}
		else if (message->message_data == MW_UI_ARROW_DOWN &&
					settings_data.lines_to_scroll < (list_box_settings_data.number_of_items - list_box_settings_data.number_of_lines))
		{
			/* down arrow, scroll list box down is ok to do so */
			settings_data.lines_to_scroll++;

			if (settings_data.lines_to_scroll == list_box_settings_data.number_of_items - list_box_settings_data.number_of_lines)
			{
				mw_set_control_enabled(arrow_settings_down, false);
				mw_paint_control(arrow_settings_down);
			}

			mw_set_control_enabled(arrow_settings_up, true);
			mw_paint_control(arrow_settings_up);

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					list_box_settings_id,
					settings_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_settings_id);
		}
		break;

	default:
		break;
	}
}
