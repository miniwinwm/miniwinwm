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

#ifndef MINWIN_TOUCH_H
#define MINWIN_TOUCH_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>
#include "hal/hal_touch.h"
#include "calibrate.h"

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
 * Get the raw touch screen pointhal_touch module and apply the calibration procedure transformation (if specified)
 * to get the touch coordinates in pixels.
 *
 * @param x Pointer to value to return the x coordinate in pixels
 * @param y Pointer to value to return the y coordinate in pixels
 * @return The touch up/down state
 */
mw_hal_touch_state_t mw_touch_get_display_touch(int16_t* x, int16_t* y);

/**
 * Run the touch screen calibration procedure. This plots 3 crosses on the screen that the user needs to touch.
 * The results are returned in the MATRIX structure which the caller then needs to store in non-vol memory.
 *
 * @param matrixPtr Pointer to a MATRIX structure calculated and subsequently used by the screen calibration module
 */
void mw_touch_calibrate(MATRIX_CAL *matrix);

#ifdef __cplusplus
}
#endif

#endif
