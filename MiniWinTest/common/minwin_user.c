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
#include "window_drag.h"
#include "window_gl.h"
#include "window_ok_cancel.h"
#include "window_scroll.h"
#include "window_test.h"
#include "window_yield.h"
#include "window_paint_rect.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const char *menu_bar_labels[] = {"Cat", "Dog", "\xa2\xa3\xa4"};
#define MENU_BAR_1_ITEMS_COUNT				(sizeof(menu_bar_labels)/sizeof(char *))
static const char *radio_button_labels[] = {"Elk", "Ant", "Hog"};
#define RADIO_BUTTON_1_ITEMS_COUNT			(sizeof(radio_button_labels)/sizeof(char *))
static const char *list_box_1_labels[] = {"Aardvark", "Heffalump", "Dingbat"};
#define LIST_BOX_1_ITEMS_COUNT				(sizeof(list_box_1_labels)/sizeof(char *))
static const char *list_box_2_labels[] = {"Line", "Square", "Cube"};
#define LIST_BOX_2_ITEMS_COUNT				(sizeof(list_box_2_labels)/sizeof(char *))
static const char *list_box_3_labels[] = {"List", "Button", "Menu", "Label", "Scroll", "Window", "Control", "Icon", "Root"};
#define LIST_BOX_3_ITEMS_COUNT				(sizeof(list_box_3_labels)/sizeof(char *))

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/* windows */
uint8_t window_test_id;
uint8_t window_gl_id;
uint8_t window_drag_id;
uint8_t window_ok_cancel_id;
uint8_t window_scroll_id;
uint8_t window_yield_id;
uint8_t window_paint_rect_id;

/* controls */
uint8_t check_box_1_id;
uint8_t radio_button_1_id;
uint8_t button_ok_id;
uint8_t button_cancel_id;
uint8_t scroll_bar_vert_1_id;
uint8_t scroll_bar_vert_2_id;
uint8_t scroll_bar_horiz_1_id;
uint8_t int_number_chooser_1_id;
uint8_t keyboard_1_id;
uint8_t label_1_id;
uint8_t progress_bar_1_id;
uint8_t list_box_1_id;
uint8_t list_box_2_id;
uint8_t list_box_3_id;

