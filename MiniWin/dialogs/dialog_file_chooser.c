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
#include "dialogs/dialog_common.h"
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
	mw_handle_t button_ok_handle;									/**< Control handle of ok button */
	mw_handle_t button_cancel_handle;								/**< Control handle of cancel button */
	mw_handle_t list_box_file_handle;								/**< Control handle of list box for folders and files */
	mw_handle_t arrow_file_up_handle;								/**< Control handle of up arrow */
	mw_handle_t arrow_file_down_handle;								/**< Control handle of down arrow */
	mw_handle_t arrow_file_back_handle;								/**< Control handle of back arrow, to parent folder */
	mw_handle_t label_choice_handle;								/**< Control handle of choice label */
	mw_handle_t owner_window_handle;								/**< Handle to send response message to */
	mw_handle_t file_chooser_dialog_window_handle;					/**< Handle of file chooser dialog window */
	uint8_t lines_to_scroll;										/**< Number of lines list box is scrolled */
	uint8_t folder_depth;											/**< Root is zero, increments for every sub-folder */
	bool folders_only;												/**< If to show folders only */
	bool large_size;												/**< True for large size false for standard size */
	mw_ui_list_box_entry file_entries[FILE_LIST_BOX_MAX_ENTRIES]; 	/**< The storage for the folder entries data the list box shows; an entry contains pointers; icons and labels must exist elsewhere */
	char folder_path[MAX_FOLDER_AND_FILENAME_LENGTH + 1];			/**< Path to most recently chosen folder, and path and file name when dialog dismissed */
	mw_ui_list_box_data_t list_box_file_data;						/**< Instance data of list box */
	mw_ui_arrow_data_t arrow_up_file_data;							/**< Instance data of up arrow */
	mw_ui_arrow_data_t arrow_down_file_data;						/**< Instance data of down arrow */
	mw_ui_arrow_data_t arrow_back_file_data;						/**< Instance data of back arrow */
	mw_ui_button_data_t button_ok_data;								/**< Instance data of ok button */
	mw_ui_button_data_t button_cancel_data;							/**< Instance data of cancel button */
	mw_ui_label_data_t label_choice_data;							/**< Instance data of choice data */
	char *message;													/**< Text to display in dialog */
	uint16_t max_scroll_lines;										/**< Maximum lines the list box can scroll, depends on data currently in list box */
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

static char file_entries_label[FILE_LIST_BOX_MAX_ENTRIES][MAX_FILENAME_LENGTH + 1];
static mw_dialog_file_chooser_data_t mw_dialog_file_chooser_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void update_folder_entries(bool folders_only);
static void mw_dialog_file_chooser_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_file_chooser_message_function(const mw_message_t *message);
static uint8_t get_folder_depth(char *path);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Get the depth of a folder
 *
 * @param path The path to analyse
 * @return The folder depth
 */
static uint8_t get_folder_depth(char *path)
{
	uint8_t depth = 0;
	uint16_t i;

	for (i = 0; i < strlen(path); i++)
	{
		if (path[i] == '/')
		{
			depth++;
		}
	}

	depth--;

	return depth;
}

/**
 * Update the list box with the current folder's entries
 *
 * @param folders_only true if to search for folders only
 */
