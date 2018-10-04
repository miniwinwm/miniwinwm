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

#include "app.h"
#include "stm32f4_discovery.h"
#include "ff_gen_drv.h"
#include "usbh_diskio_dma.h"
#include "miniwin_settings.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef enum
{
	APPLICATION_IDLE = 0,
	APPLICATION_START,
	APPLICATION_RUNNING
} MSC_ApplicationTypeDef;

/***********************
*** GLOBAL VARIABLES ***
***********************/

USBH_HandleTypeDef hUSB_Host;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint8_t mw_bitmaps_file_icon_small[];
extern const uint8_t mw_bitmaps_folder_icon_small[];

/**********************
*** LOCAL VARIABLES ***
**********************/

static FATFS USBDISK_FatFs;  										/**< File system object for USB Disk logical drive */
static char USB_Path[4];     										/**< USB Disk logical drive path */
static MSC_ApplicationTypeDef Appli_state = APPLICATION_IDLE;		/**< USB host state machine state variable */
static FIL in_file;													/**< Handle to the single file used by this app */

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**
 * Configure the system clock
 */
static void SystemClock_Config(void);

/**
 * USB Host state machine state processing routine
 *
 * @param phost pointer to USB host variable
 * @param id state machine state
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void SystemClock_Config  (void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig (&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{
	switch (id)
	{
	case HOST_USER_DISCONNECTION:
		Appli_state = APPLICATION_IDLE;
		f_mount(&USBDISK_FatFs, "", 0);
		break;

	case HOST_USER_CLASS_ACTIVE:
		Appli_state = APPLICATION_START;
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	HAL_Init();
	SystemClock_Config();

	/* if board button pressed clear settings which forces a screen recalibration */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
	if (BSP_PB_GetState(BUTTON_KEY))
	{
		mw_settings_set_to_defaults();
		mw_settings_save();
	}

	/* Link the USB Mass Storage disk I/O driver */
	FATFS_LinkDriver(&USBH_Driver, USB_Path);

	/* Init Host Library */
	USBH_Init(&hUSB_Host, USBH_UserProcess, 0);

	/* Add Supported Class */
	USBH_RegisterClass(&hUSB_Host, USBH_MSC_CLASS);

	/* Start Host Process */
	USBH_Start(&hUSB_Host);

	/* Register the file system object to the FatFs module */
	f_mount(&USBDISK_FatFs, (TCHAR const*)USB_Path, 0);
}

bool app_file_open(char *path_and_file_name)
{
	bool result = false;

	if (Appli_state == APPLICATION_START)
	{
		if (f_open(&in_file, path_and_file_name, FA_READ) == FR_OK)
		{
			result = true;
		}
	}

	return result;
}

uint32_t app_file_size(void)
{
	return (uint32_t)f_size(&in_file);
}

uint8_t app_file_getc()
{
	uint8_t byte;
	UINT bytes_read;

	f_read(&in_file, &byte, 1, &bytes_read);

	return byte;
}

void app_file_fread(uint8_t *buffer, uint32_t count)
{
	UINT bytes_read;

	f_read(&in_file, buffer, count, &bytes_read);			/* Read data from the file */
}

uint32_t app_file_seek(uint32_t position)
{
	return (uint32_t)(f_lseek(&in_file, position));
}

void app_file_close(void)
{
	f_close(&in_file);
}

char *app_get_root_folder_path(void)
{
	return USB_Path;
}

void app_main_loop_process(void)
{
    USBH_Process(&hUSB_Host);
}

uint8_t find_directory_entries(char* path,
		mw_ui_list_box_entry *list_box_settings_entries,
		uint8_t max_entries)
{
    FRESULT res;
    DIR dir;
    FILINFO fno;
    UINT i;

    i = 0;
    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK)
    {
        for (;;)
        {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0)
            {
            	break;  /* Break on error or end of dir */
            }

        	/* Ignore if it's a hidden or system entry*/
        	if ((fno.fattrib & AM_HID) || (fno.fattrib & AM_SYS))
        	{
        		continue;
        	}

            mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILE_NAME_LENGTH + 1, fno.fname);
            if (fno.fattrib & AM_DIR)
            {
            	/* It is a directory */
            	list_box_settings_entries[i].icon = mw_bitmaps_folder_icon_small;
            }
            else
            {
            	/* It is a file. */
                list_box_settings_entries[i].icon = mw_bitmaps_file_icon_small;
            }
            i++;
            if (i == max_entries)
            {
            	break;
            }
        }
        f_closedir(&dir);
    }

    return i;
}
