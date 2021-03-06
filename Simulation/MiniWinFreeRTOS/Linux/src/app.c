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
#include <X11/XKBlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "app.h"
#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

Display *display;
Window frame_window;
GC graphical_context;
extern XEvent event;
Atom wm_delete_window_message;

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

void app_init(void)
{
	static	Visual *visual;
	static int depth;
	static XSetWindowAttributes frame_attributes;

	XInitThreads();

	display = XOpenDisplay(NULL);
	visual = DefaultVisual(display, 0);
	depth  = DefaultDepth(display, 0);

	frame_attributes.background_pixel = XBlackPixel(display, 0);

	/* create the application window */
	frame_window = XCreateWindow(display, 
		XRootWindow(display, 0),
		0, 
		0, 
		(unsigned int)MW_ROOT_WIDTH + 20,
		(unsigned int)MW_ROOT_HEIGHT,
		5, 
		depth,
		InputOutput, 
		visual, 
		CWBackPixel,
		&frame_attributes);

	/* register interest in delete window message */
	wm_delete_window_message = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, frame_window, &wm_delete_window_message, 1);

	XStoreName(display, frame_window, "MiniWin Sim");

	XSelectInput(display, frame_window, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask);

	graphical_context = XCreateGC(display, frame_window, 0U, NULL);

	XMapWindow(display, frame_window);
	(void)XFlush(display);
}

void app_main_loop_process(void)
{
	/* toggle the scroll lock led state */
	static bool toggle = false;

	if (mw_is_init_complete())
	{
		if (toggle)
		{
			mw_hal_lcd_filled_rectangle(MW_ROOT_WIDTH + 5, 10, 10, 10, MW_HAL_LCD_YELLOW);
		}
		else
		{
			mw_hal_lcd_filled_rectangle(MW_ROOT_WIDTH + 5, 10, 10, 10, MW_HAL_LCD_BLACK);
		}

		toggle = !toggle;
	}
}

float *app_get_gyro_readings(void)
{
	static float cumulative_gyro_readings[3] = {0.0f, 0.0f, 0.0f};

    /* keyboard events */
    if (event.type == KeyPress || event.type == KeyRelease)
    {
    	if (event.xkey.keycode == 0x72)
    	{
    		/* up */
        	cumulative_gyro_readings[GYRO_READING_Z] += 2.0f;
    	}
    	else if (event.xkey.keycode == 0x71)
    	{
    		/* down */
        	cumulative_gyro_readings[GYRO_READING_Z] -= 2.0f;
    	}
    	else if (event.xkey.keycode == 0x6f)
    	{
    		/* roll left */
        	cumulative_gyro_readings[GYRO_READING_X] += 2.0f;
    	}
    	else if (event.xkey.keycode == 0x74)
    	{
    		/* roll right */
        	cumulative_gyro_readings[GYRO_READING_X] -= 2.0f;
    	}
    	else if (event.xkey.keycode == 0x2e)
    	{
    		/* rotate left */
        	cumulative_gyro_readings[GYRO_READING_Y] += 2.0f;
    	}
    	else if (event.xkey.keycode == 0x1b)
    	{
    		/* rotate right */
        	cumulative_gyro_readings[GYRO_READING_Y] -= 2.0f;
    	}

    	event.type = 0;
    }

	return cumulative_gyro_readings;
}
