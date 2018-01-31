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
#include "ui/ui_list_box.h"

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

extern mw_control_t mw_all_controls[MW_MAX_CONTROL_COUNT];
extern volatile uint32_t mw_tick_counter;

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

void mw_ui_list_box_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	uint8_t i;
	mw_ui_list_box_data_t *this_list_box = (mw_ui_list_box_data_t*)mw_all_controls[control_ref].extra_data;

    /* draw the background rectangle */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_all_controls[control_ref].control_rect.width,
			mw_all_controls[control_ref].control_rect.height);

    /* set up text transparency */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	
	for(i = 0; i < this_list_box->number_of_lines; i++)
	{
	    /* if this item is selected draw the background in control down colour */
		if(this_list_box->line_is_selected && this_list_box->selection == i)
		{
			mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
			mw_gl_rectangle(draw_info,
					0,
					MW_UI_LIST_BOX_ROW_HEIGHT * i,
					mw_all_controls[control_ref].control_rect.width,
					MW_UI_LIST_BOX_ROW_HEIGHT);
		}

		/* set up text colour on enabled state - from control and individual items bitfield */
		if (mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_ENABLED &&
	    		mw_util_get_bit(this_list_box->line_enables, i))
		{
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		}
		else
		{
			mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		}

		/* draw the item label text */
		mw_gl_string(draw_info,
				MW_GL_STANDARD_CHARACTER_WIDTH,
				MW_UI_LIST_BOX_ROW_HEIGHT * i + MW_UI_LIST_BOX_LABEL_Y_OFFSET,
				this_list_box->list_box_labels[i]);

		/* draw feint separator between items */
		mw_gl_set_fg_colour(MW_CONTROL_SEPARATOR_COLOUR);
		mw_gl_set_line(MW_GL_DOT_LINE);
		mw_gl_hline(draw_info,
				0,
				mw_all_controls[control_ref].control_rect.width,
				MW_UI_LIST_BOX_ROW_HEIGHT * i);
	}
}

void mw_ui_list_box_message_function(const mw_message_t *message)
{
	uint16_t touch_y;
	mw_ui_list_box_data_t *this_list_box = (mw_ui_list_box_data_t*)mw_all_controls[message->recipient_id].extra_data;

	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_list_box->line_is_selected = false;
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		/* set line pressed to false, send the control response message and repaint the control */		
		this_list_box->line_is_selected = false;
		mw_post_message(MW_LIST_BOX_ITEM_PRESSED_MESSAGE,
				message->recipient_id,
				mw_all_controls[message->recipient_id].parent,
				this_list_box->selection,
				MW_WINDOW_MESSAGE);
		mw_paint_control(message->recipient_id);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */		
		touch_y = message->message_data;
		
		/* check if the control is enabled and this particular line is enabled */
		if ((mw_all_controls[message->recipient_id].control_flags & MW_CONTROL_FLAG_IS_ENABLED) &&
				mw_util_get_bit(this_list_box->line_enables, touch_y / MW_UI_LIST_BOX_ROW_HEIGHT))
		{
			this_list_box->line_is_selected = true;
			this_list_box->selection = touch_y / MW_UI_LIST_BOX_ROW_HEIGHT;
			mw_paint_control(message->recipient_id);
			mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_id, MW_CONTROL_MESSAGE);
		}
		break;

		default:
			break;
	}
}

uint8_t mw_ui_list_box_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_list_box_data_t *list_box_instance_data)
{
	mw_util_rect_t r;

	if (list_box_instance_data == NULL)
	{
		return MW_MAX_CONTROL_COUNT;
	}

	mw_util_set_rect(&r, x, y, MW_UI_LIST_BOX_WIDTH, MW_UI_LIST_BOX_ROW_HEIGHT * list_box_instance_data->number_of_lines);

	return mw_add_control(&r,
			parent,
			mw_ui_list_box_paint_function,
			mw_ui_list_box_message_function,
			flags,
			list_box_instance_data);
}
