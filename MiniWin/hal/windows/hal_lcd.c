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

#ifdef _WIN32

/***************
*** INCLUDES ***
***************/

#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include "hal/hal_lcd.h"
#include "app.h"

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

static HDC hdc;

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
	Sleep(600U);
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
	hdc = GetDC(hwnd);
	uint8_t r = (colour & 0xff0000U) >> 16;
	uint8_t g = (colour & 0xff00U) >> 8;
	uint8_t b = colour & 0xffU;

	(void)SetPixel(hdc, x, y, RGB(r, g, b));

	(void)ReleaseDC(hwnd, hdc);
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
	HBRUSH brush;
	RECT rect;
	uint8_t r = (colour & 0xff0000U) >> 16U;
	uint8_t g = (colour & 0xff00U) >> 8U;
	uint8_t b = colour & 0xffU;

	hdc = GetDC(hwnd);

	brush = CreateSolidBrush(RGB(r, g, b));
	rect.left = start_x;
	rect.top = start_y;
	rect.right = start_x + width;
	rect.bottom = start_y + height;
	(void)FillRect(hdc, &rect, brush);

	(void)DeleteObject(brush);
	(void)ReleaseDC(hwnd, hdc);
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

	hdc = GetDC(hwnd);

	for (y = 0; y < bitmap_height; y++)
	{
		for (x = 0; x < bitmap_width; x++)
		{
			if (x + image_start_x >= clip_start_x &&
					x + image_start_x < clip_start_x + clip_width &&
					y + image_start_y >= clip_start_y &&
					y + image_start_y < clip_start_y + clip_height)
			{
				(void)SetPixel(hdc,
						x + image_start_x,
						y + image_start_y,
						RGB(*(2 + image_data + (x + y * bitmap_width) * 3),
								*(1 + image_data + (x + y * bitmap_width) * 3),
								*(image_data + (x + y * bitmap_width) * 3)));
			}
		}

	}

	(void)ReleaseDC(hwnd, hdc);
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

	array_width_bytes = bitmap_width >> 3;
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
				mask >>= 1;
			}
		}
	}
}

#endif
