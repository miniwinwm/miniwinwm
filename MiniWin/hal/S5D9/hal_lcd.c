/*

MIT License

Copyright (c) John Blaiklock 2023 miniwin Embedded Window Manager

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

#ifdef _RENESAS_SYNERGY_

/***************
*** INCLUDES ***
***************/

#include <stdbool.h>
#include <string.h>
#include "miniwin_thread.h"
#include "hal/hal_lcd.h"
#include "hal/hal_delay.h"
#include "miniwin_config.h"

/****************
*** CONSTANTS ***
****************/

#define LCD_DISPLAY_WIDTH_PIXELS    240                         /**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS   320                         /**< This is the height of the display in pixels irrespective of user specified display rotation */
#define LCD_RESET                   IOPORT_PORT_06_PIN_10
#define LCD_CMD                     IOPORT_PORT_01_PIN_15
#define LCD_CS                      IOPORT_PORT_06_PIN_11

/* ILI9341 command set */
#define ILI9341_SW_RESET            0x01U
#define ILI9341_SLEEP_OUT           0x11U
#define ILI9341_VCOM1               0xC5U
#define ILI9341_VCOM2               0xC7U
#define ILI9341_RGB_INTERFACE       0xB0U
#define ILI9341_PRC                 0xF7U
#define ILI9341_POWERA              0xCBU
#define ILI9341_POWERB              0xCFU
#define ILI9341_POWER1              0xC0U
#define ILI9341_POWER2              0xC1U
#define ILI9341_PIXEL_FORMAT        0x3AU
#define ILI9341_PGAMMA              0xE0U
#define ILI9341_POWER_SEQ           0xEDU
#define ILI9341_NGAMMA              0xE1U
#define ILI9341_MAC                 0x36U
#define ILI9341_PAGE_ADDR           0x2BU
#define ILI9341_GAMMA               0x26U
#define ILI9341_FRM_CTRL1           0xB1U
#define ILI9341_INTERFACE           0xF6U
#define ILI9341_DTCA                0xE8U
#define ILI9341_DTCB                0xEAU
#define ILI9341_DFC                 0xB6U
#define ILI9341_COLUMN_ADDR         0x2AU
#define ILI9341_3GAMMA_EN           0xF2U
#define ILI9341_DISP_ON             0x29U

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static volatile bool spi_operation_complete;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static inline void filled_rectangle_rotated(int16_t start_x,
        int16_t start_y,
        int16_t width,
        int16_t height,
        mw_hal_lcd_colour_t colour);
static inline void pixel_rotated(int16_t x, int16_t y, mw_hal_lcd_colour_t colour);
static void ILI9341V_init(void);
static void lcd_write(uint8_t cmd, const uint8_t *data, uint32_t length);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Initialise the ILI9342V display via SPI to set up the specific panel and set up RGB parallel data interface
 */
static void ILI9341V_init(void)
{
    (void)g_lcd_spi.p_api->open(g_lcd_spi.p_ctrl, &g_lcd_spi_cfg);

    (void)g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_HIGH);
    (void)g_ioport.p_api->pinWrite(LCD_RESET, IOPORT_LEVEL_HIGH);
    (void)g_ioport.p_api->pinWrite(LCD_RESET, IOPORT_LEVEL_LOW);
    mw_hal_delay_ms(10U);
    (void)g_ioport.p_api->pinWrite(LCD_RESET, IOPORT_LEVEL_HIGH);

    lcd_write(ILI9341_SW_RESET, (uint8_t *) "\x0", 0UL);
    mw_hal_delay_ms(10U);
    lcd_write(ILI9341_POWERB, (uint8_t *)"\x00\xC1\x30", 3UL);
    lcd_write(ILI9341_DTCA, (uint8_t *)"\x85\x00\x78", 3UL);
    lcd_write(ILI9341_DTCB, (uint8_t *)"\x00\x00", 2UL);
    lcd_write(ILI9341_POWERA, (uint8_t *)"\x39\x2C\x00\x34\x02", 5UL);
    lcd_write(ILI9341_POWER_SEQ, (uint8_t *)"\x64\x03\x12\x81", 4UL);
    lcd_write(ILI9341_PRC, (uint8_t *)"\x20", 1UL);
    lcd_write(ILI9341_POWER1, (uint8_t *)"\x23", 1UL);
    lcd_write(ILI9341_POWER2, (uint8_t *)"\x10", 1UL);
    lcd_write(ILI9341_VCOM1, (uint8_t *)"\x3E\x28", 2UL);
    lcd_write(ILI9341_VCOM2, (uint8_t *)"\x86", 1UL);
    lcd_write(ILI9341_MAC, (uint8_t *)"\x48", 1UL);
    lcd_write(ILI9341_PIXEL_FORMAT, (uint8_t *)"\x55", 1UL);
    lcd_write(ILI9341_FRM_CTRL1, (uint8_t *)"\x00\x18", 2UL);
    lcd_write(ILI9341_DFC, (uint8_t *)"\x08\x82\x27", 3UL);
    lcd_write(ILI9341_3GAMMA_EN, (uint8_t *)"\x00", 1UL);
    lcd_write(ILI9341_RGB_INTERFACE, (uint8_t *)"\xC2", 1UL);
    lcd_write(ILI9341_INTERFACE, (uint8_t *)"\x01\x00\x06", 3UL);
    lcd_write(ILI9341_COLUMN_ADDR, (uint8_t *)"\x00\x00\x00\xEF", 4UL);
    lcd_write(ILI9341_PAGE_ADDR, (uint8_t *)"\x00\x00\x01\x3F", 4UL);
    lcd_write(ILI9341_GAMMA, (uint8_t *)"\x01", 1UL);
    lcd_write(ILI9341_PGAMMA, (uint8_t *)"\x0F\x31\x2B\x0C\x0E\x08\x4E\xF1\x37\x07\x10\x03\x0E\x09\x00", 15UL);
    lcd_write(ILI9341_NGAMMA, (uint8_t *)"\x00\x0E\x14\x03\x11\x07\x31\xC1\x48\x08\x0F\x0C\x31\x36\x0F", 15UL);
    lcd_write(ILI9341_SLEEP_OUT, (uint8_t *)"\x00", 1UL);
    mw_hal_delay_ms(20U);
    lcd_write(ILI9341_DISP_ON, (uint8_t *)"\x00", 1UL);
}

