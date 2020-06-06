/* window_camera.c generated by MiniWin code generator. */

#include <stdlib.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_camera.h"
#include "camlib.h"

typedef struct
{
	bool captured;
	uint8_t line_buffer[160 * 3];
} window_window_camera_data_t;

static window_window_camera_data_t window_window_camera_data;

void window_window_camera_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	uint16_t *frame_data;

	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

	frame_data = camlib_get_frame();
	if (window_window_camera_data.captured && frame_data != NULL)
	{
		for (uint32_t y = 0U; y < 120U; y++)
		{
			uint32_t i = 0UL;
			for (uint32_t x = 0U; x < 160U; x++)
			{
				uint16_t pixel = (frame_data[(y * 320U + x) * 2U]);

				window_window_camera_data.line_buffer[i] = (pixel >> 11) << 3;
				i++;
				window_window_camera_data.line_buffer[i] = (pixel << 5) >> 8;
				i++;
				window_window_camera_data.line_buffer[i] = pixel << 3;
				i++;
			}

			mw_gl_colour_bitmap(draw_info,
					0,
					y,
					160U,
					1U,
					window_window_camera_data.line_buffer);
		}
	}
	else
	{
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_clear_pattern();
		mw_gl_rectangle(draw_info,
				0,
				0,
				mw_get_window_client_rect(window_handle).width,
				mw_get_window_client_rect(window_handle).height);
	}
}

void window_window_camera_message_function(const mw_message_t *message)
{
    MW_ASSERT(message != (void*)0, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_window_camera_data.captured = false;
	    mw_set_timer(mw_tick_counter + 5, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

    case MW_TIMER_MESSAGE:
	    camlib_capture();
	    window_window_camera_data.captured = true;
	    mw_paint_window_client(message->recipient_handle);
	    mw_set_timer(mw_tick_counter + 2, message->recipient_handle, MW_WINDOW_MESSAGE);
        break;

	default:
		/* keep MISRA happy */
		break;
	}
}
