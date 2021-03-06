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
#include "miniwin_user.h"
#include "window_tt_font_text_box_arrows.h"

/****************
*** CONSTANTS ***
****************/

#define SCROLL_STEP_SIZE		8U			/**< Increase to speed up scrolling */

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
	 uint16_t lines_to_scroll;				/*<< Lines to scroll in pixels */
	 uint16_t max_scrollable_lines;			/**< Maximum number of pixel lines the text can be scrolled */
} window_tt_font_text_box_arrows_data_t;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_tt_font_text_box_arrows_data_t window_tt_font_text_box_arrows_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_tt_font_tbox_arrows_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

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

void window_tt_font_tbox_arrows_message_function(const mw_message_t *message)
{
	uint32_t temp_uint32;

	MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_tt_font_text_box_arrows_data.lines_to_scroll = 0U;
		break;

	case MW_TEXT_BOX_SCROLLING_REQUIRED_MESSAGE:
		/* enable/disable the down arrow depending on if scrolling is required, i.e. text won't all fit in the control */
		temp_uint32 = message->message_data >> 16;
		mw_set_control_enabled(arrow_down_handle, (bool)temp_uint32);
		temp_uint32 = message->message_data & 0xffffU;
		window_tt_font_text_box_arrows_data.max_scrollable_lines = (uint16_t)temp_uint32;
		mw_paint_control(arrow_down_handle);
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		/* an arrow has been pressed */
		if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_UP &&
				window_tt_font_text_box_arrows_data.lines_to_scroll > 0U)
		{
			/* up arrow, scroll text up is ok to do so */
			if (window_tt_font_text_box_arrows_data.lines_to_scroll < SCROLL_STEP_SIZE)
			{
				window_tt_font_text_box_arrows_data.lines_to_scroll = 0U;
			}
			else
			{
				window_tt_font_text_box_arrows_data.lines_to_scroll -= SCROLL_STEP_SIZE;
			}

			if (window_tt_font_text_box_arrows_data.lines_to_scroll == 0U)
			{
				mw_set_control_enabled(arrow_up_handle, false);
				mw_paint_control(arrow_up_handle);
			}

			mw_set_control_enabled(arrow_down_handle, true);
			mw_paint_control(arrow_down_handle);

			mw_post_message(MW_TEXT_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					text_box_arrows_handle,
					window_tt_font_text_box_arrows_data.lines_to_scroll,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(text_box_arrows_handle);
		}
		else if ((mw_ui_arrow_direction_t)message->message_data == MW_UI_ARROW_DOWN &&
				window_tt_font_text_box_arrows_data.lines_to_scroll < window_tt_font_text_box_arrows_data.max_scrollable_lines)
		{
			/* down arrow, scroll text down if ok to do so */
			window_tt_font_text_box_arrows_data.lines_to_scroll += SCROLL_STEP_SIZE;

			if (window_tt_font_text_box_arrows_data.lines_to_scroll >= window_tt_font_text_box_arrows_data.max_scrollable_lines)
			{
				window_tt_font_text_box_arrows_data.lines_to_scroll = window_tt_font_text_box_arrows_data.max_scrollable_lines;
				mw_set_control_enabled(arrow_down_handle, false);
				mw_paint_control(arrow_down_handle);
			}

			mw_set_control_enabled(arrow_up_handle, true);
			mw_paint_control(arrow_up_handle);

			mw_post_message(MW_TEXT_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					text_box_arrows_handle,
					window_tt_font_text_box_arrows_data.lines_to_scroll,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(text_box_arrows_handle);
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_handle == button_arrows_handle)
		{
			mw_set_control_enabled(arrow_up_handle, false);
			mw_paint_control(arrow_up_handle);

			/* set the new text in the text box, this sets its scroll position to 0 */
			mw_post_message(MW_TEXT_BOX_SET_TEXT_MESSAGE,
					message->recipient_handle,
					text_box_arrows_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)"Hello world!",
					MW_CONTROL_MESSAGE);
			mw_paint_control(text_box_arrows_handle);

			/* update scroll position */
			window_tt_font_text_box_arrows_data.lines_to_scroll = 0U;

			/* disable the button */
			mw_set_control_enabled(button_arrows_handle, false);
			mw_paint_control(button_arrows_handle);
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
