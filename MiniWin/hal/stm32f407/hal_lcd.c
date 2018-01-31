/*

MIT License

Copyright (c) John Blaiklock 2018 miniwin Embedded Window Manager

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
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_conf.h"
#include "hal/hal_lcd.h"
#include "hal/hal_delay.h"

/****************
*** CONSTANTS ***
****************/

#define LCD_HW_ACCELERATION

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

static void write_command(uint8_t register_address, uint16_t data);
static void set_register_address(uint8_t data);
static void write_data(uint16_t data);

#ifdef LCD_HW_ACCELERATION
void set_window(uint8_t x1, uint16_t y1, uint8_t x2, uint16_t y2);
#endif

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Write a command into a register
 *
 * @param address The lcd controller register address
 * @param data The value of the command to put into the register
 */
static void write_command(uint8_t register_address, uint16_t data)
{
	set_register_address(register_address);
	write_data(data);
}

#ifdef LCD_HW_ACCELERATION

/**
 * Set the plotting window in the lcd controller; all subsequent pixel writes will be within this window 
 *
 * @param x1 Left edge of window
 * @param y1 Top edge of window
 * @param x2 Right edge of window
 * @param y2 Bottom edge of window
 */
void set_window(uint8_t x1, uint16_t y1, uint8_t x2, uint16_t y2)
{
	write_command(0x44, (x2 << 8) + x1);
	write_command(0x45, y1);
	write_command(0x46, y2);
	write_command(0x4e, x1);
	write_command(0x4f, y1);

	set_register_address(0x22);
}

/**
 * Write an address onto the data bus to the lcd, this has RS line low
 *
 * @data The 16 bit data value to write
 */
static void set_register_address(uint8_t data)
{
	/* RS = 0 */
    GPIOD->BSRRH = GPIO_Pin_11;

    /* write data */
	GPIOE->ODR = data;

	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;
}

/**
 * Write data onto the data bus to the lcd, this has RS line high
 *
 * @data The 16 bit data value to write
 */
static void write_data(uint16_t data)
{
    /* RS = 1 */
    GPIOD->BSRRL = GPIO_Pin_11;

    /* write data */
	GPIOE->ODR = data;

	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;
}
#else

/**
 * Write an address onto the data bus to the lcd, this has RS line low
 *
 * @data The 16 bit data value to write
 */
static void set_register_address(uint8_t data)
{
	/* RS = 0 */
    GPIO_ResetBits(GPIOD, GPIO_Pin_11 );

    /* write data */
    GPIO_Write(GPIOE, data);

	/* WR = 0 */
    GPIO_ResetBits(GPIOD, GPIO_Pin_5 );
	/* WR = 1 */
    GPIO_SetBits(GPIOD, GPIO_Pin_5 );
}

/**
 * Write data onto the data bus to the lcd, this has RS line high
 *
 * @data The 16 bit data value to write
 */
