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

#ifdef _RENESAS_SYNERGY_

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include "miniwin_thread.h"
#include "hal/hal_non_vol.h"

/****************
*** CONSTANTS ***
****************/

#define FLASH_DF_BLOCK_SIZE             64UL
#define FLASH_DF_64B_BLOCK0             0x40100000UL

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
    (void)g_flash_miniwin.p_api->open(g_flash_miniwin.p_ctrl, g_flash_miniwin.p_cfg);
}

void mw_hal_non_vol_load(uint8_t *data, uint16_t length)
{
    (void)g_flash_miniwin.p_api->read(g_flash_miniwin.p_ctrl, data, FLASH_DF_64B_BLOCK0, length);
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
    uint8_t flash_block[FLASH_DF_BLOCK_SIZE];

    (void)memcpy(flash_block, data, (size_t)length);

    (void)g_flash_miniwin.p_api->erase(g_flash_miniwin.p_ctrl, FLASH_DF_64B_BLOCK0, 1UL);
    (void)g_flash_miniwin.p_api->write(g_flash_miniwin.p_ctrl, (uint32_t)flash_block, FLASH_DF_64B_BLOCK0, FLASH_DF_BLOCK_SIZE);
}

#endif
