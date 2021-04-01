/*

MIT License

Copyright (c) John Blaiklock 2021 miniwin Embedded Window Manager

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:g

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

#ifdef RASPBERRY_PI_ZERO_W

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include "bcm2835.h"
#include "hal/hal_lcd.h"
#include "miniwin_config.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

#define LCD_DISPLAY_WIDTH_PIXELS	240							/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	320							/**< This is the height of the display in pixels irrespective of user specified display rotation */
const static uint8_t window_x_command = 0x2aU;					/**< SPI command to set x bounds of plotting window */
const static uint8_t window_y_command = 0x2bu;					/**< SPI command to set y bounds of plotting window */
const static uint8_t pixel_data_command = 0x2cu;				/**< SPI command to send pixel data to plotting window */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static uint16_t line_buffer[LCD_DISPLAY_WIDTH_PIXELS];
static int16_t previous_x = -1;
static int16_t previous_width = -1;
static int16_t previous_y = -1;
static uint8_t window_x_bounds[4] = {0};
static uint8_t window_y_bounds[4] = {0};

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void write_command(const uint8_t command);
static void write_data(const uint8_t data);
static inline void pixel_rotated(int16_t x, int16_t y, mw_hal_lcd_colour_t colour);
static inline void filled_rectangle_rotated(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Plot a pixel using already rotated coordinates. Position values are not clipped to the screen.
 *
 * @param start_x X position of pixel
 * @param start_y Y position of pixel
 * @param colour The colour of the pixel to plot
 */
static inline void pixel_rotated(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
	uint16_t rgb565_colour;
	char dummy;

	/* convert pixel colour from rgb888 to rgb565 format */
	rgb565_colour = (uint16_t)((((uint32_t)colour & 0x00f80000UL) >> 8) |
			(((uint32_t)colour & 0x0000fc00UL) >> 5) |
			(((uint32_t)colour & 0x000000f8UL) >> 3));
    
    /* swap endianess */
	rgb565_colour = __builtin_bswap16(rgb565_colour);
  
	if (x != previous_x || previous_width != 1)
	{
	   	bcm2835_gpio_write(GPIO_LCD_DC, 0);		
        bcm2835_spi_transfernb((char *)&window_x_command, &dummy, (uint32_t)sizeof(window_x_command));

	   	bcm2835_gpio_write(GPIO_LCD_DC, 1);		
	   	window_x_bounds[0] = 0U;		
        window_x_bounds[1] = (uint8_t)x;
        window_x_bounds[2] = 0U;
        window_x_bounds[3] = (uint8_t)x;
        bcm2835_spi_transfern((char *)&window_x_bounds, (uint32_t)sizeof(window_x_bounds));

		previous_x = x;
		previous_width = 1;
	}

	if (y != previous_y)
	{
	   	bcm2835_gpio_write(GPIO_LCD_DC, 0);				
        bcm2835_spi_transfernb((char *)&window_y_command, &dummy, (uint32_t)sizeof(window_y_command));        
        
	   	bcm2835_gpio_write(GPIO_LCD_DC, 1);				
        window_y_bounds[0] = (uint8_t)(y >> 8);
        window_y_bounds[1] = (uint8_t)y;
        window_y_bounds[2] = (uint8_t)(y >> 8);
        window_y_bounds[3] = (uint8_t)y;
        bcm2835_spi_transfern((char *)&window_y_bounds, (uint32_t)sizeof(window_y_bounds));        

		previous_y = y;
	}

	bcm2835_gpio_write(GPIO_LCD_DC, 0);			
    bcm2835_spi_transfernb((char *)&pixel_data_command, &dummy, (uint32_t)sizeof(pixel_data_command));    
        
   	bcm2835_gpio_write(GPIO_LCD_DC, 1);			
    bcm2835_spi_transfern((char *)&rgb565_colour, sizeof(rgb565_colour));        
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
static inline void filled_rectangle_rotated(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
	int16_t y;
	uint16_t rgb565_colour;
	int16_t i;
	char dummy;
    
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

	if (start_x != previous_x || previous_width != width)
	{
	   	bcm2835_gpio_write(GPIO_LCD_DC, 0);			
        bcm2835_spi_transfernb((char *)&window_x_command, &dummy, (uint32_t)sizeof(window_x_command));        

		window_x_bounds[0] = 0U;
        window_x_bounds[1] = (uint8_t)start_x;
        window_x_bounds[2] = 0U;
        window_x_bounds[3] = (uint8_t)(start_x + width - 1);
	   	bcm2835_gpio_write(GPIO_LCD_DC, 1);				
        bcm2835_spi_transfern((char *)&window_x_bounds, (uint32_t)sizeof(window_x_bounds));        

		previous_x = start_x;
		previous_width = width;
	}

	bcm2835_gpio_write(GPIO_LCD_DC, 0);			
    bcm2835_spi_transfernb((char *)&window_y_command, &dummy, (uint32_t)sizeof(window_y_command));        

    window_y_bounds[0] = (uint8_t)(start_y >> 8);
    window_y_bounds[1] = (uint8_t)start_y;
    window_y_bounds[2] = (uint8_t)((start_y + height - 1) >> 8);
    window_y_bounds[3] = (uint8_t)(start_y + height - 1);
	bcm2835_gpio_write(GPIO_LCD_DC, 1);			
    bcm2835_spi_transfern((char *)&window_y_bounds, (uint32_t)sizeof(window_y_bounds));            

	bcm2835_gpio_write(GPIO_LCD_DC, 0);			
    bcm2835_spi_transfernb((char *)&pixel_data_command, &dummy, (uint32_t)sizeof(pixel_data_command));        

	bcm2835_gpio_write(GPIO_LCD_DC, 1);			
	for (y = 0; y < height; y++)
	{
		for (i = 0U; i < width; i++)
		{
			line_buffer[i] = rgb565_colour;
		}		
		bcm2835_spi_transfern((char *)line_buffer, (uint32_t)(width * 2));                    
	}

	previous_y = -1;
}

/**
 * Send a command byte to the ILI9341 panel. 
 *
 * @param command The command byte
 */
static void write_command(const uint8_t command)
{  
	uint8_t c = command;

	bcm2835_gpio_write(GPIO_LCD_DC, 0);			
	bcm2835_spi_transfern((char *)&c, (uint32_t)sizeof(c));                    	
}

/**
 * Send a data byte to the ILI9341 panel. 
 *
 * @param data The data byte
 */
static void write_data(const uint8_t data)
{
	uint8_t d = data;

	bcm2835_gpio_write(GPIO_LCD_DC, 1);	
	bcm2835_spi_transfern((char *)&d, (uint32_t)sizeof(d));		
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_lcd_init(void)
{
   	bcm2835_gpio_write(GPIO_LCD_RESET, 0);			
	usleep(100000);
	bcm2835_gpio_write(GPIO_LCD_RESET, 1);			
	usleep(100000);

	write_command(0x01U);
	usleep(10000);
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
	usleep(120000);
	write_command(0x29U);
	write_command(0x36U);
	write_data(0x48U);
}

int16_t mw_hal_lcd_get_display_width(void)
{
	return (LCD_DISPLAY_WIDTH_PIXELS);
}

int16_t mw_hal_lcd_get_display_height(void)
{
	return (LCD_DISPLAY_HEIGHT_PIXELS);
}

void mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
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

void mw_hal_lcd_filled_rectangle(int16_t start_x,
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
	uint16_t x;
	uint16_t y;
	mw_hal_lcd_colour_t pixel_colour;

	for (y = 0; y < bitmap_height; y++)
	{
		for (x = 0; x < bitmap_width; x++)
		{
			if (x + image_start_x >= clip_start_x &&
					x + image_start_x < clip_start_x + clip_width &&
					y + image_start_y >= clip_start_y &&
					y + image_start_y < clip_start_y + clip_height)
			{
				pixel_colour = *(image_data + (x + y * bitmap_width) * 3);
				pixel_colour |= *(1 + image_data + (x + y * bitmap_width) * 3) << 8;
				pixel_colour |= *(2 + image_data + (x + y * bitmap_width) * 3) << 16;
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
		const uint8_t *image_data)
{
	int16_t x;
	int16_t y;
	uint8_t a;
	uint8_t colour;
	uint8_t image_byte;
	uint8_t mask;
	uint8_t array_width_bytes;

	array_width_bytes = bitmap_width >> 3U;
	if (bitmap_width % 8U > 0U)
	{
		array_width_bytes++;
	}

	for (y = 0; y < bitmap_height; y++)
	{
		for (a = 0U; a < array_width_bytes; a++)
		{
			image_byte = image_data[y * array_width_bytes + a];
			mask = 0x80U;
			for (x = 0; x < 8; x++)
			{
				if ((a << 3U) + x == bitmap_width)
				{
					break;
				}
				if ((a << 3U) + x + image_start_x >= clip_start_x &&
						(a << 3U) + x + image_start_x < clip_start_x + clip_width &&
						y + image_start_y >= clip_start_y &&
						y + image_start_y < clip_start_y + clip_height)
				{
					colour = !(image_byte & mask);
					if (colour)
					{
						mw_hal_lcd_pixel((a << 3) + x + image_start_x, y + image_start_y, fg_colour);
					}
					else
					{
						mw_hal_lcd_pixel((a << 3) + x + image_start_x, y + image_start_y, bg_colour);
					}
				}
				mask >>= 1U;
			}
		}
	}
}

#endif
