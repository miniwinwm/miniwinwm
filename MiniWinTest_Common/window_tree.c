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
#include "miniwin_user.h"
#include "window_tree.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Window data structure 
 */
typedef struct 
{
	uint16_t lines_to_scroll;				/**< The number of lines to scroll */
	uint16_t max_scrollable_lines;			/**< Maximum number of lines that can be scrolled */
} window_tree_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_tree_data_t window_tree_data;
static char node_path[MW_UI_LABEL_MAX_CHARS];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_tree_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
    MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

    /* fill window's client area */
    mw_gl_set_fill(MW_GL_FILL);
    mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
    mw_gl_set_border(MW_GL_BORDER_OFF);
    mw_gl_clear_pattern();
    mw_gl_rectangle(draw_info,
        0, 0,
        mw_get_window_client_rect(window_handle).width,
        mw_get_window_client_rect(window_handle).height);
}

void window_tree_message_function(const mw_message_t *message)
{
	uint32_t intermediate_uint32;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_tree_data.lines_to_scroll = 0U;
		break;

	case MW_TREE_SCROLLING_REQUIRED_MESSAGE:
		intermediate_uint32 = message->message_data & 0xffffU;
		window_tree_data.max_scrollable_lines = (uint16_t)intermediate_uint32;

		intermediate_uint32 = message->message_data >> 16;
		if ((bool)intermediate_uint32 == false ||
				((bool)intermediate_uint32 == true && window_tree_data.max_scrollable_lines <= window_tree_data.lines_to_scroll))
		{
			mw_set_control_enabled(arrow_3_handle, false);
		}
		else
		{
			mw_set_control_enabled(arrow_3_handle, true);
		}
		mw_paint_control(arrow_3_handle);
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_UP && window_tree_data.lines_to_scroll > 0U)
		{
			/* up arrow, scroll list box up is ok to do so */
			window_tree_data.lines_to_scroll--;

			if (window_tree_data.lines_to_scroll == 0U)
			{
				mw_set_control_enabled(arrow_2_handle, false);
				mw_paint_control(arrow_2_handle);
			}

			if (window_tree_data.lines_to_scroll < window_tree_data.max_scrollable_lines)
			{
				mw_set_control_enabled(arrow_3_handle, true);
				mw_paint_control(arrow_3_handle);
			}

			if (window_tree_data.lines_to_scroll > window_tree_data.max_scrollable_lines)
			{
				window_tree_data.lines_to_scroll = window_tree_data.max_scrollable_lines;
			}

			mw_post_message(MW_TREE_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					tree_handle,
					window_tree_data.lines_to_scroll,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(tree_handle);
		}
		else if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_DOWN &&
				window_tree_data.lines_to_scroll < window_tree_data.max_scrollable_lines)
		{
			/* down arrow, scroll list box down is ok to do so */
			window_tree_data.lines_to_scroll++;

			if (window_tree_data.lines_to_scroll == window_tree_data.max_scrollable_lines)
			{
				mw_set_control_enabled(arrow_3_handle, false);
				mw_paint_control(arrow_3_handle);
			}

			mw_set_control_enabled(arrow_2_handle, true);
			mw_paint_control(arrow_2_handle);

			mw_post_message(MW_TREE_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					tree_handle,
					window_tree_data.lines_to_scroll,
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
			mw_tree_container_get_node_path(&sender_tree->tree_container, (mw_handle_t)message->message_data, node_path, MW_UI_LABEL_MAX_CHARS);
			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_7_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)node_path,
					MW_CONTROL_MESSAGE);

			mw_paint_control(label_7_handle);
		}
		break;

	case MW_TREE_FOLDER_OPENED_MESSAGE:
	case MW_TREE_FOLDER_CLOSED_MESSAGE:
		mw_ui_tree_data_changed(tree_handle);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
