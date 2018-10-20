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

#include "miniwin.h"
#include "ui/ui_common.h"
#include "window_file.h"
#include "window_text.h"

/*************************
*** EXTERNAL VARIABLES ***
**************************/

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

uint8_t window_file_id;

/* controls */
uint8_t button_open_id;
uint8_t button_set_clock_id;
uint8_t button_create_id;
uint8_t label_time_id;
uint8_t label_date_id;

/* controls instance data */
mw_ui_button_data_t button_open_data;
mw_ui_button_data_t button_set_clock_data;
mw_ui_button_data_t button_create_data;
mw_ui_label_data_t label_time_data;
mw_ui_label_data_t label_date_data;

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
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_PURPLE);
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

	mw_util_set_rect(&r, 15, 100, 220, 210);
	window_file_id = mw_add_window(&r,
			"File Demo",
			window_file_paint_function,
			window_file_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	mw_util_safe_strcpy(button_open_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Open");
	button_open_id = mw_ui_button_add_new(80,
			165,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_open_data);

	mw_util_safe_strcpy(button_set_clock_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Set");
	button_set_clock_id = mw_ui_button_add_new(80,
			145,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_set_clock_data);

	mw_util_safe_strcpy(button_create_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Create");
	button_create_id = mw_ui_button_add_new(80,
			125,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&button_create_data);

	mw_util_safe_strcpy(label_time_data.label,
			MW_UI_LABEL_MAX_CHARS,
			"Waiting...");
	label_time_id = mw_ui_label_add_new(5,
			5,
			100,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_time_data);

	mw_util_safe_strcpy(label_date_data.label,
			MW_UI_LABEL_MAX_CHARS,
			"Waiting...");
	label_date_id = mw_ui_label_add_new(5,
			20,
			100,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_date_data);

	mw_paint_all();
}
