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

#include <miniwin.h>
#include <stdio.h>
#include <string.h>
#include "dialogs/dialog_date_chooser.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const mw_util_rect_t text_rect_standard = {53, 20, 4 * MW_GL_STANDARD_CHARACTER_WIDTH, 88};
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
	uint8_t button_ok_id;
	mw_ui_button_data_t button_ok_data;
	uint8_t button_cancel_id;
	mw_ui_button_data_t button_cancel_data;
	uint8_t arrow_year_up_id;
	mw_ui_arrow_data_t arrow_year_up_data;
	uint8_t arrow_year_down_id;
	mw_ui_arrow_data_t arrow_year_down_data;
	uint8_t arrow_month_up_id;
	mw_ui_arrow_data_t arrow_month_up_data;
	uint8_t arrow_month_down_id;
	mw_ui_arrow_data_t arrow_month_down_data;
	uint8_t arrow_date_up_id;
	mw_ui_arrow_data_t arrow_date_up_data;
	uint8_t arrow_date_down_id;
	mw_ui_arrow_data_t arrow_date_down_data;
	uint8_t window_dialog_date_chooser_id;
	uint16_t current_date_year;
	uint8_t current_date_month;
	uint8_t current_date_date;
	bool large_size;
	uint8_t response_window_id;
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

static void update_arrow_enable_states(void);
static uint8_t get_max_date_for_month_and_year(uint8_t month, uint16_t year);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Get the number of days in a month for a given year
 *
 * @param month 1-12
 * @param year 0-99
 * @return the days in the month
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

	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_up_id, true);
	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_down_id, true);
	if (mw_dialog_date_chooser_data.current_date_date == 1)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_down_id, false);
	}
	else if (mw_dialog_date_chooser_data.current_date_date == get_max_date_for_month_and_year(
			mw_dialog_date_chooser_data.current_date_month,
			mw_dialog_date_chooser_data.current_date_year))
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_date_up_id, false);
	}

	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_up_id, true);
	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_down_id, true);
	if (mw_dialog_date_chooser_data.current_date_month == 1)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_down_id, false);
	}
	else if (mw_dialog_date_chooser_data.current_date_month == 12)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_month_up_id, false);
	}

	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_up_id, true);
	mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_down_id, true);
	if (mw_dialog_date_chooser_data.current_date_year == 0)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_down_id, false);
	}
	else if (mw_dialog_date_chooser_data.current_date_year == 99)
	{
		mw_set_control_enabled(mw_dialog_date_chooser_data.arrow_year_up_id, false);
	}

	mw_paint_control(mw_dialog_date_chooser_data.arrow_month_up_id);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_month_down_id);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_year_up_id);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_year_down_id);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_date_up_id);
	mw_paint_control(mw_dialog_date_chooser_data.arrow_date_down_id);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

