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

#include "miniwin.h"
#include "app.h"
#include "r_gpio_rx_if.h"
#include "r_rtc_rx_if.h"

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

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	rtc_init_t rtc_init;
	tm_t init_time = {0, 0, 0, 1, 0, 100, 0, 0, 0};

	// gpio led output
	(void)R_GPIO_PinControl(GPIO_PORT_7_PIN_0, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_7_PIN_0, GPIO_DIRECTION_OUTPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_7_PIN_0, GPIO_CMD_OUT_CMOS);

	// gpio button input
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_5, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_0_PIN_5, GPIO_DIRECTION_INPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_5, GPIO_CMD_IN_PULL_UP_DISABLE);

	rtc_init.output_freq = RTC_OUTPUT_OFF;
	rtc_init.periodic_freq = RTC_PERIODIC_OFF;
	rtc_init.periodic_priority = 0;
	rtc_init.set_time = true;
	rtc_init.p_callback = FIT_NO_FUNC;
	(void)R_RTC_Open(&rtc_init, &init_time);
}

void app_main_loop_process(void)
{
}

bool app_file_open(char *path_and_filename)
{
	return (false);
}

bool app_file_create(char *path_and_filename)
{
	return (false);
}

uint32_t app_file_size(void)
{
	return (0U);
}

uint8_t app_file_getc(void)
{
	return (0U);
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
}

uint32_t app_file_seek(uint32_t position)
{
	return (0U);
}

void app_file_close(void)
{
}

char *app_get_root_folder_path(void)
{
	static char root_folder_pathe[] = "/";

	return (root_folder_pathe);
}

uint8_t find_folder_entries(char *path,
		mw_ui_list_box_entry *list_box_settings_entries,
		bool folders_only,
		uint8_t max_entries,
		const uint8_t *file_entry_icon,
		const uint8_t *folder_entry_icon)
{
    return (0);
}

mw_time_t app_get_time_date(void)
{
	mw_time_t time_now;
	tm_t rtc_hw_time;

	(void)R_RTC_Read(&rtc_hw_time, NULL);

	time_now.tm_hour = (uint8_t)rtc_hw_time.tm_hour;
	time_now.tm_min = (uint8_t)rtc_hw_time.tm_min;
	time_now.tm_sec = (uint8_t)rtc_hw_time.tm_sec;
	time_now.tm_year = (uint16_t)rtc_hw_time.tm_year + 1900U;
	time_now.tm_mon = (uint8_t)rtc_hw_time.tm_mon + 1U;
	time_now.tm_mday = (uint8_t)rtc_hw_time.tm_mday;

	return (time_now);
}

void app_set_time_date(mw_time_t new_time)
{
	tm_t rtc_hw_time;

	rtc_hw_time.tm_sec = (int)new_time.tm_sec;
	rtc_hw_time.tm_min = (int)new_time.tm_min;
	rtc_hw_time.tm_hour = (int)new_time.tm_hour;
	rtc_hw_time.tm_mday = (int)new_time.tm_mday;
	rtc_hw_time.tm_mon = (int)new_time.tm_mon - 1;
	rtc_hw_time.tm_year = (int)new_time.tm_year - 1900;
	rtc_hw_time.tm_wday = 0;
	(void)R_RTC_Control(RTC_CMD_SET_CURRENT_TIME, &rtc_hw_time);
}
