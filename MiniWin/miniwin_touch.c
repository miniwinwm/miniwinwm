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

/***************
*** INCLUDES ***
***************/

#include <stdlib.h>
#include "miniwin_debug.h"
#include "miniwin_settings.h"
#include "miniwin_touch.h"
#include "hal/hal_lcd.h"
#include "hal/hal_touch.h"
#include "hal/hal_delay.h"

/****************
*** CONSTANTS ***
****************/

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

static void draw_cross(int16_t x, int16_t y, int16_t length);

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
static void draw_cross(int16_t x, int16_t y, int16_t length)
{
	mw_gl_draw_info_t draw_info_root = {0};
	draw_info_root.clip_rect.width = MW_ROOT_WIDTH;
	draw_info_root.clip_rect.height = MW_ROOT_HEIGHT;

	mw_hal_lcd_filled_rectangle(0, 0, MW_ROOT_WIDTH, MW_ROOT_HEIGHT, MW_HAL_LCD_WHITE);
	mw_hal_lcd_filled_rectangle(x - length / 2, y, length, 1, MW_HAL_LCD_BLACK);
	mw_hal_lcd_filled_rectangle(x, y - length / 2, 1, length, MW_HAL_LCD_BLACK);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_font(MW_GL_TITLE_FONT);
	mw_gl_string(&draw_info_root,
			(MW_ROOT_WIDTH - (int16_t)mw_gl_get_string_width_pixels(MW_CALIBRATE_TEXT)) / 2,
			MW_ROOT_HEIGHT / 2,
			MW_CALIBRATE_TEXT);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_hal_touch_state_t mw_touch_get_display_touch(int16_t* x, int16_t* y)
{
	POINT_T raw_point;
	POINT_T display_point;
	uint16_t raw_x;
	uint16_t raw_y;

	MW_ASSERT(x != (void*)0, "Null pointer argument");
	MW_ASSERT(y != (void*)0, "Null pointer argument");

	/* read touch point and check if valid */
	if (!mw_hal_touch_get_point(&raw_x, &raw_y))
	{
		/* no valid point to read */
		return (MW_HAL_TOUCH_STATE_UP);
	}

	raw_point.x = (INT_32)raw_x;
	raw_point.y = (INT_32)raw_y;

	(void)getDisplayPoint(&display_point, &raw_point, mw_settings_get_calibration_matrix());

	/* limit touch point to display size */
#if defined(MW_DISPLAY_ROTATION_0) || defined(MW_DISPLAY_ROTATION_180)
	if (display_point.x >= (INT_32)mw_hal_lcd_get_display_width())
	{
		display_point.x = (INT_32)mw_hal_lcd_get_display_width() - 1;
	}
	if (display_point.y >= (INT_32)mw_hal_lcd_get_display_height())
	{
		display_point.y = (INT_32)mw_hal_lcd_get_display_height() - 1;
	}
#else
	if (display_point.x >= (INT_32)mw_hal_lcd_get_display_height())
	{
		display_point.x = (INT_32)mw_hal_lcd_get_display_height() - 1;
	}
	if (display_point.y >= (INT_32)mw_hal_lcd_get_display_width())
	{
		display_point.y = (INT_32)mw_hal_lcd_get_display_width() - 1;
	}
#endif
	if (display_point.x < 0)
	{
		display_point.x = 0;
	}
	if (display_point.y < 0)
	{
		display_point.y = 0;
	}

	*x = (int16_t)display_point.x;
	*y = (int16_t)display_point.y;

	return (MW_HAL_TOUCH_STATE_DOWN);
}

void mw_touch_calibrate(MATRIX_CAL *matrix)
{
	int16_t minimum_screen_dimension = MW_ROOT_WIDTH < MW_ROOT_HEIGHT ? MW_ROOT_WIDTH : MW_ROOT_HEIGHT;
	int16_t touch_cross_size = minimum_screen_dimension / 6;

	POINT_T raw_points[3];
	POINT_T display_points[3];
	display_points[0].x = touch_cross_size;
	display_points[0].y = touch_cross_size;
	display_points[1].x = MW_ROOT_WIDTH - (INT_32)touch_cross_size;
	display_points[1].y = touch_cross_size;
	display_points[2].x = MW_ROOT_WIDTH - (INT_32)touch_cross_size;
	display_points[2].y = MW_ROOT_HEIGHT - (INT_32)touch_cross_size;
	uint16_t x;
	uint16_t y;

	MW_ASSERT(matrix != (void*)0, "Null pointer argument");

    /* first point */
	draw_cross((int16_t)display_points[0].x, (int16_t)display_points[0].y, touch_cross_size);
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
	}
	while (!mw_hal_touch_get_point(&x, &y))
	{
	}
	raw_points[0].x = (INT_32)x;
	raw_points[0].y = (INT_32)y;
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN)
	{
	}

    /* second point */
	draw_cross((int16_t)display_points[1].x, (int16_t)display_points[1].y, touch_cross_size);
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
	}
	while (!mw_hal_touch_get_point(&x, &y))
	{
	}
	raw_points[1].x = (INT_32)x;
	raw_points[1].y = (INT_32)y;
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN)
	{
	}

    /* third point */
	draw_cross((int16_t)display_points[2].x, (int16_t)display_points[2].y, touch_cross_size);
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
	}
	while (!mw_hal_touch_get_point(&x, &y))
	{
	}
	raw_points[2].x = (INT_32)x;
	raw_points[2].y = (INT_32)y;
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN)
	{
	}

	(void)setCalibrationMatrix(display_points, raw_points, matrix);
}
