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

#ifndef UI_RADIO_BUTTON_H
#define UI_RADIO_BUTTON_H

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

#define MW_UI_RADIO_BUTTON_LABEL_CHARACTERS		10

#define MW_UI_RADIO_BUTTON_BOX_SIZE				15
#define MW_UI_RADIO_BUTTON_HEIGHT				(MW_UI_RADIO_BUTTON_BOX_SIZE + 3)
#define MW_UI_RADIO_BUTTON_LABEL_X_OFFSET		(MW_UI_RADIO_BUTTON_BOX_SIZE + 3)
#define MW_UI_RADIO_BUTTON_LABEL_Y_OFFSET		4

#define MW_UI_RADIO_BUTTON_LARGE_BOX_SIZE		30
#define MW_UI_RADIO_BUTTON_LARGE_HEIGHT			(MW_UI_RADIO_BUTTON_LARGE_BOX_SIZE + 7)
#define MW_UI_RADIO_BUTTON_LARGE_LABEL_X_OFFSET	(MW_UI_RADIO_BUTTON_LARGE_BOX_SIZE + 7)
#define MW_UI_RADIO_BUTTON_LARGE_LABEL_Y_OFFSET	8

/************
*** TYPES ***
************/

/**
 * Instance data structure for radio_button ui component
 */
typedef struct
{
  /* User modifiable fields */
	char **radio_button_labels;			/**< array of strings of labels shown to the right of each radio_button */
	uint8_t number_of_items;			/**< number of radio_buttons in the group */  

  /* Non-user modifiable fields */  
	uint8_t selected_radio_button;		/**< the currently selected radio_button */
} mw_ui_radio_button_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a radio button control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param width The width of the control including the labels
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param radio_button_instance_data Instance structure containing radio button specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_radio_button_add_new(uint16_t x,
		uint16_t y,
		uint16_t width,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_radio_button_data_t *radio_button_instance_data);

#ifdef __cplusplus
}
#endif

#endif
