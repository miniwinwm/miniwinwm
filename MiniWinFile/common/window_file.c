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
#include <string.h>
#include "miniwin.h"
#include "ui/ui_common.h"
#include "dialogs/dialog_common.h"
#include "app.h"
#include "window_text.h"
#include "window_image.h"

/****************
*** CONSTANTS ***
****************/

#define FILE_LIST_BOX_MAX_ENTRIES 	MW_UI_LIST_BOX_MAX_ENTRIES
#define TEXT_WINDOW_COUNT			3
#define IMAGE_WINDOW_COUNT			2
#define TEXT_FILE_EXTENSION			"txt"
#define IMAGE_FILE_EXTENSION		"bmp"

/************
*** TYPES ***
************/

typedef struct
{
	uint8_t lines_to_scroll;										/**< number of lines list box is scrolled */
	mw_ui_list_box_entry file_entries[FILE_LIST_BOX_MAX_ENTRIES]; 	/**< the actual storage for the folder entries data the list box shows */
	char folder_path[MAX_FOLDER_AND_FILE_NAME_LENGTH];				/**< path to most recently chosen folder */
	uint8_t folder_depth;											/**< root is zero, increments for every sub-folder */
	text_window_data_t text_windows_data[TEXT_WINDOW_COUNT];		/**< array of window data structures for text windows */
	image_window_data_t image_windows_data[IMAGE_WINDOW_COUNT];		/**< array of window data structures for image windows */
} window_file_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern uint8_t button_id;
extern uint8_t list_box_file_id;
extern uint8_t arrow_file_up_id;
extern uint8_t arrow_file_down_id;
extern uint8_t arrow_file_back_id;
extern uint8_t label_file_id;
extern uint8_t label_folder_id;
extern mw_ui_list_box_data_t list_box_file_data;
extern const uint8_t mw_bitmaps_file_icon_small[];
extern const uint8_t mw_bitmaps_folder_icon_small[];

/**********************
*** LOCAL VARIABLES ***
**********************/

static char file_entries_label[FILE_LIST_BOX_MAX_ENTRIES][MAX_FILE_NAME_LENGTH + 1];
static window_file_data_t window_file_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void update_folder_entries(void);
static bool add_text_window(char *path, char *file_name);
static bool add_image_window(char *path, char *file_name);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void update_folder_entries(void)
{
	list_box_file_data.number_of_items = find_directory_entries(window_file_data.folder_path,
			window_file_data.file_entries,
			FILE_LIST_BOX_MAX_ENTRIES);

	if (list_box_file_data.number_of_lines < list_box_file_data.number_of_items)
	{
		mw_set_control_enabled(arrow_file_down_id, true);
	}
	else
	{
		mw_set_control_enabled(arrow_file_down_id, false);
	}

	if (window_file_data.folder_depth == 0)
	{
		mw_set_control_enabled(arrow_file_back_id, false);
	}
	else
	{
		mw_set_control_enabled(arrow_file_back_id, true);
	}

	mw_paint_control(arrow_file_up_id);
	mw_paint_control(arrow_file_down_id);
	mw_paint_control(arrow_file_back_id);
	mw_paint_control(list_box_file_id);
}

/**
 * Add a new text window if there is space available
 *
 * @param path path to text file
 * @param file_name file name of text file
 * @return true if window could be created else false
 */
static bool add_text_window(char *path, char *file_name)
{
	mw_util_rect_t r;
	uint8_t new_window_id;
	uint8_t i;

	if (!mw_find_if_any_window_slots_free())
	{
		return false;
	}

	for (i = 0; i < TEXT_WINDOW_COUNT; i++)
	{
		if (window_file_data.text_windows_data[i].text_window_id == MW_MAX_WINDOW_COUNT)
		{
			mw_util_set_rect(&r, 10, 10, 100, 100);
			new_window_id = mw_add_window(&r,
				file_name,
				window_text_paint_function,
				window_text_message_function,
				NULL,
				0,
				MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED,
				(void *)&window_file_data.text_windows_data[i]);

			window_file_data.text_windows_data[i].text_window_id  = new_window_id;
			mw_util_safe_strcpy(window_file_data.text_windows_data[i].path_and_filename_text,
					MAX_FOLDER_AND_FILE_NAME_LENGTH,
					window_file_data.folder_path);
			if (window_file_data.folder_depth > 0)
			{
				mw_util_safe_strcat(window_file_data.text_windows_data[i].path_and_filename_text,
						MAX_FOLDER_AND_FILE_NAME_LENGTH,
						"/");
			}
			mw_util_safe_strcat(window_file_data.text_windows_data[i].path_and_filename_text,
					MAX_FOLDER_AND_FILE_NAME_LENGTH,
					file_name);

			mw_set_window_visible(new_window_id, true);
			mw_paint_window_frame(new_window_id, MW_WINDOW_FRAME_COMPONENT_ALL);
			mw_paint_window_client(new_window_id);

			return true;
		}
	}

	return false;
}

