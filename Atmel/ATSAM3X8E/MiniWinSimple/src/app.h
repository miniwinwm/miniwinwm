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

#ifndef APP_H
#define APP_H

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

#define SPI_LCD_TOUCH_BASE					SPI0					/**< SPI peripheral to use for touch/LCD */
#define SPI_LCD_CHIP_SEL					0						/**< LCD CS/ line on SPI0 */
#define SPI_TS_CHIP_SEL						1						/**< Touch screen CS/ line on SPI0 */
#define TOUCH_RECAL_PIN						PIO_PD0_IDX				/**< Pin for touch screen recalibration request */
#define TOUCH_T_IRQ_PIN						PIO_PD1_IDX				/**< Pin for touch T_IRQ/ line */
#define LCD_RESET_PIN						PIO_PD2_IDX				/**< Pin for LCD RESET line */
#define LCD_DC_PIN							PIO_PD3_IDX				/**< Pin for LCD DC line */

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
 * Function called from main to perform application initializations
 */
void app_init(void);

/**
 * Function called from main to perform application main loop processing
 */
void app_main_loop_process(void);

/**
 * Transfer data to/from SPI_LCD_TOUCH_BASE SPI device 
 *
 * @param tx_buf Buffer holding data to send
 * @param rx_buf Buffer to hold data received
 * @size Length of data in tx_buf
 * @note rx_buf must be at least size bytes long
 * @note The CS/ line must already be set                                                               
 */
void spi_transfer(const uint8_t *tx_buf, uint8_t *rx_buf, size_t size);

/**
 * Send data to SPI_LCD_TOUCH_BASE SPI device 
 *
 * @param tx_buf Buffer holding data to send
 * @size Length of data in tx_buf
 * @note The CS/ line must already be set                                                               
 */
void spi_send(const uint8_t *tx_buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif
