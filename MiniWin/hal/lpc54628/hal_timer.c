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

#ifdef CPU_LPC54628J512ET180

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include "fsl_ctimer.h"
#include "fsl_gpio.h"
#include "hal/hal_timer.h"

/****************
*** CONSTANTS ***
****************/

#define APP_BOARD_TEST_LED_PORT 2U
#define APP_BOARD_TEST_LED_PIN 	2U

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

volatile uint32_t mw_tick_counter;

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

void mw_hal_timer_fired(void)
{
	mw_tick_counter++;
}


void mw_hal_timer_init(void)
{
    ctimer_config_t config;
    ctimer_match_config_t matchConfig;
    gpio_pin_config_t led_config =
    {
        kGPIO_DigitalOutput, 0U
    };

    GPIO_PortInit(GPIO, APP_BOARD_TEST_LED_PORT);
    GPIO_PinInit(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, &led_config);

    /* enable the asynchronous bridge */
    SYSCON->ASYNCAPBCTRL = 1U;

    /* use 12 MHz clock for some of the ctimers */
    CLOCK_AttachClk(kFRO12M_to_ASYNC_APB);

    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(CTIMER3, &config);

    matchConfig.enableCounterReset = true;
    matchConfig.enableCounterStop = false;
    matchConfig.matchValue = CLOCK_GetFreq(kCLOCK_AsyncApbClk) / 20U;
    matchConfig.outControl = kCTIMER_Output_NoAction;
    matchConfig.enableInterrupt = true;
    CTIMER_SetupMatch(CTIMER3, kCTIMER_Match_1, &matchConfig);
    CTIMER_StartTimer(CTIMER3);
}

void CTIMER3_IRQHandler(void)
{
    /* Clear any status flags that were set */
	uint32_t int_stat = CTIMER_GetStatusFlags(CTIMER3);
    CTIMER_ClearStatusFlags(CTIMER3, int_stat);

    mw_hal_timer_fired();

    GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1U << APP_BOARD_TEST_LED_PIN);
}

#endif
