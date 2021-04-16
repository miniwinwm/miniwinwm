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

#ifdef STM32F429xx

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"
#include "stm32f4xx_hal.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

volatile uint32_t mw_tick_counter;
TIM_HandleTypeDef Tim3Handle;

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

void mw_hal_timer_init(void)
{
	uint32_t uwPrescalerValue =  ((SystemCoreClock / 2U) / 10000U) - 1U;

	__HAL_RCC_TIM3_CLK_ENABLE();

	Tim3Handle.Instance = TIM3;
	Tim3Handle.Init.Period = (10000U / MW_TICKS_PER_SECOND) -1U;
	Tim3Handle.Init.Prescaler = uwPrescalerValue;
	Tim3Handle.Init.ClockDivision = 0U;
	Tim3Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	(void)HAL_TIM_Base_Init(&Tim3Handle);

	HAL_NVIC_SetPriority(TIM3_IRQn, 0U, 1U);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	(void)HAL_TIM_Base_Start_IT(&Tim3Handle);
}

void mw_hal_timer_fired(void)
{
	mw_tick_counter++;
}

#endif
