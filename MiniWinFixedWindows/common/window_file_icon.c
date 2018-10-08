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
#include "miniwin.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef struct
{
	bool touch_down;

} window_file_icon_data_t;


/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint8_t file_bitmap[];
extern const uint8_t file_down_bitmap[];
extern volatile uint32_t mw_tick_counter;
extern uint8_t window_file_id;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_file_icon_data_t window_file_icon_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_file_icon_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info, "Null pointer parameter");

	if (window_file_icon_data.touch_down)
	{
		mw_gl_colour_bitmap(draw_info,
			0,
			0,
			104,
			104,
			file_down_bitmap);
	}
	else
	{
		mw_gl_colour_bitmap(draw_info,
			0,
			0,
			104,
			104,
			file_bitmap);
	}
}

void window_file_icon_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer parameter");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_file_icon_data.touch_down = false;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		window_file_icon_data.touch_down = true;
		mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_id, MW_WINDOW_MESSAGE);
		mw_paint_window_client(message->recipient_id);
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		if (window_file_icon_data.touch_down)
		{
			/* repaint the window up for a moment before switching to the new window, this is not necessary but makes the ui feel better */
			window_file_icon_data.touch_down = false;
			mw_paint_window_client(message->recipient_id);
			mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME * 2, message->recipient_id, MW_WINDOW_MESSAGE);
		}
		else
		{
			/* set window window_settings_id visible */
			mw_set_window_visible(window_file_id, true);

			/* a window has changed visibility so repaint it */
			mw_paint_window_frame(window_file_id, MW_WINDOW_FRAME_COMPONENT_ALL);
			mw_paint_window_client(window_file_id);
		}
		break;

	default:
		break;
	}
}