/**
 * Add a new image window if there is space available
 *
 * @param path path to image file
 * @param file_name file name of image file
 * @return true if window could be created else false
 */
static bool add_image_window(char *path, char *file_name)
{
	mw_util_rect_t r;
	uint8_t new_window_id;
	uint8_t i;

	if (!mw_find_if_any_window_slots_free())
	{
		return false;
	}

	for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
	{
		if (window_file_data.image_windows_data[i].image_window_id == MW_MAX_WINDOW_COUNT)
		{
			mw_util_set_rect(&r, 10, 10, 100, 100);
			new_window_id = mw_add_window(&r,
				file_name,
				window_image_paint_function,
				window_image_message_function,
				NULL,
				0,
				MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED,
				(void *)&window_file_data.image_windows_data[i]);

			window_file_data.image_windows_data[i].image_window_id  = new_window_id;
			mw_util_safe_strcpy(window_file_data.image_windows_data[i].path_and_filename_image,
					MAX_FOLDER_AND_FILE_NAME_LENGTH,
					window_file_data.folder_path);
			if (window_file_data.folder_depth > 0)
			{
				mw_util_safe_strcat(window_file_data.image_windows_data[i].path_and_filename_image,
						MAX_FOLDER_AND_FILE_NAME_LENGTH,
						"/");
			}
			mw_util_safe_strcat(window_file_data.image_windows_data[i].path_and_filename_image,
					MAX_FOLDER_AND_FILE_NAME_LENGTH,
					file_name);

			mw_set_window_visible(new_window_id, true);
			mw_paint_window_frame(new_window_id, MW_WINDOW_FRAME_COMPONENT_ALL);
			mw_paint_window_client(new_window_id);

			return true;
		}
	}

	return false;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_file_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info, "Null pointer parameter");

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

