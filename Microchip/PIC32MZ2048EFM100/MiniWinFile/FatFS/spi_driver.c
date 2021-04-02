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

/***************
*** INCLUDES ***
***************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "definitions.h"

/****************
*** CONSTANTS ***
****************/

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

void SPI1_init(void)
{
    SD_CS_Set();
}

#if 0
void SPI1_send_receive(const uint8_t *send_buffer, uint8_t *receive_buffer, uint32_t size)
{
	/* check prameter values sensible */
	if (size == 0U || (send_buffer == NULL && receive_buffer == NULL))
	{
		return;
	}
    
    SPI1_WriteRead((void *)send_buffer, (size_t)size, (void *)receive_buffer, (size_t)size);
}
#endif

void SPI1_send(const uint8_t *send_buffer, uint32_t size)
{
    SPI1_Write((void *)send_buffer, size);
}

void SPI1_receive(uint8_t *receive_buffer, uint32_t size)
{
    SPI1_Read((void *)receive_buffer, size);
}

void delay_us(uint32_t us)
{
    CORETIMER_DelayUs(us);
}