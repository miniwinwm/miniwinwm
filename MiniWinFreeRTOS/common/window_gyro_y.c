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

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "miniwin.h"
#include "ui/ui_common.h"
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "gyro_util.h"

/****************
*** CONSTANTS ***
****************/

#define SHAPE_POINTS (sizeof(shape_x_const) / sizeof(int16_t))		/**< Number of points in arrow shape */
static const int16_t shape_x_const[] = {0, -12, 0, 12};				/**< Arrow shape x coordinates */
static const int16_t shape_y_const[] = {-25, 25, 12, 25};			/**< Arrow shape y coordinates */
static const mw_util_rect_t arrow_rect = {13, 13, 54, 54};			/**< Clip region for redrawing arrow */

/************
*** TYPES ***
************/

typedef struct
{
	int16_t angle;					/**< Last received angle */
	char text_transfer_buffer[10];	/**< Buffer for label text */
	int16_t angle_offset;			//**< Offset set using zero button */
	int16_t previous_drawn_angle;	/**< The previous angle shown on the display */
} window_gyro_y_data_t;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern mw_handle_t button_gyro_y_handle;
extern mw_handle_t label_gyro_y_handle;
extern MessageBufferHandle_t gyro_y_message_buffer;
extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_gyro_y_data_t window_gyro_y_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_gyro_y_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	static int16_t shape_x[SHAPE_POINTS];
	uint16_t offset_adjusted_angle;
	uint8_t i;

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

	/* draw angle arrow */
	offset_adjusted_angle = gyro_util_rationalize_angle(window_gyro_y_data.angle - window_gyro_y_data.angle_offset);

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLUE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	memcpy(shape_x, shape_x_const, sizeof(shape_x));
	for (i = 0; i < SHAPE_POINTS; i++)
	{
		shape_x[i] *= 100.0f * cos((float)offset_adjusted_angle / (float)(180.0 / M_PI));
		shape_x[i] /= 100;
	}
	mw_gl_poly(draw_info, SHAPE_POINTS, shape_x, shape_y_const, 40, 40);
}

void window_gyro_y_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_gyro_y_data.angle_offset = 0;
		window_gyro_y_data.angle = 0;
		window_gyro_y_data.previous_drawn_angle = 0;
		mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND / 4, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		window_gyro_y_data.angle_offset = window_gyro_y_data.angle;
		break;

	case MW_TIMER_MESSAGE:
		{
			float angle;
			size_t bytes;
			int16_t offset_adjusted_angle;

			bytes = xMessageBufferReceive(gyro_y_message_buffer,
		                              (void *)&angle,
		                              sizeof(float),
		                              0);

			if (bytes > 0)
			{
				window_gyro_y_data.angle = (int16_t)angle;

				offset_adjusted_angle = gyro_util_rationalize_angle(window_gyro_y_data.angle - window_gyro_y_data.angle_offset);

				/* check if angle has changed since last drawn */
				if (window_gyro_y_data.previous_drawn_angle != offset_adjusted_angle)
				{
					/* it has so redraw */
					window_gyro_y_data.previous_drawn_angle = offset_adjusted_angle;

					sprintf(window_gyro_y_data.text_transfer_buffer, "%d", (int)offset_adjusted_angle);
					mw_ui_common_post_pointer_to_control(label_gyro_y_handle, window_gyro_y_data.text_transfer_buffer);
					mw_paint_control(label_gyro_y_handle);

					mw_paint_window_client_rect(message->recipient_handle, &arrow_rect);
				}
			}

			/* reset timer */
			mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND / 4, message->recipient_handle, MW_WINDOW_MESSAGE);
		}
		break;

	default:
		break;
	}
}
