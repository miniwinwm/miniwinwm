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

#ifdef CPU_LPC54628J512ET180

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>
#include <cr_section_macros.h>
#include "fsl_lcdc.h"
#include "fsl_sctimer.h"
#include "hal/hal_lcd.h"
#include "miniwin_config.h"

/****************
*** CONSTANTS ***
****************/
#define LCD_DISPLAY_WIDTH_PIXELS	480							/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	272							/**< This is the height of the display in pixels irrespective of user specified display rotation */
#define LCD_PANEL_CLK 	9000000
#define LCD_PPL 		480
#define LCD_HSW 		2
#define LCD_HFP 		8
#define LCD_HBP 		43
#define LCD_LPP 		272
#define LCD_VSW 		10
#define LCD_VFP 		4
#define LCD_VBP 		12
#define LCD_POL_FLAGS 	(kLCDC_InvertVsyncPolarity | kLCDC_InvertHsyncPolarity)

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

__attribute__((aligned(8)))
__NOINIT(RAM4) static uint32_t s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS][LCD_DISPLAY_WIDTH_PIXELS];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void BOARD_InitPWM(void)
{
    sctimer_config_t config;
    sctimer_pwm_signal_param_t pwmParam;
    uint32_t event;

    CLOCK_AttachClk(kMAIN_CLK_to_SCT_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivSctClk, 2, true);
    SCTIMER_GetDefaultConfig(&config);
    SCTIMER_Init(SCT0, &config);

    pwmParam.output = kSCTIMER_Out_5;
    pwmParam.level = kSCTIMER_LowTrue;
    pwmParam.dutyCyclePercent = 5;

    SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_CenterAlignedPwm, 1000U, CLOCK_GetFreq(kCLOCK_Sct), &event);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_lcd_init(void)
{
    lcdc_config_t lcdConfig;

    /* clear the screen buffers */
    memset(s_frameBuf0, 0, LCD_DISPLAY_WIDTH_PIXELS * LCD_DISPLAY_HEIGHT_PIXELS * sizeof(uint32_t));

    /* route Main clock to lcd */
    CLOCK_AttachClk(kMAIN_CLK_to_LCD_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivLcdClk, 1, true);

    /* set the back light pwm */
    BOARD_InitPWM();

    /* populate lcd module config then initialize the lcd */
    LCDC_GetDefaultConfig(&lcdConfig);
    lcdConfig.panelClock_Hz = LCD_PANEL_CLK;
    lcdConfig.ppl = LCD_PPL;
    lcdConfig.hsw = LCD_HSW;
    lcdConfig.hfp = LCD_HFP;
    lcdConfig.hbp = LCD_HBP;
    lcdConfig.lpp = LCD_LPP;
    lcdConfig.vsw = LCD_VSW;
    lcdConfig.vfp = LCD_VFP;
    lcdConfig.vbp = LCD_VBP;
    lcdConfig.polarityFlags = LCD_POL_FLAGS;
    lcdConfig.upperPanelAddr = (uint32_t)s_frameBuf0;
    lcdConfig.bpp = kLCDC_24BPP;
    lcdConfig.display = kLCDC_DisplayTFT;
    lcdConfig.swapRedBlue = true;
    LCDC_Init(LCD, &lcdConfig, CLOCK_GetFreq(kCLOCK_LCD));

    /* power up and start lcd driver module */
    LCDC_Start(LCD);
    LCDC_PowerUp(LCD);
}

uint16_t mw_hal_lcd_get_display_width(void)
{
	return LCD_DISPLAY_WIDTH_PIXELS;
}

uint16_t mw_hal_lcd_get_display_height(void)
{
	return LCD_DISPLAY_HEIGHT_PIXELS;
}

void mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
#if defined(MW_DISPLAY_ROTATION_0)
	s_frameBuf0[y][x] = colour;
#elif defined(MW_DISPLAY_ROTATION_90)
	s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - x][y] = colour;
#elif defined (MW_DISPLAY_ROTATION_180)
	s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - y][LCD_DISPLAY_WIDTH_PIXELS - x - 1] = colour;
#elif defined (MW_DISPLAY_ROTATION_270)
	s_frameBuf0[x][LCD_DISPLAY_WIDTH_PIXELS - 1 - y] = colour;
#endif
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		uint16_t width,
		uint16_t height,
		mw_hal_lcd_colour_t colour)
{
	uint16_t x;
	uint16_t y;

	for (x = start_x; x < start_x + width; x++)
	{
		for (y = start_y; y < start_y + height; y++)
		{
			//s_frameBuf0[y][x] = colour;
#if defined(MW_DISPLAY_ROTATION_0)
			s_frameBuf0[y][x] = colour;
#elif defined(MW_DISPLAY_ROTATION_90)
			s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - x][y] = colour;
#elif defined (MW_DISPLAY_ROTATION_180)
			s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - y][LCD_DISPLAY_WIDTH_PIXELS - x - 1] = colour;
#elif defined (MW_DISPLAY_ROTATION_270)
			s_frameBuf0[x][LCD_DISPLAY_WIDTH_PIXELS - 1 - y] = colour;
#endif
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
		const uint8_t *data)
{
	uint16_t x;
	uint16_t y;
	mw_hal_lcd_colour_t pixel_colour;

	for (y = 0; y < image_data_height_pixels; y++)
	{
		for (x = 0; x < image_data_width_pixels; x++)
		{
			if (x + image_start_x >= clip_start_x &&
					x + image_start_x < clip_start_x + clip_width &&
					y + image_start_y >= clip_start_y &&
					y + image_start_y < clip_start_y + clip_height)
			{
				pixel_colour = *(data + (x + y * image_data_width_pixels) * 3);
				pixel_colour |= *(1 + data + (x + y * image_data_width_pixels) * 3) << 8;
				pixel_colour |= *(2 + data + (x + y * image_data_width_pixels) * 3) << 16;
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

#endif
