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

#ifndef UI_LABEL_H
#define UI_LABEL_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

#define MW_UI_LABEL_MAX_CHARS		40

#define MW_UI_LABEL_HEIGHT			12
#define MW_UI_LABEL_X_OFFSET		2

#define MW_UI_LABEL_LARGE_HEIGHT	18
#define MW_UI_LABEL_LARGE_X_OFFSET	2

/************
*** TYPES ***
************/

/**
 * Instance data structure for label ui component
 */
typedef struct
{
	/* User modifiable fields */
	char label[MW_UI_LABEL_MAX_CHARS + 1U];			/**< text of label */
  
	/* Non-user modifiable fields */
} mw_ui_label_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a label control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param width Width of label containing box
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param label_instance_data Instance structure containing label specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_label_add_new(int16_t x,
		int16_t y,
		int16_t width,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_label_data_t *label_instance_data);

#ifdef __cplusplus
}
#endif

#endif
