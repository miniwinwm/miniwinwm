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

uint8_t button_id;
uint8_t list_box_file_id;
uint8_t arrow_file_up_id;
uint8_t arrow_file_down_id;
uint8_t arrow_file_back_id;
uint8_t label_file_id;
uint8_t label_folder_id;

/* controls extra data */

mw_ui_button_data_t button_data;
mw_ui_list_box_data_t list_box_file_data;
mw_ui_arrow_data_t arrow_up_file_data;
mw_ui_arrow_data_t arrow_down_file_data;
mw_ui_arrow_data_t arrow_back_file_data;
mw_ui_label_data_t label_file_data;
mw_ui_label_data_t label_folder_data;

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

	mw_util_safe_strcpy(button_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Open");
	button_id = mw_ui_button_add_new(80,
			165,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_data);

	/* create a list box for directory listing */
	list_box_file_data.number_of_lines = 5;
	list_box_file_data.number_of_items = 0;
	list_box_file_data.list_box_entries = NULL;
	list_box_file_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_file_id = mw_ui_list_box_add_new(50,
			20,
			120,
			window_file_id,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&list_box_file_data);

	arrow_up_file_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	arrow_file_up_id = mw_ui_arrow_add_new(175,
			20,
			window_file_id,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&arrow_up_file_data);

	arrow_down_file_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	arrow_file_down_id = mw_ui_arrow_add_new(175,
			74,
			window_file_id,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&arrow_down_file_data);

	arrow_back_file_data.mw_ui_arrow_direction = MW_UI_ARROW_LEFT;
	arrow_file_back_id = mw_ui_arrow_add_new(175,
			46,
			window_file_id,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&arrow_back_file_data);

	/* create file label */
	mw_util_safe_strcpy(label_file_data.label, MW_UI_LABEL_MAX_CHARS, "");
	label_file_id = mw_ui_label_add_new(20,
			140,
			180,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_file_data);

	/* create folder label */
	mw_util_safe_strcpy(label_file_data.label, MW_UI_LABEL_MAX_CHARS, "");
	label_folder_id = mw_ui_label_add_new(20,
			125,
			180,
			window_file_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_folder_data);

	mw_paint_all();
}
