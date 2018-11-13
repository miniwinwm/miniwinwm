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

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "dialogs/dialog_common.h"
#include "miniwin.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

const mw_util_rect_t number_display_rect = {24, 5, 65, 14};
const mw_util_rect_t number_display_large_rect = {48, 3, 130, 18};

/************
*** TYPES ***
************/

/**
 * Window data structure
 */
typedef struct
{
	mw_handle_t keypad_handle;						/**< Keypad control handle */
	mw_handle_t button_ok_handle;					/**< Control handle of ok button */
	mw_handle_t button_cancel_handle;				/**< Control handle of cancel button */
	mw_handle_t owner_window_handle;				/**< Window handle to send response message to */
	mw_handle_t number_entry_dialog_window_handle;	/**< Handle of number entry dialog window */
	mw_util_rect_t cursor_rect;						/**< Rect of cursor in window coordinates */
	mw_ui_keypad_data_t mw_ui_keypad_data;			/**< Keypad control instance data */
	mw_ui_button_data_t button_ok_data;				/**< Instance data of ok button */
	mw_ui_button_data_t button_cancel_data;			/**< Instance data of cancel button */
	char number_buffer[MW_DIALOG_MAX_NUMBER_LENGTH + 2];	/**< MW_DIALOG_MAX_NUMBER_LENGTH digits, - sign, terminating null */
	bool is_negative;								/**< If the number is negative */
	bool large_size;								/**< True for large size false for standard size */
	bool draw_cursor;								/**< if to draw cursor this timer tick or not */
} mw_dialog_number_entry_data_t;

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

static mw_dialog_number_entry_data_t mw_dialog_number_entry_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static uint16_t get_cursor_x_coordinate(void);
static void mw_dialog_number_entry_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_number_entry_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Gets the cursor x coordinate from its position
 *
 * @return The x coordinate
 */
