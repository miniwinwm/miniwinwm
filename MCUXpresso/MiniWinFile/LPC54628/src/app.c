/*

MIT License

Copyright (c) John Blaiklock 2018 miniwin Embedded Window Manager

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

#include <time.h>
#include "fsl_rtc.h"
#include "miniwin.h"
#include "board.h"
#include "pin_mux.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint8_t mw_bitmaps_file_icon_small[];
extern const uint8_t mw_bitmaps_folder_icon_small[];

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
    /* enable the rtc 32k oscillator */
    SYSCON->RTCOSCCTRL |= SYSCON_RTCOSCCTRL_EN_MASK;

    BOARD_InitPins();
    BOARD_BootClockPLL220M();
    BOARD_InitSDRAM();

    /* init rtc */
    RTC_Init(RTC);
}

bool app_file_open(char *path_and_filename)
{
	bool result = false;
/*
	if (application_state == APPLICATION_START)
	{
		if (f_open(&file_handle, path_and_filename, FA_READ) == FR_OK)
		{
			result = true;
		}
	}
*/
	return result;
}

bool app_file_create(char *path_and_filename)
{
	bool result = false;
/*
	if (application_state == APPLICATION_START)
	{
		if (f_open(&file_handle, path_and_filename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK)
		{
			result = true;
		}
	}
*/
	return result;
}

uint32_t app_file_size(void)
{
	/*
	return (uint32_t)f_size(&file_handle);
	*/
	return 0;
}

uint8_t app_file_getc()
{
	/*
	uint8_t byte;
	UINT bytes_read;

	f_read(&file_handle, &byte, 1, &bytes_read);

	return byte;
	*/
	return 0;
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
	/*
	UINT bytes_read;

	f_read(&file_handle, buffer, count, &bytes_read);
*/
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
	/*
	UINT bytes_written;

	f_write (&file_handle, buffer, count, &bytes_written);
	*/
}

uint32_t app_file_seek(uint32_t position)
{
	/*
	return (uint32_t)(f_lseek(&file_handle, position));
	*/
	return 0;
}

void app_file_close(void)
{
	/*
	f_close(&file_handle);
	*/
}

char *app_get_root_folder_path(void)
{
	return "/";
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
#if 0
    FRESULT result;
    DIR folder;
    FILINFO file_info;
    UINT i = 0;

    /* strip off terminating '/' for FatFS folders */
    path[strlen(path) - 1] = '\0';

    result = f_opendir(&folder, path);                       /* Open the folder */
    if (result == FR_OK)
    {
        for (;;)
        {
            result = f_readdir(&folder, &file_info);                   /* Read a folder item */
            if (result != FR_OK || file_info.fname[0] == 0)
            {
            	break;  /* Break on error or end of folder */
            }

        	/* Ignore if it's a hidden or system entry*/
        	if ((file_info.fattrib & AM_HID) || (file_info.fattrib & AM_SYS))
        	{
        		continue;
        	}

        	/* ignore if not a folder and we want directories only */
        	if (folders_only && !(file_info.fattrib & AM_DIR))
        	{
        		continue;
        	}

            mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1, file_info.fname);
            if (file_info.fattrib & AM_DIR)
            {
            	/* It is a folder */
            	list_box_settings_entries[i].icon = folder_entry_icon;
            }
            else
            {
            	/* It is a file. */
                list_box_settings_entries[i].icon = file_entry_icon;
            }
            i++;
            if (i == max_entries)
            {
            	break;
            }
        }
        f_closedir(&folder);
    }

    /* replace terminating '/' */
    path[strlen(path)] = '/';

    return i;
#endif

    return 0;
}

struct tm app_get_time_date(void)
{
	struct tm stdlib_tm;
    rtc_datetime_t date;

    RTC_GetDatetime(RTC, &date);
    stdlib_tm.tm_year = date.year;
    stdlib_tm.tm_mon = date.month;
    stdlib_tm.tm_mday = date.day;
    stdlib_tm.tm_hour = date.hour;
    stdlib_tm.tm_min =  date.minute;
    stdlib_tm.tm_sec = date.second;

	return stdlib_tm;
}

void app_set_time_date(struct tm tm)
{
    rtc_datetime_t date;

    /* rtc time counter has to be stopped before setting the date & time */
    RTC_StopTimer(RTC);

    /* set rtc time */
    date.year = tm.tm_year;
    date.month = tm.tm_mon;
    date.day = tm.tm_mday;
    date.hour = tm.tm_hour;
    date.minute = tm.tm_min;
    date.second = 0;
    RTC_SetDatetime(RTC, &date);

    /* start the rtc time counter */
    RTC_StartTimer(RTC);
}

/*
DWORD get_fattime (void)
{
	DWORD fattime = 0;
	struct tm tm;

	tm = app_get_time_date();

	fattime = (tm.tm_year - 1980) << 25;
	fattime |= tm.tm_mon << 21;
	fattime |= tm.tm_mday << 16;
	fattime |= tm.tm_hour << 11;
	fattime |= tm.tm_min << 5;
	fattime |= tm.tm_sec / 2;

	return fattime;
}
*/
