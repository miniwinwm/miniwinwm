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

#ifdef STM32F429xx

/***************
*** INCLUDES ***
***************/

#include "hal/hal_lcd.h"
#include "miniwin_config.h"
#include "stm32f429i_discovery_lcd.h"

/****************
*** CONSTANTS ***
****************/

#define LCD_DISPLAY_WIDTH_PIXELS	240							/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	320							/**< This is the height of the display in pixels irrespective of user specified display rotation */
#define LCD_FRAME_BUFFER_LAYER0     (LCD_FRAME_BUFFER + 0x130000U)
#define LCD_FRAME_BUFFER_LAYER1     LCD_FRAME_BUFFER

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

void mw_hal_lcd_init(void)
{
    BSP_LCD_Init();

    /* layer2 Init */
    BSP_LCD_LayerDefaultInit(1U, LCD_FRAME_BUFFER_LAYER1);
    BSP_LCD_SelectLayer(1U);
    BSP_LCD_SetLayerVisible(1U, DISABLE);

    /* layer1 Init */
    BSP_LCD_LayerDefaultInit(0U, LCD_FRAME_BUFFER_LAYER0);
    BSP_LCD_SelectLayer(0U);
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetLayerVisible(0U, ENABLE);

    BSP_LCD_DisplayOn();
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
	BSP_LCD_DrawPixel(x, y, colour);
#elif defined(MW_DISPLAY_ROTATION_90)
	BSP_LCD_DrawPixel(y, LCD_DISPLAY_HEIGHT_PIXELS - 1 - x, colour);
#elif defined (MW_DISPLAY_ROTATION_180)
	BSP_LCD_DrawPixel(LCD_DISPLAY_WIDTH_PIXELS - x - 1, LCD_DISPLAY_HEIGHT_PIXELS - 1 - y, colour);
#elif defined (MW_DISPLAY_ROTATION_270)
	BSP_LCD_DrawPixel(LCD_DISPLAY_WIDTH_PIXELS - 1 - y, x, colour);
#endif
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
#if defined(MW_DISPLAY_ROTATION_0)
	BSP_LCD_FillRect((uint16_t)start_x, (uint16_t)start_y, (uint16_t)width, (uint16_t)height, (uint32_t)colour);
#elif defined(MW_DISPLAY_ROTATION_90)
	BSP_LCD_FillRect((uint16_t)start_y, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - (uint16_t)start_x - (uint16_t)width, (uint16_t)height, (uint16_t)width, (uint32_t)colour);
#elif defined (MW_DISPLAY_ROTATION_180)
	BSP_LCD_FillRect((uint16_t)LCD_DISPLAY_WIDTH_PIXELS - (uint16_t)start_x - (uint16_t)width, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - (uint16_t)start_y - (uint16_t)height, (uint16_t)width, (uint16_t)height, (uint32_t)colour);
#elif defined (MW_DISPLAY_ROTATION_270)
	BSP_LCD_FillRect((uint16_t)LCD_DISPLAY_WIDTH_PIXELS - (uint16_t)start_y - (uint16_t)height, (uint16_t)start_x, (uint16_t)height, (uint16_t)width, (uint32_t)colour);
#endif
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

#if defined(MW_DISPLAY_ROTATION_0)
	/* check if pixels in data buffer are all to be drawn and if so use bitmap draw routine */
	if (image_start_x >= clip_start_x &&
			image_start_y >= clip_start_y &&
			image_start_x + (int16_t)image_data_width_pixels <= clip_start_x + clip_width &&
			image_start_y + (int16_t)image_data_height_pixels <= clip_start_y + clip_height)
	{
		BSP_LCD_DrawBitmap24((uint16_t)image_start_x,
				(uint16_t)image_start_y,
				(uint16_t)image_data_width_pixels,
				(uint16_t)image_data_height_pixels,
				data);
		return;
	}
#endif

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
