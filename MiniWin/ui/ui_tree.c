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
 * Extra data structure passed to found child/sub-child node callback when finding all child/sub-child
 * nodes of a folder
 */
typedef struct
{
	mw_ui_tree_data_t *this_tree;			/**< Pointer to tree control's instance data */
	const mw_gl_draw_info_t *draw_info;		/**< Structure used for drawing via gl */
	int16_t next_line;						/**< The line in the control where to draw this node's label */
	int16_t control_width;					/**< Width of the tree control */
	bool large_size;						/**< true if the control is large size, false if standard size */
} tree_callback_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void tree_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void tree_message_function(const mw_message_t *message);
static bool node_callback(struct mw_tree_container_t *tree, mw_handle_t node_handle, void *callback_data);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Pointer type to callback function called from library to user code when finding all descendants of a folder node
 *
 * @param tree Pointer to tree structure
 * @param node_handle The handle of the next found node
 * @param callback_data Generic pointer to extra data that needs passing to callback function
 * @return Return true to continue searching or false to quit searching
 */
static bool node_callback(struct mw_tree_container_t *tree, mw_handle_t node_handle, void *callback_data)
{
	tree_callback_data_t *tree_callback_data = (tree_callback_data_t *)callback_data;
	uint8_t node_flags;
	uint16_t node_level;
	int16_t label_icon_offset;

	if (node_handle == MW_INVALID_HANDLE)
	{
		return (false);
	}

	node_flags = mw_tree_container_get_node_flags(tree, node_handle);
	node_level = mw_tree_container_get_node_level(tree, node_handle);

	/* draw background of selected node */
	if ((node_flags & MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG) == MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG)
	{
		mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
		mw_gl_rectangle(tree_callback_data->draw_info,
				1,
				(tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
				tree_callback_data->control_width - 2,
				tree_callback_data->this_tree->row_height);
	}

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_colour(MW_HAL_LCD_WHITE);

	if ((node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
	{
		if ((node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
		{
			if (tree_callback_data->large_size == true)
			{
				mw_gl_monochrome_bitmap(tree_callback_data->draw_info,
						tree_callback_data->this_tree->row_left_border + MW_UI_TREE_LEFT_BORDER + (int16_t)node_level * ((int16_t)tree_callback_data->this_tree->icon_size + 2),
						tree_callback_data->this_tree->row_top_border + (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
						tree_callback_data->this_tree->icon_size,
						tree_callback_data->this_tree->icon_size,
						mw_bitmaps_folder_close_icon_large);
			}
			else
			{
				mw_gl_monochrome_bitmap(tree_callback_data->draw_info,
						tree_callback_data->this_tree->row_left_border + MW_UI_TREE_LEFT_BORDER + (int16_t)node_level * ((int16_t)tree_callback_data->this_tree->icon_size + 2),
						tree_callback_data->this_tree->row_top_border + (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
						tree_callback_data->this_tree->icon_size,
						tree_callback_data->this_tree->icon_size,
						mw_bitmaps_folder_close_icon_small);
			}
		}
		else
		{
			if (tree_callback_data->large_size == true)
			{
				mw_gl_monochrome_bitmap(tree_callback_data->draw_info,
						tree_callback_data->this_tree->row_left_border + MW_UI_TREE_LEFT_BORDER + (int16_t)node_level * ((int16_t)tree_callback_data->this_tree->icon_size + 2),
						tree_callback_data->this_tree->row_top_border + (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
						tree_callback_data->this_tree->icon_size,
						tree_callback_data->this_tree->icon_size,
						mw_bitmaps_folder_open_icon_large);
			}
			else
			{
				mw_gl_monochrome_bitmap(tree_callback_data->draw_info,
						tree_callback_data->this_tree->row_left_border + MW_UI_TREE_LEFT_BORDER + (int16_t)node_level * ((int16_t)tree_callback_data->this_tree->icon_size + 2),
						tree_callback_data->this_tree->row_top_border + (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
						tree_callback_data->this_tree->icon_size,
						tree_callback_data->this_tree->icon_size,
						mw_bitmaps_folder_open_icon_small);
			}
		}
	}

	/* draw file/folder icons if required */
	label_icon_offset = 0;
	if ((node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
	{
		if (tree_callback_data->this_tree->folder_icon != NULL)
		{
			mw_gl_monochrome_bitmap(tree_callback_data->draw_info,
					tree_callback_data->this_tree->row_left_border + MW_UI_TREE_LEFT_BORDER + ((int16_t)node_level + 1) * ((int16_t)tree_callback_data->this_tree->icon_size + 2),
					tree_callback_data->this_tree->row_top_border + (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
					tree_callback_data->this_tree->icon_size,
					tree_callback_data->this_tree->icon_size,
					tree_callback_data->this_tree->folder_icon);
			label_icon_offset = (int16_t)tree_callback_data->this_tree->icon_size + 2;
		}
	}
	else
	{
		if (tree_callback_data->this_tree->file_icon != NULL)
		{
			mw_gl_monochrome_bitmap(tree_callback_data->draw_info,
					tree_callback_data->this_tree->row_left_border + MW_UI_TREE_LEFT_BORDER + ((int16_t)node_level + 1) * ((int16_t)tree_callback_data->this_tree->icon_size + 2),
					tree_callback_data->this_tree->row_top_border + (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
					tree_callback_data->this_tree->icon_size,
					tree_callback_data->this_tree->icon_size,
					tree_callback_data->this_tree->file_icon);
			label_icon_offset = (int16_t)tree_callback_data->this_tree->icon_size + 2;
		}
	}

	mw_gl_string(tree_callback_data->draw_info,
			tree_callback_data->this_tree->row_left_border + MW_UI_TREE_LEFT_BORDER + label_icon_offset + ((int16_t)node_level + 1) * ((int16_t)tree_callback_data->this_tree->icon_size + 2),
			tree_callback_data->this_tree->row_top_border + (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
			mw_tree_container_get_node_label(tree, node_handle));

	tree_callback_data->next_line++;

	/* check if reached bottom of control allowing search of nodes to be aborted */
	if (tree_callback_data->next_line - (int16_t)tree_callback_data->this_tree->lines_to_scroll > (int16_t)tree_callback_data->this_tree->number_of_lines)
	{
		return (false);
	}

	return (true);
}

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void tree_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	tree_callback_data_t tree_callback_data;
	tree_callback_data.this_tree = (mw_ui_tree_data_t*)mw_get_control_instance_data(control_handle);

	MW_ASSERT(draw_info != (void*)0, "Null pointer argument");

	tree_callback_data.draw_info = draw_info;
	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		tree_callback_data.large_size = true;
	}
	else
	{
		tree_callback_data.large_size = false;
	}
	tree_callback_data.control_width = mw_get_control_rect(control_handle).width;

	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
	}

    /* draw the background rectangle */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_control_rect(control_handle).width,
			mw_get_control_rect(control_handle).height);

    /* set up text */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	tree_callback_data.next_line = 0;
	(void)node_callback(&tree_callback_data.this_tree->tree_container,
			tree_callback_data.this_tree->root_handle,
			&tree_callback_data);

	tree_callback_data.next_line = 1;
	(void)mw_tree_container_get_all_children(&tree_callback_data.this_tree->tree_container,
			tree_callback_data.this_tree->root_handle,
			node_callback,
			(void *)&tree_callback_data);
}

void mw_ui_tree_data_changed(mw_handle_t changed_tree_handle)
{
	if (changed_tree_handle == MW_INVALID_HANDLE)
	{
		MW_ASSERT((bool)false, "Invalid handle");

		return;
	}

	mw_ui_tree_data_t *tree = (mw_ui_tree_data_t*)mw_get_control_instance_data(changed_tree_handle);

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Invalid handle");

		return;
	}

	uint32_t message_data;

	/* get number of visible children of root folder */
	tree->visible_children = mw_tree_container_get_open_children_count(&tree->tree_container, tree->root_handle);

	/* add root folder to count */
	tree->visible_children++;

	/* send message to parent window about whether scrolling is needed */
	message_data = 0U;
	if (tree->visible_children > tree->number_of_lines)
	{
		message_data = 0x010000;
		message_data |= ((uint32_t)tree->visible_children - (uint32_t)tree->number_of_lines);
	}

	mw_post_message(MW_TREE_SCROLLING_REQUIRED_MESSAGE,
			MW_INVALID_HANDLE,
			mw_get_control_parent_window_handle(changed_tree_handle),
			message_data,
			NULL,
			MW_WINDOW_MESSAGE);
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void tree_message_function(const mw_message_t *message)
{
	mw_ui_tree_data_t *this_tree = (mw_ui_tree_data_t*)mw_get_control_instance_data(message->recipient_handle);
	uint32_t message_data;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		{
			if ((mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
			{
				this_tree->icon_size = MW_UI_TREE_LARGE_ICON_SIZE;
				this_tree->row_height = MW_UI_TREE_LARGE_ROW_HEIGHT;
				this_tree->row_left_border = MW_UI_TREE_LARGE_LEFT_BORDER;
				this_tree->row_top_border = MW_UI_TREE_LARGE_TOP_BORDER;
			}
			else
			{
				this_tree->icon_size = MW_UI_TREE_ICON_SIZE;
				this_tree->row_height = MW_UI_TREE_ROW_HEIGHT;
				this_tree->row_left_border = MW_UI_TREE_LEFT_BORDER;
				this_tree->row_top_border = MW_UI_TREE_TOP_BORDER;
			}

			/* initialise selected line invalid rect */
			this_tree->invalid_rect.height = this_tree->row_height;
			this_tree->invalid_rect.x = 1;

			/* get number of visible children of root folder */
			this_tree->visible_children = mw_tree_container_get_open_children_count(&this_tree->tree_container, this_tree->root_handle);

			/* add root folder to count */
			this_tree->visible_children++;

			/* initialise the control */
			this_tree->lines_to_scroll = 0U;

			/* send message about whether scrolling is needed */
			message_data = 0U;
			if (this_tree->visible_children > this_tree->number_of_lines)
			{
				message_data = 0x010000;
				message_data |= ((uint32_t)this_tree->visible_children - (uint32_t)this_tree->number_of_lines);
			}

			mw_post_message(MW_TREE_SCROLLING_REQUIRED_MESSAGE,
					message->recipient_handle,
					mw_get_control_parent_window_handle(message->recipient_handle),
					message_data,
					NULL,
					MW_WINDOW_MESSAGE);
		}
		break;

	case MW_TREE_SCROLL_BAR_POSITION_MESSAGE:
		{
			uint32_t intermediate_uint32;

			/* check if scrolling is appropriate */
			if (this_tree->visible_children <= this_tree->number_of_lines)
			{
				/* no, so set scroll lines to zero */
				intermediate_uint32 = 0U;
			}
			else
			{
				/* yes so recalculate vertical scroll lines from last scroll bar position recorded */
				  intermediate_uint32 = (message->message_data *
						((uint32_t)this_tree->visible_children - (uint32_t)this_tree->number_of_lines)) /
						(uint32_t)UINT8_MAX;
			}

			if (this_tree->lines_to_scroll != (uint8_t)intermediate_uint32)
			{
				this_tree->lines_to_scroll = (uint8_t)intermediate_uint32;
				mw_post_message(MW_SCROLLED_CONTROL_NEEDS_PAINTING_HINT_MESSAGE,
						message->recipient_handle,
						mw_get_control_parent_window_handle(message->recipient_handle),
						MW_UNUSED_MESSAGE_PARAMETER,
						NULL,
						MW_WINDOW_MESSAGE);
			}
		}
		break;

	case MW_TREE_LINES_TO_SCROLL_MESSAGE:
		{
			/* check if scrolling is appropriate */
			if (this_tree->visible_children <= this_tree->number_of_lines)
			{
				/* no, so set scroll lines to zero */
				this_tree->lines_to_scroll = 0U;
			}
			else
			{
				/* yes so set new scroll position */
				this_tree->lines_to_scroll = (uint8_t)message->message_data;

				/* check that the new scroll position doesn't exceed maximum possible */
				if (this_tree->lines_to_scroll > (this_tree->visible_children - this_tree->number_of_lines))
				{
					this_tree->lines_to_scroll = this_tree->visible_children - (uint16_t)this_tree->number_of_lines;
				}
			}
		}
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		{
			int16_t touch_x;
			int16_t touch_y;
			mw_handle_t selected_node_handle;
			uint8_t node_flags;
			uint16_t node_level;
			int16_t line_number;
			uint32_t intermediate_uint32;

			/* handle a touch down event within this control */
			intermediate_uint32 = message->message_data >> 16;
			touch_x = (int16_t)intermediate_uint32;
			touch_y = (int16_t)message->message_data;
			line_number = touch_y / this_tree->row_height + (int16_t)this_tree->lines_to_scroll;

			/* check if the control is enabled */
			if ((mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
			{
				/* control is enabled, get selected node handle from y poisition */
				selected_node_handle = mw_tree_container_get_handle_from_visible_position(&this_tree->tree_container,
						this_tree->root_handle,
						(uint16_t)line_number);

				/* check for valid handle, an empty line returns an invalid handle */
				if (selected_node_handle != MW_INVALID_HANDLE)
				{
					/* get details of selected node */
					node_flags = mw_tree_container_get_node_flags(&this_tree->tree_container, selected_node_handle);
					node_level = mw_tree_container_get_node_level(&this_tree->tree_container, selected_node_handle);

					/* check for selection on a folder >/V area */
					if ((node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG &&
							touch_x < ((int16_t)(node_level) + 1) * ((int16_t)this_tree->icon_size + 2))
					{
						/* selected folder >/V area */
						if ((node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
						{
							mw_tree_container_change_folder_node_open_state(&this_tree->tree_container, selected_node_handle, false);

							/* let parent window know that a folder has been closed */
							mw_post_message(MW_TREE_FOLDER_CLOSED_MESSAGE,
									message->recipient_handle,
									mw_get_control_parent_window_handle(message->recipient_handle),
									selected_node_handle,
									NULL,
									MW_WINDOW_MESSAGE);
						}
						else
						{
							mw_tree_container_change_folder_node_open_state(&this_tree->tree_container, selected_node_handle, true);

							/* let parent window know that a folder has been opened */
							mw_post_message(MW_TREE_FOLDER_OPENED_MESSAGE,
									message->recipient_handle,
									mw_get_control_parent_window_handle(message->recipient_handle),
									selected_node_handle,
									NULL,
									MW_WINDOW_MESSAGE);
						}

						/* update number of visible children of root folder */
						this_tree->visible_children = mw_tree_container_get_open_children_count(&this_tree->tree_container, this_tree->root_handle);

						/* add root folder to count */
						this_tree->visible_children++;

						/* send message about whether scrolling is needed */
						message_data = 0U;
						if (this_tree->visible_children > this_tree->number_of_lines)
						{
							message_data = 0x010000;
							message_data |= ((uint32_t)this_tree->visible_children - (uint32_t)this_tree->number_of_lines);
						}

						mw_post_message(MW_TREE_SCROLLING_REQUIRED_MESSAGE,
								message->recipient_handle,
								mw_get_control_parent_window_handle(message->recipient_handle),
								message_data,
								NULL,
								MW_WINDOW_MESSAGE);

						/* repaint whole control */
						mw_paint_control(message->recipient_handle);
					}
					else
					{
						/* not selected folder >/V area */
						if ((node_flags & MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG) == MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG)
						{
							/* mark node chosen as selected */
							mw_tree_container_change_node_selected_state(&this_tree->tree_container, selected_node_handle, false);

							/* post node selected message */
							mw_post_message(MW_TREE_NODE_DESELECTED_MESSAGE,
									message->recipient_handle,
									mw_get_control_parent_window_handle(message->recipient_handle),
									(uint32_t)selected_node_handle,
									NULL,
									MW_WINDOW_MESSAGE);
						}
						else
						{
							/* mark node chosen as deselected */
							mw_tree_container_change_node_selected_state(&this_tree->tree_container, selected_node_handle, true);

							/* post node selected message */
							mw_post_message(MW_TREE_NODE_SELECTED_MESSAGE,
									message->recipient_handle,
									mw_get_control_parent_window_handle(message->recipient_handle),
									(uint32_t)selected_node_handle,
									NULL,
									MW_WINDOW_MESSAGE);
						}

						/* repaint only selected/deselected line */
						this_tree->invalid_rect.y = (touch_y / this_tree->row_height) * this_tree->row_height;
						this_tree->invalid_rect.width = mw_get_control_rect(message->recipient_handle).width - 2,
						mw_paint_control_rect(message->recipient_handle, &this_tree->invalid_rect);
					}
				}
			}
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_tree_add_new(int16_t x,
		int16_t y,
		int16_t width,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_tree_data_t *tree_instance_data)
{
	mw_util_rect_t r;

	/* check for null parameters */
	if (tree_instance_data == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (MW_INVALID_HANDLE);
	}

	if (tree_instance_data->tree_container.nodes_array_size < 1U ||
			tree_instance_data->tree_container.node_count < 1U ||
			tree_instance_data->tree_container.nodes_array[0].label == NULL ||
			tree_instance_data->tree_container.nodes_array[0].handle == MW_INVALID_HANDLE)
	{
		MW_ASSERT((bool)false, "Bad tree container");
		return (MW_INVALID_HANDLE);
	}

	if ((flags & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		/* check for a sensible width */
		if (width < MW_UI_TREE_LARGE_MIN_WIDTH)
		{
			return (MW_INVALID_HANDLE);
		}

		mw_util_set_rect(&r,
				x,
				y,
				width,
				MW_UI_TREE_LARGE_ROW_HEIGHT * (int16_t)tree_instance_data->number_of_lines);
	}
	else
	{
		/* check for a sensible width */
		if (width < MW_UI_TREE_MIN_WIDTH)
		{
			return (MW_INVALID_HANDLE);
		}

		mw_util_set_rect(&r,
				x,
				y,
				width,
				MW_UI_TREE_ROW_HEIGHT * (int16_t)tree_instance_data->number_of_lines);
	}

	return (mw_add_control(&r,
			parent_handle,
			tree_paint_function,
			tree_message_function,
			flags,
			tree_instance_data));
}
