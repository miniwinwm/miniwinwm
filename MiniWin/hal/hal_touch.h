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

#ifndef _HAL_TOUCH_H
#define _HAL_TOUCH_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Enumeration of touch states
 */
typedef enum
{
	MW_HAL_TOUCH_STATE_DOWN,       /**< the touch screen is currently being touched */
	MW_HAL_TOUCH_STATE_UP          /**< the touch screen is currently not being touched */
} mw_hal_touch_state_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Initialise the touch screen driver
 */
void mw_hal_touch_init(void);

/**
 * Get a touch screen touch up/down state
 *
 * @return One of mw_hal_touch_state_t.
 */
mw_hal_touch_state_t mw_hal_touch_get_state();

/**
 * Get a touch screen reading
 *
 * @param x The returned x coordinate as a raw digitiser reading
 * @param y The returned y coordinate as a raw digitiser reading
 * @return true if a successful touch down reading was made else false
 */
bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y);

#ifdef __cplusplus
}
#endif

#endif
