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

#ifndef HAL_NON_VOL_H
#define HAL_NON_VOL_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>

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
 * Initialise the non-vol driver
 */
void mw_hal_non_vol_init(void);

/**
 * Load length bytes from non-volatile memory into buffer pointed to by data
 *
 * @param data An allocated memory buffer of at least length bytes
 * @param length The number of bytes to load
 */
void mw_hal_non_vol_load(uint8_t *data, uint16_t length);

/**
 * Save length bytes into non-volatile memory from buffer pointed to by data
 *
 * @param data A pointer to the buffer containing the data to save
 * @param length The number of bytes to save
 */
void mw_hal_non_vol_save(uint8_t *data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif
