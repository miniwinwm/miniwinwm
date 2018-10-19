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

#include <string.h>
#include "dialogs/dialog_file_chooser.h"
#include "miniwin.h"
#include "ui/ui_common.h"
#include "app.h"

#ifdef MW_DIALOG_FILE_CHOOSER

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
	uint8_t lines_to_scroll;										/**< number of lines list box is scrolled */
	mw_ui_list_box_entry file_entries[FILE_LIST_BOX_MAX_ENTRIES]; 	/**< the storage for the folder entries data the list box shows; an entry contains pointers; icons and labels must exist elsewhere */
	char folder_path[MAX_FOLDER_AND_FILE_NAME_LENGTH + 1];			/**< path to most recently chosen folder, and path and file name when dialog dismissed */
	uint8_t folder_depth;											/**< root is zero, increments for every sub-folder */
	uint8_t button_ok_id;											/**< Control id of ok button */
	uint8_t button_cancel_id;										/**< Control id of cancel button */
	uint8_t list_box_file_id;										/**< Control id of list box for folders and files */
	uint8_t arrow_file_up_id;										/**< Control id of up arrow */
	uint8_t arrow_file_down_id;										/**< Control id of down arrow */
	uint8_t arrow_file_back_id;										/**< Control id of back arrow, to parent folder */
	uint8_t label_file_id;											/**< Control id of filename label */
	mw_ui_list_box_data_t list_box_file_data;						/**< Instance data of list box */
	mw_ui_arrow_data_t arrow_up_file_data;							/**< Instance data of up arrow */
	mw_ui_arrow_data_t arrow_down_file_data;						/**< Instance data of down arrow */
	mw_ui_arrow_data_t arrow_back_file_data;						/**< Instance data of back arrow */
	mw_ui_button_data_t button_ok_data;								/**< Instance data of ok button */
	mw_ui_button_data_t button_cancel_data;							/**< Instance data of cancel button */
	mw_ui_label_data_t label_file_data;								/**< Instance data of file name data */
	uint8_t window_dialog_file_chooser_id;							/**< Window id of dialog */
	char *message;													/**< Text to display in dialog */
	bool large_size;												/**< True for large size false for standard size */
	uint8_t response_window_id;										/**< Window id to send response message to */
} mw_dialog_file_chooser_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint8_t mw_bitmaps_file_icon_small[];
extern const uint8_t mw_bitmaps_folder_icon_small[];
extern const uint8_t mw_bitmaps_file_icon_large[];
extern const uint8_t mw_bitmaps_folder_icon_large[];

/**********************
*** LOCAL VARIABLES ***
**********************/

static char file_entries_label[FILE_LIST_BOX_MAX_ENTRIES][MAX_FILE_NAME_LENGTH + 1];
static mw_dialog_file_chooser_data_t mw_dialog_file_chooser_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void remove_resources(void);
static void update_folder_entries(void);
static void mw_dialog_file_chooser_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_file_chooser_message_function(const mw_message_t *message);
static uint8_t get_folder_depth(char *path);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Get the depth of a folder
 *
 * @param path The path to analyse
 * @return the folder depth
 */
static uint8_t get_folder_depth(char *path)
{
	uint8_t depth;
	uint16_t i;

	if (path[strlen(path)] == '/')
	{
		depth = 0;
	}
	else
	{
		for (i = 0; i < strlen(path); i++)
		{
			if (path[i] == '/')
			{
				depth++;
			}
		}

		depth--;
	}

	return depth;
}

/**
 * Remove this dialog window and all controls
 */
static void remove_resources(void)
{
	mw_remove_control(mw_dialog_file_chooser_data.arrow_file_up_id);
	mw_remove_control(mw_dialog_file_chooser_data.arrow_file_down_id);
	mw_remove_control(mw_dialog_file_chooser_data.arrow_file_back_id);
	mw_remove_control(mw_dialog_file_chooser_data.list_box_file_id);
	mw_remove_control(mw_dialog_file_chooser_data.button_ok_id);
	mw_remove_control(mw_dialog_file_chooser_data.button_cancel_id);
	mw_remove_control(mw_dialog_file_chooser_data.label_file_id);
	mw_remove_window(mw_dialog_file_chooser_data.window_dialog_file_chooser_id);
}

/**
 * Update the list box with the current folder's entries
 */
