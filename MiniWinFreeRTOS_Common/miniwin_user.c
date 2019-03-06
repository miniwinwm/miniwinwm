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

#include <stdlib.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_gyro_x.h"
#include "window_gyro_y.h"
#include "window_gyro_z.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/* window */
mw_handle_t window_gyro_x_handle;
mw_handle_t window_gyro_y_handle;
mw_handle_t window_gyro_z_handle;

/* control */
mw_handle_t button_gyro_x_handle;
mw_handle_t label_gyro_x_handle;
mw_handle_t button_gyro_y_handle;
mw_handle_t label_gyro_y_handle;
mw_handle_t button_gyro_z_handle;
mw_handle_t label_gyro_z_handle;

/**********************
*** LOCAL VARIABLES ***
**********************/

/* controls instance data */
static mw_ui_label_data_t label_gyro_x_data;
static mw_ui_button_data_t button_gyro_x_data;
static mw_ui_label_data_t label_gyro_y_data;
static mw_ui_button_data_t button_gyro_y_data;
static mw_ui_label_data_t label_gyro_z_data;
static mw_ui_button_data_t button_gyro_z_data;

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

	mw_util_set_rect(&r, 0, 0, 160, 100);
	window_gyro_x_handle = mw_add_window(&r,
			"Gyro X",
			window_gyro_x_paint_function,
			window_gyro_x_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	(void)mw_util_safe_strcpy(label_gyro_x_data.label, MW_UI_LABEL_MAX_CHARS, "0");
	label_gyro_x_handle = mw_ui_label_add_new(100,
			5,
			MW_UI_BUTTON_WIDTH,
			window_gyro_x_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&label_gyro_x_data);

	(void)mw_util_safe_strcpy(button_gyro_x_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Zero");
	button_gyro_x_handle = mw_ui_button_add_new(100,
			40,
			window_gyro_x_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_gyro_x_data);

	(void)mw_util_set_rect(&r, 20, 110, 160, 100);
	window_gyro_y_handle = mw_add_window(&r,
			"Gyro Y",
			window_gyro_y_paint_function,
			window_gyro_y_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	(void)mw_util_safe_strcpy(label_gyro_y_data.label, MW_UI_LABEL_MAX_CHARS, "0");
	label_gyro_y_handle = mw_ui_label_add_new(100,
			5,
			MW_UI_BUTTON_WIDTH,
			window_gyro_y_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&label_gyro_y_data);

	(void)mw_util_safe_strcpy(button_gyro_y_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Zero");
	button_gyro_y_handle = mw_ui_button_add_new(100,
			40,
			window_gyro_y_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_gyro_y_data);

	(void)mw_util_set_rect(&r, 40, 220, 160, 100);
	window_gyro_z_handle = mw_add_window(&r,
			"Gyro Z",
			window_gyro_z_paint_function,
			window_gyro_z_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	(void)mw_util_safe_strcpy(label_gyro_z_data.label, MW_UI_LABEL_MAX_CHARS, "0");
	label_gyro_z_handle = mw_ui_label_add_new(100,
			5,
			MW_UI_BUTTON_WIDTH,
			window_gyro_z_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&label_gyro_z_data);

	(void)mw_util_safe_strcpy(button_gyro_z_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Zero");
	button_gyro_z_handle = mw_ui_button_add_new(100,
			40,
			window_gyro_z_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_gyro_z_data);

	mw_paint_all();
}