uint8_t mw_create_window_dialog_date_chooser(uint16_t x,
		uint16_t y,
		uint8_t start_date_date,
		uint8_t start_date_month,
		uint16_t start_date_year,
		bool large_size,
		uint8_t response_window_id)
{
	mw_util_rect_t rect;

	/* check the start date */
	if (start_date_year > 9999 ||
			start_date_month > 12 || start_date_month == 0 ||
			start_date_date == 0 || start_date_date > get_max_date_for_month_and_year(start_date_month - 1, start_date_year))
	{
		return MW_MAX_WINDOW_COUNT;
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

	mw_dialog_date_chooser_data.large_size = large_size;
	mw_dialog_date_chooser_data.response_window_id = response_window_id;
	rect.x = x;
	rect.y = y;

	mw_dialog_date_chooser_data.window_dialog_date_chooser_id = mw_add_window(&rect,
			"Set date",
			mw_dialog_date_chooser_paint_function,
			mw_dialog_date_chooser_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_date_chooser_data.window_dialog_date_chooser_id == MW_MAX_WINDOW_COUNT)
	{
		/* it couldn't so exit */
		return MW_MAX_WINDOW_COUNT;
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
		mw_dialog_date_chooser_data.button_ok_id = mw_ui_button_add_new(5,
				250,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.button_ok_data);

		mw_dialog_date_chooser_data.button_cancel_id = mw_ui_button_add_new(120,
				250,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.button_cancel_data);

		mw_dialog_date_chooser_data.arrow_date_up_id = mw_ui_arrow_add_new(186,
				10,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_date_up_data);

		mw_dialog_date_chooser_data.arrow_date_down_id = mw_ui_arrow_add_new(186,
				50,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_date_down_data);

		mw_dialog_date_chooser_data.arrow_month_up_id = mw_ui_arrow_add_new(186,
				90,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_month_up_data);

		mw_dialog_date_chooser_data.arrow_month_down_id = mw_ui_arrow_add_new(186,
				130,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_month_down_data);

		mw_dialog_date_chooser_data.arrow_year_up_id = mw_ui_arrow_add_new(186,
				170,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_month_up_data);

		mw_dialog_date_chooser_data.arrow_year_down_id = mw_ui_arrow_add_new(186,
				210,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_date_chooser_data.arrow_year_down_data);
	}
	else
	{
		mw_dialog_date_chooser_data.button_ok_id = mw_ui_button_add_new(5,
				130,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_date_chooser_data.button_ok_data);

		mw_dialog_date_chooser_data.button_cancel_id = mw_ui_button_add_new(60,
				130,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_date_chooser_data.button_cancel_data);

		mw_dialog_date_chooser_data.arrow_date_up_id = mw_ui_arrow_add_new(93,
				5,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_date_up_data);

		mw_dialog_date_chooser_data.arrow_date_down_id = mw_ui_arrow_add_new(93,
				25,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_date_down_data);

		mw_dialog_date_chooser_data.arrow_month_up_id = mw_ui_arrow_add_new(93,
				45,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_month_up_data);

		mw_dialog_date_chooser_data.arrow_month_down_id = mw_ui_arrow_add_new(93,
				65,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_month_down_data);

		mw_dialog_date_chooser_data.arrow_year_up_id = mw_ui_arrow_add_new(93,
				85,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_year_up_data);

		mw_dialog_date_chooser_data.arrow_year_down_id = mw_ui_arrow_add_new(93,
				105,
				mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_date_chooser_data.arrow_year_down_data);
	}

	if (mw_dialog_date_chooser_data.button_ok_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_date_chooser_data.button_cancel_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_date_chooser_data.arrow_year_up_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_date_chooser_data.arrow_year_down_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_date_chooser_data.arrow_month_up_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_date_chooser_data.arrow_month_down_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_date_chooser_data.arrow_date_up_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_date_chooser_data.arrow_date_down_id == MW_MAX_CONTROL_COUNT)
	{
		mw_remove_control(mw_dialog_date_chooser_data.button_ok_id);
		mw_remove_control(mw_dialog_date_chooser_data.button_cancel_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_year_up_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_year_down_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_month_up_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_month_down_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_date_up_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_date_down_id);

		mw_remove_window(mw_dialog_date_chooser_data.window_dialog_date_chooser_id);
		return MW_MAX_WINDOW_COUNT;
	}

	/* set arrow enable states appropriately */
	update_arrow_enable_states();

	/* a window has changed visibility so repaint all */
	mw_paint_all();

	return mw_dialog_date_chooser_data.window_dialog_date_chooser_id;
}

void mw_dialog_date_chooser_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
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
			mw_get_window_client_rect(window_ref).width,
			mw_get_window_client_rect(window_ref).height);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	snprintf(text_year, 16, "Year: %04u", (unsigned int)mw_dialog_date_chooser_data.current_date_year);
	snprintf(text_month, 16, "Month: %u", (unsigned int)mw_dialog_date_chooser_data.current_date_month);
	snprintf(text_date, 16, "Date: %u", (unsigned int)mw_dialog_date_chooser_data.current_date_date);

	if (mw_dialog_date_chooser_data.large_size)
	{
		mw_gl_large_string(draw_info, 101, 37, text_date);
		mw_gl_large_string(draw_info, 91, 120, text_month);
		mw_gl_large_string(draw_info, 101, 200, text_year);
	}
	else
	{
		mw_gl_string(draw_info, 18, 20, text_date);
		mw_gl_string(draw_info, 12, 60, text_month);
		mw_gl_string(draw_info, 18, 100, text_year);
	}
}

