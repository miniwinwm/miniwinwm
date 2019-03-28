#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include "iodefine.h"

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
