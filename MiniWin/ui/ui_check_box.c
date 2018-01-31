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
#include "ui/ui_check_box.h"

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

void mw_ui_check_box_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_check_box_data_t *this_check_box = (mw_ui_check_box_data_t*)mw_all_controls[control_ref].extra_data;

    /* set the box outline, text and X colour depending on enabled state */   
    if (mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_ENABLED)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	}
    
    /* draw the box */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_clear_pattern();
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_rectangle(draw_info, 0, 0, MW_UI_CHECK_BOX_HEIGHT, MW_UI_CHECK_BOX_HEIGHT);
    
    /* draw the X if needed */
	if (this_check_box->checked)
	{
		mw_gl_line(draw_info, 1, 1, MW_UI_CHECK_BOX_HEIGHT - 2, MW_UI_CHECK_BOX_HEIGHT - 2);
		mw_gl_line(draw_info, MW_UI_CHECK_BOX_HEIGHT - 2, 1, 1, MW_UI_CHECK_BOX_HEIGHT - 2);
	}
    
    /* draw the label text */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_string(draw_info,
			MW_UI_CHECK_BOX_LABEL_X_OFFSET,
			MW_UI_CHECK_BOX_LABEL_Y_OFFSET,
			this_check_box->label);
}

void mw_ui_check_box_message_function(const mw_message_t *message)
{
	mw_ui_check_box_data_t *this_check_box = (mw_ui_check_box_data_t*)mw_all_controls[message->recipient_id].extra_data;

	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */		
		this_check_box->checked = false;
		break;
		
	case MW_TRANSFER_DATA_1_MESSAGE:
		/* handle a transfer data message, which contains new number */
		this_check_box->checked = message->message_data & 0x01;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */		
		if (mw_all_controls[message->recipient_id].control_flags & MW_CONTROL_FLAG_IS_ENABLED)
		{
			this_check_box->checked = !this_check_box->checked;
			mw_paint_control(message->recipient_id);
			mw_post_message(MW_CHECKBOX_STATE_CHANGE_MESSAGE,
					message->recipient_id,
					mw_all_controls[message->recipient_id].parent,
					this_check_box->checked,
					MW_WINDOW_MESSAGE);
		}
		break;

		default:
			break;
	}
}

uint8_t mw_ui_check_box_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_check_box_data_t *check_box_instance_data)
{
	mw_util_rect_t r;

	mw_util_set_rect(&r, x, y, MW_UI_CHECK_BOX_WIDTH, MW_UI_CHECK_BOX_HEIGHT);

	return mw_add_control(&r,
			parent,
			mw_ui_check_box_paint_function,
			mw_ui_check_box_message_function,
			flags,
			check_box_instance_data);
}
