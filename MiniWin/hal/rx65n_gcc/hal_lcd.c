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

#ifdef RX65N_GCC

/***************
*** INCLUDES ***
***************/

#include <iodefine.h>
#include "hal/hal_lcd.h"
#include "miniwin_config.h"

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
	/* allow writing to PFSWE bit */
    MPC.PWPR.BIT.B0WI = 0U;

    /* enable writing to PFS registers. */
    MPC.PWPR.BIT.PFSWE = 1U;

    /* set LCD_CLK pin to peripheral i/o */
    MPC.PB5PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B5 = 1U;

    /* set LCD_TCON0 pin to peripheral i/o */
    MPC.PB4PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B4 = 1U;

    /* set LCD_TCON2 pin to peripheral i/o */
    MPC.PB2PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B2 = 1U;

    /* set LCD_TCON3 pin to peripheral i/o */
    MPC.PB1PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B1 = 1U;

    /* set LCD_DATA0 pin to peripheral i/o */
    MPC.PB0PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B0 = 1U;

    /* set LCD_DATA1 pin to peripheral i/o */
    MPC.PA7PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B7 = 1U;

    /* set LCD_DATA2 pin to peripheral i/o */
    MPC.PA6PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B6 = 1U;

    /* set LCD_DATA3 pin to peripheral i/o */
    MPC.PA5PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B5 = 1U;

    /* set LCD_DATA4 pin to peripheral i/o */
    MPC.PA4PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B4 = 1U;

    /* set LCD_DATA5 pin to peripheral i/o */
    MPC.PA3PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B3 = 1U;

    /* set LCD_DATA6 pin to peripheral i/o */
    MPC.PA2PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B2 = 1U;

    /* set LCD_DATA7 pin to peripheral i/o */
    MPC.PA1PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B1 = 1U;

    /* set LCD_DATA8 pin to peripheral i/o */
    MPC.PA0PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B0 = 1U;

    /* set LCD_DATA9 pin to peripheral i/o */
    MPC.PE7PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B7 = 1U;

    /* set LCD_DATA10 pin to peripheral i/o */
    MPC.PE6PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B6 = 1U;

    /* set LCD_DATA11 pin to peripheral i/o */
    MPC.PE5PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B5 = 1U;

    /* set LCD_DATA12 pin to peripheral i/o */
    MPC.PE4PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B4 = 1U;

    /* set LCD_DATA13 pin to peripheral i/o */
    MPC.PE3PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B3 = 1U;

    /* set LCD_DATA14 pin to peripheral i/o */
    MPC.PE2PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B2 = 1U;

    /* set LCD_DATA15 pin to peripheral i/o */
    MPC.PE1PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B1 = 1U;

    /* disable writing to PFS registers. */
    MPC.PWPR.BIT.PFSWE = 0U;

    /* disable writing of PFSWE bit. */
    MPC.PWPR.BIT.B0WI = 1U;

    /* set up reset line and bring display out of reset */
	PORT6.PMR.BIT.B3 = 0U;	/* mode to gpio */
	PORT6.PDR.BIT.B3 = 1U; 	/* port direction output */
	PORT6.PODR.BIT.B3 = 1U; /* bring display out of reset */

	/* set backlight pin as gpio output and switch backlight on */
	PORT6.PMR.BIT.B6 = 0U;	/* mode to gpio */
	PORT6.PDR.BIT.B6 = 1U;	/* port direction output */
	PORT6.ODR0.BIT.B6 = 0U;	/* cmos */
	PORT6.PODR.BIT.B6 = 1U;	/* backlight on */

	/* enable writing to clock control bit */
	SYSTEM.PRCR.WORD = 0xa502U;

	/* supply the peripheral clock to the glcd module */
	MSTP(GLCDC) = 0U;

	/* disable writing to clock control bit */
	SYSTEM.PRCR.WORD = 0xa500;

	/* release glcd module from a software reset status */
	GLCDC.BGEN.BIT.SWRST = 1U;

	/* set the dot clock to pll clock */
	GLCDC.PANELCLK.BIT.CLKSEL = 1U;

	/* set clock division ratio */
	GLCDC.PANELCLK.BIT.DCDR = 0x18U;

	/* selects pixel clock output to no division */
	GLCDC.PANELCLK.BIT.PIXSEL = 0U;

	/* enable panel clock LCD_CLK output */
	GLCDC.PANELCLK.BIT.CLKEN = 1U;

	/* waiting for supply of panel clock(LCD_CLK) and pixel clock(PXCLK)
	 * the BGMON.SWRST bit is sampled with PXCLK so if the CLKEN bit is set,
	 * the BGEN.SWRST bit is reflected on the BGMON.SWRST bit. */
	while (0U == GLCDC.BGMON.BIT.SWRST)
	{
		__asm("NOP");
	}

	/* set the panel signal timing */

	/* the outputs of LCD_DATA are synchronized with rising edges of LCD_CLK */
	GLCDC.CLKPHASE.BIT.LCDEDG = 0U;

	/* the output of LCD_TCON0 is synchronized with rising edges of LCD_CLK */
	GLCDC.CLKPHASE.BIT.TCON0EDG = 0U;

	/* the output of LCD_TCON2 is synchronized with rising edges of LCD_CLK */
	GLCDC.CLKPHASE.BIT.TCON2EDG = 0U;

	/* the output of LCD_TCON3 is synchronized with rising edges of LCD_CLK */
	GLCDC.CLKPHASE.BIT.TCON3EDG = 0U;

	/* horiz synch timing offset is 1 pixel */
	GLCDC.TCONTIM.BIT.OFFSET = 0U;

	/* vert synch timing offset is 1 pixel */
	GLCDC.TCONTIM.BIT.HALF = 0U;

	/* output signal select STHA */
	GLCDC.TCONSTHA2.BIT.SEL = 2U;

	/* invert the STHy signal */
	GLCDC.TCONSTHA2.BIT.INV = 1U;

	/* set Hsync beginning position to no delay */
	GLCDC.TCONSTHA1.BIT.HS = 0U;

	/* select input Hsync as reference */
	GLCDC.TCONSTHA2.BIT.HSSEL = 0U;

	/* STHy signal pulse width 1 pixel */
	GLCDC.TCONSTHA1.BIT.HW = 1U;

	/* vsync to STVA */
	GLCDC.TCONSTVA2.BIT.SEL = 0U;

	/* invert vsync */
	GLCDC.TCONSTVA2.BIT.INV = 1U;

	/* no vsync delay */
	GLCDC.TCONSTVA1.BIT.VS = 0U;

	/* pulse width 1 */
	GLCDC.TCONSTVA1.BIT.VW = 1U;

	/* output signal data enable */
	GLCDC.TCONSTHB2.BIT.SEL = 7U;

	/* don't invert data enable */
	GLCDC.TCONDE.BIT.INV = 0U;

	/* hsync delay */
	GLCDC.TCONSTHB1.BIT.HS = 0x29U;

	/* horiz width 480 */
	GLCDC.TCONSTHB1.BIT.HW = LCD_DISPLAY_WIDTH_PIXELS;

	/* hsync is reference */
	GLCDC.TCONSTHB2.BIT.HSSEL = 0U;

	/* vsync 9 lines delay */
	GLCDC.TCONSTVB1.BIT.VS = 9U;

	/* vert height 272 */
	GLCDC.TCONSTVB1.BIT.VW = LCD_DISPLAY_HEIGHT_PIXELS;

	/* configure the background screen */
	GLCDC.BGPERI.BIT.FH = 0x20dU;

	/* vsync period */
	GLCDC.BGPERI.BIT.FV = 0x120U;

	/* hsync assert position */
	GLCDC.BGSYNC.BIT.HP = 3U;

	/* vsync assert position */
	GLCDC.BGSYNC.BIT.VP = 7U;

	/* horiz active start pixel */
	GLCDC.BGHSIZE.BIT.HP = 0x2cU;

	/* vert active start position */
	GLCDC.BGVSIZE.BIT.VP = 0x10U;

	/* horiz active pixel width */
	GLCDC.BGHSIZE.BIT.HW = LCD_DISPLAY_WIDTH_PIXELS;

	/* vert active pixel height */
	GLCDC.BGVSIZE.BIT.VW = LCD_DISPLAY_HEIGHT_PIXELS;

	/* set background colour to black */
	GLCDC.BGCOLOR.BIT.R = 0U;
	GLCDC.BGCOLOR.BIT.G = 0U;
	GLCDC.BGCOLOR.BIT.B = 0U;

	/* frame buffer 565 format */
	GLCDC.GR2FLM6.BIT.FORMAT = 0U;

	/* set start address of gr2 buffer */
	GLCDC.GR2FLM2 = 0x800000U;

	/* set gr2 background colour */
	GLCDC.GR2BASE.BIT.R = 0U;
	GLCDC.GR2BASE.BIT.G = 0U;
	GLCDC.GR2BASE.BIT.B = 0U;
    
    /* set number of 64 byte transfers, gr2 */
	GLCDC.GR2FLM5.BIT.DATANUM = 0xeU;

	/* set number of lines in display */
	GLCDC.GR2FLM5.BIT.LNNUM = 0x10fU;

	/* line offset bytes */
	GLCDC.GR2FLM3.BIT.LNOFF = LCD_DISPLAY_WIDTH_PIXELS * 2U;

	/* width of graphical area */
	GLCDC.GR2AB2.BIT.GRCVW = LCD_DISPLAY_HEIGHT_PIXELS;

	/* graphical area vertical start position */
	GLCDC.GR2AB2.BIT.GRCVS = 9U;

	/* height of graphical area */
	GLCDC.GR2AB3.BIT.GRCHW = LCD_DISPLAY_WIDTH_PIXELS;

	/* graphical area horizontal start position */
	GLCDC.GR2AB3.BIT.GRCHS = 0x29U;

	/* frame not displayed */
	GLCDC.GR2AB1.BIT.GRCDISPON = 0U;

	/* show current graphics */
	GLCDC.GR2AB1.BIT.DISPSEL = 2U;

	/* disable chroma control */
	GLCDC.GR2AB7.BIT.CKON = 0U;

	/* configure the output control block */
	GLCDC.OUTSET.BIT.ENDIANON = 0U;

	/* byte order RGB */
	GLCDC.OUTSET.BIT.SWAPON = 0U;

	/* pixel format 565 */
	GLCDC.OUTSET.BIT.FORMAT = 2U;
	GLCDC.PANELDTHA.BIT.FORM = 2U;

	/* no pixel clock division */
	GLCDC.OUTSET.BIT.FRQSEL = 0U;

	/* rounding mode is truncate */
	GLCDC.PANELDTHA.BIT.SEL = 0U;

	/* brightness setting correction all midpoint */
	GLCDC.BRIGHT1.BIT.BRTG = 512U;
	GLCDC.BRIGHT2.BIT.BRTB = 512U;
	GLCDC.BRIGHT2.BIT.BRTR = 512U;

	/* contrast setting correction all midpoint */
	GLCDC.CONTRAST.BIT.CONTG = 128U;
	GLCDC.CONTRAST.BIT.CONTB = 128U;
	GLCDC.CONTRAST.BIT.CONTR = 128U;

	/* disable gamma correction */
	GLCDC.GAMSW.BIT.GAMON = 0U;

	/* set the GLCD detections and interrupts */

	/* disable VPOS line notification */
	GLCDC.DTCTEN.BIT.VPOSDTC = 0U;

	/* disable gr1 underflow notification */
	GLCDC.DTCTEN.BIT.GR1UFDTC = 0U;

	/* disable gr2 underflow notification */
	GLCDC.DTCTEN.BIT.GR2UFDTC = 0U;

	/* disable gr1 underflow interrupt */
	GLCDC.INTEN.BIT.GR1UFINTEN = 0U;
	EN(GLCDC, GR1UF) = 0U;
	while (0U != IS(GLCDC, GR1UF))
	{
		__asm("NOP");
	}

	/* disable gr2 underflow interrupt */
	GLCDC.INTEN.BIT.GR2UFINTEN = 0U;
	EN(GLCDC, GR2UF) = 0U;
	while (0U != IS(GLCDC,GR2UF))
	{
		__asm("NOP");
	}

	IEN(ICU, GROUPAL1) = 0U;
	IPR(ICU, GROUPAL1) = 0U;

	/* allow reading of the frame buffer */
	GLCDC.GR2FLMRD.BIT.RENB = 1U;

	/* enable background generating block */
	GLCDC.BGEN.BIT.EN = 1U;

	/* enable register reflection */
	GLCDC.BGEN.BIT.VEN = 1U;

	/* release from software reset */
	GLCDC.BGEN.BIT.SWRST = 1U;
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
	uint16_t* address = (uint16_t*)0x00800000u;
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
	uint32_t converted_colour = ((colour & 0xf80000U) >> 8) |
			((colour & 0xfc00U) >> 5) |
			((colour & 0xf8U) >> 3);

	end_x = start_x + width - 1;
	end_y = start_y + height - 1;

	for (x = start_x; x <= end_x; x++)
	{
		for (y = start_y; y <= end_y; y++)
		{
			address = (uint16_t*)0x00800000u;
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
