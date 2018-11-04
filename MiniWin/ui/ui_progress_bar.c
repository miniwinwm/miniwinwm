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

static void progress_bar_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void progress_bar_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void progress_bar_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_progress_bar_data_t *this_progress_bar = (mw_ui_progress_bar_data_t*)mw_get_control_instance_data(control_handle);

    /* draw the background */
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_clear_pattern();
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_control_rect(control_handle).width,
			mw_get_control_rect(control_handle).height);

	if (this_progress_bar->progress_percent > 100)
	{
		this_progress_bar->progress_percent = 100;
	}

	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info, 1, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, 1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info, mw_get_control_rect(control_handle).width - 2, 1, mw_get_control_rect(control_handle).height - 2);
	mw_gl_hline(draw_info, 1, mw_get_control_rect(control_handle).width - 2, mw_get_control_rect(control_handle).height - 2);

    /* set progress_bar progress fill colour according to enabled state */
	if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED)
	{
		mw_gl_set_solid_fill_colour(MW_PROGRESS_BAR_COLOUR);
	}
	else
	{
		mw_gl_set_solid_fill_colour(MW_CONTROL_DISABLED_COLOUR);
	}

	mw_gl_set_border(MW_GL_BORDER_OFF);

	mw_gl_rectangle(draw_info,
			2,
			2,
			((mw_get_control_rect(control_handle).width - 4) * this_progress_bar->progress_percent) / 100,
			mw_get_control_rect(control_handle).height - 4);
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void progress_bar_message_function(const mw_message_t *message)
{
	mw_ui_progress_bar_data_t *this_progress_bar = (mw_ui_progress_bar_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_PROGRESS_BAR_SET_PROGRESS_MESSAGE:
		/* handle a transfer data message, which contains new progress_bar progress */
		this_progress_bar->progress_percent = message->message_data;
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_progress_bar_add_new(uint16_t x,
		uint16_t y,
		uint16_t width,
		uint16_t height,
		mw_handle_t parent,
		uint32_t flags,
		mw_ui_progress_bar_data_t *progress_bar_instance_data)
{
	mw_util_rect_t r;

	if (height < 3 || width < 3)
	{
		MW_ASSERT(false, "Height too small");
		return MW_INVALID_HANDLE;
	}

	mw_util_set_rect(&r, x, y, width, height);

	/* no account taken of the MW_CONTROL_FLAG_LARGE_SIZE flag as user sets required size of this control */

	return mw_add_control(&r,
			parent,
			progress_bar_paint_function,
			progress_bar_message_function,
			flags,
			progress_bar_instance_data);
}
