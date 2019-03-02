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
#include "stm32f4_discovery.h"
#include "ff_gen_drv.h"
#include "usbh_diskio_dma.h"

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

/**********************
*** LOCAL VARIABLES ***
**********************/

static FATFS usb_disk_fatfs;  										/**< File system object for USB Disk logical drive */
static char usb_path[4U];     										/**< USB Disk logical drive path */
static MSC_ApplicationTypeDef application_state = APPLICATION_IDLE;	/**< USB host state machine state variable */
static FIL file_handle;												/**< File to access */
static RTC_HandleTypeDef rtc_handle;								/**< Driver handle for RTC */

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
  RCC_OscInitStruct.PLL.PLLM = 8U;
  RCC_OscInitStruct.PLL.PLLN = 336U;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7U;
  (void)HAL_RCC_OscConfig (&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  (void)HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001U)
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
		application_state = APPLICATION_IDLE;
		(void)f_mount(&usb_disk_fatfs, "", 0U);
		break;

	case HOST_USER_CLASS_ACTIVE:
		application_state = APPLICATION_START;
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	RTC_DateTypeDef  hal_date_structure;
	RTC_TimeTypeDef  hal_time_structure;

	(void)HAL_Init();
	SystemClock_Config();

	rtc_handle.Instance = RTC;
	rtc_handle.Init.HourFormat = RTC_HOURFORMAT_24;
	rtc_handle.Init.AsynchPrediv = 0x7FU;
	rtc_handle.Init.SynchPrediv = 0x0130U;
	rtc_handle.Init.OutPut = RTC_OUTPUT_DISABLE;
	rtc_handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	rtc_handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	(void)HAL_RTC_Init(&rtc_handle);

	hal_date_structure.Year = 0x00U;
	hal_date_structure.Month = RTC_MONTH_JANUARY;
	hal_date_structure.Date = 0x01U;
	hal_date_structure.WeekDay = RTC_WEEKDAY_MONDAY;	/* must be set to something even if not correct for the date */
	(void)HAL_RTC_SetDate(&rtc_handle, &hal_date_structure, FORMAT_BCD);

	hal_time_structure.Hours = 0x01U;
	hal_time_structure.Minutes = 0x0U;
	hal_time_structure.Seconds = 0x00U;
	hal_time_structure.TimeFormat = RTC_HOURFORMAT12_AM;
	hal_time_structure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	hal_time_structure.StoreOperation = RTC_STOREOPERATION_RESET;
	(void)HAL_RTC_SetTime(&rtc_handle, &hal_time_structure, FORMAT_BCD);

	/* Link the USB Mass Storage disk I/O driver */
	(void)FATFS_LinkDriver(&USBH_Driver, usb_path);

	/* Init Host Library */
	(void)USBH_Init(&hUSB_Host, USBH_UserProcess, 0U);

	/* Add Supported Class */
	(void)USBH_RegisterClass(&hUSB_Host, USBH_MSC_CLASS);

	/* Start Host Process */
	(void)USBH_Start(&hUSB_Host);

	/* Register the file system object to the FatFs module */
	(void)f_mount(&usb_disk_fatfs, (TCHAR const*)usb_path, 0U);
}

bool app_file_open(char *path_and_filename)
{
	bool result = false;

	if (application_state == APPLICATION_START)
	{
		if (f_open(&file_handle, path_and_filename, FA_READ) == FR_OK)
		{
			result = true;
		}
	}

	return (result);
}

bool app_file_create(char *path_and_filename)
{
	bool result = false;

	if (application_state == APPLICATION_START)
	{
		if (f_open(&file_handle, path_and_filename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK)
		{
			result = true;
		}
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

	f_read(&file_handle, &byte, 1, &bytes_read);

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

	(void)f_write (&file_handle, buffer, count, &bytes_written);
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
	return (usb_path);
}

void app_main_loop_process(void)
{
	(void)USBH_Process(&hUSB_Host);
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
    UINT i;

    i = 0U;
    result = f_opendir(&folder, path);                       /* Open the folder */
    if (result == FR_OK)
    {
        for (;;)
        {
            result = f_readdir(&folder, &file_info);                   /* Read a folder item */
            if (result != FR_OK || file_info.fname[0] == 0)
            {
            	break;  /* Break on error or end of dir */
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

            mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1U, file_info.fname);
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
        (void)f_closedir(&folder);
    }

    return (i);
}

mw_time_t app_get_time_date(void)
{
	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;
	mw_time_t time_now;

	(void)HAL_RTC_GetTime(&rtc_handle, &rtc_time, FORMAT_BIN);
	(void)HAL_RTC_GetDate(&rtc_handle, &rtc_date, FORMAT_BIN);

	time_now.tm_hour = rtc_time.Hours;
	time_now.tm_min = rtc_time.Minutes;
	time_now.tm_sec = rtc_time.Seconds;
	time_now.tm_year = (uint16_t)rtc_date.Year + 2000U;
	time_now.tm_mon = rtc_date.Month;
	time_now.tm_mday = rtc_date.Date;

	return (time_now);
}

void app_set_time_date(mw_time_t new_time)
{
	uint16_t temp_uint16;

	RTC_DateTypeDef  hal_date_structure;
	RTC_TimeTypeDef  hal_time_structure;

	temp_uint16 = new_time.tm_year - 2000U;
	hal_date_structure.Year = (uint8_t)temp_uint16;
	hal_date_structure.Month = new_time.tm_mon;
	hal_date_structure.Date = new_time.tm_mday;
	hal_date_structure.WeekDay = RTC_WEEKDAY_MONDAY;	/* must be set to something even if not correct for the date */
	(void)HAL_RTC_SetDate(&rtc_handle, &hal_date_structure, FORMAT_BIN);

	hal_time_structure.Hours = new_time.tm_hour;
	hal_time_structure.Minutes = new_time.tm_min;
	hal_time_structure.Seconds = 0x00U;
	hal_time_structure.TimeFormat = RTC_HOURFORMAT12_AM;
	hal_time_structure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	hal_time_structure.StoreOperation = RTC_STOREOPERATION_RESET;
	(void)HAL_RTC_SetTime(&rtc_handle, &hal_time_structure, FORMAT_BIN);
}

DWORD get_fattime (void)
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
