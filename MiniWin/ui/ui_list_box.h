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

#include <miniwin.h>

/****************
*** CONSTANTS ***
****************/

#define MW_UI_LIST_BOX_LABEL_CHARACTERS		    10

#define MW_UI_LIST_BOX_ROW_HEIGHT				14
#define MW_UI_LIST_BOX_LABEL_Y_OFFSET			3
#define MW_UI_LIST_BOX_LABEL_X_OFFSET 			8
#define MW_UI_LIST_BOX_WIDTH				    68

#define MW_UI_LIST_BOX_LARGE_ROW_HEIGHT			28
#define MW_UI_LIST_BOX_LARGE_LABEL_Y_OFFSET		6
#define MW_UI_LIST_BOX_LARGE_LABEL_X_OFFSET 	8
#define MW_UI_LIST_BOX_LARGE_WIDTH				138

/************
*** TYPES ***
************/

/**
 * Extra data structure for list box ui component
 */
typedef struct
{
  /* User modifiable fields */   
	uint8_t number_of_lines;				/**< number of lines displayed in the list box */
	uint8_t number_of_items;				/**< number of items in the list box */
	char **list_box_labels;					/**< array of strings of labels shown to the right of each line */
	uint16_t line_enables;					/**< bit field of which lines are enabled/disabled; lsb is top line, 1 is enabled */

  /* Non-user modifiable fields */   
	uint8_t selection;						/**< the currently selected line */
	bool line_is_selected;					/**< a line is currently selected */
	uint16_t touch_down_y_position;			/**< the last down down position */
	uint8_t lines_to_scroll;				/**< the number of entries down to shart showing entries */
} mw_ui_list_box_data_t;

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
void mw_ui_list_box_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info);

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
void mw_ui_list_box_message_function(const mw_message_t *message);

/**
 * Add a list box control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param parent The containing window of this control
 * @param flags General control flags controlling the control
 * @param list_box_instance_data Instance structure containing list box specific data items
 */
uint8_t mw_ui_list_box_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_list_box_data_t *list_box_instance_data);

#ifdef __cplusplus
}
#endif

#endif
