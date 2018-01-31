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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "gl/gl.h"
#include "hal/hal_lcd.h"

/****************
*** CONSTANTS ***
****************/

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

void mw_debug_print_assert(const char *function_name, int32_t line_number)
{
    const mw_gl_draw_info_t draw_info = {0, 0, {0, 0, MW_HAL_LCD_WIDTH, MW_HAL_LCD_HEIGHT}};
    char number_buffer[15];

	mw_hal_lcd_filled_rectangle(0,
		0,
		MW_HAL_LCD_WIDTH,
		MW_HAL_LCD_HEIGHT,
		MW_HAL_LCD_BLUE);

	mw_gl_set_fg_colour(MW_HAL_LCD_YELLOW);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

	mw_gl_string(&draw_info, 0, 0, "ASSERT FAILED");
	mw_gl_string(&draw_info, 0, MW_GL_STANDARD_CHARACTER_HEIGHT, function_name);
	sprintf(number_buffer, "line: %d", (int)line_number);
	mw_gl_string(&draw_info, 0, 2 * MW_GL_STANDARD_CHARACTER_HEIGHT, number_buffer);

	while(true);
}
#endif
