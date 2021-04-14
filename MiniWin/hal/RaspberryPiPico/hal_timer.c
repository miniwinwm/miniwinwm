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

#ifdef RASPBERRY_PI_PICO

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hal/hal_timer.h"
#include "miniwin_config.h"
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

volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

bool repeating_timer_callback(struct repeating_timer *t);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

bool repeating_timer_callback(struct repeating_timer *t) 
{
    static bool toggle;

    toggle = !toggle;
    gpio_put(LED_PIN, toggle);
    
    mw_hal_timer_fired();
    
    return true;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_timer_fired(void)
{
    mw_tick_counter++;
}

void mw_hal_timer_init(void)
{
    static struct repeating_timer timer;

    add_repeating_timer_ms(-(int32_t)(1000U / MW_TICKS_PER_SECOND), repeating_timer_callback, NULL, &timer);
}

#endif
