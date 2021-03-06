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

#ifndef WINDOW_TEXT_H
#define WINDOW_TEXT_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/*************************
*** EXTERNAL VARIABLES ***
*************************/

 /**
  * Structure holding instance data for text displaying window
  */
 typedef struct
 {
	char path_and_filename_text[MAX_FOLDER_AND_FILENAME_LENGTH + 1];	/**< Path and filename of text to display */
	mw_handle_t text_window_handle;										/**< Handle of this window instance */
 	int16_t max_line_width;												/**< Maximum width in characters of all lines in displayed text */
 	int16_t number_of_lines;											/**< Number of lines of text being displayed */
 	int16_t x_scroll_pos;												/**< x scroll position as pixels */
 	int16_t y_scroll_pos;												/**< y scroll position as pixels */
 	int16_t last_drag_x;												/**< x position of last drag message */
 	int16_t last_drag_y;												/**< y position of last drag message */
 } text_window_data_t;

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
void window_text_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
void window_text_message_function(const mw_message_t *message);

#ifdef __cplusplus
}
#endif

#endif
