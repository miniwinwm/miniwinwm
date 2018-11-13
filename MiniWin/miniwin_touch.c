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

#include "miniwin_debug.h"
#include "miniwin_settings.h"
#include "miniwin_touch.h"
#include "hal/hal_lcd.h"
#include "hal/hal_touch.h"
#include "hal/hal_delay.h"

/****************
*** CONSTANTS ***
****************/

#define MIN_SCREEN_DIMENSION (MW_HAL_LCD_WIDTH < MW_HAL_LCD_HEIGHT ? MW_HAL_LCD_WIDTH : MW_HAL_LCD_HEIGHT)
#define TOUCH_CROSS_SIZE ( MIN_SCREEN_DIMENSION / 6 )

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern volatile uint32_t mw_tick_counter;
extern const mw_gl_draw_info_t draw_info_root;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void draw_cross(uint16_t x, int16_t y, int16_t length);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Draw a cross for touch calibration purposes. 
 *
 * @param X coordinate of centre of cross 
 * @param Y y coordinate of centre of cross
 * @param length Length of each cross arm
 */
static void draw_cross(uint16_t x, int16_t y, int16_t length)
{
	mw_hal_lcd_filled_rectangle(0, 0, MW_HAL_LCD_WIDTH, MW_HAL_LCD_HEIGHT, MW_HAL_LCD_WHITE);
	mw_hal_lcd_filled_rectangle(x - length / 2, y, length, 1, MW_HAL_LCD_BLACK);
	mw_hal_lcd_filled_rectangle(x, y - length / 2, 1, length, MW_HAL_LCD_BLACK);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_font(MW_GL_TITLE_FONT);
	mw_gl_string(&draw_info_root,
			(MW_HAL_LCD_WIDTH - mw_gl_get_string_width_pixels(MW_CALIBRATE_TEXT)) / 2,
			MW_HAL_LCD_HEIGHT / 2,
			MW_CALIBRATE_TEXT);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_hal_touch_state_t mw_touch_get_display_touch(uint16_t* x, uint16_t* y)
{
	POINT raw_point;
	POINT display_point;
	uint16_t raw_x;
	uint16_t raw_y;

	MW_ASSERT(x, "Null pointer argument");
	MW_ASSERT(y, "Null pointer argument");

	/* read touch point and check if valid */
	if (!mw_hal_touch_get_point(&raw_x, &raw_y))
	{
		/* no valid point to read */
		return MW_HAL_TOUCH_STATE_UP;
	}

	raw_point.x = raw_x;
	raw_point.y = raw_y;

	getDisplayPoint(&display_point, &raw_point, mw_settings_get_calibration_matrix());
	*x = display_point.x;
	*y = display_point.y;

	return MW_HAL_TOUCH_STATE_DOWN;
}

void mw_touch_calibrate(MATRIX *matrix)
{
	POINT raw_points[3];
	POINT display_points[3] = { {TOUCH_CROSS_SIZE, TOUCH_CROSS_SIZE},
			{MW_HAL_LCD_WIDTH - TOUCH_CROSS_SIZE, TOUCH_CROSS_SIZE},
			{MW_HAL_LCD_WIDTH - TOUCH_CROSS_SIZE, MW_HAL_LCD_HEIGHT - TOUCH_CROSS_SIZE} };
	uint16_t x;
	uint16_t y;

	MW_ASSERT(matrix, "Null pointer argument");

    /* first point */
	draw_cross(display_points[0].x, display_points[0].y, TOUCH_CROSS_SIZE);
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
	}
	while (!mw_hal_touch_get_point(&x, &y))
	{
	}
	raw_points[0].x = x;
	raw_points[0].y = y;
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN)
	{
	}

    /* second point */
	draw_cross(display_points[1].x, display_points[1].y, TOUCH_CROSS_SIZE);
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
	}
	while (!mw_hal_touch_get_point(&x, &y))
	{
	}
	raw_points[1].x = x;
	raw_points[1].y = y;
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN)
	{
	}

    /* third point */
	draw_cross(display_points[2].x, display_points[2].y, TOUCH_CROSS_SIZE);
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
	}
	while (!mw_hal_touch_get_point(&x, &y))
	{
	}
	raw_points[2].x = x;
	raw_points[2].y = y;
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN)
	{
	}

	setCalibrationMatrix(display_points, raw_points, matrix);
}
