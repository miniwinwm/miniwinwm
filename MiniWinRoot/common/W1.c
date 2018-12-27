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

#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

typedef struct
{    /* Add your data members here */
} window_W1_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern mw_handle_t button_B1_handle;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_W1_data_t window_W1_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_W1_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
    MW_ASSERT(draw_info, "Null pointer parameter");

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

void window_W1_message_function(const mw_message_t *message)
{
    MW_ASSERT(message, "Null pointer parameter");

    /* Next line stops compiler warnings as variable is currently unused */
    (void)window_W1_data;

    switch (message->message_id)
    {
    case MW_WINDOW_CREATED_MESSAGE:
        /* Add any window initiaslisation code here */
        break;

    case MW_BUTTON_PRESSED_MESSAGE:
        if (message->sender_handle == button_B1_handle)
        {
            /* Add your handler code for this control here */
        }
        break;

    default:
        break;
    }
}
