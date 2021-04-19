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

#ifdef __SAM3X8E__

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include <asf.h>
#include "hal/hal_non_vol.h"

/****************
*** CONSTANTS ***
****************/

#define TEST_PAGE_ADDRESS (IFLASH1_ADDR + IFLASH1_SIZE - IFLASH1_PAGE_SIZE)

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
    (void)memcpy((void *)data, (void *)TEST_PAGE_ADDRESS, (size_t)length);
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
	(void)flash_init(FLASH_ACCESS_MODE_128, 6);
	(void)flash_unlock(TEST_PAGE_ADDRESS, TEST_PAGE_ADDRESS + IFLASH1_PAGE_SIZE - 1U, 0U, 0U);
	
	(void)flash_write(TEST_PAGE_ADDRESS, data, (uint32_t)length, 1U);	
	
	(void)flash_lock(TEST_PAGE_ADDRESS, TEST_PAGE_ADDRESS + IFLASH1_PAGE_SIZE - 1U, 0U, 0U);
}

#endif
