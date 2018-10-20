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

#include <stdio.h>
#include <string.h>
#include "miniwin.h"
#include "dialogs/dialog_common.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const mw_util_rect_t text_rect_standard = {66, 20, 12, 50};
static const mw_util_rect_t text_rect_large = {140, 40, 20, 95};

/************
*** TYPES ***
************/

/**
 * Window data structure
 */
typedef struct
{
	uint8_t button_ok_id;							/**< Control id of ok button */
	mw_ui_button_data_t button_ok_data;				/**< Instance data of ok button */
	uint8_t button_cancel_id;						/**< Control id of cancel button */
	mw_ui_button_data_t button_cancel_data;			/**< Instance data of cancel button */
	uint8_t arrow_hour_up_id;						/**< Control id of hour up button */
	mw_ui_arrow_data_t arrow_hour_up_data;			/**< Instance data of hour up button */
	uint8_t arrow_hour_down_id;						/**< Control id of hour down button */
	mw_ui_arrow_data_t arrow_hour_down_data;		/**< Instance data of hour down button */
	uint8_t arrow_minute_up_id;						/**< Control id of minute up button */
	mw_ui_arrow_data_t arrow_minute_up_data;		/**< Instance data of minute up button */
	uint8_t arrow_minute_down_id;					/**< Control id of minute down button */
	mw_ui_arrow_data_t arrow_minute_down_data;		/**< Instance data of minute down button */
	uint8_t current_time_hours;						/**< Current time in dialog hours */
	uint8_t current_time_mins;						/**< Current time in dialog minutes */
	bool large_size;								/**< True for large size false for standard size */
	uint8_t response_window_id;						/**< Window id to send response message to */
	mw_dialog_response_t mw_dialog_response;		/**< Dialog response structure */
} mw_dialog_time_chooser_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_time_chooser_data_t mw_dialog_time_chooser_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void remove_resources(void);
static void update_arrow_enable_states(void);
static void mw_dialog_time_chooser_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_time_chooser_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Remove this dialog window and all controls
 */
static void remove_resources(void)
{
	mw_remove_control(mw_dialog_time_chooser_data.button_ok_id);
	mw_remove_control(mw_dialog_time_chooser_data.button_ok_id);
	mw_remove_control(mw_dialog_time_chooser_data.arrow_hour_up_id);
	mw_remove_control(mw_dialog_time_chooser_data.arrow_hour_down_id);
	mw_remove_control(mw_dialog_time_chooser_data.arrow_minute_up_id);
	mw_remove_control(mw_dialog_time_chooser_data.arrow_minute_down_id);
	mw_remove_window(mw_dialog_time_chooser_data.mw_dialog_response.window_id);
}

/**
 * Set all the arrow enable states according to value of current time
 */
static void update_arrow_enable_states(void)
{
	mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_minute_up_id, true);
	mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_minute_down_id, true);

	if (mw_dialog_time_chooser_data.current_time_mins == 0)
	{
		mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_minute_down_id, false);
	}
	else if (mw_dialog_time_chooser_data.current_time_mins == 59)
	{
		mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_minute_up_id, false);
	}

	mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_hour_up_id, true);
	mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_hour_down_id, true);

	if (mw_dialog_time_chooser_data.current_time_hours == 0)
	{
		mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_hour_down_id, false);
	}
	else if (mw_dialog_time_chooser_data.current_time_hours == 23)
	{
		mw_set_control_enabled(mw_dialog_time_chooser_data.arrow_hour_up_id, false);
	}

	mw_paint_control(mw_dialog_time_chooser_data.arrow_minute_up_id);
	mw_paint_control(mw_dialog_time_chooser_data.arrow_minute_down_id);
	mw_paint_control(mw_dialog_time_chooser_data.arrow_hour_up_id);
	mw_paint_control(mw_dialog_time_chooser_data.arrow_hour_down_id);
}

