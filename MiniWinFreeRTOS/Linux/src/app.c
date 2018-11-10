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

/****************
*** CONSTANTS ***
****************/

#define CAPS_LOCK 	2
#define NUM_LOCK 	16
#define SCROLL_LOCK 1

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

Display *display;
Window frame_window;
GC graphical_context;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern XEvent event;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void setLeds(int32_t leds);

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

	display = XOpenDisplay(NULL);
	visual = DefaultVisual(display, 0);
	depth  = DefaultDepth(display, 0);

	frame_attributes.background_pixel = XBlackPixel(display, 0);

	/* create the application window */
	frame_window = XCreateWindow(display, 
		XRootWindow(display, 0),
		0, 
		0, 
		240,
		320,
		5, 
		depth,
		InputOutput, 
		visual, 
		CWBackPixel,
		&frame_attributes);

	graphical_context = XCreateGC( display, frame_window, 0, 0 );

	XSelectInput(display, frame_window, KeyPressMask);
	XMapWindow(display, frame_window);
	XFlush(display);
}

/**
 * Set the computer's keyboard led state
 *
 * @param leds Binary or of the leds that are to be set on using the #defines above or 0 for off
 */
static void setLeds(int32_t leds)
{
    XKeyboardControl values;

    values.led_mode = leds & SCROLL_LOCK ? LedModeOn : LedModeOff;
    values.led = 3;
    XChangeKeyboardControl(display, KBLedMode, &values);
    XkbLockModifiers(display, XkbUseCoreKbd, CAPS_LOCK | NUM_LOCK, leds & (CAPS_LOCK | NUM_LOCK));
    XFlush(display);
}

void app_main_loop_process(void)
{
	/* toggle the scroll lock led state */
	static bool toggle = false;

	if (toggle)
	{
		setLeds(SCROLL_LOCK);
	}
	else
	{
		setLeds(0);
	}

	toggle = !toggle;
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
