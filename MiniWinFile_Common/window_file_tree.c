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
	uint16_t lines_to_scroll;				/**< The number of lines to scroll */
	uint16_t max_scrollable_lines;			/**< Maximum number of lines that can be scrolled */
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
	uint32_t temp_uint32;

	MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_file_tree_data.lines_to_scroll = 0U;
		break;

	case MW_TREE_SCROLLING_REQUIRED_MESSAGE:
		/* enable/disable the down arrow depending on if scrolling is required, i.e. tree won't all fit in the control */
		if (message->message_data >> 16 == 0U)
		{
			mw_set_control_enabled(arrow_down_handle, false);
			window_file_tree_data.max_scrollable_lines = 0U;
			window_file_tree_data.lines_to_scroll = 0U;
		}
		else
		{
			temp_uint32 = message->message_data & 0xffffU;
			window_file_tree_data.max_scrollable_lines = (uint16_t)temp_uint32;
			if (window_file_tree_data.lines_to_scroll >= window_file_tree_data.max_scrollable_lines)
			{
				window_file_tree_data.lines_to_scroll = window_file_tree_data.max_scrollable_lines;
				mw_set_control_enabled(arrow_down_handle, false);
			}
			else
			{
				mw_set_control_enabled(arrow_down_handle, true);
			}
		}
		mw_paint_control(arrow_down_handle);
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_UP &&
				window_file_tree_data.lines_to_scroll > 0U)
		{
			/* up arrow, scroll text up is ok to do so */
			if (window_file_tree_data.lines_to_scroll > 0U)
			{
				window_file_tree_data.lines_to_scroll--;
			}

			if (window_file_tree_data.lines_to_scroll == 0U)
			{
				mw_set_control_enabled(arrow_up_handle, false);
				mw_paint_control(arrow_up_handle);
			}

			mw_set_control_enabled(arrow_down_handle, true);
			mw_paint_control(arrow_down_handle);

			mw_post_message(MW_TREE_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					tree_handle,
					window_file_tree_data.lines_to_scroll,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(tree_handle);
		}
		else if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_DOWN &&
				window_file_tree_data.lines_to_scroll < window_file_tree_data.max_scrollable_lines)
		{
			/* down arrow, scroll text down as it's ok to do so */
			window_file_tree_data.lines_to_scroll++;

			if (window_file_tree_data.lines_to_scroll == window_file_tree_data.max_scrollable_lines)
			{
				mw_set_control_enabled(arrow_down_handle, false);
				mw_paint_control(arrow_down_handle);
			}

			mw_set_control_enabled(arrow_up_handle, true);
			mw_paint_control(arrow_up_handle);

			mw_post_message(MW_TREE_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					tree_handle,
					window_file_tree_data.lines_to_scroll,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(tree_handle);
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_TREE_NODE_SELECTED_MESSAGE:
		{
			mw_ui_tree_data_t *sender_tree = (mw_ui_tree_data_t*)mw_get_control_instance_data(message->sender_handle);
			mw_tree_container_get_node_path(&sender_tree->tree_container, message->message_data, node_path, 100);
			//todo do something with this
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
