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

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef struct
{
	mw_ui_tree_data_t *this_tree;
	int16_t next_line;
	const mw_gl_draw_info_t *draw_info;
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

/**********************
*** LOCAL FUNCTIONS ***
**********************/

bool node_callback(mw_tree_container_t *tree, mw_handle_t node_handle, void *callback_data)
{
	tree_callback_data_t *tree_callback_data = (tree_callback_data_t *)callback_data;
	uint8_t node_flags;
	uint16_t node_level;
	char c;

	if (node_handle == MW_INVALID_HANDLE)
	{
		return false;
	}

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);

	node_flags = mw_tree_container_get_node_flags(tree, node_handle);
	node_level = mw_tree_container_get_node_level(tree, node_handle);

	if ((node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
	{
		if ((node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
		{
			c='-';
		}
		else
		{
			c='+';
		}

		mw_gl_character(tree_callback_data->draw_info,
				node_level * 10,
				(tree_callback_data->next_line - tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
				c);
	}

	if ((node_flags & MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG) == MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_RED);
	}

	mw_gl_string(tree_callback_data->draw_info,
			10 + node_level * 10,
			(tree_callback_data->next_line - tree_callback_data->this_tree->lines_to_scroll) * tree_callback_data->this_tree->row_height,
			mw_tree_container_get_node_label(tree, node_handle));

	tree_callback_data->next_line++;

	return true;
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
		mw_gl_set_font(MW_GL_TITLE_FONT);
		tree_callback_data.this_tree->row_height = MW_UI_TREE_LARGE_ROW_HEIGHT;
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		tree_callback_data.this_tree->row_height = MW_UI_TREE_ROW_HEIGHT;
	}

    /* draw the background rectangle */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
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
	node_callback(&tree_callback_data.this_tree->tree_container,
			tree_callback_data.this_tree->root_handle,
			&tree_callback_data);

	tree_callback_data.next_line = 1;
	(void)mw_tree_container_get_all_children(&tree_callback_data.this_tree->tree_container,
			tree_callback_data.this_tree->root_handle,
			node_callback,
			(void *)&tree_callback_data);

#if 0
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info, 1, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, 1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info, mw_get_control_rect(control_handle).width - 2, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, mw_get_control_rect(control_handle).height - 2);

    /* set up text */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	
	for (i = 0U; i < this_tree->number_of_lines; i++)
	{
		/* draw feint separator between items */
		mw_gl_set_fg_colour(MW_CONTROL_SEPARATOR_COLOUR);
		mw_gl_set_line(MW_GL_DOT_LINE);

		if (i > 0U)
		{
			mw_gl_hline(draw_info,
				2,
				mw_get_control_rect(control_handle).width - 4,
				row_height * (int16_t)i);
		}

		if (i >= this_tree->number_of_items)
		{
			continue;
		}

	    /* if this item is selected draw the background in control down colour */
		if (this_tree->line_is_selected && (this_tree->selection - this_tree->lines_to_scroll) == i)
		{
			mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
			mw_gl_set_border(MW_GL_BORDER_OFF);
			mw_gl_rectangle(draw_info,
					2,
					row_height * (int16_t)i + 1,
					mw_get_control_rect(control_handle).width - 4,
					row_height - 2);
			mw_gl_set_line(MW_GL_SOLID_LINE);
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
			mw_gl_vline(draw_info,
					1,
					row_height * (int16_t)i + 1,
					row_height * ((int16_t)i + 1) - 1);
			mw_gl_hline(draw_info,
					1,
					mw_get_control_rect(control_handle).width - 2,
					row_height * (int16_t)i + 1);
			mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
			mw_gl_vline(draw_info,
					mw_get_control_rect(control_handle).width - 3,
					row_height * (int16_t)i + 1,
					row_height * (int16_t)i + row_height - 1);
			mw_gl_hline(draw_info,
					1,
					mw_get_control_rect(control_handle).width - 3,
					row_height * ((int16_t)i + 1) - 1);
		}

		/* set up text colour on enabled state - from control and individual items bitfield */
		intermediate_bool = (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED;
		if (mw_util_get_bit(this_tree->line_enables, i) && intermediate_bool)
		{
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		}
		else
		{
			mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		}

		/* draw the item label text and icon */
		if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
		{
			/* large text and icon */
			/* check if there is an icon on this row */
			if (this_tree->tree_entries[i + this_tree->lines_to_scroll].icon != NULL)
			{
				/* there's an icon so update text offset */
				text_x_offset = (int16_t)MW_UI_TREE_LARGE_LABEL_X_OFFSET + (int16_t)MW_UI_TREE_LARGE_ICON_SIZE;

				/* draw icon */
				mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
				if(this_tree->line_is_selected && (this_tree->selection - this_tree->lines_to_scroll) == i)
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset + 2,
							row_height * (int16_t)i + MW_UI_TREE_LARGE_LABEL_Y_OFFSET,
							MW_UI_TREE_LARGE_ICON_SIZE,
							MW_UI_TREE_LARGE_ICON_SIZE,
							this_tree->tree_entries[i + this_tree->lines_to_scroll].icon);
				}
				else
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset,
							row_height * (int16_t)i + MW_UI_TREE_LARGE_LABEL_Y_OFFSET - 2,
							MW_UI_TREE_LARGE_ICON_SIZE,
							MW_UI_TREE_LARGE_ICON_SIZE,
							this_tree->tree_entries[i + this_tree->lines_to_scroll].icon);
				}
			}
			else
			{
				/* there's not an icon */
				text_x_offset = MW_UI_TREE_LARGE_LABEL_X_OFFSET;
			}

			if(this_tree->line_is_selected && (this_tree->selection - this_tree->lines_to_scroll) == i)
			{
				mw_gl_string(draw_info,
						text_x_offset + 2,
						row_height * (int16_t)i + MW_UI_TREE_LARGE_LABEL_Y_OFFSET + 2,
						this_tree->tree_entries[i + this_tree->lines_to_scroll].label);
			}
			else
			{
				mw_gl_string(draw_info,
						text_x_offset,
						row_height * (int16_t)i + MW_UI_TREE_LARGE_LABEL_Y_OFFSET,
						this_tree->tree_entries[i + this_tree->lines_to_scroll].label);
			}
		}
		else
		{
			/* small text and icon */
			/* check if there is an icon on this row */
			if (this_tree->tree_entries[i + this_tree->lines_to_scroll].icon != NULL)
			{
				/* there's an icon so update text offset */
				text_x_offset = (int16_t)MW_UI_TREE_LABEL_X_OFFSET * (int16_t)2 + (int16_t)MW_UI_TREE_ICON_SIZE;

				/* draw icon */
				mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
				if(this_tree->line_is_selected && (this_tree->selection - this_tree->lines_to_scroll) == i)
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset + 1,
							row_height * (int16_t)i + MW_UI_TREE_LABEL_Y_OFFSET,
							MW_UI_TREE_ICON_SIZE,
							MW_UI_TREE_ICON_SIZE,
							this_tree->tree_entries[i + this_tree->lines_to_scroll].icon);				}
				else
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset,
							row_height * (int16_t)i + MW_UI_TREE_LABEL_Y_OFFSET - 1,
							MW_UI_TREE_ICON_SIZE,
							MW_UI_TREE_ICON_SIZE,
							this_tree->tree_entries[i + this_tree->lines_to_scroll].icon);
				}
			}
			else
			{
				/* there's not an icon */
				text_x_offset = MW_UI_TREE_LABEL_X_OFFSET;
			}

			if(this_tree->line_is_selected && (this_tree->selection - this_tree->lines_to_scroll) == i)
			{
				mw_gl_string(draw_info,
						text_x_offset + 1,
						row_height * (int16_t)i + MW_UI_TREE_LABEL_Y_OFFSET + 1,
						this_tree->tree_entries[i + this_tree->lines_to_scroll].label);
			}
			else
			{
				mw_gl_string(draw_info,
						text_x_offset,
						row_height * (int16_t)i + MW_UI_TREE_LABEL_Y_OFFSET,
						this_tree->tree_entries[i + this_tree->lines_to_scroll].label);
			}
		}
	}
