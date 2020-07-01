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

#include <string.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_gl.h"

/****************
*** CONSTANTS ***
****************/

#define GL_TEST_TIME	 	14U			/**< Time between tests in system ticks */
#define SHAPE_POINTS 		(uint8_t)(sizeof(shape_x_const) / sizeof(int16_t))

/************
*** TYPES ***
************/

/**
 * Window data structure 
 */
typedef struct
{
	uint8_t next_test;				/**< Next test to run */
	mw_handle_t timer_handle;		/**< Timer driving tests */
} window_gl_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_gl_data_t window_GL_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_gl_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	/* width = 18
	   height = 16 */
	const uint8_t snail[] = {
	255U, 255U, 128U,
	255U, 255U, 0U,
	129U, 255U, 128U,
	60U, 255U, 0U,
	126U, 127U, 128U,
	97U, 63U, 0U,
	76U, 191U, 128U,
	94U, 177U, 0U,
	88U, 170U, 128U,
	95U, 32U, 0U,
	76U, 42U, 128U,
	97U, 133U, 0U,
	48U, 3U, 128U,
	128U, 7U, 0U,
	0U, 15U, 128U,
	0U, 15U, 0U
	};
	const int16_t shape_x_const[] = {0, -5, 0, 5};
	const int16_t shape_y_const[] = {-10, 10, 5, 10};
	const uint16_t pattern[16] = {0xffff, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0xffff, 0xffff,
			0xffff, 0xffff, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0xffff};
	int16_t shape_x[SHAPE_POINTS];
	int16_t shape_y[SHAPE_POINTS];
	int16_t x;
	int16_t y;

	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	switch (window_GL_data.next_test)
	{
	case 1:
		/* check hline, solid and line-styled, clipping, and location relative to screen edges */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 1);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width * 2, 3);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, mw_get_window_client_rect(window_handle).height - 2);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 10);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 20);
		break;

	case 2:
		/* check vline, solid and line-styled, clipping, and location relative to screen edges */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_vline(draw_info, 1, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 3, 0, mw_get_window_client_rect(window_handle).height * 2);
		mw_gl_vline(draw_info, mw_get_window_client_rect(window_handle).width - 2, 0, mw_get_window_client_rect(window_handle).height - 2);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_vline(draw_info, 10, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_vline(draw_info, 20, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 3:
		/* check 2 pixel drawing routines for different colours */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_clear_pattern();
		for (y = 20; y < 40; y++)
		{
			for (x = 30; x < 50; x++)
			{
				mw_gl_fg_pixel(draw_info, x, y);
				mw_gl_bg_pixel(draw_info, x, y + 30);
			}
		}
		break;

	case 4:
		/* check general line solid and with line style and clipping */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_line(draw_info, -10, -100, 1000, 1000);
		mw_gl_line(draw_info, 10, 10, 100, 100);
		mw_gl_line(draw_info, 10, 20, mw_get_window_client_rect(window_handle).width * 2, 110);
		mw_gl_line(draw_info, 10, 30, 100, mw_get_window_client_rect(window_handle).height * 2);
		break;

	case 5:
		/* check general line in all directions */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_line(draw_info,
				0,
				0,
				mw_get_window_client_rect(window_handle).width,
				mw_get_window_client_rect(window_handle).height);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_line(draw_info,
				mw_get_window_client_rect(window_handle).width,
				0,
				0,
				mw_get_window_client_rect(window_handle).height);
		break;

	case 6:
		/* check position of rectangle */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 7:
		/* check rectangle line style */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		break;

	case 8:
		/* check rectangle no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 9:
		/* check rectangle with border solid fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_YELLOW);
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 10:
		/* check rectangle no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLUE);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 11:
		/* check rectangle with border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLUE);
		mw_gl_set_bg_colour(MW_HAL_LCD_GREEN);
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 12:
		/* check pattern clear */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_CYAN);
		mw_gl_clear_pattern();
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		break;

	case 13:
		/* check text without background 0 degrees*/
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_vline(draw_info, 10, 0, 200);
		mw_gl_hline(draw_info, 0, 200, 30);
		mw_gl_hline(draw_info, 0, 200, 40);
		mw_gl_hline(draw_info, 0, 200, 53);
		mw_gl_hline(draw_info, 0, 200, 70);
		mw_gl_hline(draw_info, 0, 200, 90);
		mw_gl_hline(draw_info, 0, 200, 120);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 10, 30, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 10, 40, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 10, 53, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 10, 70, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 10, 90, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 10, 120, "Fred and Berty");
		break;

	case 14:
		/* check text with background 0 degrees */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_vline(draw_info, 10, 0, 200);
		mw_gl_hline(draw_info, 0, 200, 30);
		mw_gl_hline(draw_info, 0, 200, 40);
		mw_gl_hline(draw_info, 0, 200, 53);
		mw_gl_hline(draw_info, 0, 200, 70);
		mw_gl_hline(draw_info, 0, 200, 90);
		mw_gl_hline(draw_info, 0, 200, 120);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 10, 30, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 10, 40, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 10, 53, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 10, 70, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 10, 90, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 10, 120, "Fred and Berty");
		break;

	case 15:
		/* check rotated text without background 90 degrees*/
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_hline(draw_info, 0, 200, 10);
		mw_gl_vline(draw_info, 30, 0, 200);
		mw_gl_vline(draw_info, 43, 0, 200);
		mw_gl_vline(draw_info, 60, 0, 200);
		mw_gl_vline(draw_info, 81, 0, 200);
		mw_gl_vline(draw_info, 105, 0, 200);
		mw_gl_vline(draw_info, 135, 0, 200);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_90);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 30, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 43, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 60, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 81, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 105, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 135, 10, "Fred and Berty");
		break;

	case 16:
		/* check rotated text with background 90 degrees */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_hline(draw_info, 0, 200, 10);
		mw_gl_vline(draw_info, 30, 0, 200);
		mw_gl_vline(draw_info, 43, 0, 200);
		mw_gl_vline(draw_info, 60, 0, 200);
		mw_gl_vline(draw_info, 81, 0, 200);
		mw_gl_vline(draw_info, 105, 0, 200);
		mw_gl_vline(draw_info, 135, 0, 200);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_90);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 30, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 43, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 60, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 81, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 105, 10, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 135, 10, "Fred and Berty");
		break;

	case 17:
		/* check rotated text without background 180 degrees*/
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_vline(draw_info, 200, 0, 200);
		mw_gl_hline(draw_info, 0, 200, 30);
		mw_gl_hline(draw_info, 0, 200, 43);
		mw_gl_hline(draw_info, 0, 200, 60);
		mw_gl_hline(draw_info, 0, 200, 81);
		mw_gl_hline(draw_info, 0, 200, 105);
		mw_gl_hline(draw_info, 0, 200, 135);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_180);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 200, 30, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 200, 43, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 200, 60, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 200, 81, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 200, 105, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 200, 135, "Fred and Berty");
		break;

	case 18:
		/* check rotated text with background 180 degrees */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_vline(draw_info, 200, 0, 200);
		mw_gl_hline(draw_info, 0, 200, 30);
		mw_gl_hline(draw_info, 0, 200, 43);
		mw_gl_hline(draw_info, 0, 200, 60);
		mw_gl_hline(draw_info, 0, 200, 81);
		mw_gl_hline(draw_info, 0, 200, 105);
		mw_gl_hline(draw_info, 0, 200, 135);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_180);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 200, 30, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 200, 43, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 200, 60, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 200, 81, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 200, 105, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 200, 135, "Fred and Berty");
		break;

	case 19:
		/* check rotated text without background 270 degrees*/
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_hline(draw_info, 0, 200, 150);
		mw_gl_vline(draw_info, 30, 0, 200);
		mw_gl_vline(draw_info, 43, 0, 200);
		mw_gl_vline(draw_info, 60, 0, 200);
		mw_gl_vline(draw_info, 81, 0, 200);
		mw_gl_vline(draw_info, 105, 0, 200);
		mw_gl_vline(draw_info, 135, 0, 200);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_270);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 30, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 43, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 60, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 81, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 105, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 135, 150, "Fred and Berty");
		break;

	case 20:
		/* check rotated text with background 270 degrees */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);

		mw_gl_set_fg_colour(MW_HAL_LCD_PURPLE);
		mw_gl_hline(draw_info, 0, 200, 150);
		mw_gl_vline(draw_info, 30, 0, 200);
		mw_gl_vline(draw_info, 43, 0, 200);
		mw_gl_vline(draw_info, 60, 0, 200);
		mw_gl_vline(draw_info, 81, 0, 200);
		mw_gl_vline(draw_info, 105, 0, 200);
		mw_gl_vline(draw_info, 135, 0, 200);

		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_270);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 30, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_12);
		mw_gl_string(draw_info, 43, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_16);
		mw_gl_string(draw_info, 60, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_20);
		mw_gl_string(draw_info, 81, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_FONT_24);
		mw_gl_string(draw_info, 105, 150, "Fred and Berty");
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 135, 150, "Fred and Berty");
		break;

	case 21:
		/* check mono bitmap rendering and location */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_RED);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_monochrome_bitmap(draw_info, 1, 1, 18, 16, snail);
		mw_gl_hline(draw_info, 0, 100, 1);
		mw_gl_vline(draw_info, 1, 0, 100);
		break;

	case 22:
		/* check bitmap clipping */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_monochrome_bitmap(draw_info, mw_get_window_client_rect(window_handle).width - 10, 1, 18, 16, snail);
		mw_gl_monochrome_bitmap(draw_info, 10, mw_get_window_client_rect(window_handle).height - 10, 18, 16, snail);
		break;

	case 23:
		/* check bitmap transparent */
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_CYAN);
		mw_gl_clear_pattern();
		mw_gl_rectangle(draw_info, 10, 10, 100, 100);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_monochrome_bitmap(draw_info, 30, 30, 18, 16, snail);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		break;

	case 24:
		/* check position of circle with border fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 25:
		/* check circle line style */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_circle(draw_info, 100, 100, 100);
		break;

	case 26:
		/* check circle no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 27:
		/* check circle clipped with border solid fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_circle(draw_info, mw_get_window_client_rect(window_handle).width - 20, mw_get_window_client_rect(window_handle).height - 20, 50);
		break;

	case 28:
		/* check circle no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 29:
		/* check circle with border pattern fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_pattern(pattern);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 30:
		/* check plain arc */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, -45, 45);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 31:
		/* check line-styled arc */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_arc(draw_info, 100, 100, 50, 10, 350);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 32:
		/* check arc angles 1 */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 0, 360);
		break;

	case 33:
		/* check arc angles 2 */	
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 10, 180);
		break;

	case 34:
		/* check arc angles 3 */	
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 10, 270);
		break;

	case 35:
		/* check arc angles 4 */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 45, 90);
		break;

	case 36:
		/* check arc angles 5 */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 45, 15);
		break;

	case 37:
		/* check position of segment */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 38:
		/* check segment line style */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_segment(draw_info, 100, 100, 100, 120, 90);
		break;

	case 39:
		/* check segment no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_RED);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 40:
		/* check segment with border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 41:
		/* check segment no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 42:
		/* check segment with border pattern fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_pattern(pattern);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 43:
		/* check position of rounded rectangle */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_handle).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_handle).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_handle).height);
		break;

	case 44:
		/* check rounded rectangle line style */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 45:
		/* check rounded rectangle no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 46:
		/* check rounded rectangle with border solid fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 47:
		/* check rounded rectangle no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_RED);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 48:
		/* check rounded rectangle with border pattern fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_RED);
		mw_gl_set_pattern(pattern);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 49:
		/* check poly draw 1 */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 50:
		/* check poly scale and rotate */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 45);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 51:
		/* check poly rotate 2 */	
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, -45);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 52:
		/* check poly rotate 3 */	
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 245);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 53:
		/* basic poly */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 35);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 54:
		/* check poly line style */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 35);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 55:
		/* check poly no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 35);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 56:
		/* poly with border solid fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 35);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 57:
		/* check poly no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fg_colour(MW_HAL_LCD_RED);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 35);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 58:
		/* check poly with border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fg_colour(MW_HAL_LCD_RED);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		(void)memcpy((shape_x), (shape_x_const), (sizeof(shape_x)));
		(void)memcpy((shape_y), (shape_y_const), (sizeof(shape_y)));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 35);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 59:
		/* check colour bitmap */
		mw_gl_colour_bitmap(draw_info,
				10,
				10,
				150,
				137,
				kitten);
		break;

	default:
		/* send animation counter back to start */
		window_GL_data.next_test = 0;
		break;
	}
}

void window_gl_message_function(const mw_message_t *message)
{
	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_GL_data.next_test = 0;
		window_GL_data.timer_handle = mw_set_timer(mw_tick_counter + GL_TEST_TIME, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

	case MW_TIMER_MESSAGE:
		window_GL_data.timer_handle = mw_set_timer(mw_tick_counter + GL_TEST_TIME, message->recipient_handle, MW_WINDOW_MESSAGE);
		window_GL_data.next_test++;
		mw_paint_window_client(message->recipient_handle);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
