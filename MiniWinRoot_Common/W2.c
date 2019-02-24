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
#include "W2.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef struct
{    /* Add your data members here */
} window_W2_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_W2_data_t window_W2_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_W2_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
    MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

    /* Fill window's client area with solid white */
    mw_gl_set_fill(MW_GL_FILL);
    mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
    mw_gl_set_border(MW_GL_BORDER_OFF);
    mw_gl_clear_pattern();
    mw_gl_rectangle(draw_info,
        0, 0,
        mw_get_window_client_rect(window_handle).width,
        mw_get_window_client_rect(window_handle).height);

    /* Add you window painting code here */
}

void window_W2_message_function(const mw_message_t *message)
{
    MW_ASSERT(message != (void*)0, "Null pointer parameter");

    /* Next line stops compiler warnings as variable is currently unused */
    (void)window_W2_data;

    switch (message->message_id)
    {
    case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
        if (message->sender_handle == list_box_LB1_handle)
        {
        	if (message->message_data == 0)
        	{
        		 mw_create_window_dialog_colour_chooser(10,
        				10,
        				"Root colour",
						desktop_colour,
        				false,
        				message->recipient_handle);
        	}
        	mw_set_window_visible(window_W2_handle, false);

        	/* this window will lose focus and get a MW_WINDOW_LOST_FOCUS_MESSAGE which will perform the paint all */
        }
        break;

    case MW_DIALOG_COLOUR_CHOOSER_OK_MESSAGE:
    	desktop_colour = message->message_data;
		mw_paint_window_client(MW_ROOT_WINDOW_HANDLE);
    	break;

	case MW_WINDOW_LOST_FOCUS_MESSAGE:
		mw_set_window_visible(window_W2_handle, false);
		mw_paint_all();
		break;

    default:
		/* keep MISRA happy */
    	break;
    }
}
