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

#include <stdio.h>
#include <string.h>
#include "hal/RaspberryPiZeroW/bcm2835.h"
#include "miniwin.h"
#include "app.h"

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
	if (!bcm2835_init())
	{
		exit(1);
	}
	
	if (!bcm2835_spi_begin())
	{
		exit(1);
	}
	
    bcm2835_spi_set_speed_hz(SPI_LCD_SPEED);    
    bcm2835_spi_chipSelect(SPI_LCD_CS);        	
	
	bcm2835_gpio_fsel(GPIO_TOUCH_IRQ, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(GPIO_LCD_DC, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(GPIO_LCD_RESET, BCM2835_GPIO_FSEL_OUTP);	
	
	/* set the on board led0 trigger to none */
	system("sh -c \"echo none > /sys/class/leds/led0/trigger\"");
}

void app_main_loop_process(void)
{
	/* toggle the on board led0 state */
	static bool toggle = false;

	if (mw_is_init_complete())
	{
		if (toggle)
		{
			system("sh -c \"echo 1 > /sys/class/leds/led0/brightness\"");
		}
		else
		{
			system("sh -c \"echo 0 > /sys/class/leds/led0/brightness\"");
		}

		toggle = !toggle;
	}	
}

float *app_get_gyro_readings(void)
{
	static float gyro_angles[3] = {0.0f, 0.0f, 0.0f};

    gyro_angles[0] += 0.3f;
	gyro_angles[1] += 0.5f;
	gyro_angles[2] += 0.7f;

	return gyro_angles;
}
