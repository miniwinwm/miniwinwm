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

#ifndef DIALOG_DATE_CHOOSER_H
#define DIALOG_DATE_CHOOSER_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Create a dynamic date chooser dialog window.
 *
 * @param x Left coordinate of dialog window
 * @param y Top coordinate of dialog window
 * @param start_date_date Date of month of date to show on startup, 1 to 31
 * @param start_date_month Month of year of date to show on startup, 1 to 12
 * @param start_date_year Year of date to show on startup, 4 digit format
 * @param large_size true for large size controls/text, false for small
 * @param owner_window_handle Handle of the window that created this dialog and to which the response will be sent
 * @return The window handle of the window used for the dialog which is only valid while the dialog is showing
 * @note There must be space in the window array for one new window and space in the control array
 *       for one new control. These resources are released when the dialog is dismissed.
 *       The dialog is created modal and is brought to the front on showing.
 *       The dialog must fit entirely on the screen or else it will not be created.
 * @warning Do not call this from a client window paint function. In debug mode it will cause an assert failure.
 */
 mw_handle_t mw_create_window_dialog_date_chooser(int16_t x,
		int16_t y,
		uint8_t start_date_date,
		uint8_t start_date_month,
		uint16_t start_date_year,
		bool large_size,
		mw_handle_t owner_window_handle);

#ifdef __cplusplus
}
#endif

#endif
