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

#include <stdint.h>

/****************
*** CONSTANTS ***
****************/

#define SPI_LCD_SPEED		32000000UL
#define SPI_LCD_CS			BCM2835_SPI_CS1
#define GPIO_LCD_DC			RPI_V2_GPIO_P1_38
#define GPIO_LCD_RESET		RPI_V2_GPIO_P1_40

#define SPI_TOUCH_SPEED		1000000UL
#define SPI_TOUCH_CS		BCM2835_SPI_CS0
#define GPIO_TOUCH_IRQ		RPI_V2_GPIO_P1_35

/************
*** TYPES ***
************/

typedef enum
 {
	 GYRO_READING_X = 0,
	 GYRO_READING_Y = 1,
	 GYRO_READING_Z = 2
 } gyro_reading_t;

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
 * Get the gyroscope accumulated readings
 *
 * @return The cumulative readings in degrees
 */
float *app_get_gyro_readings(void);

#ifdef __cplusplus
}
#endif

#endif