void mw_dialog_date_chooser_message_function(const mw_message_t *message)
{
	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_ARROW_PRESSED_MESSAGE:
		if (message->sender_id == mw_dialog_date_chooser_data.arrow_year_up_id)
		{
			if (mw_dialog_date_chooser_data.current_date_year < 9999)
			{
				mw_dialog_date_chooser_data.current_date_year++;
			}
		}
		else if (message->sender_id == mw_dialog_date_chooser_data.arrow_year_down_id)
		{
			if (mw_dialog_date_chooser_data.current_date_year > 0)
			{
				mw_dialog_date_chooser_data.current_date_year--;
			}
		}
		else if (message->sender_id == mw_dialog_date_chooser_data.arrow_month_up_id)
		{
			if (mw_dialog_date_chooser_data.current_date_month < 12)
			{
				mw_dialog_date_chooser_data.current_date_month++;
			}
		}
		else if (message->sender_id == mw_dialog_date_chooser_data.arrow_month_down_id)
		{
			if (mw_dialog_date_chooser_data.current_date_month > 1)
			{
				mw_dialog_date_chooser_data.current_date_month--;
			}
		}
		else if (message->sender_id == mw_dialog_date_chooser_data.arrow_date_up_id)
		{
			if (mw_dialog_date_chooser_data.current_date_date <
					get_max_date_for_month_and_year(mw_dialog_date_chooser_data.current_date_month,
							mw_dialog_date_chooser_data.current_date_year))
			{
				mw_dialog_date_chooser_data.current_date_date++;
			}
		}
		else if (message->sender_id == mw_dialog_date_chooser_data.arrow_date_down_id)
		{
			if (mw_dialog_date_chooser_data.current_date_date > 1)
			{
				mw_dialog_date_chooser_data.current_date_date--;
			}
		}
		else
		{
			MW_ASSERT(false);
		}

		/* enable or disable arrow controls as required */
		update_arrow_enable_states();

		/* just paint the changed text */
		if (mw_dialog_date_chooser_data.large_size)
		{
			mw_paint_window_client_rect(mw_dialog_date_chooser_data.window_dialog_date_chooser_id, &text_rect_large);
		}
		else
		{
			mw_paint_window_client_rect(mw_dialog_date_chooser_data.window_dialog_date_chooser_id, &text_rect_standard);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_id == mw_dialog_date_chooser_data.button_ok_id)
		{
			/* post response to receiving window */
			mw_post_message(MW_DIALOG_DATE_CHOOSER_DISMISSED_MESSAGE,
					mw_dialog_date_chooser_data.window_dialog_date_chooser_id,
					mw_dialog_date_chooser_data.response_window_id,
					(uint32_t)mw_dialog_date_chooser_data.current_date_year << 16 |
						(uint32_t)mw_dialog_date_chooser_data.current_date_month << 8 |
						mw_dialog_date_chooser_data.current_date_date,
					MW_WINDOW_MESSAGE);
		}
		else if (message->sender_id == mw_dialog_date_chooser_data.button_cancel_id)
		{
			/* do nothing */
		}
		else
		{
			MW_ASSERT(false);
		}

		/* remove the controls */
		mw_remove_control(mw_dialog_date_chooser_data.button_ok_id);
		mw_remove_control(mw_dialog_date_chooser_data.button_ok_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_year_up_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_year_down_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_month_up_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_month_down_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_date_up_id);
		mw_remove_control(mw_dialog_date_chooser_data.arrow_date_down_id);

		/* remove this window */
		mw_remove_window(mw_dialog_date_chooser_data.window_dialog_date_chooser_id);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	default:
		break;
	}
}
