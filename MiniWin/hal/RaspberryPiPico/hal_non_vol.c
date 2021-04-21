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

#ifdef RASPBERRY_PI_PICO

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <string.h>
#include "hardware/sync.h"
#include "hardware/flash.h"
#include "hal/hal_non_vol.h"

/****************
*** CONSTANTS ***
****************/

#define FLASH_TARGET_OFFSET		(PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)
static const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

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
	(void)memcpy(data, flash_target_contents, (length));
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
    uint32_t interrupts;
    
 	/* disable and dave all interrupts before doing flash things */
    interrupts = save_and_disable_interrupts();
    
    /* erase sector */
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);	
    
    /* write data */
    flash_range_program(FLASH_TARGET_OFFSET, data, length);

    /* restore all interrupts when flash stuff done */
    restore_interrupts(interrupts);    
}

#endif