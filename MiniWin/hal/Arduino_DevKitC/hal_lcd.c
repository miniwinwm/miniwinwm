/*

MIT License

Copyright (c) John Blaiklock 2020 miniwin Embedded Window Manager

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

#ifdef ARDUINO_ARCH_ESP32

/***************
*** INCLUDES ***
***************/

#include <stdbool.h>
#include <string.h>
#include "hal/hal_lcd.h"
#include "miniwin_config.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


/****************
*** CONSTANTS ***
****************/

#define LCD_DISPLAY_WIDTH_PIXELS	240							/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	320							/**< This is the height of the display in pixels irrespective of user specified display rotation */

#define PIN_NUM_MISO 				25							/**< MISO line of LCD controller */
#define PIN_NUM_MOSI 				23							/**< MOSI line of LCD controller */
#define PIN_NUM_CLK  				19							/**< Clock line of LCD controller */
#define PIN_NUM_CS_LCD  			22							/**< CS line of LCD controller */
#define PIN_NUM_DC   				21							/**< Command/Data line of LCD controller */
#define PIN_NUM_RST  				18							/**< RESET line of LCD controller */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static spi_device_handle_t spi_device_handle_lcd;
static spi_transaction_t spi_transactions[6];
DMA_ATTR static uint16_t line_buffer[LCD_DISPLAY_WIDTH_PIXELS];

static int16_t previous_x = -1;
static int16_t previous_width = -1;
static int16_t previous_y = -1;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static inline void filled_rectangle_rotated(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour);
static inline void pixel_rotated(int16_t x, int16_t y, mw_hal_lcd_colour_t colour);
static void write_command(const uint8_t command);
static void write_data(const uint8_t data);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Send a command to the ILI9341 panel. The callback switches the DC line to C first
 *
 * @param command The command byte
 */
static void write_command(const uint8_t command)
{
    spi_transaction_t spi_transaction;

    memset(&spi_transaction, (size_t)0, sizeof(spi_transaction_t)); 		/* zero out the transaction */
    spi_transaction.length = 8;                     						/* command is 8 bits */
    spi_transaction.tx_buffer = &command;               					/* the data is the cmd itself */
    gpio_set_level(PIN_NUM_DC, 0);											/* set DC to command */
    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transaction);  	/* transmit */
}

/**
 * Send a command to the ILI9341 panel. The callback switches the DC line to D first
 *
 * @param dtaa The data byte
 */
static void write_data(const uint8_t data)
{
    spi_transaction_t spi_transaction;

    memset(&spi_transaction, (size_t)0, sizeof(spi_transaction_t)); 		/* zero out the transaction */
    spi_transaction.length = 8;                 							/* len is in bytes, transaction length is in bits */
    spi_transaction.tx_buffer = &data;               						/* data */
    gpio_set_level(PIN_NUM_DC, 1);											/* set DC to data */
    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transaction);  	/* transmit */
}

/**
 * Plot a filled rectangle using already rotated coordinates. Position and size values are not clipped to the screen.
 *
 * @param start_x X position of left edge of rectangle
 * @param start_y Y position of top of rectangle
 * @param width Width of rectangle, pixels plotted are from start_x to (start_x + width) - 1
 * @param height Height of rectangle, pixels plotted are from start_y to (start_y + height) - 1
 * @param colour The colour of the pixel to plot
 */
