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

#include "miniwin.h"
#include "miniwin_user.h"
#include "window_tabs.h"

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
	char dummy;		/* some compilers treat empty structs as errors */
} window_tabs_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_util_rect_t auto_tab_rect = {0, MW_UI_TABS_LARGE_HEIGHT, 0, 0};
static const mw_util_rect_t fixed_tab_rect = {20, 45, 120, 70};

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_tabs_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
    MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

    /* fill window's client area */
    mw_gl_set_fill(MW_GL_FILL);
    mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
    mw_gl_set_border(MW_GL_BORDER_OFF);
    mw_gl_clear_pattern();
    mw_gl_rectangle(draw_info,
        0, 0,
        mw_get_window_client_rect(window_handle).width,
        mw_get_window_client_rect(window_handle).height);

    /* draw box under fixed tabs control */
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	if (mw_ui_tabs_get_selection(tabs_auto_handle) == 1U)
	{
		mw_gl_vline(draw_info, 20, 30, 90);
		mw_gl_hline(draw_info, 20, 139, 90);
		mw_gl_vline(draw_info, 139, 30, 90);
	}
}

void window_tabs_message_function(const mw_message_t *message)
{
	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
    case MW_TAB_SELECTED_MESSAGE:
    	if (message->sender_handle == tabs_auto_handle)
    	{
			if (message->message_data == 0U)
			{
				mw_set_control_visible(label_2_handle, true);
				mw_set_control_visible(label_3_handle, false);
				mw_set_control_visible(label_4_handle, false);
				mw_set_control_visible(label_5_handle, false);
				mw_set_control_visible(label_6_handle, false);
				mw_set_control_visible(tabs_fixed_handle, false);
			}
			else if (message->message_data == 1U)
			{
				mw_set_control_visible(label_2_handle, false);
				mw_set_control_visible(label_3_handle, false);

				if (mw_ui_tabs_get_selection(tabs_fixed_handle) == 0U)
				{
					mw_set_control_visible(label_4_handle, true);
				}
				else
				{
					mw_set_control_visible(label_4_handle, false);
				}

				if (mw_ui_tabs_get_selection(tabs_fixed_handle) == 1U)
				{
					mw_set_control_visible(label_5_handle, true);
				}
				else
				{
					mw_set_control_visible(label_5_handle, false);
				}

				if (mw_ui_tabs_get_selection(tabs_fixed_handle) == 2U)
				{
					mw_set_control_visible(label_6_handle, true);
				}
				else
				{
					mw_set_control_visible(label_6_handle, false);
				}

				mw_set_control_visible(tabs_fixed_handle, true);
			}
			else
			{
				mw_set_control_visible(label_2_handle, false);
				mw_set_control_visible(label_3_handle, true);
				mw_set_control_visible(label_4_handle, false);
				mw_set_control_visible(label_5_handle, false);
				mw_set_control_visible(label_6_handle, false);
				mw_set_control_visible(tabs_fixed_handle, false);
			}

	    	//mw_paint_window_client(message->recipient_handle);
			auto_tab_rect.width = mw_get_window_client_rect(message->recipient_handle).width;
			auto_tab_rect.height = mw_get_window_client_rect(message->recipient_handle).height - MW_UI_TABS_LARGE_HEIGHT;

			mw_paint_window_client_rect(message->recipient_handle, &auto_tab_rect);
    	}
    	else if (message->sender_handle == tabs_fixed_handle)
    	{
			if (message->message_data == 0U)
			{
				mw_set_control_visible(label_4_handle, true);
				mw_set_control_visible(label_5_handle, false);
				mw_set_control_visible(label_6_handle, false);
			}
			else if (message->message_data == 1U)
			{
				mw_set_control_visible(label_4_handle, false);
				mw_set_control_visible(label_5_handle, true);
				mw_set_control_visible(label_6_handle, false);
			}
			else
			{
				mw_set_control_visible(label_4_handle, false);
				mw_set_control_visible(label_5_handle, false);
				mw_set_control_visible(label_6_handle, true);
			}

			/* only repaint the fixed tab control and the box below it that it controls */
			mw_paint_window_client_rect(message->recipient_handle, &fixed_tab_rect);
    	}
    	else
    	{
    		/* keep MISRA happy */
    	}
    	break;

	default:
		/* keep MISRA happy */
		break;
	}
}