#endif
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void tree_message_function(const mw_message_t *message)
{
	mw_ui_tree_data_t *this_tree = (mw_ui_tree_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		{
			uint32_t message_data = 0U;

			/* get number of visible children of root folder */
			(void)mw_tree_container_get_open_children_count(&this_tree->tree_container, this_tree->root_handle, &this_tree->visible_children);

			/* add root folder to count */
			this_tree->visible_children++;

			/* initialise the control */
			this_tree->lines_to_scroll = 0U;

			/* send message about whether scrolling is needed */
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

#if 0
	case MW_TREE_SCROLL_BAR_POSITION_MESSAGE:
		/* check if scrolling is appropriate */
		if (this_tree->number_of_items <= this_tree->number_of_lines)
		{
			/* no, so set scroll lines to zero */
			this_tree->lines_to_scroll = 0U;
		}
		else
		{
			/* yes so recalculate vertical scroll lines from last scroll bar position recorded */
			  intermediate_uint32 = (message->message_data *
					((uint32_t)this_tree->number_of_items - (uint32_t)this_tree->number_of_lines)) /
					(uint32_t)UINT8_MAX;
			  this_tree->lines_to_scroll = (uint8_t)intermediate_uint32;

		}
		break;
#endif

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
					this_tree->lines_to_scroll = this_tree->visible_children - this_tree->number_of_lines;
				}
			}
		}
		break;

