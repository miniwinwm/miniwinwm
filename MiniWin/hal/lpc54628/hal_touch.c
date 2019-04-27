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

#ifdef CPU_LPC54628J512ET180

/***************
*** INCLUDES ***
***************/

#include "fsl_i2c.h"
#include "fsl_ft5406.h"
#include "fsl_gpio.h"
#include "hal/hal_touch.h"
#include "hal/hal_delay.h"

/****************
*** CONSTANTS ***
****************/

#define I2C_MASTER_CLOCK_FREQUENCY 	12000000
#define I2C_MASTER_SLAVE_ADDR_7BIT 	0x7EU
#define APP_BOARD_USER_BUTTON_PORT 	1
#define APP_BOARD_USER_BUTTON_PIN	1

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

static ft5406_handle_t touch_handle;

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
    i2c_master_config_t masterConfig;

	/* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);

    /* initialize the I2C master peripheral */
    I2C_MasterGetDefaultConfig(&masterConfig);
    I2C_MasterInit(I2C2, &masterConfig, I2C_MASTER_CLOCK_FREQUENCY);

    /* initialize the touch controller */
    (void)FT5406_Init(&touch_handle, I2C2);

    /* give touch hardware time to settle to prevent false touch at startup */
    mw_hal_delay_ms(50U);
}

bool mw_hal_touch_is_recalibration_required(void)
{
	return (GPIO_PinRead(GPIO, APP_BOARD_USER_BUTTON_PORT, APP_BOARD_USER_BUTTON_PIN) == 0U);
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
    touch_event_t touch_event;
    int cursorPosX;
    int cursorPosY;

	(void)FT5406_GetSingleTouch(&touch_handle, &touch_event, &cursorPosX, &cursorPosY);

    if (touch_event == kTouch_Down || touch_event == kTouch_Contact)
	{
    	*y = (uint16_t)cursorPosX;
    	*x = (uint16_t)cursorPosY;

    	return (true);
	}

	return (false);
}

mw_hal_touch_state_t mw_hal_touch_get_state(void)
{
    touch_event_t touch_event;
    int cursorPosX;
    int cursorPosY;

    (void)FT5406_GetSingleTouch(&touch_handle, &touch_event, &cursorPosX, &cursorPosY);

    if (touch_event == kTouch_Down || touch_event == kTouch_Contact)
	{
		return (MW_HAL_TOUCH_STATE_DOWN);
	}

	return (MW_HAL_TOUCH_STATE_UP);
}

#endif
