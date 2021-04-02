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

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"
#include "app.h"
#include "r_gpio_rx_if.h"

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
	// gpio led output
	(void)R_GPIO_PinControl(GPIO_PORT_7_PIN_0, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_7_PIN_0, GPIO_DIRECTION_OUTPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_7_PIN_0, GPIO_CMD_OUT_CMOS);

	// gpio button input
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_5, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_0_PIN_5, GPIO_DIRECTION_INPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_5, GPIO_CMD_IN_PULL_UP_DISABLE);
}

void app_main_loop_process(void)
{
}

float *app_get_gyro_readings(void)
{
	static float cumulative_gyro_readings[3U] = {0.0f, 0.0f, 0.0f};

	cumulative_gyro_readings[GYRO_READING_X] += 0.1f;
	cumulative_gyro_readings[GYRO_READING_Y] += 0.15f;
	cumulative_gyro_readings[GYRO_READING_Z] += 0.2f;

	return (cumulative_gyro_readings);
}
