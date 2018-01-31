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
#include "stm32f4xx.h"

/****************
*** CONSTANTS ***
****************/

#define CONFIG_SECTOR 				FLASH_Sector_15
#define CONFIG_ADDRESS				0x0810C000

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

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
	memcpy(data, (uint8_t *)(CONFIG_ADDRESS), length);
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
	uint32_t words = (length / sizeof(uint32_t)) + ((length % sizeof(uint32_t)) ? 1 : 0);
	uint32_t index;
	uint32_t address = CONFIG_ADDRESS;
	uint32_t *data2 = (uint32_t *)data;

	FLASH_Unlock();

	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
	                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

	FLASH_EraseSector(CONFIG_SECTOR, VoltageRange_3);

	for (index = 0; index < words; index++)
	{
		FLASH_ProgramWord(address, data2[index]);
		address += sizeof(uint32_t);
	}

	FLASH_Lock();
}