#if 0
	case MW_TREE_SET_ENTRIES_MESSAGE:
		{
			uint32_t message_data = 0U;

			if (message->message_pointer != NULL)
			{
				this_tree->number_of_items = (uint8_t)message->message_data;
				this_tree->tree_entries = (mw_ui_tree_entry *)message->message_pointer;
				this_tree->lines_to_scroll = 0U;

				/* send message about whether scrolling is needed */
				if (this_tree->number_of_items > this_tree->number_of_lines)
				{
					message_data = 0x010000;
					message_data |= ((uint32_t)this_tree->number_of_items - (uint32_t)this_tree->number_of_lines);
				}
				mw_post_message(MW_TREE_SCROLLING_REQUIRED_MESSAGE,
						message->recipient_handle,
						mw_get_control_parent_window_handle(message->recipient_handle),
						message_data,
						NULL,
						MW_WINDOW_MESSAGE);
			}
			else
			{
				MW_ASSERT((bool)false, "Null pointer");
			}
		}
		break;
#endif

	case MW_TOUCH_DOWN_MESSAGE:
		{
			int16_t touch_x;
			int16_t touch_y;
			mw_handle_t selected_node_handle;
			uint8_t node_flags;
			uint16_t node_level;
			int16_t line_number;

			/* handle a touch down event within this control */
			touch_x = (int16_t)(message->message_data >> 16);
			touch_y = (int16_t)message->message_data;
			line_number = touch_y / this_tree->row_height + this_tree->lines_to_scroll;

			/* check if the control is enabled and there's an entry on this line */ // todo 2nd bit of this comment
			if ((mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
			{
				selected_node_handle = mw_tree_container_get_handle_from_visible_position(&this_tree->tree_container,
						this_tree->root_handle,
						line_number);

				if (selected_node_handle != MW_INVALID_HANDLE)
				{
					node_flags = mw_tree_container_get_node_flags(&this_tree->tree_container, selected_node_handle);
					node_level = mw_tree_container_get_node_level(&this_tree->tree_container, selected_node_handle);

					/* check for selection on a folder +/- area */
					if ((node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG &&
							touch_x < node_level * 10)
					{
						/* selected folder +/- area */
						if ((node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
						{
							mw_tree_container_change_folder_node_open_state(&this_tree->tree_container, selected_node_handle, false);

						}
						else
						{
							mw_tree_container_change_folder_node_open_state(&this_tree->tree_container, selected_node_handle, true);
						}
					}
					else
					{
						/* not selected folder +/- area */
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
					}

					mw_paint_control(message->recipient_handle);
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
//	uint8_t i;

	/* check for null parameters */
	if (tree_instance_data == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (MW_INVALID_HANDLE);
	}
#if 0
	/* check for null pointers in entry text */
	for (i = 0U; i < tree_instance_data->number_of_items; i++)
	{
		if (tree_instance_data->tree_entries[i].label == NULL)
		{
			MW_ASSERT((bool)false, "Null pointer value in array");
			return (MW_INVALID_HANDLE);
		}
	}
#endif
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