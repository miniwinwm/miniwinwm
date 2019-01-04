/*

MIT License

Copyright (c) John Blaiklock 2018 miniwin Embedded Window Manager

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

#include <math.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "miniwin.h"
#include "board.h"
#include "pin_mux.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

#define ACCELEROMETER_DEVICE_ADDRESS 	0x1d
#define CTRL_REG_1						0x2a
#define CTRL_REG_2						0x2b
#define OUT_X_MSB_REG					0X01
#define FREERTOS_LED_PORT 				3U
#define FREERTOS_LED_PIN	 			3U

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

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
    BOARD_InitPins();
    BOARD_BootClockPLL220M();
    BOARD_InitSDRAM();

    gpio_pin_config_t led_config =
    {
        kGPIO_DigitalOutput, 0
    };

    GPIO_PortInit(GPIO, FREERTOS_LED_PORT);
    GPIO_PinInit(GPIO, FREERTOS_LED_PORT, FREERTOS_LED_PIN, &led_config);
}

static void get_accelerometer_readings(float *readings)
{
	uint8_t acc_data[6];
	int16_t x_acc_raw;
	int16_t y_acc_raw;
	int16_t z_acc_raw;
	static bool initialized;

	if (!initialized)
	{
		/* The i2c bus used for the accelerometer in this project is shared with the display touch controller.
		 * The miniwin touch driver in the hal layer will ungate the clock and initialise the i2c driver
		 * shared by these peripherals so here just wait until miniwin reports that its initializations
		 * are complete.
		 */
		if (!mw_is_init_complete())
		{
			return;
		}

		/* i2c peripheral now initialised so send initialisation commands to the accelerometer chip */

		/* reset the chip and wait */
		BOARD_Accel_I2C_Send(ACCELEROMETER_DEVICE_ADDRESS, CTRL_REG_2, 1, 0x40);
		vTaskDelay(10);

		/* set high definition */
	    BOARD_Accel_I2C_Send(ACCELEROMETER_DEVICE_ADDRESS, CTRL_REG_2, 1, 0x02);

	    /* start readings */
	    BOARD_Accel_I2C_Send(ACCELEROMETER_DEVICE_ADDRESS, CTRL_REG_1, 1, 0x01);
	    initialized = true;
	    return;
	}

	BOARD_Accel_I2C_Receive(ACCELEROMETER_DEVICE_ADDRESS, OUT_X_MSB_REG, 1, acc_data, 6);

	x_acc_raw = (int16_t)(acc_data[0]) << 8 | (int16_t)(acc_data[1]) >> 4;
	y_acc_raw = (int16_t)(acc_data[2]) << 8 | (int16_t)(acc_data[3]) >> 4;
	z_acc_raw = (int16_t)(acc_data[4]) << 8 | (int16_t)(acc_data[5]) >> 4;

	readings[0] = ((float) x_acc_raw) / (16384.0f);
	readings[1] = ((float) y_acc_raw) / (16384.0f);
	readings[2] = ((float) z_acc_raw) / (16384.0f);
}

void app_main_loop_process(void)
{
    GPIO_PortToggle(GPIO, FREERTOS_LED_PORT, 1u << FREERTOS_LED_PIN);
}

float *app_get_gyro_readings(void)
{
	static float gyro_angles[3];
	static float gyro_accelerations[10][3];
	static uint8_t i;
	double average_accelerations[3];
	uint8_t c;

	get_accelerometer_readings(gyro_accelerations[i]);

	i++;

	/* calculate average when have 10 readings */
	if (i == 10)
	{
		i = 0;

		/* zero sum */
		memset(&average_accelerations, 0, sizeof(average_accelerations));

		/* sum 10 accelerations readings */
		for (c = 0; c < 10; c++)
		{
			average_accelerations[GYRO_READING_X] += gyro_accelerations[c][GYRO_READING_X];
			average_accelerations[GYRO_READING_Y] += gyro_accelerations[c][GYRO_READING_Y];
			average_accelerations[GYRO_READING_Z] += gyro_accelerations[c][GYRO_READING_Z];
		}

		/* calculate average */
		average_accelerations[GYRO_READING_X] /= 10.0;
		average_accelerations[GYRO_READING_Y] /= 10.0;
		average_accelerations[GYRO_READING_Z] /= 10.0;

		/* calculate x angle */
		gyro_angles[GYRO_READING_X] = M_PI + (float)(atan2(-average_accelerations[GYRO_READING_Y],
				-average_accelerations[GYRO_READING_Z]));

		/* calculate y angle */
		gyro_angles[GYRO_READING_Y] = (float)(atan2(average_accelerations[GYRO_READING_X],
				sqrt(average_accelerations[GYRO_READING_Y] *
				average_accelerations[GYRO_READING_Y] +
				average_accelerations[GYRO_READING_Z] *
				average_accelerations[GYRO_READING_Z])));

		/* convert angles to degrees */
		gyro_angles[GYRO_READING_X] *= (180.0f / M_PI);
		gyro_angles[GYRO_READING_Y] *= (180.0f / M_PI);
	}

	return gyro_angles;
}

