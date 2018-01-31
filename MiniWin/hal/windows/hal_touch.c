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

#include <windows.h>
#include <stdio.h>
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

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static HANDLE hStdin;
static bool mouse_down = false;
static SHORT mx;
static SHORT my;

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
    DWORD fdwMode;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode = ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
    switch(mer.dwEventFlags)
    {
        case 0:
            if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                mouse_down = true;
            }
            else if (mer.dwButtonState == 0)
            {
            	mouse_down = false;
            }
            break;

        case MOUSE_MOVED:
        {
        	RECT r;
        	GetWindowRect( GetConsoleWindow(), &r );

        	POINT p;
        	GetCursorPos(&p);

        	mx = p.x - r.left - 4;
        	my = p.y - r.top - 23;

        	if (mx < 0)
        	{
        		mx = 0;
        	}

        	if (my < 0)
        	{
        		my = 0;
        	}

        	if (mx > 239)
        	{
        		mx = 239;
        	}

        	if (my > 319)
        	{
        		my = 319;
        	}
        }
        break;
    }
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
	if (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_UP)
	{
		return false;
	}

	*x = mx;
	*y = my;

	return true;
}

mw_hal_touch_state_t mw_hal_touch_get_state(void)
{
	DWORD lpcNumberOfEvents, cNumRead;
    INPUT_RECORD irInBuf[1];

	GetNumberOfConsoleInputEvents(hStdin, &lpcNumberOfEvents);

	if (lpcNumberOfEvents > 0)
	{
		ReadConsoleInput(hStdin,
		                irInBuf,
		                1,
		                &cNumRead);
	}

	switch(irInBuf[0].EventType)
	{
		case MOUSE_EVENT:
			MouseEventProc(irInBuf[0].Event.MouseEvent);
			break;
	};

	if (mouse_down)
	{
		return MW_HAL_TOUCH_STATE_DOWN;
	}

	return MW_HAL_TOUCH_STATE_UP;
}
