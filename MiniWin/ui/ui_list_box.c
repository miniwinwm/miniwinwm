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

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void list_box_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void list_box_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void list_box_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	uint8_t i;
	mw_ui_list_box_data_t *this_list_box = (mw_ui_list_box_data_t*)mw_get_control_instance_data(control_handle);
	uint16_t row_height;
	uint16_t icon_x_offset;
	uint16_t text_x_offset;

	if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		row_height = MW_UI_LIST_BOX_LARGE_ROW_HEIGHT;
		icon_x_offset = MW_UI_LIST_BOX_LARGE_LABEL_X_OFFSET - 4;
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		row_height = MW_UI_LIST_BOX_ROW_HEIGHT;
		icon_x_offset = MW_UI_LIST_BOX_LABEL_X_OFFSET;
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

	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info, 1, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, 1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info, mw_get_control_rect(control_handle).width - 2, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, mw_get_control_rect(control_handle).height - 2);

    /* set up text */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	
	for(i = 0; i < this_list_box->number_of_lines; i++)
	{
		/* draw feint separator between items */
		mw_gl_set_fg_colour(MW_CONTROL_SEPARATOR_COLOUR);
		mw_gl_set_line(MW_GL_DOT_LINE);

		if (i > 0)
		{
			mw_gl_hline(draw_info,
				2,
				mw_get_control_rect(control_handle).width - 4,
				row_height * i);
		}

		if (i >= this_list_box->number_of_items)
		{
			continue;
		}

	    /* if this item is selected draw the background in control down colour */
		if(this_list_box->line_is_selected && (this_list_box->selection - this_list_box->lines_to_scroll) == i)
		{
			mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
			mw_gl_set_border(MW_GL_BORDER_OFF);
			mw_gl_rectangle(draw_info,
					2,
					row_height * i + 1,
					mw_get_control_rect(control_handle).width - 4,
					row_height - 2);
			mw_gl_set_line(MW_GL_SOLID_LINE);
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
			mw_gl_vline(draw_info,
					1,
					row_height * i + 1,
					row_height * (i + 1) - 1);
			mw_gl_hline(draw_info,
					1,
					mw_get_control_rect(control_handle).width - 2,
					row_height * i + 1);
			mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
			mw_gl_vline(draw_info,
					mw_get_control_rect(control_handle).width - 3,
					row_height * i + 1,
					row_height * i + row_height - 1);
			mw_gl_hline(draw_info,
					1,
					mw_get_control_rect(control_handle).width - 3,
					row_height * (i + 1) - 1);
		}

		/* set up text colour on enabled state - from control and individual items bitfield */
		if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED &&
	    		mw_util_get_bit(this_list_box->line_enables, i))
		{
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		}
		else
		{
			mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		}

		/* draw the item label text and icon */
		if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
		{
			/* large text and icon */
			/* check if there is an icon on this row */
			if (this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].icon != NULL)
			{
				/* there's an icon so update text offset */
				text_x_offset = MW_UI_LIST_BOX_LARGE_LABEL_X_OFFSET + MW_UI_LIST_BOX_LARGE_ICON_SIZE;

				/* draw icon */
				mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
				if(this_list_box->line_is_selected && (this_list_box->selection - this_list_box->lines_to_scroll) == i)
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset + 2,
							row_height * i + MW_UI_LIST_BOX_LARGE_LABEL_Y_OFFSET,
							MW_UI_LIST_BOX_LARGE_ICON_SIZE,
							MW_UI_LIST_BOX_LARGE_ICON_SIZE,
							this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].icon);
				}
				else
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset,
							row_height * i + MW_UI_LIST_BOX_LARGE_LABEL_Y_OFFSET - 2,
							MW_UI_LIST_BOX_LARGE_ICON_SIZE,
							MW_UI_LIST_BOX_LARGE_ICON_SIZE,
							this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].icon);
				}
			}
			else
			{
				/* there's not an icon */
				text_x_offset = MW_UI_LIST_BOX_LARGE_LABEL_X_OFFSET;
			}

			if(this_list_box->line_is_selected && (this_list_box->selection - this_list_box->lines_to_scroll) == i)
			{
				mw_gl_string(draw_info,
						text_x_offset + 2,
						row_height * i + MW_UI_LIST_BOX_LARGE_LABEL_Y_OFFSET + 2,
						this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].label);
			}
			else
			{
				mw_gl_string(draw_info,
						text_x_offset,
						row_height * i + MW_UI_LIST_BOX_LARGE_LABEL_Y_OFFSET,
						this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].label);
			}
		}
		else
		{
			/* small text and icon */
			/* check if there is an icon on this row */
			if (this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].icon != NULL)
			{
				/* there's an icon so update text offset */
				text_x_offset = MW_UI_LIST_BOX_LABEL_X_OFFSET * 2 + MW_UI_LIST_BOX_ICON_SIZE;

				/* draw icon */
				mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
				if(this_list_box->line_is_selected && (this_list_box->selection - this_list_box->lines_to_scroll) == i)
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset + 1,
							row_height * i + MW_UI_LIST_BOX_LABEL_Y_OFFSET,
							MW_UI_LIST_BOX_ICON_SIZE,
							MW_UI_LIST_BOX_ICON_SIZE,
							this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].icon);				}
				else
				{
					mw_gl_monochrome_bitmap(draw_info,
							icon_x_offset,
							row_height * i + MW_UI_LIST_BOX_LABEL_Y_OFFSET - 1,
							MW_UI_LIST_BOX_ICON_SIZE,
							MW_UI_LIST_BOX_ICON_SIZE,
							this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].icon);
				}
			}
			else
			{
				/* there's not an icon */
				text_x_offset = MW_UI_LIST_BOX_LABEL_X_OFFSET;
			}

			if(this_list_box->line_is_selected && (this_list_box->selection - this_list_box->lines_to_scroll) == i)
			{
				mw_gl_string(draw_info,
						text_x_offset + 1,
						row_height * i + MW_UI_LIST_BOX_LABEL_Y_OFFSET + 1,
						this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].label);
			}
			else
			{
				mw_gl_string(draw_info,
						text_x_offset,
						row_height * i + MW_UI_LIST_BOX_LABEL_Y_OFFSET,
						this_list_box->list_box_entries[i + this_list_box->lines_to_scroll].label);
			}
		}
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void list_box_message_function(const mw_message_t *message)
{
	uint16_t touch_y;
	mw_ui_list_box_data_t *this_list_box = (mw_ui_list_box_data_t*)mw_get_control_instance_data(message->recipient_handle);
	uint16_t row_height;

	MW_ASSERT(message, "Null pointer argument");

	if (mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		row_height = MW_UI_LIST_BOX_LARGE_ROW_HEIGHT;
	}
	else
	{
		row_height = MW_UI_LIST_BOX_ROW_HEIGHT;
	}

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_list_box->line_is_selected = false;
		this_list_box->lines_to_scroll = 0;

		/* send message about whether scrolling is needed */
		mw_post_message(MW_LIST_BOX_SCROLLING_REQUIRED_MESSAGE,
				message->recipient_handle,
				mw_get_control_parent_window_handle(message->recipient_handle),
				this_list_box->number_of_items > this_list_box->number_of_lines,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);
		break;

	case MW_LIST_BOX_SCROLL_BAR_POSITION_MESSAGE:
		/* check if scrolling is appropriate */
		if (this_list_box->number_of_items <= this_list_box->number_of_lines)
		{
			/* no, so set scroll lines to zero */
			this_list_box->lines_to_scroll = 0;
		}
		else
		{
			/* yes so recalculate vertical scroll lines from last scroll bar position recorded */
			this_list_box->lines_to_scroll = (message->message_data *
					(this_list_box->number_of_items - this_list_box->number_of_lines)) /
					UINT8_MAX;
		}
		break;

	case MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE:
		/* check if scrolling is appropriate */
		if (this_list_box->number_of_items <= this_list_box->number_of_lines)
		{
			/* no, so set scroll lines to zero */
			this_list_box->lines_to_scroll = 0;
		}
		else
		{
			/* yes so set new scroll position */
			this_list_box->lines_to_scroll = message->message_data;

			/* check that the new scroll position doesn't exceed maximum possible */
			if (this_list_box->lines_to_scroll > (this_list_box->number_of_items - this_list_box->number_of_lines))
			{
				this_list_box->lines_to_scroll = this_list_box->number_of_items - this_list_box->number_of_lines;
			}
		}
		break;

	case MW_LIST_BOX_SET_ENTRIES_MESSAGE:
		if (message->message_pointer && message->message_data > 0)
		{
			this_list_box->number_of_items = message->message_data;
			this_list_box->list_box_entries = (mw_ui_list_box_entry *)message->message_pointer;

			/* send message about whether scrolling is needed */
			mw_post_message(MW_LIST_BOX_SCROLLING_REQUIRED_MESSAGE,
					message->recipient_handle,
					mw_get_control_parent_window_handle(message->recipient_handle),
					this_list_box->number_of_items > this_list_box->number_of_lines,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_WINDOW_MESSAGE);
		}
		else
		{
			MW_ASSERT(message->message_data > 0, "Illegal number of list box entries");
			MW_ASSERT(message->message_pointer, "Null pointer");
		}
		break;

	case MW_TIMER_MESSAGE:
		/* set line pressed to false, send the control response message and repaint the control */		
		this_list_box->line_is_selected = false;
		mw_post_message(MW_LIST_BOX_ITEM_PRESSED_MESSAGE,
				message->recipient_handle,
				mw_get_control_parent_window_handle(message->recipient_handle),
				this_list_box->selection,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);
		mw_paint_control(message->recipient_handle);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */		
		touch_y = message->message_data;
		
		/* check if the control is enabled and this particular line is enabled and
		 * there's an entry on this line */
		if ((mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED) &&
				mw_util_get_bit(this_list_box->line_enables, touch_y / row_height) &&
				(touch_y / row_height) < this_list_box->number_of_items)
		{
			this_list_box->line_is_selected = true;
			this_list_box->selection = touch_y / row_height + this_list_box->lines_to_scroll;
			mw_paint_control(message->recipient_handle);
			mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
		}
		break;

		default:
			break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_list_box_add_new(uint16_t x,
		uint16_t y,
		uint16_t width,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_list_box_data_t *list_box_instance_data)
{
	mw_util_rect_t r;
	uint8_t i;

	/* check for null parameters */
	if (list_box_instance_data == NULL ||
			list_box_instance_data->list_box_entries == NULL)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_INVALID_HANDLE;
	}

	/* check for 0 entries */
	if (list_box_instance_data->number_of_items == 0 ||
			list_box_instance_data->number_of_lines == 0)
	{
		MW_ASSERT(false, "Zero argument");
		return MW_INVALID_HANDLE;
	}

	/* check for null pointers in entry text */
	for (i = 0; i < list_box_instance_data->number_of_items; i++)
	{
		if (list_box_instance_data->list_box_entries[i].label == NULL)
		{
			MW_ASSERT(false, "Null pointer value in array");
			return MW_INVALID_HANDLE;
		}
	}

	if (list_box_instance_data == NULL)
	{
		return MW_INVALID_HANDLE;
	}

	if (flags & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		/* check for a sensible width */
		if (width < MW_UI_LIST_BOX_LARGE_MIN_WIDTH)
		{
			return MW_INVALID_HANDLE;
		}

		mw_util_set_rect(&r,
				x,
				y,
				width,
				MW_UI_LIST_BOX_LARGE_ROW_HEIGHT * list_box_instance_data->number_of_lines);
	}
	else
	{
		/* check for a sensible width */
		if (width < MW_UI_LIST_BOX_MIN_WIDTH)
		{
			return MW_INVALID_HANDLE;
		}

		mw_util_set_rect(&r,
				x,
				y,
				width,
				MW_UI_LIST_BOX_ROW_HEIGHT * list_box_instance_data->number_of_lines);
	}

	return mw_add_control(&r,
			parent_handle,
			list_box_paint_function,
			list_box_message_function,
			flags,
			list_box_instance_data,
			MW_UI_CONTROL_LIST_BOX_TYPE);
}

uint8_t mw_ui_list_box_get_max_lines_to_scroll(mw_handle_t list_box_handle)
{
	mw_ui_control_type_t control_type = mw_get_control_type(list_box_handle);

	/* check handle is not invalid or of wrong type*/
	if (control_type != MW_UI_CONTROL_LIST_BOX_TYPE)
	{
		MW_ASSERT(false, "Bad handle");
		return 0;
	}

	mw_ui_list_box_data_t *this_list_box = (mw_ui_list_box_data_t*)mw_get_control_instance_data(list_box_handle);
	if (this_list_box == NULL)
	{
		MW_ASSERT(false, "Handle doesn't reference a control");
		return 0;
	}

	if (this_list_box->number_of_items <= this_list_box->number_of_lines)
	{
		return 0;
	}

	return this_list_box->number_of_items - this_list_box->number_of_lines;
}