static inline void IRAM_ATTR filled_rectangle_rotated(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
	int_fast16_t y;
	uint16_t rgb565_colour;
	int_fast16_t i;
	
    if (width > LCD_DISPLAY_WIDTH_PIXELS)
    {
        /* something gone wrong here */
        return;
    }

	/* convert pixel colour from rgb888 to rgb565 format */
	rgb565_colour = (uint16_t)((((uint32_t)colour & 0x00f80000UL) >> 8) |
			(((uint32_t)colour & 0x0000fc00UL) >> 5) |
			(((uint32_t)colour & 0x000000f8UL) >> 3));

	/* swap endianess */
	rgb565_colour = __builtin_bswap16(rgb565_colour);

	for (i = 0U; i < width; i++)
	{
		line_buffer[i] = rgb565_colour;
	}

	spi_device_acquire_bus(spi_device_handle_lcd, portMAX_DELAY);

	if (start_x != previous_x || previous_width != width)
	{
		gpio_set_level(PIN_NUM_DC, 0);
		spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[0]);

		spi_transactions[1].tx_data[1] = (uint8_t)start_x;
		spi_transactions[1].tx_data[3] = (uint8_t)(start_x + width - 1);
		gpio_set_level(PIN_NUM_DC, 1);
		spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[1]);

		previous_x = start_x;
		previous_width = width;
	}

	spi_transactions[5].length = (size_t)(width * 2 * 8);
	spi_transactions[5].rxlength = (size_t)(width * 2 * 8);
	spi_transactions[5].flags = 0UL;
	spi_transactions[5].tx_buffer = line_buffer;

	for (y = start_y; y < (start_y + height); y++)
	{
	    gpio_set_level(PIN_NUM_DC, 0);
	    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[2]);

		spi_transactions[3].tx_data[0] = (uint8_t)(y >> 8);        					/* start row high */
		spi_transactions[3].tx_data[1] = (uint8_t)y;		      					/* start row low */
		spi_transactions[3].tx_data[2] = (uint8_t)(y >> 8);    						/* end row high */
		spi_transactions[3].tx_data[3] = (uint8_t)y;								/* end row low */
	    gpio_set_level(PIN_NUM_DC, 1);
	    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[3]);

	    gpio_set_level(PIN_NUM_DC, 0);
	    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[4]);

	    gpio_set_level(PIN_NUM_DC, 1);
	    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[5]);
	}

	previous_y = y - 1;

	spi_device_release_bus(spi_device_handle_lcd);
}

/**
 * Plot a pixel using already rotated coordinates. Position values are not clipped to the screen.
 *
 * @param start_x X position of pixel
 * @param start_y Y position of pixel
 * @param colour The colour of the pixel to plot
 */
