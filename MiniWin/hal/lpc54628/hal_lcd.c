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
#define LCD_DISPLAY_WIDTH_PIXELS	480U						/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	272U						/**< This is the height of the display in pixels irrespective of user specified display rotation */
#define LCD_PANEL_CLK 				9000000U
#define LCD_PPL 					480U
#define LCD_HSW 					2U
#define LCD_HFP 					8U
#define LCD_HBP 					43U
#define LCD_LPP 					272U
#define LCD_VSW 					10U
#define LCD_VFP 					4U
#define LCD_VBP 					12U
#define LCD_POL_FLAGS 				(kLCDC_InvertVsyncPolarity | kLCDC_InvertHsyncPolarity)

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
    CLOCK_SetClkDiv(kCLOCK_DivSctClk, 2U, true);
    SCTIMER_GetDefaultConfig(&config);
    (void)SCTIMER_Init(SCT0, &config);

    pwmParam.output = kSCTIMER_Out_5;
    pwmParam.level = kSCTIMER_LowTrue;
    pwmParam.dutyCyclePercent = 5U;

    (void)SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_CenterAlignedPwm, 1000U, CLOCK_GetFreq(kCLOCK_Sct), &event);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_lcd_init(void)
{
    lcdc_config_t lcdConfig;

    /* clear the screen buffers */
    (void)memset((s_frameBuf0), 0, ((size_t)LCD_DISPLAY_WIDTH_PIXELS * (size_t)LCD_DISPLAY_HEIGHT_PIXELS * sizeof(uint32_t)));

    /* route Main clock to lcd */
    CLOCK_AttachClk(kMAIN_CLK_to_LCD_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivLcdClk, 1U, true);

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
    (void)LCDC_Init(LCD, &lcdConfig, CLOCK_GetFreq(kCLOCK_LCD));

    /* power up and start lcd driver module */
    LCDC_Start(LCD);
    LCDC_PowerUp(LCD);
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
	s_frameBuf0[y][x] = (uint32_t)colour;
#elif defined(MW_DISPLAY_ROTATION_90)
	s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - x][y] = (uint32_t)colour;
#elif defined (MW_DISPLAY_ROTATION_180)
	s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - y][LCD_DISPLAY_WIDTH_PIXELS - x - 1] = (uint32_t)colour;
#elif defined (MW_DISPLAY_ROTATION_270)
	s_frameBuf0[x][LCD_DISPLAY_WIDTH_PIXELS - 1 - y] = (uint32_t)colour;
#endif
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
	int16_t x;
	int16_t y;

	for (x = start_x; x < start_x + width; x++)
	{
		for (y = start_y; y < start_y + height; y++)
		{
#if defined(MW_DISPLAY_ROTATION_0)
			s_frameBuf0[y][x] = (uint32_t)colour;
#elif defined(MW_DISPLAY_ROTATION_90)
			s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - x][y] = (uint32_t)colour;
#elif defined (MW_DISPLAY_ROTATION_180)
			s_frameBuf0[LCD_DISPLAY_HEIGHT_PIXELS - 1 - y][LCD_DISPLAY_WIDTH_PIXELS - x - 1] = (uint32_t)colour;
#elif defined (MW_DISPLAY_ROTATION_270)
			s_frameBuf0[x][LCD_DISPLAY_WIDTH_PIXELS - 1 - y] = (uint32_t)colour;
#endif
		}
	}
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
