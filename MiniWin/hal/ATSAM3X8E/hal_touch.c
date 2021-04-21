/*

MIT License

Copyright (c) John Blaiklock 2021 miniwin Embedded Window Manager

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

#ifdef __SAM3X8E__

/***************
*** INCLUDES ***
***************/

#include <asf.h>
#include "app.h"
#include "hal/hal_touch.h"  

/****************
*** CONSTANTS ***
****************/

#define MW_HAL_TOUCH_READ_POINTS_COUNT		10U						/**< Number of samples to take to reduce noise */
#define COMMAND_READ_X             			0xd0U					/**< Command to read X position from touch screen */
#define COMMAND_READ_Y             			0x90U					/**< Command to read Y position from touch screen */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

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
}

bool mw_hal_touch_is_recalibration_required(void)
{
	/* if board button pressed clear settings which forces a screen recalibration */
   // if (S1_Get() == 0x01U)
   // {
   //     return false;
   // }
    
    return true;
}

mw_hal_touch_state_t mw_hal_touch_get_state()
{
	if (!ioport_get_pin_level(TOUCH_T_IRQ_PIN))
	{
		return(MW_HAL_TOUCH_STATE_DOWN);
	}

	return (MW_HAL_TOUCH_STATE_UP);
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
	uint8_t i;
	bool sorted;
	uint16_t swap_value;
	uint16_t x_raw;
	uint16_t y_raw;
	uint16_t databuffer[2][MW_HAL_TOUCH_READ_POINTS_COUNT];
	uint8_t touch_count;
	uint8_t ts_command[3] = {0};
	uint8_t ts_response[3];
	
	spi_set_peripheral_chip_select_value(SPI_LCD_TOUCH_BASE, spi_get_pcs(SPI_TS_CHIP_SEL));
	
	touch_count = 0U;
	do
	{
		ts_command[0] = COMMAND_READ_X;
		spi_transfer(ts_command, ts_response, sizeof(ts_response));
		x_raw = (uint16_t)ts_response[1] << 8;
		x_raw |= (uint16_t)ts_response[2];
		x_raw >>= 3;

		ts_command[0] = COMMAND_READ_Y;
		spi_transfer(ts_command, ts_response, sizeof(ts_response));
		y_raw = (uint16_t)ts_response[1] << 8;
		y_raw |= (uint16_t)ts_response[2];
		y_raw >>= 3;
		
		databuffer[0][touch_count] = x_raw;
		databuffer[1][touch_count] = y_raw;
		touch_count++;
	}
	while ((mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN) && (touch_count < MW_HAL_TOUCH_READ_POINTS_COUNT));

	if (touch_count != MW_HAL_TOUCH_READ_POINTS_COUNT)
	{
		return (false);
	}

	do
	{
		sorted = true;
		for (i = 0U; i < (touch_count - 1U); i++)
		{
			if (databuffer[0][i] > databuffer[0][i + 1U])
			{
				swap_value = databuffer[0][i + 1U];
				databuffer[0][i + 1U] = databuffer[0][i];
				databuffer[0][i] = swap_value;
				sorted = false;
			}
		}
	}
	while (!sorted);

	do
	{
		sorted = true;
		for (i = 0U; i < (touch_count - 1U); i++)
		{
			if (databuffer[1][i] > databuffer[1][i + 1U])
			{
				swap_value = databuffer[1][i + 1U];
				databuffer[1][i + 1U] = databuffer[1][i];
				databuffer[1][i] = swap_value;
				sorted = false;
			}
		}
	}
	while (!sorted);

	*x = (databuffer[0][4] + databuffer[0][5]) / 8U;
	*y = (databuffer[1][4] + databuffer[1][5]) / 8U;
	
	return (true);
}


#endif
