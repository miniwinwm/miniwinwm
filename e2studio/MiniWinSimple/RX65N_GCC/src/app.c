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

/***************
*** INCLUDES ***
***************/

#include <iodefine.h>
#include "miniwin.h"
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

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void system_clock_config(void);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

//todo dox
static void system_clock_config(void)
{
	/* enable all protect register bits */
	SYSTEM.PRCR.WORD = 0xA50B;

	SYSTEM.MOFCR.BIT.MOFXIN = 0;
	SYSTEM.MOFCR.BIT.MOSEL = 0;
	if (1 == SYSTEM.HOCOCR.BIT.HCSTP)
	{
		SYSTEM.HOCOPCR.BYTE = 0x01;
	}
	else
	{
		while(0 == SYSTEM.OSCOVFSR.BIT.HCOVF)
		{
			__asm("NOP");
		}
	}

	SYSTEM.MOFCR.BIT.MODRV2 = 2;
	SYSTEM.MOSCWTCR.BYTE = 0x53;
	SYSTEM.MOSCCR.BYTE = 0x00;
	if (0x00 ==  SYSTEM.MOSCCR.BYTE)
	{
		__asm("NOP");
	}

	while(0 == SYSTEM.OSCOVFSR.BIT.MOOVF)
	{
		__asm("NOP");
	}

	/* disable the sub-clock as no crystal input on hw */
	RTC.RCR3.BIT.RTCEN = 0;

	SYSTEM.PLLCR.BIT.PLIDIV = 0;

	/* select mian clock oscillator */
	SYSTEM.PLLCR.BIT.PLLSRCSEL = 0;

	SYSTEM.PLLCR.BIT.STC = ((uint8_t)((float)20 * 2.0)) - 1;

	/* set pll in operation */
	SYSTEM.PLLCR2.BYTE = 0x00;

	/* wait for clock stabilization */
	while (0 == SYSTEM.OSCOVFSR.BIT.PLOVF)
	{
		__asm("NOP");
	}
	SYSTEM.ROMWT.BYTE = 0x02;
	if (0x02 == SYSTEM.ROMWT.BYTE)
	{
		__asm("NOP");
	}

	SYSTEM.SCKCR.LONG = 0x31c22333;
	SYSTEM.SCKCR2.WORD = 0x0011;
	SYSTEM.SCKCR3.WORD = 0x0400;

	/* low speed oscillator is stopped */
	SYSTEM.LOCOCR.BYTE = 0x01;

	/* disable all protect register bits */
	SYSTEM.PRCR.WORD = 0xA500;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	system_clock_config();

	/* set up push button gpio input */
	PORT0.PMR.BIT.B5 = 0U;	/* mode to gpio */
	PORT0.PDR.BIT.B5 = 0U;	/* input */
	PORT0.PCR.BIT.B5 = 0U;  /* pull-up disable */

	/* set up push button gpio input */
	PORT7.PMR.BIT.B0 = 0U;	/* mode to gpio */
	PORT7.ODR1.BIT.B6 = 0U;	/* cmos output type */
	PORT7.PDR.BIT.B0 = 1U;	/* output */
}

void app_main_loop_process(void)
{
}