/**
 * Window paint routine, called by window manager.
 *
 * @param window_ref The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_time_chooser_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	char text_hour[16];
	char text_min[16];

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
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	snprintf(text_hour, 16, "Hour: %u", (unsigned int)mw_dialog_time_chooser_data.current_time_hours);
	snprintf(text_min, 16, "Minute: %u", (unsigned int)mw_dialog_time_chooser_data.current_time_mins);

	if (mw_dialog_time_chooser_data.large_size)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 101, 40, text_hour);
		mw_gl_string(draw_info, 89, 120, text_min);
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 30, 20, text_hour);
		mw_gl_string(draw_info, 18, 60, text_min);
	}
}

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void mw_dialog_time_chooser_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_ARROW_PRESSED_MESSAGE:
		if (message->sender_id == mw_dialog_time_chooser_data.arrow_hour_up_id)
		{
			if (mw_dialog_time_chooser_data.current_time_hours < 23)
			{
				mw_dialog_time_chooser_data.current_time_hours++;
			}
		}
		else if (message->sender_id == mw_dialog_time_chooser_data.arrow_hour_down_id)
		{
			if (mw_dialog_time_chooser_data.current_time_hours > 0)
			{
				mw_dialog_time_chooser_data.current_time_hours--;
			}
		}
		else if (message->sender_id == mw_dialog_time_chooser_data.arrow_minute_up_id)
		{
			if (mw_dialog_time_chooser_data.current_time_mins < 59)
			{
				mw_dialog_time_chooser_data.current_time_mins++;
			}
		}
		else if (message->sender_id == mw_dialog_time_chooser_data.arrow_minute_down_id)
		{
			if (mw_dialog_time_chooser_data.current_time_mins > 0)
			{
				mw_dialog_time_chooser_data.current_time_mins--;
			}
		}
		else
		{
			MW_ASSERT(false, "Unknown control id");
		}

		/* enable or disable arrow controls as required */
		update_arrow_enable_states();

		/* just paint the changed text */
		if (mw_dialog_time_chooser_data.large_size)
		{
			mw_paint_window_client_rect(mw_dialog_time_chooser_data.mw_dialog_response.window_id, &text_rect_large);
		}
		else
		{
			mw_paint_window_client_rect(mw_dialog_time_chooser_data.mw_dialog_response.window_id, &text_rect_standard);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		/* remove all controls and window */
		remove_resources();

		if (message->sender_id == mw_dialog_time_chooser_data.button_ok_id)
		{
			/* post ok response to receiving window */
			mw_dialog_time_chooser_data.mw_dialog_response.data = mw_dialog_time_chooser_data.current_time_hours << 8 |
					mw_dialog_time_chooser_data.current_time_mins;
			mw_post_message(MW_DIALOG_TIME_CHOOSER_OK_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_time_chooser_data.response_window_id,
					(uint32_t)&mw_dialog_time_chooser_data.mw_dialog_response,
					MW_WINDOW_MESSAGE);
		}
		else if (message->sender_id == mw_dialog_time_chooser_data.button_cancel_id)
		{
			/* post cancel response to receiving window */
			mw_dialog_time_chooser_data.mw_dialog_response.data = MW_UNUSED_MESSAGE_PARAMETER;
			mw_post_message(MW_DIALOG_TIME_CHOOSER_CANCEL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					mw_dialog_time_chooser_data.response_window_id,
					(uint32_t)&mw_dialog_time_chooser_data.mw_dialog_response,
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

uint8_t mw_create_window_dialog_time_chooser(uint16_t x,
		uint16_t y,
		uint8_t start_time_hour,
		uint8_t start_time_minute,
		bool large_size,
		uint8_t response_window_id)
{
	mw_util_rect_t rect;


	/* check the start time */
	if (start_time_hour > 23 || start_time_minute > 59)
	{
		return MW_MAX_WINDOW_COUNT;
	}
	mw_dialog_time_chooser_data.current_time_hours = start_time_hour;
	mw_dialog_time_chooser_data.current_time_mins = start_time_minute;

	/* check width */
	if (large_size)
	{
		rect.width = 226;
		rect.height = 225;
	}
	else
	{
		rect.width = 118;
		rect.height = 130;
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

	mw_dialog_time_chooser_data.large_size = large_size;
	mw_dialog_time_chooser_data.response_window_id = response_window_id;
	rect.x = x;
	rect.y = y;

	mw_dialog_time_chooser_data.mw_dialog_response.window_id = mw_add_window(&rect,
			"Set time",
			mw_dialog_time_chooser_paint_function,
			mw_dialog_time_chooser_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_IS_MODAL,
			NULL);

	/* check if window could be created */
	if (mw_dialog_time_chooser_data.mw_dialog_response.window_id == MW_MAX_WINDOW_COUNT)
	{
		/* it couldn't so exit */
		return MW_MAX_WINDOW_COUNT;
	}

	/* set controls data */
	mw_util_safe_strcpy(mw_dialog_time_chooser_data.button_ok_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	mw_util_safe_strcpy(mw_dialog_time_chooser_data.button_cancel_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "Cancel");
	mw_dialog_time_chooser_data.arrow_hour_up_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	mw_dialog_time_chooser_data.arrow_hour_down_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	mw_dialog_time_chooser_data.arrow_minute_up_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	mw_dialog_time_chooser_data.arrow_minute_down_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;

	if (large_size)
	{
		mw_dialog_time_chooser_data.button_ok_id = mw_ui_button_add_new(5,
				170,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_time_chooser_data.button_ok_data);

		mw_dialog_time_chooser_data.button_cancel_id = mw_ui_button_add_new(120,
				170,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_time_chooser_data.button_cancel_data);

		mw_dialog_time_chooser_data.arrow_hour_up_id = mw_ui_arrow_add_new(186,
				10,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_time_chooser_data.arrow_hour_up_data);

		mw_dialog_time_chooser_data.arrow_hour_down_id = mw_ui_arrow_add_new(186,
				50,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_time_chooser_data.arrow_hour_down_data);

		mw_dialog_time_chooser_data.arrow_minute_up_id = mw_ui_arrow_add_new(186,
				90,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_time_chooser_data.arrow_minute_up_data);

		mw_dialog_time_chooser_data.arrow_minute_down_id = mw_ui_arrow_add_new(186,
				130,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAGS_LARGE_SIZE,
				&mw_dialog_time_chooser_data.arrow_minute_down_data);
	}
	else
	{
		mw_dialog_time_chooser_data.button_ok_id = mw_ui_button_add_new(5,
				90,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_time_chooser_data.button_ok_data);

		mw_dialog_time_chooser_data.button_cancel_id = mw_ui_button_add_new(60,
				90,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_time_chooser_data.button_cancel_data);

		mw_dialog_time_chooser_data.arrow_hour_up_id = mw_ui_arrow_add_new(93,
				5,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_time_chooser_data.arrow_hour_up_data);

		mw_dialog_time_chooser_data.arrow_hour_down_id = mw_ui_arrow_add_new(93,
				25,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_time_chooser_data.arrow_hour_down_data);

		mw_dialog_time_chooser_data.arrow_minute_up_id = mw_ui_arrow_add_new(93,
				45,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_time_chooser_data.arrow_minute_up_data);

		mw_dialog_time_chooser_data.arrow_minute_down_id = mw_ui_arrow_add_new(93,
				65,
				mw_dialog_time_chooser_data.mw_dialog_response.window_id,
				MW_CONTROL_FLAG_IS_VISIBLE,
				&mw_dialog_time_chooser_data.arrow_minute_down_data);
	}

	if (mw_dialog_time_chooser_data.button_ok_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_time_chooser_data.button_cancel_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_time_chooser_data.arrow_hour_up_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_time_chooser_data.arrow_hour_down_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_time_chooser_data.arrow_minute_up_id == MW_MAX_CONTROL_COUNT ||
			mw_dialog_time_chooser_data.arrow_minute_down_id == MW_MAX_CONTROL_COUNT)
	{
		/* remove all controls and window */
		remove_resources();

		return MW_MAX_WINDOW_COUNT;
	}

	/* set arrow enable states appropriately */
	update_arrow_enable_states();

	/* a window has changed visibility so repaint all */
	mw_paint_all();

	return mw_dialog_time_chooser_data.mw_dialog_response.window_id;
}

