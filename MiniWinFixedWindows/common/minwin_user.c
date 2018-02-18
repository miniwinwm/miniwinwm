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
#include "window_help.h"
#include "window_file.h"
#include "window_time.h"
#include "window_date.h"
#include "window_settings.h"
#include "window_temp.h"
#include "ui/ui_common.h"
#include "window_temp_graph.h"

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

uint8_t window_help_id;
uint8_t window_file_id;
uint8_t window_date_id;
uint8_t window_time_id;
uint8_t window_settings_id;
uint8_t window_temp_id;
uint8_t window_temp_graph_id;

/* controls */

uint8_t button_ok_id;

/* controls extra data */

mw_ui_button_data_t button_ok_data;

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
	window_date_id = mw_add_window(&r,
			"",
			window_date_paint_function,
			window_date_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 125, 1, 104, 104);
	window_time_id = mw_add_window(&r,
			"",
			window_time_paint_function,
			window_time_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 10, 107, 104, 104);
	window_temp_id = mw_add_window(&r,
			"",
			window_temp_paint_function,
			window_temp_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 125, 107, 104, 104);
	window_settings_id = mw_add_window(&r,
			"",
			window_settings_paint_function,
			window_settings_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 10, 213, 104, 104);
	window_file_id = mw_add_window(&r,
			"",
			window_file_paint_function,
			window_file_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 125, 213, 104, 104);
	window_help_id = mw_add_window(&r,
			"",
			window_help_paint_function,
			window_help_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_TOUCH_FOCUS_AND_EVENT);

	mw_util_set_rect(&r, 0, 0, 240, 320);
	window_temp_graph_id = mw_add_window(&r,
			"",
			window_temp_graph_paint_function,
			window_temp_graph_message_function,
			NULL,
			0,
			0);

	mw_util_safe_strcpy(button_ok_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "BACK");
	button_ok_id = mw_ui_button_add_new(95,
			300,
			window_temp_graph_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_ok_data);

	mw_paint_all();
}
