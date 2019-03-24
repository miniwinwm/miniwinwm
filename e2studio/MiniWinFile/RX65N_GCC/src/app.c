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
#include "hal/hal_delay.h"
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

static int bcd_to_dec(uint8_t value);
static uint8_t dec_to_bcd(uint8_t value);

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void system_clock_config(void);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static int bcd_to_dec(uint8_t value)
{
    return (int)((((value & 0xf0U) >> 4) * 10U) + (value & 0x0fU));
}

static uint8_t dec_to_bcd(uint8_t value)
{
    return (((value / 10U) << 4) & 0xf0U) | (value % 10U);
}

/**
 * Configure the system and peripheral clocks
 */
static void system_clock_config(void)
{
	/* enable all protect register bits */
	SYSTEM.PRCR.WORD = 0xA50B;

	/* forcibly oscillate the main clock */
	SYSTEM.MOFCR.BIT.MOFXIN = 0U;

	/* select resonator as main clock source */
	SYSTEM.MOFCR.BIT.MOSEL = 0;

	/* stop the HOCO, not using it */
	SYSTEM.HOCOCR.BIT.HCSTP = 1U;

	/* disable the sub-clock as no crystal input on hw */
	RTC.RCR3.BIT.RTCEN = 0;

	/* not using USB clock */
	SYSTEM.SCKCR2.WORD = 0x0001U;

	/* set drive level for 12MHz input */
	SYSTEM.MOFCR.BIT.MODRV2 = 2U;

	/* set wait time for starting main clock oscillator */
	SYSTEM.MOSCWTCR.BYTE = 0x53;

	/* start main clock oscillator */
	SYSTEM.MOSCCR.BIT.MOSTP = 0U;

	/* set rom wait state appropriate to main clock speed */
	SYSTEM.ROMWT.BIT.ROMWT = 2U;

	/* set PLL division to 1 */
	SYSTEM.PLLCR.BIT.PLIDIV = 0U;

	/* set PLL multiplication to 20 */
	SYSTEM.PLLCR.BIT.STC = 39U;

	/* start the PLL */
	SYSTEM.PLLCR2.BIT.PLLEN = 0U;

	/* wait for clock stabilization */
	while (0 == SYSTEM.OSCOVFSR.BIT.PLOVF)
	{
		__asm("NOP");
	}

	/* ICLK to 120MHz */
	SYSTEM.SCKCR.BIT.ICK = 1U;

	/* FCLK to 60 MHz */
	SYSTEM.SCKCR.BIT.FCK = 2U;

	/* PCLKA to 120MHz */
	SYSTEM.SCKCR.BIT.PCKA = 1U;

	/* PCLKB to 60MHz */
	SYSTEM.SCKCR.BIT.PCKB = 2U;

	/* PCLKC to 60MHz */
	SYSTEM.SCKCR.BIT.PCKC = 2U;

	/* PCLKD to 60MHz */
	SYSTEM.SCKCR.BIT.PCKD = 2U;

	/* SDCLK not used */
	SYSTEM.SCKCR.BIT.PSTOP0 = 1U;

	/* BCLK not used */
	SYSTEM.SCKCR.BIT.PSTOP1 = 1U;

	/* switch main clock source to PLL */
	SYSTEM.SCKCR3.BIT.CKSEL = 4U;

	/* stop LOCO as finished with it now */
	SYSTEM.LOCOCR.BYTE = 1U;

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

	/* set up led gpio output */
	PORT7.PMR.BIT.B0 = 0U;	/* mode to gpio */
	PORT7.ODR0.BIT.B0 = 0U;	/* cmos output type */
	PORT7.PDR.BIT.B0 = 1U;	/* output */

	/* configure the rtc */

	/* select main clock as source */
	RTC.RCR4.BIT.RCKSEL = 1U;

	/* delay 6 clock cycles */
	mw_hal_delay_us(1U);

	/* stop clock */
	RTC.RCR2.BIT.START = 0U;
	while (RTC.RCR2.BIT.START != 0U)
	{
		__asm("NOP");
	}

	/* set divider */
	RTC.RFRH.WORD = 1U;
	RTC.RFRL.WORD = 0x6e35U;

	/* select count mode to calendar */
	RTC.RCR2.BIT.CNTMD = 0U;

	/* reset RTC */
	RTC.RCR2.BIT.RESET = 1U;
	while (RTC.RCR2.BIT.RESET != 0U)
	{
		__asm("NOP");
	}

	/* set rtc carry interrupt to software configurable interrupt 176 */
    ICU.SLIBR176.BYTE = 49U;

    /* disable all rtc interrupts */
    IEN(RTC, PRD) = 0U;
    IEN(RTC, ALM) = 0U;
    IEN(PERIB, INTB176) = 0U;
}

