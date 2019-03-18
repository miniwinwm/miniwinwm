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

#ifdef RX65N_GCC

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include <iodefine.h>
#include "hal/hal_non_vol.h"

/****************
*** CONSTANTS ***
****************/

#define FCU_COMMAND_AREA              	 	 	0x007E0000U
#define DATA_FLASH_START_ADDRESS				0x00100000U

/************
*** TYPES ***
************/

typedef volatile uint8_t * FCU_BYTE_PTR __attribute__ ((aligned (4)));
typedef volatile uint16_t * FCU_WORD_PTR __attribute__ ((aligned (4)));

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
	(void)memcpy((data), ((uint8_t *)(uint32_t)DATA_FLASH_START_ADDRESS), ((size_t)length));
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
	const FCU_BYTE_PTR g_pfcu_cmd_area = (uint8_t*)FCU_COMMAND_AREA;
	uint32_t blocks;
	uint32_t block_counter;
	uint32_t words;
	uint32_t word_counter;
	uint16_t short_word;

	/* permits programming/erasure, and blank checking */
	FLASH.FWEPROR.BIT.FLWE = 1;

	/* set mode entry register with key to program/erase data memory */
	FLASH.FENTRYR.WORD = 0xAA80;
    while (FLASH.FENTRYR.WORD != 0x0080)
    {
    }

    /* set erasure priority mode */
    FLASH.FCPSR.WORD = 0x0001;

    /* calculate number of 64 byte blocks to erase */
	blocks = (uint32_t)length / 64U;
	blocks += ((uint32_t)length % 64U > 0U) ? 1U : 0U;

    /* do erase in 64 byte blocks */
	for (block_counter = 0U; block_counter < blocks; block_counter++)
	{
		/* set command start address */
		FLASH.FSADDR.LONG = DATA_FLASH_START_ADDRESS + block_counter * 64U;

		/* send FACI command to do a block erase of 64 bytes of flash memory */
		*g_pfcu_cmd_area = 0x20;
		*g_pfcu_cmd_area = 0xd0;

		/* wait until FACI command completed */
		while (1 != FLASH.FSTATR.BIT.FRDY)
		{
		}
	}

    /* calculate number of 4 byte words to write */
    words = (uint32_t)length / sizeof(uint32_t);
   	words += ((uint32_t)length % sizeof(uint32_t) > 0U) ? 1U : 0U;

   	/* write each 4 byte word */
	for (word_counter = 0U; word_counter < words; word_counter++)
	{
		/* set command start address */
		FLASH.FSADDR.LONG = DATA_FLASH_START_ADDRESS + word_counter * 4U;

		*g_pfcu_cmd_area = 0xe8U;
		*g_pfcu_cmd_area = 0x02U;

		/* write first 2 byte short word */
		short_word = (uint16_t)data[word_counter * 4U];
		short_word += ((uint16_t)(data[word_counter * 4U + 1U])) << 8;
		*(FCU_WORD_PTR) g_pfcu_cmd_area = short_word;

		/* wait for buffer to empty */
		while (FLASH.FSTATR.BIT.DBFULL == 1)
		{
		}

		/* write second 2 byte short word */
		short_word = (uint16_t)data[word_counter * 4U + 2U];
		short_word += ((uint16_t)(data[word_counter * 4U + 3U])) << 8;
		*(FCU_WORD_PTR) g_pfcu_cmd_area = short_word;

		/* wait for buffer to empty */
		while (FLASH.FSTATR.BIT.DBFULL == 1)
		{
		}

		/* write command complete byte */
		*g_pfcu_cmd_area = 0xd0U;

		/* wait until FACI command completed */
		while (1 != FLASH.FSTATR.BIT.FRDY)
	    {
	    }
	}

	/* reset Mode Entry Register with key */
	FLASH.FENTRYR.WORD = 0xAA00;
    while (FLASH.FENTRYR.WORD != 0x000)
    {
    }

	/* prevents programming/erasure, and blank checking */
	FLASH.FWEPROR.BIT.FLWE = 0;
}

#endif