static void write_data(uint16_t data)
{
    /* RS = 1 */
    GPIO_SetBits(GPIOD, GPIO_Pin_11 );

    /* write data */
	GPIO_Write(GPIOE, data);

	/* WR = 0 */
    GPIO_ResetBits(GPIOD, GPIO_Pin_5 );
	/* WR = 1 */
    GPIO_SetBits(GPIOD, GPIO_Pin_5 );
}
#endif

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_lcd_init(void)
{
	/* init the i/o */
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_7 | GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* reset the display */
    GPIO_SetBits(GPIOD, GPIO_Pin_1 );
    mw_hal_delay_ms(5);
	GPIO_ResetBits(GPIOD, GPIO_Pin_1);
    mw_hal_delay_ms(30);
    GPIO_SetBits(GPIOD, GPIO_Pin_1 );
    mw_hal_delay_ms(20);

	/* RD = 1 */
    GPIO_SetBits(GPIOD, GPIO_Pin_4 );

	/* WR = 1 */
    GPIO_SetBits(GPIOD, GPIO_Pin_5 );

	/* CS = 1 */
    GPIO_ResetBits(GPIOD, GPIO_Pin_7 );

    write_command(0x00,0x0001);		/* oscillator on/off */
    write_command(0x03,0xA8A4);		/* power control 1 */
    write_command(0x0C,0x0000);		/* power control 2 */
    write_command(0x0D,0x080C);		/* power control 3 */
    write_command(0x0E,0x2B00);		/* power control 4 */
    write_command(0x1E,0x00B0);		/* power control 5 */
    write_command(0x01,0x2B3F);		/* driver output control */
    write_command(0x02,0x0600);		/* LCD drive AC control */
    write_command(0x10,0x0000);		/* sleep mode */
    write_command(0x11,0x6070);		/* entry mode */
    write_command(0x05,0x0000);		/* compare register 1 */
    write_command(0x06,0x0000);		/* compare register 2 */
    write_command(0x16,0xEF1C);		/* horizontal porch */
    write_command(0x17,0x0003);		/* vertical porch */
    write_command(0x07,0x0233);		/* display control */
    write_command(0x0B,0x0000);		/* frame cycle control */
    write_command(0x0F,0x0000);		/* gate scan start pos */
    write_command(0x41,0x0000);		/* vertical scroll control 1 */
    write_command(0x42,0x0000);		/* vertical scroll control 2 */
    write_command(0x48,0x0000);		/* first window start */
    write_command(0x49,0x013F);		/* first window end */
    write_command(0x4A,0x0000);		/* second window start */
    write_command(0x4B,0x0000);		/* second window end */
    write_command(0x44,0xEF00);		/* horizontal ram address pos */
    write_command(0x45,0x0000);		/* vertical ram address start pos */
    write_command(0x46,0x013F);		/* vertical ram address end pos */
    write_command(0x30,0x0707);		/* gamma control */
    write_command(0x31,0x0204);
    write_command(0x32,0x0204);
    write_command(0x33,0x0502);
    write_command(0x34,0x0507);
    write_command(0x35,0x0204);
    write_command(0x36,0x0204);
    write_command(0x37,0x0502);
    write_command(0x3A,0x0302);
    write_command(0x3B,0x0302);
    write_command(0x23,0x0000);		/* ram write data mask 1 */
    write_command(0x24,0x0000);		/* ram write data mask 2 */
    write_command(0x4f,0x0000);		/* ram x address counter */
    write_command(0x4e,0x0000);		/* ram y address counter */

    mw_hal_lcd_filled_rectangle(0, 0, MW_HAL_LCD_WIDTH, MW_HAL_LCD_HEIGHT, MW_HAL_LCD_WHITE);
}

#ifdef LCD_HW_ACCELERATION
void mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
	/* RS = 0 */
    GPIOD->BSRRH = GPIO_Pin_11;
    /* write data */
	GPIOE->ODR = 0x4e;
	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;
	write_data(x);
    /* RS = 1 */
    GPIOD->BSRRL = GPIO_Pin_11;
    /* write data */
	GPIOE->ODR = x;
	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;

	/* RS = 0 */
    GPIOD->BSRRH = GPIO_Pin_11;
    /* write data */
	GPIOE->ODR = 0x4f;
	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;
    /* RS = 1 */
    GPIOD->BSRRL = GPIO_Pin_11;
    /* write data */
	GPIOE->ODR = y;
	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;

	/* RS = 0 */
    GPIOD->BSRRH = GPIO_Pin_11;
    /* write data */
	GPIOE->ODR = 0x22;
	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;
    /* RS = 1 */
    GPIOD->BSRRL = GPIO_Pin_11;
    /* write data */
	GPIOE->ODR = colour;
	/* WR = 0 */
	GPIOD->BSRRH = GPIO_Pin_5;
	/* WR = 1 */
	GPIOD->BSRRL = GPIO_Pin_5;
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		uint16_t width,
		uint16_t height,
		mw_hal_lcd_colour_t colour)
{
	int16_t end_x;
	int16_t end_y;
	int32_t n;
	int32_t pixels;

	end_x = start_x + width - 1;
	end_y = start_y + height - 1;

#ifndef NDEBUG
	/* check the coordinates used to set hardware window */
	if (start_x < 0 || start_y < 0 || end_x >= MW_HAL_LCD_WIDTH || end_y >= MW_HAL_LCD_HEIGHT)
	{
		/* oops! */
		while (true);
	}
#endif

	/* set window in lcd hardware */
	set_window(start_x, start_y, end_x, end_y);

	/* write the colour of the rectangle once */
	write_data(colour);

	/* clock in all the pixels */
	pixels = width * height;
	for (n = 0; n < pixels; n++)
	{
		/* WR = 0 */
		GPIOD->BSRRH = GPIO_Pin_5;
		/* WR = 1 */
		GPIOD->BSRRL = GPIO_Pin_5;
	}
}

