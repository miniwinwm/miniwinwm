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
#include "window_drag.h"
#include "window_gl.h"
#include "window_scroll.h"
#include "window_test.h"
#include "window_yield.h"
#include "window_paint_rect.h"
#include "window_tabs.h"
#include "window_tree.h"

/****************
*** CONSTANTS ***
****************/

static char menu_bar_label_cat[] = "Cat";
static char menu_bar_label_dog[] = "Dog";
static char menu_bar_label_gnu[] = "Gnu";
static char *menu_bar_labels[] = {menu_bar_label_cat, menu_bar_label_dog, menu_bar_label_gnu};

static char radio_button_label_elk[] = "Elk";
static char radio_button_label_ant[] = "Ant";
static char radio_button_label_hog[] = "Hog";
static char *radio_button_labels[] = {radio_button_label_elk, radio_button_label_ant, radio_button_label_hog};

static char list_box_label_to_back[] = "To Back";
static char list_box_label_disabled[] = "Disabled";
static const mw_ui_list_box_entry list_box_1_entries[] = {
		{list_box_label_to_back, NULL},
		{list_box_label_disabled, NULL}};

static char list_box_label_line[] = "Line";
static char list_box_label_square[] = "Square";
static char list_box_label_cube[] = "Cube";
static const mw_ui_list_box_entry list_box_2_entries[] = {
		{list_box_label_line, NULL},
		{list_box_label_square, NULL},
		{list_box_label_cube, NULL}};

static char list_box_label_list[] = "List";
static char list_box_label_button[] = "Button";
static char list_box_label_menu[] = "Menu";
static char list_box_label_label[] = "Label";
static char list_box_label_scroll[] = "Scroll";
static char list_box_label_window[] = "Window";
static char list_box_label_control[] = "Control";
static char list_box_label_icon[] = "Icon";
static char list_box_label_root[] = "Root";
static const mw_ui_list_box_entry list_box_3_entries[] = {
		{list_box_label_list, NULL},
		{list_box_label_button, NULL},
		{list_box_label_menu, NULL},
		{list_box_label_label, NULL},
		{list_box_label_scroll, NULL},
		{list_box_label_window, NULL},
		{list_box_label_control, NULL},
		{list_box_label_icon, NULL},
		{list_box_label_root, NULL}};

static char *tabs_labels_auto[] = {"Freddy", "Bert", "Pete"};
static char *tabs_labels_fixed[] = {"Cat", "Dog", "Mouse"};

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
mw_handle_t window_tabs_handle;
mw_handle_t window_tree_handle;

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
mw_handle_t scroll_bar_vert_3_handle;
mw_handle_t tabs_auto_handle;
mw_handle_t tabs_fixed_handle;
mw_handle_t label_2_handle;
mw_handle_t label_3_handle;
mw_handle_t label_4_handle;
mw_handle_t label_5_handle;
mw_handle_t label_6_handle;
mw_handle_t tree_handle;
mw_handle_t arrow_2_handle;
mw_handle_t arrow_3_handle;
mw_handle_t label_7_handle;

/**********************
*** LOCAL VARIABLES ***
**********************/

