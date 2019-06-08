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

#include <string.h>
#include "ff.h"
#include "fsl_rtc.h"
#include "fsl_iocon.h"
#include "fsl_sd.h"
#include "fsl_sd_disk.h"
#include "board.h"
#include "pin_mux.h"
#include "app.h"
#include "diskio.h"

/****************
*** CONSTANTS ***
****************/

static const sdmmchost_detect_card_t s_sdCardDetect =
{
    .cdType = BOARD_SD_DETECT_TYPE,
    .cdTimeOut_ms = ~0U
};

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static FIL file_handle;
static FATFS file_system;
static TCHAR root_folder_path[] = {SDDISK + '0', ':', '/', '\0'};
static bool sd_card_mounted = false;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**
 * Initialize the unused SD card interface data pins 
 */
static void init_sdif_unused_data_pins(void);

/**
 * Check if the SD card is inserted 
 *
 * @return kStatus_Fail if the card is not inserted or its status cannot be found, kStatus_Success if the card is inserted
 * @note If an inserted card is found it is powered up by this function
 */
static status_t check_sd_card_inserted(void);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static status_t check_sd_card_inserted(void)
{
    /* save host information. */
    g_sd.host.base = SD_HOST_BASEADDR;
    g_sd.host.sourceClock_Hz = SD_HOST_CLK_FREQ;

    /* card detect type */
    g_sd.usrParam.cd = &s_sdCardDetect;

    /* SD host init function */
    if (SD_HostInit(&g_sd) != kStatus_Success)
    {
        return (kStatus_Fail);
    }

    /* power off card */
    SD_PowerOffCard(g_sd.host.base, g_sd.usrParam.pwr);

    /* wait for card insert */
    if (SD_WaitCardDetectStatus(SD_HOST_BASEADDR, &s_sdCardDetect, true) == kStatus_Success)
    {
        /* power on card */
        SD_PowerOnCard(g_sd.host.base, g_sd.usrParam.pwr);
    }
    else
    {
        return (kStatus_Fail);
    }

    return (kStatus_Success);
}

