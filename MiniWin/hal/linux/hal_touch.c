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

#include <X11/Xlib.h>
#include "hal/hal_touch.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

XEvent event;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern Display *display;
extern Window frame_window;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
    int win_x;
	int win_y;
	int root_x;
	int root_y;
    unsigned int mask = 0;
    Window child_win;
	Window root_win;

	if (XCheckMaskEvent(display, KeyPressMask, &event))
	{
    	XNextEvent(display, &event);
    }
    XQueryPointer(display, frame_window, &child_win, &root_win, &root_x, &root_y, &win_x, &win_y, &mask);

    if (mask == 256)
    {
    	*x = win_x;
    	*y = win_y;

    	return true;
    }

    return false;
}

mw_hal_touch_state_t mw_hal_touch_get_state(void)
{
    int win_x;
	int win_y;
	int root_x;
	int root_y;
    unsigned int mask = 0;
    Window child_win;
	Window root_win;

    XQueryPointer(display, frame_window, &child_win, &root_win, &root_x, &root_y, &win_x, &win_y, &mask);

    if (mask == 256)
    {
    	return MW_HAL_TOUCH_STATE_DOWN;
    }

	return MW_HAL_TOUCH_STATE_UP;
}
