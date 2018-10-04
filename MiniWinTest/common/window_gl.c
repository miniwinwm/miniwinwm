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

#include <miniwin.h>
#include <string.h>

/****************
*** CONSTANTS ***
****************/

#define GL_TEST_TIME	 	14
#define SHAPE_POINTS 		(sizeof(shape_x_const) / sizeof(int16_t))
static const int16_t shape_x_const[] = {0, -5, 0, 5};
static const int16_t shape_y_const[] = {-10, 10, 5, 10};

/* width = 18
   height = 16 */
static const uint8_t snail[]={
255, 255, 128,
255, 255, 0,
129, 255, 128,
60, 255, 0,
126, 127, 128,
97, 63, 0,
76, 191, 128,
94, 177, 0,
88, 170, 128,
95, 32, 0,
76, 42, 128,
97, 133, 0,
48, 3, 128,
128, 7, 0,
0, 15, 128,
0, 15, 0
};

/************
*** TYPES ***
************/

/**
 * Window data structure 
 */
typedef struct
{
	uint8_t next_test;				/**< Next test to run */
	uint8_t timer_id;				/**< Timer driving tests */
} window_gl_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint8_t kitten[];
extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_gl_data_t window_GL_data;
static int16_t shape_x[SHAPE_POINTS];
static int16_t shape_y[SHAPE_POINTS];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_gl_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	uint16_t x;
	uint16_t y;
	const uint16_t pattern[16]={0xffff, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0xffff, 0xffff,
			0xffff, 0xffff, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0x83c1, 0xffff};

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_ref).width,
			mw_get_window_client_rect(window_ref).height);

	switch (window_GL_data.next_test)
	{
	case 1:
		/* check hline, solid and line-styled, clipping, and location relative to screen edges */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 1);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width * 2, 3);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, mw_get_window_client_rect(window_ref).height - 2);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 10);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 20);
		break;

	case 2:
		/* check vline, solid and line-styled, clipping, and location relative to screen edges */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_vline(draw_info, 1, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 3, 0, mw_get_window_client_rect(window_ref).height * 2);
		mw_gl_vline(draw_info, mw_get_window_client_rect(window_ref).width - 2, 0, mw_get_window_client_rect(window_ref).height - 2);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_vline(draw_info, 10, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_vline(draw_info, 20, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 3:
		/* check 2 pixel drawing routines for different colours */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_clear_pattern();
		for(y = 20; y < 40; y++)
		{
			for(x = 30; x < 50; x++)
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
		mw_gl_line(draw_info, 10, 10, 100, 100);
		mw_gl_line(draw_info, 10, 20, mw_get_window_client_rect(window_ref).width * 2, 110);
		mw_gl_line(draw_info, 10, 30, 100, mw_get_window_client_rect(window_ref).height * 2);
		break;

	case 5:
		/* check general line in all directions */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_line(draw_info,
				0,
				0,
				mw_get_window_client_rect(window_ref).width,
				mw_get_window_client_rect(window_ref).height);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_line(draw_info,
				mw_get_window_client_rect(window_ref).width,
				0,
				0,
				mw_get_window_client_rect(window_ref).height);
		break;

	case 6:
		/* check position of rectangle */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_rectangle(draw_info, 50, 50, 100, 80);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_ref).height);
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
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_ref).height);
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
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_ref).height);
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
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_ref).height);
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
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_ref).height);
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
		/* check text without background and clipping */
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_string(draw_info, 100, 50, "Fred and Berty");
		mw_gl_string(draw_info, mw_get_window_client_rect(window_ref).width - 40, 100, "Fred and Berty");
		break;

	case 14:
		/* check text with background and clipping */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_string(draw_info, 100, 50, "Fred and Berty");
		mw_gl_string(draw_info, mw_get_window_client_rect(window_ref).width - 40, 100, "Fred and Berty");
		break;

	case 15:
		/* check rotated text without background and clipping */
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_DASH_LINE);
		mw_gl_string_vert(draw_info, 100, 50, "Fred and Berty");
		mw_gl_vline(draw_info, 100, 20, 70);
		mw_gl_hline(draw_info, 10, 120, 50);
		mw_gl_string_vert(draw_info, 100, mw_get_window_client_rect(window_ref).height - 20, "Fred and Berty");
		break;

	case 16:
		/* check rotated text with background and clipping */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_string_vert(draw_info, 100, 50, "Fred and Berty");
		mw_gl_string_vert(draw_info, 100, mw_get_window_client_rect(window_ref).height - 20, "Fred and Berty");
		break;

	case 17:
		/* check mono bitmap rendering and location */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_RED);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_monochrome_bitmap(draw_info, 1, 1, 18, 16, snail);
		mw_gl_hline(draw_info, 0, 100, 1);
		mw_gl_vline(draw_info, 1, 0, 100);
		break;

	case 18:
		/* check bitmap clipping */
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_colour(MW_HAL_LCD_BLACK);
		mw_gl_monochrome_bitmap(draw_info, mw_get_window_client_rect(window_ref).width - 10, 1, 18, 16, snail);
		mw_gl_monochrome_bitmap(draw_info, 10, mw_get_window_client_rect(window_ref).height - 10, 18, 16, snail);
		break;

	case 19:
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

	case 20:
		/* check position of circle with border fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 21:
		/* check circle line style */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_circle(draw_info, 100, 100, 100);
		break;

	case 22:
		/* check circle no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 23:
		/* check circle clipped with border solid fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_circle(draw_info, mw_get_window_client_rect(window_ref).width - 20, mw_get_window_client_rect(window_ref).height - 20, 50);
		break;

	case 24:
		/* check circle no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 25:
		/* check circle with border pattern fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_pattern(pattern);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_circle(draw_info, 100, 100, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 26:
		/* check plain arc */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 10, 350);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 27:
		/* check line-styled arc */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_arc(draw_info, 100, 100, 50, 10, 350);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 28:
		/* check arc angles 1 */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 0, 360);
		break;

	case 29:
		/* check arc angles 2 */	
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 10, 180);
		break;

	case 30:
		/* check arc angles 3 */	
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 10, 270);
		break;

	case 31:
		/* check arc angles 4 */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 45, 90);
		break;

	case 32:
		/* check arc angles 5 */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_arc(draw_info, 100, 100, 50, 45, 15);
		break;

	case 33:
		/* check position of segment */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 34:
		/* check segment line style */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_segment(draw_info, 100, 100, 100, 120, 90);
		break;

	case 35:
		/* check segment no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_RED);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 36:
		/* check segment with border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 37:
		/* check segment no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_PINK);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 38:
		/* check segment with border pattern fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_pattern(pattern);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_segment(draw_info, 100, 100, 50, 120, 90);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 150);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 150, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 39:
		/* check position of rounded rectangle */
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 50);
		mw_gl_hline(draw_info, 0, mw_get_window_client_rect(window_ref).width, 129);
		mw_gl_vline(draw_info, 50, 0, mw_get_window_client_rect(window_ref).height);
		mw_gl_vline(draw_info, 149, 0, mw_get_window_client_rect(window_ref).height);
		break;

	case 40:
		/* check rounded rectangle line style */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 41:
		/* check rounded rectangle no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 42:
		/* check rounded rectangle with border solid fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 43:
		/* check rounded rectangle no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_RED);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 44:
		/* check rounded rectangle with border pattern fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_RED);
		mw_gl_set_pattern(pattern);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_rounded_rectangle(draw_info, 50, 50, 100, 80, 20);
		break;

	case 45:
		/* check poly draw 1 */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		memcpy(shape_x, shape_x_const, sizeof(shape_x));
		memcpy(shape_y, shape_y_const, sizeof(shape_y));
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 46:
		/* check poly scale and rotate */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		memcpy(shape_x, shape_x_const, sizeof(shape_x));
		memcpy(shape_y, shape_y_const, sizeof(shape_y));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 45);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 47:
		/* check poly rotate 2 */	
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		memcpy(shape_x, shape_x_const, sizeof(shape_x));
		memcpy(shape_y, shape_y_const, sizeof(shape_y));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, -45);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 48:
		/* check poly rotate 3 */	
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		memcpy(shape_x, shape_x_const, sizeof(shape_x));
		memcpy(shape_y, shape_y_const, sizeof(shape_y));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 245);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 49:
		/* basic poly */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_border(MW_GL_BORDER_ON);
		memcpy(shape_x, shape_x_const, sizeof(shape_x));
		memcpy(shape_y, shape_y_const, sizeof(shape_y));
		mw_gl_scale_shape(SHAPE_POINTS, shape_x, shape_y, 100, 100);
		mw_gl_rotate_shape(SHAPE_POINTS, shape_x, shape_y, 35);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 50:
		/* check poly line style */
		mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fill(MW_GL_NO_FILL);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 51:
		/* check poly no border solid fill */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 52:
		/* poly with border solid fill */
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 53:
		/* check poly no border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_set_fg_colour(MW_HAL_LCD_RED);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150,150);
		break;

	case 54:
		/* check poly with border pattern fill */
		mw_gl_set_pattern(pattern);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_fg_colour(MW_HAL_LCD_RED);
		mw_gl_set_bg_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y, 150, 150);
		break;

	case 55:
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
	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_GL_data.next_test = 0;
		window_GL_data.timer_id = mw_set_timer(mw_tick_counter + GL_TEST_TIME, message->recipient_id, MW_WINDOW_MESSAGE);
		break;

	case MW_WINDOW_REMOVED_MESSAGE:
		mw_cancel_timer(window_GL_data.timer_id);
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		window_GL_data.timer_id = mw_set_timer(mw_tick_counter + GL_TEST_TIME, message->recipient_id, MW_WINDOW_MESSAGE);
		window_GL_data.next_test++;
		mw_paint_window_client(message->recipient_id);
		break;

	default:
		break;
	}
}
