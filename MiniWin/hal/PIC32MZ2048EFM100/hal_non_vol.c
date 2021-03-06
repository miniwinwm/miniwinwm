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

#ifdef PIC32MZ2048EFM100

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include "definitions.h" 
#include "miniwin.h"
#include "hal/hal_non_vol.h"

/****************
*** CONSTANTS ***
****************/

#define BUFFER_SIZE             (NVM_FLASH_PAGESIZE / sizeof(uint32_t))
#define APP_FLASH_ADDRESS       (NVM_FLASH_START_ADDRESS + NVM_FLASH_SIZE - NVM_FLASH_PAGESIZE)

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static uint32_t flash_data_buffer[BUFFER_SIZE] CACHE_ALIGN;

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
    (void)NVM_Read(flash_data_buffer, sizeof(flash_data_buffer), APP_FLASH_ADDRESS); 
    (void)memcpy((void *)data, (void *)flash_data_buffer, (size_t)length);
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
    uint32_t address = APP_FLASH_ADDRESS;
    uint8_t *writePtr = (uint8_t *)flash_data_buffer;
    uint32_t i;
    
    /* Erase the Page */
    (void)NVM_PageErase(APP_FLASH_ADDRESS);
    while (NVM_IsBusy() == true)
    {
    }

    (void)memcpy((void *)flash_data_buffer, (void *)data, (size_t)length);

    for (i = 0U; i < NVM_FLASH_PAGESIZE; i+= NVM_FLASH_ROWSIZE)
    {
        /* Program a row of data */
        (void)NVM_RowWrite((uint32_t *)writePtr, address);

        while (NVM_IsBusy() == true)
        {
        }        

        writePtr += NVM_FLASH_ROWSIZE;
        address  += NVM_FLASH_ROWSIZE;
    }  
}

#endif
