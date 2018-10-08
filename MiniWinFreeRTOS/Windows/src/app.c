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
#include <conio.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "app.h"

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

static uint32_t desktop_width;
static uint32_t desktop_height;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**
 * Get the screen maximum coordinates
 *
 * @param Pointer to placeholder for screen width
 * @param Pointer to placeholder for screen height
 */
static void GetDesktopResolution(uint32_t *width, uint32_t *height);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void GetDesktopResolution(uint32_t *width, uint32_t *height)
{
   RECT desktop;

   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   *width = desktop.right;
   *height = desktop.bottom;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
	/* get screen maximum coordinates used for mouse simulation of rotating board */
	GetDesktopResolution(&desktop_width, &desktop_height);
}

void app_main_loop_process(void)
{
	/* draw a flashing led */
	static bool toggle = false;
	HWND hwnd;
	uint16_t x;
	uint16_t y;

	hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	for (x = 245; x < 255; x++)
	{
		for (y = 10; y < 20; y++)
		{
			if (toggle)
			{
				SetPixel(hdc, x, y, RGB(0xff, 0, 0));
			}
			else
			{
				SetPixel(hdc, x, y, RGB(0, 0, 0));
			}
		}
	}

	toggle = !toggle;

	ReleaseDC(hwnd, hdc);
}

float *app_get_gyro_readings(void)
{
	static float cumulative_gyro_readings[3] = {0.0f, 0.0f, 0.0f};
	POINT p;

	GetCursorPos(&p);

	if (_kbhit())
	{
		/* check for an arrow key */
		if (getch() == 224)
		{
			switch(getch())
			{
			        case 77:
			            /* code for arrow up */
			        	cumulative_gyro_readings[GYRO_READING_Z] += 5.0f;
			            break;

			        case 75:
			        	cumulative_gyro_readings[GYRO_READING_Z] -= 5.0f;
			            /* code for arrow down */
			            break;
			}
		}
	}

	cumulative_gyro_readings[GYRO_READING_Y] = (float)p.x / (float)desktop_width * 360.0f;
	cumulative_gyro_readings[GYRO_READING_X] = (float)p.y / (float)desktop_height * 360.0f;

	return cumulative_gyro_readings;
}
