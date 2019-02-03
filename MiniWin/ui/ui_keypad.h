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

#ifndef _UI_KEYPAD_H
#define _UI_KEYPAD_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

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
    bool enable_negative;    					/**< If to enable negative sign */
	
	 /* Non-user modifiable fields */ 
	bool is_key_pressed;						/**< If a key is currently pressed */
	int16_t key_pressed_row;					/**< The currently pressed key */
	int16_t key_pressed_column;					/**< The currently pressed key */
	mw_util_rect_t invalid_rect;				/**< Rect used for partial repainting of the control */
	mw_handle_t timer_handle;					/**< Timer handle for animations and hold down repeat timeout */
	uint32_t touch_down_time;					/**< Time in ticks a key was first pressed down */
	bool holding_down;							/**< true when holding down a key */
	int16_t key_size;							/**< Size of individual key depending on if large size or standard size */
} mw_ui_keypad_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add an integer number chooser control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param keypad_instance_data Instance structure containing integer number chooser specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_keypad_add_new(int16_t x,
		int16_t y,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_keypad_data_t *keypad_instance_data);

#ifdef __cplusplus
}
#endif

#endif
