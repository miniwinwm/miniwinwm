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
#include "dialogs/dialog_common.h"
#include "miniwin.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const mw_util_rect_t text_display_rect = {51, 5, 125, 14};
static const mw_util_rect_t text_display_rect_large = {121, 5, 205, 24};
#define TITLE_FONT_FIXED_CHARACTER_PITCH		10

/************
*** TYPES ***
************/

/**
 * Window data structure
 */
typedef struct
{
	mw_handle_t keyboard_handle;					/**< Keyboard control handle */
	mw_handle_t button_ok_handle;					/**< Control handle of ok button */
	mw_handle_t button_cancel_handle;				/**< Control handle of cancel button */
	mw_handle_t owner_window_handle;				 /**< Window handle to send response message to */
	mw_handle_t text_entry_dialog_window_handle;	/**< Handle of text entry dialog window */
	mw_util_rect_t text_rect;						/**< Rect of text entry box */
	mw_util_rect_t cursor_rect;						/**< Rect of cursor in window coordinates */
	mw_ui_button_data_t button_ok_data;				/**< Instance data of ok button */
	mw_ui_button_data_t button_cancel_data;			/**< Instance data of cancel button */
	mw_ui_keyboard_data_t mw_ui_keyboard_data;	 	/**< Keyboard control instance data */
	char text_buffer[MW_DIALOG_MAX_TEXT_LENGTH + 1];	/**< MW_DIALOG_MAX_TEXT_LENGTH digits, terminating null */
	bool draw_cursor;								/**< If to draw cursor this timer tick or not */
	bool large_size;								/**< True for large size false for standard size */
	int16_t cursor_position;						/**< Current position of cursor in characters */
	int16_t character_pitch;						/**< The x offset between each character */
} mw_dialog_text_entry_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_text_entry_data_t mw_dialog_text_entry_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static int16_t get_cursor_x_coordinate(void);
static void mw_dialog_text_entry_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_text_entry_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Gets the cursor x coordinate from its position
 *
 * @return The x coordinate of cursor
 */