static inline void IRAM_ATTR pixel_rotated(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
	uint16_t rgb565_colour;

	/* convert pixel colour from rgb888 to rgb565 format */
	rgb565_colour = (uint16_t)((((uint32_t)colour & 0x00f80000UL) >> 8) |
			(((uint32_t)colour & 0x0000fc00UL) >> 5) |
			(((uint32_t)colour & 0x000000f8UL) >> 3));

	spi_device_acquire_bus(spi_device_handle_lcd, portMAX_DELAY);

	if (x != previous_x || previous_width != 1)
	{
		gpio_set_level(PIN_NUM_DC, 0);
		spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[0]);

		spi_transactions[1].tx_data[1] = (uint8_t)x;              					/* start column low */
		spi_transactions[1].tx_data[3] = (uint8_t)x;     							/* end column low */
		gpio_set_level(PIN_NUM_DC, 1);
		spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[1]);

		previous_x = x;
		previous_width = 1;
	}

	if (y != previous_y)
	{
		gpio_set_level(PIN_NUM_DC, 0);
		spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[2]);

		spi_transactions[3].tx_data[0] = (uint8_t)(y >> 8);        					/* start row high */
		spi_transactions[3].tx_data[1] = (uint8_t)y;      							/* start row low */
		spi_transactions[3].tx_data[2] = (uint8_t)(y >> 8);    						/* end row high */
		spi_transactions[3].tx_data[3] = (uint8_t)y;								/* end row low */
		gpio_set_level(PIN_NUM_DC, 1);
		spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[3]);

		previous_y = y;
	}

    gpio_set_level(PIN_NUM_DC, 0);
	spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[4]);

	spi_transactions[5].rxlength = (size_t)0;
	spi_transactions[5].tx_data[0] = rgb565_colour >> 8;
    spi_transactions[5].tx_data[1] = rgb565_colour;
	spi_transactions[5].length = (size_t)(2 * 8);
    spi_transactions[5].flags = SPI_TRANS_USE_TXDATA;
    gpio_set_level(PIN_NUM_DC, 1);
	spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[5]);

	spi_device_release_bus(spi_device_handle_lcd);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_lcd_init(void)
{
    spi_bus_config_t spi_bus_config =
    {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 240 * 2
    };

    spi_device_interface_config_t spi_device_interface_config_lcd =
    {
        .clock_speed_hz = 26 * 1000 * 1000,       	/* clock out at 26 MHz */
        .mode = 0,                                	/* SPI mode 0 */
        .spics_io_num = PIN_NUM_CS_LCD,             /* CS pin */
        .queue_size = 7,                          	/* we want to be able to queue 7 transactions at a time */
        .pre_cb = NULL								/* specify no pre-transfer callback */
    };

    /* initialize the SPI bus */
    spi_bus_initialize(HSPI_HOST, &spi_bus_config, 2);

    /* attach the LCD to the SPI bus */
    spi_bus_add_device(HSPI_HOST, &spi_device_interface_config_lcd, &spi_device_handle_lcd);

    /* initialize non-SPI GPIOs */
    gpio_set_direction(PIN_NUM_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_RST, GPIO_MODE_OUTPUT);

    /* reset the display */
    gpio_set_level(PIN_NUM_RST, 0UL);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(PIN_NUM_RST, 1UL);
    vTaskDelay(100 / portTICK_RATE_MS);

	write_command(0x01U);
	vTaskDelay(10 / portTICK_RATE_MS);
	write_command(0xcbU);
	write_data(0x39U);
	write_data(0x2cU);
	write_data(0x00U);
	write_data(0x34U);
	write_data(0x02U);
	write_command(0xcfU);
	write_data(0x00U);
	write_data(0xc1U);
	write_data(0x30U);
	write_command(0xe8U);
	write_data(0x85U);
	write_data(0x00U);
	write_data(0x78U);
	write_command(0xeaU);
	write_data(0x00U);
	write_data(0x00U);
	write_command(0xedU);
	write_data(0x64U);
	write_data(0x03U);
	write_data(0x12U);
	write_data(0x81U);
	write_command(0xf7U);
	write_data(0x20U);
	write_command(0xc0U);
	write_data(0x23U);
	write_command(0xc1U);
	write_data(0x10U);
	write_command(0xc5U);
	write_data(0x3eU);
	write_data(0x28U);
	write_command(0xc7U);
	write_data(0x86U);
	write_command(0x36U);
	write_data(0x48U);
	write_command(0x3aU);
	write_data(0x55U);
	write_command(0xb1U);
	write_data(0x00U);
	write_data(0x18U);
	write_command(0xb6U);
	write_data(0x08U);
	write_data(0x82U);
	write_data(0x27U);
	write_command(0xf2U);
	write_data(0x00U);
	write_command(0x26U);
	write_data(0x01U);
	write_command(0xe0U);
	write_data(0x0fU);
	write_data(0x31U);
	write_data(0x2bU);
	write_data(0x0cU);
	write_data(0x0eU);
	write_data(0x08U);
	write_data(0x4eU);
	write_data(0xf1U);
	write_data(0x37U);
	write_data(0x07U);
	write_data(0x10U);
	write_data(0x03U);
	write_data(0x0eU);
	write_data(0x09U);
	write_data(0x00U);
	write_command(0xe1U);
	write_data(0x00U);
	write_data(0x0eU);
	write_data(0x14U);
	write_data(0x03U);
	write_data(0x11U);
	write_data(0x07U);
	write_data(0x31U);
	write_data(0xc1U);
	write_data(0x48U);
	write_data(0x08U);
	write_data(0x0fU);
	write_data(0x0cU);
	write_data(0x31U);
	write_data(0x36U);
	write_data(0x0fU);
	write_command(0x11U);
	vTaskDelay(120 / portTICK_RATE_MS);
	write_command(0x29U);
	write_command(0x36U);
	write_data(0x48U);

    memset(spi_transactions, 0, sizeof(spi_transactions));

    spi_transactions[0].tx_data[0] = 0x2AU;         	/* column address set */
	spi_transactions[0].length = (size_t)8;
    spi_transactions[0].flags = SPI_TRANS_USE_TXDATA;

	spi_transactions[1].length = (size_t)(4 * 8);
    spi_transactions[1].flags = SPI_TRANS_USE_TXDATA;
	spi_transactions[1].tx_data[0] = 0U;              	/* start column high */
	spi_transactions[1].tx_data[2] = 0U;       			/* end column high */

    spi_transactions[2].tx_data[0] = 0x2BU;          	/* page address set */
	spi_transactions[2].length = (size_t)8;
    spi_transactions[2].flags = SPI_TRANS_USE_TXDATA;

	spi_transactions[3].length = (size_t)(4 * 8);
    spi_transactions[3].flags = SPI_TRANS_USE_TXDATA;

    spi_transactions[4].tx_data[0] = 0x2CU;          	/* memory write */
	spi_transactions[4].length = (size_t)8;
    spi_transactions[4].flags = SPI_TRANS_USE_TXDATA;
}

