/*

MIT License

Copyright (c) John Blaiklock 2021 miniwin Embedded Window Manager

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

#ifdef PIC32MZ2048EFM100 

/***************
*** INCLUDES ***
***************/

#include "definitions.h"   
#include "hal/hal_timer.h"
#include "miniwin.h"

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

static void TMR2_InterruptSvcRoutine(uint32_t status, uintptr_t context);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void TMR2_InterruptSvcRoutine(uint32_t status, uintptr_t context)
{
    (void)status;
    (void)context;
    
    LED1_Toggle();
    mw_hal_timer_fired();
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_timer_init(void)
{
    TMR2_CallbackRegister(TMR2_InterruptSvcRoutine, (uintptr_t)NULL);
    TMR2_Start();
}

void mw_hal_timer_fired(void)
{
	mw_tick_counter++;
}

#endif
