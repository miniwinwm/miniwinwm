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

#include <string.h>
#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

#define ARROW_POINTS 			(sizeof(shape_x_const) / sizeof(int16_t))
static const int16_t shape_x_const[] = {-3, 0, 4};
static const int16_t shape_y_const[] = {4, -3, 4};
static const int16_t shape_large_x_const[] = {-7, 0, 8};
static const int16_t shape_large_y_const[] = {8, -7, 8};

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static int16_t shape_x[ARROW_POINTS];
static int16_t shape_y[ARROW_POINTS];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void arrow_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void arrow_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void arrow_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_arrow_data_t *this_arrow = (mw_ui_arrow_data_t*)mw_get_control_instance_data(control_handle);
	int16_t arrow_size;
	int16_t arrow_offset;
	mw_hal_lcd_colour_t highlighted_colour;
	mw_hal_lcd_colour_t lowlighted_colour;

    /* set the arrow box fill colour depending on up/down state */
	if (this_arrow->arrow_down)
	{
		mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
	}
	else
	{
		mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	}

    /* draw the arrow's box */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_clear_pattern();
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_control_rect(control_handle).width,
			mw_get_control_rect(control_handle).height);

	if (this_arrow->arrow_down)
	{
		highlighted_colour = MW_HAL_LCD_BLACK;
		lowlighted_colour = MW_HAL_LCD_GREY2;
	}
	else
	{
		highlighted_colour = MW_HAL_LCD_WHITE;
		lowlighted_colour = MW_HAL_LCD_GREY7;
	}

	mw_gl_set_fg_colour(highlighted_colour);
	mw_gl_vline(draw_info, 1, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, 1);
	mw_gl_set_fg_colour(lowlighted_colour);
	mw_gl_vline(draw_info, mw_get_control_rect(control_handle).width - 2, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, mw_get_control_rect(control_handle).height - 2);

	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		(void)memcpy((shape_x), (shape_large_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_large_y_const), (sizeof(shape_y)));
		arrow_size = MW_UI_ARROW_LARGE_SIZE;
	}
	else
	{
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		arrow_size = MW_UI_ARROW_SIZE;
	}
	mw_gl_rotate_shape((uint8_t)ARROW_POINTS, shape_x, shape_y, (int16_t)this_arrow->mw_ui_arrow_direction);

	if (this_arrow->arrow_down)
	{
		arrow_offset = arrow_size / 2 + 1;
	}
	else
	{
		arrow_offset = arrow_size / 2;
	}

	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
	{
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
	}
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_line(MW_GL_SOLID_LINE);

	mw_gl_poly(draw_info,
			(uint8_t)ARROW_POINTS,
			shape_x,
			shape_y,
			arrow_offset,
			arrow_offset);
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void arrow_message_function(const mw_message_t *message)
{
	mw_ui_arrow_data_t *this_arrow = (mw_ui_arrow_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_arrow->arrow_down = false;
		break;

	case MW_TIMER_MESSAGE:
		/* set arrow pressed to false, send the control response message and repaint the control */
		this_arrow->arrow_down = false;
		mw_post_message(MW_ARROW_PRESSED_MESSAGE,
				message->recipient_handle,
				mw_get_control_parent_window_handle(message->recipient_handle),
				(uint32_t)this_arrow->mw_ui_arrow_direction,
				NULL,
				MW_WINDOW_MESSAGE);
		mw_paint_control(message->recipient_handle);
		break;

	case MW_TOUCH_DRAG_MESSAGE:
	case MW_TOUCH_HOLD_DOWN_MESSAGE:
		mw_cancel_timer(this_arrow->timer_handle);
		this_arrow->timer_handle = mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
		if (mw_tick_counter - this_arrow->touch_down_time > MW_HOLD_DOWN_DELAY_TICKS)
		{
			mw_post_message(MW_ARROW_PRESSED_MESSAGE,
					message->recipient_handle,
					mw_get_control_parent_window_handle(message->recipient_handle),
					(uint32_t)this_arrow->mw_ui_arrow_direction,
					NULL,
					MW_WINDOW_MESSAGE);
		}
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */	
		if ((mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
		{
			this_arrow->timer_handle = mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
			this_arrow->arrow_down = true;
			mw_paint_control(message->recipient_handle);
			this_arrow->touch_down_time = mw_tick_counter;
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

mw_handle_t mw_ui_arrow_add_new(int16_t x,
		int16_t y,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_arrow_data_t *arrow_instance_data)
{
	mw_util_rect_t r;

	if ((flags & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, MW_UI_ARROW_LARGE_SIZE + 1, MW_UI_ARROW_LARGE_SIZE + 1);
	}
	else
	{
		mw_util_set_rect(&r, x, y, MW_UI_ARROW_SIZE + 1, MW_UI_ARROW_SIZE + 1);
	}

	return (mw_add_control(&r,
			parent_handle,
			arrow_paint_function,
			arrow_message_function,
			flags,
			arrow_instance_data));
}
