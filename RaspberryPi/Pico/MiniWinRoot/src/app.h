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

#ifndef APP_H
#define APP_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

#define LCD_SPEED							32000000UL		/**< SPI clock speed for LCD */
#define TOUCH_SPEED							1000000UL		/**< SPI clock speed for touch controller */
#define TOUCH_T_IRQ_GPIO 					6				/**< GPIO for touch T_IRQ pin */
#define TOUCH_RECAL_GPIO					20				/**< GPIO for touch recal request button */
#define TOUCH_CS_GPIO						17				/**< GPIO for touch controller CS/ pin */
#define SPI0_MISO_GPIO						16				/**< GPIO for SPI0 MOSI pin */
#define SPI0_MOSI_GPIO						19				/**< GPIO for SPI0 MISO pin */
#define SPI0_CLK_GPIO						18				/**< GPIO for SPI0 CLK pin */
#define LED_GPIO 							25				/**< GPIO for on board LED */
#define LCD_RESET_GPIO 						15				/**< GPIO for LCD reset pin */
#define LCD_DC_GPIO 						14				/**< GPIO for LCD DC pin */
#define LCD_CS_GPIO 						13				/**< GPIO for LCD CS/ pin */
#define SPI_TOUCH_LCD_ID					spi0			/**< SPI module used for LCD and touch controller */

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

#ifdef __cplusplus
}
#endif

#endif
