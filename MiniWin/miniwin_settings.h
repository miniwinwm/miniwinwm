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

#ifndef MINWIN_SETTINGS_H
#define MINWIN_SETTINGS_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"
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
 * Save the settings data into non-volatile memory.
 */
void mw_settings_load(void);

/**
 * Load the settings data from non-volatile memory.
 */
void mw_settings_save(void);

/**
 * Return if the settings initialised flag is set.
 *
 * @return true if set else false
 */
bool mw_settings_is_initialised(void);

/**
 * Set all the settings in the memory copy of settings to their defaults. This does not affect or save the settings in non-vol storage.
 */
void mw_settings_set_to_defaults(void);

/**
 * Return if the settings touch screen calibrated flag is set.
 *
 * @return: true if set else false
 */
bool mw_settings_is_calibrated(void);

/**
 * Set the touch screen calibrated flag in the local memory copy of the settings. This does not affect or save the settings in non-vol storage.
 *
 * @param calibrated true if calibrated else false
 */
void mw_settings_set_calibrated(bool calibrated);

/**
 * Get a pointer to the touch screen calibration matrix.
 *
 * @return Pointer to the touch screen calibration matrix from memory. Settings must have been loaded from non-vol storage first.
 */
MATRIX_CAL *mw_settings_get_calibration_matrix(void);

/**
 * Set the touch screen calibration matrix in the local memory copy of the settings. This does not affect or save the settings in non-vol storage.
 *
 * @param new_calibration_matrix Pointer to a filled in touch screen calibration matrix. Ownership not taken.
 */
void mw_settings_set_calibration_matrix(const MATRIX_CAL *new_calibration_matrix);

#ifdef __cplusplus
}
#endif

#endif
