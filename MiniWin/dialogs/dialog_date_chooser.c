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
#include <stdio.h>
#include "miniwin.h"
#include "dialogs/dialog_common.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const mw_util_rect_t text_rect_standard = {53, 20, 24, 88};
static const mw_util_rect_t text_rect_large = {139, 36, 32, 178};
static const uint8_t days_in_months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/************
*** TYPES ***
************/

/**
 * Window data structure
 */
typedef struct
{
	mw_handle_t button_ok_handle;					/**< Control handle of ok button */
	mw_handle_t button_cancel_handle;				/**< Control handle of cancel button */
	mw_handle_t arrow_year_up_handle;				/**< Control handle of year up button */
	mw_handle_t arrow_year_down_handle;				/**< Control handle of year down button */
	mw_handle_t arrow_month_up_handle;				/**< Control handle of month up button */
	mw_handle_t arrow_month_down_handle;			/**< Control handle of month down button */
	mw_handle_t arrow_date_up_handle;				/**< Control handle of date up button */
	mw_handle_t arrow_date_down_handle;				/**< Control handle of date down button */
	mw_ui_button_data_t button_ok_data;				/**< Instance data of ok button */
	mw_ui_button_data_t button_cancel_data;			/**< Instance data of cancel button */
	mw_ui_arrow_data_t arrow_year_up_data;			/**< Instance data of year up button */
	mw_ui_arrow_data_t arrow_year_down_data;		/**< Instance data of year down button */
	mw_ui_arrow_data_t arrow_month_up_data;			/**< Instance data of month up button */
	mw_ui_arrow_data_t arrow_month_down_data;		/**< Instance data of month down button */
	mw_ui_arrow_data_t arrow_date_up_data;			/**< Instance data of date up button */
	mw_ui_arrow_data_t arrow_date_down_data;		/**< Instance data of date down button */
	uint16_t current_date_year;						/**< Current year in dialog xxxx */
	uint8_t current_date_month;						/**< Current month in dialog 1-12 */
	uint8_t current_date_date;						/**< Current date in dialog 1-31 */
	bool large_size;								/**< true for large size false for standard size */
	mw_handle_t response_window_handle;				/**< Window handle to send response message to */
	mw_handle_t date_chooser_dialog_window_handle;	/**< Handle of date chooser dialog window */
} mw_dialog_date_chooser_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_date_chooser_data_t mw_dialog_date_chooser_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void remove_resources(void);
static void update_arrow_enable_states(void);
static uint8_t get_max_date_for_month_and_year(uint8_t month, uint16_t year);
static void mw_dialog_date_chooser_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_date_chooser_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Remove this dialog window and all controls
 */
static void remove_resources(void)
{
	mw_remove_control(mw_dialog_date_chooser_data.button_ok_handle);
	mw_remove_control(mw_dialog_date_chooser_data.button_ok_handle);
	mw_remove_control(mw_dialog_date_chooser_data.arrow_year_up_handle);
	mw_remove_control(mw_dialog_date_chooser_data.arrow_year_down_handle);
	mw_remove_control(mw_dialog_date_chooser_data.arrow_month_up_handle);
	mw_remove_control(mw_dialog_date_chooser_data.arrow_month_down_handle);
	mw_remove_control(mw_dialog_date_chooser_data.arrow_date_up_handle);
	mw_remove_control(mw_dialog_date_chooser_data.arrow_date_down_handle);
	mw_remove_window(mw_dialog_date_chooser_data.date_chooser_dialog_window_handle);
}

/**
 * Get the number of days in a month for a given year
 *
 * @param month 1-12
 * @param year 0-99
 * @return The days in the month
 */
static uint8_t get_max_date_for_month_and_year(uint8_t month, uint16_t year)
{
	uint8_t days;

	days = days_in_months[month];
	if (month == 2)
	{
		if (year % 4 == 0)
		{
			days++;

			if (year % 100 == 0)
			{
				days--;

				if (year % 400 == 0)
				{
					days++;
				}
			}
		}
	}

	return days;
}

