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

#ifdef RX65N

/***************
*** INCLUDES ***
***************/

#include "hal/hal_touch.h"
#include "r_gpio_rx_if.h"
#include "r_sci_iic_rx_if.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static sci_iic_info_t i2c_info;
static volatile bool busy = false;
static uint8_t i2c_buffer[7];
static uint16_t received_x;
static uint16_t received_y;
static uint8_t touch_controller_i2c_address[1] = {0x38U};
static uint8_t i2c_register_address[1];
static volatile bool touched = false;
static bool first_touch_received = false;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void touch_state_callback(void);
static void touch_position_callback(void);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
	/* gpio touch interrupt input */
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_2, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_0_PIN_2, GPIO_DIRECTION_INPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_2, GPIO_CMD_IN_PULL_UP_DISABLE);

	/* gpio touch reset output */
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_7, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_0_PIN_7, GPIO_DIRECTION_OUTPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_7, GPIO_CMD_OUT_CMOS);

	/* reset touch ic */
	R_GPIO_PinWrite(GPIO_PORT_0_PIN_7, GPIO_LEVEL_LOW);
	(void)R_BSP_SoftwareDelay(1U, BSP_DELAY_MILLISECS);
	R_GPIO_PinWrite(GPIO_PORT_0_PIN_7, GPIO_LEVEL_HIGH);

	i2c_info.ch_no = 6U;
	i2c_info.p_slv_adr    = touch_controller_i2c_address;
	i2c_info.dev_sts      = SCI_IIC_NO_INIT;

	/* set up callback for majority of touch hal layer calls */
	i2c_info.callbackfunc = &touch_position_callback;

	(void)R_SCI_IIC_Open(&i2c_info);
}

bool mw_hal_touch_is_recalibration_required(void)
{
	/* if board button pressed clear settings which forces a screen recalibration */
	if (R_GPIO_PinRead(GPIO_PORT_0_PIN_5) == GPIO_LEVEL_LOW)
	{
		return true;
	}

	return (false);
}

mw_hal_touch_state_t mw_hal_touch_get_state(void)
{
	/* touch sensor powers up thinking that there's a touch down so ignore this until touch interrupt
	 * line indicates a real first touch down */
	if (!first_touch_received)
	{
		if (R_GPIO_PinRead(GPIO_PORT_0_PIN_2) == GPIO_LEVEL_HIGH)
		{
			return MW_HAL_TOUCH_STATE_UP;
		}

		first_touch_received = true;
		return MW_HAL_TOUCH_STATE_DOWN;
	}

	/* touch interrupt line is unreliable so interrogate touch module for a touch down */
	i2c_info.callbackfunc = &touch_state_callback;
	i2c_register_address[0] = 2U;
	i2c_info.cnt1st = 1U;
	i2c_info.cnt2nd = 1U;
	i2c_info.p_data1st = i2c_register_address;
	i2c_info.p_data2nd = i2c_buffer;

	(void)R_SCI_IIC_MasterReceive(&i2c_info);
	busy = true;
	while (busy)
	{
	}

	/* set up address for majority of touch hal layer calls */
	i2c_info.callbackfunc = &touch_position_callback;

	if (touched)
	{
		return (MW_HAL_TOUCH_STATE_DOWN);
	}
	else
	{
		return (MW_HAL_TOUCH_STATE_UP);
	}
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
	/* touch sensor powers up thinking that there's a touch down so ignore this until touch interrupt
	 * line indicates a real first touch down */
	if (!first_touch_received)
	{
		if (R_GPIO_PinRead(GPIO_PORT_0_PIN_2) == GPIO_LEVEL_HIGH)
		{
			return false;
		}

		first_touch_received = true;
		return true;
	}

	i2c_register_address[0] = 2U;
	i2c_info.cnt1st = 1U;
	i2c_info.cnt2nd = 7U;
	i2c_info.p_data1st = i2c_register_address;
	i2c_info.p_data2nd = i2c_buffer;

	(void)R_SCI_IIC_MasterReceive(&i2c_info);
	busy = true;
	while (busy)
	{
	}

	if (!touched)
	{
		return false;
	}

	*x = received_x;
	*y = received_y;

	return (true);
}

static void touch_state_callback(void)
{
	if (i2c_buffer[0] > 0U)
	{
		touched = true;
	}
	else
	{
		touched = false;
	}
	busy = false;
}

static void touch_position_callback(void)
{
	if (i2c_buffer[0] > 0U)
	{
		received_x = ((uint16_t)(i2c_buffer[1]) & 0x000FU) << 8U | (uint16_t)i2c_buffer[2];
		received_y = ((uint16_t)(i2c_buffer[3]) & 0x000FU) << 8U | (uint16_t)i2c_buffer[4];
		touched = true;
	}
	else
	{
		touched = false;
	}

	busy = false;
}

#endif