static int16_t get_cursor_x_coordinate(void)
{
	return (mw_dialog_text_entry_data.text_rect.x + 2 + mw_dialog_text_entry_data.cursor_position * mw_dialog_text_entry_data.character_pitch);
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
	char c[2] = {0};
	int16_t i;

	MW_ASSERT(draw_info != (void*)0, "Null pointer argument");

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
	mw_gl_rectangle(draw_info, mw_dialog_text_entry_data.text_rect.x,
			mw_dialog_text_entry_data.text_rect.y,
			mw_dialog_text_entry_data.text_rect.width,
			mw_dialog_text_entry_data.text_rect.height);

	/* draw 3d effect */
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info,
			mw_dialog_text_entry_data.text_rect.x + 1,
			mw_dialog_text_entry_data.text_rect.y + 1,
			mw_dialog_text_entry_data.text_rect.y + mw_dialog_text_entry_data.text_rect.height - 2);
	mw_gl_hline(draw_info,
			mw_dialog_text_entry_data.text_rect.x + 1,
			mw_dialog_text_entry_data.text_rect.x + mw_dialog_text_entry_data.text_rect.width - 2,
			mw_dialog_text_entry_data.text_rect.y - 1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info,
			mw_dialog_text_entry_data.text_rect.x + mw_dialog_text_entry_data.text_rect.width - 2,
			mw_dialog_text_entry_data.text_rect.y + 1,
			mw_dialog_text_entry_data.text_rect.y + mw_dialog_text_entry_data.text_rect.height - 2);
	mw_gl_hline(draw_info,
			mw_dialog_text_entry_data.text_rect.x + 1,
			mw_dialog_text_entry_data.text_rect.x + mw_dialog_text_entry_data.text_rect.width - 2,
			mw_dialog_text_entry_data.text_rect.y + mw_dialog_text_entry_data.text_rect.height - 2);

	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);

	if (mw_dialog_text_entry_data.large_size)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);

		/* draw text */
		for (i = 0; i < (int16_t)strlen(mw_dialog_text_entry_data.text_buffer); i++)
		{
			c[0] = mw_dialog_text_entry_data.text_buffer[i];
			mw_gl_string(draw_info, text_display_rect_large.x + 4 + i * TITLE_FONT_FIXED_CHARACTER_PITCH, 10, c);
		}
	}
	else
	{
		/* draw the text */
		mw_gl_set_font(MW_GL_FONT_9);

		/* draw text */
		mw_gl_string(draw_info, text_display_rect.x + 3, 8, mw_dialog_text_entry_data.text_buffer);
	}

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
	uint32_t temp_uint32;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		(void)mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS, message->recipient_handle, MW_WINDOW_MESSAGE);
		mw_dialog_text_entry_data.cursor_position = (int16_t)strlen(mw_dialog_text_entry_data.text_buffer);

		/* set dialog size specific values */
		if (mw_dialog_text_entry_data.large_size)
		{
			mw_dialog_text_entry_data.cursor_rect.height = 22;
			mw_dialog_text_entry_data.character_pitch = TITLE_FONT_FIXED_CHARACTER_PITCH;
			(void)memcpy((&mw_dialog_text_entry_data.text_rect), (&text_display_rect_large), (sizeof(text_display_rect_large)));
		}
		else
		{
			mw_dialog_text_entry_data.cursor_rect.height = 13;
			mw_gl_set_font(MW_GL_FONT_9);
			mw_dialog_text_entry_data.character_pitch = (int16_t)mw_gl_get_font_width() + 1;
			(void)memcpy((&mw_dialog_text_entry_data.text_rect), (&text_display_rect), (sizeof(text_display_rect)));
		}

		/* set cursor rect values */
		mw_dialog_text_entry_data.cursor_rect.x = get_cursor_x_coordinate();
		mw_dialog_text_entry_data.cursor_rect.y = 6;
		mw_dialog_text_entry_data.cursor_rect.width = 1;
		break;

	case MW_TIMER_MESSAGE:
		mw_dialog_text_entry_data.draw_cursor = !mw_dialog_text_entry_data.draw_cursor;
		mw_paint_window_client_rect(message->recipient_handle, &mw_dialog_text_entry_data.cursor_rect);
		(void)mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		temp_uint32 = message->message_data >> 16U;
		mw_dialog_text_entry_data.cursor_position = ((int16_t)temp_uint32 - mw_dialog_text_entry_data.text_rect.x) /
				mw_dialog_text_entry_data.character_pitch;

		if (mw_dialog_text_entry_data.cursor_position > (int16_t)strlen(mw_dialog_text_entry_data.text_buffer))
		{
			mw_dialog_text_entry_data.cursor_position = (int16_t)strlen(mw_dialog_text_entry_data.text_buffer);
		}

		mw_dialog_text_entry_data.cursor_rect.x = get_cursor_x_coordinate();
		mw_paint_window_client_rect(message->recipient_handle, &mw_dialog_text_entry_data.text_rect);
		break;

	case MW_KEY_PRESSED_MESSAGE:
		{
			int16_t current_length;
			char *destination;
			const char *source;

			current_length = (int16_t)strlen(mw_dialog_text_entry_data.text_buffer);
			if (message->message_data == (uint32_t)'\b')
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
						/* move everything from 1 place before cursor onwards backwards and delete 1 character */
						source = &mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position];
						destination = &mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position - 1];

						/* this memmove gives a false warning with some versions of GCC with Os optimization */
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
						(void)memmove((destination), (source), ((size_t)current_length - (size_t)mw_dialog_text_entry_data.cursor_position + (size_t)1));
#ifdef __GNUC__
#pragma GCC diagnostic error "-Warray-bounds"
#endif
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
						destination = &mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position + 1];
						source = &mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position];

						/* this memmove gives a false warning with some versions of GCC with Os optimization */
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
						(void)memmove((destination), (source), ((size_t)current_length - (size_t)mw_dialog_text_entry_data.cursor_position));
