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
#include <stdio.h>
#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

static const float daily_temps[25] = {11.0f, 11.1f, 10.9f, 10.3f, 10.3f, 10.1f, 10.3f, 11.4f, 12.4f, 14.1f, 15.9f,
		                              16.8f, 20.0f, 21.1f, 22.8f, 23.0f, 22.5f, 22.0f, 20.4f, 18.9f, 17.0f, 14.4f,
									  12.3f, 11.9f, 11.7f};

static const float weekly_mins[8] = {11.0f, 10.5f, 12.6f, 13.1f, 11.9f, 11.2f, 10.4f, 11.2f};

static const float weekly_maxs[8] = {22.8f, 17.5f, 19.6f, 23.0f, 23.9f, 21.2f, 19.4f, 17.2f};

/************
*** TYPES ***
************/

typedef struct
{
} window_temp_data_t;


/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern mw_handle_t button_handle;

/**********************
*** LOCAL VARIABLES ***
**********************/

/* no data in this structure yet so not used
static window_temp_data_t window_temp_data;
*/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_temp_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	uint8_t i;
	uint16_t x;
	uint16_t y;
	char buf[3];

	MW_ASSERT(draw_info, "Null pointer parameter");

	/* white background */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	/* grey borders */
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREY2);
	mw_gl_rectangle(draw_info,
			0,
			18,
			mw_get_window_client_rect(window_handle).width,
			5);
	mw_gl_rectangle(draw_info,
			0,
			18,
			5,
			mw_get_window_client_rect(window_handle).height - 18);
	mw_gl_rectangle(draw_info,
			mw_get_window_client_rect(window_handle).width - 5,
			18,
			5,
			mw_get_window_client_rect(window_handle).height - 18);
	mw_gl_rectangle(draw_info,
			5,
			mw_get_window_client_rect(window_handle).height - 40,
			mw_get_window_client_rect(window_handle).width - 10,
			40);

	/* blue title bar */
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLUE);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			18);
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_font(MW_GL_TITLE_FONT);
	mw_gl_string(draw_info, 2, 2, "Temperature Log");

	/* white area edge */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_vline(draw_info, 5, 23, 279);
	mw_gl_hline(draw_info, 6, 234, 23);
	mw_gl_vline(draw_info, 234, 23, 279);
	mw_gl_hline(draw_info, 6, 234, 279);

	/* top graph background */
	mw_gl_set_solid_fill_colour(0xe7d9);
	mw_gl_rectangle(draw_info, 30, 50, 192, 80);

	/* top graph title */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_font(MW_GL_FONT_9);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_string(draw_info, 13, 30, "Day Log");

	/* top graph vertical lines */
    for (x = 30; x <= 222; x += 8)
    {
    	if (x == 30 || x == 222)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
    	}
    	else if ((x - 30) % 16 == 0)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY4);
    	}
    	else
    	{
    		mw_gl_set_line(MW_GL_DOT_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY3);
    	}
    	mw_gl_vline(draw_info, x, 50, 130);
    }

    /* top graph horizontal lines */
	for (y = 50; y <= 130; y+= 10)
	{
    	if (y == 50 || y == 130)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
    	}
    	else if ((y - 50) % 20 == 0)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY4);
    	}
    	else
    	{
    		mw_gl_set_line(MW_GL_DOT_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY3);
    	}
		mw_gl_hline(draw_info, 31, 221, y);
	}

	/* top graph y axis labels */
	mw_gl_set_fg_colour(0x54c2);
	for (y = 10; y <= 26; y += 4)
	{
		sprintf(buf, "%u", y);
		mw_gl_string(draw_info, 13, 128 - (y - 10) * 5, buf);
	}

	/* top graph x axis labels */
	for (x = 0; x <= 24; x += 4)
	{
		sprintf(buf, "%02u", x);
		mw_gl_string(draw_info, 25 + x * 8 , 135, buf);
	}

	/* top graph graph line */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	for (i = 0; i < 24; i++)
	{
		mw_gl_line(draw_info, 30 + i * 8,
				130 - (daily_temps[i] - 10) * 5,
				30 + (i + 1) * 8,
				130 - (daily_temps[i + 1] - 10) * 5);
	}

	/* bottom graph background */
	mw_gl_set_solid_fill_colour(0xe7d9);
	mw_gl_rectangle(draw_info, 30, 180, 196, 80);

	/* bottom graph title */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_string(draw_info, 13, 160, "Weekly Max/Min");

	/* bottom graph vertical lines */
    for (x = 30; x <= 226; x += 7)
    {
    	if (x == 30 || x == 226)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
    	}
    	else if ((x - 30) % 14 == 0)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY4);
    	}
    	else
    	{
    		mw_gl_set_line(MW_GL_DOT_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY3);
    	}
    	mw_gl_vline(draw_info, x, 180, 260);
    }

    /* bottom graph horizontal lines */
	for (y = 180; y <= 260; y+= 10)
	{
    	if (y == 180 || y == 260)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
    	}
    	else if ((y - 180) % 20 == 0)
    	{
    		mw_gl_set_line(MW_GL_SOLID_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY4);
    	}
    	else
    	{
    		mw_gl_set_line(MW_GL_DOT_LINE);
    		mw_gl_set_fg_colour(MW_HAL_LCD_GREY3);
    	}
		mw_gl_hline(draw_info, 31, 225, y);
	}

	/* bottom graph y axis labels */
	mw_gl_set_fg_colour(0x54c2);
	for (y = 10; y <= 26; y += 4)
	{
		sprintf(buf, "%u", y);
		mw_gl_string(draw_info, 13, 258 - (y - 10) * 5, buf);
	}

	/* bottom graph x axis labels */
	for (x = 0; x <= 7; x++)
	{
		sprintf(buf, "%02u", x);
		mw_gl_string(draw_info, 25 + x * 28 , 265, buf);
	}

	/* bottom graph mins graph line */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLUE);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	for (i = 0; i < 7; i++)
	{
		mw_gl_line(draw_info, 30 + i * 28,
				260 - (weekly_mins[i] - 10) * 5,
				30 + (i + 1) * 28,
				260 - (weekly_mins[i + 1] - 10) * 5);
	}

	/* bottom graph mins graph line */
	mw_gl_set_fg_colour(MW_HAL_LCD_RED);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	for (i = 0; i < 7; i++)
	{
		mw_gl_line(draw_info, 30 + i * 28,
				260 - (weekly_maxs[i] - 10) * 5,
				30 + (i + 1) * 28,
				260 - (weekly_maxs[i + 1] - 10) * 5);
	}
}

void window_temp_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
	    /* set window invisible */
		mw_set_window_visible(message->recipient_handle, false);

		/* a window has changed visibility so repaint all */
		mw_paint_all();
		break;

	default:
		break;
	}
}
