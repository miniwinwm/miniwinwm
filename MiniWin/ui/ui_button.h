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

#ifndef UI_BUTTON_H
#define UI_BUTTON_H

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

#define MW_UI_BUTTON_LABEL_MAX_CHARS	10

#define MW_UI_BUTTON_WIDTH				50
#define MW_UI_BUTTON_HEIGHT				15

#define MW_UI_BUTTON_LARGE_WIDTH		100
#define MW_UI_BUTTON_LARGE_HEIGHT		30

/************
*** TYPES ***
************/

/**
 * Extra data structure for button ui component
 */
typedef struct
{
  /* User modifiable fields */
	char button_label[MW_UI_BUTTON_LABEL_MAX_CHARS + 1];	/**< text of label shown to right of button */
  
  /* Non-user modifiable fields */
	bool button_down;										/**< set when the button is down */
} mw_ui_button_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_ref The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
void mw_ui_button_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info);

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
void mw_ui_button_message_function(const mw_message_t *message);

/**
 * Add a button control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param parent The containing window of this control
 * @param flags General control flags controlling the control
 * @param button_instance_data Instance structure containing button specific data items
 */
uint8_t mw_ui_button_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_button_data_t *button_instance_data);

#ifdef __cplusplus
}
#endif

#endif
