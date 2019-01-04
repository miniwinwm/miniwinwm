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

#ifdef STM32F429xx

/***************
*** INCLUDES ***
***************/

#include "hal/hal_touch.h"
#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery_ts.h"
#include "stm32f429i_discovery_lcd.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
}

bool mw_hal_touch_is_calibration_required(void)
{
	return true;
}

bool mw_hal_touch_is_recalibration_required(void)
{
	/* if board button pressed clear settings which forces a screen recalibration */
	return BSP_PB_GetState(BUTTON_KEY);
}

mw_hal_touch_state_t mw_hal_touch_get_state()
{
	TS_StateTypeDef touch_state;

	BSP_TS_GetState(&touch_state);

	if (touch_state.TouchDetected)
	{
		return MW_HAL_TOUCH_STATE_DOWN;
	}

	return MW_HAL_TOUCH_STATE_UP;
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
	TS_StateTypeDef touch_state;

	if (BSP_TS_IsFifoEmpty())
	{
		return false;
	}

	BSP_TS_GetState(&touch_state);

	if (!touch_state.TouchDetected)
	{
		return false;
	}

	*x = touch_state.X;
	*y = touch_state.Y;

	return true;
}

#endif
