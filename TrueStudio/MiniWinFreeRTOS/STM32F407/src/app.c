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

#include <math.h>
#include <string.h>
#include "miniwin.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_accelerometer.h"
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

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void SystemClock_Config(void);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	 clocked below the maximum system frequency, to update the voltage scaling value
	 regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8U;
	RCC_OscInitStruct.PLL.PLLN = 336U;
	RCC_OscInitStruct.PLL.PLLP = 2U;
	RCC_OscInitStruct.PLL.PLLQ = 7U;
	(void)HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	(void)HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	(void)HAL_Init();
	SystemClock_Config();

	/* if board button pressed clear settings which forces a screen recalibration */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
	if (BSP_PB_GetState(BUTTON_KEY))
	{
		mw_settings_set_to_defaults();
		mw_settings_save();
	}

	/* initialise the leds */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	/* initialise the gyro */
	(void)BSP_ACCELERO_Init();
	(void)BSP_ACCELERO_Reset();
}

void app_main_loop_process(void)
{
	BSP_LED_Toggle(LED4);
}

float *app_get_gyro_readings(void)
{
	static float gyro_angles[3U] = {0};
	static int16_t gyro_accelerations[10U][3U];
	static uint8_t i;
	double average_accelerations[3U];
	uint8_t c;

	BSP_ACCELERO_GetXYZ(gyro_accelerations[i]);

	/* filter out readings cause by shocks rather than gravity */
	if (gyro_accelerations[i][GYRO_READING_X] > 1000.0f ||
			gyro_accelerations[i][GYRO_READING_Y] > 1000.0f ||
			gyro_accelerations[i][GYRO_READING_Z] > 1000.0f ||
			gyro_accelerations[i][GYRO_READING_X] < -1000.0f ||
			gyro_accelerations[i][GYRO_READING_Y] < -1000.0f ||
			gyro_accelerations[i][GYRO_READING_Z] < -1000.0f)
	{
		return gyro_angles;
	}

	i++;

	/* calculate average when have 10 readings */
	if (i == 10U)
	{
		i = 0U;

		/* zero sum */
		(void)memset(&average_accelerations, 0, sizeof(average_accelerations));

		/* sum 10 accelerations readings */
		for (c = 0U; c < 10U; c++)
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

	return (gyro_angles);
}
