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
typedef enum
{
	ROOT_FOLDER,							/**< root folder on show */
	FOLDER_IMAGES,						/**< images folder shown */
	FOLDER_DOCS							/**< documents folder shown */
} folder_shown_t;

typedef struct
{
	uint8_t lines_to_scroll;				/**< number of lines folder list box is scrolled */
	folder_shown_t folder_shown;		/**< the current folder on display in the list box */
} file_data_t;


/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern uint8_t button_2_id;
extern uint8_t list_box_file_id;
extern uint8_t label_file_id;
extern uint8_t arrow_file_up_id;
extern uint8_t arrow_file_down_id;
extern mw_ui_list_box_data_t list_box_file_data;
extern mw_ui_list_box_entry list_box_file_entries_root[];
extern mw_ui_list_box_entry list_box_file_entries_images[];
extern mw_ui_list_box_entry list_box_file_entries_docs[];
extern const uint8_t list_box_file_entries_root_count;
extern const uint8_t list_box_file_entries_images_count;
extern const uint8_t list_box_file_entries_docs_count;

/**********************
*** LOCAL VARIABLES ***
**********************/

static file_data_t file_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_file_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_ref).width,
			mw_get_window_client_rect(window_ref).height);

	/* blue title bar */
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLUE);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_ref).width,
			18);
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_font(MW_GL_TITLE_FONT);
	mw_gl_string(draw_info, 2, 2, "File Chooser");
}

void window_file_message_function(const mw_message_t *message)
{
	uint8_t item_chosen;
	bool folder_changed;

	MW_ASSERT(message, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		break;

	case MW_WINDOW_VISIBILITY_CHANGED:
		if (message->message_data)
		{
			/* visibility gained */
			mw_ui_common_post_pointer_to_control(label_file_id, "");
			mw_paint_control(label_file_id);

			file_data.lines_to_scroll = 0;
			file_data.folder_shown = ROOT_FOLDER;
			list_box_file_data.list_box_entries = list_box_file_entries_root;
			list_box_file_data.number_of_items = list_box_file_entries_root_count;
			mw_set_control_enabled(arrow_file_up_id, false);
			if (list_box_file_data.number_of_lines < list_box_file_data.number_of_items)
			{
				mw_set_control_enabled(arrow_file_down_id, true);
			}
			else
			{
				mw_set_control_enabled(arrow_file_down_id, false);
			}
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
	    /* set window invisible */
		mw_set_window_visible(message->recipient_id, false);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		/* list box item pressed, get the item chosen number */
		item_chosen = message->message_data;

		/* update label with text of item chosen */
		mw_ui_common_post_pointer_to_control(label_file_id, list_box_file_data.list_box_entries[item_chosen].label);
		mw_paint_control(label_file_id);

		/* check if a folder has been chosen and if so update the list control to show new contents */
		folder_changed = false;
		if (file_data.folder_shown == ROOT_FOLDER)
		{
			if (item_chosen == 0)
			{
				file_data.folder_shown = FOLDER_IMAGES;
				list_box_file_data.list_box_entries = list_box_file_entries_images;
				list_box_file_data.number_of_items = list_box_file_entries_images_count;
				folder_changed = true;
			}
			else if (item_chosen == 1)
			{
				file_data.folder_shown = FOLDER_DOCS;
				list_box_file_data.list_box_entries = list_box_file_entries_docs;
				list_box_file_data.number_of_items = list_box_file_entries_docs_count;
				folder_changed = true;
			}
		}
		else if (item_chosen == 0)
		{
			file_data.folder_shown = ROOT_FOLDER;
			list_box_file_data.list_box_entries = list_box_file_entries_root;
			list_box_file_data.number_of_items = list_box_file_entries_root_count;
			folder_changed = true;
		}

		/* if folder changed update folder list box data and arrow enabled states and repaint all of them */
		if (folder_changed)
		{
			file_data.lines_to_scroll = 0;
			mw_paint_control(list_box_file_id);

			mw_set_control_enabled(arrow_file_up_id, false);
			if (list_box_file_data.number_of_lines < list_box_file_data.number_of_items)
			{
				mw_set_control_enabled(arrow_file_down_id, true);
			}
			else
			{
				mw_set_control_enabled(arrow_file_down_id, false);
			}
			mw_paint_control(arrow_file_up_id);
			mw_paint_control(arrow_file_down_id);
		}
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if (message->message_data == MW_UI_ARROW_UP && file_data.lines_to_scroll > 0)
		{
			/* up arrow, scroll list box up is ok to do so */
			file_data.lines_to_scroll--;

			if (file_data.lines_to_scroll == 0)
			{
				mw_set_control_enabled(arrow_file_up_id, false);
				mw_paint_control(arrow_file_up_id);
			}

			mw_set_control_enabled(arrow_file_down_id, true);
			mw_paint_control(arrow_file_down_id);

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					list_box_file_id,
					file_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_file_id);
		}
		else if (message->message_data == MW_UI_ARROW_DOWN &&
					file_data.lines_to_scroll < (list_box_file_data.number_of_items - list_box_file_data.number_of_lines))
		{
			/* down arrow, scroll list box down is ok to do so */
			file_data.lines_to_scroll++;

			if (file_data.lines_to_scroll == list_box_file_data.number_of_items - list_box_file_data.number_of_lines)
			{
				mw_set_control_enabled(arrow_file_down_id, false);
				mw_paint_control(arrow_file_down_id);
			}

			mw_set_control_enabled(arrow_file_up_id, true);
			mw_paint_control(arrow_file_up_id);

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					list_box_file_id,
					file_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_file_id);
		}
		break;

	default:
		break;
	}
}
