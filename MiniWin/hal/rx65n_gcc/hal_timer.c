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

#ifdef RX65N_GCC

/***************
*** INCLUDES ***
***************/

#include <iodefine.h>
#include "miniwin.h"
#include "hal/hal_timer.h"

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

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_timer_init(void)
{
	/* set the protect register to write enable and key */
	SYSTEM.PRCR.WORD = 0xa502U;

	/* bring module out of stop state */
	MSTP(CMT0) = 0U;

	/* stop counter */
	CMT.CMSTR0.BIT.STR0 = 0U;

	/* set the match value */
	CMT0.CMCOR = 117900U / MW_TICKS_PER_SECOND;

	/* set the clock divider to 512 */
	CMT0.CMCR.BIT.CKS = 3U;

	/* enable interrupt on match */
	CMT0.CMCR.BIT.CMIE = 1U;

	/* clear counter. */
	CMT0.CMCNT = 0U;

	/* clear any previously pending interrupts */
	IR(CMT0, CMI0) = 0U;

	/* set interrupt priority */
	IPR(CMT0, CMI0) = 5U;

	/* enable compare match interrupt */
	IEN(CMT0, CMI0) = 1U;

	/* start counter. */
	CMT.CMSTR0.BIT.STR0 = 1U;

	/* set the protect register to write disable and key */
    SYSTEM.PRCR.WORD = 0xa500U;
}

void mw_hal_timer_fired(void)
{
	mw_tick_counter++;

	if ((mw_tick_counter & 0x00000001U) == 0x00000001U)
	{
		PORT7.PODR.BIT.B0 = 0U;
	}
	else
	{
		PORT7.PODR.BIT.B0 = 1U;
	}
}

#endif
