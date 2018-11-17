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
#include "miniwin.h"
#include "window_drag.h"
#include "window_gl.h"
#include "window_scroll.h"
#include "window_test.h"
#include "window_yield.h"
#include "window_paint_rect.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const char *menu_bar_labels[] = {"Cat", "Dog", "Gnu"};
#define MENU_BAR_1_ITEMS_COUNT				(sizeof(menu_bar_labels)/sizeof(char *))
static const char *radio_button_labels[] = {"Elk", "Ant", "Hog"};
#define RADIO_BUTTON_1_ITEMS_COUNT			(sizeof(radio_button_labels)/sizeof(char *))
static const mw_ui_list_box_entry list_box_1_labels[] = {
		{"To back", NULL},
		{"Disabled", NULL}};
#define LIST_BOX_1_ITEMS_COUNT				(sizeof(list_box_1_labels)/sizeof(mw_ui_list_box_entry))
static const mw_ui_list_box_entry list_box_2_labels[] = {
		{"Line", NULL},
		{"Square", NULL},
		{"Cube", NULL}};
#define LIST_BOX_2_ITEMS_COUNT				(sizeof(list_box_2_labels)/sizeof(mw_ui_list_box_entry))
static const mw_ui_list_box_entry list_box_3_labels[] = {
		{"List", NULL},
		{"Button", NULL},
		{"Menu", NULL},
		{"Label", NULL},
		{"Scroll", NULL},
		{"Window", NULL},
		{"Control", NULL},
		{"Icon", NULL},
		{"Root", NULL}};
#define LIST_BOX_3_ITEMS_COUNT				(sizeof(list_box_3_labels)/sizeof(mw_ui_list_box_entry))

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/* windows */
mw_handle_t window_test_handle;
mw_handle_t window_gl_handle;
mw_handle_t window_drag_handle;
mw_handle_t window_scroll_handle;
mw_handle_t window_yield_handle;
mw_handle_t window_paint_rect_handle;

/* controls */
mw_handle_t check_box_1_handle;
mw_handle_t arrow_1_handle;
mw_handle_t button_1_handle;
mw_handle_t radio_button_1_handle;
mw_handle_t scroll_bar_vert_1_handle;
mw_handle_t scroll_bar_vert_2_handle;
mw_handle_t scroll_bar_horiz_1_handle;
mw_handle_t label_1_handle;
mw_handle_t progress_bar_1_handle;
mw_handle_t list_box_1_handle;
mw_handle_t list_box_2_handle;
mw_handle_t list_box_3_handle;
mw_handle_t check_box_1_large_handle;
mw_handle_t arrow_1_large_handle;
mw_handle_t button_1_large_handle;
mw_handle_t radio_button_1_large_handle;
mw_handle_t scroll_bar_vert_1_large_handle;
mw_handle_t scroll_bar_vert_2_large_handle;
mw_handle_t scroll_bar_horiz_1_large_handle;
mw_handle_t label_1_large_handle;
mw_handle_t list_box_3_large_handle;

