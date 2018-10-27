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

const mw_util_rect_t text_display_rect = {51, 5, 125, 14};

/************
*** TYPES ***
************/

/**
 * Window data structure
 */
typedef struct
{
	mw_handle_t keyboard_handle;				/**< Keyboard control handle */
	mw_handle_t button_ok_handle;				/**< Control handle of ok button */
	mw_handle_t button_cancel_handle;			/**< Control handle of cancel button */
	mw_ui_button_data_t button_ok_data;			/**< Instance data of ok button */
	mw_ui_button_data_t button_cancel_data;		/**< Instance data of cancel button */
	mw_ui_keyboard_data_t mw_ui_keyboard_data;	/**< Keyboard control instance data */
	char text_buffer[MW_DIALOG_MAX_TEXT_LENGTH + 1];	/**< MW_DIALOG_MAX_TEXT_LENGTH digits, terminating null */
	mw_handle_t response_window_handle;			/**< Window handle to send response message to */
	mw_dialog_response_t mw_dialog_response;	/**< Dialog response structure */
	bool draw_cursor;							/**< if to draw cursor this timer tick or not */
	uint8_t cursor_position;					/**< current position of cursor in characters */
	mw_util_rect_t cursor_rect;					/**< rect of cursor in window coordinates */
} mw_dialog_text_entry_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_text_entry_data_t mw_dialog_text_entry_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void remove_resources(void);
static uint16_t get_cursor_x_coordinate(void);
static void mw_dialog_text_entry_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_text_entry_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Remove this dialog window and all controls
 */
static void remove_resources(void)
{
	mw_remove_control(mw_dialog_text_entry_data.keyboard_handle);
	mw_remove_control(mw_dialog_text_entry_data.button_ok_handle);
	mw_remove_control(mw_dialog_text_entry_data.button_cancel_handle);
	mw_remove_window(mw_dialog_text_entry_data.mw_dialog_response.window_handle);
}

/**
 * Gets the cursor x coordinate from its position
 *
 * @return The x coordinate
 */
static uint16_t get_cursor_x_coordinate(void)
{
	mw_gl_set_font(MW_GL_FONT_9);
	return (53 + mw_dialog_text_entry_data.cursor_position * (mw_gl_get_font_width() + 1));
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_handle The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_text_entry_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
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

	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);

	/* draw the box the text is displayed in */
	mw_gl_rectangle(draw_info, 51, 5, 125, 14);

	/* draw 3d effect */
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info,
			52,
			6,
			17);
	mw_gl_hline(draw_info,
			52,
			174,
			4);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info,
			174,
			6,
			17);
	mw_gl_hline(draw_info,
			52,
			174,
			17);

	/* draw the text */
	mw_gl_set_font(MW_GL_FONT_9);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);

	/* draw text */
	mw_gl_string(draw_info, 54, 8, mw_dialog_text_entry_data.text_buffer);

	/* draw cursor */
	if (mw_dialog_text_entry_data.draw_cursor)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_vline(draw_info,
				mw_dialog_text_entry_data.cursor_rect.x,
				mw_dialog_text_entry_data.cursor_rect.y,
				mw_dialog_text_entry_data.cursor_rect.y + mw_dialog_text_entry_data.cursor_rect.height);
	}
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
	case MW_WINDOW_CREATED_MESSAGE:
		mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS, message->recipient_handle,	MW_WINDOW_MESSAGE);
		mw_dialog_text_entry_data.cursor_position = strlen(mw_dialog_text_entry_data.text_buffer);

		/* set cursor rect values */
		mw_dialog_text_entry_data.cursor_rect.x = get_cursor_x_coordinate();
		mw_dialog_text_entry_data.cursor_rect.y = 6;
		mw_dialog_text_entry_data.cursor_rect.width = 1;
		mw_dialog_text_entry_data.cursor_rect.height = 11;
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		mw_dialog_text_entry_data.draw_cursor = !mw_dialog_text_entry_data.draw_cursor;
		mw_paint_window_client_rect(message->recipient_handle, &mw_dialog_text_entry_data.cursor_rect);
		mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS, message->recipient_handle,	MW_WINDOW_MESSAGE);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */
		if (mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED)
		{
			mw_gl_set_font(MW_GL_FONT_9);		/* needed to get font width */
			mw_dialog_text_entry_data.cursor_position = ((message->message_data >> 16) - 51) /
					(mw_gl_get_font_width() + 1);

			if (mw_dialog_text_entry_data.cursor_position > strlen(mw_dialog_text_entry_data.text_buffer))
			{
				mw_dialog_text_entry_data.cursor_position = strlen(mw_dialog_text_entry_data.text_buffer);
			}

			mw_dialog_text_entry_data.cursor_rect.x = get_cursor_x_coordinate();
			mw_paint_window_client_rect(message->recipient_handle, &text_display_rect);
		}
		break;

	case MW_KEY_PRESSED_MESSAGE:
		{
			uint8_t current_length;

			current_length = strlen(mw_dialog_text_entry_data.text_buffer);
			if (message->message_data == '\b')
			{
				if (current_length > 0 && mw_dialog_text_entry_data.cursor_position > 0)
				{
					if (mw_dialog_text_entry_data.cursor_position == current_length)
					{
						mw_dialog_text_entry_data.text_buffer[current_length - 1] = '\0';
						mw_dialog_text_entry_data.cursor_position--;
					}
					else
					{
						memmove(&mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position - 1],
										&mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position],
										current_length - mw_dialog_text_entry_data.cursor_position + 1);
						if (mw_dialog_text_entry_data.cursor_position > 0)
						{
							mw_dialog_text_entry_data.cursor_position--;
						}
					}
				}
			}
			else
			{
				if (current_length < MW_DIALOG_MAX_TEXT_LENGTH)
				{
					if (current_length == mw_dialog_text_entry_data.cursor_position)
					{
						/* append entered digit to existing digits */
						mw_dialog_text_entry_data.text_buffer[current_length] = (char)message->message_data;
						mw_dialog_text_entry_data.text_buffer[current_length + 1] = '\0';
						mw_dialog_text_entry_data.cursor_position++;
					}
					else
					{
						/* move everything from cursor onwards along and insert character */
						memmove(&mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position + 1],
										&mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position],
										current_length - mw_dialog_text_entry_data.cursor_position);
						mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position] = (char)message->message_data;
						mw_dialog_text_entry_data.cursor_position++;
					}
				}
			}

			mw_dialog_text_entry_data.cursor_rect.x = get_cursor_x_coordinate();
			mw_paint_window_client_rect(message->recipient_handle, &text_display_rect);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		/* remove all controls and window */
		remove_resources();

		if (message->sender_handle == mw_dialog_text_entry_data.button_cancel_handle)
		{
			/* post cancel response to receiving window */
			mw_dialog_text_entry_data.mw_dialog_response.data = MW_UNUSED_MESSAGE_PARAMETER;
			mw_post_message(MW_DIALOG_TEXT_ENTRY_CANCEL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_text_entry_data.response_window_handle,
					(uint32_t)&mw_dialog_text_entry_data.mw_dialog_response,
					MW_WINDOW_MESSAGE);
		}
		else
		{
			/* post ok response to receiving window */
			mw_dialog_text_entry_data.mw_dialog_response.data = (uint32_t)mw_dialog_text_entry_data.text_buffer;
			mw_post_message(MW_DIALOG_TEXT_ENTRY_OK_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_text_entry_data.response_window_handle,
					(uint32_t)&mw_dialog_text_entry_data.mw_dialog_response,
					MW_WINDOW_MESSAGE);
		}

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

