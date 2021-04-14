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
#include "definitions.h"   

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
void SPI1_init(void);

/**
 * Send/receive data synchronously to SCI2 configured for SPI
 *
 * @param send_buffer Data to send, or NULL if receiving only
 * @param receive_buffer Buffer for received data, or NULL if sending only
 * @param size Bytes to transfer
 * @note Buffer pointers must not both be NULL
 */
void SPI1_send(const uint8_t *send_buffer, uint32_t size);

/**
 * Send/receive data synchronously to SCI2 configured for SPI
 *
 * @param send_buffer Data to send, or NULL if receiving only
 * @param receive_buffer Buffer for received data, or NULL if sending only
 * @param size Bytes to transfer
 * @note Buffer pointers must not both be NULL
 */
void SPI1_receive(uint8_t *receive_buffer, uint32_t size);

/**
 * Delay in a busy wait loop for microseconds
 * 
 * @param us Microseconds to delay for 
 */
 void delay_us(uint32_t us);

/**
 * Set chip select level
 *
 * @param level The level to write to the pin, 0 or 1
 */
static inline void SPI1_chip_select(uint8_t level)
{
    if (level == 0U)
    {
        SD_CS_Clear();
    }
    else
    {
        SD_CS_Set();
    }
}

#endif
