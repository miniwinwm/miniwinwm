/*

MIT License

Copyright (c) John Blaiklock 2020 miniwin Embedded Window Manager

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

#ifdef DEVKITC

/***************
*** INCLUDES ***
***************/

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "hal/hal_timer.h"
#include "miniwin_config.h"

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

/**********************
*** LOCAL VARIABLES ***
**********************/

static TimerHandle_t timer;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void vTimerCallback(TimerHandle_t xTimer);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void vTimerCallback(TimerHandle_t xTimer)
{
	mw_tick_counter++;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_timer_init(void)
{
	timer = xTimerCreate("Timer", (TickType_t)(configTICK_RATE_HZ / MW_TICKS_PER_SECOND), pdTRUE, (void *)0, vTimerCallback);
	xTimerStart(timer, 0);
}

void mw_hal_timer_fired(void)
{
}

#endif
