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

#include "miniwin.h"
#include "miniwin_user.h"
#include "window_tt_font.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void set_scroll(const mw_message_t *message, window_tt_font_data_t *window_tt_font_data);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Update scroll bar enabled state and calculations after a scroll or when window created
 *
 * @param message The window message passed to the message handler
 * @param window_tt_font_data The window instance data passed
 */
static void set_scroll(const mw_message_t *message, window_tt_font_data_t *window_tt_font_data)
{
	mw_util_rect_t window_client_rect = mw_get_window_client_rect(message->recipient_handle);

	/* get height of rendered text in pixels without actually rendering it */
	window_tt_font_data->text_height_pixels = mw_gl_tt_get_render_text_lines(window_client_rect.width,
			window_tt_font_data->justification,
			window_tt_font_data->rle_font,
			window_tt_font_data->text);

	/* now compare height of text in pixels compared to window client height */
	if (window_tt_font_data->text_height_pixels <= window_client_rect.height)
	{
		/* set scroll bar disabled and scroll pixels to zero */
		mw_set_window_vert_scroll_bar_enabled_state(message->recipient_handle, false);
		window_tt_font_data->vert_scroll_pixels = 0;
	}
	else
	{
		/* set scroll bar enabled */
		mw_set_window_vert_scroll_bar_enabled_state(message->recipient_handle, true);
		window_tt_font_data->max_vert_scroll_pixels = window_tt_font_data->text_height_pixels -
				window_client_rect.height;

		/* recalculate vertical scroll pixels from last scroll bar position recorded */
		window_tt_font_data->vert_scroll_pixels = (window_tt_font_data->max_vert_scroll_pixels * (int16_t)window_tt_font_data->vert_scroll_bar_position) / UINT8_MAX;
	}

	/* repaint the scroll bar */
	mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_tt_font_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	window_tt_font_data_t *window_tt_font_data = (window_tt_font_data_t *)mw_get_window_instance_data(window_handle);
	mw_util_rect_t window_client_rect = mw_get_window_client_rect(window_handle);
	mw_util_rect_t text_rect;

	MW_ASSERT(draw_info != (void*)0 && window_tt_font_data != (void*)0, "Null pointer parameter");

	mw_gl_set_fg_colour(window_tt_font_data->fg_colour);
	mw_gl_set_bg_colour(window_tt_font_data->bg_colour);
	mw_util_set_rect(&text_rect, 0, 0, window_client_rect.width, window_client_rect.height);
	mw_gl_tt_render_text(draw_info,
			&text_rect,
			window_tt_font_data->justification,
			window_tt_font_data->rle_font,
			window_tt_font_data->text,
			window_tt_font_data->vert_scroll_pixels);

	/* if the text has not filled the whole window paint the background of what remains */
	if (window_client_rect.height > window_tt_font_data->text_height_pixels)
	{
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(window_tt_font_data->bg_colour);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_clear_pattern();
		mw_gl_rectangle(draw_info,
				0,
				window_tt_font_data->text_height_pixels,
				window_client_rect.width,
				window_client_rect.height - window_tt_font_data->text_height_pixels);
	}
}

void window_tt_font_message_function(const mw_message_t *message)
{
	window_tt_font_data_t *window_tt_font_data = (window_tt_font_data_t *)mw_get_window_instance_data(message->recipient_handle);

	MW_ASSERT(message != (void*)0 && window_tt_font_data != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_tt_font_data->vert_scroll_pixels = 0;
		set_scroll(message, window_tt_font_data);
		break;

	case MW_WINDOW_RESIZED_MESSAGE:
		set_scroll(message, window_tt_font_data);
		break;

	case MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		window_tt_font_data->vert_scroll_bar_position = (uint8_t)message->message_data;
		window_tt_font_data->vert_scroll_pixels = (window_tt_font_data->max_vert_scroll_pixels * (int16_t)message->message_data) / UINT8_MAX;
		mw_paint_window_client(message->recipient_handle);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
