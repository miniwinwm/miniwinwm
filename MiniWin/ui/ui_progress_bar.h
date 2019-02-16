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

#ifndef UI_PROGRESS_BAR_H
#define UI_PROGRESS_BAR_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

#define MW_PROGRESS_BAR_COLOUR				MW_HAL_LCD_BLUE

/************
*** TYPES ***
************/

/**
 * Instance data structure for label ui component
 */
typedef struct
{
	/* User modifiable fields */
	uint8_t progress_percent;				/**< The progress as a percentage */
  
	/* Non-user modifiable fields */
} mw_ui_progress_bar_data_t;

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a label control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param width Width of progress bar containing box
 * @param height Height of progress bar containing box
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param progress_bar_instance_data Instance structure containing progress bar specific data items
 * @note No account taken of the MW_CONTROL_FLAG_LARGE_SIZE flag as user sets required size of this control
 * @return The new control's handle
 */
mw_handle_t mw_ui_progress_bar_add_new(int16_t x,
		int16_t y,
		int16_t width,
		int16_t height,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_progress_bar_data_t *progress_bar_instance_data);

#ifdef __cplusplus
}
#endif

#endif
