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
#include <asf.h>
#include "miniwin.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

#define SPI_TOUCH_CLK_POLARITY					0						/**< Touch SPI clock polarity */
#define SPI_TOUCH_CLK_PHASE						1						/**< Touch SPI clock phase */
#define SPI_TOUCH_DLYBS							0x40					/**< Touch SPI post CS/ delay */
#define SPI_TOUCH_DLYBCT						0x10					/**< Touch SPI consecutive transfers delay */
#define SPI_TOUCH_SPEED							1000000UL				/**< Touch SPI baud rate */

#define SPI_LCD_CLK_POLARITY					0						/**< LCD SPI clock polarity */
#define SPI_LCD_CLK_PHASE						1						/**< LCD SPI clock phase */
#define SPI_LCD_DLYBS							0x00					/**< LCD SPI post CS/ delay */
#define SPI_LCD_DLYBCT							0x00					/**< LCD SPI consecutive transfers delay */
#define SPI_LCD_SPEED							32000000UL				/**< LCD SPI baud rate */

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

static mw_time_t mw_time_now;
static FIL file_handle;
static FATFS fs;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

void update_real_time(void)
{
	uint8_t days_in_month;
	
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

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{	
	/* initialize all modules */
	sysclk_init();
	board_init();
	uhc_start();
	
	/* initialise LED pin */
	/* this is done in board_init() in init.c */
	
	/* configure touch recal request pin */
	ioport_set_pin_dir(TOUCH_RECAL_PIN, IOPORT_DIR_INPUT);
	(void)gpio_configure_pin(TOUCH_RECAL_PIN, PIO_PULLUP);
		
	/* configure touch t_irq pin */
	ioport_set_pin_dir(TOUCH_T_IRQ_PIN, IOPORT_DIR_INPUT);
	
	/* configure lcd DC & RESET pins */
	ioport_set_pin_dir(LCD_RESET_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_DC_PIN, IOPORT_DIR_OUTPUT);

	/* initialize SPI_LCD_TOUCH_BASE pins */
	/* this is done in board_init() in init.c controlled by enabling #define CONF_BOARD_SPI0 in conf_board.h */
	
	/* initialise touch CS/ pin */
	/* this is done in board_init() in init.c controlled by enabling #define CONF_BOARD_SPI0_NPCS0 in conf_board.h */
	
	/* initialise LCD CS/ pin */
	/* this is done in board_init() in init.c controlled by enabling #define CONF_BOARD_SPI0_NPCS1 in conf_board.h */
	
	/* initialise SPI_LCD_TOUCH_BASE device */
	spi_enable_clock(SPI_LCD_TOUCH_BASE);
	spi_disable(SPI_LCD_TOUCH_BASE);
	spi_reset(SPI_LCD_TOUCH_BASE);
	spi_set_fixed_peripheral_select(SPI_LCD_TOUCH_BASE);
	spi_set_master_mode(SPI_LCD_TOUCH_BASE);
	spi_disable_mode_fault_detect(SPI_LCD_TOUCH_BASE);
	
	/* configure SPI when touch CS/ is active */
	spi_set_clock_polarity(SPI_LCD_TOUCH_BASE, SPI_TOUCH_CHIP_SEL, SPI_TOUCH_CLK_POLARITY);
	spi_set_clock_phase(SPI_LCD_TOUCH_BASE, SPI_TOUCH_CHIP_SEL, SPI_TOUCH_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_LCD_TOUCH_BASE, SPI_TOUCH_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	(void)spi_set_baudrate_div(SPI_LCD_TOUCH_BASE, SPI_TOUCH_CHIP_SEL, sysclk_get_peripheral_hz() / SPI_TOUCH_SPEED);
	spi_set_transfer_delay(SPI_LCD_TOUCH_BASE, SPI_TOUCH_CHIP_SEL, SPI_TOUCH_DLYBS, SPI_TOUCH_DLYBCT);
	
	/* configure SPI when LCD CS/ is active */
	spi_set_clock_polarity(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_LCD_CLK_POLARITY);
	spi_set_clock_phase(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_LCD_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	(void)spi_set_baudrate_div(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, sysclk_get_peripheral_hz() / SPI_LCD_SPEED);
	spi_set_transfer_delay(SPI_LCD_TOUCH_BASE, SPI_LCD_CHIP_SEL, SPI_LCD_DLYBS, SPI_LCD_DLYBCT);
		
	spi_enable(SPI_LCD_TOUCH_BASE);
	
	f_mount(LUN_ID_USB, &fs);
}

void main_usb_sof_event(void)
{
}

void main_usb_connection_event(uhc_device_t * dev, bool b_present)
{
}

void app_main_loop_process(void)
{
}

void spi_transfer(const uint8_t *tx_buf, uint8_t *rx_buf, size_t size)
{
	size_t i;

	size--;
	for (i = (size_t)0; i < size; i++)
	{
		spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
		while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
		{
		}
		rx_buf[i] = (uint8_t)spi_get(SPI_LCD_TOUCH_BASE);
	}
	
	spi_set_lastxfer(SPI_LCD_TOUCH_BASE);

	spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
	while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
	{
	}
	rx_buf[i] = (uint8_t)spi_get(SPI_LCD_TOUCH_BASE);
}

void spi_send(const uint8_t *tx_buf, size_t size)
{
	size_t i;

	size--;
	for (i = (size_t)0; i < size; i++)
	{
		spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
		while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
		{
		}
		(void)spi_get(SPI_LCD_TOUCH_BASE);
	}
	
	spi_set_lastxfer(SPI_LCD_TOUCH_BASE);

	spi_put(SPI_LCD_TOUCH_BASE, (uint16_t)tx_buf[i]);
	while ((spi_read_status(SPI_LCD_TOUCH_BASE) & SPI_SR_RDRF) == 0U)
	{
	}
	(void)spi_get(SPI_LCD_TOUCH_BASE);
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
	static char root_folder_path[] = {LUN_ID_USB + '0', ':', '/', '\0'};

	return (root_folder_path);
}

void app_populate_tree_from_file_system(struct mw_tree_container_t *tree, mw_handle_t start_folder_handle)
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
	tc_stop(TC1, 0);
	mw_time_now = new_time;
	tc_start(TC1, 0);
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