void mw_hal_lcd_colour_bitmap_clip(int16_t image_start_x,
		int16_t image_start_y,
		uint16_t image_data_width_pixels,
		uint16_t image_data_height_pixels,
		int16_t clip_start_x,
		int16_t clip_start_y,
		uint16_t clip_width,
		uint16_t clip_height,
		const mw_hal_lcd_colour_t *data)
{
	uint16_t x;
	uint16_t y;
	mw_hal_lcd_colour_t pixel_colour;
	uint16_t image_end_x;
	uint16_t image_end_y;
	uint16_t start_pixel_in_bitmap_row;
	uint16_t start_pixel_in_bitmap_column;
	int16_t window_left;
	int16_t window_top;
	int16_t window_right;
	int16_t window_bottom;
	uint16_t pixel_counter_x;
	uint16_t pixel_counter_y;

	image_end_x = image_start_x + image_data_width_pixels - 1;
	image_end_y = image_start_y + image_data_height_pixels - 1;

	/* check if bitmap can be plotted with no clipping */
	if (image_start_x >= clip_start_x &&
			image_end_x < clip_start_x + clip_width &&
			image_start_y >= clip_start_y &&
			image_end_y < clip_start_y + clip_height)
	{
		/* clipping not needed so set window for whole bitmap and clock in data */
		set_window(image_start_x, image_start_y, image_end_x, image_end_y);

	    /* RS = 1 */
		GPIOD->BSRRL = GPIO_Pin_11;

		for (y = 0; y < image_data_height_pixels; y++)
		{
			for (x = 0; x < image_data_width_pixels; x++)
			{
			    /* write data */
				GPIOE->ODR = data[y * image_data_width_pixels + x];
				/* WR = 0 */
				GPIOD->BSRRH = GPIO_Pin_5;
				/* WR = 1 */
				GPIOD->BSRRL = GPIO_Pin_5;
			}
		}

		return;
	}

	/* clipping is needed, first find hardware window edges */

	/* left edge */
	if (clip_start_x > image_start_x)
	{
		start_pixel_in_bitmap_row = clip_start_x - image_start_x;
		window_left = clip_start_x;
	}
	else
	{
		start_pixel_in_bitmap_row = 0;
		window_left = image_start_x;
	}

	/* right edge */
	if (clip_start_x + clip_width > image_start_x + image_data_width_pixels)
	{
		window_right = image_start_x + image_data_width_pixels - 1;
	}
	else
	{
		window_right = clip_start_x + clip_width - 1;
	}

	/* top edge */
	if (clip_start_y > image_start_y)
	{
		start_pixel_in_bitmap_column = clip_start_y - image_start_y;
		window_top = clip_start_y;
	}
	else
	{
		start_pixel_in_bitmap_column = 0;
		window_top = image_start_y;
	}

	/* bottom edge */
	if (clip_start_y + clip_height > image_start_y + image_data_height_pixels)
	{
		window_bottom = image_start_y + image_data_height_pixels - 1;
	}
	else
	{
		window_bottom = clip_start_y + clip_height - 1;
	}

#ifndef NDEBUG
	/* check the coordinates used to set hardware window */
	if (window_left < 0 || window_top < 0 || window_right >= MW_HAL_LCD_WIDTH || window_bottom >= MW_HAL_LCD_HEIGHT)
	{
		/* oops! */
		while (true);
	}
#endif

	/* set window in lcd hardware */
	set_window(window_left, window_top, window_right, window_bottom);

    /* RS = 1 */
	GPIOD->BSRRL = GPIO_Pin_11;

	/* extract each pixel from bit map, set colour and then clock it in */
	pixel_counter_y = 0;
	for (y = window_top; y <= window_bottom; y++)
	{
		pixel_counter_x = 0;
		for (x = window_left; x <= window_right; x++)
		{
			pixel_colour = *(data + ((start_pixel_in_bitmap_column + pixel_counter_y) * image_data_width_pixels) + pixel_counter_x + start_pixel_in_bitmap_row);
			pixel_counter_x++;

		    /* write data */
			GPIOE->ODR = pixel_colour;
			/* WR = 0 */
			GPIOD->BSRRH = GPIO_Pin_5;
			/* WR = 1 */
			GPIOD->BSRRL = GPIO_Pin_5;
		}
		pixel_counter_y++;
	}
}
#else
void mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
	write_command(0x4e, x);
	write_command(0x4f, y);
	write_command(0x22, colour);
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		uint16_t width,
		uint16_t height,
		mw_hal_lcd_colour_t colour)
{
	int16_t end_x;
	int16_t end_y;
	uint16_t x;
	uint16_t y;

	/* set window in lcd hardware */
	end_x = start_x + width - 1;
	end_y = start_y + height - 1;

	for (x = start_x; x <= end_x; x++)
	{
		for (y = start_y; y <= end_y; y++)
		{
			mw_hal_lcd_pixel(x, y, colour);
		}
	}
}

