/*

MIT License

Copyright (c) John Blaiklock 2020 miniwin Embedded Window Manager

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
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"

/****************
*** CONSTANTS ***
****************/

#define PIN_NUM_MISO 	2			/**< SD card SPI MISO pin */
#define PIN_NUM_MOSI 	15			/**< SD catd SPI MOSI pin */
#define PIN_NUM_CLK  	14			/**< SD card SPI clock pin */
#define PIN_NUM_CS   	13			/**< SD card SPI chip select pin */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static FILE* f;						/**< Handle of the single file opened by the application at a time */

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
    sdmmc_card_t* card;

    sdmmc_host_t host = 
    {
		.flags = SDMMC_HOST_FLAG_SPI, 
		.slot = VSPI_HOST, 
		.max_freq_khz = SDMMC_FREQ_DEFAULT, 
		.io_voltage = 3.3f, 
		.init = &sdspi_host_init, 
		.set_bus_width = NULL, 
		.get_bus_width = NULL, 
		.set_bus_ddr_mode = NULL, 
		.set_card_clk = &sdspi_host_set_card_clk, 
		.do_transaction = &sdspi_host_do_transaction, 
		.deinit = &sdspi_host_deinit, 
		.io_int_enable = &sdspi_host_io_int_enable, 
		.io_int_wait = &sdspi_host_io_int_wait, 
		.command_timeout_ms = 0
    };
    
    sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
    slot_config.gpio_miso = PIN_NUM_MISO;
    slot_config.gpio_mosi = PIN_NUM_MOSI;
    slot_config.gpio_sck  = PIN_NUM_CLK;
    slot_config.gpio_cs   = PIN_NUM_CS;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = 
    {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    (void)esp_vfs_fat_sdmmc_mount("", &host, &slot_config, &mount_config, &card);
}

void app_main_loop_process(void)
{
	/* this is required to stop task watchdog timing out if it is enabled */
	vTaskDelay(1);
}

bool app_file_open(char *path_and_filename)
{
    f = fopen(path_and_filename, "r");
	
	return (f != NULL);
}

bool app_file_create(char *path_and_filename)
{
    f = fopen(path_and_filename, "w");
	
	return (f != NULL);
}

uint32_t app_file_size(void)
{
	long int size;
	
	(void)fseek(f, 0L, SEEK_END);   
	size = ftell(f);
		
	return ((uint32_t)size);
}

uint8_t app_file_getc(void)
{
	uint8_t c = (uint8_t)fgetc(f);
	
	return c;
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
	(void)fread(buffer, (size_t)1, (size_t)count, f);
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
	(void)fwrite(buffer, (size_t)1, (size_t)count, f);
}

uint32_t app_file_seek(uint32_t position)
{
	return fseek(f, (long int)position, SEEK_SET);
}

void app_file_close(void)
{
	(void)fclose(f);
}

char *app_get_root_folder_path(void)
{
	static char root_folder_path[] = "/";

	return (root_folder_path);
}

void app_populate_tree_from_file_system(struct mw_tree_container_t *tree,
		mw_handle_t start_folder_handle)
{
	DIR *dp;
	struct dirent *ep;     
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
    
    /* open the folder */
	dp = opendir(path);
	
    if (dp != NULL)
    {
        while (true)
        {    
			ep = readdir(dp);
			if (ep == NULL)
			{
            	/* break on error or end of folder */				
				break;
			}        	
			
        	node_flags = 0U;
            if (ep->d_type == DT_DIR)
            {
            	/* it is a folder */
        	}

        	(void)mw_tree_container_add_node(tree,
        			start_folder_handle,
					ep->d_name,
        			node_flags);
        }
        
    	(void)closedir(dp);
    }
}

uint8_t find_folder_entries(char *path,
		mw_ui_list_box_entry *list_box_settings_entries,
		bool folders_only,
		uint8_t max_entries,
		const uint8_t *file_entry_icon,
		const uint8_t *folder_entry_icon)
{
	DIR *dp;
	struct dirent *ep;     
	uint8_t i = 0U;
	
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
	
	dp = opendir(path);

	if (dp != NULL)
	{
		while (true)
		{
			ep = readdir(dp);
			if (ep == NULL)
			{
				break;
			}

        	/* ignore if not a folder and we want directories only */
        	if (folders_only && ep->d_type != DT_DIR)
        	{
        		continue;
        	}
			
            (void)mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1U, ep->d_name);
            if (ep->d_type == DT_DIR)
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
		
		(void)closedir(dp);
	}

	return (i);
}

mw_time_t app_get_time_date(void)
{
	mw_time_t mw_time_now;
	time_t time_now;
	struct tm *tm_now;
	
	time_now = time(NULL);
	tm_now = gmtime(&time_now);
	
	mw_time_now.tm_hour = tm_now->tm_hour;
	mw_time_now.tm_min = tm_now->tm_min;
	mw_time_now.tm_sec = tm_now->tm_sec;
	mw_time_now.tm_year = (uint16_t)(tm_now->tm_year + 1900);
	mw_time_now.tm_mon = tm_now->tm_mon;
	mw_time_now.tm_mday = tm_now->tm_mday;

	return (mw_time_now);
}

void app_set_time_date(mw_time_t new_time)
{
	struct timeval tv;
	struct timezone tz = {0, 0};
	struct tm tm_now;	
	
	tm_now.tm_hour = new_time.tm_hour;
	tm_now.tm_min = new_time.tm_min;
	tm_now.tm_sec = new_time.tm_sec;
	tm_now.tm_year = (int)new_time.tm_year - 1900;
	tm_now.tm_mon = new_time.tm_mon;
	tm_now.tm_mday = new_time.tm_mday;
	
	tv.tv_sec = mktime(&tm_now);
	tv.tv_usec = (suseconds_t)0;
	
	settimeofday(&tv, &tz);
}
