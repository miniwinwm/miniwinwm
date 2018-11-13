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

static void scroll_bar_horiz_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void scroll_bar_horiz_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void scroll_bar_horiz_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_scroll_bar_horiz_data_t *this_scroll_bar_horiz = (mw_ui_scroll_bar_horiz_data_t*)mw_get_control_instance_data(control_handle);
	uint16_t scroll_bar_horiz_slider_left;
	uint16_t narrow_dimension;
	uint16_t slider_size;

	if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		narrow_dimension = MW_SCROLL_BAR_LARGE_NARROW_DIMENSION;
		slider_size = MW_SCROLL_BAR_LARGE_SLIDER_SIZE;
	}
	else
	{
		narrow_dimension = MW_SCROLL_BAR_NARROW_DIMENSION;
		slider_size = MW_SCROLL_BAR_SLIDER_SIZE;
	}

	/* check if there's enough parent client rect height to draw the bar */
	if (mw_get_window_client_rect(mw_get_control_parent_window_handle(control_handle)).height > narrow_dimension &&
			mw_get_window_client_rect(mw_get_control_parent_window_handle(control_handle)).width > slider_size)
	{
		/* draw the bar */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
		if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED)
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
				mw_get_control_rect(control_handle).width,
				narrow_dimension);

		scroll_bar_horiz_slider_left = (mw_get_control_rect(control_handle).width - slider_size) *
				this_scroll_bar_horiz->scroll_position / UINT8_MAX;

		mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_rectangle(draw_info,
				scroll_bar_horiz_slider_left + 1,
				1,
				slider_size - 2,
				narrow_dimension - 2);

		/* draw 3d effect */
		mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
		mw_gl_vline(draw_info,
				scroll_bar_horiz_slider_left + 2,
				2,
				slider_size - 3);
		mw_gl_hline(draw_info,
				scroll_bar_horiz_slider_left + 2,
				scroll_bar_horiz_slider_left + slider_size - 4,
				2);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
		mw_gl_vline(draw_info,
				scroll_bar_horiz_slider_left + slider_size - 3,
				2,
				slider_size - 4);
		mw_gl_hline(draw_info,
				scroll_bar_horiz_slider_left + 3,
				scroll_bar_horiz_slider_left + slider_size - 3,
				narrow_dimension - 3);
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void scroll_bar_horiz_message_function(const mw_message_t *message)
{
	mw_ui_scroll_bar_horiz_data_t *this_scroll_bar_horiz = (mw_ui_scroll_bar_horiz_data_t*)mw_get_control_instance_data(message->recipient_handle);
	int16_t touch_x;
	uint8_t new_scroll_position;

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{	
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_scroll_bar_horiz->scroll_position = 0;
		break;
		
	case MW_SCROLL_BAR_SET_SCROLL_MESSAGE:
		/* handle a transfer data message, which contains new position */
		this_scroll_bar_horiz->scroll_position  = (uint8_t)message->message_data;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
	case MW_TOUCH_DRAG_MESSAGE:
		/* respond to a down or drag event by recalulating the new slider position from the touch coordinate */
		if (mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED)
		{
			touch_x = (int16_t)(message->message_data >> 16);

			/* scale touch point to middle 90% of scroll bar length */
			touch_x = mw_ui_common_scale_scroll_bar_touch_point(mw_get_control_rect(message->recipient_handle).width, touch_x);

			new_scroll_position = (uint8_t)(UINT8_MAX * touch_x / (uint32_t)mw_get_control_rect(message->recipient_handle).width);
			if (new_scroll_position != this_scroll_bar_horiz->scroll_position)
			{
				/* only repaint if the scroll slider position has changed */
				this_scroll_bar_horiz->scroll_position = new_scroll_position;
				mw_paint_control(message->recipient_handle);

				/* post the control response message */
				mw_post_message(MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE,
						message->recipient_handle,
						mw_get_control_parent_window_handle(message->recipient_handle),
						this_scroll_bar_horiz->scroll_position,
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_WINDOW_MESSAGE);
			}
		}
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_scroll_bar_horiz_add_new(uint16_t x,
		uint16_t y,
		uint16_t width,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_scroll_bar_horiz_data_t *scroll_bar_horiz_instance_data)
{
	mw_util_rect_t r;

	if (flags & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, width, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION);
	}
	else
	{
		mw_util_set_rect(&r, x, y, width, MW_SCROLL_BAR_NARROW_DIMENSION);
	}

	return mw_add_control(&r,
			parent_handle,
			scroll_bar_horiz_paint_function,
			scroll_bar_horiz_message_function,
			flags,
			scroll_bar_horiz_instance_data);
}
