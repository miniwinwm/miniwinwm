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
#include "ui/ui_button.h"

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
	mw_handle_t button_handle;						/**< Control handle of button */
	mw_handle_t response_window_handle;				/**< Window handle to send response message to */
	mw_handle_t one_button_dialog_window_handle;	/**< Handle of one button dialog window */
	char *message;									/**< Text to display in dialog */
	mw_ui_button_data_t button_data;				/**< Instance data of button */
	bool large_size;								/**< True for large size false for standard size */
} mw_dialog_one_button_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_one_button_data_t mw_dialog_one_button_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void remove_resources(void);
static void mw_dialog_one_button_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_one_button_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Remove this dialog window and all controls
 */
static void remove_resources(void)
{
	mw_remove_control(mw_dialog_one_button_data.button_handle);
	mw_remove_window(mw_dialog_one_button_data.one_button_dialog_window_handle);
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_handle The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_one_button_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
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

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	if (mw_dialog_one_button_data.large_size)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 12, 10, mw_dialog_one_button_data.message);
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 12, 10, mw_dialog_one_button_data.message);
	}
}

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void mw_dialog_one_button_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_BUTTON_PRESSED_MESSAGE:
		/* remove all controls and window */
		remove_resources();

		/* post response to receiving window */
		mw_post_message(MW_DIALOG_ONE_BUTTON_DISMISSED_MESSAGE,
				MW_UNUSED_MESSAGE_PARAMETER,
				mw_dialog_one_button_data.response_window_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_create_window_dialog_one_button(uint16_t x,
		uint16_t y,
		uint16_t width,
		char *title,
		char *message,
		char *button_label,
		bool large_size,
		mw_handle_t response_window_handle)
{
	mw_util_rect_t rect;
	uint16_t window_client_width;

	/* check pointer parameters */
	if (!title || !message || !button_label)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_INVALID_HANDLE;
	}

	/* check width */
	if (large_size)
	{
		if (width < MW_UI_BUTTON_LARGE_WIDTH + 2 * MW_BORDER_WIDTH)
		{
			return MW_INVALID_HANDLE;
		}
		rect.height = 95;
	}
	else
	{
		if (width < MW_UI_BUTTON_WIDTH + 2 * MW_BORDER_WIDTH)
		{
			return MW_INVALID_HANDLE;
		}
		rect.height = 75;
	}

	/* check start position */
	if (width > MW_ROOT_WIDTH || x + width > MW_ROOT_WIDTH)
	{
		return MW_INVALID_HANDLE;
	}
	if (y + rect.height > MW_ROOT_HEIGHT)
	{
		return MW_INVALID_HANDLE;
	}

	/* check no modal windows already showing */
	if (mw_is_any_window_modal())
	{
		return MW_INVALID_HANDLE;
	}

	/* check response window handle */
	if (!mw_is_window_handle_valid(response_window_handle))
	{
		return MW_INVALID_HANDLE;
	}

	mw_dialog_one_button_data.large_size = large_size;
	mw_dialog_one_button_data.message = message;
	mw_dialog_one_button_data.response_window_handle = response_window_handle;
	rect.x = x;
	rect.y = y;
	rect.width = width;

	mw_dialog_one_button_data.one_button_dialog_window_handle = mw_add_window(&rect,
			title,
			mw_dialog_one_button_paint_function,
			mw_dialog_one_button_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_one_button_data.one_button_dialog_window_handle == MW_INVALID_HANDLE)
	{
		/* it couldn't so exit */
		return MW_INVALID_HANDLE;
	}

	/* get window client rect width */
	window_client_width = mw_get_window_client_rect(mw_dialog_one_button_data.one_button_dialog_window_handle).width;

	/* create a button control and add it to the  window */
	mw_util_safe_strcpy(mw_dialog_one_button_data.button_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, button_label);
	if (large_size)
	{
		mw_dialog_one_button_data.button_handle = mw_ui_button_add_new(
				(window_client_width - MW_UI_BUTTON_LARGE_WIDTH) / 2,
				35,
				mw_dialog_one_button_data.one_button_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_one_button_data.button_data);
	}
	else
	{
		mw_dialog_one_button_data.button_handle = mw_ui_button_add_new(
				(window_client_width - MW_UI_BUTTON_WIDTH) / 2,
				30,
				mw_dialog_one_button_data.one_button_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_one_button_data.button_data);
	}

	/* check if button could be created */
	if (mw_dialog_one_button_data.button_handle == MW_INVALID_HANDLE)
	{
		/* remove all controls and window */
		remove_resources();

		return MW_INVALID_HANDLE;
	}

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_one_button_data.one_button_dialog_window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_one_button_data.one_button_dialog_window_handle);

	return mw_dialog_one_button_data.one_button_dialog_window_handle;
}
