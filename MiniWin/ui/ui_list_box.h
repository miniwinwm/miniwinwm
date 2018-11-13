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

#ifndef UI_LIST_BOX_H
#define UI_LIST_BOX_H

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

#define MW_UI_LIST_BOX_ROW_HEIGHT				14
#define MW_UI_LIST_BOX_LABEL_Y_OFFSET			3
#define MW_UI_LIST_BOX_LABEL_X_OFFSET 			8
#define MW_UI_LIST_BOX_MIN_WIDTH			    12
#define MW_UI_LIST_BOX_ICON_SIZE				8

#define MW_UI_LIST_BOX_LARGE_ROW_HEIGHT			28
#define MW_UI_LIST_BOX_LARGE_LABEL_Y_OFFSET		6
#define MW_UI_LIST_BOX_LARGE_LABEL_X_OFFSET 	8
#define MW_UI_LIST_BOX_LARGE_MIN_WIDTH			24
#define MW_UI_LIST_BOX_LARGE_ICON_SIZE			16

#define MW_UI_LIST_BOX_MAX_ENTRIES				16

/************
*** TYPES ***
************/

 /**
  * List box entry text and icon structure containing details of each row
  */
 typedef struct
 {
	 char *label;			/**< The text to show on a list box line */
	 const uint8_t *icon;	/**< The icon to show on a list box line, or NULL if no icon */
 } mw_ui_list_box_entry;

/**
 * Instance data structure for list box ui component
 */
typedef struct
{
	/* User modifiable fields */
	uint8_t number_of_lines;						/**< Number of lines displayed in the list box */
	uint8_t number_of_items;						/**< Number of items in the list box */
	const mw_ui_list_box_entry *list_box_entries;	/**< Array of list box entries containing labels & icon pointers */
	uint16_t line_enables;							/**< Bit field of which lines are enabled/disabled; lsb is top line, 1 is enabled */

	/* Non-user modifiable fields */
	uint8_t selection;								/**< The currently selected line */
	bool line_is_selected;							/**< A line is currently selected */
	uint16_t touch_down_y_position;					/**< The last down down position */
	uint8_t lines_to_scroll;						/**< The number of entries down to start showing entries */
} mw_ui_list_box_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a list box control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param width the width of the list box
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param list_box_instance_data Instance structure containing list box specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_list_box_add_new(uint16_t x,
		uint16_t y,
		uint16_t width,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_list_box_data_t *list_box_instance_data);

#ifdef __cplusplus
}
#endif

#endif
