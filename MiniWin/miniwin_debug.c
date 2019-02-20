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

#include <stdint.h>
#include <stdbool.h>
#include "miniwin.h"

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

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

#ifndef NDEBUG

void mw_debug_print_assert(bool expression, const char *function_name, int32_t line_number, const char *message)
{
    mw_gl_draw_info_t draw_info = {0};
    draw_info.clip_rect.width = MW_ROOT_WIDTH;
    draw_info.clip_rect.height = MW_ROOT_HEIGHT;

    char number_buffer[15];

    if (expression)
    {
    	return;
    }

	mw_hal_lcd_filled_rectangle(0,
		0,
		MW_ROOT_WIDTH,
		MW_ROOT_HEIGHT,
		MW_HAL_LCD_BLUE);

	mw_gl_set_fg_colour(MW_HAL_LCD_YELLOW);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_font(MW_GL_FONT_9);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	mw_gl_string(&draw_info, 0, 0, "ASSERT FAILED");
	mw_gl_string(&draw_info, 0, (int16_t)mw_gl_get_font_height() + 1, function_name);
	(void)mw_util_safe_itoa(line_number, number_buffer, 15, 10, false, 0, ' ');

	mw_gl_string(&draw_info, 0, 2 * ((int16_t)mw_gl_get_font_height() + 1), number_buffer);
	mw_gl_string(&draw_info, 0, 3 * ((int16_t)mw_gl_get_font_height() + 1), message);

	while (true)
	{
	}
}
#endif