#ifdef __GNUC__
#pragma GCC diagnostic error "-Warray-bounds"
#endif
						mw_dialog_text_entry_data.text_buffer[mw_dialog_text_entry_data.cursor_position] = (char)message->message_data;
						mw_dialog_text_entry_data.cursor_position++;
					}
				}
			}

			/* update enabled state of ok button */
			mw_set_control_enabled(mw_dialog_text_entry_data.button_ok_handle, strlen(mw_dialog_text_entry_data.text_buffer) > 0U);
			mw_paint_control(mw_dialog_text_entry_data.button_ok_handle);

			/* repaint text box */
			mw_dialog_text_entry_data.cursor_rect.x = get_cursor_x_coordinate();
			mw_paint_window_client_rect(message->recipient_handle, &mw_dialog_text_entry_data.text_rect);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		/* remove all controls and window */
		mw_remove_window(mw_dialog_text_entry_data.text_entry_dialog_window_handle);

		/* a window has changed visibility so repaint all */
		mw_paint_all();

		if (message->sender_handle == mw_dialog_text_entry_data.button_cancel_handle)
		{
			/* post cancel response to receiving window */
			mw_post_message(MW_DIALOG_TEXT_ENTRY_CANCEL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_text_entry_data.owner_window_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					NULL,
					MW_WINDOW_MESSAGE);
		}
		else
		{
			/* post ok response to receiving window */
			mw_post_message(MW_DIALOG_TEXT_ENTRY_OK_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_text_entry_data.owner_window_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)mw_dialog_text_entry_data.text_buffer,
					MW_WINDOW_MESSAGE);
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_create_window_dialog_text_entry(int16_t x,
		int16_t y,
		char *title,
		char *initial_text,
		bool large_size,
		mw_handle_t owner_window_handle)
{
	mw_util_rect_t rect;
	mw_handle_t temp_handle;

	/* check pointer parameters */
	if (title == NULL || initial_text == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (MW_INVALID_HANDLE);
	}

	if (large_size)
	{
		rect.width = 452;
		rect.height = 217;
	}
	else
	{
		rect.width = 232;
		rect.height = 130;
	}
	rect.x = x;
	rect.y = y;

	/* check start position */
	if (x + rect.width > MW_ROOT_WIDTH || x < 0)
	{
		return (MW_INVALID_HANDLE);
	}
	if (y + rect.height > MW_ROOT_HEIGHT || y < 0)
	{
		return (MW_INVALID_HANDLE);
	}

	/* check no modal windows already showing */
	if (mw_is_any_window_modal())
	{
		return (MW_INVALID_HANDLE);
	}

	/* check response window handle */
	if (!mw_is_window_handle_valid(owner_window_handle))
	{
		return (MW_INVALID_HANDLE);
	}

	mw_dialog_text_entry_data.owner_window_handle = owner_window_handle;

	mw_dialog_text_entry_data.text_entry_dialog_window_handle = mw_add_window(&rect,
			title,
			mw_dialog_text_entry_paint_function,
			mw_dialog_text_entry_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_IS_MODAL | (uint32_t)(large_size ? MW_WINDOW_FLAG_LARGE_SIZE : 0U),
			NULL);

	/* check if window could be created */
	if (mw_dialog_text_entry_data.text_entry_dialog_window_handle == MW_INVALID_HANDLE)
	{
		/* it couldn't so exit */
		return (MW_INVALID_HANDLE);
	}

	/* set controls instance data */
	(void)mw_util_safe_strcpy(mw_dialog_text_entry_data.button_ok_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	(void)mw_util_safe_strcpy(mw_dialog_text_entry_data.button_cancel_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "Cancel");

	/* create controls */
	if (large_size)
	{
		temp_handle = mw_ui_keyboard_add_new(5,
				34,
				mw_dialog_text_entry_data.text_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_text_entry_data.mw_ui_keyboard_data);
		mw_dialog_text_entry_data.keyboard_handle = temp_handle;

		temp_handle = mw_ui_button_add_new(50,
				161,
				mw_dialog_text_entry_data.text_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_text_entry_data.button_ok_data);
		mw_dialog_text_entry_data.button_ok_handle = temp_handle;

		temp_handle = mw_ui_button_add_new(300,
				161,
				mw_dialog_text_entry_data.text_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_text_entry_data.button_cancel_data);
		mw_dialog_text_entry_data.button_cancel_handle = temp_handle;
	}
	else
	{
		temp_handle = mw_ui_keyboard_add_new(5,
				24,
				mw_dialog_text_entry_data.text_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_text_entry_data.mw_ui_keyboard_data);
		mw_dialog_text_entry_data.keyboard_handle = temp_handle;

		temp_handle = mw_ui_button_add_new(25,
				90,
				mw_dialog_text_entry_data.text_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_text_entry_data.button_ok_data);
		mw_dialog_text_entry_data.button_ok_handle = temp_handle;

		temp_handle = mw_ui_button_add_new(156,
				90,
				mw_dialog_text_entry_data.text_entry_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_text_entry_data.button_cancel_data);
		mw_dialog_text_entry_data.button_cancel_handle = temp_handle;
	}

	/* check if controls could be created */
	if (mw_dialog_text_entry_data.keyboard_handle == MW_INVALID_HANDLE ||
			mw_dialog_text_entry_data.button_ok_handle == MW_INVALID_HANDLE ||
			mw_dialog_text_entry_data.button_cancel_handle == MW_INVALID_HANDLE)
	{
		/* remove all controls and window */
		mw_remove_window(mw_dialog_text_entry_data.text_entry_dialog_window_handle);

		return (MW_INVALID_HANDLE);
	}

	/* set initial text */
	(void)mw_util_safe_strcpy(mw_dialog_text_entry_data.text_buffer, MW_DIALOG_MAX_TEXT_LENGTH + 1, initial_text);

	/* set large size flag */
	mw_dialog_text_entry_data.large_size = large_size;

	/* owner window needs its title bar redrawing */
	mw_paint_window_frame(owner_window_handle, MW_WINDOW_FRAME_COMPONENT_TITLE_BAR);

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_text_entry_data.text_entry_dialog_window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_text_entry_data.text_entry_dialog_window_handle);

	return (mw_dialog_text_entry_data.text_entry_dialog_window_handle);
}
