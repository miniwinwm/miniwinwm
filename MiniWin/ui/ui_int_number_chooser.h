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

#ifndef _UI_INT_NUMBER_CHOOSER_H
#define _UI_INT_NUMBER_CHOOSER_H

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

#define MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE			16
#define MW_UI_INT_NUMBER_CHOOSER_KEY_COUNT			14
#define MW_UI_INT_NUMBER_CHOOSER_WIDTH				(MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE * MW_UI_INT_NUMBER_CHOOSER_KEY_COUNT)
#define MW_UI_INT_NUMBER_CHOOSER_HEIGHT				(MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE * 2)
#define MW_UI_INT_NUMBER_CHOOSER_MAX_CHARS			10
#define MW_UI_INT_NUMBER_CHOOSER_KEY_TEXT_OFFSET	5
#define MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_OFFSET	1
#define MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_SIZE	(MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2)

/************
*** TYPES ***
************/

/**
 * Instance data structure for number chooser ui component
 */
typedef struct
{
 	/* User modifiable fields */  
    bool is_only_positive;    					/**< only a positive number can be entered */
	
	 /* Non-user modifiable fields */ 
  	char number_buffer[MW_UI_INT_NUMBER_CHOOSER_MAX_CHARS + 1];	/**< buffer holding number as text but not negative sign */
	bool is_negative;							/**< if the number is to be returned as negative */
	bool is_key_pressed;						/**< if a key is currently pressed */
	uint8_t	key_pressed_number;					/**< the currently pressed key */
	uint8_t timer_id;							/**< timer used for key presses and cursor */
	bool draw_cursor;							/**< if to draw cursor this timer tick or not */
	uint8_t cursor_position;					/**< current position of cursor */
} mw_ui_int_number_chooser_data_t;

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
 * @param int_number_chooser_instance_data Instance structure containing integer number chooser specific data items
 */
uint8_t mw_ui_int_number_chooser_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_int_number_chooser_data_t *int_number_chooser_instance_data);

#ifdef __cplusplus
}
#endif

#endif
