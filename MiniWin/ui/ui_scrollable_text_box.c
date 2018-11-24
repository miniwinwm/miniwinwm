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

static void scrollable_text_box_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void scrollable_text_box_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void scrollable_text_box_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_scrollable_text_box_data_t *this_scrollable_text_box = (mw_ui_scrollable_text_box_data_t*)mw_get_control_instance_data(control_handle);
	mw_util_rect_t control_rect;

	/* get control's client rect */
	mw_util_set_rect(&control_rect,
			0,
			0,
			mw_get_control_rect(control_handle).width,
			mw_get_control_rect(control_handle).height);

	/* render text */
	mw_gl_set_fg_colour(this_scrollable_text_box->fg_colour);
	mw_gl_set_bg_colour(this_scrollable_text_box->bg_colour);
	mw_gl_tt_render_text(draw_info,
			&control_rect,
			this_scrollable_text_box->justification,
			this_scrollable_text_box->tt_font,
			this_scrollable_text_box->text,
			this_scrollable_text_box->lines_to_scroll);

	/* if the text has not filled the whole control paint the background of what remains */
	if (control_rect.height > this_scrollable_text_box->text_height_pixels)
	{
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(this_scrollable_text_box->bg_colour);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_clear_pattern();
		mw_gl_rectangle(draw_info,
				0,
				this_scrollable_text_box->text_height_pixels,
				control_rect.width,
				control_rect.height - this_scrollable_text_box->text_height_pixels);
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void scrollable_text_box_message_function(const mw_message_t *message)
{
	mw_ui_scrollable_text_box_data_t *this_scrollable_text_box = (mw_ui_scrollable_text_box_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */
		this_scrollable_text_box->lines_to_scroll = 0;

		/* get height of rendered text in pixels without actually rendering it */
		this_scrollable_text_box->text_height_pixels = mw_gl_tt_get_render_text_lines(mw_get_control_rect(message->recipient_handle).width,
				this_scrollable_text_box->justification,
				this_scrollable_text_box->tt_font,
				this_scrollable_text_box->text);

		/* send message about whether scrolling is needed */
		mw_post_message(MW_TEXT_BOX_SCROLLING_REQUIRED,
				message->recipient_handle,
				mw_get_control_parent_window_handle(message->recipient_handle),
				this_scrollable_text_box->text_height_pixels > mw_get_control_rect(message->recipient_handle).height,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);
		break;

	case MW_TEXT_BOX_SCROLL_BAR_POSITION_MESSAGE:
		if (this_scrollable_text_box->text_height_pixels <= mw_get_control_rect(message->recipient_handle).height)
		{
			/* set scroll pixels to zero */
			this_scrollable_text_box->lines_to_scroll = 0;
		}
		else
		{
			/* recalculate vertical scroll pixels from last scroll bar position recorded */
			uint16_t max_scroll_lines = this_scrollable_text_box->text_height_pixels - mw_get_control_rect(message->recipient_handle).height;
			this_scrollable_text_box->lines_to_scroll = (max_scroll_lines * message->message_data) / 255;
			mw_paint_control(message->recipient_handle);
		}
		break;

	case MW_TEXT_BOX_SET_TEXT_MESSAGE:
		/* message pointer field contains pointer to new text */
		if (message->message_pointer)
		{
			this_scrollable_text_box->text = (char *)(message->message_pointer);
			this_scrollable_text_box->lines_to_scroll = 0;
			mw_paint_control(message->recipient_handle);

			/* get height of rendered text in pixels without actually rendering it */
			this_scrollable_text_box->text_height_pixels = mw_gl_tt_get_render_text_lines(mw_get_control_rect(message->recipient_handle).width,
					this_scrollable_text_box->justification,
					this_scrollable_text_box->tt_font,
					this_scrollable_text_box->text);

			/* send message about whether scrolling is needed */
			mw_post_message(MW_TEXT_BOX_SCROLLING_REQUIRED,
					message->recipient_handle,
					mw_get_control_parent_window_handle(message->recipient_handle),
					this_scrollable_text_box->text_height_pixels > mw_get_control_rect(message->recipient_handle).height,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_WINDOW_MESSAGE);
		}
		else
		{
			MW_ASSERT(false, "Null pointer argument");
		}
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_scrollable_text_box_add_new(mw_util_rect_t *control_rect,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_scrollable_text_box_data_t *scrollable_text_box_instance_data)
{
	/* check for null parameters */
	if (control_rect == NULL ||
			scrollable_text_box_instance_data == NULL ||
			scrollable_text_box_instance_data->tt_font == NULL ||
			scrollable_text_box_instance_data->text == NULL)
	{
		MW_ASSERT(false, "Null pointer argument");
		return MW_INVALID_HANDLE;
	}

	return mw_add_control(control_rect,
			parent_handle,
			scrollable_text_box_paint_function,
			scrollable_text_box_message_function,
			flags,
			scrollable_text_box_instance_data,
			MW_UI_CONTROL_TEXT_BOX_TYPE);
}