static void update_folder_entries(bool folders_only)
{
	if (mw_dialog_file_chooser_data.large_size)
	{
		mw_dialog_file_chooser_data.list_box_file_data.number_of_items = find_folder_entries(mw_dialog_file_chooser_data.folder_path,
				mw_dialog_file_chooser_data.file_entries,
				folders_only,
				FILE_LIST_BOX_MAX_ENTRIES,
				mw_bitmaps_file_icon_large,
				mw_bitmaps_folder_icon_large);
	}
	else
	{
		mw_dialog_file_chooser_data.list_box_file_data.number_of_items = find_folder_entries(mw_dialog_file_chooser_data.folder_path,
				mw_dialog_file_chooser_data.file_entries,
				folders_only,
				FILE_LIST_BOX_MAX_ENTRIES,
				mw_bitmaps_file_icon_small,
				mw_bitmaps_folder_icon_small);
	}

	/* let the list box know of new data */
	mw_post_message(MW_LIST_BOX_SET_ENTRIES_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			mw_dialog_file_chooser_data.list_box_file_handle,
			mw_dialog_file_chooser_data.list_box_file_data.number_of_items,
			(void *)mw_dialog_file_chooser_data.file_entries,
			MW_CONTROL_MESSAGE);

	/* up arrow always disabled on new data as scrolling will be at top position */
	mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_up_handle, false);

	/* update enabled state of back arrow depending on folder depth */
	if (mw_dialog_file_chooser_data.folder_depth == 0)
	{
		mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_back_handle, false);
	}
	else
	{
		mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_back_handle, true);
	}

	/* paint arrows updated here */
	mw_paint_control(mw_dialog_file_chooser_data.arrow_file_up_handle);
	mw_paint_control(mw_dialog_file_chooser_data.arrow_file_back_handle);
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_handle The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_file_chooser_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);
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
		update_folder_entries(mw_dialog_file_chooser_data.folders_only);
		break;

	case MW_LIST_BOX_SCROLLING_REQUIRED_MESSAGE:
		mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_down_handle, message->message_data >> 16);
		mw_dialog_file_chooser_data.max_scroll_lines = message->message_data & 0xffff;
		mw_paint_control(mw_dialog_file_chooser_data.arrow_file_down_handle);
		mw_paint_control(mw_dialog_file_chooser_data.list_box_file_handle);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		{
			/* remove all controls and window */
			mw_remove_window(mw_dialog_file_chooser_data.file_chooser_dialog_window_handle);

			/* a window has changed visibility so repaint all */
			mw_paint_all();

			if (message->sender_handle == mw_dialog_file_chooser_data.button_cancel_handle)
			{
				/* post cancel response to receiving window */
				mw_post_message(MW_DIALOG_FILE_CHOOSER_CANCEL_MESSAGE,
						MW_UNUSED_MESSAGE_PARAMETER,
						mw_dialog_file_chooser_data.owner_window_handle,
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_WINDOW_MESSAGE);
			}
			else
			{
				/* post ok response to receiving window */
				if (mw_dialog_file_chooser_data.folders_only)
				{
					/* post folder ok response to receiving window */
					mw_post_message(MW_DIALOG_FILE_CHOOSER_FOLDER_OK_MESSAGE,
							MW_UNUSED_MESSAGE_PARAMETER,
							mw_dialog_file_chooser_data.owner_window_handle,
							MW_UNUSED_MESSAGE_PARAMETER,
							(void *)mw_dialog_file_chooser_data.folder_path,
							MW_WINDOW_MESSAGE);
				}
				else
				{
					/* post file ok response to receiving window */
					if (mw_dialog_file_chooser_data.folder_depth > 0)
					{
						mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
								MAX_FOLDER_AND_FILENAME_LENGTH,
								"/");
					}

					/* add the file name */
					mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
							MAX_FOLDER_AND_FILENAME_LENGTH,
							mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[mw_dialog_file_chooser_data.list_box_file_data.selection].label);

					/* post file ok response to receiving window */
					mw_post_message(MW_DIALOG_FILE_CHOOSER_FILE_OK_MESSAGE,
							MW_UNUSED_MESSAGE_PARAMETER,
							mw_dialog_file_chooser_data.owner_window_handle,
							MW_UNUSED_MESSAGE_PARAMETER,
							(void *)mw_dialog_file_chooser_data.folder_path,
							MW_WINDOW_MESSAGE);
				}
			}
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
				mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_up_handle, false);
				mw_paint_control(mw_dialog_file_chooser_data.arrow_file_up_handle);
			}

			mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_down_handle, true);
			mw_paint_control(mw_dialog_file_chooser_data.arrow_file_down_handle);

			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					0,
					mw_dialog_file_chooser_data.list_box_file_handle,
					mw_dialog_file_chooser_data.lines_to_scroll,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(mw_dialog_file_chooser_data.list_box_file_handle);
		}
		else if (message->message_data == MW_UI_ARROW_DOWN &&
				mw_dialog_file_chooser_data.lines_to_scroll < mw_dialog_file_chooser_data.max_scroll_lines)
		{
			/* down arrow, scroll list box down is ok to do so */
			mw_dialog_file_chooser_data.lines_to_scroll++;

			if (mw_dialog_file_chooser_data.lines_to_scroll ==
					mw_dialog_file_chooser_data.max_scroll_lines)
			{
				mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_down_handle, false);
				mw_paint_control(mw_dialog_file_chooser_data.arrow_file_down_handle);
			}

			mw_set_control_enabled(mw_dialog_file_chooser_data.arrow_file_up_handle, true);
			mw_paint_control(mw_dialog_file_chooser_data.arrow_file_up_handle);

			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					0,
					mw_dialog_file_chooser_data.list_box_file_handle,
					mw_dialog_file_chooser_data.lines_to_scroll,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(mw_dialog_file_chooser_data.list_box_file_handle);
		}
		else if (message->message_data == MW_UI_ARROW_LEFT)
		{
			/* left arrow, go up a folder path */
			*strrchr(mw_dialog_file_chooser_data.folder_path, '/') = '\0';
			*strrchr(mw_dialog_file_chooser_data.folder_path, '/') = '\0';
			strcat(mw_dialog_file_chooser_data.folder_path, "/");
			mw_dialog_file_chooser_data.folder_depth--;

			/* update folder entries for this new folder */
			update_folder_entries(mw_dialog_file_chooser_data.folders_only);
			if (mw_dialog_file_chooser_data.folders_only)
			{
				/* update label with folder chosen */
				mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
						message->recipient_handle,
						mw_dialog_file_chooser_data.label_choice_handle,
						MW_UNUSED_MESSAGE_PARAMETER,
						(void *)mw_dialog_file_chooser_data.folder_path,
						MW_CONTROL_MESSAGE);
				mw_paint_control(mw_dialog_file_chooser_data.label_choice_handle);
			}

			/* new folder so grey out ok button and reset label if choosing a file */
			if (!mw_dialog_file_chooser_data.folders_only)
			{
				mw_set_control_enabled(mw_dialog_file_chooser_data.button_ok_handle, false);
				mw_paint_control(mw_dialog_file_chooser_data.button_ok_handle);
				mw_util_safe_strcpy(mw_dialog_file_chooser_data.label_choice_data.label,
						MW_UI_LABEL_MAX_CHARS,
						"No File");
				mw_paint_control(mw_dialog_file_chooser_data.label_choice_handle);
			}
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
				/* new folder so grey out ok button and reset label if choosing a file */
				if (!mw_dialog_file_chooser_data.folders_only)
				{
					mw_util_safe_strcpy(mw_dialog_file_chooser_data.label_choice_data.label,
							MW_UI_LABEL_MAX_CHARS,
							"No File");
					mw_paint_control(mw_dialog_file_chooser_data.label_choice_handle);
					mw_set_control_enabled(mw_dialog_file_chooser_data.button_ok_handle, false);
					mw_paint_control(mw_dialog_file_chooser_data.button_ok_handle);
				}

				mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
						MAX_FOLDER_AND_FILENAME_LENGTH,
						mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].label);
				mw_util_safe_strcat(mw_dialog_file_chooser_data.folder_path,
										MAX_FOLDER_AND_FILENAME_LENGTH,
										"/");

				/* increment sub-folder depth counter */
				mw_dialog_file_chooser_data.folder_depth++;

				/* now get the new sub-folder's entries */
				update_folder_entries(mw_dialog_file_chooser_data.folders_only);

				/* update label */
				if (mw_dialog_file_chooser_data.folders_only)
				{
					/* update label with folder chosen */
					mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
							message->recipient_handle,
							mw_dialog_file_chooser_data.label_choice_handle,
							MW_UNUSED_MESSAGE_PARAMETER,
							(void *)mw_dialog_file_chooser_data.folder_path,
							MW_CONTROL_MESSAGE);
				}
				else
				{
					/* update label with file not chosen */
					mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
							message->recipient_handle,
							mw_dialog_file_chooser_data.label_choice_handle,
							MW_UNUSED_MESSAGE_PARAMETER,
							(void *)"No File",
							MW_CONTROL_MESSAGE);
				}
				mw_paint_control(mw_dialog_file_chooser_data.label_choice_handle);
			}
			else if ((mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].icon ==
					mw_bitmaps_file_icon_large && mw_dialog_file_chooser_data.large_size) ||
					(mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].icon ==
					mw_bitmaps_file_icon_small && !mw_dialog_file_chooser_data.large_size))
			{
				/* new file chosen so enable ok button */
				mw_set_control_enabled(mw_dialog_file_chooser_data.button_ok_handle, true);
				mw_paint_control(mw_dialog_file_chooser_data.button_ok_handle);

				/* file chosen, update label with name of file chosen */
				mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
						message->recipient_handle,
						mw_dialog_file_chooser_data.label_choice_handle,
						MW_UNUSED_MESSAGE_PARAMETER,
						(void *)mw_dialog_file_chooser_data.list_box_file_data.list_box_entries[item_chosen].label,
						MW_CONTROL_MESSAGE);
				mw_paint_control(mw_dialog_file_chooser_data.label_choice_handle);
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