void static init_sdif_unused_data_pins(void)
{
    IOCON_PinMuxSet(IOCON, 4U, 29U,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[4] */
    IOCON_PinMuxSet(IOCON, 4U, 30U,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[5] */
    IOCON_PinMuxSet(IOCON, 4U, 31U,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[6] */
    IOCON_PinMuxSet(IOCON, 5U, 0U,
                    (IOCON_FUNC2 | IOCON_PIO_SLEW_MASK | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP)); /* sd data[7] */
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
    DIR folder;

    /* enable the rtc 32k oscillator */
    SYSCON->RTCOSCCTRL |= SYSCON_RTCOSCCTRL_EN_MASK;

    BOARD_InitPins();
    BOARD_BootClockPLL220M();
    BOARD_InitSDRAM();

    /* init rtc */
    RTC_Init(RTC);

    /* attach main clock to SDIF */
    CLOCK_AttachClk(BOARD_SDIF_CLK_ATTACH);
    init_sdif_unused_data_pins();

    /* clear the halt bit in clock divider register */
    CLOCK_SetClkDiv(kCLOCK_DivSdioClk, (uint32_t)(SystemCoreClock / FSL_FEATURE_SDIF_MAX_SOURCE_CLOCK + 1U), true);

    if (check_sd_card_inserted() != kStatus_Success)
    {
        return;
    }

    if (f_mount(&file_system, (const TCHAR *)root_folder_path, 0U))
    {
        return;
    }

    (void)f_chdrive((const TCHAR *)root_folder_path);

    /* first access to the file system is slow so do it here */
    (void)f_opendir(&folder, root_folder_path);
    (void)f_closedir(&folder);

    sd_card_mounted = true;
}

bool app_file_open(char *path_and_filename)
{
	bool result = false;

	if (sd_card_mounted)
	{
		if (f_open(&file_handle, (TCHAR *)path_and_filename, FA_READ) == FR_OK)
		{
			result = true;
		}
	}

	return (result);
}

bool app_file_create(char *path_and_filename)
{
	bool result = false;

	if (sd_card_mounted)
	{
		if (f_open(&file_handle, (TCHAR *)path_and_filename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK)
		{
			result = true;
		}
	}

	return (result);
}

uint32_t app_file_size(void)
{
	uint32_t size = 0U;

	if (sd_card_mounted)
	{
		size = (uint32_t)f_size(&file_handle);
	}

	return (size);
}

uint8_t app_file_getc(void)
{
	uint8_t byte = 0U;
	UINT bytes_read;

	if (sd_card_mounted)
	{
		(void)f_read(&file_handle, (void *)&byte, 1, (UINT *)&bytes_read);
	}

	return (byte);
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
	UINT bytes_read;

	if (sd_card_mounted)
	{
		(void)f_read(&file_handle, (void *)buffer, (UINT)count, (UINT *)&bytes_read);
	}
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
	UINT bytes_written;

	if (sd_card_mounted)
	{
		(void)f_write(&file_handle, (void *)buffer, (UINT)count, (UINT *)&bytes_written);
	}
}

uint32_t app_file_seek(uint32_t position)
{
	return ((uint32_t)(f_lseek(&file_handle, (FSIZE_t)position)));
}

void app_file_close(void)
{
	if (sd_card_mounted)
	{
		(void)f_close(&file_handle);
	}
}

char *app_get_root_folder_path(void)
{
	return (root_folder_path);
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
    UINT i = 0U;

	if (!sd_card_mounted)
	{
		return (0U);
	}

	/* check pointer parameter */
	if (path == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return (0U);
	}

	/* check path string not empty */
    if (strlen(path) == (size_t)0)
    {
    	return (0U);
    }

    /* strip off terminating '/' for FatFS folders */
    path[strlen(path) - 1U] = '\0';

    /* open the folder */
    result = f_opendir(&folder, path);
    if (result == FR_OK)
    {
        for (;;)
        {
            if (i == max_entries)
            {
            	break;
            }

        	/* read a folder item */
            result = f_readdir(&folder, &file_info);
            if (result != FR_OK || file_info.fname[0] == '\0')
            {
            	/* break on error or end of folder */
            	break;
            }

        	/* ignore if it's a hidden or system entry*/
        	if ((file_info.fattrib & (BYTE)AM_HID) == AM_HID || (file_info.fattrib & (BYTE)AM_SYS) == AM_SYS)
        	{
        		continue;
        	}

        	/* ignore if not a folder and we want directories only */
        	if (folders_only && (file_info.fattrib & (BYTE)AM_DIR) == (BYTE)0)
        	{
        		continue;
        	}

        	(void)mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1U, file_info.fname);
            if ((file_info.fattrib & (BYTE)AM_DIR) == (BYTE)AM_DIR)
            {
            	/* it is a folder */
            	list_box_settings_entries[i].icon = folder_entry_icon;
            }
            else
            {
            	/* it is a file */
                list_box_settings_entries[i].icon = file_entry_icon;
            }
            i++;
        }
        (void)f_closedir(&folder);
    }

    /* replace terminating '/' */
    path[strlen(path)] = '/';

    return (i);
}

void app_populate_tree_from_file_system(struct mw_tree_container_t *tree,
		mw_handle_t start_folder_handle)

{
    FRESULT result;
    DIR folder;
    FILINFO file_info;
    char path[MAX_FOLDER_AND_FILENAME_LENGTH];
	uint8_t node_flags;

	/* check pointer parameter */
	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

    mw_tree_container_get_node_path(tree, start_folder_handle, path, MAX_FOLDER_AND_FILENAME_LENGTH);

    if (strlen(path) == (size_t)0)
    {
    	return;
    }

    /* strip off terminating '/' for FatFS folders */
    path[strlen(path) - 1U] = '\0';

    /* open the folder */
    result = f_opendir(&folder, path);
    if (result == FR_OK)
    {
        for (;;)
        {
        	/* read a folder item */
            result = f_readdir(&folder, &file_info);
            if (result != FR_OK || file_info.fname[0] == '\0')
            {
            	/* break on error or end of folder */
            	break;
            }

        	/* ignore if it's a hidden or system entry*/
        	if ((file_info.fattrib & (BYTE)AM_HID) == AM_HID || (file_info.fattrib & (BYTE)AM_SYS) == AM_SYS)
        	{
        		continue;
        	}

        	node_flags = 0U;
            if ((file_info.fattrib & (BYTE)AM_DIR) == (BYTE)AM_DIR)
        	{
        		node_flags = MW_TREE_CONTAINER_NODE_IS_FOLDER;
        	}

        	(void)mw_tree_container_add_node(tree,
        			start_folder_handle,
					file_info.fname,
        			node_flags);

        }
        (void)f_closedir(&folder);
    }
}

mw_time_t app_get_time_date(void)
{
	mw_time_t time_now;
    rtc_datetime_t date;

    RTC_GetDatetime(RTC, &date);
    time_now.tm_year = date.year;
    time_now.tm_mon = date.month;
    time_now.tm_mday = date.day;
    time_now.tm_hour = date.hour;
    time_now.tm_min =  date.minute;
    time_now.tm_sec = date.second;

	return (time_now);
}

void app_set_time_date(mw_time_t new_time)
{
    rtc_datetime_t date;

    /* rtc time counter has to be stopped before setting the date & time */
    RTC_StopTimer(RTC);

    /* set rtc time */
    date.year = new_time.tm_year;
    date.month = new_time.tm_mon;
    date.day = new_time.tm_mday;
    date.hour = new_time.tm_hour;
    date.minute = new_time.tm_min;
    date.second = 0U;
    (void)RTC_SetDatetime(RTC, &date);

    /* start the rtc time counter */
    RTC_StartTimer(RTC);
}

DWORD get_fattime(void)
{
	uint32_t fattime = 0U;
	mw_time_t time_now;

	time_now = app_get_time_date();

	fattime = (time_now.tm_year - 1980U) << 25;
	fattime |= time_now.tm_mon << 21;
	fattime |= time_now.tm_mday << 16;
	fattime |= time_now.tm_hour << 11;
	fattime |= time_now.tm_min << 5;
	fattime |= time_now.tm_sec / 2;

	return ((DWORD)fattime);
}
