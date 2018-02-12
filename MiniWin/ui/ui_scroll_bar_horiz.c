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
#include "ui/ui_scroll_bar_horiz.h"
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

void mw_ui_scroll_bar_horiz_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_scroll_bar_horiz_data_t *this_scroll_bar_horiz = (mw_ui_scroll_bar_horiz_data_t*)mw_all_controls[control_ref].extra_data;
	uint16_t scroll_bar_horiz_slider_left;

	/* check if there's enough parent client rect height to draw the bar */
	if (mw_all_windows[mw_all_controls[control_ref].parent].client_rect.height > MW_SCROLL_BAR_NARROW_DIMESION &&
			mw_all_windows[mw_all_controls[control_ref].parent].client_rect.width > MW_SCROLL_BAR_SLIDER_SIZE)
	{
		/* draw the bar */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
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
				mw_all_controls[control_ref].control_rect.width,
				MW_SCROLL_BAR_NARROW_DIMESION);

		scroll_bar_horiz_slider_left = (mw_all_controls[control_ref].control_rect.width - MW_SCROLL_BAR_SLIDER_SIZE) *
				this_scroll_bar_horiz->scroll_position / UINT8_MAX;

		mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_rectangle(draw_info,
				scroll_bar_horiz_slider_left + 1,
				1,
				MW_SCROLL_BAR_SLIDER_SIZE - 2,
				MW_SCROLL_BAR_NARROW_DIMESION - 2);

		/* draw 3d effect */
		mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
		mw_gl_vline(draw_info,
				scroll_bar_horiz_slider_left + 2,
				2,
				MW_SCROLL_BAR_SLIDER_SIZE - 3);
		mw_gl_hline(draw_info,
				scroll_bar_horiz_slider_left + 2,
				scroll_bar_horiz_slider_left + MW_SCROLL_BAR_SLIDER_SIZE - 4,
				2);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
		mw_gl_vline(draw_info,
				scroll_bar_horiz_slider_left + MW_SCROLL_BAR_SLIDER_SIZE - 3,
				2,
				MW_SCROLL_BAR_SLIDER_SIZE - 4);
		mw_gl_hline(draw_info,
				scroll_bar_horiz_slider_left + 3,
				scroll_bar_horiz_slider_left + MW_SCROLL_BAR_SLIDER_SIZE - 3,
				MW_SCROLL_BAR_NARROW_DIMESION - 3);
	}
}

void mw_ui_scroll_bar_horiz_message_function(const mw_message_t *message)
{
	mw_ui_scroll_bar_horiz_data_t *this_scroll_bar_horiz = (mw_ui_scroll_bar_horiz_data_t*)mw_all_controls[message->recipient_id].extra_data;
	int16_t touch_x;
	uint8_t new_scroll_position;

	MW_ASSERT(message);

	switch (message->message_id)
	{	
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_scroll_bar_horiz->scroll_position = 0;
		break;
		
	case MW_TRANSFER_DATA_1_MESSAGE:
		/* handle a transfer data message, which contains new position */
		this_scroll_bar_horiz->scroll_position  = (uint8_t)message->message_data;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
	case MW_TOUCH_DRAG_MESSAGE:
		/* respond to a down or drag event by recalulating the new slider position from the touch coordinate */
		if (mw_all_controls[message->recipient_id].control_flags & MW_CONTROL_FLAG_IS_ENABLED)
		{
			touch_x = (int16_t)(message->message_data >> 16);

			/* scale touch point to middle 90% of scroll bar length */
			touch_x = mw_ui_common_scale_scroll_bar_touch_point(mw_all_controls[message->recipient_id].control_rect.width, touch_x);

			new_scroll_position = (uint8_t)(UINT8_MAX * touch_x / (uint32_t)mw_all_controls[message->recipient_id].control_rect.width);
			if (new_scroll_position != this_scroll_bar_horiz->scroll_position)
			{
				/* only repaint if the scroll slider position has changed */
				this_scroll_bar_horiz->scroll_position = new_scroll_position;
				mw_paint_control(message->recipient_id);

				/* post the control response message */
				mw_post_message(MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE,
						message->recipient_id,
						mw_all_controls[message->recipient_id].parent,
						this_scroll_bar_horiz->scroll_position,
						MW_WINDOW_MESSAGE);
			}
		}
		break;

	default:
		break;
	}
}

uint8_t mw_ui_scroll_bar_horiz_add_new(uint16_t x,
		uint16_t y,
		uint16_t width,
		uint8_t parent,
		uint32_t flags,
		mw_ui_scroll_bar_horiz_data_t *scroll_bar_horiz_instance_data)
{
	mw_util_rect_t r;

	mw_util_set_rect(&r, x, y, width, MW_SCROLL_BAR_NARROW_DIMESION);

	return mw_add_control(&r,
			parent,
			mw_ui_scroll_bar_horiz_paint_function,
			mw_ui_scroll_bar_horiz_message_function,
			flags,
			scroll_bar_horiz_instance_data);
}
