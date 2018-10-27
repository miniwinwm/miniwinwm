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

#ifndef _UI_KEYBOARD_H
#define _UI_KEYBOARD_H

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

#define MW_UI_KEYBOARD_KEY_SIZE				20
#define MW_UI_KEYBOARD_WIDTH				(MW_UI_KEYBOARD_KEY_SIZE * 11)
#define MW_UI_KEYBOARD_HEIGHT				(MW_UI_KEYBOARD_KEY_SIZE * 3)
#define MW_UI_KEYBOARD_KEY_TEXT_OFFSET		7
#define MW_UI_KEYBOARD_KEY_BITMAP_OFFSET	2
#define MW_UI_KEYBOARD_KEY_BITMAP_SIZE		16

/************
*** TYPES ***
************/

 typedef enum
 {
 	KEYBOARD_UPPER_CHARS,
 	KEYBOARD_LOWER_CHARS,
 	KEYBOARD_NUMBERS,
 	KEYBOARD_SYMBOLS
 } keyboard_display_t;

/**
 * Instance data structure for number chooser ui component
 */
typedef struct
{
  	/* User modifiable fields */ 
  
    /* Non-user modifiable fields */ 
	bool is_key_pressed;						/**< if a key is currently pressed */
	bool swap_keyboard;							/**< if the keyboard needs swapping on next key up timer event */
	uint8_t	key_pressed_row;					/**< the currently pressed key row */
	uint8_t	key_pressed_column;					/**< the currently pressed key column */
	keyboard_display_t keyboard_display;		/**< the keyboard to display */
	mw_handle_t timer_handle;					/**< timer handle for animations and hold down repeat timeout */
	uint32_t touch_down_time;					/**< time in ticks a key was first pressed down */
	bool holding_down;							/**< true when holding down a key */
} mw_ui_keyboard_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a keyboard control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param parent The containing window of this control
 * @param flags General control flags controlling the control
 * @param keyboard_instance_data Instance structure containing integer number chooser specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_keyboard_add_new(uint16_t x,
		uint16_t y,
		mw_handle_t parent,
		uint32_t flags,
		mw_ui_keyboard_data_t *keyboard_instance_data);

#ifdef __cplusplus
}
#endif

#endif
