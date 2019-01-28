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

#ifndef UI_ARROW_H
#define UI_ARROW_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

/* standard control size settings */
#define MW_UI_ARROW_SIZE		15

/* large control size settings */
#define MW_UI_ARROW_LARGE_SIZE	30

/************
*** TYPES ***
************/

 typedef enum
 {
	 MW_UI_ARROW_UP = 0,
	 MW_UI_ARROW_RIGHT = 90,
	 MW_UI_ARROW_DOWN = 180,
	 MW_UI_ARROW_LEFT = 270
 } mw_ui_arrow_direction_t;

/**
 * Instance data structure for arrow ui component
 */
typedef struct
{
	/* User modifiable fields */
	mw_ui_arrow_direction_t mw_ui_arrow_direction;			/**< Direction of arrow */
  
	/* Non-user modifiable fields */
	bool arrow_down;										/**< Set when the arrow is down */
	mw_handle_t timer_handle;								/**< Used for animation and holding down */
	uint32_t touch_down_time;								/**< Time in ticks the arrow was first pressed down */
} mw_ui_arrow_data_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a button control to a window
 *
 * @param x The x coordinate of the control relative to parent window client area
 * @param y The y coordinate of the control relative to parent window client area
 * @param parent_handle The containing window of this control
 * @param flags General control flags controlling the control
 * @param button_instance_data Instance structure containing button specific data items
 * @return The new control's handle
 */
mw_handle_t mw_ui_arrow_add_new(int16_t x,
		int16_t y,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_arrow_data_t *button_instance_data);

#ifdef __cplusplus
}
#endif

#endif
