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
#include "window_tt_font_text_box_scroll_bar.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

 /**
  * Window instance data for each true type font window
  */
 typedef struct
 {
	/* User-modifiable values */

 	/* Non user-modifiable values */
 } window_tt_font_text_box_scroll_bar_data_t;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern mw_handle_t button_scroll_bar_handle;
extern mw_handle_t text_box_scroll_bar_handle;
extern mw_handle_t vert_scroll_bar_handle;

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

void window_tt_font_text_box_scroll_bar_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREY4);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);
}

void window_tt_font_text_box_scroll_bar_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_TEXT_BOX_SCROLLING_REQUIRED_MESSAGE:
		/* enable/disable the scroll bar depending on if scrolling is required, i.e. text won't all fit in the control */
		mw_set_control_enabled(vert_scroll_bar_handle, message->message_data);
		mw_paint_control(vert_scroll_bar_handle);
		break;

	case MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		/* vertical scroll bar scroll new position message received so send it on to the text box */
		mw_post_message(MW_TEXT_BOX_SCROLL_BAR_POSITION_MESSAGE,
				message->recipient_handle,
				text_box_scroll_bar_handle,
				message->message_data,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_CONTROL_MESSAGE);
		mw_paint_control(text_box_scroll_bar_handle);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_handle == button_scroll_bar_handle)
		{
			/* set scroll bar position back to zero */
			mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
					message->recipient_handle,
					vert_scroll_bar_handle,
					0,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(vert_scroll_bar_handle);

			/* set the new text in the text box, this sets its scroll position to 0 */
			mw_post_message(MW_TEXT_BOX_SET_TEXT_MESSAGE,
					message->recipient_handle,
					text_box_scroll_bar_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)"Hello world!",
					MW_CONTROL_MESSAGE);
			mw_paint_control(text_box_scroll_bar_handle);

			/* disable the button */
			mw_set_control_enabled(button_scroll_bar_handle, false);
			mw_paint_control(button_scroll_bar_handle);
		}
		break;

	default:
		break;
	}
}
