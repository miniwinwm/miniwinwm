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

#include <string.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_file.h"
#include "window_text.h"
#include "window_image.h"

/****************
*** CONSTANTS ***
****************/

#define TEXT_WINDOW_COUNT			3U		/**< Maximum number of text windows concurrently open */
#define IMAGE_WINDOW_COUNT			2U		/**< Maximum number of image windows concurrently open */
#define TEXT_FILE_EXTENSION			"txt"	/**< Text file extension */
#define IMAGE_FILE_EXTENSION		"bmp"	/**< Image file extension */

/************
*** TYPES ***
************/

/**
 * Window instance data structure
 */
typedef struct
{
	text_window_data_t text_windows_data[TEXT_WINDOW_COUNT];				/**< Array of window instance data structures for text windows */
	image_window_data_t image_windows_data[IMAGE_WINDOW_COUNT];				/**< Array of window instance data structures for image windows */
	mw_time_t set_time;														/**< Time/date from dialogs to send to hardware clock */
	char create_path_and_filename[MAX_FOLDER_AND_FILENAME_LENGTH + 1];		/**< Path and file name for file to create */
} window_file_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_file_data_t window_file_data;
static char time_text[MW_UI_LABEL_MAX_CHARS + 1U];
static char date_text[MW_UI_LABEL_MAX_CHARS + 1U];
static char button_yes_label[] = "Yes";
static char button_no_label[] = "No";
static char button_ok_label[] = "OK";
static char button_warning_label[] = "Warning";
static char no_more_windows_message[] = "No more windows.";
static char choose_file_message[] = "Choose file";
static char choose_folder_message[] = "Choose folder";
static char file_already_exists_message[] = "File already exists. Overwrite?";
static char creating_file_message[] = "Creating file";
static char new_file_name_message[] = "New file name";
static char empty_message[] = "";

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static bool add_text_window(char *path_and_filename);
static bool add_image_window(char *path_and_filename);
static void create_new_file(mw_handle_t response_window_handle);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Create a new text file and add some text
 */
static void create_new_file(mw_handle_t response_window_handle)
{
	if (app_file_create(window_file_data.create_path_and_filename))
	{
		app_file_write((uint8_t *)"Created by MiniWin File example app.\n", 37);
		app_file_close();
		(void)mw_create_window_dialog_one_button(20,
				20,
				175,
				"File create",
				"File created successfully",
				"Ok",
				false,
				response_window_handle);
	}
	else
	{
		(void)mw_create_window_dialog_one_button(20,
				20,
				150,
				"File create",
				"Could not create file",
				"Ok",
				false,
				response_window_handle);
	}
}

/**
 * Add a new text window if there is space available
 *
 * @param path_and_filename Path and filename of text file
 * @return true if window could be created else false
 */