/**
 * Set all the arrow enable states according to value of current time
 */
static void update_arrow_enable_states(void)
{
	/* rationalize date first so we don't end up with dates like 30th feb*/
	if (mw_dialog_date_chooser_data.current_date_date >
	get_max_date_for_month_and_year(
				mw_dialog_date_chooser_data.current_date_month,
				mw_dialog_date_chooser_data.current_date_year))
	{
		mw_dialog_date_chooser_data.current_date_date =
			get_max_date_for_month_and_year(
						mw_dialog_date_chooser_data.current_date_month,
						mw_dialog_date_chooser_data.current_date_year);
	}

	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_up_handle, true);
	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_down_handle, true);
	if (mw_dialog_date_chooser_data.current_date_date == 1)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_down_handle, false);
	}
	else if (mw_dialog_date_chooser_data.current_date_date == get_max_date_for_month_and_year(
			mw_dialog_date_chooser_data.current_date_month,
			mw_dialog_date_chooser_data.current_date_year))
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_up_handle, false);
	}

	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_up_handle, true);
	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_down_handle, true);
	if (mw_dialog_date_chooser_data.current_date_month == 1)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_down_handle, false);
	}
	else if (mw_dialog_date_chooser_data.current_date_month == 12)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_up_handle, false);
	}

	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_up_handle, true);
	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_down_handle, true);
	if (mw_dialog_date_chooser_data.current_date_year == 0)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_down_handle, false);
	}
	else if (mw_dialog_date_chooser_data.current_date_year == 99)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_up_handle, false);
	}

	mw_paint_control(mw_dialog_date_chooser_data.arrow_month_up_handle);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_month_down_handle);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_year_up_handle);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_year_down_handle);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_date_up_handle);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_date_down_handle);
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_handle The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_date_chooser_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	char text_year[16];
	char text_month[16];
	char text_date[16];

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

	snprintf(text_year, 16, "Year: %04u", (unsigned int)mw_dialog_date_chooser_data.current_date_year);
	snprintf(text_month, 16, "Month: %u", (unsigned int)mw_dialog_date_chooser_data.current_date_month);
	snprintf(text_date, 16, "Date: %u", (unsigned int)mw_dialog_date_chooser_data.current_date_date);

	if (mw_dialog_date_chooser_data.large_size)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 101, 37, text_date);
		mw_gl_string(draw_info, 91, 120, text_month);
		mw_gl_string(draw_info, 101, 200, text_year);
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 18, 20, text_date);
		mw_gl_string(draw_info, 12, 60, text_month);
		mw_gl_string(draw_info, 18, 100, text_year);
	}
}

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void mw_dialog_date_chooser_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_ARROW_PRESSED_MESSAGE:
		if (message->sender_handle == mw_dialog_date_chooser_data.arrow_year_up_handle)
		{
			if (mw_dialog_date_chooser_data.current_date_year < 9999)
			{
				mw_dialog_date_chooser_data.current_date_year++;
			}
		}
		else if (message->sender_handle == mw_dialog_date_chooser_data.arrow_year_down_handle)
		{
			if (mw_dialog_date_chooser_data.current_date_year > 0)
			{
				mw_dialog_date_chooser_data.current_date_year--;
			}
		}
		else if (message->sender_handle == mw_dialog_date_chooser_data.arrow_month_up_handle)
		{
			if (mw_dialog_date_chooser_data.current_date_month < 12)
			{
				mw_dialog_date_chooser_data.current_date_month++;
			}
		}
		else if (message->sender_handle == mw_dialog_date_chooser_data.arrow_month_down_handle)
		{
			if (mw_dialog_date_chooser_data.current_date_month > 1)
			{
				mw_dialog_date_chooser_data.current_date_month--;
			}
		}
		else if (message->sender_handle == mw_dialog_date_chooser_data.arrow_date_up_handle)
		{
			if (mw_dialog_date_chooser_data.current_date_date <
					get_max_date_for_month_and_year(mw_dialog_date_chooser_data.current_date_month,
							mw_dialog_date_chooser_data.current_date_year))
			{
				mw_dialog_date_chooser_data.current_date_date++;
			}
		}
		else if (message->sender_handle == mw_dialog_date_chooser_data.arrow_date_down_handle)
		{
			if (mw_dialog_date_chooser_data.current_date_date > 1)
			{
				mw_dialog_date_chooser_data.current_date_date--;
			}
		}
		else
		{
			MW_ASSERT(false, "Unknown control id");
		}

		/* enable or disable arrow controls as required */
		update_arrow_enable_states();

		/* just paint the changed text */
		if (mw_dialog_date_chooser_data.large_size)
		{
			mw_paint_window_client_rect(mw_dialog_date_chooser_data.date_chooser_dialog_window_handle, &text_rect_large);
		}
		else
		{
			mw_paint_window_client_rect(mw_dialog_date_chooser_data.date_chooser_dialog_window_handle, &text_rect_standard);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		/* remove all controls and window */
		remove_resources();

		if (message->sender_handle == mw_dialog_date_chooser_data.button_ok_handle)
		{
			/* post ok response to receiving window */
			mw_post_message(MW_DIALOG_DATE_CHOOSER_OK_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_date_chooser_data.response_window_handle,
					(uint32_t)mw_dialog_date_chooser_data.current_date_year << 16 |
							(uint32_t)mw_dialog_date_chooser_data.current_date_month << 8 |
							mw_dialog_date_chooser_data.current_date_date,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_WINDOW_MESSAGE);
		}
		else if (message->sender_handle == mw_dialog_date_chooser_data.button_cancel_handle)
		{
			/* post cancel response to receiving window */
			mw_post_message(MW_DIALOG_DATE_CHOOSER_CANCEL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_date_chooser_data.response_window_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_WINDOW_MESSAGE);
		}
		else
		{
			MW_ASSERT(false, "Unknown control id");
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

mw_handle_t mw_create_window_dialog_date_chooser(uint16_t x,
		uint16_t y,
		uint8_t start_date_date,
		uint8_t start_date_month,
		uint16_t start_date_year,
		bool large_size,
		mw_handle_t response_window_handle)
{
	mw_util_rect_t rect;

	/* check the start date */
	if (start_date_year > 9999 ||
			start_date_month > 12 || start_date_month == 0 ||
			start_date_date == 0 || start_date_date > get_max_date_for_month_and_year(start_date_month, start_date_year))
	{
		return MW_INVALID_HANDLE;
	}
	mw_dialog_date_chooser_data.current_date_year = start_date_year;
	mw_dialog_date_chooser_data.current_date_month = start_date_month;
	mw_dialog_date_chooser_data.current_date_date = start_date_date;

	/* check width */
	if (large_size)
	{
		rect.width = 226;
		rect.height = 305;
	}
	else
	{
		rect.width = 118;
		rect.height = 170;
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
	if (!mw_is_window_handle_valid(response_window_handle))
	{
		return MW_INVALID_HANDLE;
	}

	mw_dialog_date_chooser_data.large_size = large_size;
	mw_dialog_date_chooser_data.response_window_handle = response_window_handle;
	rect.x = x;
	rect.y = y;

	mw_dialog_date_chooser_data.date_chooser_dialog_window_handle = mw_add_window(&rect,
			"Set date",
			mw_dialog_date_chooser_paint_function,
			mw_dialog_date_chooser_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_date_chooser_data.date_chooser_dialog_window_handle == MW_INVALID_HANDLE)
	{
		/* it couldn't so exit */
		return MW_INVALID_HANDLE;
	}

	/* set controls data */
	mw_util_safe_strcpy(mw_dialog_date_chooser_data.button_ok_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	mw_util_safe_strcpy(mw_dialog_date_chooser_data.button_cancel_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "Cancel");
	mw_dialog_date_chooser_data.arrow_year_up_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	mw_dialog_date_chooser_data.arrow_year_down_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	mw_dialog_date_chooser_data.arrow_month_up_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	mw_dialog_date_chooser_data.arrow_month_down_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	mw_dialog_date_chooser_data.arrow_date_up_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	mw_dialog_date_chooser_data.arrow_date_down_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;

	if (large_size)
	{
		mw_dialog_date_chooser_data.button_ok_handle = mw_ui_button_add_new(5,
				250,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.button_ok_data);

		mw_dialog_date_chooser_data.button_cancel_handle = mw_ui_button_add_new(120,
				250,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.button_cancel_data);

		mw_dialog_date_chooser_data.arrow_date_up_handle = mw_ui_arrow_add_new(186,
				10,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_date_up_data);

		mw_dialog_date_chooser_data.arrow_date_down_handle = mw_ui_arrow_add_new(186,
				50,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_date_down_data);

		mw_dialog_date_chooser_data.arrow_month_up_handle = mw_ui_arrow_add_new(186,
				90,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_month_up_data);

		mw_dialog_date_chooser_data.arrow_month_down_handle = mw_ui_arrow_add_new(186,
				130,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_month_down_data);

		mw_dialog_date_chooser_data.arrow_year_up_handle = mw_ui_arrow_add_new(186,
				170,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_month_up_data);

		mw_dialog_date_chooser_data.arrow_year_down_handle = mw_ui_arrow_add_new(186,
				210,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_year_down_data);
	}
	else
	{
		mw_dialog_date_chooser_data.button_ok_handle = mw_ui_button_add_new(5,
				130,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_date_chooser_data.button_ok_data);

		mw_dialog_date_chooser_data.button_cancel_handle = mw_ui_button_add_new(60,
				130,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_date_chooser_data.button_cancel_data);

		mw_dialog_date_chooser_data.arrow_date_up_handle = mw_ui_arrow_add_new(93,
				5,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_date_up_data);

		mw_dialog_date_chooser_data.arrow_date_down_handle = mw_ui_arrow_add_new(93,
				25,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_date_down_data);

		mw_dialog_date_chooser_data.arrow_month_up_handle = mw_ui_arrow_add_new(93,
				45,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_month_up_data);

		mw_dialog_date_chooser_data.arrow_month_down_handle = mw_ui_arrow_add_new(93,
				65,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_month_down_data);

		mw_dialog_date_chooser_data.arrow_year_up_handle = mw_ui_arrow_add_new(93,
				85,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_year_up_data);

		mw_dialog_date_chooser_data.arrow_year_down_handle = mw_ui_arrow_add_new(93,
				105,
				mw_dialog_date_chooser_data.date_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_year_down_data);
	}

	if (mw_dialog_date_chooser_data.button_ok_handle == MW_INVALID_HANDLE ||
			mw_dialog_date_chooser_data.button_cancel_handle == MW_INVALID_HANDLE ||
			mw_dialog_date_chooser_data.arrow_year_up_handle == MW_INVALID_HANDLE ||
			mw_dialog_date_chooser_data.arrow_year_down_handle == MW_INVALID_HANDLE ||
			mw_dialog_date_chooser_data.arrow_month_up_handle == MW_INVALID_HANDLE ||
			mw_dialog_date_chooser_data.arrow_month_down_handle == MW_INVALID_HANDLE ||
			mw_dialog_date_chooser_data.arrow_date_up_handle == MW_INVALID_HANDLE ||
			mw_dialog_date_chooser_data.arrow_date_down_handle == MW_INVALID_HANDLE)
	{
		/* remove all controls and window */
		remove_resources();

		return MW_INVALID_HANDLE;
	}

	/* set arrow enable states appropriately */
	update_arrow_enable_states();

	/* a window has changed visibility so repaint all */
	mw_paint_all();

	return mw_dialog_date_chooser_data.date_chooser_dialog_window_handle;
}
