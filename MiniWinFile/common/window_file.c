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
#include <stdio.h>
#include <time.h>
#include "miniwin.h"
#include "ui/ui_common.h"
#include "dialogs/dialog_common.h"
#include "app.h"
#include "window_text.h"
#include "window_image.h"

/****************
*** CONSTANTS ***
****************/

#define TEXT_WINDOW_COUNT			3
#define IMAGE_WINDOW_COUNT			2
#define TEXT_FILE_EXTENSION			"txt"
#define IMAGE_FILE_EXTENSION		"bmp"

/************
*** TYPES ***
************/

typedef struct
{
	text_window_data_t text_windows_data[TEXT_WINDOW_COUNT];		/**< array of window data structures for text windows */
	image_window_data_t image_windows_data[IMAGE_WINDOW_COUNT];		/**< array of window data structures for image windows */
	struct tm set_time;												/**< Time/date from dialogs to send to hardware clock */
} window_file_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern uint8_t button_id;
extern uint8_t button_set_clock_id;
extern uint8_t label_time_id;
extern uint8_t label_date_id;
extern mw_ui_label_data_t label_time_data;
extern mw_ui_label_data_t label_date_data;
extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_file_data_t window_file_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static bool add_text_window(char *path_and_filename);
static bool add_image_window(char *path_and_filename);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Add a new text window if there is space available
 *
 * @param path_and_filename Path and filename of text file
 * @return true if window could be created else false
 */
static bool add_text_window(char *path_and_filename)
{
	mw_util_rect_t r;
	uint8_t new_window_id;
	uint8_t i;
	char *filename;

	if (!path_and_filename)
	{
		MW_ASSERT(false, "Null pointer");
		return false;
	}

	if (!mw_find_if_any_window_slots_free())
	{
		return false;
	}

	filename = strrchr(path_and_filename, '/');
	if (!filename)
	{
		MW_ASSERT(false, "No filename found");
		return false;
	}
	filename++;

	for (i = 0; i < TEXT_WINDOW_COUNT; i++)
	{
		if (window_file_data.text_windows_data[i].text_window_id == MW_MAX_WINDOW_COUNT)
		{
			mw_util_set_rect(&r, 10, 10, 100, 100);
			new_window_id = mw_add_window(&r,
				filename,
				window_text_paint_function,
				window_text_message_function,
				NULL,
				0,
				MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED,
				(void *)&window_file_data.text_windows_data[i]);

			window_file_data.text_windows_data[i].text_window_id  = new_window_id;

			mw_util_safe_strcpy(window_file_data.text_windows_data[i].path_and_filename_text,
					MAX_FOLDER_AND_FILE_NAME_LENGTH,
					path_and_filename);

			/* removal of the dialog choosing the image file causes a repaint all */
			mw_set_window_visible(new_window_id, true);

			return true;
		}
	}

	return false;
}

/**
 * Add a new image window if there is space available
 *
 * @param path_and_filename Path and filename of image file
 * @return true if window could be created else false
 */
static bool add_image_window(char *path_and_filename)
{
	mw_util_rect_t r;
	uint8_t new_window_id;
	uint8_t i;
	char *filename;

	if (!path_and_filename)
	{
		MW_ASSERT(false, "Null pointer");
		return false;
	}

	if (!mw_find_if_any_window_slots_free())
	{
		return false;
	}

	filename = strrchr(path_and_filename, '/');
	if (!filename)
	{
		MW_ASSERT(false, "No filename found");
		return false;
	}
	filename++;

	for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
	{
		if (window_file_data.image_windows_data[i].image_window_id == MW_MAX_WINDOW_COUNT)
		{
			mw_util_set_rect(&r, 10, 10, 100, 100);
			new_window_id = mw_add_window(&r,
				filename,
				window_image_paint_function,
				window_image_message_function,
				NULL,
				0,
				MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED,
				(void *)&window_file_data.image_windows_data[i]);

			window_file_data.image_windows_data[i].image_window_id  = new_window_id;

			mw_util_safe_strcpy(window_file_data.image_windows_data[i].path_and_filename_image,
					MAX_FOLDER_AND_FILE_NAME_LENGTH,
					path_and_filename);

			/* removal of the dialog choosing the image file causes a repaint all */
			mw_set_window_visible(new_window_id, true);

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

			for (i = 0; i < TEXT_WINDOW_COUNT; i++)
			{
				window_file_data.text_windows_data[i].text_window_id = MW_MAX_WINDOW_COUNT;
			}
			for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
			{
				window_file_data.image_windows_data[i].image_window_id = MW_MAX_WINDOW_COUNT;
			}

			mw_set_timer(mw_tick_counter + 20, message->recipient_id, MW_WINDOW_MESSAGE);
		}
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		{
			struct tm t;

			t = app_get_time_date();
			snprintf(label_time_data.label,
					MW_UI_LABEL_MAX_CHARS,
					"%02d:%02d:%02d",
					t.tm_hour,
					t.tm_min,
					t.tm_sec);

			snprintf(label_date_data.label,
					MW_UI_LABEL_MAX_CHARS,
					"%02d/%02d/%02d",
					t.tm_mday,
					t.tm_mon,
					t.tm_year);

			mw_paint_control(label_time_id);
			mw_paint_control(label_date_id);

			mw_set_timer(mw_tick_counter + 20, message->recipient_id, MW_WINDOW_MESSAGE);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_id == button_id)
		{
			mw_create_window_dialog_file_chooser(5,
					20,
					"Choose File",
					app_get_root_folder_path(),
					false,
					message->recipient_id);
		}
		else if (message->sender_id == button_set_clock_id)
		{
			mw_create_window_dialog_time_chooser(5,
					20,
					0,
					0,
					false,
					message->recipient_id);
		}
		break;

	case MW_DIALOG_DATE_CHOOSER_OK_MESSAGE:
		window_file_data.set_time.tm_mday = (int)(message->message_data & 0xff);
		window_file_data.set_time.tm_mon = (int)((message->message_data >> 8) & 0xff);
		window_file_data.set_time.tm_year = (int)(message->message_data >> 16);
		app_set_time_date(window_file_data.set_time);
		break;

	case MW_DIALOG_TIME_CHOOSER_OK_MESSAGE:
		window_file_data.set_time.tm_sec = 0;
		window_file_data.set_time.tm_hour = (int)(message->message_data >> 8);
		window_file_data.set_time.tm_min = (int)(message->message_data & 0xff);

		mw_create_window_dialog_date_chooser(5,
				20,
				1,
				1,
				2018,
				false,
				message->recipient_id);
		break;

	case MW_DIALOG_FILE_CHOOSER_OK_PTR_MESSAGE:
		{
			const char *extension;
			bool window_added;
			bool format_supported;
			char *item_chosen_path_and_filename;

			/* get the item chosen path and file name from message */
			item_chosen_path_and_filename = (char *)message->message_data;

			/* get filename extension */
			extension = mw_util_get_file_name_ext(item_chosen_path_and_filename);

			window_added = false;
			format_supported = false;
			if (mw_util_strcicmp(extension, TEXT_FILE_EXTENSION) == 0)
			{
				format_supported = true;
				window_added = add_text_window(item_chosen_path_and_filename);
			}
			else if (mw_util_strcicmp(extension, IMAGE_FILE_EXTENSION) == 0)
			{
				format_supported = true;
				window_added = add_image_window(item_chosen_path_and_filename);
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
