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

#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery.h"
#include "miniwin_settings.h"
#include "l3gd20.h"
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
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	HAL_Init();
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
	L3GD20_Init(0x00FF);
	L3GD20_RebootCmd();
}

void app_main_loop_process(void)
{
	BSP_LED_Toggle(LED4);
}

float *app_get_gyro_readings(void)
{
	static float cumulative_gyro_readings[3] = {0.0f, 0.0f, 0.0f};
	float latest_gyro_readings[3];
	uint8_t i;

	L3GD20_ReadXYZAngRate(latest_gyro_readings);
	cumulative_gyro_readings[GYRO_READING_X] += latest_gyro_readings[GYRO_READING_X] / 100000.0f;
	cumulative_gyro_readings[GYRO_READING_Y] += latest_gyro_readings[GYRO_READING_Y] / 100000.0f;
	cumulative_gyro_readings[GYRO_READING_Z] += latest_gyro_readings[GYRO_READING_Z] / 100000.0f;


	/* rationalize readings to 0 to 360 range */
	for (i = GYRO_READING_X; i <= GYRO_READING_Y; i++)
	{
		if (cumulative_gyro_readings[i] > 360.0f)
		{
			cumulative_gyro_readings[i] -= 360.0f;
		}
		else if (cumulative_gyro_readings[i] < 0.0f)
		{
			cumulative_gyro_readings[i] += 360.0f;
		}
	}

	return cumulative_gyro_readings;
}
