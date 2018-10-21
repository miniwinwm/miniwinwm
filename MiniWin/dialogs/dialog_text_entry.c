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
	uint8_t keyboard_id;						/**< Keyboard control id */
	mw_ui_keyboard_data_t mw_ui_keyboard_data;	/**< Keyboard control instance data */
	uint8_t response_window_id;					/**< Window id to send response message to */
	mw_dialog_response_t mw_dialog_response;	/**< Dialog response structure */
} mw_dialog_text_entry_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_text_entry_data_t mw_dialog_text_entry_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void remove_resources(void);
static void mw_dialog_text_entry_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_text_entry_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Remove this dialog window and all controls
 */
static void remove_resources(void)
{
	mw_remove_control(mw_dialog_text_entry_data.keyboard_id);
	mw_remove_window(mw_dialog_text_entry_data.mw_dialog_response.window_id);
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_ref The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_text_entry_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
}

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void mw_dialog_text_entry_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_KEYBOARD_OK_MESSAGE:
		/* remove all controls and window */
		remove_resources();

		/* post response to receiving window */
		mw_dialog_text_entry_data.mw_dialog_response.data = (uint32_t)mw_dialog_text_entry_data.mw_ui_keyboard_data.entry_buffer;
		mw_post_message(MW_DIALOG_TEXT_ENTRY_OK_MESSAGE,
				MW_UNUSED_MESSAGE_PARAMETER,
				mw_dialog_text_entry_data.response_window_id,
				(uint32_t)&mw_dialog_text_entry_data.mw_dialog_response,
				MW_WINDOW_MESSAGE);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	case MW_KEYBOARD_CANCEL_MESSAGE:
		/* remove all controls and window */
		remove_resources();

		/* post response to receiving window */
		mw_dialog_text_entry_data.mw_dialog_response.data = MW_UNUSED_MESSAGE_PARAMETER;
		mw_post_message(MW_DIALOG_TEXT_ENTRY_CANCEL_MESSAGE,
				MW_UNUSED_MESSAGE_PARAMETER,
				mw_dialog_text_entry_data.response_window_id,
				(uint32_t)&mw_dialog_text_entry_data.mw_dialog_response,
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

uint8_t mw_create_window_dialog_text_entry(uint16_t x,
		uint16_t y,
		char *title,
		uint8_t response_window_id)
{
	mw_util_rect_t rect;

	/* check pointer parameters */
	if (!title)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_MAX_WINDOW_COUNT;
	}

	rect.width = 178;
	rect.height = 82;

	/* check start position */
	if (x + rect.width > MW_ROOT_WIDTH)
	{
		return MW_MAX_WINDOW_COUNT;
	}
	if (y + rect.height > MW_ROOT_HEIGHT)
	{
		return MW_MAX_WINDOW_COUNT;
	}

	/* check no modal windows already showing */
	if (mw_is_any_window_modal())
	{
		return MW_MAX_WINDOW_COUNT;
	}

	mw_dialog_text_entry_data.response_window_id = response_window_id;
	rect.x = x;
	rect.y = y;

	mw_dialog_text_entry_data.mw_dialog_response.window_id = mw_add_window(&rect,
			title,
			mw_dialog_text_entry_paint_function,
			mw_dialog_text_entry_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_text_entry_data.mw_dialog_response.window_id == MW_MAX_WINDOW_COUNT)
	{
		/* it couldn't so exit */
		return MW_MAX_WINDOW_COUNT;
	}

	mw_dialog_text_entry_data.keyboard_id = mw_ui_keyboard_add_new(0,
			0,
			mw_dialog_text_entry_data.mw_dialog_response.window_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&mw_dialog_text_entry_data.mw_ui_keyboard_data);

	/* check if keyboard could be created */
	if (mw_dialog_text_entry_data.keyboard_id == MW_MAX_CONTROL_COUNT)
	{
		/* remove all controls and window */
		remove_resources();

		return MW_MAX_WINDOW_COUNT;
	}

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_text_entry_data.mw_dialog_response.window_id, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_text_entry_data.mw_dialog_response.window_id);

	return mw_dialog_text_entry_data.mw_dialog_response.window_id;
}