void mw_hal_lcd_colour_bitmap_clip(int16_t image_start_x,
		int16_t image_start_y,
		uint16_t image_data_width_pixels,
		uint16_t image_data_height_pixels,
		int16_t clip_start_x,
		int16_t clip_start_y,
		uint16_t clip_width,
		uint16_t clip_height,
		const mw_hal_lcd_colour_t *data)
{
	uint16_t x;
	uint16_t y;
	mw_hal_lcd_colour_t pixel_colour;

	for (y = 0; y < image_data_height_pixels - 1; y++)
	{
		for (x = 0; x < image_data_width_pixels - 1; x++)
		{
			pixel_colour = *(data + (y * image_data_width_pixels) + x);
			if (x + image_start_x >= clip_start_x &&
					x + image_start_x < clip_start_x + clip_width &&
					y + image_start_y >= clip_start_y &&
					y + image_start_y < clip_start_y + clip_height)
			{
				mw_hal_lcd_pixel(x + image_start_x, y + image_start_y, pixel_colour);
			}
		}

	}
}
#endif

// todo optimise this
void mw_hal_lcd_monochrome_bitmap_clip(int16_t image_start_x,
		int16_t image_start_y,
		uint16_t bitmap_width,
		uint16_t bitmap_height,
		int16_t clip_start_x,
		int16_t clip_start_y,
		uint16_t clip_width,
		uint16_t clip_height,
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

	array_width_bytes = bitmap_width >> 3;
	if (bitmap_width % 8 > 0)
	{
		array_width_bytes++;
	}

	for (y = 0; y < bitmap_height; y++)
	{
		for (a = 0; a < array_width_bytes; a++)
		{
			image_byte = image_data[y * array_width_bytes + a];
			mask = 0x80;
			for (x = 0; x < 8; x++)
			{
				if ((a << 3) + x == bitmap_width)
				{
					break;
				}
				if ((a << 3) + x + image_start_x >= clip_start_x &&
						(a << 3) + x + image_start_x < clip_start_x + clip_width &&
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
				mask >>= 1;
			}
		}
	}
}
