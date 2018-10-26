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

#ifndef _UI_KEYPAD_H
#define _UI_KEYPAD_H

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

#define MW_UI_KEYPAD_KEY_SIZE			20
#define MW_UI_KEYPAD_KEY_LARGE_SIZE		40

/************
*** TYPES ***
************/

/**
 * Instance data structure for number chooser ui component
 */
typedef struct
{
 	/* User modifiable fields */  
    bool enable_negative;    					/**< if to enable negative sign */
	
	 /* Non-user modifiable fields */ 
	bool is_key_pressed;						/**< if a key is currently pressed */
	uint8_t	key_pressed_row;					/**< the currently pressed key */
	uint8_t	key_pressed_column;					/**< the currently pressed key */
	uint8_t key_size;							/**< size of individual key depending on if large size or standard size */
	mw_handle_t timer_handle;					/**< timer handle for animations and hold down repeat timeout */
	uint32_t touch_down_time;					/**< time in ticks a key was first pressed down */
	bool holding_down;							/**< true when holding down a key */
} mw_ui_keypad_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add an integer number chooser control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param parent The containing window of this control
 * @param flags General control flags controlling the control
 * @param keypad_instance_data Instance structure containing integer number chooser specific data items
 */
uint8_t mw_ui_keypad_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_keypad_data_t *keypad_instance_data);

#ifdef __cplusplus
}
#endif

#endif