static uint16_t get_cursor_x_coordinate(void)
{
	uint16_t pixel_length;
	uint16_t offset;

	if (mw_dialog_number_entry_data.large_size)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		offset = 58;
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		offset = 27;
	}

	pixel_length = mw_gl_get_string_width_pixels(mw_dialog_number_entry_data.number_buffer);
	if (mw_dialog_number_entry_data.is_negative)
	{
		pixel_length += mw_gl_get_string_width_pixels("-");
	}

	return pixel_length + offset;
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_handle The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_number_entry_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
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
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	if (mw_dialog_number_entry_data.large_size)
	{
		/* draw the box the number is displayed in */
		mw_gl_rectangle(draw_info, 54, 3, 120, 20);

		/* draw 3d effect */
		mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
		mw_gl_vline(draw_info,
				55,
				4,
				21);
		mw_gl_hline(draw_info,
				55,
				172,
				4);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
		mw_gl_vline(draw_info,
				172,
				4,
				21);
		mw_gl_hline(draw_info,
				55,
				172,
				21);

		/* draw the number */
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);

		if (mw_dialog_number_entry_data.is_negative && strcmp(mw_dialog_number_entry_data.number_buffer, "0") !=0)
		{
			/* draw negative sign and number */
			mw_gl_character(draw_info, 58, 6, '-');
			mw_gl_string(draw_info, 58 + mw_gl_get_string_width_pixels("-"), 6, mw_dialog_number_entry_data.number_buffer);
		}
		else
		{
			/* draw number only */
			mw_gl_string(draw_info, 58, 6, mw_dialog_number_entry_data.number_buffer);
		}
	}
	else
	{
		/* draw the box the number is displayed in */
		mw_gl_rectangle(draw_info, 24, 5, 65, 14);

		/* draw 3d effect */
		mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
		mw_gl_vline(draw_info,
				25,
				6,
				17);
		mw_gl_hline(draw_info,
				25,
				87,
				6);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
		mw_gl_vline(draw_info,
				87,
				6,
				17);
		mw_gl_hline(draw_info,
				25,
				87,
				17);

		/* draw the number */
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);

		if (mw_dialog_number_entry_data.is_negative && strcmp(mw_dialog_number_entry_data.number_buffer, "0") !=0)
		{
			/* draw negative sign and number */
			mw_gl_character(draw_info, 27, 8, '-');
			mw_gl_string(draw_info, 27 + mw_gl_get_font_width() + 1, 8, mw_dialog_number_entry_data.number_buffer);
		}
		else
		{
			/* draw number only */
			mw_gl_string(draw_info, 27, 8, mw_dialog_number_entry_data.number_buffer);
		}
	}

	/* draw cursor, already adjusted for standard/large size */
	if (mw_dialog_number_entry_data.draw_cursor)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_vline(draw_info,
				mw_dialog_number_entry_data.cursor_rect.x,
				mw_dialog_number_entry_data.cursor_rect.y,
				mw_dialog_number_entry_data.cursor_rect.y + mw_dialog_number_entry_data.cursor_rect.height);
	}
}

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void mw_dialog_number_entry_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS, message->recipient_handle, MW_WINDOW_MESSAGE);

		/* set cursor rect values */
		mw_dialog_number_entry_data.cursor_rect.x = get_cursor_x_coordinate();
		mw_dialog_number_entry_data.cursor_rect.width = 1;
		if (mw_dialog_number_entry_data.large_size)
		{
			mw_dialog_number_entry_data.cursor_rect.y = 4;
			mw_dialog_number_entry_data.cursor_rect.height = 16;
		}
		else
		{
			mw_dialog_number_entry_data.cursor_rect.y = 6;
			mw_dialog_number_entry_data.cursor_rect.height = 11;
		}
		break;

	case MW_TIMER_MESSAGE:
		mw_dialog_number_entry_data.draw_cursor = !mw_dialog_number_entry_data.draw_cursor;
		mw_paint_window_client_rect(message->recipient_handle, &mw_dialog_number_entry_data.cursor_rect);
		mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

	case MW_KEY_PRESSED_MESSAGE:
		{
			uint8_t current_length;

			if (isdigit(message->message_data) || message->message_data == '-' || message->message_data == '\b')
			{
				current_length = strlen(mw_dialog_number_entry_data.number_buffer);

				if (message->message_data == '-')
				{
					mw_dialog_number_entry_data.is_negative = !mw_dialog_number_entry_data.is_negative;
				}
				else if (message->message_data == '\b')
				{
					if (current_length == 1)
					{
						mw_dialog_number_entry_data.is_negative = false;
						strcpy(mw_dialog_number_entry_data.number_buffer, "0");
					}
					else
					{
						mw_dialog_number_entry_data.number_buffer[current_length - 1] = '\0';
					}
				}
				else
				{
					if (current_length < MW_DIALOG_MAX_NUMBER_LENGTH)
					{
						if (mw_dialog_number_entry_data.number_buffer[0] == '0')
						{
							/* replace 0 with entered digit */
							mw_dialog_number_entry_data.number_buffer[0] = (char)message->message_data;
							mw_dialog_number_entry_data.number_buffer[1] = '\0';
						}
						else
						{
							/* append entered digit to existing digits */
							mw_dialog_number_entry_data.number_buffer[current_length] = (char)message->message_data;
							mw_dialog_number_entry_data.number_buffer[current_length + 1] = '\0';
						}
					}
				}

				mw_dialog_number_entry_data.cursor_rect.x = get_cursor_x_coordinate();
				if (mw_dialog_number_entry_data.large_size)
				{
					mw_paint_window_client_rect(message->recipient_handle, &number_display_large_rect);
				}
				else
				{
					mw_paint_window_client_rect(message->recipient_handle, &number_display_rect);
				}
			}
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		{
			/* remove all controls and window */
			mw_remove_window(mw_dialog_number_entry_data.number_entry_dialog_window_handle);

			if (message->sender_handle == mw_dialog_number_entry_data.button_cancel_handle)
			{
				/* post cancel response to receiving window */
				mw_post_message(MW_DIALOG_NUMBER_ENTRY_CANCEL_MESSAGE,
						MW_UNUSED_MESSAGE_PARAMETER,
						mw_dialog_number_entry_data.owner_window_handle,
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_WINDOW_MESSAGE);
			}
			else
			{
				/* post ok response to receiving window */
				/* insert - sign if required */
				if (mw_dialog_number_entry_data.is_negative)
				{
					memmove(mw_dialog_number_entry_data.number_buffer,
							mw_dialog_number_entry_data.number_buffer + 1,
							1 + strlen(mw_dialog_number_entry_data.number_buffer));
					mw_dialog_number_entry_data.number_buffer[0] = '-';
				}
				mw_post_message(MW_DIALOG_NUMBER_ENTRY_OK_MESSAGE,
						MW_UNUSED_MESSAGE_PARAMETER,
						mw_dialog_number_entry_data.owner_window_handle,
						MW_UNUSED_MESSAGE_PARAMETER,
						(void *)mw_dialog_number_entry_data.number_buffer,
						MW_WINDOW_MESSAGE);
			}

			/* a window has changed visibility so repaint all */
			mw_paint_all();
		}
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_create_window_dialog_number_entry(uint16_t x,
		uint16_t y,
		char *title,
		bool enable_negative,
		int32_t initial_number,
		bool large_size,
		mw_handle_t owner_window_handle)
{
	mw_util_rect_t rect;

	/* check pointer parameters */
	if (!title)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_INVALID_HANDLE;
	}

	/* check negative/initial number sanity */
	if (!enable_negative && initial_number < 0)
	{
		MW_ASSERT(false, "Nonsense arguments");
		return MW_INVALID_HANDLE;
	}

	if (large_size)
	{
		rect.width = 230;
		rect.height = 247;
		rect.x = x;
		rect.y = y;	}
	else
	{
		rect.width = 115;
		rect.height = 149;
		rect.x = x;
		rect.y = y;
	}

	/* check start position */
	if (x + rect.width > MW_ROOT_WIDTH)
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
	if (!mw_is_window_handle_valid(owner_window_handle))
	{
		return MW_INVALID_HANDLE;
	}

	mw_dialog_number_entry_data.owner_window_handle = owner_window_handle;

	mw_dialog_number_entry_data.number_entry_dialog_window_handle = mw_add_window(&rect,
			title,
			mw_dialog_number_entry_paint_function,
			mw_dialog_number_entry_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_number_entry_data.number_entry_dialog_window_handle == MW_INVALID_HANDLE)
	{
		/* it couldn't so exit */
		return MW_INVALID_HANDLE;
	}

	/* set controls instance data */
	mw_dialog_number_entry_data.mw_ui_keypad_data.enable_negative = enable_negative;
	mw_util_safe_strcpy(mw_dialog_number_entry_data.button_ok_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	mw_util_safe_strcpy(mw_dialog_number_entry_data.button_cancel_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "Cancel");

	/* create controls */
	if (large_size)
	{
		mw_dialog_number_entry_data.keypad_handle = mw_ui_keypad_add_new(54,
				25,
				mw_dialog_number_entry_data.number_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_number_entry_data.mw_ui_keypad_data);

		mw_dialog_number_entry_data.button_ok_handle = mw_ui_button_add_new(10,
				191,
				mw_dialog_number_entry_data.number_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_number_entry_data.button_ok_data);

		mw_dialog_number_entry_data.button_cancel_handle = mw_ui_button_add_new(118,
				191,
				mw_dialog_number_entry_data.number_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_number_entry_data.button_cancel_data);
	}
	else
	{
		mw_dialog_number_entry_data.keypad_handle = mw_ui_keypad_add_new(27,
				25,
				mw_dialog_number_entry_data.number_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_number_entry_data.mw_ui_keypad_data);

		mw_dialog_number_entry_data.button_ok_handle = mw_ui_button_add_new(5,
				110,
				mw_dialog_number_entry_data.number_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_number_entry_data.button_ok_data);

		mw_dialog_number_entry_data.button_cancel_handle = mw_ui_button_add_new(58,
				110,
				mw_dialog_number_entry_data.number_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_number_entry_data.button_cancel_data);
	}

	/* check if controls could be created */
	if (mw_dialog_number_entry_data.keypad_handle == MW_INVALID_HANDLE ||
		mw_dialog_number_entry_data.button_ok_handle == MW_INVALID_HANDLE ||
		mw_dialog_number_entry_data.button_cancel_handle == MW_INVALID_HANDLE)
	{
		/* remove all controls and window */
		mw_remove_window(mw_dialog_number_entry_data.number_entry_dialog_window_handle);

		return MW_INVALID_HANDLE;
	}

	/* set initial value which comes as number but is converted to string, minus sign (if minus) stored separately */
	mw_dialog_number_entry_data.is_negative = (initial_number < 0);
	if (initial_number < 0)
	{
		initial_number =-initial_number;
	}
	sprintf(mw_dialog_number_entry_data.number_buffer, "%u", (unsigned int)initial_number);
	mw_dialog_number_entry_data.large_size = large_size;

	/* owner window needs its title bar redrawing */
	mw_paint_window_frame(owner_window_handle, MW_WINDOW_FRAME_COMPONENT_TITLE_BAR);

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_number_entry_data.number_entry_dialog_window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_number_entry_data.number_entry_dialog_window_handle);

	return mw_dialog_number_entry_data.number_entry_dialog_window_handle;
}
