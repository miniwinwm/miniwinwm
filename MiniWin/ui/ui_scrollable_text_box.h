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

#ifndef _UI_SCROLLABLE_TEXT_BOX_H
#define _UI_SCROLLABLE_TEXT_BOX_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"
#include "mcufont.h"

/****************
*** CONSTANTS ***
****************/

 /************
*** TYPES ***
************/

/**
 * Instance data structure for scrollable_text_box ui component
 */
typedef struct
{
	/* User modifiable fields */
	const struct mf_rlefont_s *tt_font;
	mw_gl_tt_font_justification_t justification;
	const char *text;
	mw_hal_lcd_colour_t fg_colour;
	mw_hal_lcd_colour_t bg_colour;

	/* Non-user modifiable fields */
	uint16_t scroll_position;
	uint16_t text_height_pixels;
} mw_ui_scrollable_text_box_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a scrollable_text_box control to a window
 *
 * @param control_rect The bounding box of the rect containing this text box
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param scrollable_text_box_instance_data Instance structure containing scrollable_text_box specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_scrollable_text_box_add_new(mw_util_rect_t *control_rect,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_scrollable_text_box_data_t *scrollable_text_box_instance_data);

#ifdef __cplusplus
}
#endif

#endif