void app_main_loop_process(void)
{
}

uint8_t find_folder_entries(char *path,
		mw_ui_list_box_entry *list_box_settings_entries,
		bool folders_only,
		uint8_t max_entries,
		const uint8_t *file_entry_icon,
		const uint8_t *folder_entry_icon)
{
	return 0;
}

char *app_get_root_folder_path(void)
{
	return "";
}

bool app_file_open(char *path_and_filename)
{
	return false;
}

bool app_file_create(char *path_and_filename)
{
	return false;
}

uint32_t app_file_size(void)
{
	return 0U;
}

uint8_t app_file_getc(void)
{
	return 0U;
}

uint32_t app_file_seek(uint32_t position)
{
	return 0U;
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
}

void app_file_close(void)
{
}

mw_time_t app_get_time_date(void)
{
	static mw_time_t current_time = {0};


	uint16_t bcd_years;

	/* disable carry interrupt in icu */
	IEN(PERIB, INTB176) = 0U;

	/* enable carry interrupt in rtc */
	RTC.RCR1.BIT.CIE = 1U;

	do
	{
		/* clear carry flag in icu */
		IR(PERIB, INTB176) = 0U;

		/* get all the time/date parts */
		current_time.tm_sec  = bcd_to_dec(RTC.RSECCNT.BYTE & 0x7fU);
		current_time.tm_min  = bcd_to_dec(RTC.RMINCNT.BYTE & 0x7fU);
		current_time.tm_hour = bcd_to_dec(RTC.RHRCNT.BYTE & 0x3fU);
		current_time.tm_mday = bcd_to_dec(RTC.RDAYCNT.BYTE);
		current_time.tm_mon  = bcd_to_dec(RTC.RMONCNT.BYTE) + 1U;
		bcd_years = RTC.RYRCNT.WORD;
		current_time.tm_year = bcd_to_dec(bcd_years & 0xffU) + 2000U;
	}
	while (IR(PERIB, INTB176) == 1U); /* if carry occurs during read then read again*/

	return current_time;
}

void app_set_time_date(mw_time_t new_time)
{
	/* stop clock */
	RTC.RCR2.BIT.START = 0U;
	while (RTC.RCR2.BIT.START != 0U)
	{
		__asm("NOP");
	}

	/* reset RTC */
	RTC.RCR2.BIT.RESET = 1U;
	while (RTC.RCR2.BIT.RESET != 0U)
	{
		__asm("NOP");
	}

	/* set 24 hour mode */
    RTC.RCR2.BIT.HR24 = 1U;

    /* set all the time/date parts, waiting to confirm that the change has taken place in the rtc after each write */
	RTC.RSECCNT.BYTE = dec_to_bcd((uint8_t)new_time.tm_sec);
	while(RTC.RSECCNT.BYTE != dec_to_bcd((uint8_t)new_time.tm_sec))
	{
		__asm("NOP");
	}

	RTC.RMINCNT.BYTE = dec_to_bcd((uint8_t)new_time.tm_min);
	while(RTC.RMINCNT.BYTE != dec_to_bcd((uint8_t)new_time.tm_min))
	{
		__asm("NOP");
	}

	RTC.RHRCNT.BYTE = dec_to_bcd((uint8_t)new_time.tm_hour);
	while(RTC.RHRCNT.BYTE != dec_to_bcd((uint8_t)new_time.tm_hour))
	{
		__asm("NOP");
	}

	RTC.RDAYCNT.BYTE = dec_to_bcd((uint8_t)new_time.tm_mday);
	while(RTC.RDAYCNT.BYTE != dec_to_bcd((uint8_t)new_time.tm_mday))
	{
		__asm("NOP");
	}

	RTC.RMONCNT.BYTE = dec_to_bcd((uint8_t)new_time.tm_mon - 1U);
	while(RTC.RMONCNT.BYTE != dec_to_bcd((uint8_t)new_time.tm_mon - 1U))
	{
		__asm("NOP");
	}

    RTC.RYRCNT.WORD = (uint16_t)(dec_to_bcd((uint8_t)(new_time.tm_year - 2000U)));
	while(RTC.RYRCNT.WORD != (uint16_t)(dec_to_bcd((uint8_t)(new_time.tm_year - 2000U))))
	{
		__asm("NOP");
	}

	/* start clock */
	RTC.RCR2.BIT.START = 1U;
	while (RTC.RCR2.BIT.START != 1U)
	{
		__asm("NOP");
	}
}