int16_t mw_hal_lcd_get_display_width(void)
{
	return (LCD_DISPLAY_WIDTH_PIXELS);
}

int16_t mw_hal_lcd_get_display_height(void)
{
	return (LCD_DISPLAY_HEIGHT_PIXELS);
}

void inline IRAM_ATTR mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
#if defined(MW_DISPLAY_ROTATION_0)
	pixel_rotated(x, y, colour);
#elif defined(MW_DISPLAY_ROTATION_90)
	pixel_rotated(y, LCD_DISPLAY_HEIGHT_PIXELS - 1 - x, colour);
#elif defined (MW_DISPLAY_ROTATION_180)
	pixel_rotated(LCD_DISPLAY_WIDTH_PIXELS - x - 1, LCD_DISPLAY_HEIGHT_PIXELS - 1 - y, colour);
#elif defined (MW_DISPLAY_ROTATION_270)
	pixel_rotated(LCD_DISPLAY_WIDTH_PIXELS - 1 - y, x, colour);
#endif
}

void inline IRAM_ATTR mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
#if defined(MW_DISPLAY_ROTATION_0)
	filled_rectangle_rotated(start_x, start_y, width, height, colour);
#elif defined(MW_DISPLAY_ROTATION_90)
	filled_rectangle_rotated(start_y, LCD_DISPLAY_HEIGHT_PIXELS - start_x - width, height, width, colour);
#elif defined (MW_DISPLAY_ROTATION_180)
	filled_rectangle_rotated(LCD_DISPLAY_WIDTH_PIXELS - start_x - width, LCD_DISPLAY_HEIGHT_PIXELS - start_y - height, width, height, colour);
#elif defined (MW_DISPLAY_ROTATION_270)
	filled_rectangle_rotated(LCD_DISPLAY_WIDTH_PIXELS - start_y - height, start_x, height, width, colour);
#endif
}

