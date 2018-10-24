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

#ifndef _DIALOG_TEXT_ENTRY_H
#define _DIALOG_TEXT_ENTRY_H

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

#define MW_DIALOG_MAX_TEXT_LENGTH		20 /**< Maximum number of characters that can be entered */

 /************
 *** TYPES ***
 ************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Create a dynamic dialog window with one button.
 *
 * @param x left coordinate of dialog window
 * @param y top coordinate of dialog window
 * @param title pointer to text displayed in the window title bar
 * @param response_window_id window id of the window that the response message is posted to when the dialog is dismissed
 * @return the window id of the window used for the dialog which is only valid while the dialog is showing
 * @note There must be space in the window array for one new window and space in the control array
 *       for one new control. These resources are released when the dialog is dismissed.
 *       The dialog is created modal and is brought to the front on showing.
 *       The dialog must fit entirely on the screen or else it will not be created.
 *       The text strings are not copied and must exists while the dialog is showing
 *
 * @warning Do not call this from a client window paint function. In debug mode it will cause an assert failure.
 */
uint8_t mw_create_window_dialog_text_entry(uint16_t x,
		uint16_t y,
		char *title,
		uint8_t response_window_id);

#ifdef __cplusplus
}
#endif

#endif
