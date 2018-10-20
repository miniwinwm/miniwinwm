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
#include "ui/ui_common.h"

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

void mw_ui_radio_button_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	uint8_t i;
	mw_ui_radio_button_data_t *this_radio_radio_button = (mw_ui_radio_button_data_t*)mw_get_control_instance_data(control_ref);
	uint16_t height;
	uint16_t box_size;

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_clear_pattern();
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	/* set size dependent values */
	if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		height = MW_UI_RADIO_BUTTON_LARGE_HEIGHT;
		box_size = MW_UI_RADIO_BUTTON_LARGE_BOX_SIZE;
		mw_gl_set_font(MW_GL_TITLE_FONT);
	}
	else
	{
		height = MW_UI_RADIO_BUTTON_HEIGHT;
		box_size = MW_UI_RADIO_BUTTON_BOX_SIZE;
		mw_gl_set_font(MW_GL_FONT_9);
	}

	for (i = 0; i < this_radio_radio_button->number_of_items; i++)
	{
        /* set the box outline and text colour depending on enabled state */
		if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAG_IS_ENABLED)
		{
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		}
		else
		{
			mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		}

		/* check size this control is being drawn at and draw appropriate text*/
		if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAGS_LARGE_SIZE)
		{
			/* draw the label text */
			mw_gl_string(draw_info,
					MW_UI_RADIO_BUTTON_LARGE_LABEL_X_OFFSET,
					MW_UI_RADIO_BUTTON_LARGE_LABEL_Y_OFFSET + i * MW_UI_RADIO_BUTTON_LARGE_HEIGHT,
					this_radio_radio_button->radio_button_labels[i]);
		}
		else
		{
			/* draw the label text */
			mw_gl_string(draw_info,
					MW_UI_RADIO_BUTTON_LABEL_X_OFFSET,
					MW_UI_RADIO_BUTTON_LABEL_Y_OFFSET + i * MW_UI_RADIO_BUTTON_HEIGHT,
					this_radio_radio_button->radio_button_labels[i]);
		}

        /* draw the empty box */
		mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
		mw_gl_rectangle(draw_info,
				0,
				i * height,
				box_size,
				box_size);

		/* draw 3d effect */
		mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
		mw_gl_vline(draw_info,
				1,
				1 + i * height,
				i * height + box_size - 2);
		mw_gl_hline(draw_info,
				1,
				box_size - 2,
				1 + i * height);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
		mw_gl_vline(draw_info,
				box_size - 2,
				1 + i * height,
				 i * height + box_size - 2);
		mw_gl_hline(draw_info,
				1,
				box_size - 2,
				i * height + box_size - 2);
        
        /* check if this radio_button is selected */
		if (i == this_radio_radio_button->selected_radio_button)
		{
            /* it is so set the box fill colour according to enabled state */
			if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAG_IS_ENABLED)
			{
				mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLACK);
			}
			else
			{
				mw_gl_set_solid_fill_colour(MW_CONTROL_DISABLED_COLOUR);
			}
            
            /* draw the fill box */
			mw_gl_rectangle(draw_info,
					3,
					i * height + 3,
					box_size - 6,
					box_size - 6);
		}
	}
}

void mw_ui_radio_button_message_function(const mw_message_t *message)
{
	mw_ui_radio_button_data_t *this_radio_radio_button = (mw_ui_radio_button_data_t*)mw_get_control_instance_data(message->recipient_id);
	uint16_t height;

	MW_ASSERT(message, "Null pointer argument");

	/* set size dependent values */
	if (mw_get_control_flags(message->recipient_id) & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		height = MW_UI_RADIO_BUTTON_LARGE_HEIGHT;
	}
	else
	{
		height = MW_UI_RADIO_BUTTON_HEIGHT;
	}

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */				
		this_radio_radio_button->selected_radio_button = 0;
		break;
		
	case MW_TRANSFER_DATA_1_MESSAGE:
		/* handle a transfer data message, which contains new position */
		if (message->message_data < this_radio_radio_button->number_of_items)
		{
			this_radio_radio_button->selected_radio_button  = message->message_data;
		}
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */		
		if (mw_get_control_flags(message->recipient_id) & MW_CONTROL_FLAG_IS_ENABLED)
		{
			/* find which button was touched */
			this_radio_radio_button->selected_radio_button = (message->message_data & 0xffff) / height;
			
			/* send control response message */
			mw_post_message(MW_RADIO_BUTTON_ITEM_SELECTED_MESSAGE,
					message->recipient_id,
					mw_get_control_parent_window(message->recipient_id),
					this_radio_radio_button->selected_radio_button,
					MW_WINDOW_MESSAGE);
			mw_paint_control(message->recipient_id);
		}
		break;

	default:
		break;
	}
}

uint8_t mw_ui_radio_button_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_radio_button_data_t *radio_button_instance_data)
{
	mw_util_rect_t r;

	if (radio_button_instance_data == NULL)
	{
		return MW_MAX_CONTROL_COUNT;
	}

	if (flags & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, MW_UI_RADIO_BUTTON_LARGE_WIDTH, MW_UI_RADIO_BUTTON_LARGE_HEIGHT * radio_button_instance_data->number_of_items);
	}
	else
	{
		mw_util_set_rect(&r, x, y, MW_UI_RADIO_BUTTON_WIDTH, MW_UI_RADIO_BUTTON_HEIGHT * radio_button_instance_data->number_of_items);
	}

	return mw_add_control(&r,
			parent,
			mw_ui_radio_button_paint_function,
			mw_ui_radio_button_message_function,
			flags,
			radio_button_instance_data);
}
