/*

MIT License

Copyright (c) John Blaiklock 2023 miniwin Embedded Window Manager

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

#ifdef _RENESAS_SYNERGY_

/***************
*** INCLUDES ***
***************/

#include "miniwin_thread.h"
#include "hal/hal_timer.h"
#include "miniwin_config.h"

/****************
*** CONSTANTS ***
****************/

#define LED_1                   IOPORT_PORT_06_PIN_00

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

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void g_miniwin_timer_callback(timer_callback_args_t *p_args)
{
    (void)p_args;

    mw_hal_timer_fired();
}

void mw_hal_timer_init(void)
{
    (void)g_miniwin_timer.p_api->open(g_miniwin_timer.p_ctrl, g_miniwin_timer.p_cfg);
}

void mw_hal_timer_fired(void)
{
    static bool led_state;

    led_state = !led_state;
    (void)g_ioport.p_api->pinWrite(LED_1, led_state ? IOPORT_LEVEL_HIGH : IOPORT_LEVEL_LOW);

	mw_tick_counter++;
}

#endif
