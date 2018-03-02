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
#include <string.h>
#include "ui/ui_common.h"

#include "window_date_icon.h"
#include "window_file_icon.h"
#include "window_help_icon.h"
#include "window_settings_icon.h"
#include "window_temp_icon.h"
#include "window_time_icon.h"
#include "window_temp.h"
#include "window_settings.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/* windows */

uint8_t window_help_icon_id;
uint8_t window_file_icon_id;
uint8_t window_date_icon_id;
uint8_t window_time_icon_id;
uint8_t window_settings_icon_id;
uint8_t window_temp_icon_id;
uint8_t window_temp_id;
uint8_t window_settings_id;

/* controls */

uint8_t button_temp_ok_id;
uint8_t button_settings_ok_id;
uint8_t check_box_settings_id;

/* controls extra data */

mw_ui_button_data_t button_temp_ok_data;
mw_ui_button_data_t button_settings_ok_data;
mw_ui_check_box_data_t check_box_settings_ok_data;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_user_root_paint_function(const mw_gl_draw_info_t *draw_info)
{
	mw_gl_set_solid_fill_colour(0x9edd);
	mw_gl_clear_pattern();
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_rectangle(draw_info, 0, 0, MW_ROOT_WIDTH, MW_ROOT_HEIGHT);
}

void mw_user_root_message_function(const mw_message_t *message)
{
	(void)message;
}

void mw_user_init(void)
{
	mw_util_rect_t r;

	mw_util_set_rect(&r, 10, 1, 104, 104);
	window_date_icon_id = mw_add_window(&r,
			"",
			window_date_icon_paint_function,
			window_date_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 125, 1, 104, 104);
	window_time_icon_id = mw_add_window(&r,
			"",
			window_time_icon_paint_function,
			window_time_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 10, 107, 104, 104);
	window_temp_icon_id = mw_add_window(&r,
			"",
			window_temp_icon_paint_function,
			window_temp_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 125, 107, 104, 104);
	window_settings_icon_id = mw_add_window(&r,
			"",
			window_settings_icon_paint_function,
			window_settings_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 10, 213, 104, 104);
	window_file_icon_id = mw_add_window(&r,
			"",
			window_file_icon_paint_function,
			window_file_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 125, 213, 104, 104);
	window_help_icon_id = mw_add_window(&r,
			"",
			window_help_icon_paint_function,
			window_help_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 0, 0, 240, 320);
	window_temp_id = mw_add_window(&r,
			"",
			window_temp_paint_function,
			window_temp_message_function,
			NULL,
			0,
			0);

	mw_util_set_rect(&r, 0, 0, 240, 320);
	window_settings_id = mw_add_window(&r,
			"",
			window_settings_paint_function,
			window_settings_message_function,
			NULL,
			0,
			0);

	mw_util_safe_strcpy(button_temp_ok_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "BACK");
	button_temp_ok_id = mw_ui_button_add_new(70,
			285,
			window_temp_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
			&button_temp_ok_data);

	mw_util_safe_strcpy(button_settings_ok_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "BACK");
	button_settings_ok_id = mw_ui_button_add_new(70,
			285,
			window_settings_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
			&button_settings_ok_data);


	mw_util_safe_strcpy(check_box_settings_ok_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, "Blimp");
	check_box_settings_id = mw_ui_check_box_add_new(20,
			30,
			window_settings_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAGS_LARGE_SIZE,
			&check_box_settings_ok_data);

	mw_paint_all();
}
