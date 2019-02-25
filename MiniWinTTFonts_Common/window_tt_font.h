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

#ifndef WINDOW_TT_FONT_H
#define WINDOW_TT_FONT_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"

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
 	const char *text;								/**< Pointer to the text to draw in the window */
 	const struct mf_rlefont_s *rle_font;			/**< Pointer to run-length encoded true type font structure */
 	bool bw_font;									/**< If the font was created as a black and white font */
 	mw_hal_lcd_colour_t fg_colour;					/**< Text foreground colour */
 	mw_hal_lcd_colour_t bg_colour;					/**< Text background colour */
 	mw_gl_tt_font_justification_t justification;	/**< Text justification */

 	/* Non user-modifiable values */
 	int16_t vert_scroll_pixels;						/**< How many pixel lines to scroll the text up */
 	int16_t text_height_pixels;						/**< Height of all the text in pixels irrespective if it fits in bounding box */
 	int16_t max_vert_scroll_pixels;					/**< Number of scroll lines in pixels that the text can be scrolled */
 	uint8_t vert_scroll_bar_position;				/**< Scroll bar position as reported by the scroll bar, 0 - UINT8_MAX */
 } window_tt_font_data_t;

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Window paint routine, called by window manager.
 *
 * @param window_handle The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
void window_tt_font_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
void window_tt_font_message_function(const mw_message_t *message);

#ifdef __cplusplus
}
#endif

#endif
