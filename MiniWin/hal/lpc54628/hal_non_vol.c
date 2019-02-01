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

#ifdef CPU_LPC54628J512ET180

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include "fsl_eeprom.h"

/****************
*** CONSTANTS ***
****************/

#define FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES (FSL_FEATURE_EEPROM_SIZE / FSL_FEATURE_EEPROM_PAGE_COUNT)
#define FSL_FEATURE_EEPROM_PAGE_SIZE_WORDS (FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES / sizeof(uint32_t))

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
    eeprom_config_t config;

    EEPROM_GetDefaultConfig(&config);
    EEPROM_Init(EEPROM, &config, CLOCK_GetFreq(kCLOCK_BusClk));
}

void mw_hal_non_vol_load(uint8_t *data, uint16_t length)
{
	(void)memcpy(data, (uint8_t *)(FSL_FEATURE_EEPROM_BASE_ADDRESS), length);
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
	uint32_t words = (length / sizeof(uint32_t)) + ((length % sizeof(uint32_t)) ? 1U : 0U);
	uint32_t pages = (words / FSL_FEATURE_EEPROM_PAGE_SIZE_WORDS) + ((length % FSL_FEATURE_EEPROM_PAGE_SIZE_WORDS) ? 1 : 0);
	uint32_t page;
	uint32_t buffer[FSL_FEATURE_EEPROM_PAGE_SIZE_WORDS];

	/* write settings */
	for (page = 0U; page < pages; page++)
	{
		(void)memset((uint8_t *)buffer, 0, FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES);
		if (length < FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES)
		{
			(void)memcpy((uint8_t *)buffer, data + (page * FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES), length);
		}
		else
		{
			(void)memcpy((uint8_t *)buffer, data + (page * FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES), FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES);
			length -= FSL_FEATURE_EEPROM_PAGE_SIZE_BYTES;
		}

		(void)EEPROM_WritePage(EEPROM, page, buffer);
	}
}

#endif