static void update_folder_entries()
{
	if (mw_dialog_file_chooser_data.large_size)
	{
		mw_dialog_file_chooser_data.list_box_file_data.number_of_items = find_directory_entries(mw_dialog_file_chooser_data.folder_path,
				mw_dialog_file_chooser_data.file_entries,
				FILE_LIST_BOX_MAX_ENTRIES,
				mw_bitmaps_file_icon_large,
				mw_bitmaps_folder_icon_large);
	}
	else
	{
		mw_dialog_file_chooser_data.list_box_file_data.number_of_items = find_directory_entries(mw_dialog_file_chooser_data.folder_path,
				mw_dialog_file_chooser_data.file_entries,
				FILE_LIST_BOX_MAX_ENTRIES,
				mw_bitmaps_file_icon_small,
				mw_bitmaps_folder_icon_small);
	}

	if (mw_dialog_file_chooser_data.list_box_file_data.number_of_lines < mw_dialog_file_chooser_data.list_box_file_data.number_of_items)
	{
		mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_down_id, true);
	}
	else
	{
		mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_down_id, false);
	}

	if (mw_dialog_file_chooser_data.folder_depth == 0)
	{
		mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_back_id, false);
	}
	else
	{
		mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_back_id, true);
	}

	mw_paint_control(mw_dialog_file_chooser_data.arrow_file_up_id);
	mw_paint_control(mw_dialog_file_chooser_data.arrow_file_down_id);
	mw_paint_control(mw_dialog_file_chooser_data.arrow_file_back_id);
	mw_paint_control(mw_dialog_file_chooser_data.list_box_file_id);
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_ref The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_file_chooser_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
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
}

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void mw_dialog_file_chooser_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		mw_dialog_file_chooser_data.folder_depth =
				get_folder_depth(mw_dialog_file_chooser_data.folder_path);
		update_folder_entries();
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		{
			/* remove all controls and window */
			remove_resources();

			if (message->sender_id == mw_dialog_file_chooser_data.button_ok_id)
			{
				if (mw_dialog_file_chooser_data.folder_depth > 0)
				{
					mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
							MAX_FOLDER_AND_FILE_NAME_LENGTH,
							"/");
				}

				mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
						MAX_FOLDER_AND_FILE_NAME_LENGTH,
						mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[mw_dialog_file_chooser_data.list_box_file_data.selection].label);

				/* post ok response to receiving window */
				mw_post_message(MW_DIALOG_FILE_CHOOSER_OK_PTR_MESSAGE,
						MW_UNUSED_MESSAGE_PARAMETER,
						mw_dialog_file_chooser_data.response_window_id,
						(uint32_t)mw_dialog_file_chooser_data.folder_path,
						MW_WINDOW_MESSAGE);
			}
			else
			{
				/* post cancel response to receiving window */
				mw_post_message(MW_DIALOG_FILE_CHOOSER_CANCEL_MESSAGE,
						MW_UNUSED_MESSAGE_PARAMETER,
						mw_dialog_file_chooser_data.response_window_id,
						0,
						MW_WINDOW_MESSAGE);
			}

			/* a window has changed visibility so repaint all */
			mw_paint_all();
		}
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if (message->message_data == MW_UI_ARROW_UP && mw_dialog_file_chooser_data.lines_to_scroll > 0)
		{
			/* up arrow, scroll list box up is ok to do so */
			mw_dialog_file_chooser_data.lines_to_scroll--;

			if (mw_dialog_file_chooser_data.lines_to_scroll == 0)
			{
				mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_up_id, false);
				mw_paint_control(mw_dialog_file_chooser_data.arrow_file_up_id);
			}

			mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_down_id, true);
			mw_paint_control(mw_dialog_file_chooser_data.arrow_file_down_id);

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					mw_dialog_file_chooser_data.list_box_file_id,
					mw_dialog_file_chooser_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(mw_dialog_file_chooser_data.list_box_file_id);
		}
		else if (message->message_data == MW_UI_ARROW_DOWN &&
				mw_dialog_file_chooser_data.lines_to_scroll <
				(mw_dialog_file_chooser_data.list_box_file_data.number_of_items -
						mw_dialog_file_chooser_data.list_box_file_data.number_of_lines))
		{
			/* down arrow, scroll list box down is ok to do so */
			mw_dialog_file_chooser_data.lines_to_scroll++;

			if (mw_dialog_file_chooser_data.lines_to_scroll ==
					mw_dialog_file_chooser_data.list_box_file_data.number_of_items -
					mw_dialog_file_chooser_data.list_box_file_data.number_of_lines)
			{
				mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_down_id, false);
				mw_paint_control(mw_dialog_file_chooser_data.arrow_file_down_id);
			}

			mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_up_id, true);
			mw_paint_control(mw_dialog_file_chooser_data.arrow_file_up_id);

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					mw_dialog_file_chooser_data.list_box_file_id,
					mw_dialog_file_chooser_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(mw_dialog_file_chooser_data.list_box_file_id);
		}
		else if (message->message_data == MW_UI_ARROW_LEFT)
		{
			/* left arrow, go up a folder path */
			*strrchr(mw_dialog_file_chooser_data.folder_path, '/') = '\0';
			mw_dialog_file_chooser_data.folder_depth--;

			/* check if back to root and if so add / again as it's the only folder that ends in a '/' */
			if (mw_dialog_file_chooser_data.folder_depth == 0)
			{
				mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path, MAX_FOLDER_AND_FILE_NAME_LENGTH, "/");
			}
			update_folder_entries();
		}
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		{
			/* list box item pressed, get the item chosen number */
			uint8_t item_chosen = message->message_data;

			if ((mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].icon ==
					mw_bitmaps_folder_icon_large && mw_dialog_file_chooser_data.large_size) ||
					(mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].icon ==
					mw_bitmaps_folder_icon_small && !mw_dialog_file_chooser_data.large_size))
			{
				/* folder chosen */

				/* update label with file not chosen */
				mw_ui_common_post_pointer_to_control(mw_dialog_file_chooser_data.label_file_id,
						"No File");
				mw_paint_control(mw_dialog_file_chooser_data.label_file_id);

				/* change directory to list_box_file_data.list_box_entries[item_chosen].label
				 * create new folder path by adding / and then the sub-folder name, but don't add /
				 * to root folder path as it ends in / already
				 */
				if (mw_dialog_file_chooser_data.folder_depth > 0)
				{
					mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
							MAX_FOLDER_AND_FILE_NAME_LENGTH,
							"/");
				}
				mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
						MAX_FOLDER_AND_FILE_NAME_LENGTH,
						mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].label);

				/* increment sub-folder depth counter */
				mw_dialog_file_chooser_data.folder_depth++;

				/* now get the new sub-folder's entries */
				update_folder_entries();
			}
			else if ((mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].icon ==
					mw_bitmaps_file_icon_large && mw_dialog_file_chooser_data.large_size) ||
					(mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].icon ==
					mw_bitmaps_file_icon_small && !mw_dialog_file_chooser_data.large_size))
			{
				/* file chosen, update label with name of file chosen */
				mw_ui_common_post_pointer_to_control(mw_dialog_file_chooser_data.label_file_id,
						mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].label);
				mw_paint_control(mw_dialog_file_chooser_data.label_file_id);
			}
		}
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

