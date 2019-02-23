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

#include <stdlib.h>
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

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void scroll_bar_vert_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void scroll_bar_vert_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info draw info structure describing offset and clip region
 */
static void scroll_bar_vert_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_scroll_bar_vert_data_t *this_scroll_bar_vert = (mw_ui_scroll_bar_vert_data_t*)mw_get_control_instance_data(control_handle);
	int16_t scroll_bar_vert_slider_top;
	int16_t narrow_dimension;
	int16_t slider_size;

	MW_ASSERT(draw_info != (void*)0, "Null pointer argument");

	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		narrow_dimension = MW_SCROLL_BAR_LARGE_NARROW_DIMENSION;
		slider_size = MW_SCROLL_BAR_LARGE_SLIDER_SIZE;
	}
	else
	{
		narrow_dimension = MW_SCROLL_BAR_NARROW_DIMENSION;
		slider_size = MW_SCROLL_BAR_SLIDER_SIZE;
	}

	/* check if there's enough parent client rect width to draw the bar */
	if (mw_get_window_client_rect(mw_get_control_parent_window_handle(control_handle)).width > narrow_dimension)
	{
		if (mw_get_window_client_rect(mw_get_control_parent_window_handle(control_handle)).height > slider_size)
		{
			/* draw the bar */
			mw_gl_set_fill(MW_GL_FILL);
			mw_gl_set_border(MW_GL_BORDER_ON);
			mw_gl_set_line(MW_GL_SOLID_LINE);
			mw_gl_clear_pattern();
			mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
			if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
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
					narrow_dimension,
					mw_get_control_rect(control_handle).height);

			/* only paint slider if enabled */
			if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
			{
				scroll_bar_vert_slider_top = (mw_get_control_rect(control_handle).height - slider_size) *
						(int16_t)this_scroll_bar_vert->scroll_position / UINT8_MAX;

				mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
				mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
				mw_gl_rectangle(draw_info,
						1,
						scroll_bar_vert_slider_top + 1,
						narrow_dimension - 2,
						slider_size - 2);

				/* draw 3d effect */
				mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
				mw_gl_vline(draw_info,
						2,
						scroll_bar_vert_slider_top + 2,
						scroll_bar_vert_slider_top + slider_size - 3);
				mw_gl_hline(draw_info,
						2,
						narrow_dimension - 4,
						scroll_bar_vert_slider_top + 2);
				mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
				mw_gl_vline(draw_info,
						narrow_dimension - 3,
						scroll_bar_vert_slider_top + 2,
						scroll_bar_vert_slider_top + slider_size - 4);
				mw_gl_hline(draw_info,
						3,
						narrow_dimension - 3,
						scroll_bar_vert_slider_top + slider_size - 3);
			}
		}
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void scroll_bar_vert_message_function(const mw_message_t *message)
{
	mw_ui_scroll_bar_vert_data_t *this_scroll_bar_vert = (mw_ui_scroll_bar_vert_data_t*)mw_get_control_instance_data(message->recipient_handle);
	int16_t touch_y;
	uint8_t new_scroll_position;
	uint32_t misra_temp;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_scroll_bar_vert->scroll_position = 0U;
		break;
		
	case MW_SCROLL_BAR_SET_SCROLL_MESSAGE:
		/* handle a transfer data message, which contains new position */
		this_scroll_bar_vert->scroll_position  = (uint8_t)message->message_data;
		break;

	case MW_TOUCH_UP_MESSAGE:
		mw_post_message(MW_TOUCH_UP_MESSAGE,
				message->recipient_handle,
				mw_get_control_parent_window_handle(message->recipient_handle),
				MW_UNUSED_MESSAGE_PARAMETER,
				NULL,
				MW_WINDOW_MESSAGE);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
	case MW_TOUCH_DRAG_MESSAGE:
		/* respond to a down or drag event by recalculating the new slider position from the touch coordinate */
		if ((mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
		{
			misra_temp = message->message_data & 0xffffU;
			touch_y = (int16_t)misra_temp;

			/* scale touch point to middle 90% of scroll bar length */
			touch_y = mw_ui_common_scale_scroll_bar_touch_point(mw_get_control_rect(message->recipient_handle).height, touch_y);

			new_scroll_position = (uint8_t)((uint32_t)UINT8_MAX * (uint32_t)touch_y / (uint32_t)mw_get_control_rect(message->recipient_handle).height);
			if (new_scroll_position != this_scroll_bar_vert->scroll_position)
			{
				/* only repaint if the scroll slider position has changed */
				this_scroll_bar_vert->scroll_position = new_scroll_position;
				mw_paint_control(message->recipient_handle);

				mw_post_message(MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE,
						message->recipient_handle,
						mw_get_control_parent_window_handle(message->recipient_handle),
						this_scroll_bar_vert->scroll_position,
						NULL,
						MW_WINDOW_MESSAGE);
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

mw_handle_t mw_ui_scroll_bar_vert_add_new(int16_t x,
		int16_t y,
		int16_t height,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_scroll_bar_vert_data_t *scroll_bar_vert_instance_data)
{
	mw_util_rect_t r;

	if ((flags & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION, height);
	}
	else
	{
		mw_util_set_rect(&r, x, y, MW_SCROLL_BAR_NARROW_DIMENSION, height);
	}

	return (mw_add_control(&r,
			parent_handle,
			scroll_bar_vert_paint_function,
			scroll_bar_vert_message_function,
			flags,
			scroll_bar_vert_instance_data));
}
