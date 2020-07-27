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

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include "iodefine.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Initialize SCI comms interface 2 for SPI transfer
 */
void sci2_spi_init(void);

/**
 * Send/receive data synchronously to SCI2 configured for SPI
 *
 * @param send_buffer Data to send, or NULL if receiving only
 * @param receive_buffer Buffer for received data, or NULL if sending only
 * @param size Bytes to transfer
 * @note Buffer pointers must not both be NULL
 */
void sci2_spi_send_receive(const uint8_t *send_buffer, uint8_t *receive_buffer, uint32_t size);

/**
 * Set chip select level
 *
 * @param level The level to write to the pin, 0 or 1
 */
static inline void sci2_spi_chip_select(uint8_t level)
{
	PORTJ.PODR.BIT.B5 = level;
}

#endif
