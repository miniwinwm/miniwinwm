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

#ifndef UI_TAB_H
#define UI_TAB_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

#define MW_UI_TABS_HEIGHT				16
#define MW_UI_TABS_CORNER_RADIUS		5
#define MW_UI_TABS_LARGE_HEIGHT			23
#define MW_UI_TABS_CORNER_LARGE_RADIUS	7
#define MW_UI_TABS_Y_OFFSET				2
#define MW_UI_TABS_LABEL_X_OFFSET		4
#define MW_UI_TABS_LABEL_Y_OFFSET		5

/************
*** TYPES ***
************/

/**
 * Instance data structure for tabs ui component
 */
typedef struct
{
	/* User modifiable fields */
	bool automatic;								/**< If tabs are automatic. Automatic tabs are always at the top of the
													 window and resize themselves to the full window client area width */
	char **tabs_labels;							/**< Array of strings of labels shown in each tab */
	int16_t number_of_tabs;						/**< Number of tabs */
	mw_hal_lcd_colour_t foreground_colour;		/**< The colour to fill the foreground area in with */
	mw_hal_lcd_colour_t background_colour;		/**< The colour to fill the background area in with */

	/* Non-user modifiable fields */
	uint8_t selection;							/**< The currently selected tab */
} mw_ui_tabs_data_t;

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a tabs control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area, ignored when automatic
 * @param y The y coordinate of the control relative to parent window client area, ignored when automatic
 * @param width The width of the control, ignored when automatic
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param tab_instance_data Instance structure containing tabs specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_tabs_add_new(int16_t x,
		int16_t y,
		int16_t width,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_tabs_data_t *tabs_instance_data);

/**
 * Get the currently selected tab of a tabs control
 *
 * @param tabs_handle Handle of the tab control to query
 * @return The currently selected tab (0 based) or 0 if tabs_handle does not refererence a tabs control
 */
uint8_t mw_ui_tabs_get_selection(mw_handle_t tabs_handle);

#ifdef __cplusplus
}
#endif

#endif
