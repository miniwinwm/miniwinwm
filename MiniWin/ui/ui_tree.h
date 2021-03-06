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

#ifndef UI_TREE_H
#define UI_TREE_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include "miniwin_tree_container.h"

/****************
*** CONSTANTS ***
****************/

#define MW_UI_TREE_ROW_HEIGHT				14
#define MW_UI_TREE_TOP_BORDER				3
#define MW_UI_TREE_LEFT_BORDER 				1
#define MW_UI_TREE_MIN_WIDTH			    12
#define MW_UI_TREE_ICON_SIZE				8

#define MW_UI_TREE_LARGE_ROW_HEIGHT			22
#define MW_UI_TREE_LARGE_TOP_BORDER			4
#define MW_UI_TREE_LARGE_LEFT_BORDER 		2
#define MW_UI_TREE_LARGE_MIN_WIDTH			24
#define MW_UI_TREE_LARGE_ICON_SIZE			16

/************
*** TYPES ***
************/

/**
 * Instance data structure for tree ui component
 */
typedef struct
{
	/* User modifiable fields */
	struct mw_tree_container_t tree_container;		/**< Tree container data structure containing the data of the tree */
	mw_handle_t root_handle;						/**< Handle of the root folder node */
	const uint8_t *folder_icon;						/**< Pointer to icon to show for folder or NULL if no icon needed */
	const uint8_t *file_icon;						/**< Pointer to icon to show for file or NULL if no icon needed */
	uint8_t number_of_lines;						/**< Number of lines displayed in the tree */

	/* Non-user modifiable fields */
	uint16_t lines_to_scroll;						/**< The number of entries down to start showing entries */
	uint16_t visible_children;						/**< Total number of children of all folders that are open */
	int16_t row_height;								/**< Height in pixels of a line on the display */
	uint16_t icon_size;								/**< Width and height of all icons used in control */
	int16_t row_left_border;						/**< Distance from left of row to start of contents */
	int16_t row_top_border;							/**< Distance from top of row to start of contents */
	mw_util_rect_t invalid_rect;					/**< Rect used for partial repainting of the control */
	mw_handle_t	node_to_animate;					/**< Node to draw down and then up when no node selection in tree is allowed */
} mw_ui_tree_data_t;

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a tree control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param width the width of the tree's box
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param tree_instance_data Instance structure containing tree specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_tree_add_new(int16_t x,
		int16_t y,
		int16_t width,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_tree_data_t *tree_instance_data);

#ifdef __cplusplus
}
#endif

#endif