mw_handle_t mw_create_window_dialog_text_entry(uint16_t x,
		uint16_t y,
		char *title,
		char *initial_text,
		mw_handle_t response_window_handle)
{
	mw_util_rect_t rect;

	/* check pointer parameters */
	if (!title || !initial_text)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_MAX_WINDOW_COUNT;
	}

	rect.width = 232;
	rect.height = 130;

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

	mw_dialog_text_entry_data.response_window_handle = response_window_handle;
	rect.x = x;
	rect.y = y;

	mw_dialog_text_entry_data.mw_dialog_response.window_handle = mw_add_window(&rect,
			title,
			mw_dialog_text_entry_paint_function,
			mw_dialog_text_entry_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_text_entry_data.mw_dialog_response.window_handle == MW_MAX_WINDOW_COUNT)
	{
		/* it couldn't so exit */
		return MW_MAX_WINDOW_COUNT;
	}

	/* set controls instance data */
	mw_util_safe_strcpy(mw_dialog_text_entry_data.button_ok_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	mw_util_safe_strcpy(mw_dialog_text_entry_data.button_cancel_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "Cancel");

	/* create controls */
	mw_dialog_text_entry_data.keyboard_handle = mw_ui_keyboard_add_new(5,
			24,
			mw_dialog_text_entry_data.mw_dialog_response.window_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&mw_dialog_text_entry_data.mw_ui_keyboard_data);

	mw_dialog_text_entry_data.button_ok_handle = mw_ui_button_add_new(25,
			90,
			mw_dialog_text_entry_data.mw_dialog_response.window_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&mw_dialog_text_entry_data.button_ok_data);

	mw_dialog_text_entry_data.button_cancel_handle = mw_ui_button_add_new(156,
			90,
			mw_dialog_text_entry_data.mw_dialog_response.window_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&mw_dialog_text_entry_data.button_cancel_data);

	/* check if keyboard could be created */
	if (mw_dialog_text_entry_data.keyboard_handle == MW_MAX_CONTROL_COUNT ||
			mw_dialog_text_entry_data.button_ok_handle == MW_MAX_CONTROL_COUNT ||
			mw_dialog_text_entry_data.button_cancel_handle == MW_MAX_CONTROL_COUNT)
	{
		/* remove all controls and window */
		remove_resources();

		return MW_MAX_WINDOW_COUNT;
	}

	/* set initial text */
	mw_util_safe_strcpy(mw_dialog_text_entry_data.text_buffer, MW_DIALOG_MAX_TEXT_LENGTH + 1, initial_text);

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_text_entry_data.mw_dialog_response.window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_text_entry_data.mw_dialog_response.window_handle);

	return mw_dialog_text_entry_data.mw_dialog_response.window_handle;
}
