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
#include "window_file.h"
#include "window_file_tree.h"

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
mw_handle_t window_file_handle;
mw_handle_t window_file_tree_handle;

/* controls */
mw_handle_t button_open_handle;
mw_handle_t button_set_clock_handle;
mw_handle_t button_create_handle;
mw_handle_t label_time_handle;
mw_handle_t label_date_handle;
mw_handle_t tree_handle;
mw_handle_t arrow_up_handle;
mw_handle_t arrow_down_handle;
mw_handle_t label_path_handle;

/**********************
*** LOCAL VARIABLES ***
**********************/

/* controls instance data */
static mw_ui_button_data_t button_open_data;
static mw_ui_button_data_t button_set_clock_data;
static mw_ui_button_data_t button_create_data;
static mw_ui_label_data_t label_time_data;
static mw_ui_label_data_t label_date_data;
static mw_ui_tree_data_t tree_data;
static mw_ui_arrow_data_t arrow_up_data;
static mw_ui_arrow_data_t arrow_down_data;
//static mw_tree_container_node_t nodes_array[20];  //todo
mw_tree_container_node_t *nodes_array;
static mw_ui_label_data_t label_path_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/
/**
 * Request from tree container to expand the node storage array
 *
 * @param tree Pointer to tree structure
 * @note From the tree container structure parameter get the existing size of the node array.
 *       Calculate the new expanded size from this. Reallocate the node array storage of this
 *       new size using the tree container structure parameter to get the pointer to the existing
 *       node array storage. If the reallocate succeeds set the new storage and its size using the
 *       tree container structure parameter.
 */
static void expand_node_array(mw_tree_container_t *tree);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void expand_node_array(mw_tree_container_t *tree)
{
	uint16_t new_node_array_size = mw_tree_container_get_node_array_size(tree) + 5U;
	void *new_node_array = realloc(mw_tree_container_get_node_array(tree), new_node_array_size * sizeof(mw_tree_container_node_t));

	if (new_node_array == NULL)
	{
		/* realloc failed */
		return;
	}

	/* realloc success so set new array and size, contents copied automatically */
	mw_tree_container_set_new_node_array(tree, (mw_tree_container_node_t *)new_node_array, new_node_array_size);
}

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

	mw_util_set_rect(&r, 5, 5, 230, 188);
	window_file_tree_handle = mw_add_window(&r,
			"File Tree Demo",
			window_file_tree_paint_function,
			window_file_tree_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	nodes_array=(mw_tree_container_node_t *)malloc(sizeof(mw_tree_container_node_t) * 12);	//todo
	tree_data.number_of_lines = 8U;
//	tree_data.file_icon = mw_bitmaps_file_icon_small;
//	tree_data.folder_icon = mw_bitmaps_folder_icon_small;
	tree_data.file_icon = mw_bitmaps_file_icon_large;
	tree_data.folder_icon = mw_bitmaps_folder_icon_large;
	tree_data.root_handle = mw_tree_container_init(&tree_data.tree_container,
			nodes_array,
			12,
			"0:",
			MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG,
			0U,
			expand_node_array);
	tree_handle = mw_ui_tree_add_new(5,
			5,
			125,
			window_file_tree_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
			&tree_data);

	arrow_up_data.mw_ui_arrow_direction = MW_UI_ARROW_UP;
	arrow_up_handle = mw_ui_arrow_add_new(130,
			5,
			window_file_tree_handle,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&arrow_up_data);

	arrow_down_data.mw_ui_arrow_direction = MW_UI_ARROW_DOWN;
	arrow_down_handle = mw_ui_arrow_add_new(130,
			101,
			window_file_tree_handle,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&arrow_down_data);

	(void)mw_util_safe_strcpy(label_path_data.label,
			MW_UI_LABEL_MAX_CHARS,
			"Not set");
	label_path_handle = mw_ui_label_add_new(5,
			140,
			220,
			window_file_tree_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_path_data);

	mw_util_set_rect(&r, 15, 70, 162, 128);
	window_file_handle = mw_add_window(&r,
			"File Demo",
			window_file_paint_function,
			window_file_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_IS_VISIBLE,
			NULL);

	(void)mw_util_safe_strcpy(button_open_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Open");
	button_open_handle = mw_ui_button_add_new(20,
			75,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_open_data);

	(void)mw_util_safe_strcpy(button_set_clock_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Set");
	button_set_clock_handle = mw_ui_button_add_new(95,
			25,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_set_clock_data);

	(void)mw_util_safe_strcpy(button_create_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Create");
	button_create_handle = mw_ui_button_add_new(90,
			75,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&button_create_data);

	(void)mw_util_safe_strcpy(label_time_data.label,
			MW_UI_LABEL_MAX_CHARS,
			"Waiting...");
	label_time_handle = mw_ui_label_add_new(10,
			20,
			70,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_time_data);

	(void)mw_util_safe_strcpy(label_date_data.label,
			MW_UI_LABEL_MAX_CHARS,
			"Waiting...");
	label_date_handle = mw_ui_label_add_new(10,
			35,
			70,
			window_file_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&label_date_data);





	//todo
	mw_tree_container_add_node(&tree_data.tree_container,
			tree_data.root_handle,
			"file1",
			0U);
	mw_handle_t fold1_handle = mw_tree_container_add_node(&tree_data.tree_container,
			tree_data.root_handle,
			"Foldy1",
			MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG | MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG);
	mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"file2",
			0U);
	mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"file3",
			0U);
	mw_handle_t fold2_handle = mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"fold2",
			MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG | MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG);
	mw_handle_t fold3_handle = mw_tree_container_add_node(&tree_data.tree_container,
			fold1_handle,
			"fold3",
			MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG | MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG);
	mw_tree_container_add_node(&tree_data.tree_container,
			fold3_handle,
			"file6",
			0U);
	mw_tree_container_add_node(&tree_data.tree_container,
			fold3_handle,
			"file7",
			0U);
	mw_tree_container_add_node(&tree_data.tree_container,
			fold2_handle,
			"file4",
			0U);
	mw_tree_container_add_node(&tree_data.tree_container,
			fold2_handle,
			"file5",
			0U);


	mw_paint_all();
}

void tree_container_add_file_to_folder(mw_handle_t parent_folder, char *filename)
{
	mw_tree_container_add_node(&tree_data.tree_container,
			parent_folder,
			filename,
			0U);
}
