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
#include "hal/hal_touch.h"  
//#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

#define MW_HAL_TOUCH_READ_POINTS_COUNT		10U						/**< Number of samples to take to reduce noise */
#define COMMAND_READ_X             			0xd0U					/**< Command to read X position from touch screen */
#define COMMAND_READ_Y             			0x90U					/**< Command to read Y position from touch screen */

#define SPI_TS_CHIP_SEL			0
#define SPI_LCD_CHIP_SEL			1

#define SPI_MASTER_BASE			SPI0
#define SPI_CLK_POLARITY		0
#define SPI_CLK_PHASE			0
#define SPI_DLYBS				0x40
#define SPI_DLYBCT				0x10
static uint32_t gs_ul_spi_clock = 1000000;

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

static void spi_master_transfer(uint8_t *tx_buf, uint8_t *rx_buf, size_t size);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void spi_master_transfer(uint8_t *tx_buf, uint8_t *rx_buf, size_t size)
{
	size_t i;

	size--;
	for (i = (size_t)0; i < size; i++)
	{
		spi_put(SPI_MASTER_BASE, (uint16_t)tx_buf[i]);
		while ((spi_read_status(SPI_MASTER_BASE) & SPI_SR_RDRF) == 0U)
		{
		}
		rx_buf[i] = (uint8_t)spi_get(SPI_MASTER_BASE);
	}
	
	spi_set_lastxfer(SPI_MASTER_BASE);

	spi_put(SPI_MASTER_BASE, (uint16_t)tx_buf[i]);
	while ((spi_read_status(SPI_MASTER_BASE) & SPI_SR_RDRF) == 0U)
	{
	}
	rx_buf[i] = (uint8_t)spi_get(SPI_MASTER_BASE);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
	/* t_irq pin */
	ioport_set_pin_dir(PIO_PD1_IDX, IOPORT_DIR_INPUT);	
	
	(void)gpio_configure_pin(PIO_PA25_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	(void)gpio_configure_pin(PIO_PA26_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	(void)gpio_configure_pin(PIO_PA27_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	(void)gpio_configure_pin(PIO_PA28_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	(void)gpio_configure_pin(PIO_PA29_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	
	spi_enable_clock(SPI_MASTER_BASE);
	spi_disable(SPI_MASTER_BASE);
	spi_reset(SPI_MASTER_BASE);
	spi_set_fixed_peripheral_select(SPI_MASTER_BASE);
	spi_set_master_mode(SPI_MASTER_BASE);
	spi_disable_mode_fault_detect(SPI_MASTER_BASE);
	spi_set_peripheral_chip_select_value(SPI_MASTER_BASE, spi_get_pcs(SPI_LCD_CHIP_SEL));
	spi_set_clock_polarity(SPI_MASTER_BASE, SPI_TS_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_MASTER_BASE, SPI_TS_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_MASTER_BASE, SPI_TS_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	(void)spi_set_baudrate_div(SPI_MASTER_BASE, SPI_TS_CHIP_SEL, (sysclk_get_peripheral_hz() / gs_ul_spi_clock));
	spi_set_transfer_delay(SPI_MASTER_BASE, SPI_TS_CHIP_SEL, SPI_DLYBS, SPI_DLYBCT);
	spi_enable(SPI_MASTER_BASE);	
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
	if (!ioport_get_pin_level(PIO_PD1_IDX))
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
	
	spi_set_peripheral_chip_select_value(SPI_MASTER_BASE, spi_get_pcs(SPI_TS_CHIP_SEL));
	
	touch_count = 0U;
	do
	{
		ts_command[0] = COMMAND_READ_X;
		spi_master_transfer(ts_command, ts_response, sizeof(ts_response));
		x_raw = (uint16_t)ts_response[1] << 8;
		x_raw |= (uint16_t)ts_response[2];
		x_raw >>= 3;

		ts_command[0] = COMMAND_READ_Y;
		spi_master_transfer(ts_command, ts_response, sizeof(ts_response));
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
