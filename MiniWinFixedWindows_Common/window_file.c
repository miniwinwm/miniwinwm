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
#include <stdlib.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_file.h"

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
	ROOT_FOLDER,						/**< Root folder on show */
	FOLDER_IMAGES,						/**< Images folder shown */
	FOLDER_DOCS							/**< Documents folder shown */
} folder_shown_t;

typedef struct
{
	uint8_t lines_to_scroll;			/**< Number of lines folder list box is scrolled */
	folder_shown_t folder_shown;		/**< The current folder on display in the list box */
	uint16_t max_scrollable_lines;		/**< Maximum number of lines list box can be scrolled */
} file_data_t;

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

void window_file_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

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
	mw_gl_string(draw_info, 2, 2, "File Chooser");
}

void window_file_message_function(const mw_message_t *message)
{
	uint8_t item_chosen;
	bool folder_changed;
	uint32_t temp_uint32;

	MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		break;

	case MW_LIST_BOX_SCROLLING_REQUIRED_MESSAGE:
		temp_uint32 = message->message_data >> 16;
		mw_set_control_enabled(arrow_file_down_handle, (bool)temp_uint32);
		temp_uint32 = message->message_data & 0xffffU;
		file_data.max_scrollable_lines = (uint16_t)temp_uint32;
		mw_paint_control(arrow_file_down_handle);
		break;

	case MW_WINDOW_VISIBILITY_CHANGED_MESSAGE:
		if (message->message_data != 0U)
		{
			/* visibility gained */
			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_file_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)"",
					MW_CONTROL_MESSAGE);
			mw_paint_control(label_file_handle);

			file_data.lines_to_scroll = 0;
			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					message->recipient_handle,
					list_box_file_handle,
					0,
					NULL,
					MW_CONTROL_MESSAGE);
			file_data.folder_shown = ROOT_FOLDER;

			mw_post_message(MW_LIST_BOX_SET_ENTRIES_MESSAGE,
					message->recipient_handle,
					list_box_file_handle,
					list_box_file_entries_root_count,
					(void *)list_box_file_entries_root,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_file_handle);

			mw_set_control_enabled(arrow_file_up_handle, false);
			mw_paint_control(arrow_file_up_handle);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
	    /* set window invisible */
		mw_set_window_visible(message->recipient_handle, false);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		/* list box item pressed, get the item chosen number */
		item_chosen = (uint8_t)message->message_data;

		/* update label with text of item chosen */
		switch (file_data.folder_shown)
		{
		case ROOT_FOLDER:
			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_file_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)list_box_file_entries_root[item_chosen].label,
					MW_CONTROL_MESSAGE);
			break;

		case FOLDER_IMAGES:
			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_file_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)list_box_file_entries_images[item_chosen].label,
					MW_CONTROL_MESSAGE);
			break;

		case FOLDER_DOCS:
			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_file_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)list_box_file_entries_docs[item_chosen].label,
					MW_CONTROL_MESSAGE);
			break;

		default:
			/* keep MISRA happy */
			break;
		}
		mw_paint_control(label_file_handle);

		/* check if a folder has been chosen and if so update the list control to show new contents */
		folder_changed = false;
		if (file_data.folder_shown == ROOT_FOLDER)
		{
			if (item_chosen == 0U)
			{
				file_data.folder_shown = FOLDER_IMAGES;

				mw_post_message(MW_LIST_BOX_SET_ENTRIES_MESSAGE,
						message->recipient_handle,
						list_box_file_handle,
						list_box_file_entries_images_count,
						(void *)list_box_file_entries_images,
						MW_CONTROL_MESSAGE);

				folder_changed = true;
			}
			else if (item_chosen == 1U)
			{
				file_data.folder_shown = FOLDER_DOCS;

				mw_post_message(MW_LIST_BOX_SET_ENTRIES_MESSAGE,
						message->recipient_handle,
						list_box_file_handle,
						list_box_file_entries_docs_count,
						(void *)list_box_file_entries_docs,
						MW_CONTROL_MESSAGE);

				folder_changed = true;
			}
			else
			{
				/* keep MISRA happy */
			}
		}
		else if (item_chosen == 0U)
		{
			file_data.folder_shown = ROOT_FOLDER;

			mw_post_message(MW_LIST_BOX_SET_ENTRIES_MESSAGE,
					message->recipient_handle,
					list_box_file_handle,
					list_box_file_entries_root_count,
					(void *)list_box_file_entries_root,
					MW_CONTROL_MESSAGE);

			folder_changed = true;
		}
		else
		{
			/* keep MISRA happy */
		}

		/* if folder changed update folder list box data and arrow enabled states and repaint all of them */
		if (folder_changed)
		{
			file_data.lines_to_scroll = 0;

			mw_set_control_enabled(arrow_file_up_handle, false);
			if (file_data.max_scrollable_lines > 0U)
			{
				mw_set_control_enabled(arrow_file_down_handle, true);
			}
			else
			{
				mw_set_control_enabled(arrow_file_down_handle, false);
			}
			mw_paint_control(arrow_file_up_handle);
			mw_paint_control(arrow_file_down_handle);
			mw_paint_control(list_box_file_handle);
		}
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_UP && file_data.lines_to_scroll > 0U)
		{
			/* up arrow, scroll list box up is ok to do so */
			file_data.lines_to_scroll--;

			if (file_data.lines_to_scroll == 0U)
			{
				mw_set_control_enabled(arrow_file_up_handle, false);
				mw_paint_control(arrow_file_up_handle);
			}

			mw_set_control_enabled(arrow_file_down_handle, true);
			mw_paint_control(arrow_file_down_handle);

			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					list_box_file_handle,
					file_data.lines_to_scroll,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_file_handle);
		}
		else if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_DOWN &&
					file_data.lines_to_scroll < file_data.max_scrollable_lines)
		{
			/* down arrow, scroll list box down is ok to do so */
			file_data.lines_to_scroll++;

			if (file_data.lines_to_scroll == file_data.max_scrollable_lines)
			{
				mw_set_control_enabled(arrow_file_down_handle, false);
				mw_paint_control(arrow_file_down_handle);
			}

			mw_set_control_enabled(arrow_file_up_handle, true);
			mw_paint_control(arrow_file_up_handle);

			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					list_box_file_handle,
					file_data.lines_to_scroll,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_file_handle);
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
