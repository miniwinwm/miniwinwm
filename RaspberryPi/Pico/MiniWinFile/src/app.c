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

/***************
*** INCLUDES ***
***************/

#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"  
#include "ff.h"
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

static FATFS fatfs;
static FIL file_handle;

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
    /* Start on a sensible date */
    datetime_t t = {
            .year  = 2021,
            .month = 04,
            .day   = 14,
            .dotw  = 3, 
            .hour  = 17,
            .min   = 20,
            .sec   = 00
    };    
    
    rtc_init();
    rtc_set_datetime(&t);
    
    /* led setup */
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    /* spi touch/lcd setup */
    spi_init(SPI_ID, LCD_SPEED);
    gpio_set_function(SPI0_MISO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI0_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI0_MOSI_PIN, GPIO_FUNC_SPI);      
    
    /* touch setup */
    gpio_init(TOUCH_CS_PIN);
    gpio_set_dir(TOUCH_CS_PIN, GPIO_OUT);
    gpio_put(TOUCH_CS_PIN, 1);
    gpio_init(TOUCH_T_IRQ_PIN);
    gpio_set_dir(TOUCH_T_IRQ_PIN, GPIO_IN);    
    gpio_init(TOUCH_RECAL_PIN);
    gpio_set_dir(TOUCH_RECAL_PIN, GPIO_IN);   
    gpio_pull_up(TOUCH_RECAL_PIN);
    
    /* lcd setup */
    gpio_init(LCD_RESET_PIN);
    gpio_set_dir(LCD_RESET_PIN, GPIO_OUT);
    gpio_init(LCD_DC_PIN);
    gpio_set_dir(LCD_DC_PIN, GPIO_OUT);
    gpio_init(LCD_CS_PIN);
    gpio_set_dir(LCD_CS_PIN, GPIO_OUT);      
    gpio_put(LCD_CS_PIN, 1);
    
    /* spi SD setup */    
    spi_init(SPI_SD_ID, SD_SPEED);
    gpio_set_function(SPI1_MISO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI1_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI1_MOSI_PIN, GPIO_FUNC_SPI);  
    gpio_pull_up(SPI1_MISO_PIN);
    
    gpio_init(SD_CS_PIN);
    gpio_set_dir(SD_CS_PIN, GPIO_OUT);
    gpio_put(SD_CS_PIN, 1);
        
    /* mount the file system */
    f_mount(&fatfs, "", 0U);        
}

void app_main_loop_process(void)
{
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
    datetime_t t;
    mw_time_t time_now;
    
    rtc_get_datetime(&t);
    
    time_now.tm_year = t.year;
    time_now.tm_mon = t.month;
    time_now.tm_mday = t.day;
    time_now.tm_hour = t.hour;
    time_now.tm_min = t.min;
    time_now.tm_sec = t.sec;
            
    return time_now;
}

void app_set_time_date(mw_time_t new_time)
{        
    datetime_t t;
    
    t.year = new_time.tm_year;
    t.month = new_time.tm_mon;
    t.day = new_time.tm_mday;
    t.hour = new_time.tm_hour;
    t.min = new_time.tm_min;
    t.sec = new_time.tm_sec;
    t.dotw = 0;
    
    rtc_set_datetime(&t);
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
