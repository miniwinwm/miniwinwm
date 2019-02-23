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

static void label_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void label_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void label_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_label_data_t *this_label = (mw_ui_label_data_t*)mw_get_control_instance_data(control_handle);

	MW_ASSERT(draw_info != (void*)0, "Null pointer argument");

    /* draw the background */
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_clear_pattern();
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_control_rect(control_handle).width,
			mw_get_control_rect(control_handle).height);

    /* set label text colour according to enabled state */
	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED) == MW_CONTROL_FLAG_IS_ENABLED)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	}
    
    /* draw the label text */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);    
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, MW_UI_LABEL_LARGE_X_OFFSET, 1, this_label->label);
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, MW_UI_LABEL_LARGE_X_OFFSET, 1, this_label->label);
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void label_message_function(const mw_message_t *message)
{
	mw_ui_label_data_t *this_label = (mw_ui_label_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_LABEL_SET_LABEL_TEXT_MESSAGE:
		/* message pointer field contains pointer to new text */
		if (message->message_pointer != NULL)
		{
			(void)mw_util_safe_strcpy(this_label->label, MW_UI_LABEL_MAX_CHARS, (char *)message->message_pointer);
		}
		else
		{
			MW_ASSERT((bool)false, "Null pointer argument");
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

mw_handle_t mw_ui_label_add_new(int16_t x,
		int16_t y,
		int16_t width,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_label_data_t *label_instance_data)
{
	mw_util_rect_t r;

	if ((flags & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, width, MW_UI_LABEL_LARGE_HEIGHT);
	}
	else
	{
		mw_util_set_rect(&r, x, y, width, MW_UI_LABEL_HEIGHT);
	}

	return (mw_add_control(&r,
			parent_handle,
			label_paint_function,
			label_message_function,
			flags,
			label_instance_data));
}
