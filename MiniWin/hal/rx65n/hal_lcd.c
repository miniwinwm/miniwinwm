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

#ifdef RX65N

/***************
*** INCLUDES ***
***************/

#include <stdlib.h>
#include "hal/hal_lcd.h"
#include "miniwin_config.h"
#include "r_smc_entry.h"
#include "r_glcdc_rx_if.h"
#include "r_pinset.h"
#include "r_gpio_rx_if.h"

/****************
*** CONSTANTS ***
****************/

#define LCD_DISPLAY_WIDTH_PIXELS	480							/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	272							/**< This is the height of the display in pixels irrespective of user specified display rotation */

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
	glcdc_cfg_t glcdc_cfg;

	/* set up LCD pins */
	R_GLCDC_PinSet();

	/* display reset line */
	(void)R_GPIO_PinControl(GPIO_PORT_6_PIN_3, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_6_PIN_3, GPIO_DIRECTION_OUTPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_6_PIN_3, GPIO_CMD_OUT_CMOS);
	R_GPIO_PinWrite(GPIO_PORT_6_PIN_3, GPIO_LEVEL_HIGH);

	/* backlight control */
	(void)R_GPIO_PinControl(GPIO_PORT_6_PIN_6, GPIO_CMD_ASSIGN_TO_GPIO);
	R_GPIO_PinDirectionSet(GPIO_PORT_6_PIN_6, GPIO_DIRECTION_OUTPUT);
	(void)R_GPIO_PinControl(GPIO_PORT_6_PIN_6, GPIO_CMD_OUT_CMOS);
	R_GPIO_PinWrite(GPIO_PORT_6_PIN_6, GPIO_LEVEL_HIGH);

	glcdc_cfg.output.htiming.back_porch = 40U;
	glcdc_cfg.output.htiming.sync_width = 1U;
	glcdc_cfg.output.vtiming.back_porch = 8U;
	glcdc_cfg.output.vtiming.sync_width = 1U;
	glcdc_cfg.output.htiming.display_cyc = 480U;
	glcdc_cfg.output.vtiming.display_cyc = 272U;
	glcdc_cfg.output.htiming.front_porch = 5U;
	glcdc_cfg.output.vtiming.front_porch = 8U;
	glcdc_cfg.p_callback = NULL;
	glcdc_cfg.output.clksrc = GLCDC_CLK_SRC_INTERNAL;
	glcdc_cfg.output.clock_div_ratio = GLCDC_PANEL_CLK_DIVISOR_24;
	glcdc_cfg.output.format = GLCDC_OUT_FORMAT_16BITS_RGB565;
	glcdc_cfg.output.sync_edge = GLCDC_SIGNAL_SYNC_EDGE_RISING;
	glcdc_cfg.output.tcon_hsync = GLCDC_TCON_PIN_2;
	glcdc_cfg.output.hsync_polarity = GLCDC_SIGNAL_POLARITY_LOACTIVE;
	glcdc_cfg.output.tcon_vsync = GLCDC_TCON_PIN_0;
	glcdc_cfg.output.vsync_polarity = GLCDC_SIGNAL_POLARITY_LOACTIVE;
	glcdc_cfg.output.tcon_de = GLCDC_TCON_PIN_3;
	glcdc_cfg.output.data_enable_polarity = GLCDC_SIGNAL_POLARITY_HIACTIVE;
	glcdc_cfg.output.bg_color.byte.r = 0U;
	glcdc_cfg.output.bg_color.byte.g = 0U;
	glcdc_cfg.output.bg_color.byte.b = 0U;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].format = GLCDC_IN_FORMAT_16BITS_RGB565;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_1].p_base = NULL;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].p_base = (uint32_t *)0x00800000U;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].bg_color.byte.r = 0U;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].bg_color.byte.g = 0U;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].bg_color.byte.b = 0U;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].hsize = 480U;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].vsize = 272U;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].offset = 960;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].frame_edge = false;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].coordinate.x = 0;
	glcdc_cfg.input[GLCDC_FRAME_LAYER_2].coordinate.y = 0;
	glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].blend_control = GLCDC_BLEND_CONTROL_NONE;
	glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].visible = true;
	glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].frame_edge = false;
	glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].start_coordinate.x = 0;
	glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].end_coordinate.x= 480;
	glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].start_coordinate.y = 0;
	glcdc_cfg.blend[GLCDC_FRAME_LAYER_2].end_coordinate.y= 272;
	glcdc_cfg.chromakey[GLCDC_FRAME_LAYER_2].enable = false;
	glcdc_cfg.output.endian = GLCDC_ENDIAN_LITTLE;
	glcdc_cfg.output.color_order = GLCDC_COLOR_ORDER_RGB;
	glcdc_cfg.output.dithering.dithering_on = false;
	glcdc_cfg.output.brightness.enable = true;
	glcdc_cfg.output.brightness.r = 0x200U;
	glcdc_cfg.output.brightness.g = 0x200U;
	glcdc_cfg.output.brightness.b = 0x200U;
	glcdc_cfg.output.contrast.enable = true;
	glcdc_cfg.output.contrast.b = 0x80U;
	glcdc_cfg.output.contrast.g = 0x80U;
	glcdc_cfg.output.contrast.r = 0x80U;
	glcdc_cfg.output.gamma.enable = false;
	glcdc_cfg.clut[GLCDC_FRAME_LAYER_2].enable = false;
	glcdc_cfg.detection.vpos_detect = false;
	glcdc_cfg.interrupt.vpos_enable = false;
	glcdc_cfg.detection.gr1uf_detect = false;
	glcdc_cfg.detection.gr2uf_detect = false;
	glcdc_cfg.interrupt.gr1uf_enable = false;
	glcdc_cfg.interrupt.gr2uf_enable = false;

	(void)R_GLCDC_Open(&glcdc_cfg);
	(void)R_GLCDC_Control(GLCDC_CMD_START_DISPLAY, NULL);
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
	uint16_t* address = (uint16_t*)0x00800000U;
	uint32_t converted_colour = ((colour & 0xf80000U) >> 8) |
			((colour & 0xfc00U) >> 5) |
			((colour & 0xf8U) >> 3);

