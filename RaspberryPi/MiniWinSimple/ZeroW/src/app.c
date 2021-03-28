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

/***************
*** INCLUDES ***
***************/

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include "miniwin.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

#define PAGE_SIZE 					(4 * 1024)
#define BLOCK_SIZE 					(4 * 1024)
#define BCM2708_PERI_BASE   		0x20000000
#define GPIO_BASE           		(BCM2708_PERI_BASE + 0x200000) 
#define INP_GPIO(g) 				*(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) 				*(gpio + ((g) / 10)) |=  (1 << (((g) % 10) * 3))
const static char *spi_device_0  = "/dev/spidev0.0";
const static char *spi_device_1  = "/dev/spidev0.1";

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

volatile unsigned int *gpio;

/**********************
*** LOCAL VARIABLES ***
**********************/

static uint32_t spi_speeds[2];
static uint32_t spi_fds[2];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	int  mem_fd;
	void *gpio_map;

	/* open /dev/mem */
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0) 
	{
		printf("can't open /dev/mem \n");
		exit(-1);
	}

   /* mmap GPIO */
   gpio_map = mmap(
		NULL,             		// Any adddress in our space will do
		BLOCK_SIZE,       		// Map length
		PROT_READ|PROT_WRITE,	// Enable reading & writting to mapped memory
		MAP_SHARED,       		// Shared with other processes
		mem_fd,           		// File to map
		GPIO_BASE         		// Offset to GPIO peripheral
	);

	close(mem_fd);

	if (gpio_map == MAP_FAILED) 
	{
		printf("mmap error %d\n", (int)gpio_map);
		exit(-1);
	}

	gpio = (volatile unsigned *)gpio_map;	

	INP_GPIO(TS_IRQ_GPIO);
	INP_GPIO(LCD_DC_GPIO);
	OUT_GPIO(LCD_DC_GPIO);
	INP_GPIO(LCD_RESET_GPIO);
	OUT_GPIO(LCD_RESET_GPIO);
}

void app_main_loop_process(void)
{
}

int32_t app_spi_setup(uint8_t channel, uint32_t speed, uint32_t mode)
{
	int32_t fd;
	static int spiBPW = 8U;

	mode &= 0x03U;	
	channel &= 0x01U;	

	if ((fd = (int32_t)open(channel == 0U ? spi_device_0 : spi_device_1, O_RDWR)) < 0)
	{
		return -1;
	}

	spi_fds[channel] = fd;
	spi_speeds[channel] = speed;
	
	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0)
	{
		return -1;
	}

	if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0)
	{
		return -1;
	}

	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
	{
		return -1;
	}

	return fd;
}

int32_t app_spi_transfer(uint8_t channel, const uint8_t *data_in, uint8_t *data_out, uint32_t length)
{
  struct spi_ioc_transfer spi;

  channel &= 0x01U;

  memset (&spi, 0, sizeof(spi));

  spi.tx_buf        = (unsigned long)data_in;
  spi.rx_buf        = (unsigned long)data_out;
  spi.len           = (int)length;
  spi.delay_usecs   = 0;
  spi.speed_hz      = spi_speeds[channel];
  spi.bits_per_word = 8;

  return (int32_t)ioctl(spi_fds [channel], SPI_IOC_MESSAGE(1), &spi);
}
