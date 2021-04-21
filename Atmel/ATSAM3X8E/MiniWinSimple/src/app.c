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

/***************
*** INCLUDES ***
***************/

#include <asf.h>
#include "app.h"

/****************
*** CONSTANTS ***
****************/

#define SPI_TOUCH_CLK_POLARITY					0						/**< Touch SPI clock polarity */
#define SPI_TOUCH_CLK_PHASE						1						/**< Touch SPI clock phase */
#define SPI_TOUCH_DLYBS							0x40
#define SPI_TOUCH_DLYBCT						0x10					
#define SPI_TOUCH_SPEED							1000000UL				/**< Touch SPI baud rate */

#define SPI_LCD_CLK_POLARITY					0						/**< LCD SPI clock polarity */
#define SPI_LCD_CLK_PHASE						1						/**< LCD SPI clock phase */
#define SPI_LCD_DLYBS							0x00
#define SPI_LCD_DLYBCT							0x00
#define SPI_LCD_SPEED							32000000UL				/**< LCD SPI baud rate */

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

void app_init(void)
{
	/* initialize all modules */
	sysclk_init();
	board_init();
		
	/* configure touch t_irq pin */
	ioport_set_pin_dir(TOUCH_T_IRQ_PIN, IOPORT_DIR_INPUT);
	
	/* configure lcd DC & RESET pins */
	ioport_set_pin_dir(LCD_RESET_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_DC_PIN, IOPORT_DIR_OUTPUT);

	/* initialize SPI_LCD_TOUCH_BASE pins */
	(void)gpio_configure_pin(PIO_PA25_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	(void)gpio_configure_pin(PIO_PA26_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	(void)gpio_configure_pin(PIO_PA27_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	
	/* initialise touch CS/ pin */
	(void)gpio_configure_pin(PIO_PA28_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	
	/* initialise LCD CS/ pin */
	(void)gpio_configure_pin(PIO_PA29_IDX, PIO_PERIPH_A | PIO_DEFAULT);
	
	/* initialise SPI_LCD_TOUCH_BASE device */
	spi_enable_clock(SPI_LCD_TOUCH_BASE);
	spi_disable(SPI_LCD_TOUCH_BASE);
	spi_reset(SPI_LCD_TOUCH_BASE);
	spi_set_fixed_peripheral_select(SPI_LCD_TOUCH_BASE);
	spi_set_master_mode(SPI_LCD_TOUCH_BASE);
	spi_disable_mode_fault_detect(SPI_LCD_TOUCH_BASE);
	
	/* configure SPI when touch CS/ is active */
	spi_set_clock_polarity(SPI_LCD_TOUCH_BASE, SPI_TS_CHIP_SEL, SPI_TOUCH_CLK_POLARITY);
	spi_set_clock_phase(SPI_LCD_TOUCH_BASE, SPI_TS_CHIP_SEL, SPI_TOUCH_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_LCD_TOUCH_BASE, SPI_TS_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	(void)spi_set_baudrate_div(SPI_LCD_TOUCH_BASE, SPI_TS_CHIP_SEL, sysclk_get_peripheral_hz() / SPI_TOUCH_SPEED);
	spi_set_transfer_delay(SPI_LCD_TOUCH_BASE, SPI_TS_CHIP_SEL, SPI_TOUCH_DLYBS, SPI_TOUCH_DLYBCT);
	
	/* configure SPI when LCD CS/ is active */
	spi_set_clock_polarity(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_LCD_CLK_POLARITY);
	spi_set_clock_phase(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_LCD_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	(void)spi_set_baudrate_div(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, sysclk_get_peripheral_hz() / SPI_LCD_SPEED);
	spi_set_transfer_delay(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_LCD_DLYBS, SPI_LCD_DLYBCT);
		
	spi_enable(SPI_LCD_TOUCH_BASE);
}

void app_main_loop_process(void)
{
}

void spi_transfer(const uint8_t *tx_buf, uint8_t *rx_buf, size_t size)
{
	size_t i;

	size--;
	for (i = (size_t)0; i < size; i++)
	{
		spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
		while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
		{
		}
		rx_buf[i] = (uint8_t)spi_get(SPI_LCD_TOUCH_BASE);
	}
	
	spi_set_lastxfer(SPI_LCD_TOUCH_BASE);

	spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
	while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
	{
	}
	rx_buf[i] = (uint8_t)spi_get(SPI_LCD_TOUCH_BASE);
}

void spi_send(const uint8_t *tx_buf, size_t size)
{
	size_t i;

	size--;
	for (i = (size_t)0; i < size; i++)
	{
		spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
		while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
		{
		}
		(void)spi_get(SPI_LCD_TOUCH_BASE);
	}
	
	spi_set_lastxfer(SPI_LCD_TOUCH_BASE);

	spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
	while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
	{
	}
	(void)spi_get(SPI_LCD_TOUCH_BASE);
}


