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

extern const uint8_t mw_bitmaps_tick[];
extern const uint8_t mw_bitmaps_tick_large[];

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void check_box_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void check_box_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void check_box_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	uint16_t height;
	mw_ui_check_box_data_t *this_check_box = (mw_ui_check_box_data_t*)mw_get_control_instance_data(control_handle);

    /* set the box outline, text and X colour depending on enabled state */   
    if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	}

	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

    if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
    {
    	height = MW_UI_CHECK_BOX_LARGE_HEIGHT;

    	/* draw the label text */
		mw_gl_set_font(MW_GL_TITLE_FONT);
    	mw_gl_string(draw_info,
    			MW_UI_CHECK_BOX_LARGE_LABEL_X_OFFSET,
    			MW_UI_CHECK_BOX_LARGE_LABEL_Y_OFFSET,
    			this_check_box->label);
    }
    else
    {
    	height = MW_UI_CHECK_BOX_HEIGHT;

    	/* draw the label text */
		mw_gl_set_font(MW_GL_FONT_9);
    	mw_gl_string(draw_info,
    			MW_UI_CHECK_BOX_LABEL_X_OFFSET,
    			MW_UI_CHECK_BOX_LABEL_Y_OFFSET,
    			this_check_box->label);
    }

    /* draw the box */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_clear_pattern();
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_rectangle(draw_info, 0, 0, height, height);

	/* draw 3d effect */
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info, 1, 1, height - 2);
	mw_gl_hline(draw_info, 1, height - 2, 1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info, height - 2, 1, height - 2);
	mw_gl_hline(draw_info, 1, height - 2, height - 2);

    /* draw the tick if needed */
	if (this_check_box->checked)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

	    if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
	    {
	    	mw_gl_monochrome_bitmap(draw_info, 2, 2, 24, 24, mw_bitmaps_tick_large);
	    }
	    else
	    {
	    	mw_gl_monochrome_bitmap(draw_info, 1, 1, 12, 12, mw_bitmaps_tick);
	    }
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void check_box_message_function(const mw_message_t *message)
{
	mw_ui_check_box_data_t *this_check_box = (mw_ui_check_box_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */		
		this_check_box->checked = false;
		break;
		
	case MW_CHECK_BOX_SET_CHECKED_STATE_MESSAGE:
		/* handle a transfer data message, which contains new number */
		this_check_box->checked = message->message_data & 0x01;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */		
		if (mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED)
		{
			this_check_box->checked = !this_check_box->checked;
			mw_paint_control(message->recipient_handle);
			mw_post_message(MW_CHECKBOX_STATE_CHANGE_MESSAGE,
					message->recipient_handle,
					mw_get_control_parent_window_handle(message->recipient_handle),
					this_check_box->checked,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_WINDOW_MESSAGE);
		}
		break;

		default:
			break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_check_box_add_new(uint16_t x,
		uint16_t y,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_check_box_data_t *check_box_instance_data)
{
	mw_util_rect_t r;

	if (flags & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, MW_UI_CHECK_BOX_LARGE_WIDTH, MW_UI_CHECK_BOX_LARGE_HEIGHT);
	}
	else
	{
		mw_util_set_rect(&r, x, y, MW_UI_CHECK_BOX_WIDTH, MW_UI_CHECK_BOX_HEIGHT);
	}

	return mw_add_control(&r,
			parent_handle,
			check_box_paint_function,
			check_box_message_function,
			flags,
			check_box_instance_data);
}
