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

extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void button_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void button_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void button_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_button_data_t *this_button = (mw_ui_button_data_t*)mw_get_control_instance_data(control_handle);
	mw_hal_lcd_colour_t highlighted_colour;
	mw_hal_lcd_colour_t lowlighted_colour;
	uint16_t text_width;
	uint16_t text_x;

    /* set the button box fill colour depending on enabled state */    
	if (this_button->button_down)
	{
		mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
	}
	else
	{
		mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	}

    /* draw the button's box */
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

	if (this_button->button_down)
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

 	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	/* set text colour according to enabled state */
	if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	}

	/* get the text width */
	if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		text_width = mw_gl_get_string_width_pixels(this_button->button_label);
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		text_width = strlen(this_button->button_label) * (mw_gl_get_font_width() + 1);
	}
	text_x = (mw_get_control_rect(control_handle).width - text_width) / 2;

	if (this_button->button_down)
	{
		if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAGS_LARGE_SIZE)
		{
			mw_gl_string(draw_info, text_x + 2, 11, this_button->button_label);
		}
		else
		{
			mw_gl_string(draw_info, text_x + 2, 4, this_button->button_label);
		}
	}
	else
	{
		if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAGS_LARGE_SIZE)
		{
			mw_gl_string(draw_info, text_x, 9, this_button->button_label);
		}
		else
		{
			mw_gl_string(draw_info, text_x, 3, this_button->button_label);
		}
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void button_message_function(const mw_message_t *message)
{
	mw_ui_button_data_t *this_button = (mw_ui_button_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */			
		this_button->button_down = false;
		break;

	case MW_TIMER_MESSAGE:
		/* set button pressed to false, send the control response message and repaint the control */	
		this_button->button_down = false;
		mw_post_message(MW_BUTTON_PRESSED_MESSAGE,
				message->recipient_handle,
				mw_get_control_parent_window(message->recipient_handle),
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);
		mw_paint_control(message->recipient_handle);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */	
		if (mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED)
		{
			mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
			this_button->button_down = true;
			mw_paint_control(message->recipient_handle);
		}
		break;

		default:
			break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_button_add_new(uint16_t x,
		uint16_t y,
		mw_handle_t parent,
		uint32_t flags,
		mw_ui_button_data_t *button_instance_data)
{
	mw_util_rect_t r;

	if (flags & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, MW_UI_BUTTON_LARGE_WIDTH, MW_UI_BUTTON_LARGE_HEIGHT);
	}
	else
	{
		mw_util_set_rect(&r, x, y, MW_UI_BUTTON_WIDTH, MW_UI_BUTTON_HEIGHT);
	}

	return mw_add_control(&r,
			parent,
			button_paint_function,
			button_message_function,
			flags,
			button_instance_data);
}