#if defined(MW_DISPLAY_ROTATION_0)
	address += x;
	address += y * LCD_DISPLAY_WIDTH_PIXELS;
#elif defined(MW_DISPLAY_ROTATION_90)
	address += x * LCD_DISPLAY_WIDTH_PIXELS;
	address += LCD_DISPLAY_WIDTH_PIXELS - 1 - y;
#elif defined (MW_DISPLAY_ROTATION_180)
	address += LCD_DISPLAY_WIDTH_PIXELS - 1 - x;
	address += (LCD_DISPLAY_HEIGHT_PIXELS - 1 - y) * LCD_DISPLAY_WIDTH_PIXELS;
#elif defined (MW_DISPLAY_ROTATION_270)
	address += (LCD_DISPLAY_HEIGHT_PIXELS - 1 - x) * LCD_DISPLAY_WIDTH_PIXELS;
	address += y;
#endif
	*address = (uint16_t)converted_colour;
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
	uint16_t* address;
	uint32_t converted_colour = ((colour & 0xf80000U) >> 8U) |
			((colour & 0xfc00U) >> 5U) |
			((colour & 0xf8U) >> 3U);

	end_x = start_x + width - 1;
	end_y = start_y + height - 1;

	for (x = start_x; x <= end_x; x++)
	{
		for (y = start_y; y <= end_y; y++)
		{
			address = (uint16_t*)0x00800000U;
#if defined(MW_DISPLAY_ROTATION_0)
			address += x;
			address += y * 480;
#elif defined(MW_DISPLAY_ROTATION_90)
			address += x * LCD_DISPLAY_WIDTH_PIXELS;
			address += LCD_DISPLAY_WIDTH_PIXELS - 1 - y;
#elif defined (MW_DISPLAY_ROTATION_180)
			address += LCD_DISPLAY_WIDTH_PIXELS - 1 - x;
			address += (LCD_DISPLAY_HEIGHT_PIXELS - 1 - y) * LCD_DISPLAY_WIDTH_PIXELS;
#elif defined (MW_DISPLAY_ROTATION_270)
			address += (LCD_DISPLAY_HEIGHT_PIXELS - 1 - x) * LCD_DISPLAY_WIDTH_PIXELS;
			address += y;
#endif
			*address = (uint16_t)converted_colour;
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
