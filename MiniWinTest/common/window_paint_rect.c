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

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Window data structure 
 */
typedef struct 
{
	uint8_t choice;					/**< The list box choice made by the user */
} window_paint_rect_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static const mw_util_rect_t rect_to_repaint = {10, 10, 80, 80};
static window_paint_rect_data_t window_paint_rect_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_paint_rect_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	float x;
	float y;

	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_fill(MW_GL_NO_FILL);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_rectangle(draw_info,
			10,
			10,
			80,
			80);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLUE);
	mw_gl_hline(draw_info, 10, 90, 50);
	mw_gl_vline(draw_info, 50, 10, 90);

	mw_gl_set_fg_colour(MW_HAL_LCD_RED);
	switch (window_paint_rect_data.choice)
	{
	case 0:
		for (x = -40.0f; x < 40.0f; x += 1.0f)
		{
			y = -2.0f * x;
			if (x > -40.0f && x < 40.0f && y > -40.0f && y < 40.0f)
			{
				mw_gl_fg_pixel(draw_info, (int16_t)x + 50, (int16_t)y + 50);
			}
		}
		break;

	case 1:
		for (x = -40.0f; x < 40.0f; x += 1.0f)
		{
			y = (x * x) / -20.0f;
			if (x > -40.0f && x < 40.0f && y > -40.0f && y < 40.0f)
			{
				mw_gl_fg_pixel(draw_info, (int16_t)x + 50, (int16_t)y + 50);
			}
		}
		break;

	case 2:
		for (x = -40.0f; x < 40.0f; x += 1.0f)
		{
			y = (x * x * x) / -400.0f;
			if (x > -40.0f && x < 40.0f && y > -40.0f && y < 40.0f)
			{
				mw_gl_fg_pixel(draw_info, (int16_t)x + 50, (int16_t)y + 50);
			}
		}
		break;

	default:
		break;
	}
}

void window_paint_rect_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_paint_rect_data.choice = 0;
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		/* pop up list box item pressed */
		window_paint_rect_data.choice = message->message_data;
		mw_paint_window_client_rect(message->recipient_handle, &rect_to_repaint);
		break;

	default:
		break;
	}
}
