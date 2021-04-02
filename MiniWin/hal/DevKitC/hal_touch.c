/*

MIT License

Copyright (c) John Blaiklock 2020 miniwin Embedded Window Manager

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

#ifdef DEVKITC

/***************
*** INCLUDES ***
***************/

#include "hal/hal_touch.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

/****************
*** CONSTANTS ***
****************/

#define MW_HAL_TOUCH_READ_POINTS_COUNT		10U						/**< Number of samples to take to reduce noise */
#define COMMAND_READ_X             			0xd0U					/**< Command to read X position from touch screen */
#define COMMAND_READ_Y             			0x90U					/**< Command to read Y position from touch screen */
#define PIN_NUM_CS_TOUCH  					17						/**< CS line of touch controller */
#define PIN_NUM_IRQ_TOUCH  					5						/**< IRQ line of touch controller */
#define PIN_NUM_RECALIBRATION				16						/**< Recalibration is required */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static spi_device_handle_t spi_device_handle_touch;
static spi_transaction_t spi_transaction;

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
    uint16_t x;
    uint16_t y;

    spi_device_interface_config_t spi_device_interface_config_touch =
    {
        .clock_speed_hz = 1000000,       			/* clock out Hz */
        .mode = 0,                                	/* SPI mode 0 */
        .spics_io_num = PIN_NUM_CS_TOUCH,           /* CS pin */
        .queue_size = 1,                          	/* we want to be able to queue 1 transaction at a time */
        .pre_cb = NULL
    };

    /* attach the touch controller to the SPI bus */
    spi_bus_add_device(HSPI_HOST, &spi_device_interface_config_touch, &spi_device_handle_touch);

    /* set up irq pin */
    gpio_set_direction(PIN_NUM_IRQ_TOUCH, GPIO_MODE_INPUT);

    /* set up recalibration required pin */
    gpio_set_pull_mode(PIN_NUM_RECALIBRATION, GPIO_PULLUP_ONLY);
    gpio_set_direction(PIN_NUM_RECALIBRATION, GPIO_MODE_INPUT);

    /* do a dummy read to get t_irq line enabled */
    (void)mw_hal_touch_get_point(&x, &y);
}

bool mw_hal_touch_is_recalibration_required(void)
{
	return gpio_get_level(PIN_NUM_RECALIBRATION) == 0;
}

mw_hal_touch_state_t mw_hal_touch_get_state()
{
	if (gpio_get_level(PIN_NUM_IRQ_TOUCH) == 0)
	{
		return (MW_HAL_TOUCH_STATE_DOWN);
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

	if (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
		return false;
	}

	spi_transaction.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
	spi_transaction.length = (size_t)(8 * 3);

	touch_count = 0U;
	do
	{
		spi_transaction.tx_data[0] = COMMAND_READ_X;
		spi_transaction.rxlength = (size_t)0;

		spi_device_polling_transmit(spi_device_handle_touch, &spi_transaction);
		x_raw = (uint16_t)spi_transaction.rx_data[1] << 8;
		x_raw |= (uint16_t)spi_transaction.rx_data[2];
		x_raw >>= 3;

		spi_transaction.tx_data[0] = COMMAND_READ_Y;
		spi_transaction.rxlength = (size_t)0;

		spi_device_polling_transmit(spi_device_handle_touch, &spi_transaction);
		y_raw = (uint16_t)spi_transaction.rx_data[1] << 8;
		y_raw |= (uint16_t)spi_transaction.rx_data[2];
		y_raw >>= 3;

		databuffer[0][touch_count] = x_raw;
		databuffer[1][touch_count] = y_raw;

		touch_count++;
	}
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN && touch_count < MW_HAL_TOUCH_READ_POINTS_COUNT);

	if (touch_count != MW_HAL_TOUCH_READ_POINTS_COUNT)
	{
		return (false);
	}

	do
	{
		sorted = true;
		for (i = 0U; i < touch_count - 1U; i++)
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
		for (i = 0U; i < touch_count - 1U; i++)
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