uint8_t mw_create_window_dialog_file_chooser(uint16_t x,
		uint16_t y,
		char *title,
		char *start_path,
		bool large_size,
		uint8_t response_window_id)
{
	mw_util_rect_t rect;
	uint8_t i;

	/* check pointer parameters */
	if (!title)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_MAX_WINDOW_COUNT;
	}

	/* set width & height */
	if (large_size)
	{
		rect.width = 220;
		rect.height = 232;
	}
	else
	{
		rect.width = 153;
		rect.height = 135;
	}

	/* check start position */
	if (rect.width > MW_ROOT_WIDTH || x + rect.width > MW_ROOT_WIDTH)
	{
		return MW_MAX_WINDOW_COUNT;
	}
	if (y + rect.height > MW_ROOT_HEIGHT)
	{
		return MW_MAX_WINDOW_COUNT;
	}

	mw_dialog_file_chooser_data.large_size = large_size;
	mw_dialog_file_chooser_data.response_window_id = response_window_id;
	rect.x = x;
	rect.y = y;

	mw_dialog_file_chooser_data.window_dialog_file_chooser_id = mw_add_window(&rect,
			title,
			mw_dialog_file_chooser_paint_function,
			mw_dialog_file_chooser_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_file_chooser_data.window_dialog_file_chooser_id == MW_MAX_WINDOW_COUNT)
	{
		/* it couldn't so exit */
		return MW_MAX_WINDOW_COUNT;
	}

	/* set controls' data */
	mw_dialog_file_chooser_data.arrow_up_file_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	mw_dialog_file_chooser_data.arrow_down_file_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	mw_dialog_file_chooser_data.arrow_back_file_data.mw_ui_arrow_direction = MW_UI_ARROW_LEFT;
	mw_dialog_file_chooser_data.list_box_file_data.number_of_lines = 5;
	mw_dialog_file_chooser_data.list_box_file_data.number_of_items = 0;
	mw_dialog_file_chooser_data.list_box_file_data.list_box_entries = NULL;
	mw_dialog_file_chooser_data.list_box_file_data.line_enables = MW_ALL_ITEMS_ENABLED;
	mw_util_safe_strcpy(mw_dialog_file_chooser_data.button_ok_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	mw_util_safe_strcpy(mw_dialog_file_chooser_data.button_cancel_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "Cancel");
	mw_util_safe_strcpy(mw_dialog_file_chooser_data.label_file_data.label,
			MW_UI_LABEL_MAX_CHARS,
			"No File");

	/* create controls */
	if (large_size)
	{
		mw_dialog_file_chooser_data.arrow_file_up_id = mw_ui_arrow_add_new(182,
				5,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_file_chooser_data.arrow_up_file_data);

		mw_dialog_file_chooser_data.arrow_file_down_id = mw_ui_arrow_add_new(182,
				112,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_file_chooser_data.arrow_down_file_data);

		mw_dialog_file_chooser_data.arrow_file_back_id = mw_ui_arrow_add_new(182,
				58,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_file_chooser_data.arrow_back_file_data);

		mw_dialog_file_chooser_data.list_box_file_id = mw_ui_list_box_add_new(5,
				5,
				170,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_file_chooser_data.list_box_file_data);

		mw_dialog_file_chooser_data.button_ok_id = mw_ui_button_add_new(5,
				175,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_file_chooser_data.button_ok_data);

		mw_dialog_file_chooser_data.button_cancel_id = mw_ui_button_add_new(112,
				175,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_file_chooser_data.button_cancel_data);

		mw_dialog_file_chooser_data.label_file_id = mw_ui_label_add_new(5,
				150,
				170,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_file_chooser_data.label_file_data);	}
	else
	{
		mw_dialog_file_chooser_data.arrow_file_up_id = mw_ui_arrow_add_new(130,
				5,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.arrow_up_file_data);

		mw_dialog_file_chooser_data.arrow_file_down_id = mw_ui_arrow_add_new(130,
				59,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.arrow_down_file_data);

		mw_dialog_file_chooser_data.arrow_file_back_id = mw_ui_arrow_add_new(130,
				31,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.arrow_back_file_data);

		mw_dialog_file_chooser_data.list_box_file_id = mw_ui_list_box_add_new(5,
				5,
				120,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.list_box_file_data);

		mw_dialog_file_chooser_data.button_ok_id = mw_ui_button_add_new(5,
				97,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_file_chooser_data.button_ok_data);

		mw_dialog_file_chooser_data.button_cancel_id = mw_ui_button_add_new(95,
				97,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_file_chooser_data.button_cancel_data);

		mw_dialog_file_chooser_data.label_file_id = mw_ui_label_add_new(5,
				80,
				120,
				mw_dialog_file_chooser_data.window_dialog_file_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_file_chooser_data.label_file_data);
	}

	/* check if controls could be created */
	if (mw_dialog_file_chooser_data.arrow_file_up_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_file_chooser_data.arrow_file_down_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_file_chooser_data.arrow_file_back_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_file_chooser_data.list_box_file_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_file_chooser_data.button_ok_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_file_chooser_data.button_cancel_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_file_chooser_data.label_file_id == MW_MAX_CONTROL_COUNT)
	{
		/* remove all controls and window */
		remove_resources();

		return MW_MAX_WINDOW_COUNT;
	}

	mw_dialog_file_chooser_data.lines_to_scroll = 0;
	mw_dialog_file_chooser_data.folder_depth = 0;
	mw_util_safe_strcpy(mw_dialog_file_chooser_data.folder_path,
			MAX_FOLDER_AND_FILE_NAME_LENGTH,
			start_path);

	for (i = 0; i < FILE_LIST_BOX_MAX_ENTRIES; i++)
	{
		mw_dialog_file_chooser_data.file_entries[i].label = file_entries_label[i];
		mw_dialog_file_chooser_data.file_entries[i].icon = NULL;
	}

	/* set list box entries pointer to windows entries array and entry count to 0 */
	mw_dialog_file_chooser_data.list_box_file_data.list_box_entries = mw_dialog_file_chooser_data.file_entries;
	mw_dialog_file_chooser_data.list_box_file_data.number_of_items = 0;

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_file_chooser_data.window_dialog_file_chooser_id, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_file_chooser_data.window_dialog_file_chooser_id);

	return mw_dialog_file_chooser_data.window_dialog_file_chooser_id;
}

#endif