/* controls instance data */
mw_ui_check_box_data_t check_box_1_data;
mw_ui_arrow_data_t arrow_1_data;
mw_ui_button_data_t button_1_data;
mw_ui_radio_button_data_t radio_button_1_data;
mw_ui_list_box_data_t list_box_1_data;
mw_ui_label_data_t label_1_data;
mw_ui_progress_bar_data_t progress_bar_1_data;
mw_ui_list_box_data_t list_box_2_data;
mw_ui_list_box_data_t list_box_3_data;
mw_ui_scroll_bar_vert_data_t scroll_bar_vert_1_data;
mw_ui_scroll_bar_vert_data_t scroll_bar_vert_2_data;
mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_1_data;
mw_ui_check_box_data_t check_box_1_large_data;
mw_ui_arrow_data_t arrow_1_large_data;
mw_ui_button_data_t button_1_large_data;
mw_ui_radio_button_data_t radio_button_1_large_data;
mw_ui_label_data_t label_1_large_data;
mw_ui_list_box_data_t list_box_3_large_data;
mw_ui_scroll_bar_vert_data_t scroll_bar_vert_1_large_data;
mw_ui_scroll_bar_vert_data_t scroll_bar_vert_2_large_data;
mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_1_large_data;

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

	/* create the new graphics library test window */
	mw_util_set_rect(&r, 15, 100, 220, 210);
	window_gl_handle = mw_add_window(&r,
			"GL 1",
			window_gl_paint_function,
			window_gl_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	/* create the new ui test window */
	mw_util_set_rect(&r, 0, 10, 220, 140);
	window_test_handle = mw_add_window(&r,
			"Test 2",
			window_test_paint_function,
			window_test_message_function,
			(char **)menu_bar_labels,
			MENU_BAR_1_ITEMS_COUNT,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_HAS_MENU_BAR | MW_WINDOW_FLAG_MENU_BAR_ENABLED,
			NULL);

	mw_set_menu_bar_items_enabled_state(window_test_handle, mw_util_change_bit(MW_ALL_ITEMS_ENABLED, 0, false));

	/* create a check box control and add it to the ui test window */
	mw_util_safe_strcpy(check_box_1_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, "Check");
	check_box_1_handle = mw_ui_check_box_add_new(10,
			20,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&check_box_1_data);

	/* create a large check box control and add it to the ui test window */
	mw_util_safe_strcpy(check_box_1_large_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, "Check");
	check_box_1_large_handle = mw_ui_check_box_add_new(30,
			235,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&check_box_1_large_data);

	arrow_1_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	arrow_1_handle = mw_ui_arrow_add_new(10,
			50,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&arrow_1_data);

	arrow_1_large_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	arrow_1_large_handle = mw_ui_arrow_add_new(80,
			125,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&arrow_1_large_data);

	/* create a button control and add it to the ui test window */
	mw_util_safe_strcpy(button_1_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Go Big");
	button_1_handle = mw_ui_button_add_new(140,
			80,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_1_data);

	/* create a large button control and add it to the ui test window */
	mw_util_safe_strcpy(button_1_large_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Go Small");
	button_1_large_handle = mw_ui_button_add_new(130,
			235,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&button_1_large_data);

	/* create a new progress bar control and add it to the ui test window */
	progress_bar_1_data.progress_percent = 0;
	progress_bar_1_handle = mw_ui_progress_bar_add_new(10,
			5,
			100,
			10,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&progress_bar_1_data);

	/* create a new radio buttons control and add it to the ui test window */
	radio_button_1_data.number_of_items = RADIO_BUTTON_1_ITEMS_COUNT;
	radio_button_1_data.radio_button_labels = (char **)radio_button_labels;
	radio_button_1_handle = mw_ui_radio_button_add_new(150,
			10,
			60,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&radio_button_1_data);

	/* create a new large radio buttons control and add it to the ui test window */
	radio_button_1_large_data.number_of_items = RADIO_BUTTON_1_ITEMS_COUNT;
	radio_button_1_large_data.radio_button_labels = (char **)radio_button_labels;
	radio_button_1_large_handle = mw_ui_radio_button_add_new(10,
			125,
			60,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&radio_button_1_large_data);

	/* create a new list box control and add it to the ui test window, y position to be directly under the menu bar, control invisible for now */
	list_box_1_data.number_of_lines = LIST_BOX_1_ITEMS_COUNT;
	list_box_1_data.number_of_items = LIST_BOX_1_ITEMS_COUNT;
	list_box_1_data.list_box_entries = list_box_1_labels;
	list_box_1_data.line_enables = mw_util_change_bit(MW_ALL_ITEMS_ENABLED, 1, false);
	list_box_1_handle = mw_ui_list_box_add_new(0,
			0,
			68,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED,
			&list_box_1_data);

	/* create a label control and add it to the ui test window */
	mw_util_safe_strcpy(label_1_data.label, MW_UI_LABEL_MAX_CHARS, "0");
	label_1_handle = mw_ui_label_add_new(120,
			5,
			20,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_1_data);

	/* create a large label control and add it to the ui test window */
	mw_util_safe_strcpy(label_1_large_data.label, MW_UI_LABEL_MAX_CHARS, "0");
	label_1_large_handle = mw_ui_label_add_new(175,
			5,
			20,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&label_1_large_data);

	/* create a new horizontal scroll bar */
	scroll_bar_horiz_1_handle = mw_ui_scroll_bar_horiz_add_new(10,
			80,
			100,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&scroll_bar_horiz_1_data);

	/* create a new large horizontal scroll bar */
	scroll_bar_horiz_1_large_handle = mw_ui_scroll_bar_horiz_add_new(80,
			195,
			150,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&scroll_bar_horiz_1_large_data);

	/* create a new vertical scroll bar */
	scroll_bar_vert_1_handle = mw_ui_scroll_bar_vert_add_new(195,
			10,
			50,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&scroll_bar_vert_1_large_data);

	/* create a new large vertical scroll bar */
	scroll_bar_vert_1_large_handle = mw_ui_scroll_bar_vert_add_new(205,
			10,
			170,
			window_test_handle,
			MW_CONTROL_FLAG_LARGE_SIZE,
			&scroll_bar_vert_1_large_data);

	/* create a new list box control and add it to the ui test window */
	list_box_3_data.number_of_lines = 3;
	list_box_3_data.number_of_items = LIST_BOX_3_ITEMS_COUNT;
	list_box_3_data.list_box_entries = list_box_3_labels;
	list_box_3_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_3_handle = mw_ui_list_box_add_new(60,
			30,
			68,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&list_box_3_data);

	/* create a new large list box control and add it to the ui test window */
	list_box_3_large_data.number_of_lines = 3;
	list_box_3_large_data.number_of_items = LIST_BOX_3_ITEMS_COUNT;
	list_box_3_large_data.list_box_entries = list_box_3_labels;
	list_box_3_large_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_3_large_handle = mw_ui_list_box_add_new(10,
			30,
			130,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&list_box_3_large_data);

	/* create a new vertical scroll bar for the list box*/
	scroll_bar_vert_2_handle = mw_ui_scroll_bar_vert_add_new(127,
			30,
			MW_UI_LIST_BOX_ROW_HEIGHT * list_box_3_data.number_of_lines,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&scroll_bar_vert_2_data);

	/* create a new large vertical scroll bar for the large list box*/
	scroll_bar_vert_2_large_handle = mw_ui_scroll_bar_vert_add_new(139,
			30,
			MW_UI_LIST_BOX_LARGE_ROW_HEIGHT * list_box_3_large_data.number_of_lines,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&scroll_bar_vert_2_large_data);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	/* create the new drag test window */
	mw_util_set_rect(&r, 20, 120, 150, 190);
	window_drag_handle = mw_add_window(&r,
			"Drag 3",
			window_drag_paint_function,
			window_drag_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	mw_util_set_rect(&r, 20, 220, 100, 95);
	window_scroll_handle = mw_add_window(&r,
			"Scroll 5",
			window_scroll_paint_function,
			window_scroll_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR | MW_WINDOW_FLAG_HAS_HORIZ_SCROLL_BAR |
				MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED | MW_WINDOW_FLAG_HORIZ_SCROLL_BAR_ENABLED |
				MW_WINDOW_FLAG_IS_MINIMISED,
			NULL);

	while (mw_process_message());

	mw_util_set_rect(&r, 20, 100, 120, 120);
	window_scroll_handle = mw_add_window(&r,
			"Yield 6",
			window_yield_paint_function,
			window_yield_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_IS_MINIMISED,
			NULL);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	mw_util_set_rect(&r, 20, 150, 180, 120);
	window_paint_rect_handle = mw_add_window(&r,
			"Paint Rect 7",
			window_paint_rect_paint_function,
			window_paint_rect_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	/* create a new list box control and add it to the paint rect window */
	list_box_2_data.number_of_lines = LIST_BOX_2_ITEMS_COUNT;
	list_box_2_data.number_of_items = LIST_BOX_2_ITEMS_COUNT;
	list_box_2_data.list_box_entries = list_box_2_labels;
	list_box_2_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_2_handle = mw_ui_list_box_add_new(100,
			10,
			68,
			window_paint_rect_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&list_box_2_data);

	mw_paint_all();
}