/**
 * Write a command to the ILI9341V LCD controller chip
 *
 * @param cmd The command to write
 * @param data The data that accompanies the command
 * @param length The length of the data in bytes
 */
static void lcd_write(uint8_t cmd, const uint8_t *data, uint32_t length)
{
    (void)g_ioport.p_api->pinWrite(LCD_CMD, IOPORT_LEVEL_LOW);
    (void)g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_LOW);

    spi_operation_complete = false;
    (void)g_lcd_spi.p_api->write(g_lcd_spi.p_ctrl, &cmd, 1UL, SPI_BIT_WIDTH_8_BITS);
    while (!spi_operation_complete)
    {
        mw_hal_delay_ms(1U);
    }

    if (length != 0UL && data != NULL)
    {
        (void)g_ioport.p_api->pinWrite(LCD_CMD, IOPORT_LEVEL_HIGH);

        spi_operation_complete = false;
        (void)g_lcd_spi.p_api->write(g_lcd_spi.p_ctrl, data, length, SPI_BIT_WIDTH_8_BITS);

        while (!spi_operation_complete)
        {
            mw_hal_delay_ms(1U);
        }
    }

    (void)g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_HIGH);
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
    uint32_t x;
    uint32_t y;

    for (y = (uint32_t)start_y; y < (uint32_t)(start_y + height); y++)
    {
        for (x = (uint32_t)start_x; x < (uint32_t)(start_x + width); x++)
        {
            ((uint32_t *)g_display_fb_foreground)[y * (uint32_t)LCD_DISPLAY_WIDTH_PIXELS + x] = (uint32_t)colour;
        }
    }
}

/**
 * Plot a pixel using already rotated coordinates. Position values are not clipped to the screen.
 *
 * @param start_x X position of pixel
 * @param start_y Y position of pixel
 * @param colour The colour of the pixel to plot
 */
static inline void pixel_rotated(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
    ((uint32_t *)g_display_fb_foreground)[(uint32_t)y * (uint32_t)LCD_DISPLAY_WIDTH_PIXELS + (uint32_t)x] = (uint32_t)colour;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void g_lcd_spi_callback(spi_callback_args_t * p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        spi_operation_complete = true;
    }
}

void mw_hal_lcd_init(void)
{
    /* initialize the lcd driver chip */
    ILI9341V_init();

    /* open the display driver */
    g_display.p_api->open(g_display.p_ctrl, g_display.p_cfg);

    /* start displaying the content */
    g_display.p_api->start(g_display.p_ctrl);
}

int16_t mw_hal_lcd_get_display_width(void)
{
    return (LCD_DISPLAY_WIDTH_PIXELS);
}

int16_t mw_hal_lcd_get_display_height(void)
{
    return (LCD_DISPLAY_HEIGHT_PIXELS);
}

inline void mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
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

inline void mw_hal_lcd_filled_rectangle(int16_t start_x,
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
    const uint8_t* image_data)
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
                        mw_hal_lcd_pixel((int16_t)((a * 8) + x + image_start_x), y + image_start_y, fg_colour);
                    }
                    else
                    {
                        mw_hal_lcd_pixel((int16_t)((a * 8) + x + image_start_x), y + image_start_y, bg_colour);
                    }
                }
                mask >>= 1;
            }
        }
    }
}

#endif
