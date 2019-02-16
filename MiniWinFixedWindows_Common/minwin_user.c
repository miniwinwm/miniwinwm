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
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_date_icon.h"
#include "window_file_icon.h"
#include "window_help_icon.h"
#include "window_settings_icon.h"
#include "window_temp_icon.h"
#include "window_time_icon.h"
#include "window_temp.h"
#include "window_settings.h"
#include "window_file.h"

/****************
*** CONSTANTS ***
****************/

static const char *radio_button_labels[] = {"12 Hour", "24 Hour"};
#define RADIO_BUTTON_ITEMS_COUNT			(sizeof(radio_button_labels)/sizeof(char *))
const mw_ui_list_box_entry list_box_settings_entries[] = {
		{"2 Minutes", NULL},
		{"5 Minutes",  NULL},
		{"15 Minutes",  NULL},
		{"30 Minutes",  NULL},
		{"1 Hour",  NULL},
		{"2 Hours",  NULL},
		{"4 Hours",  NULL},
		{"6 Hours",  NULL},
		{"12 Hours", NULL}};
#define LIST_BOX_SETTINGS_ITEMS_COUNT		(sizeof(list_box_settings_entries)/sizeof(mw_ui_list_box_entry))
const mw_ui_list_box_entry list_box_file_entries_root[] = {
		{"Images", mw_bitmaps_folder_icon_large},
		{"Documents",  mw_bitmaps_folder_icon_large},
		{"License.txt",  mw_bitmaps_file_icon_large},
		{"Readme.txt",  mw_bitmaps_file_icon_large}};
const uint8_t list_box_file_entries_root_count = (sizeof(list_box_file_entries_root)/sizeof(mw_ui_list_box_entry));
const mw_ui_list_box_entry list_box_file_entries_images[] = {
		{"..", mw_bitmaps_folder_icon_large},
		{"image1.jpg",  mw_bitmaps_file_icon_large},
		{"image2.jpg",  mw_bitmaps_file_icon_large}};
const uint8_t list_box_file_entries_images_count = (sizeof(list_box_file_entries_images)/sizeof(mw_ui_list_box_entry));
const mw_ui_list_box_entry list_box_file_entries_docs[] = {
		{"..", mw_bitmaps_folder_icon_large},
		{"doc1.doc",  mw_bitmaps_file_icon_large},
		{"doc2.doc",  mw_bitmaps_file_icon_large},
		{"doc3.doc",  mw_bitmaps_file_icon_large}};
const uint8_t list_box_file_entries_docs_count = (sizeof(list_box_file_entries_docs)/sizeof(mw_ui_list_box_entry));

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/* windows */
mw_handle_t window_help_icon_handle;
mw_handle_t window_file_icon_handle;
mw_handle_t window_file_handle;
mw_handle_t window_date_icon_handle;
mw_handle_t window_time_icon_handle;
mw_handle_t window_settings_icon_handle;
mw_handle_t window_settings_handle;
mw_handle_t window_temp_icon_handle;
mw_handle_t window_temp_handle;

/* controls */
mw_handle_t button_temp_back_handle;
mw_handle_t button_settings_ok_handle;
mw_handle_t check_box_settings_handle;
mw_handle_t radio_button_settings_handle;
mw_handle_t list_box_settings_handle;
mw_handle_t label_settings_handle;
mw_handle_t arrow_settings_up;
mw_handle_t arrow_settings_down;
mw_handle_t list_box_file_handle;
mw_handle_t arrow_file_up_handle;
mw_handle_t arrow_file_down_handle;
mw_handle_t label_file_handle;
mw_handle_t button_file_ok_handle;

/**********************
*** LOCAL VARIABLES ***
**********************/