void mw_hal_lcd_colour_bitmap_clip(int16_t image_start_x,
		int16_t image_start_y,
		uint16_t bitmap_width,
		uint16_t bitmap_height,
		int16_t clip_start_x,
		int16_t clip_start_y,
		int16_t clip_width,
		int16_t clip_height,
		const uint8_t *image_data)
{
	int16_t x;
	int16_t y;
	mw_hal_lcd_colour_t pixel_colour;
	uint16_t rgb565_colour;

#if defined(MW_DISPLAY_ROTATION_0)
	/* check if pixels in data buffer are all to be drawn and if so use dma */
	if (image_start_x >= clip_start_x &&
			image_start_y >= clip_start_y &&
			image_start_x + (int16_t)bitmap_width <= clip_start_x + clip_width &&
			image_start_y + (int16_t)bitmap_height <= clip_start_y + clip_height &&
            bitmap_width <= LCD_DISPLAY_WIDTH_PIXELS)
	{
		spi_device_acquire_bus(spi_device_handle_lcd, portMAX_DELAY);
		
		if (image_start_x != previous_x || previous_width != bitmap_width)
		{
			gpio_set_level(PIN_NUM_DC, 0);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[0]);

			spi_transactions[1].tx_data[1] = (uint8_t)image_start_x;
			spi_transactions[1].tx_data[3] = (uint8_t)(image_start_x + bitmap_width - 1);
			gpio_set_level(PIN_NUM_DC, 1);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[1]);

			previous_x = image_start_x;
			previous_width = bitmap_width;
		}		
		
		spi_transactions[5].length = (size_t)(bitmap_width * 2 * 8);
		spi_transactions[5].rxlength = (size_t)(bitmap_width * 2 * 8);
		spi_transactions[5].flags = 0UL;
		spi_transactions[5].tx_buffer = line_buffer;
		
		for (y = 0; y < (int16_t)bitmap_height; y++)
		{
			for (x = 0; x < (int16_t)bitmap_width; x++)
			{
				pixel_colour = *(2 + image_data + (x + y * (int16_t)bitmap_width) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(1 + image_data + (x + y * (int16_t)bitmap_width) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(image_data + (x + y * (int16_t)bitmap_width) * 3);
				
				rgb565_colour = (uint16_t)((((uint32_t)pixel_colour & 0x00f80000UL) >> 8) |
							(((uint32_t)pixel_colour & 0x0000fc00UL) >> 5) |
							(((uint32_t)pixel_colour & 0x000000f8UL) >> 3));
				
				line_buffer[x] = __builtin_bswap16(rgb565_colour);
			}
			
		    gpio_set_level(PIN_NUM_DC, 0);
		    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[2]);

			spi_transactions[3].tx_data[0] = (uint8_t)((image_start_y + y) >> 8);        		/* start row high */
			spi_transactions[3].tx_data[1] = (uint8_t)(image_start_y + y);		      			/* start row low */
			spi_transactions[3].tx_data[2] = (uint8_t)((image_start_y + y) >> 8);    			/* end row high */
			spi_transactions[3].tx_data[3] = (uint8_t)(image_start_y + y);						/* end row low */
		    gpio_set_level(PIN_NUM_DC, 1);
		    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[3]);

		    gpio_set_level(PIN_NUM_DC, 0);
		    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[4]);

		    gpio_set_level(PIN_NUM_DC, 1);
		    spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[5]);			
		}
		
		previous_y = image_start_y + y - 1;

		spi_device_release_bus(spi_device_handle_lcd);
		
		return;
	}
