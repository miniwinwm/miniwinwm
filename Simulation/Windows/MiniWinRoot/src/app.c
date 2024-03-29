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

#include <windows.h>
#include <stdbool.h>
#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

#define WINDOW_START_LOCATION_X		100			/**< Position of left edge of window when it shows */
#define WINDOW_START_LOCATION_Y		100			/**< Position of top edge of window when it shows */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

HWND hwnd;
bool mouse_down = false;
SHORT mx;
SHORT my;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static VOID MouseEventProc(LPARAM lp);
static LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wp, LPARAM lp);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Retrieve point coordinates from long param received by a Windows touch down or touch drag message
 * 
 * @param lp The long parameter that contains the coordinates in two shorts
 */
static VOID MouseEventProc(LPARAM lp)
{
    POINTS mouse_point;

    mouse_point = MAKEPOINTS(lp);
	mx = mouse_point.x;
	my = mouse_point.y;

	if (mx < 0)
	{
		mx = 0;
	}

	if (my < 0)
	{
		my = 0;
	}

	if (mx > MW_ROOT_WIDTH - 1)
	{
		mx = MW_ROOT_WIDTH - 1;
	}

	if (my > MW_ROOT_HEIGHT - 1)
	{
		my = MW_ROOT_HEIGHT - 1;
	}
}

/**
 * Windows message handling function
 * 
 * @param window Handle of the window receiving the message
 * @param msg The message to process
 * @param wp First message parameter
 * @param lp Second message parameter
 */
static LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
	case WM_DESTROY:
		PostQuitMessage(0);
		exit(0);

	case WM_LBUTTONDOWN:
		mouse_down = true;
		MouseEventProc(lp);
		break;

	case WM_MOUSEMOVE:
		MouseEventProc(lp);
		break;

	case WM_LBUTTONUP:
		mouse_down = false;
		break;

	case WM_SETFOCUS:
		mw_paint_all();
		break;

	default:
		return DefWindowProc(window, msg, wp, lp);
    }

    return (0);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
    const char* const miniwin_class = "miniwin_class";
    WNDCLASSEX wndclass = {sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProc,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), (HBRUSH)COLOR_WINDOW+1,
                            0, miniwin_class, LoadIcon(0,IDI_APPLICATION)};
    (void)RegisterClassEx(&wndclass);

    RECT r = {WINDOW_START_LOCATION_X,
    		WINDOW_START_LOCATION_Y,
			WINDOW_START_LOCATION_X + MW_ROOT_WIDTH,
			WINDOW_START_LOCATION_Y + MW_ROOT_HEIGHT};
    (void)AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0);

	hwnd = CreateWindow(miniwin_class, "MiniWin Sim",
			   WS_OVERLAPPEDWINDOW | WS_CAPTION, r.left, r.top,
			   r.right - r.left, r.bottom - r.top, 0, 0, GetModuleHandle(0), 0);

	(void)ShowWindow(hwnd, SW_SHOWDEFAULT);
}

void app_main_loop_process(void)
{
    MSG msg;

    while (PeekMessageA(&msg, hwnd, 0, 0, PM_NOREMOVE))
    {
    	(void)GetMessage(&msg, 0, 0, 0);
		(void)DispatchMessage(&msg) ;
    }
}