/* controls instance data */
static mw_ui_check_box_data_t check_box_1_data;
static mw_ui_arrow_data_t arrow_1_data;
static mw_ui_button_data_t button_1_data;
static mw_ui_radio_button_data_t radio_button_1_data;
static mw_ui_list_box_data_t list_box_1_data;
static mw_ui_label_data_t label_1_data;
static mw_ui_progress_bar_data_t progress_bar_1_data;
static mw_ui_list_box_data_t list_box_2_data;
static mw_ui_list_box_data_t list_box_3_data;
static mw_ui_scroll_bar_vert_data_t scroll_bar_vert_1_data;
static mw_ui_scroll_bar_vert_data_t scroll_bar_vert_2_data;
static mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_1_data;
static mw_ui_check_box_data_t check_box_1_large_data;
static mw_ui_arrow_data_t arrow_1_large_data;
static mw_ui_button_data_t button_1_large_data;
static mw_ui_radio_button_data_t radio_button_1_large_data;
static mw_ui_label_data_t label_1_large_data;
static mw_ui_list_box_data_t list_box_3_large_data;
static mw_ui_scroll_bar_vert_data_t scroll_bar_vert_1_large_data;
static mw_ui_scroll_bar_vert_data_t scroll_bar_vert_2_large_data;
static mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_1_large_data;
static mw_ui_scroll_bar_vert_data_t scroll_bar_vert_3_data;
static mw_ui_tabs_data_t tabs_auto_data;
static mw_ui_tabs_data_t tabs_fixed_data;
static mw_ui_label_data_t label_2_data;
static mw_ui_label_data_t label_3_data;
static mw_ui_label_data_t label_4_data;
static mw_ui_label_data_t label_5_data;
static mw_ui_label_data_t label_6_data;
static mw_ui_tree_data_t tree_data;
static mw_ui_arrow_data_t arrow_2_data;
static mw_ui_arrow_data_t arrow_3_data;
static mw_tree_container_node_t tree_nodes_array[20];
static mw_ui_label_data_t label_7_data;

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
	mw_handle_t intermediate_handle;
	mw_handle_t fold1_handle;
	mw_handle_t fold2_handle;
	mw_handle_t fold3_handle;

	/* create the new graphics library test window */
	mw_util_set_rect(&r, 15, 100, 220, 210);
	window_gl_handle = mw_add_window(&r,
			"GL 1",
			window_gl_paint_function,
			window_gl_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message())
	{
	}

	/* create the new ui test window */
	mw_util_set_rect(&r, 0, 10, 220, 140);
	size_t menu_bar_count = sizeof(menu_bar_labels) / sizeof(char *);
	window_test_handle = mw_add_window(&r,
			"Test 2",
			window_test_paint_function,
			window_test_message_function,
			menu_bar_labels,
			(uint8_t)menu_bar_count,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_HAS_MENU_BAR | MW_WINDOW_FLAG_MENU_BAR_ENABLED,
			NULL);

	mw_set_menu_bar_items_enabled_state(window_test_handle, mw_util_change_bit(MW_ALL_ITEMS_ENABLED, 0, false));

	/* create a check box control and add it to the ui test window */
	(void)mw_util_safe_strcpy(check_box_1_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, "Check");
	check_box_1_handle = mw_ui_check_box_add_new(10,
			20,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&check_box_1_data);

	/* create a large check box control and add it to the ui test window */
	(void)mw_util_safe_strcpy(check_box_1_large_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, "Check");
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
	(void)mw_util_safe_strcpy(button_1_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Go Big");
	button_1_handle = mw_ui_button_add_new(140,
			80,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_1_data);

	/* create a large button control and add it to the ui test window */
	(void)mw_util_safe_strcpy(button_1_large_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Go Small");
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
	size_t radio_button_1_count = sizeof(radio_button_labels) / sizeof(char *);
	radio_button_1_data.number_of_items = (uint8_t)radio_button_1_count;
	radio_button_1_data.radio_button_labels = radio_button_labels;
	radio_button_1_handle = mw_ui_radio_button_add_new(150,
			10,
			60,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&radio_button_1_data);

	/* create a new large radio buttons control and add it to the ui test window */
	radio_button_1_large_data.number_of_items = (uint8_t)radio_button_1_count;
	radio_button_1_large_data.radio_button_labels = radio_button_labels;
	radio_button_1_large_handle = mw_ui_radio_button_add_new(10,
			125,
			60,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&radio_button_1_large_data);

	/* create a new list box control and add it to the ui test window, y position to be directly under the menu bar, control invisible for now */
	size_t list_box_1_count = sizeof(list_box_1_entries) / sizeof(mw_ui_list_box_entry);
	list_box_1_data.number_of_lines = (uint8_t)list_box_1_count;
	list_box_1_data.number_of_items = (uint8_t)list_box_1_count;
	list_box_1_data.list_box_entries = list_box_1_entries;
	list_box_1_data.line_enables = mw_util_change_bit(MW_ALL_ITEMS_ENABLED, 1, false);
	list_box_1_handle = mw_ui_list_box_add_new(0,
			0,
			68,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED,
			&list_box_1_data);

	/* create a label control and add it to the ui test window */
	(void)mw_util_safe_strcpy(label_1_data.label, MW_UI_LABEL_MAX_CHARS, "0");
	label_1_handle = mw_ui_label_add_new(120,
			5,
			20,
			window_test_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_1_data);

	/* create a large label control and add it to the ui test window */
	(void)mw_util_safe_strcpy(label_1_large_data.label, MW_UI_LABEL_MAX_CHARS, "0");
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
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&scroll_bar_vert_1_data);

	/* create a new large vertical scroll bar */
	scroll_bar_vert_1_large_handle = mw_ui_scroll_bar_vert_add_new(205,
			10,
			170,
			window_test_handle,
			MW_CONTROL_FLAG_LARGE_SIZE | MW_CONTROL_FLAG_IS_ENABLED,
			&scroll_bar_vert_1_large_data);

	/* create a new list box control and add it to the ui test window */
	size_t list_box_3_count = sizeof(list_box_3_entries) / sizeof(mw_ui_list_box_entry);
	list_box_3_data.number_of_lines = 3U;
	list_box_3_data.number_of_items = (uint8_t)list_box_3_count;
	list_box_3_data.list_box_entries = list_box_3_entries;
	list_box_3_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_3_handle = mw_ui_list_box_add_new(60,
			30,
			68,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&list_box_3_data);

	/* create a new large list box control and add it to the ui test window */
	list_box_3_large_data.number_of_lines = 3U;
	list_box_3_large_data.number_of_items = (uint8_t)list_box_3_count;
	list_box_3_large_data.list_box_entries = list_box_3_entries;
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
			(int16_t)MW_UI_LIST_BOX_ROW_HEIGHT * (int16_t)list_box_3_data.number_of_lines,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&scroll_bar_vert_2_data);

	/* create a new large vertical scroll bar for the large list box*/
	scroll_bar_vert_2_large_handle = mw_ui_scroll_bar_vert_add_new(139,
			30,
			(int16_t)MW_UI_LIST_BOX_LARGE_ROW_HEIGHT * (int16_t)list_box_3_large_data.number_of_lines,
			window_test_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&scroll_bar_vert_2_large_data);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message())
	{
	}

	/* create the new drag test window */
	mw_util_set_rect(&r, 20, 120, 180, 190);
	window_drag_handle = mw_add_window(&r,
			"Drag 3",
			window_drag_paint_function,
			window_drag_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR | MW_WINDOW_FLAG_HAS_HORIZ_SCROLL_BAR |
				MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED | MW_WINDOW_FLAG_HORIZ_SCROLL_BAR_ENABLED | MW_WINDOW_FLAG_LARGE_SIZE,
			NULL);

	/* create a new vertical scroll bar for the drag window */
	scroll_bar_vert_3_handle = mw_ui_scroll_bar_vert_add_new(120,
			30,
			100,
			window_drag_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&scroll_bar_vert_3_data);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message())
	{
	}

	mw_util_set_rect(&r, 20, 220, 100, 95);
	window_scroll_handle = mw_add_window(&r,
			"Scroll 4",
			window_scroll_paint_function,
			window_scroll_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR | MW_WINDOW_FLAG_HAS_HORIZ_SCROLL_BAR |
				MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED | MW_WINDOW_FLAG_HORIZ_SCROLL_BAR_ENABLED |
				MW_WINDOW_FLAG_IS_MINIMISED,
			NULL);

	while (mw_process_message())
	{
	}

	mw_util_set_rect(&r, 20, 100, 120, 120);
	window_scroll_handle = mw_add_window(&r,
			"Yield 5",
			window_yield_paint_function,
			window_yield_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_IS_MINIMISED,
			NULL);

	/* process waiting messages to reduce queue contents */
	while (mw_process_message())
	{
	}

	mw_util_set_rect(&r, 20, 150, 180, 120);
	window_paint_rect_handle = mw_add_window(&r,
			"Paint Rect 6",
			window_paint_rect_paint_function,
			window_paint_rect_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	/* create a new list box control and add it to the paint rect window */
	size_t list_box_2_count = sizeof(list_box_2_entries) / sizeof(mw_ui_list_box_entry);
	list_box_2_data.number_of_lines = (uint8_t)list_box_2_count;
	list_box_2_data.number_of_items = (uint8_t)list_box_2_count;
	list_box_2_data.list_box_entries = list_box_2_entries;
	list_box_2_data.line_enables = MW_ALL_ITEMS_ENABLED;
	list_box_2_handle = mw_ui_list_box_add_new(100,
			10,
			68,
			window_paint_rect_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&list_box_2_data);

	mw_util_set_rect(&r, 30, 160, 180, 120);
	window_tabs_handle = mw_add_window(&r,
			"Tabs 7",
			window_tabs_paint_function,
			window_tabs_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	/* create an automatic tabs control */
    tabs_auto_data.number_of_tabs = 3;
    tabs_auto_data.tabs_labels = tabs_labels_auto;
    tabs_auto_data.foreground_colour = MW_CONTROL_UP_COLOUR;
    tabs_auto_data.background_colour = MW_HAL_LCD_WHITE;
    tabs_auto_data.automatic = true;
    tabs_auto_handle = mw_ui_tabs_add_new(0, 0, 0, window_tabs_handle,
    		MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
    		&tabs_auto_data);

    /* create a fixed tabs control */
    tabs_fixed_data.number_of_tabs = 3;
    tabs_fixed_data.tabs_labels = tabs_labels_fixed;
    tabs_fixed_data.foreground_colour = MW_CONTROL_UP_COLOUR;
    tabs_fixed_data.background_colour = MW_CONTROL_UP_COLOUR;
    tabs_fixed_data.automatic = false;
    tabs_fixed_handle = mw_ui_tabs_add_new(20, 30, 120, window_tabs_handle,
    		MW_CONTROL_FLAG_IS_ENABLED,
    		&tabs_fixed_data);

	/* create label controls and add them to the tabs test window */
	(void)mw_util_safe_strcpy(label_2_data.label, MW_UI_LABEL_MAX_CHARS, "Cat");
	label_2_handle = mw_ui_label_add_new(5,
			40,
			20,
			window_tabs_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_2_data);

	(void)mw_util_safe_strcpy(label_3_data.label, MW_UI_LABEL_MAX_CHARS, "Dog");
	label_3_handle = mw_ui_label_add_new(25,
			50,
			20,
			window_tabs_handle,
			MW_CONTROL_FLAG_IS_ENABLED,
			&label_3_data);

	(void)mw_util_safe_strcpy(label_4_data.label, MW_UI_LABEL_MAX_CHARS, "Elk");
	label_4_handle = mw_ui_label_add_new(50,
			50,
			20,
			window_tabs_handle,
			MW_CONTROL_FLAG_IS_ENABLED,
			&label_4_data);

	(void)mw_util_safe_strcpy(label_5_data.label, MW_UI_LABEL_MAX_CHARS, "Ant");
	label_5_handle = mw_ui_label_add_new(60,
			60,
			20,
			window_tabs_handle,
			MW_CONTROL_FLAG_IS_ENABLED,
			&label_5_data);

	(void)mw_util_safe_strcpy(label_6_data.label, MW_UI_LABEL_MAX_CHARS, "Bee");
	label_6_handle = mw_ui_label_add_new(70,
			70,
			20,
			window_tabs_handle,
			MW_CONTROL_FLAG_IS_ENABLED,
			&label_6_data);

	mw_util_set_rect(&r, 40, 170, 180, 140);
	window_tree_handle = mw_add_window(&r,
			"Tree 8",
			window_tree_paint_function,
			window_tree_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	arrow_2_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	arrow_2_handle = mw_ui_arrow_add_new(155,
			5,
			window_tree_handle,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&arrow_2_data);

	arrow_3_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	arrow_3_handle = mw_ui_arrow_add_new(155,
			59,
			window_tree_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&arrow_3_data);

	tree_data.number_of_lines = 5U;
	tree_data.file_icon = NULL;
	tree_data.folder_icon = NULL;
	intermediate_handle = mw_tree_container_init(&tree_data.tree_container,
			tree_nodes_array,
			20,
			"Root/",
			0U,
			MW_TREE_CONTAINER_NO_SELECT,
			NULL,
			'/');
	tree_data.root_handle = intermediate_handle;
	tree_handle = mw_ui_tree_add_new(5,
			5,
			150,
			window_tree_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&tree_data);

	(void)mw_util_safe_strcpy(label_7_data.label, MW_UI_LABEL_MAX_CHARS, "Not set");
	label_7_handle = mw_ui_label_add_new(5,
			100,
			150,
			window_tree_handle,
			MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_IS_VISIBLE,
			&label_7_data);

	(void)mw_tree_container_add_node(&tree_data.tree_container,
			tree_data.root_handle,
			"file1",
			0U);
	fold1_handle = mw_tree_container_add_node(&tree_data.tree_container,
			tree_data.root_handle,
			"Foldy1",
			MW_TREE_CONTAINER_NODE_IS_FOLDER | MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN);
	(void)mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"file2",
			0U);
	(void)mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"file3",
			0U);
	fold2_handle = mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"fold2",
			MW_TREE_CONTAINER_NODE_IS_FOLDER | MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN);
	fold3_handle = mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"fold3",
			MW_TREE_CONTAINER_NODE_IS_FOLDER | MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN);
	(void)mw_tree_container_add_node(&tree_data.tree_container,
			fold3_handle,
			"file6",
			0U);
	(void)mw_tree_container_add_node(&tree_data.tree_container,
			fold3_handle,
			"file7",
			0U);
	(void)mw_tree_container_add_node(&tree_data.tree_container,
			fold2_handle,
			"file4",
			0U);
	(void)mw_tree_container_add_node(&tree_data.tree_container,
			fold2_handle,
			"file5",
			0U);

	mw_paint_all();
}
