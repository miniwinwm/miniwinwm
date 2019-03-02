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

#ifdef STM32F407xx

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include "stm32f4xx_hal.h"

/****************
*** CONSTANTS ***
****************/

#define CONFIG_SECTOR 				FLASH_SECTOR_1
#define CONFIG_ADDRESS				((uint32_t)0x08004000)

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

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

void mw_hal_non_vol_init(void)
{
}

void mw_hal_non_vol_load(uint8_t *data, uint16_t length)
{
	(void)memcpy((data), ((uint8_t *)(CONFIG_ADDRESS)), (length));
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
	uint32_t words = ((uint32_t)length / (uint32_t)sizeof(uint32_t)) + (((uint32_t)length % (uint32_t)sizeof(uint32_t)) ? 1U : 0U);
	uint32_t *data2 = (uint32_t *)data;
	uint32_t address;
	uint32_t index;
	uint32_t sector_error;
	FLASH_EraseInitTypeDef erase_init_struct;

	(void)HAL_FLASH_Unlock();

	/* erase sector */
	erase_init_struct.TypeErase = FLASH_TYPEERASE_SECTORS;
	erase_init_struct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	erase_init_struct.Sector = CONFIG_SECTOR;
	erase_init_struct.NbSectors = 1U;
	(void)HAL_FLASHEx_Erase(&erase_init_struct, &sector_error);

	/* write settings */
	address = CONFIG_ADDRESS;
	for (index = 0U; index < words; index++)
	{
		(void)HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data2[index]);
		address += (uint32_t)sizeof(uint32_t);
	}

	(void)HAL_FLASH_Lock();
}

#endif
