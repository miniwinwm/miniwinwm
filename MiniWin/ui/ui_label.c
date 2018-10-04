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
#include <miniwin_utilities.h>
#include "ui/ui_label.h"

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

void mw_ui_label_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_label_data_t *this_label = (mw_ui_label_data_t*)mw_get_control_instance_data(control_ref);

    /* draw the background */
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_clear_pattern();
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_control_rect(control_ref).width,
			mw_get_control_rect(control_ref).height);

    /* set label text colour according to enabled state */
	if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAG_IS_ENABLED)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	}
    
    /* draw the label text */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);    
	if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		mw_gl_large_string(draw_info, MW_UI_LABEL_LARGE_X_OFFSET, 1, this_label->label);
	}
	else
	{
		mw_gl_string(draw_info, MW_UI_LABEL_LARGE_X_OFFSET, 1, this_label->label);
	}
}

void mw_ui_label_message_function(const mw_message_t *message)
{
	mw_ui_label_data_t *this_label = (mw_ui_label_data_t*)mw_get_control_instance_data(message->recipient_id);

	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_TRANSFER_DATA_1_PTR_MESSAGE:
		/* handle a transfer data pointer message, which contains new label text */
		if (message->message_data)
		{
			mw_util_safe_strcpy(this_label->label, MW_UI_LABEL_MAX_CHARS, (char *)message->message_data);
		}
		else
		{
			MW_ASSERT(false);
		}
		break;

	default:
		break;
	}
}

uint8_t mw_ui_label_add_new(uint16_t x,
		uint16_t y,
		uint16_t width,
		uint8_t parent,
		uint32_t flags,
		mw_ui_label_data_t *label_instance_data)
{
	mw_util_rect_t r;

	if (flags & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, width, MW_UI_LABEL_LARGE_HEIGHT);
	}
	else
	{
		mw_util_set_rect(&r, x, y, width, MW_UI_LABEL_HEIGHT);
	}

	return mw_add_control(&r,
			parent,
			mw_ui_label_paint_function,
			mw_ui_label_message_function,
			flags,
			label_instance_data);
}
