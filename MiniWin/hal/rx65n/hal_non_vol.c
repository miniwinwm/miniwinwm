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

#ifdef RX65N

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include "hal/hal_non_vol.h"
#include "r_smc_entry.h"
#include "r_flash_rx_if.h"

/****************
*** CONSTANTS ***
****************/

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
	(void)memcpy((data), ((uint8_t *)(uint32_t)FLASH_DF_BLOCK_0), ((size_t)length));
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
	uint32_t words = (uint32_t)length / sizeof(uint32_t);
	words += ((uint32_t)length % sizeof(uint32_t) > 0U) ? 1U : 0U;
	uint32_t pages = (uint32_t)words / 0x10U;
	pages += ((uint32_t)length % 0x10U > 0U) ? 1U : 0U;
	uint32_t page;
	uint32_t buffer[0x10U];

	/* write settings */
	(void)R_FLASH_Open();
	(void)R_FLASH_Erase(FLASH_DF_BLOCK_0, pages);
	for (page = 0U; page < pages; page++)
	{
		(void)memset(((uint8_t *)buffer), (0), (FLASH_DF_BLOCK_SIZE));
		if ((uint32_t)length < (uint32_t)FLASH_DF_BLOCK_SIZE)
		{
			(void)memcpy(((uint8_t *)buffer), (data + (page * ((uint32_t)FLASH_DF_BLOCK_SIZE))), ((size_t)length));
		}
		else
		{
			(void)memcpy(((uint8_t *)buffer), (data + (page * (uint32_t)FLASH_DF_BLOCK_SIZE)), ((size_t)FLASH_DF_BLOCK_SIZE));
			length -= (uint16_t)FLASH_DF_BLOCK_SIZE;
		}

		(void)R_FLASH_Write((uint32_t)buffer,
				(uint32_t)FLASH_DF_BLOCK_0 + (uint32_t)FLASH_DF_BLOCK_SIZE * page,
				FLASH_DF_BLOCK_SIZE);
	}
	(void)R_FLASH_Close();
}

#endif