static bool add_text_window(char *path_and_filename)
{
	mw_util_rect_t r;
	mw_handle_t new_window_handle;
	uint8_t i;
	char *filename;

	if (path_and_filename == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");
		return false;
	}

	if (!mw_find_if_any_window_slots_free())
	{
		return false;
	}

	filename = strrchr(path_and_filename, (long)'/');
	if (filename == NULL)
	{
		MW_ASSERT((bool)false, "No filename found");
		return false;
	}
	filename++;

	for (i = 0; i < TEXT_WINDOW_COUNT; i++)
	{
		if (window_file_data.text_windows_data[i].text_window_handle == MW_INVALID_HANDLE)
		{
			mw_util_set_rect(&r, 10, 10, 100, 100);
			new_window_handle = mw_add_window(&r,
				filename,
				window_text_paint_function,
				window_text_message_function,
				NULL,
				0,
				MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
				(void *)&window_file_data.text_windows_data[i]);

			window_file_data.text_windows_data[i].text_window_handle  = new_window_handle;

			(void)mw_util_safe_strcpy(window_file_data.text_windows_data[i].path_and_filename_text,
					MAX_FOLDER_AND_FILENAME_LENGTH,
					path_and_filename);

			/* paint new window created which will be at the top of the z order */
			mw_paint_window_client(new_window_handle);
			mw_paint_window_frame(new_window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);

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
	mw_handle_t new_window_handle;
	uint8_t i;
	char *filename;

	if (!path_and_filename)
	{
		MW_ASSERT((bool)false, "Null pointer");
		return false;
	}

	if (!mw_find_if_any_window_slots_free())
	{
		return false;
	}

	filename = strrchr(path_and_filename, (long)'/');
	if (filename == NULL)
	{
		MW_ASSERT((bool)false, "No filename found");
		return false;
	}
	filename++;

	for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
	{
		if (window_file_data.image_windows_data[i].image_window_handle == MW_INVALID_HANDLE)
		{
			mw_util_set_rect(&r, 10, 10, 100, 100);
			new_window_handle = mw_add_window(&r,
				filename,
				window_image_paint_function,
				window_image_message_function,
				NULL,
				0,
				MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED |
					MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR | MW_WINDOW_FLAG_HAS_HORIZ_SCROLL_BAR  | MW_WINDOW_FLAG_IS_VISIBLE,
				(void *)&window_file_data.image_windows_data[i]);

			window_file_data.image_windows_data[i].image_window_handle  = new_window_handle;

			(void)mw_util_safe_strcpy(window_file_data.image_windows_data[i].path_and_filename_image,
					MAX_FOLDER_AND_FILENAME_LENGTH,
					path_and_filename);

			/* paint new window created which will be at the top of the z order */
			mw_paint_window_client(new_window_handle);
			mw_paint_window_frame(new_window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);

			return true;
		}
	}

	return false;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_file_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	/* Draw rectangles */
	mw_gl_set_fill(MW_GL_NO_FILL);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_rectangle(draw_info, 5, 7, 150, 50);
	mw_gl_rectangle(draw_info, 5, 62, 150, 40);

	/* Draw text on rectangles */
	mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_font(MW_GL_FONT_9);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_colour(MW_HAL_LCD_WHITE);
	mw_gl_string(draw_info, 15, 5, "Time/Date");
	mw_gl_string(draw_info, 15, 60, "File");
}

void window_file_message_function(const mw_message_t *message)
{
	MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		{
			uint8_t i;

			for (i = 0; i < TEXT_WINDOW_COUNT; i++)
			{
				window_file_data.text_windows_data[i].text_window_handle = MW_INVALID_HANDLE;
			}
			for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
			{
				window_file_data.image_windows_data[i].image_window_handle = MW_INVALID_HANDLE;
			}

			(void)mw_set_timer(mw_tick_counter + 20U, message->recipient_handle, MW_WINDOW_MESSAGE);
		}
		break;

	case MW_TIMER_MESSAGE:
		{
			mw_time_t time_now = app_get_time_date();
			char temp_buffer[3];

			(void)mw_util_safe_itoa((int32_t)time_now.tm_hour, temp_buffer, (size_t)3, 10, true, 2U, '0');
			(void)mw_util_safe_strcpy(time_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, temp_buffer);
			(void)mw_util_safe_strcat(time_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, ":");
			(void)mw_util_safe_itoa((int32_t)time_now.tm_min, temp_buffer, (size_t)3, 10, true, 2U, '0');
			(void)mw_util_safe_strcat(time_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, temp_buffer);
			(void)mw_util_safe_strcat(time_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, ":");
			(void)mw_util_safe_itoa((int32_t)time_now.tm_sec, temp_buffer, (size_t)3, 10, true, 2U, '0');
			(void)mw_util_safe_strcat(time_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, temp_buffer);

			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_time_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					time_text,
					MW_CONTROL_MESSAGE);
			mw_paint_control(label_time_handle);

			(void)mw_util_safe_itoa((int32_t)time_now.tm_mday, temp_buffer, (size_t)3, 10, true, 2U, '0');
			(void)mw_util_safe_strcpy(date_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, temp_buffer);
			(void)mw_util_safe_strcat(date_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, "/");
			(void)mw_util_safe_itoa((int32_t)time_now.tm_mon, temp_buffer, (size_t)3, 10, true, 2U, '0');
			(void)mw_util_safe_strcat(date_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, temp_buffer);
			(void)mw_util_safe_strcat(date_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, "/");
			(void)mw_util_safe_itoa((int32_t)time_now.tm_year % (int32_t)100, temp_buffer, (size_t)3, 10, true, 2U, '0');
			(void)mw_util_safe_strcat(date_text, (size_t)MW_UI_LABEL_MAX_CHARS + (size_t)1, temp_buffer);

			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_date_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					date_text,
					MW_CONTROL_MESSAGE);
			mw_paint_control(label_date_handle);

			(void)mw_set_timer(mw_tick_counter + 20U, message->recipient_handle, MW_WINDOW_MESSAGE);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_handle == button_open_handle)
		{
			(void)mw_create_window_dialog_file_chooser(70,
					100,
					choose_file_message,
					app_get_root_folder_path(),
					false,
					false,
					message->recipient_handle);
		}
		else if (message->sender_handle == button_set_clock_handle)
		{
			(void)mw_create_window_dialog_time_chooser(70,
					120,
					0,
					0,
					false,
					message->recipient_handle);
		}
		else if (message->sender_handle == button_create_handle)
		{
			(void)mw_create_window_dialog_file_chooser(70,
					120,
					choose_folder_message,
					app_get_root_folder_path(),
					true,
					false,
					message->recipient_handle);
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_DIALOG_DATE_CHOOSER_OK_MESSAGE:
		{
			uint32_t temp_uint32;
			temp_uint32 = message->message_data & 0xffU;
			window_file_data.set_time.tm_mday = (uint8_t)temp_uint32;
			temp_uint32 = (message->message_data >> 8) & 0xffU;
			window_file_data.set_time.tm_mon = (uint8_t)temp_uint32;
			temp_uint32 = message->message_data >> 16;
			window_file_data.set_time.tm_year = (uint16_t)temp_uint32;
			app_set_time_date(window_file_data.set_time);

			/* enable the create button now time/date set */
			mw_set_control_enabled(button_create_handle, true);
			mw_paint_control(button_create_handle);
		}
		break;

	case MW_DIALOG_TIME_CHOOSER_OK_MESSAGE:
		{
			uint32_t temp_uint32;

			window_file_data.set_time.tm_sec = 0U;
			temp_uint32 = message->message_data >> 8;
			window_file_data.set_time.tm_hour = (uint8_t)temp_uint32;
			temp_uint32 = message->message_data & 0xffU;
			window_file_data.set_time.tm_min = (uint8_t)temp_uint32;

			(void)mw_create_window_dialog_date_chooser(70,
					100,
					1,
					1,
					2018,
					false,
					message->recipient_handle);
		}
		break;

	case MW_DIALOG_FILE_CHOOSER_FILE_OK_MESSAGE:
		{
			const char *extension;
			bool window_added;
			bool format_supported;
			char *open_path_and_filename;

			/* get the item chosen path and file name from message */
			open_path_and_filename = (char *)message->message_pointer;

			/* get filename extension */
			extension = mw_util_get_filename_ext(open_path_and_filename);

			window_added = false;
			format_supported = false;
			if (mw_util_strcicmp(extension, TEXT_FILE_EXTENSION) == 0)
			{
				format_supported = true;
				window_added = add_text_window(open_path_and_filename);
			}
			else if (mw_util_strcicmp(extension, IMAGE_FILE_EXTENSION) == 0)
			{
				format_supported = true;
				window_added = add_image_window(open_path_and_filename);
			}
			else
			{
				/* format not supported, show dialog warning */
				(void)mw_create_window_dialog_one_button(20,
						50,
						150,
						button_warning_label,
						"Format not supported.",
						button_ok_label,
						false,
						message->recipient_handle);
			}

			if (format_supported && !window_added)
			{
				/* format supported but window couldn't be added, show warning */
				(void)mw_create_window_dialog_one_button(20,
						50,
						150,
						button_warning_label,
						no_more_windows_message,
						button_ok_label,
						false,
						message->recipient_handle);
			}

			/* repaint this window too as it's lost focus */
			mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_ALL);
			mw_paint_window_client(message->recipient_handle);
		}
		break;

	case MW_DIALOG_FILE_CHOOSER_FOLDER_OK_MESSAGE:
		{
			(void)mw_util_safe_strcpy(window_file_data.create_path_and_filename,
					MAX_FOLDER_AND_FILENAME_LENGTH,
					(char *)message->message_pointer);
			(void)mw_create_window_dialog_text_entry(5, 10, new_file_name_message, empty_message, false, message->recipient_handle);
		}
		break;

	case MW_DIALOG_TEXT_ENTRY_OK_MESSAGE:
		{
			/* add trailing / to path if it isn't there */
			if (window_file_data.create_path_and_filename[strlen(window_file_data.create_path_and_filename) - (size_t)1] != '/')
			{
				(void)mw_util_safe_strcat(window_file_data.create_path_and_filename,
						MAX_FOLDER_AND_FILENAME_LENGTH,
						"/");
			}

			/* add file name */
			(void)mw_util_safe_strcat(window_file_data.create_path_and_filename,
					MAX_FOLDER_AND_FILENAME_LENGTH,
					(char *)message->message_pointer);

			/* attempt to open file for reading to see if it's there */
			if (app_file_open(window_file_data.create_path_and_filename))
			{
				/* file opened successfully, it must exists already */
				app_file_close();

				/* ask if to overwrite */
				(void)mw_create_window_dialog_two_button(20,
						20,
						210,
						creating_file_message,
						file_already_exists_message,
						button_yes_label,
						button_no_label,
						false,
						message->recipient_handle);
			}
			else
			{
				/* create the new file */
				create_new_file(message->recipient_handle);
			}
		}
		break;

	case MW_DIALOG_TWO_BUTTONS_DISMISSED_MESSAGE:
		{
			/* check response from dialog asking if to overwrite existing file when creating a new one */
			if (message->message_data == 0U)
			{
				/* left button is yes response so create file */
				create_new_file(message->recipient_handle);
			}
		}
		break;


	case MW_USER_1_MESSAGE:
		/* message received from image window when the image file cannot be decoded */
		(void)mw_create_window_dialog_one_button(20,
				50,
				150,
				"Warning",
				"Bad file format.",
				"OK",
				false,
				message->recipient_handle);
		break;

	case MW_WINDOW_EXTERNAL_WINDOW_REMOVED_MESSAGE:
		/* a pop up window has been closed */
		{
			uint8_t i;

			for (i = 0; i < TEXT_WINDOW_COUNT; i++)
			{
				if (message->sender_handle == window_file_data.text_windows_data[i].text_window_handle)
				{
					window_file_data.text_windows_data[i].text_window_handle = MW_INVALID_HANDLE;
					break;
				}
			}
			for (i = 0; i < IMAGE_WINDOW_COUNT; i++)
			{
				if (message->sender_handle == window_file_data.image_windows_data[i].image_window_handle)
				{
					window_file_data.image_windows_data[i].image_window_handle = MW_INVALID_HANDLE;
					break;
				}
			}
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