void window_file_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		{
			uint8_t i;

			/* on window creation initialize window data structure */
			window_file_data.lines_to_scroll = 0;
			window_file_data.folder_depth = 0;
			mw_util_safe_strcpy(window_file_data.folder_path,
					MAX_FOLDER_AND_FILE_NAME_LENGTH,
					app_get_root_folder_path());
			for (i = 0; i < TEXT_WINDOW_COUNT; i++)
			{
				window_file_data.text_windows_data[i].text_window_id = MW_MAX_WINDOW_COUNT;
			}
			for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
			{
				window_file_data.image_windows_data[i].image_window_id = MW_MAX_WINDOW_COUNT;
			}
			for (i = 0; i < FILE_LIST_BOX_MAX_ENTRIES; i++)
			{
				window_file_data.file_entries[i].label = file_entries_label[i];
				window_file_data.file_entries[i].icon = NULL;
			}

			/* disable all arrows */
			mw_set_control_enabled(arrow_file_up_id, false);
			mw_set_control_enabled(arrow_file_down_id, false);
			mw_set_control_enabled(arrow_file_back_id, false);

			/* set list box entries pointer to windows entries array and entry count to 0 */
			list_box_file_data.list_box_entries = window_file_data.file_entries;
			list_box_file_data.number_of_items = 0;

			/* initialise labels */
			mw_ui_common_post_pointer_to_control(label_folder_id, window_file_data.folder_path);
			mw_paint_control(label_folder_id);
			mw_ui_common_post_pointer_to_control(label_file_id, "File: Not chosen");
			mw_paint_control(label_file_id);
		}
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if (message->message_data == MW_UI_ARROW_UP && window_file_data.lines_to_scroll > 0)
		{
			/* up arrow, scroll list box up is ok to do so */
			window_file_data.lines_to_scroll--;

			if (window_file_data.lines_to_scroll == 0)
			{
				mw_set_control_enabled(arrow_file_up_id, false);
				mw_paint_control(arrow_file_up_id);
			}

			mw_set_control_enabled(arrow_file_down_id, true);
			mw_paint_control(arrow_file_down_id);

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					list_box_file_id,
					window_file_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_file_id);
		}
		else if (message->message_data == MW_UI_ARROW_DOWN &&
				window_file_data.lines_to_scroll < (list_box_file_data.number_of_items - list_box_file_data.number_of_lines))
		{
			/* down arrow, scroll list box down is ok to do so */
			window_file_data.lines_to_scroll++;

			if (window_file_data.lines_to_scroll == list_box_file_data.number_of_items - list_box_file_data.number_of_lines)
			{
				mw_set_control_enabled(arrow_file_down_id, false);
				mw_paint_control(arrow_file_down_id);
			}

			mw_set_control_enabled(arrow_file_up_id, true);
			mw_paint_control(arrow_file_up_id);

			mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
					0,
					list_box_file_id,
					window_file_data.lines_to_scroll,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_file_id);
		}
		else if (message->message_data == MW_UI_ARROW_LEFT)
		{
			/* left arrow, go up a folder path */
			*strrchr(window_file_data.folder_path, '/') = '\0';
			window_file_data.folder_depth--;

			/* check if back to root and if so add / again as it's the only folder that ends in a '/' */
			if (window_file_data.folder_depth == 0)
			{
				mw_util_safe_strcat(window_file_data.folder_path, MAX_FOLDER_AND_FILE_NAME_LENGTH, "/");
			}
			update_folder_entries();

			/* update label with name of folder chosen */
			mw_ui_common_post_pointer_to_control(label_folder_id, window_file_data.folder_path);
			mw_paint_control(label_folder_id);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_id == button_id)
		{
			update_folder_entries();
		}
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		{
			const char *extension;
			bool window_added;
			bool format_supported;

			/* list box item pressed, get the item chosen number */
			uint8_t item_chosen = message->message_data;

			if (list_box_file_data.list_box_entries[item_chosen].icon == mw_bitmaps_folder_icon_small)
			{
				/* folder chosen */

				/* update label with file not chosen */
				mw_ui_common_post_pointer_to_control(label_file_id, "File: Not chosen");
				mw_paint_control(label_file_id);

				/* change directory to list_box_file_data.list_box_entries[item_chosen].label
				 * create new folder path by adding / and then the sub-folder name, but don't add /
				 * to root folder path as it ends in / already
				 */
				if (window_file_data.folder_depth > 0)
				{
					mw_util_safe_strcat(window_file_data.folder_path, MAX_FOLDER_AND_FILE_NAME_LENGTH, "/");
				}
				mw_util_safe_strcat(window_file_data.folder_path, MAX_FOLDER_AND_FILE_NAME_LENGTH, list_box_file_data.list_box_entries[item_chosen].label);

				/* increment sub-folder depth counter */
				window_file_data.folder_depth++;

				/* now get the new sub-folder's entries */
				update_folder_entries();

				/* update folder label with name of folder chosen */
				mw_ui_common_post_pointer_to_control(label_folder_id, window_file_data.folder_path);
				mw_paint_control(label_folder_id);
			}
			else if (list_box_file_data.list_box_entries[item_chosen].icon == mw_bitmaps_file_icon_small)
			{
				/* file chosen */

				/* update label with name of file chosen */
				mw_ui_common_post_pointer_to_control(label_file_id, list_box_file_data.list_box_entries[item_chosen].label);
				mw_paint_control(label_file_id);

				/* open file list_box_file_data.list_box_entries[item_chosen].label here */

				/* get filename extension */
				extension = mw_util_get_file_name_ext(list_box_file_data.list_box_entries[item_chosen].label);

				window_added = false;
				format_supported = false;
				if (mw_util_strcicmp(extension, TEXT_FILE_EXTENSION) == 0)
				{
					format_supported = true;
					window_added = add_text_window(window_file_data.folder_path,
							list_box_file_data.list_box_entries[item_chosen].label);
				}
				else if (mw_util_strcicmp(extension, IMAGE_FILE_EXTENSION) == 0)
				{
					format_supported = true;
					window_added = add_image_window(window_file_data.folder_path,
							list_box_file_data.list_box_entries[item_chosen].label);
				}
				else
				{
					/* format not supported, show dialog warning */
					mw_create_window_dialog_one_button(20,
							50,
							150,
							"Warning",
							"Format not supported.",
							"OK",
							false,
							message->recipient_id);
				}

				if (format_supported && !window_added)
				{
					/* format supported but window couldn't be added, show warning */
					mw_create_window_dialog_one_button(20,
							50,
							150,
							"Warning",
							"No more windows.",
							"OK",
							false,
							message->recipient_id);
				}

				/* repaint this window too as it's lost focus */
				mw_paint_window_frame(message->recipient_id, MW_WINDOW_FRAME_COMPONENT_ALL);
				mw_paint_window_client(message->recipient_id);
			}
		}
		break;

	case MW_TRANSFER_DATA_1_MESSAGE:
		/* a pop up window has been closed */
		{
			uint8_t i;

			for (i = 0; i < TEXT_WINDOW_COUNT; i++)
			{
				if (message->sender_id == window_file_data.text_windows_data[i].text_window_id)
				{
					window_file_data.text_windows_data[i].text_window_id = MW_MAX_WINDOW_COUNT;
					break;
				}
			}
			for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
			{
				if (message->sender_id == window_file_data.image_windows_data[i].image_window_id)
				{
					window_file_data.image_windows_data[i].image_window_id = MW_MAX_WINDOW_COUNT;
					break;
				}
			}
		}
		break;

	default:
		break;
	}
}
