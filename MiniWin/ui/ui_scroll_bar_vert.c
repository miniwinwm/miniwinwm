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

#include <limits.h>
#include <miniwin.h>
#include "ui/ui_scroll_bar_vert.h"
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

extern mw_control_t mw_all_controls[MW_MAX_CONTROL_COUNT];
extern mw_window_t mw_all_windows[MW_MAX_WINDOW_COUNT];

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

void mw_ui_scroll_bar_vert_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_scroll_bar_vert_data_t *this_scroll_bar_vert = (mw_ui_scroll_bar_vert_data_t*)mw_all_controls[control_ref].extra_data;
	uint16_t scroll_bar_vert_slider_top;

	/* check if there's enough parent client rect width to draw the bar */
	if (mw_all_windows[mw_all_controls[control_ref].parent].client_rect.width > MW_SCROLL_BAR_NARROW_DIMESION &&
			mw_all_windows[mw_all_controls[control_ref].parent].client_rect.height > MW_SCROLL_BAR_SLIDER_SIZE)
	{
		/* draw the bar */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_SCROLL_BAR_BAR_COLOUR);
		if (mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_ENABLED)
		{
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		}
		else
		{
			mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		}
		mw_gl_rectangle(draw_info,
				0,
				0,
				MW_SCROLL_BAR_NARROW_DIMESION,
				mw_all_controls[control_ref].control_rect.height);

		scroll_bar_vert_slider_top = (mw_all_controls[control_ref].control_rect.height - MW_SCROLL_BAR_SLIDER_SIZE) *
				this_scroll_bar_vert->scroll_position / UINT8_MAX;

		if (mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_ENABLED)
		{
			mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
		}
		else
		{
			mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
		}
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_rectangle(draw_info,
				1,
				scroll_bar_vert_slider_top + 1,
				MW_SCROLL_BAR_NARROW_DIMESION - 2,
				MW_SCROLL_BAR_SLIDER_SIZE - 2);
	}
}

void mw_ui_scroll_bar_vert_message_function(const mw_message_t *message)
{
	mw_ui_scroll_bar_vert_data_t *this_scroll_bar_vert = (mw_ui_scroll_bar_vert_data_t*)mw_all_controls[message->recipient_id].extra_data;
	int16_t touch_y;
	uint8_t new_scroll_position;

	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_scroll_bar_vert->scroll_position = 0;
		break;
		
	case MW_TRANSFER_DATA_1_MESSAGE:
		/* handle a transfer data message, which contains new position */
		this_scroll_bar_vert->scroll_position  = (uint8_t)message->message_data;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
	case MW_TOUCH_DRAG_MESSAGE:
		/* respond to a down or drag event by recalculating the new slider position from the touch coordinate */
		if (mw_all_controls[message->recipient_id].control_flags & MW_CONTROL_FLAG_IS_ENABLED)
		{
			touch_y = (int16_t)(message->message_data & 0xffff);

			/* scale touch point to middle 90% of scroll bar length */
			touch_y = mw_ui_common_scale_scroll_bar_touch_point(mw_all_controls[message->recipient_id].control_rect.height, touch_y);

			new_scroll_position = (uint8_t)(UINT8_MAX * touch_y / (uint32_t)mw_all_controls[message->recipient_id].control_rect.height);
			if (new_scroll_position != this_scroll_bar_vert->scroll_position)
			{
				/* only repaint if the scroll slider position has changed */
				this_scroll_bar_vert->scroll_position = new_scroll_position;
				mw_paint_control(message->recipient_id);

				mw_post_message(MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE,
						message->recipient_id,
						mw_all_controls[message->recipient_id].parent,
						this_scroll_bar_vert->scroll_position,
						MW_WINDOW_MESSAGE);
			}
		}
		break;

	default:
		break;
	}
}

uint8_t mw_ui_scroll_bar_vert_add_new(uint16_t x,
		uint16_t y,
		uint16_t height,
		uint8_t parent,
		uint32_t flags,
		mw_ui_scroll_bar_vert_data_t *scroll_bar_vert_instance_data)
{
	mw_util_rect_t r;

	mw_util_set_rect(&r, x, y, MW_SCROLL_BAR_NARROW_DIMESION, height);

	return mw_add_control(&r,
			parent,
			mw_ui_scroll_bar_vert_paint_function,
			mw_ui_scroll_bar_vert_message_function,
			flags,
			scroll_bar_vert_instance_data);
}
