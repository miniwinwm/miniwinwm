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

#include <stdlib.h>
#include <string.h>
#include "definitions.h" 
#include "miniwin.h"
#include "app.h"
#include "ff.h"
#include "spi_driver.h"

/****************
*** CONSTANTS ***
****************/

static const uint8_t days_in_months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static FATFS fatfs;
static FIL file_handle;
static mw_time_t mw_time_now;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void TMR3_InterruptSvcRoutine(uint32_t status, uintptr_t context)
{
    (void)status;
    (void)context;
    
    static uint8_t quarter_second;
    uint8_t days_in_month;
    
    quarter_second++;
    if (quarter_second == 8U)
    {
        /* whole second has elapsed */
        quarter_second = 0U;
        
        /* update internal clock value */
        mw_time_now.tm_sec++;
        if (mw_time_now.tm_sec == 60U)
        {
            mw_time_now.tm_sec = 0U;
            mw_time_now.tm_min ++;
            if (mw_time_now.tm_min == 60U)
            {
                mw_time_now.tm_min = 0U;
                mw_time_now.tm_hour++;
                if (mw_time_now.tm_hour == 24U)
                {
                    mw_time_now.tm_hour = 0U;
                    mw_time_now.tm_mday++;
                    days_in_month = days_in_months[mw_time_now.tm_mon];
                    if (mw_time_now.tm_mon == 2U)
                    {
                        if (mw_time_now.tm_year % 4U == 0U && mw_time_now.tm_year % 100U != 0U)
                        {
                            days_in_month++;
                        }
                    }
                    if (mw_time_now.tm_mday > days_in_month)
                    {
                        mw_time_now.tm_mday = 1U;
                        mw_time_now.tm_mon++;
                        if (mw_time_now.tm_mon > 12U)
                        {
                            mw_time_now.tm_mon = 1U;
                            mw_time_now.tm_year++;
                        }
                    }

                }
            }
        }
    }
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
    /* initialize all modules */
    SYS_Initialize(NULL);
    
    /* start the clock used for real time */
    TMR3_CallbackRegister(TMR3_InterruptSvcRoutine, (uintptr_t)NULL);
    TMR3_Start();    
    
    /* initialize SPI1 interface */
    SPI1_init();

    /* mount the file system */
    f_mount(&fatfs, "", 0U);    
}

void app_main_loop_process(void)
{
    /* maintain state machines of all polled MPLAB Harmony modules. */
    SYS_Tasks();
}


bool app_file_open(char *path_and_filename)
{
    bool result = false;

    if (f_open(&file_handle, path_and_filename, FA_READ) == FR_OK)
    {
	result = true;
    }

    return (result);
}

bool app_file_create(char *path_and_filename)
{
    bool result = false;

    if (f_open(&file_handle, path_and_filename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK)
    {
	result = true;
    }

    return (result);
}

uint32_t app_file_size(void)
{
    return ((uint32_t)f_size(&file_handle));
}

uint8_t app_file_getc(void)
{
    uint8_t byte;
    UINT bytes_read;

    (void)f_read(&file_handle, &byte, 1, &bytes_read);

    return (byte);
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
    UINT bytes_read;

    (void)f_read(&file_handle, buffer, count, &bytes_read);
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
    UINT bytes_written;

    (void)f_write(&file_handle, buffer, count, &bytes_written);
}

uint32_t app_file_seek(uint32_t position)
{
    return ((uint32_t)(f_lseek(&file_handle, position)));
}

void app_file_close(void)
{
    (void)f_close(&file_handle);
}

char *app_get_root_folder_path(void)
{
    static char root_folder_path[] = "0:/";

    return (root_folder_path);
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
            	/* it is a file. */
                list_box_settings_entries[i].icon = file_entry_icon;
            }
            i++;
            if (i == max_entries)
            {
            	break;
            }
        }
        (void)f_closedir(&folder);
    }

    /* replace terminating '/' */
    path[strlen(path)] = '/';

    return (i);
}

mw_time_t app_get_time_date(void)
{
    return mw_time_now;
}

void app_set_time_date(mw_time_t new_time)
{    
    TMR3_Stop();    
    mw_time_now = new_time;
    TMR3_Start();    
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
    fattime |= time_now.tm_sec / 2U;

    return ((DWORD)fattime);
}
