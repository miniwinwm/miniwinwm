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

#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Window instance data structure
 */
typedef struct
{
	mw_handle_t tree_handle;	/**< Handle of the tree ui component plotting selected nodes for */
	int16_t next_line;			/**< The next row position to drawe text at */
} window_selection_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_selection_data_t window_selection_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static bool node_callback(struct mw_tree_container_t *tree, mw_handle_t node_handle, void *callback_data);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Callback function called from library to user code when finding all descendants of a folder node
 *
 * @param tree Pointer to tree structure
 * @param node_handle The handle of the next found node
 * @param callback_data Generic pointer to extra data that needs passing to callback function
 * @return Return true to continue searching or false to quit searching
 */
static bool node_callback(struct mw_tree_container_t *tree, mw_handle_t node_handle, void *callback_data)
{
	mw_gl_draw_info_t *draw_info = (mw_gl_draw_info_t *)callback_data;

	mw_gl_string(draw_info,
			2,
			window_selection_data.next_line * 10,
			mw_tree_container_get_node_label(tree, node_handle));

	window_selection_data.next_line++;

	return true;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_selection_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_tree_data_t *tree_instance_data;
	struct mw_tree_container_t *tree_container;

	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	if (window_selection_data.tree_handle != MW_INVALID_HANDLE)
	{
		tree_instance_data = (mw_ui_tree_data_t *)mw_get_control_instance_data(window_selection_data.tree_handle);
		if (tree_instance_data != NULL)
		{
			tree_container = &tree_instance_data->tree_container;
			if (tree_container != NULL)
			{
				mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
				mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
				mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
				mw_gl_set_font(MW_GL_FONT_9);
				window_selection_data.next_line = 0;

				/* add the root folder if it's selected */
				if ((mw_tree_container_get_node_flags(tree_container, tree_instance_data->root_handle) & MW_TREE_CONTAINER_NODE_IS_SELECTED) == MW_TREE_CONTAINER_NODE_IS_SELECTED)
				{
					node_callback(tree_container, tree_instance_data->root_handle, (void *)draw_info);
				}

				/* add all root folder children selecting selected nodes only */
				mw_tree_container_get_all_children(tree_container,
						tree_instance_data->root_handle,
						true,
						node_callback,
						(void *)draw_info);
			}
		}
	}
}

void window_selection_message_function(const mw_message_t *message)
{
	MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_selection_data.tree_handle = MW_INVALID_HANDLE;
		break;

	case MW_USER_1_MESSAGE:
		window_selection_data.tree_handle = (mw_handle_t)message->message_data;
		mw_set_window_visible(message->recipient_handle, true);
		mw_bring_window_to_front(message->recipient_handle);
		(void)mw_set_timer(mw_tick_counter + 100U, message->recipient_handle, message->message_recipient_type);
		mw_paint_all();
		break;

	case MW_TIMER_MESSAGE:
		mw_set_window_visible(message->recipient_handle, false);
		mw_paint_all();
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
