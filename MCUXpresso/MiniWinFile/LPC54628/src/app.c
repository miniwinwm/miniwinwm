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
#include "ff.h"
#include "fsl_rtc.h"
#include "fsl_iocon.h"
#include "fsl_sd.h"
#include "fsl_sd_disk.h"
#include "miniwin.h"
#include "board.h"
#include "pin_mux.h"
#include "app.h"


#include <string.h>
#include "diskio.h"

/****************
*** CONSTANTS ***
****************/

#define BUFFER_SIZE (100U)

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

static FIL file_handle;
static FATFS g_fileSystem;

SDK_ALIGN(uint8_t g_bufferWrite[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
          MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));
SDK_ALIGN(uint8_t g_bufferRead[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
          MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));

static const sdmmchost_detect_card_t s_sdCardDetect =
{
    .cdType = BOARD_SD_DETECT_TYPE,
    .cdTimeOut_ms = (~0U),
};

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

//todo
static void Board_InitSdifUnusedDataPin(void);
static status_t sdcardWaitCardInsert(void);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static status_t sdcardWaitCardInsert(void)
{
    /* Save host information. */
    g_sd.host.base = SD_HOST_BASEADDR;
    g_sd.host.sourceClock_Hz = SD_HOST_CLK_FREQ;

    /* card detect type */
    g_sd.usrParam.cd = &s_sdCardDetect;

    /* SD host init function */
    if (SD_HostInit(&g_sd) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* power off card */
    SD_PowerOffCard(g_sd.host.base, g_sd.usrParam.pwr);

    /* wait card insert */
    if (SD_WaitCardDetectStatus(SD_HOST_BASEADDR, &s_sdCardDetect, true) == kStatus_Success)
    {
        /* power on the card */
        SD_PowerOnCard(g_sd.host.base, g_sd.usrParam.pwr);
    }
    else
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

void static Board_InitSdifUnusedDataPin(void)
{
    IOCON_PinMuxSet(IOCON, 4, 29,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[4] */
    IOCON_PinMuxSet(IOCON, 4, 30,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[5] */
    IOCON_PinMuxSet(IOCON, 4, 31,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[6] */
    IOCON_PinMuxSet(IOCON, 5, 0,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[7] */
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
    const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};

    /* enable the rtc 32k oscillator */
    SYSCON->RTCOSCCTRL |= SYSCON_RTCOSCCTRL_EN_MASK;

    BOARD_InitPins();
    BOARD_BootClockPLL220M();
    BOARD_InitSDRAM();

    /* init rtc */
    RTC_Init(RTC);




    /* attach main clock to SDIF */
    CLOCK_AttachClk(BOARD_SDIF_CLK_ATTACH);
    Board_InitSdifUnusedDataPin();

    /* need call this function to clear the halt bit in clock divider register */
    CLOCK_SetClkDiv(kCLOCK_DivSdioClk, (uint32_t)(SystemCoreClock / FSL_FEATURE_SDIF_MAX_SOURCE_CLOCK + 1U), true);

    if (sdcardWaitCardInsert() != kStatus_Success)
    {
        return;
    }

    if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
    {
        return;
    }

    f_chdrive((char const *)&driverNumberBuffer[0U]);
}

bool app_file_open(char *path_and_filename)
{
	bool result = false;

	// todo
//	if (application_state == APPLICATION_START)
	{
		if (f_open(&file_handle, path_and_filename, FA_READ) == FR_OK)
		{
			result = true;
		}
	}

	return result;
}

bool app_file_create(char *path_and_filename)
{
	bool result = false;
/* todo
	if (application_state == APPLICATION_START)*/
	{
		if (f_open(&file_handle, path_and_filename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK)
		{
			result = true;
		}
	}

	return result;
}

uint32_t app_file_size(void)
{
	return (uint32_t)f_size(&file_handle);
}

uint8_t app_file_getc()
{
	uint8_t byte;
	UINT bytes_read;

	f_read(&file_handle, &byte, 1, &bytes_read);

	return byte;
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
	UINT bytes_read;

	f_read(&file_handle, buffer, count, &bytes_read);
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
	UINT bytes_written;

	f_write (&file_handle, buffer, count, &bytes_written);
}

uint32_t app_file_seek(uint32_t position)
{
	return (uint32_t)(f_lseek(&file_handle, position));
}

void app_file_close(void)
{
	f_close(&file_handle);
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
