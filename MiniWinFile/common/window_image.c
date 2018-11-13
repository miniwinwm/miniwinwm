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
#include "miniwin.h"
#include "dialogs/dialog_common.h"
#include "gl/gl.h"
#include "app.h"
#include "window_image.h"

/****************
*** CONSTANTS ***
****************/

#define BITMAP_TRASFER_BUFFER_SIZE		16
#define BASIC_BMP_FILE_HEADER_SIZE		0x36

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern mw_handle_t window_file_handle;

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
	uint16_t client_width;
	uint16_t client_height;
	bool success;
	uint8_t file_buffer[4];
	uint32_t image_width;
	uint32_t image_height;
	uint32_t file_data_offset;
	uint16_t x_pos;
	uint16_t y_pos;
	uint32_t row_size;
	uint32_t row_start_address;
	uint32_t pixel;
	image_window_data_t *image_window_data;

	MW_ASSERT(draw_info, "Null pointer parameter");

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREY12);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	/* get this window instance data pointer and check for not null */
	image_window_data = (image_window_data_t *)mw_get_window_instance_data(window_handle);
	if (image_window_data == NULL)
	{
		MW_ASSERT(false, "Couldn't find window instance data");
		return;
	}

	success = false;
	client_width = mw_get_window_client_rect(window_handle).width;
	client_height = mw_get_window_client_rect(window_handle).height;
	if (app_file_open(image_window_data->path_and_filename_image))
	{
		file_size = app_file_size();
		if (file_size >= BASIC_BMP_FILE_HEADER_SIZE)
		{
			if (app_file_getc() == 'B' && app_file_getc() == 'M')
			{
				app_file_seek(10);
				app_file_read(file_buffer, 4);
				file_data_offset = file_buffer[0] + (file_buffer[1] << 8) + (file_buffer[2] << 16) + (file_buffer[3] << 24);
				app_file_read(file_buffer, 4);
				if (file_buffer[0] + (file_buffer[1] << 8) + (file_buffer[2] << 16) + (file_buffer[3] << 24) == 40)
				{
					/* Windows BITMAPINFOHEADER */
					app_file_read(file_buffer, 4);
					image_width = file_buffer[0] + (file_buffer[1] << 8) + (file_buffer[2] << 16) + (file_buffer[3] << 24);
					app_file_read(file_buffer, 4);
					image_height = file_buffer[0] + (file_buffer[1] << 8) + (file_buffer[2] << 16) + (file_buffer[3] << 24);
					row_size = ((image_width * 3) + 3) & 0xfffffffc;

					app_file_read(file_buffer, 4);
					if (file_buffer[0] + (file_buffer[1] << 8) + (file_buffer[2] << 16) + (file_buffer[3] << 24) == 0x00180001)
					{
						success = true;
						for (y_pos = 0; y_pos < image_height; y_pos++)
						{
							if (y_pos == client_height)
							{
								break;
							}

							row_start_address = file_data_offset + row_size * ((image_height - 1) - y_pos);
							app_file_seek(row_start_address);

							for (x_pos = 0; x_pos < image_width && x_pos < client_width; x_pos += BITMAP_TRASFER_BUFFER_SIZE)
							{
								if (x_pos + BITMAP_TRASFER_BUFFER_SIZE < image_width && x_pos + 16 < client_width)
								{
									app_file_read(bitmap_buffer, 48);
									mw_gl_colour_bitmap(draw_info,
											x_pos,
											y_pos,
											16,
											1,
											bitmap_buffer);
								}
								else
								{
									uint16_t remainder;
									if (image_width < client_width)
									{
										remainder = image_width - x_pos;
									}
									else
									{
										remainder = client_width - x_pos;
									}

									for (uint16_t x = x_pos; x < x_pos + remainder; x++)
									{
										app_file_read(file_buffer, 3);
										pixel = (file_buffer[0]) | (file_buffer[1] << 8) | (file_buffer[2] << 16);
										mw_gl_set_fg_colour(pixel);
										mw_gl_fg_pixel(draw_info, x, y_pos);
									}
								}
							}
						}
					}
				}
			}
		}

		app_file_close();
	}

	if (!success)
	{
		/* get a warning dialog displayed */
		mw_post_message(MW_USER_1_MESSAGE,
				window_handle,
				window_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);

		/* close this window to prevent continuous repaints and let file window know */
		mw_remove_window(window_handle);
		mw_post_message(MW_WINDOW_EXTERNAL_WINDOW_REMOVED,
				window_handle,
				window_file_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);
	}
}

void window_image_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_REMOVED_MESSAGE:
		mw_post_message(MW_WINDOW_EXTERNAL_WINDOW_REMOVED,
				message->recipient_handle,
				window_file_handle,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);
		break;

	case MW_USER_1_MESSAGE:
		mw_create_window_dialog_one_button(20,
				50,
				150,
				"Warning",
				"Bad file format.",
				"OK",
				false,
				0);
		break;

	default:
		break;
	}
}
