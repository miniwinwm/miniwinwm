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

#ifndef UI_SCROLL_BAR_VERT_H
#define UI_SCROLL_BAR_VERT_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <miniwin.h>

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Instance data structure for vertical scroll bar ui component
 */
typedef struct
{
  /* User modifiable fields */
  
  /* Non-user modifiable fields */        
	uint8_t scroll_position;			/**< the scroll position as a proportion of 0xff */
} mw_ui_scroll_bar_vert_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_ref The control identifier in the array of controls
 * @param draw_info draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
void mw_ui_scroll_bar_vert_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info);

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
void mw_ui_scroll_bar_vert_message_function(const mw_message_t *message);

/**
 * Add a vertical scroll bar control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param height Height of scroll bar containing box
 * @param parent The containing window of this control
 * @param flags General control flags controlling the control
 * @param scroll_bar_vert_instance_data Instance structure containing vertical scroll bar specific data items
 */
uint8_t mw_ui_scroll_bar_vert_add_new(uint16_t x,
		uint16_t y,
		uint16_t height,
		uint8_t parent,
		uint32_t flags,
		mw_ui_scroll_bar_vert_data_t *scroll_bar_vert_instance_data);

#ifdef __cplusplus
}
#endif

#endif
