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

#include <dialogs/dialog_two_button.h>
#include <miniwin.h>
#include <string.h>
#include "ui/ui_button.h"

/****************
*** CONSTANTS ***
****************/

#define BUTTON_GAP			10		/**< horizontal space between buttons */
#define BUTTON_LARGE_GAP	10		/**< horizontal space between large buttons */

/************
*** TYPES ***
************/

/**
 * Window data structure
 */
typedef struct
{
	uint8_t button_1_id;
	uint8_t button_2_id;
	mw_ui_button_data_t button_1_data;
	mw_ui_button_data_t button_2_data;
	uint8_t window_dialog_two_button_id;
	char *message;
	bool large_size;
	uint8_t response_window_id;
} mw_dialog_two_button_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_two_button_data_t mw_dialog_two_button_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

uint8_t mw_create_window_dialog_two_button(uint16_t x,
		uint16_t y,
		uint16_t width,
		char *title,
		char *message,
		char *button_1_label,
		char *button_2_label,
		bool large_size,
		uint8_t response_window_id)
{
	mw_util_rect_t rect;
	uint16_t window_client_width;

	/* check pointer parameters */
	if (!title || !message || !button_1_label || !button_2_label)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_MAX_WINDOW_COUNT;
	}

	/* check width */
	if (large_size)
	{
		if (width < 2 * MW_UI_BUTTON_LARGE_WIDTH + 2 * MW_BORDER_WIDTH + BUTTON_LARGE_GAP)
		{
			return MW_MAX_WINDOW_COUNT;
		}
		rect.height = 95;
	}
	else
	{
		if (width < 2 * MW_UI_BUTTON_WIDTH + 2 * MW_BORDER_WIDTH + BUTTON_GAP)
		{
			return MW_MAX_WINDOW_COUNT;
		}
		rect.height = 75;
	}

	/* check start position */
	if (width > MW_ROOT_WIDTH || x + width > MW_ROOT_WIDTH)
	{
		return MW_MAX_WINDOW_COUNT;
	}
	if (y + rect.height > MW_ROOT_HEIGHT)
	{
		return MW_MAX_WINDOW_COUNT;
	}

	mw_dialog_two_button_data.large_size = large_size;
	mw_dialog_two_button_data.message = message;
	mw_dialog_two_button_data.response_window_id = response_window_id;
	rect.x = x;
	rect.y = y;
	rect.width = width;

	mw_dialog_two_button_data.window_dialog_two_button_id = mw_add_window(&rect,
			title,
			mw_dialog_two_button_paint_function,
			mw_dialog_two_button_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_two_button_data.window_dialog_two_button_id == MW_MAX_WINDOW_COUNT)
	{
		/* it couldn't so exit */
		return MW_MAX_WINDOW_COUNT;
	}

	/* get window client rect width */
	window_client_width = mw_get_window_client_rect(mw_dialog_two_button_data.window_dialog_two_button_id).width;

	/* create first button control and add it to the  window */
	mw_util_safe_strcpy(mw_dialog_two_button_data.button_1_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, button_1_label);
	if (large_size)
	{
		mw_dialog_two_button_data.button_1_id = mw_ui_button_add_new(
				(window_client_width - BUTTON_LARGE_GAP) / 2 - MW_UI_BUTTON_LARGE_WIDTH,
				35,
				mw_dialog_two_button_data.window_dialog_two_button_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_two_button_data.button_1_data);
	}
	else
	{
		mw_dialog_two_button_data.button_1_id = mw_ui_button_add_new(
				(window_client_width - BUTTON_GAP) / 2 - MW_UI_BUTTON_WIDTH,
				30,
				mw_dialog_two_button_data.window_dialog_two_button_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_two_button_data.button_1_data);
	}

	/* check if button 1 could be created */
	if (mw_dialog_two_button_data.button_1_id == MW_MAX_CONTROL_COUNT)
	{
		/* it couldn't so remove window then exit */
		mw_remove_window(mw_dialog_two_button_data.window_dialog_two_button_id);
		return MW_MAX_WINDOW_COUNT;
	}

	/* create second button control and add it to the  window */
	mw_util_safe_strcpy(mw_dialog_two_button_data.button_2_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, button_2_label);
	if (large_size)
	{
		mw_dialog_two_button_data.button_2_id = mw_ui_button_add_new(
				(window_client_width / 2) + BUTTON_LARGE_GAP / 2,
				35,
				mw_dialog_two_button_data.window_dialog_two_button_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_two_button_data.button_2_data);
	}
	else
	{
		mw_dialog_two_button_data.button_2_id = mw_ui_button_add_new(
				(window_client_width / 2) + BUTTON_GAP / 2,
				30,
				mw_dialog_two_button_data.window_dialog_two_button_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_two_button_data.button_2_data);
	}

	/* check if button 2 could be created */
	if (mw_dialog_two_button_data.button_2_id == MW_MAX_CONTROL_COUNT)
	{
		/* it couldn't so remove button 1 and window then exit */
		mw_remove_control(mw_dialog_two_button_data.button_2_id);
		mw_remove_window(mw_dialog_two_button_data.window_dialog_two_button_id);
		return MW_MAX_WINDOW_COUNT;
	}

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_two_button_data.window_dialog_two_button_id, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_two_button_data.window_dialog_two_button_id);

	return mw_dialog_two_button_data.window_dialog_two_button_id;
}

void mw_dialog_two_button_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
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
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

	if (mw_dialog_two_button_data.large_size)
	{
		mw_gl_large_string(draw_info, 12, 10, mw_dialog_two_button_data.message);
	}
	else
	{
		mw_gl_string(draw_info, 12, 10, mw_dialog_two_button_data.message);
	}
}


void mw_dialog_two_button_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_BUTTON_PRESSED_MESSAGE:
		{
			uint32_t button_pressed;

			/* find which button was pressed */
			if (message->sender_id == mw_dialog_two_button_data.button_1_id)
			{
				button_pressed = 0;
			}
			else
			{
				button_pressed = 1;
			}

			/* remove the buttons */
			mw_remove_control(mw_dialog_two_button_data.button_1_id);
			mw_remove_control(mw_dialog_two_button_data.button_2_id);

			/* post response to receiving window */
			mw_post_message(MW_DIALOG_TWO_BUTTONS_DISMISSED_MESSAGE,
					mw_dialog_two_button_data.window_dialog_two_button_id,
					mw_dialog_two_button_data.response_window_id,
					button_pressed,
					MW_WINDOW_MESSAGE);

			/* remove this window */
			mw_remove_window(mw_dialog_two_button_data.window_dialog_two_button_id);

			/* a window has changed visibility so repaint all */
			mw_paint_all();
		}
		break;

	default:
		break;
	}
}