/* controls instance data */
static mw_ui_button_data_t button_temp_back_data;
static mw_ui_button_data_t button_settings_ok_data;
static mw_ui_check_box_data_t check_box_settings_ok_data;
static mw_ui_radio_button_data_t radio_button_settings_data;
static mw_ui_label_data_t label_settings_data;
static mw_ui_arrow_data_t arrow_up_settings_data;
static mw_ui_arrow_data_t arrow_down_settings_data;
static mw_ui_arrow_data_t arrow_up_file_data;
static mw_ui_arrow_data_t arrow_down_file_data;
static mw_ui_label_data_t label_file_data;
static mw_ui_button_data_t button_file_ok_data;
static mw_ui_list_box_data_t list_box_settings_data;
static mw_ui_list_box_data_t list_box_file_data;

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

	/* create date icon window with no title bar or border */
	mw_util_set_rect(&r, 10, 1, 104, 104);
	window_date_icon_handle = mw_add_window(&r,
			"",
			window_date_icon_paint_function,
			window_date_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_TOUCH_FOCUS_AND_EVENT,
			NULL);

	/* create time icon window with no title bar or border */
	mw_util_set_rect(&r, 125, 1, 104, 104);
	window_time_icon_handle = mw_add_window(&r,
			"",
			window_time_icon_paint_function,
			window_time_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_TOUCH_FOCUS_AND_EVENT,
			NULL);

	/* create temperature icon window with no title bar or border */
	mw_util_set_rect(&r, 10, 107, 104, 104);
	window_temp_icon_handle = mw_add_window(&r,
			"",
			window_temp_icon_paint_function,
			window_temp_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_TOUCH_FOCUS_AND_EVENT,
			NULL);

	/* create settings icon window with no title bar or border */
	mw_util_set_rect(&r, 125, 107, 104, 104);
	window_settings_icon_handle = mw_add_window(&r,
			"",
			window_settings_icon_paint_function,
			window_settings_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_TOUCH_FOCUS_AND_EVENT,
			NULL);

	/* create file icon window with no title bar or border */
	mw_util_set_rect(&r, 10, 213, 104, 104);
	window_file_icon_handle = mw_add_window(&r,
			"",
			window_file_icon_paint_function,
			window_file_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_TOUCH_FOCUS_AND_EVENT,
			NULL);

	/* create help icon window with no title bar or border */
	mw_util_set_rect(&r, 125, 213, 104, 104);
	window_help_icon_handle = mw_add_window(&r,
			"",
			window_help_icon_paint_function,
			window_help_icon_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_TOUCH_FOCUS_AND_EVENT,
			NULL);

	/* create temperature graphs window */
	mw_util_set_rect(&r, 0, 0, 240, 320);
	window_temp_handle = mw_add_window(&r,
			"",
			window_temp_paint_function,
			window_temp_message_function,
			NULL,
			0,
			0,
			NULL);

	/* create temperature graph window back button */
	mw_util_safe_strcpy(button_temp_back_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "BACK");
	button_temp_back_handle = mw_ui_button_add_new(70,
			285,
			window_temp_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&button_temp_back_data);

	/* create settings window */
	mw_util_set_rect(&r, 0, 0, 240, 320);
	window_settings_handle = mw_add_window(&r,
			"",
			window_settings_paint_function,
			window_settings_message_function,
			NULL,
			0,
			0,
			NULL);

	/* create settings window ok button */
	mw_util_safe_strcpy(button_settings_ok_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	button_settings_ok_handle = mw_ui_button_add_new(70,
			285,
			window_settings_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&button_settings_ok_data);

	/* create settings window check box */
	mw_util_safe_strcpy(check_box_settings_ok_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, "GMT");
	check_box_settings_handle = mw_ui_check_box_add_new(20,
			30,
			window_settings_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&check_box_settings_ok_data);

	/* create settings window radio buttons */
	radio_button_settings_data.number_of_items = RADIO_BUTTON_ITEMS_COUNT;
	radio_button_settings_data.radio_button_labels = radio_button_labels;
	radio_button_settings_handle = mw_ui_radio_button_add_new(20,
			70,
			100,
			window_settings_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&radio_button_settings_data);

	/* create settings window label */
	mw_util_safe_strcpy(label_settings_data.label, MW_UI_LABEL_MAX_CHARS, "Period: Not set");
	label_settings_handle = mw_ui_label_add_new(20,
			160,
			110,
			window_settings_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&label_settings_data);

	/* create a list box */
	list_box_settings_data.number_of_lines = 3;
	list_box_settings_data.number_of_items = LIST_BOX_SETTINGS_ITEMS_COUNT;
	list_box_settings_data.list_box_entries = list_box_settings_entries;
	list_box_settings_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_settings_handle = mw_ui_list_box_add_new(20,
			180,
			138,
			window_settings_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE  | MW_CONTROL_FLAG_LARGE_SIZE,
			&list_box_settings_data);

	arrow_up_settings_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	arrow_settings_up = mw_ui_arrow_add_new(180,
			180,
			window_settings_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
			&arrow_up_settings_data);

	arrow_down_settings_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	arrow_settings_down = mw_ui_arrow_add_new(180,
			232,
			window_settings_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
			&arrow_down_settings_data);

	/* create file window */
	mw_util_set_rect(&r, 0, 0, 240, 320);
	window_file_handle = mw_add_window(&r,
			"",
			window_file_paint_function,
			window_file_message_function,
			NULL,
			0,
			0,
			NULL);

	/* create file window ok button */
	mw_util_safe_strcpy(button_file_ok_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	button_file_ok_handle = mw_ui_button_add_new(70,
			285,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&button_file_ok_data);

	/* create file window label */
	mw_util_safe_strcpy(label_file_data.label, MW_UI_LABEL_MAX_CHARS, "File: Not set");
	label_file_handle = mw_ui_label_add_new(20,
			160,
			110,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&label_file_data);

	/* create a list box for folder listing */
	list_box_file_data.number_of_lines = 3;
	list_box_file_data.number_of_items = list_box_file_entries_root_count;
	list_box_file_data.list_box_entries = list_box_file_entries_root;
	list_box_file_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_file_handle = mw_ui_list_box_add_new(20,
			180,
			138,
			window_file_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE  | MW_CONTROL_FLAG_LARGE_SIZE,
			&list_box_file_data);

	arrow_up_file_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	arrow_file_up_handle = mw_ui_arrow_add_new(180,
			180,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
			&arrow_up_file_data);

	arrow_down_file_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	arrow_file_down_handle = mw_ui_arrow_add_new(180,
			232,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_LARGE_SIZE,
			&arrow_down_file_data);

	mw_paint_all();
}
