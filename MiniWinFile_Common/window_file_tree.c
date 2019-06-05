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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "app.h"
#include "window_file_tree.h"

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
	char dummy;			/**< Stop empty struct compiler warning */
} window_file_tree_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_file_tree_data_t window_file_tree_data;
static char node_path[100];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_file_tree_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
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
}

void window_file_tree_message_function(const mw_message_t *message)
{
	mw_ui_tree_data_t *sender_tree_data;

	(void)window_file_tree_data;

	MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		break;

	case MW_TREE_SCROLLING_REQUIRED_MESSAGE:
		{
			if (message->message_data >> 16 == 0U)
			{
				mw_set_control_enabled(scroll_bar_vert_handle, false);
			}
			else
			{
				mw_set_control_enabled(scroll_bar_vert_handle, true);
			}
			mw_paint_control(scroll_bar_vert_handle);
		}
		break;

	case MW_SCROLL_BAR_SET_SCROLL_MESSAGE:
		mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
				MW_UNUSED_MESSAGE_PARAMETER,
				scroll_bar_vert_handle,
				message->message_data,
				NULL,
				MW_CONTROL_MESSAGE);
		mw_paint_control(scroll_bar_vert_handle);
		break;

	case MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		mw_post_message(MW_TREE_SCROLL_BAR_POSITION_MESSAGE,
				MW_UNUSED_MESSAGE_PARAMETER,
				tree_handle,
				message->message_data,
				NULL,
				MW_CONTROL_MESSAGE);
		/* do not repaint tree control here on every message otherwise there will be too many repaints,
		 * instead wait until the tree gives us a hint that a repaint is required */
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		mw_post_message(MW_USER_1_MESSAGE,
				message->recipient_handle,
				window_selection_handle,
				tree_handle,
				NULL,
				MW_WINDOW_MESSAGE);
		break;

	case MW_TREE_NODE_SELECTED_MESSAGE:
		/* get full path of selected node and display it in a label */
		sender_tree_data = (mw_ui_tree_data_t*)mw_get_control_instance_data(message->sender_handle);
		mw_tree_container_get_node_path(&sender_tree_data->tree_container, message->message_data, node_path, 100);
		mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
				message->recipient_handle,
				label_path_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				node_path,
				MW_CONTROL_MESSAGE);
		mw_paint_control(label_path_handle);
		break;

	case MW_TREE_FOLDER_OPENED_MESSAGE:
		sender_tree_data = (mw_ui_tree_data_t*)mw_get_control_instance_data(message->sender_handle);
		app_populate_tree_from_file_system(&sender_tree_data->tree_container, (mw_handle_t)message->message_data);

		mw_post_message(MW_TREE_TREE_CONTAINER_DATA_CHANGED,
				message->recipient_handle,
				tree_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				NULL,
				MW_CONTROL_MESSAGE);
		break;

	case MW_TREE_FOLDER_CLOSED_MESSAGE:
		sender_tree_data = (mw_ui_tree_data_t*)mw_get_control_instance_data(message->sender_handle);
		mw_tree_container_remove_node_children(&sender_tree_data->tree_container, (mw_handle_t)message->message_data);

		mw_post_message(MW_TREE_TREE_CONTAINER_DATA_CHANGED,
				message->recipient_handle,
				tree_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				NULL,
				MW_CONTROL_MESSAGE);
		break;

	case MW_SCROLLED_CONTROL_NEEDS_PAINTING_HINT_MESSAGE:
		mw_paint_control(message->sender_handle);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
