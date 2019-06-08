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

#include <string.h>
#include "app.h"
#include "r_gpio_rx_if.h"
#include "r_usb_basic_if.h"
#include "r_usb_hmsc_if.h"
#include "r_sys_time_rx_if.h"
#include "r_tfat_lib.h"
#include "pin.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef enum
{
    STATE_ATTACHED, STATE_DETACHED
} usb_state_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static usb_ctrl_t usb_control;
static usb_cfg_t usb_config;
static FATFS usb_disk_fatfs;
static usb_state_t usb_state;
static FIL file_handle;
static uint32_t file_size;

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
    SYS_TIME sys_time = {0U, 0U, 0U, 1U, 1U, 1970U};

    /* this sets up USB pins */
	R_Pins_Create();

	/* gpio led output */
	(void)R_GPIO_PinControl(GPIO_PORT_7_PIN_0, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_7_PIN_0, GPIO_DIRECTION_OUTPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_7_PIN_0, GPIO_CMD_OUT_CMOS);

	/* gpio button input */
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_5, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_0_PIN_5, GPIO_DIRECTION_INPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_0_PIN_5, GPIO_CMD_IN_PULL_UP_DISABLE);

	if (R_SYS_TIME_Open() == SYS_TIME_SUCCESS)
	{
		(void)R_SYS_TIME_SetCurrentTime(&sys_time);
	}

    usb_control.module = USB_IP0;
    usb_control.type = (uint8_t)USB_HMSC;
    usb_config.usb_speed = (uint8_t)USB_FS;
    usb_config.usb_mode = (uint8_t)USB_HOST;
    (void)R_USB_Open(&usb_control, &usb_config);
    usb_state = STATE_DETACHED;

    file_size = 0U;
}

void app_main_loop_process(void)
{
    uint16_t usb_event;

	usb_event = R_USB_GetEvent(&usb_control);
	if (usb_control.address == 1U)
	{
		switch ((usb_status_t)usb_event)
		{
		case USB_STS_CONFIGURED:
			if (R_tfat_f_mount(0U, &usb_disk_fatfs) == TFAT_FR_OK)
			{
				usb_state = STATE_ATTACHED;
			}
			break;

		case USB_STS_DETACH:
		    usb_state = STATE_DETACHED;
		    file_size = 0U;
			break;

		default:
			/* keep MISRA happy */
			break;
		}
	}
}

bool app_file_open(char *path_and_filename)
{
	bool result = false;
	FILINFO file_info;

	if (usb_state == STATE_ATTACHED)
	{
		if (R_tfat_f_open(&file_handle, path_and_filename, (uint8_t)TFAT_FA_READ) == TFAT_FR_OK)
		{
			(void)R_tfat_f_stat(path_and_filename, &file_info);
			file_size = file_info.fsize;
			result = true;
		}
	}

	return (result);
}

bool app_file_create(char *path_and_filename)
{
	bool result = false;

	if (usb_state == STATE_ATTACHED)
	{
		if (R_tfat_f_open(&file_handle, path_and_filename, (uint8_t)TFAT_FA_WRITE | (uint8_t)TFAT_FA_CREATE_ALWAYS) == TFAT_FR_OK)
		{
			result = true;
		}
	}

	return (result);
}

uint32_t app_file_size(void)
{
	return file_size;
}

uint8_t app_file_getc(void)
{
	uint8_t byte = 0U;
	uint16_t bytes_read;

	if (usb_state == STATE_ATTACHED)
	{
		(void)R_tfat_f_read(&file_handle, &byte, 1, &bytes_read);
	}

	return (byte);
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
	uint16_t bytes_read;

	if (usb_state == STATE_ATTACHED)
	{
		(void)R_tfat_f_read(&file_handle, buffer, (uint16_t)count, &bytes_read);
	}
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
	uint16_t bytes_written;

	if (usb_state == STATE_ATTACHED)
	{
	    (void)R_tfat_f_write(&file_handle, buffer, (uint16_t)count, &bytes_written);
	}
}

