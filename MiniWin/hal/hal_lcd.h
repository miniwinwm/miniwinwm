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

#ifndef HAL_LCD_H
#define HAL_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>

/****************
*** CONSTANTS ***
****************/

/**
 * Pre-defined named colours, colour bit layout is rrrr rggg gggb bbbb
 */
#define MW_HAL_LCD_BLACK 			0x000000
#define MW_HAL_LCD_YELLOW 			0xffff00
#define MW_HAL_LCD_RED 				0xff0000
#define MW_HAL_LCD_GREEN 			0x00ff00
#define MW_HAL_LCD_BLUE 			0x0000ff
#define MW_HAL_LCD_WHITE 			0xffffff
#define MW_HAL_LCD_PINK 			0xff3399
#define MW_HAL_LCD_PURPLE 			0x990099
#define	MW_HAL_LCD_GREY15			0x404040
#define	MW_HAL_LCD_GREY14			0x4d4d4d
#define	MW_HAL_LCD_GREY13			0x595959
#define	MW_HAL_LCD_GREY12			0x666666
#define	MW_HAL_LCD_GREY11			0x737373
#define	MW_HAL_LCD_GREY10			0x808080
#define	MW_HAL_LCD_GREY9			0x8c8c8c
#define	MW_HAL_LCD_GREY8			0x999999
#define	MW_HAL_LCD_GREY7			0xa6a6a6
#define	MW_HAL_LCD_GREY6			0xb3b3b3
#define	MW_HAL_LCD_GREY5			0xbfbfbf
#define	MW_HAL_LCD_GREY4			0xcccccc
#define	MW_HAL_LCD_GREY3			0xd9d9d9
#define	MW_HAL_LCD_GREY2			0xe6e6e6
#define	MW_HAL_LCD_GREY1			0xf2f2f2
#define MW_HAL_LCD_ORANGE 			0xff6600
#define MW_HAL_LCD_LIGHT_BLUE		0x66ccff
#define MW_HAL_LCD_CYAN				0x00ffff
#define MW_HAL_LCD_DARK_CYAN		0x00b3b3
#define MW_HAL_LCD_LIGHT_ORANGE		0xffcc00
#define MW_HAL_LCD_BRICK_RED		0xcc0000

/************
*** TYPES ***
************/

typedef uint32_t mw_hal_lcd_colour_t;      		/**< Integer type that can hold the display driver's colour depth */

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Initialize all LCD hardware
 */
void mw_hal_lcd_init(void);

/**
 * Get the display width in pixels
 *
 * @return The display width in pixels. This is the physical unrotated pixel width.
 */
int16_t mw_hal_lcd_get_display_width(void);

/**
 * Get the display height in pixels
 *
 * @return The display height in pixels. This is the physical unrotated pixel height.
 */
int16_t mw_hal_lcd_get_display_height(void);

/**
 * Plot a single pixel. Points off screen are not clipped.
 *
 * @param x X position of pixel
 * @param y Y position of pixel
 * @param colour The colour of the pixel to plot
 */
void mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour);

/**
 * Plot a filled rectangle. Position and size values are not clipped to the screen.
 *
 * @param start_x X position of left edge of rectangle
 * @param start_y Y position of top of rectangle
 * @param width Width of rectangle, pixels plotted are from start_x to (start_x + width) - 1
 * @param height Height of rectangle, pixels plotted are from start_y to (start_y + height) - 1
 * @param colour The colour of the pixel to plot
 */
void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour);

/**
 * Plot a bitmap of single colour depth using fg_colour for values 1 in the bitmap and bg_colour for
 * values 0 in the bitmap. The bitmap is clipped to the supplied clip rect.
 * 
 * @param image_start_x The coordinate of the left edge of position to plot image
 * @param image_start_y The coordinate of the top edge of position to plot image
 * @param bitmap_width The width of the image in the bitmap data in pixels
 * @param bitmap_height The height of the image in the bitmap data in pixels
 * @param clip_start_x The coordinate of the left edge of the clip rect
 * @param clip_start_y The coordinate of the top edge of the clip rect
 * @param clip_width The width of the clip rect
 * @param clip_height The height of the clip rect
 * @param fg_colour Colour to plot pixels with value 1 in data
 * @param bg_colour Colour to plot pixels with value 0 in data
 * @param image_data The image data, 8 pixels per byte
 * @note As pixels appear in 8 bits per byte data may contain pixels in the last byte of each row that will
 *       not be plotted.
 * @note The image is not clipped to the screen, only to the clip rect; the clip rect must already provide screen clipping.
 */
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
		const uint8_t *image_data);

/**
 * Plot a bitmap of screen colour depth. The bitmap is clipped to the supplied clip rect.
 *
 * @param image_start_x The coordinate of the left edge of position to plot image
 * @param image_start_y The coordinate of the top edge of position to plot image
 * @param bitmap_width The width of the image in the bitmap data in pixels
 * @param bitmap_height The height of the image in the bitmap data in pixels
 * @param clip_start_x The left edge of the clip rect
 * @param clip_start_y The top edge of the clip rect
 * @param clip_width The width of the clip rect
 * @param clip_height The height of the clip rect
 * @param image_data The image data
 * @note The image is not clipped to the screen, only to the clip rect; the clip rect must already provide screen clipping.
 */
void mw_hal_lcd_colour_bitmap_clip(int16_t image_start_x,
		int16_t image_start_y,
		uint16_t bitmap_width,
		uint16_t bitmap_height,
		int16_t clip_start_x,
		int16_t clip_start_y,
		int16_t clip_width,
		int16_t clip_height,
		const uint8_t *image_data);

#ifdef __cplusplus
}
#endif

#endif