/* controls extra data */
mw_ui_button_data_t button_ok_data;
mw_ui_button_data_t button_cancel_data;
mw_ui_check_box_data_t check_box_1_data;
mw_ui_radio_button_data_t radio_button_1_data;
mw_ui_list_box_data_t list_box_1_data;
mw_ui_label_data_t label_1_data;
mw_ui_int_number_chooser_data_t int_number_chooser_1_data;
mw_ui_progress_bar_data_t progress_bar_1_data;
mw_ui_keyboard_data_t keyboard_1_data;
mw_ui_list_box_data_t list_box_2_data;
mw_ui_list_box_data_t list_box_3_data;
mw_ui_scroll_bar_vert_data_t scroll_bar_vert_1_data;
mw_ui_scroll_bar_vert_data_t scroll_bar_vert_2_data;
mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_1_data;

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
	window_gl_id = mw_add_window(&r,
			"GL 1",
			window_gl_paint_function,
			window_gl_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	/* create the new ui test window */
	mw_util_set_rect(&r, 10, 10, 220, 250);
	window_test_id = mw_add_window(&r,
			"Test 2",
			window_test_paint_function,
			window_test_message_function,
			(char **)menu_bar_labels,
			MENU_BAR_1_ITEMS_COUNT,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_HAS_MENU_BAR | MW_WINDOW_MENU_BAR_ENABLED);

	mw_set_menu_bar_items_enabled_state(window_test_id, mw_util_change_bit(MW_ALL_ITEMS_ENABLED, 0, false));

	/* create a check box control and add it to the ui test window */
	mw_util_safe_strcpy(check_box_1_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, "CHECKER");	
	check_box_1_id = mw_ui_check_box_add_new(10,
			40,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&check_box_1_data);

	/* create a new progress bar control and add it to the ui test window */
	progress_bar_1_data.progress_percent = 0;
	progress_bar_1_id = mw_ui_progress_bar_add_new(70,
			5,
			100,
			10,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&progress_bar_1_data);

	/* create a new radio buttons control and add it to the ui test window */
	radio_button_1_data.number_of_items = RADIO_BUTTON_1_ITEMS_COUNT;
	radio_button_1_data.radio_button_labels = (char **)radio_button_labels;
	radio_button_1_id = mw_ui_radio_button_add_new(160,
			40,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&radio_button_1_data);

	/* create a new list box control and add it to the ui test window, y position to be directly under the menu bar, control invisible for now */
	list_box_1_data.number_of_lines = LIST_BOX_1_ITEMS_COUNT;
	list_box_1_data.list_box_labels = (char **)list_box_1_labels;
	list_box_1_data.line_enables = mw_util_change_bit(MW_ALL_ITEMS_ENABLED, 1, false);
	list_box_1_id = mw_ui_list_box_add_new(0,
			0,
			window_test_id,
			MW_CONTROL_FLAG_IS_ENABLED,
			&list_box_1_data);

	/* create a new label control and add it to the ui test window */
	mw_util_safe_strcpy(label_1_data.label, MW_UI_LABEL_MAX_CHARS, "0");
	label_1_id = mw_ui_label_add_new(180,
			5,
			20,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_1_data);

	/* create a new horizontal scroll bar */
	scroll_bar_horiz_1_id = mw_ui_scroll_bar_horiz_add_new(10,
			80,
			100,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&scroll_bar_horiz_1_data);

	/* create a new vertical scroll bar */
	scroll_bar_vert_1_id = mw_ui_scroll_bar_vert_add_new(200,
			140,
			50,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&scroll_bar_vert_1_data);

	/* create a new number chooser and add it to the drag test window */
	int_number_chooser_1_data.is_only_positive = false;
	int_number_chooser_1_id = mw_ui_int_number_chooser_add_new(10,
			100,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&int_number_chooser_1_data);
	mw_ui_common_post_number_to_control(int_number_chooser_1_id, (uint32_t)-67);

	/* create a new keyboard and add it to the drag test window */
	keyboard_1_id = mw_ui_keyboard_add_new(10,
			140,
			window_test_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&keyboard_1_data);
	mw_ui_common_post_pointer_to_control(keyboard_1_id, "Fred");

	/* create a new list box control and add it to the ui test window */
	list_box_3_data.number_of_lines = 3;
	list_box_3_data.list_box_labels = (char **)list_box_3_labels;
	list_box_3_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_3_id = mw_ui_list_box_add_new(75,
			25,
			window_test_id,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&list_box_3_data);

	/* post the number of items in the scrolling list box to the owning window */
	mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_test_id,
			LIST_BOX_3_ITEMS_COUNT,
			MW_WINDOW_MESSAGE);

	/* create a new vertical scroll bar */
	scroll_bar_vert_2_id = mw_ui_scroll_bar_vert_add_new(75 + MW_UI_LIST_BOX_WIDTH - 1,
			25,
			MW_UI_LIST_BOX_ROW_HEIGHT * 3,
			window_test_id,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&scroll_bar_vert_2_data);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	/* create the new drag test window */
	mw_util_set_rect(&r, 20, 120, 150, 190);
	window_drag_id = mw_add_window(&r,
			"Drag 3",
			window_drag_paint_function,
			window_drag_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	/* create the new ok/cancel window, create it as invisible */
	mw_util_set_rect(&r, 20, 30, 150, 50);
	window_ok_cancel_id = mw_add_window(&r,
			"Ok Cancel 4",
			window_ok_cancel_paint_function,
			window_ok_cancel_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR);

	/* create a first new button control and add it to the ok/cancel window */
	mw_util_safe_strcpy(button_ok_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	button_ok_id = mw_ui_button_add_new(10,
			10,
			window_ok_cancel_id,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&button_ok_data);

	/* create a second new button control and add it to the ok/cancel window */
	mw_util_safe_strcpy(button_cancel_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "CANCEL");
	button_cancel_id = mw_ui_button_add_new(80,
			10,
			window_ok_cancel_id,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_cancel_data);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	mw_util_set_rect(&r, 20, 220, 100, 95);
	window_scroll_id = mw_add_window(&r,
			"Scroll 5",
			window_scroll_paint_function,
			window_scroll_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_HAS_VERT_SCROLL_BAR | MW_WINDOW_HAS_HORIZ_SCROLL_BAR |
				MW_WINDOWS_VERT_SCROLL_BAR_ENABLED | MW_WINDOWS_HORIZ_SCROLL_BAR_ENABLED |
				MW_WINDOW_FLAG_IS_MINIMISED);

	while (mw_process_message());

	mw_util_set_rect(&r, 20, 100, 120, 120);
	window_scroll_id = mw_add_window(&r,
			"Yield 6",
			window_yield_paint_function,
			window_yield_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_IS_MINIMISED);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message());

	mw_util_set_rect(&r, 20, 150, 180, 120);
	window_paint_rect_id = mw_add_window(&r,
			"Paint Rect 7",
			window_paint_rect_paint_function,
			window_paint_rect_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE);

	/* create a new list box control and add it to the paint rect window */
	list_box_2_data.number_of_lines = LIST_BOX_2_ITEMS_COUNT;
	list_box_2_data.list_box_labels = (char **)list_box_2_labels;
	list_box_2_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_2_id = mw_ui_list_box_add_new(100,
			10,
			window_paint_rect_id,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&list_box_2_data);

	mw_paint_all();
}