#endif	

	for (y = 0; y < (int16_t)bitmap_height; y++)
	{
		for (x = 0; x < (int16_t)bitmap_width; x++)
		{
			if (x + image_start_x >= clip_start_x &&
					x + image_start_x < clip_start_x + clip_width &&
					y + image_start_y >= clip_start_y &&
					y + image_start_y < clip_start_y + clip_height)
			{
				pixel_colour = *(2 + image_data + (x + y * (int16_t)bitmap_width) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(1 + image_data + (x + y * (int16_t)bitmap_width) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(image_data + (x + y * (int16_t)bitmap_width) * 3);
				mw_hal_lcd_pixel(x + image_start_x, y + image_start_y, pixel_colour);
			}
		}
	}
}

void mw_hal_lcd_monochrome_bitmap_clip(int16_t image_start_x,
	int16_t image_start_y,
	uint16_t bitmap_width,
	uint16_t bitmap_height,
	int16_t clip_start_x,
	int16_t clip_start_y,
	int16_t clip_width,
	int16_t clip_height,
	mw_hal_lcd_colour_t fg_colour,
	mw_hal_lcd_colour_t bg_colour,
	const uint8_t* image_data)
{
	int16_t x;
	int16_t y;
	int16_t a;
	uint8_t image_byte;
	uint8_t mask;
	int16_t array_width_bytes;
	uint16_t rgb565_fg_colour = (mw_hal_lcd_colour_t)0;
	uint16_t rgb565_bg_colour = (mw_hal_lcd_colour_t)0;
	bool use_line_buffer = false;

#if defined(MW_DISPLAY_ROTATION_0)
	if (image_start_x >= clip_start_x &&
		image_start_y >= clip_start_y &&
		image_start_x + (int16_t)bitmap_width <= clip_start_x + clip_width &&
		image_start_y + (int16_t)bitmap_height <= clip_start_y + clip_height &&
        bitmap_width <= LCD_DISPLAY_WIDTH_PIXELS)
	{
		use_line_buffer = true;
	}
#endif

	if (use_line_buffer)
	{
		rgb565_fg_colour = (uint16_t)((((uint32_t)fg_colour & 0x00f80000UL) >> 8) |
			(((uint32_t)fg_colour & 0x0000fc00UL) >> 5) |
			(((uint32_t)fg_colour & 0x000000f8UL) >> 3));

		rgb565_fg_colour = __builtin_bswap16(rgb565_fg_colour);

		rgb565_bg_colour = (uint16_t)((((uint32_t)bg_colour & 0x00f80000UL) >> 8) |
			(((uint32_t)bg_colour & 0x0000fc00UL) >> 5) |
			(((uint32_t)bg_colour & 0x000000f8UL) >> 3));

		rgb565_bg_colour = __builtin_bswap16(rgb565_bg_colour);

		spi_device_acquire_bus(spi_device_handle_lcd, portMAX_DELAY);

		if (image_start_x != previous_x || bitmap_width != previous_width)
		{
			gpio_set_level(PIN_NUM_DC, 0);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[0]);

			spi_transactions[1].tx_data[1] = (uint8_t)image_start_x;
			spi_transactions[1].tx_data[3] = (uint8_t)(image_start_x + bitmap_width - 1);
			gpio_set_level(PIN_NUM_DC, 1);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[1]);

			previous_x = image_start_x;
			previous_width = bitmap_width;
		}

		spi_transactions[5].length = (size_t)(bitmap_width * 2 * 8);
		spi_transactions[5].rxlength = (size_t)(bitmap_width * 2 * 8);
		spi_transactions[5].flags = 0UL;
		spi_transactions[5].tx_buffer = line_buffer;
	}
	
	array_width_bytes = (int16_t)bitmap_width / 8;
	if (bitmap_width % 8U > 0U)
	{
		array_width_bytes++;
	}

	for (y = 0; y < (int16_t)bitmap_height; y++)
	{
		for (a = 0; a < array_width_bytes; a++)
		{
			image_byte = image_data[y * array_width_bytes + a];
			mask = 0x80U;
			for (x = 0; x < 8; x++)
			{
				if ((a * 8) + x == (int16_t)bitmap_width)
				{
					break;
				}
				if ((a * 8) + x + image_start_x >= clip_start_x &&
						(a * 8) + x + image_start_x < clip_start_x + clip_width &&
						y + image_start_y >= clip_start_y &&
						y + image_start_y < clip_start_y + clip_height)
				{
					if (use_line_buffer)
					{
						if ((image_byte & mask) == 0U)
						{
							line_buffer[(a * 8) + x] = rgb565_fg_colour;
						}
						else
						{
							line_buffer[(a * 8) + x] = rgb565_bg_colour;
						}
					}
					else
					{
						if ((image_byte & mask) == 0U)
						{
							mw_hal_lcd_pixel((a * 8) + x + image_start_x, y + image_start_y, fg_colour);
						}
						else
						{
							mw_hal_lcd_pixel((a * 8) + x + image_start_x, y + image_start_y, bg_colour);
						}
					}
				}
				mask >>= 1;
			}
		}
		
		if (use_line_buffer)
		{
			gpio_set_level(PIN_NUM_DC, 0);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[2]);

			spi_transactions[3].tx_data[0] = (uint8_t)((image_start_y + y) >> 8);        		/* start row high */
			spi_transactions[3].tx_data[1] = (uint8_t)(image_start_y + y);		      			/* start row low */
			spi_transactions[3].tx_data[2] = (uint8_t)((image_start_y + y) >> 8);    			/* end row high */
			spi_transactions[3].tx_data[3] = (uint8_t)(image_start_y + y);						/* end row low */
			gpio_set_level(PIN_NUM_DC, 1);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[3]);

			gpio_set_level(PIN_NUM_DC, 0);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[4]);

			gpio_set_level(PIN_NUM_DC, 1);
			spi_device_polling_transmit(spi_device_handle_lcd, &spi_transactions[5]);
		}
	}
	
#if defined(MW_DISPLAY_ROTATION_0)
	previous_y = image_start_y + y - 1;
	spi_device_release_bus(spi_device_handle_lcd);
#endif
}

#endif
