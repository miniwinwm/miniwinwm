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

#ifdef STM32F407xx

/***************
*** INCLUDES ***
***************/

#include "stm32f4xx.h"
#include "hal/hal_delay.h"

/****************
*** CONSTANTS ***
****************/

#define TIMERCLOCK_SPEED_MHZ		84

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

void mw_hal_delay_init(void)
{
	TIM_HandleTypeDef Tim2Handle;

	__HAL_RCC_TIM2_CLK_ENABLE();

	Tim2Handle.Instance = TIM2;
	Tim2Handle.Init.Period = UINT16_MAX;
	Tim2Handle.Init.Prescaler = TIMERCLOCK_SPEED_MHZ - 1;
	Tim2Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim2Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&Tim2Handle);
	HAL_TIM_Base_Start(&Tim2Handle);
}

void mw_hal_delay_ms(uint16_t ms)
{
	uint16_t i;

	for(i = 0; i < 1000; i++)
	{
		mw_hal_delay_us(ms);
	}
}

void mw_hal_delay_us(uint32_t us)
{
	TIM2->CNT = 0;
	while(TIM2->CNT <= us);
}

#endif