mw_handle_t mw_create_window_dialog_file_chooser(uint16_t x,
		uint16_t y,
		char *title,
		char *start_path,
		bool folders_only,
		bool large_size,
		mw_handle_t owner_window_handle)
{
	mw_util_rect_t rect;
	uint8_t i;

	/* check pointer parameters */
	if (!title)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_INVALID_HANDLE;
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
		return MW_INVALID_HANDLE;
	}
	if (y + rect.height > MW_ROOT_HEIGHT)
	{
		return MW_INVALID_HANDLE;
	}

	/* check response window handle */
	if (!mw_is_window_handle_valid(owner_window_handle))
	{
		return MW_INVALID_HANDLE;
	}

	mw_dialog_file_chooser_data.large_size = large_size;
	mw_dialog_file_chooser_data.owner_window_handle = owner_window_handle;
	rect.x = x;
	rect.y = y;

	/* save folders_only flag */
	mw_dialog_file_chooser_data.folders_only = folders_only;

	mw_dialog_file_chooser_data.file_chooser_dialog_window_handle = mw_add_window(&rect,
			title,
			mw_dialog_file_chooser_paint_function,
			mw_dialog_file_chooser_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_file_chooser_data.file_chooser_dialog_window_handle == MW_INVALID_HANDLE)
	{
		/* it couldn't so exit */
		return MW_INVALID_HANDLE;
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
	if (mw_dialog_file_chooser_data.folders_only)
	{
		mw_util_safe_strcpy(mw_dialog_file_chooser_data.label_choice_data.label,
				MW_UI_LABEL_MAX_CHARS,
				app_get_root_folder_path());
	}
	else
	{
		mw_util_safe_strcpy(mw_dialog_file_chooser_data.label_choice_data.label,
				MW_UI_LABEL_MAX_CHARS,
				"No File");
	}

	/* create controls */
	if (large_size)
	{
		mw_dialog_file_chooser_data.arrow_file_up_handle = mw_ui_arrow_add_new(182,
				5,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_file_chooser_data.arrow_up_file_data);

		mw_dialog_file_chooser_data.arrow_file_down_handle = mw_ui_arrow_add_new(182,
				112,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_file_chooser_data.arrow_down_file_data);

		mw_dialog_file_chooser_data.arrow_file_back_handle = mw_ui_arrow_add_new(182,
				58,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_file_chooser_data.arrow_back_file_data);

		mw_dialog_file_chooser_data.list_box_file_handle = mw_ui_list_box_add_new(5,
				5,
				170,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_file_chooser_data.list_box_file_data);

		mw_dialog_file_chooser_data.button_ok_handle = mw_ui_button_add_new(5,
				175,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_file_chooser_data.button_ok_data);

		mw_dialog_file_chooser_data.button_cancel_handle = mw_ui_button_add_new(112,
				175,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_file_chooser_data.button_cancel_data);

		mw_dialog_file_chooser_data.label_choice_handle = mw_ui_label_add_new(5,
				150,
				209,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_file_chooser_data.label_choice_data);
	}
	else
	{
		mw_dialog_file_chooser_data.arrow_file_up_handle = mw_ui_arrow_add_new(130,
				5,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.arrow_up_file_data);

		mw_dialog_file_chooser_data.arrow_file_down_handle = mw_ui_arrow_add_new(130,
				59,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.arrow_down_file_data);

		mw_dialog_file_chooser_data.arrow_file_back_handle = mw_ui_arrow_add_new(130,
				31,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.arrow_back_file_data);

		mw_dialog_file_chooser_data.list_box_file_handle = mw_ui_list_box_add_new(5,
				5,
				120,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.list_box_file_data);

		mw_dialog_file_chooser_data.button_ok_handle = mw_ui_button_add_new(5,
				97,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_file_chooser_data.button_ok_data);

		mw_dialog_file_chooser_data.button_cancel_handle = mw_ui_button_add_new(95,
				97,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_file_chooser_data.button_cancel_data);

		mw_dialog_file_chooser_data.label_choice_handle = mw_ui_label_add_new(5,
				80,
				142,
				mw_dialog_file_chooser_data.file_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_file_chooser_data.label_choice_data);
	}

	/* check if controls could be created */
	if (mw_dialog_file_chooser_data.arrow_file_up_handle == MW_INVALID_HANDLE ||
			mw_dialog_file_chooser_data.arrow_file_down_handle == MW_INVALID_HANDLE ||
			mw_dialog_file_chooser_data.arrow_file_back_handle == MW_INVALID_HANDLE ||
			mw_dialog_file_chooser_data.list_box_file_handle == MW_INVALID_HANDLE ||
			mw_dialog_file_chooser_data.button_ok_handle == MW_INVALID_HANDLE ||
			mw_dialog_file_chooser_data.button_cancel_handle == MW_INVALID_HANDLE ||
			mw_dialog_file_chooser_data.label_choice_handle == MW_INVALID_HANDLE)
	{
		/* remove all controls and window */
		mw_remove_window(mw_dialog_file_chooser_data.file_chooser_dialog_window_handle);

		return MW_INVALID_HANDLE;
	}

	mw_dialog_file_chooser_data.lines_to_scroll = 0;
	mw_util_safe_strcpy(mw_dialog_file_chooser_data.folder_path,
			MAX_FOLDER_AND_FILENAME_LENGTH,
			start_path);

	for (i = 0; i < FILE_LIST_BOX_MAX_ENTRIES; i++)
	{
		mw_dialog_file_chooser_data.file_entries[i].label = file_entries_label[i];
		mw_dialog_file_chooser_data.file_entries[i].icon = NULL;
	}

	/* set list box entries pointer to windows entries array */
	mw_dialog_file_chooser_data.list_box_file_data.list_box_entries = mw_dialog_file_chooser_data.file_entries;

	/* set up enabled state of ok button, always enabled if choosing a folder */
	if (folders_only)
	{
		mw_set_control_enabled(mw_dialog_file_chooser_data.button_ok_handle, true);
	}

	/* owner window needs its title bar redrawing */
	mw_paint_window_frame(owner_window_handle, MW_WINDOW_FRAME_COMPONENT_TITLE_BAR);

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_file_chooser_data.file_chooser_dialog_window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_file_chooser_data.file_chooser_dialog_window_handle);

	return mw_dialog_file_chooser_data.file_chooser_dialog_window_handle;
}

#endif
