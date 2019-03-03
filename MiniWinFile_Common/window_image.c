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
#include "miniwin.h"
#include "miniwin_user.h"
#include "dialogs/dialog_common.h"
#include "gl/gl.h"
#include "app.h"
#include "window_image.h"

/****************
*** CONSTANTS ***
****************/

#define BITMAP_TRASFER_BUFFER_SIZE		16
#define BASIC_BMP_FILE_HEADER_SIZE		0x36U

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static uint8_t bitmap_buffer[BITMAP_TRASFER_BUFFER_SIZE * MW_GL_BITMAP_BYTES_PER_PIXEL];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_image_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	uint32_t file_size;
	int16_t client_width;
	int16_t client_height;
	bool success;
	uint8_t file_buffer[4];
	uint32_t file_data_offset;
	int16_t x_pos;
	int16_t y_pos;
	int16_t x;
	uint32_t row_size;
	uint32_t row_start_address;
	uint32_t pixel;
	image_window_data_t *image_window_data;
	int16_t x_pixels_to_plot;
	int16_t remaining;
	int16_t x_scroll_pos;
	int16_t y_scroll_pos;
	uint32_t temp_uint32;

	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

	/* get this window instance data pointer and check for not null */
	image_window_data = (image_window_data_t*)mw_get_window_instance_data(window_handle);
	if (image_window_data == (void*)0)
	{
		MW_ASSERT((bool)false, "Couldn't find window instance data");
		return;
	}

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREY12);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();

	/* get client dimensions */
	client_width = mw_get_window_client_rect(window_handle).width;
	client_height = mw_get_window_client_rect(window_handle).height;

	success = false;
	if (app_file_open(image_window_data->path_and_filename_image))
	{
		file_size = app_file_size();
		if (file_size >= BASIC_BMP_FILE_HEADER_SIZE)
		{
			app_file_read(file_buffer, 2U);
			if (file_buffer[0] == (uint8_t)'B' && file_buffer[1] == (uint8_t)'M')
			{
				(void)app_file_seek(10U);
				app_file_read(file_buffer, 4U);
				file_data_offset = (uint32_t)file_buffer[0] + ((uint32_t)file_buffer[1] << 8U) + ((uint32_t)file_buffer[2] << 16U) + ((uint32_t)file_buffer[3] << 24U);
				app_file_read(file_buffer, 4U);
				if ((uint32_t)file_buffer[0] + ((uint32_t)file_buffer[1] << 8U) + ((uint32_t)file_buffer[2] << 16U) + ((uint32_t)file_buffer[3] << 24) == 40U)
				{
					/* Windows BITMAPINFOHEADER */
					app_file_read(file_buffer, 4);
					temp_uint32 = (uint32_t)file_buffer[0] + ((uint32_t)file_buffer[1] << 8U) + ((uint32_t)file_buffer[2] << 16U) + ((uint32_t)file_buffer[3] << 24U);
					image_window_data->image_width = (int16_t)temp_uint32;
					app_file_read(file_buffer, 4);
					temp_uint32 = (uint32_t)file_buffer[0] + ((uint32_t)file_buffer[1] << 8U) + ((uint32_t)file_buffer[2] << 16U) + ((uint32_t)file_buffer[3] << 24U);
					image_window_data->image_height = (int16_t)temp_uint32;

					/* calculate the number of pixels to scroll the image vertically using the scroll bar position */
					if (client_height > image_window_data->image_height)
					{
						y_scroll_pos = 0;
					}
					else
					{
						y_scroll_pos = ((int16_t)image_window_data->y_scroll_pos * (image_window_data->image_height - client_height)) / UINT8_MAX;
					}

					/* calculate the number of pixels to scroll the image horizontally using the scroll bar position */
					if (client_width > image_window_data->image_width)
					{
						x_scroll_pos = 0;
					}
					else
					{
						x_scroll_pos = ((int16_t)image_window_data->x_scroll_pos * (image_window_data->image_width - client_width)) / UINT8_MAX;
					}

					row_size = (((uint32_t)image_window_data->image_width * 3U) + 3U) & 0xfffffffcU;
					app_file_read(file_buffer, 4U);
					if ((uint32_t)file_buffer[0] + ((uint32_t)file_buffer[1] << 8U) + ((uint32_t)file_buffer[2] << 16U) + ((uint32_t)file_buffer[3] << 24U) == 0x00180001U)
					{
						success = true;

						for (y_pos = 0; y_pos < image_window_data->image_height; y_pos++)
						{
							if (y_pos == client_height)
							{
								break;
							}

							row_start_address = file_data_offset + row_size * (((uint32_t)image_window_data->image_height - 1U) - (uint32_t)y_pos - (uint32_t)y_scroll_pos);
							row_start_address += (uint32_t)x_scroll_pos * 3U;
							(void)app_file_seek(row_start_address);

							if (client_width > image_window_data->image_width)
							{
								x_pixels_to_plot = image_window_data->image_width;
							}
							else
							{
								x_pixels_to_plot = client_width;
							}

							for (x_pos = 0; x_pos < x_pixels_to_plot; x_pos += BITMAP_TRASFER_BUFFER_SIZE)
							{
								if (x_pos + BITMAP_TRASFER_BUFFER_SIZE < x_pixels_to_plot)
								{
									app_file_read(bitmap_buffer, 48U);
									mw_gl_colour_bitmap(draw_info,
											x_pos,
											y_pos,
											BITMAP_TRASFER_BUFFER_SIZE,
											1,
											bitmap_buffer);
								}
								else
								{
									remaining = x_pixels_to_plot - x_pos;

									for (x = x_pos; x < x_pos + remaining; x++)
									{
										app_file_read(file_buffer, 3);
										pixel = ((uint32_t)file_buffer[0]) | ((uint32_t)file_buffer[1] << 8U) | ((uint32_t)file_buffer[2] << 16U);
										mw_gl_set_fg_colour(pixel);
										mw_gl_fg_pixel(draw_info, x, y_pos);
									}
								}
							}

/* simpler slower plot routine
							for (x_pos = 0; x_pos < x_pixels_to_plot; x_pos++)
							{
								app_file_read(file_buffer, 3);
								pixel = (file_buffer[0]) | (file_buffer[1] << 8) | (file_buffer[2] << 16);
								mw_gl_set_fg_colour(pixel);
								mw_gl_fg_pixel(draw_info, x_pos, y_pos);
							}
*/
						}

						/* paint remainder of window client area */

						/* bit to right */
						if (image_window_data->image_width < mw_get_window_client_rect(window_handle).width)
						{
							mw_gl_rectangle(draw_info,
									image_window_data->image_width,
									0,
									mw_get_window_client_rect(window_handle).width - image_window_data->image_width,
									image_window_data->image_height);
						}

						/* bit underneath */
						if (image_window_data->image_height < mw_get_window_client_rect(window_handle).height)
						{
							mw_gl_rectangle(draw_info,
									0,
									image_window_data->image_height,
									image_window_data->image_width,
									mw_get_window_client_rect(window_handle).height - image_window_data->image_height);
						}

						/* bit underneath and to right */
						if (image_window_data->image_height < mw_get_window_client_rect(window_handle).height)
						{
							if (image_window_data->image_height < mw_get_window_client_rect(window_handle).height)
							{
								mw_gl_rectangle(draw_info,
										image_window_data->image_width,
										image_window_data->image_height,
										mw_get_window_client_rect(window_handle).width - image_window_data->image_width,
										mw_get_window_client_rect(window_handle).height - image_window_data->image_height);

							}
						}

						/* set enabled state of window scroll bars and repaint them */
						mw_set_window_horiz_scroll_bar_enabled_state(image_window_data->image_window_handle,
								image_window_data->image_width > client_width);
						mw_set_window_vert_scroll_bar_enabled_state(image_window_data->image_window_handle,
								image_window_data->image_height > client_height);
						mw_paint_window_frame(image_window_data->image_window_handle,
								MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR | MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR);
					}
				}
			}
		}

		app_file_close();
	}

	if (!success)
	{
		/* get a warning dialog displayed by parent window, paint functions must not create new windows */
		mw_post_message(MW_USER_1_MESSAGE,
				window_handle,
				window_file_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				NULL,
				MW_WINDOW_MESSAGE);

		/* remove this window and let file window know */
		mw_remove_window(window_handle);
		mw_post_message(MW_WINDOW_EXTERNAL_WINDOW_REMOVED_MESSAGE,
				window_handle,
				window_file_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				NULL,
				MW_WINDOW_MESSAGE);
	}
}

void window_image_message_function(const mw_message_t *message)
{
	image_window_data_t *image_window_data;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	/* get this window instance data pointer and check for not null */
	image_window_data = (image_window_data_t *)mw_get_window_instance_data(message->recipient_handle);
	if (image_window_data == (void*)0)
	{
		MW_ASSERT((bool)false, "Couldn't find window instance data");
		return;
	}

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		image_window_data->x_scroll_pos = 0U;
		image_window_data->y_scroll_pos = 0U;
		break;

	case MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		image_window_data->y_scroll_pos = (uint8_t)message->message_data;
		break;

	case MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:
		image_window_data->x_scroll_pos = (uint8_t)message->message_data;
		break;

	case MW_TOUCH_UP_MESSAGE:
		mw_paint_window_client(message->recipient_handle);
		break;

	case MW_WINDOW_REMOVED_MESSAGE:
		mw_post_message(MW_WINDOW_EXTERNAL_WINDOW_REMOVED_MESSAGE,
				message->recipient_handle,
				window_file_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				NULL,
				MW_WINDOW_MESSAGE);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
