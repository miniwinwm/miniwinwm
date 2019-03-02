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

#ifdef STM32F407xx

/***************
*** INCLUDES ***
***************/

#include <stdbool.h>
#include "hal/hal_lcd.h"
#include "hal/hal_delay.h"
#include "miniwin_config.h"
#include "stm32f4xx_hal.h"

/****************
*** CONSTANTS ***
****************/

#define LCD_DISPLAY_WIDTH_PIXELS	240							/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	320							/**< This is the height of the display in pixels irrespective of user specified display rotation */

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

static void write_command(uint8_t register_address, uint16_t data);
static void set_register_address(uint8_t data);
static void write_data(uint16_t data);

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

/**
 * Write an address onto the data bus to the lcd, this has RS line low
 *
 * @data The 16 bit data value to write
 */
static void set_register_address(uint8_t data)
{
	/* RS = 0 */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET );

    /* write data */
    GPIOE->ODR = (uint32_t)data;

	/* WR = 0 */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET );
	/* WR = 1 */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET );
}

/**
 * Write data onto the data bus to the lcd, this has RS line high
 *
 * @data The 16 bit data value to write
 */
static void write_data(uint16_t data)
{
    /* RS = 1 */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET );

    /* write data */
    GPIOE->ODR = (uint32_t)data;

	/* WR = 0 */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET );
	/* WR = 1 */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET );
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_lcd_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_All;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_1  | GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_7 | GPIO_PIN_11;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* reset the display */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
    mw_hal_delay_ms(5U);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
    mw_hal_delay_ms(30U);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
    mw_hal_delay_ms(20U);

	/* RD = 1 */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);

	/* WR = 1 */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);

	/* CS = 1 */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

    write_command(0x00U, 0x0001U);		/* oscillator on/off */
    write_command(0x03U, 0xA8A4U);		/* power control 1 */
    write_command(0x0CU, 0x0000U);		/* power control 2 */
    write_command(0x0DU, 0x080CU);		/* power control 3 */
    write_command(0x0EU, 0x2B00U);		/* power control 4 */
    write_command(0x1EU, 0x00B0U);		/* power control 5 */
    write_command(0x01U, 0x2B3FU);		/* driver output control */
    write_command(0x02U, 0x0600U);		/* LCD drive AC control */
    write_command(0x10U, 0x0000U);		/* sleep mode */
    write_command(0x11U, 0x6070U);		/* entry mode */
    write_command(0x05U, 0x0000U);		/* compare register 1 */
    write_command(0x06U, 0x0000U);		/* compare register 2 */
    write_command(0x16U, 0xEF1CU);		/* horizontal porch */
    write_command(0x17U, 0x0003U);		/* vertical porch */
    write_command(0x07U, 0x0233U);		/* display control */
    write_command(0x0BU, 0x0000U);		/* frame cycle control */
    write_command(0x0FU, 0x0000U);		/* gate scan start pos */
    write_command(0x41U, 0x0000U);		/* vertical scroll control 1 */
    write_command(0x42U, 0x0000U);		/* vertical scroll control 2 */
    write_command(0x48U, 0x0000U);		/* first window start */
    write_command(0x49U, 0x013FU);		/* first window end */
    write_command(0x4AU, 0x0000U);		/* second window start */
    write_command(0x4BU, 0x0000U);		/* second window end */
    write_command(0x44U, 0xEF00U);		/* horizontal ram address pos */
    write_command(0x45U, 0x0000U);		/* vertical ram address start pos */
    write_command(0x46U, 0x013FU);		/* vertical ram address end pos */
    write_command(0x30U, 0x0707U);		/* gamma control */
    write_command(0x31U, 0x0204U);
    write_command(0x32U, 0x0204U);
    write_command(0x33U, 0x0502U);
    write_command(0x34U, 0x0507U);
    write_command(0x35U, 0x0204U);
    write_command(0x36U, 0x0204U);
    write_command(0x37U, 0x0502U);
    write_command(0x3AU, 0x0302U);
    write_command(0x3BU, 0x0302U);
    write_command(0x23U, 0x0000U);		/* ram write data mask 1 */
    write_command(0x24U, 0x0000U);		/* ram write data mask 2 */
    write_command(0x4fU, 0x0000U);		/* ram x address counter */
    write_command(0x4eU, 0x0000U);		/* ram y address counter */
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
	uint32_t temp_uint32;

#if defined(MW_DISPLAY_ROTATION_0)
	write_command(0x4eU, (uint16_t)x);
	write_command(0x4fU, (uint16_t)y);
#elif defined(MW_DISPLAY_ROTATION_90)
	write_command(0x4eU, (uint16_t)y);
	write_command(0x4fU, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - 1U - (uint16_t)x);
#elif defined (MW_DISPLAY_ROTATION_180)
	write_command(0x4eU, (uint16_t)LCD_DISPLAY_WIDTH_PIXELS - (uint16_t)x - 1U);
	write_command(0x4fU, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - 1U - (uint16_t)y);
#elif defined (MW_DISPLAY_ROTATION_270)
	write_command(0x4eU, (uint16_t)LCD_DISPLAY_WIDTH_PIXELS - 1U - (uint16_t)y);
	write_command(0x4fU, (uint16_t)x);
#endif

	temp_uint32 = (((uint32_t)colour & 0xf80000U) >> 8) |
			(((uint32_t)colour & 0xfc00U) >> 5) |
			(((uint32_t)colour & 0xf8U) >> 3);
	write_command(0x22U, (uint16_t)temp_uint32);
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
	int16_t end_x;
	int16_t end_y;
	int16_t x;
	int16_t y;

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
		int16_t clip_width,
		int16_t clip_height,
		const uint8_t *data)
{
	int16_t x;
	int16_t y;
	mw_hal_lcd_colour_t pixel_colour;

	for (y = 0; y < (int16_t)image_data_height_pixels; y++)
	{
		for (x = 0; x < (int16_t)image_data_width_pixels; x++)
		{
			if (x + image_start_x >= clip_start_x &&
					x + image_start_x < clip_start_x + clip_width &&
					y + image_start_y >= clip_start_y &&
					y + image_start_y < clip_start_y + clip_height)
			{
				pixel_colour = *(2 + data + (x + y * (int16_t)image_data_width_pixels) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(1 + data + (x + y * (int16_t)image_data_width_pixels) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(data + (x + y * (int16_t)image_data_width_pixels) * 3);
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
	int16_t a;
	uint8_t image_byte;
	uint8_t mask;
	int16_t array_width_bytes;

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
			mask = 0x80;
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
					if ((image_byte & mask) == 0U)
					{
						mw_hal_lcd_pixel((a * 8) + x + image_start_x, y + image_start_y, fg_colour);
					}
					else
					{
						mw_hal_lcd_pixel((a * 8) + x + image_start_x, y + image_start_y, bg_colour);
					}
				}
				mask >>= 1;
			}
		}
	}
}

#endif
