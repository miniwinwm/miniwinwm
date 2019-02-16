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

#ifndef UI_CHECK_BOX_H
#define UI_CHECK_BOX_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

#define MW_UI_CHECK_BOX_LABEL_MAX_CHARS			10U

#define MW_UI_CHECK_BOX_WIDTH					85
#define MW_UI_CHECK_BOX_HEIGHT					15
#define MW_UI_CHECK_BOX_LABEL_X_OFFSET			(MW_UI_CHECK_BOX_HEIGHT + 3)
#define MW_UI_CHECK_BOX_LABEL_Y_OFFSET			4

#define MW_UI_CHECK_BOX_LARGE_WIDTH				170
#define MW_UI_CHECK_BOX_LARGE_HEIGHT			30
#define MW_UI_CHECK_BOX_LARGE_LABEL_X_OFFSET	(MW_UI_CHECK_BOX_LARGE_HEIGHT + 7)
#define MW_UI_CHECK_BOX_LARGE_LABEL_Y_OFFSET	8

/************
*** TYPES ***
************/

/**
 * Instance data structure for checkbox ui component
 */
typedef struct
{
	/* User modifiable fields */
	char label[MW_UI_CHECK_BOX_LABEL_MAX_CHARS + 1U];	/**< text of label shown to right of check box */
  
	/* Non-user modifiable fields */
	bool checked;										/**< if the check box is checked */  
} mw_ui_check_box_data_t;

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a check box control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param check_box_instance_data Instance structure containing check box specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_check_box_add_new(int16_t x,
		int16_t y,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_check_box_data_t *check_box_instance_data);

#ifdef __cplusplus
}
#endif

#endif
