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

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include "miniwin.h"
#include "miniwin_debug.h"
#include "miniwin_settings.h"
#include "hal/hal_non_vol.h"

/****************
*** CONSTANTS ***
****************/

#define SETTINGS_INIT_FLAG	0xBADD10DEU      /**< Signature of the initialisation flag */

/************
*** TYPES ***
************/

/**
 * Structure defining the layout of settings held in non-vol storage
 */
typedef struct
{
	uint32_t		init_flag;              /**< flag to indicate that the settings in non-vol storage have been initialised */
	bool			is_calibrated;          /**< flag to indicate that the touch screen has been calibrated and the calibration matrix is valid */
	MATRIX			calibration_matrix;     /**< the touch screen calibration matrix */
} settings_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static settings_t settings;                  /**< Structure containing the settings in memory */

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_settings_load(void)
{
	mw_hal_non_vol_load((uint8_t *)&settings, sizeof(settings));
}

void mw_settings_save(void)
{
	mw_hal_non_vol_save((uint8_t *)&settings, sizeof(settings));
}

bool mw_settings_is_initialised(void)
{
	return (settings.init_flag == SETTINGS_INIT_FLAG);
}

void mw_settings_set_to_defaults(void)
{
	settings.init_flag = SETTINGS_INIT_FLAG;
	settings.is_calibrated = false;
}

bool mw_settings_is_calibrated(void)
{
	return (settings.is_calibrated);
}

void mw_settings_set_calibrated(bool calibrated)
{
	settings.is_calibrated = calibrated;
}

MATRIX *mw_settings_get_calibration_matrix(void)
{
	return (&settings.calibration_matrix);
}

void mw_settings_set_calibration_matrix(const MATRIX *new_calibration_matrix)
{
	MW_ASSERT(new_calibration_matrix, "Null pointer argument");

	(void)memcpy(&settings.calibration_matrix, new_calibration_matrix, sizeof(MATRIX));
}