uint32_t app_file_seek(uint32_t position)
{
	if (usb_state == STATE_ATTACHED)
	{
		return ((uint32_t)(R_tfat_f_lseek(&file_handle, position)));
	}

	return 1U;
}

void app_file_close(void)
{
	(void)R_tfat_f_close(&file_handle);
	file_size = 0U;
}

char *app_get_root_folder_path(void)
{
	static char root_folder_path[] = "0:/";

	return (root_folder_path);
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
    uint8_t i = 0U;

	if (usb_state != STATE_ATTACHED)
	{
		return 0U;
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
    path[strlen(path) - (size_t)1] = '\0';

    /* open the folder */
    result = R_tfat_f_opendir(&folder, path);
    if (result == TFAT_FR_OK)
    {
        for (;;)
        {
        	/* read a folder item */
            result = R_tfat_f_readdir(&folder, &file_info);
            if (result != TFAT_FR_OK || file_info.fname[0] == '\0')
            {
            	/* break on error or end of folder */
            	break;
            }

        	/* ignore if it's a hidden or system entry*/
        	if ((file_info.fattrib & (uint8_t)TFAT_AM_HID) == (uint8_t)TFAT_AM_HID ||
        			(file_info.fattrib & (uint8_t)TFAT_AM_SYS) == (uint8_t)TFAT_AM_SYS)
        	{
        		continue;
        	}

        	/* ignore if not a folder and we want directories only */
        	if (folders_only && (file_info.fattrib & (uint8_t)TFAT_AM_DIR) == 0U)
        	{
        		continue;
        	}

            (void)mw_util_safe_strcpy(list_box_settings_entries[i].label, (size_t)MAX_FILENAME_LENGTH + (size_t)1, file_info.fname);
            if ((file_info.fattrib & (uint8_t)TFAT_AM_DIR) == (uint8_t)TFAT_AM_DIR)
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
    result = R_tfat_f_opendir(&folder, path);
    if (result == TFAT_FR_OK)
    {
        for (;;)
        {
        	/* read a folder item */
            result = R_tfat_f_readdir(&folder, &file_info);
            if (result != TFAT_FR_OK || file_info.fname[0] == '\0')
            {
            	/* break on error or end of folder */
            	break;
            }

        	/* ignore if it's a hidden or system entry*/
        	if ((file_info.fattrib & (uint8_t)TFAT_AM_HID) == (uint8_t)TFAT_AM_HID || (file_info.fattrib & (uint8_t)TFAT_AM_SYS) == (uint8_t)TFAT_AM_SYS)
        	{
        		continue;
        	}

        	node_flags = 0U;
            if ((file_info.fattrib & (uint8_t)TFAT_AM_DIR) == (uint8_t)TFAT_AM_DIR)
        	{
        		node_flags = MW_TREE_CONTAINER_NODE_IS_FOLDER;
        	}

        	(void)mw_tree_container_add_node(tree,
        			start_folder_handle,
					file_info.fname,
        			node_flags);

        }
        //(void)f_closedir(&folder);
    }
}

mw_time_t app_get_time_date(void)
{
	mw_time_t time_now;
	SYS_TIME sys_time;

	(void)R_SYS_TIME_GetCurrentTime(&sys_time);
	time_now.tm_hour = (uint8_t)sys_time.hour;
	time_now.tm_min = (uint8_t)sys_time.min;
	time_now.tm_sec = (uint8_t)sys_time.sec;
	time_now.tm_year = (uint16_t)sys_time.year;
	time_now.tm_mon = (uint8_t)sys_time.month;
	time_now.tm_mday = (uint8_t)sys_time.day;

	return (time_now);
}

void app_set_time_date(mw_time_t new_time)
{
	SYS_TIME sys_time;

	sys_time.sec = 0U;
	sys_time.min = (uint32_t)new_time.tm_min;
	sys_time.hour = (uint32_t)new_time.tm_hour;
	sys_time.day = (uint32_t)new_time.tm_mday;
	sys_time.month = (uint32_t)new_time.tm_mon;
	sys_time.year = (uint32_t)new_time.tm_year;

	(void)R_SYS_TIME_SetCurrentTime(&sys_time);
}
