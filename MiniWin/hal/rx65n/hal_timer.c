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

#ifdef RX65N

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"
#include "hal/hal_timer.h"
#include "r_cmt_rx_if.h"
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

volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static inline void timer_fired(void *unused);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static inline void timer_fired(void *unused)
{
	mw_hal_timer_fired();
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_timer_init(void)
{
	uint32_t channel;

	(void)R_CMT_CreatePeriodic(20, &timer_fired, &channel);
}

void mw_hal_timer_fired(void)
{
	mw_tick_counter++;

	if ((mw_tick_counter & 0x00000001U) == 0x00000001U)
	{
		R_GPIO_PinWrite(GPIO_PORT_7_PIN_0, GPIO_LEVEL_LOW);
	}
	else
	{
		R_GPIO_PinWrite(GPIO_PORT_7_PIN_0, GPIO_LEVEL_HIGH);
	}
}

#endif
