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
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "miniwin.h"
#include "app.h"

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

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static FILE *file_handle;		/**< File to access */

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static VOID MouseEventProc(LPARAM lp);
static long __stdcall WindowProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);

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
static long __stdcall WindowProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
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

    return 0;
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
    RegisterClassEx(&wndclass);

    RECT r = {WINDOW_START_LOCATION_X,
    		WINDOW_START_LOCATION_Y,
			WINDOW_START_LOCATION_X + MW_ROOT_WIDTH,
			WINDOW_START_LOCATION_Y + MW_ROOT_HEIGHT};
    AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0);

	hwnd = CreateWindow(miniwin_class, "MiniWin Sim",
			   WS_OVERLAPPEDWINDOW | WS_CAPTION, r.left, r.top,
			   r.right - r.left, r.bottom - r.top, 0, 0, GetModuleHandle(0), 0);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
}

char *app_get_root_folder_path(void)
{
	return "c:/";
}

void app_main_loop_process(void)
{
    MSG msg;

    while(PeekMessageA(&msg, hwnd, 0, 0, PM_NOREMOVE))
    {
		GetMessage(&msg, 0, 0, 0);
		DispatchMessage(&msg) ;
    }
}

bool app_file_open(char *path_and_filename)
{
	bool result = false;

	file_handle = fopen(path_and_filename, "rb");

	if (file_handle != NULL)
	{
		result = true;
	}

	return result;
}

bool app_file_create(char *path_and_filename)
{
	bool result = false;

	file_handle = fopen(path_and_filename, "w");

	if (file_handle != NULL)
	{
		result = true;
	}

	return result;
}

uint32_t app_file_size(void)
{
	uint32_t size;

	fseek(file_handle, 0L, SEEK_END);
	size = (uint32_t)ftell(file_handle);
	fseek(file_handle, 0L, SEEK_SET);

	return size;
}

uint8_t app_file_getc(void)
{
	return (uint8_t)fgetc(file_handle);
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
	fread(buffer, 1, count, file_handle);
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
	fwrite(buffer, 1, count, file_handle);
}

uint32_t app_file_seek(uint32_t position)
{
	return (uint32_t)fseek(file_handle, position, SEEK_SET);
}

void app_file_close(void)
{
	fclose(file_handle);
}

uint8_t find_folder_entries(char* path,
		mw_ui_list_box_entry *list_box_settings_entries,
		bool folders_only,
		uint8_t max_entries,
		const uint8_t *file_entry_icon,
		const uint8_t *folder_entry_icon)
{
	TCHAR szDir[MAX_FOLDER_AND_FILENAME_LENGTH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	uint8_t i;

	i = 0;
	mw_util_safe_strcpy(szDir, MAX_FOLDER_AND_FILENAME_LENGTH - 2, path);
	strcat(szDir, TEXT("\\*"));

	/* Find the first file in the folder */
	hFind = FindFirstFile(szDir, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	do
	{
    	/* Ignore if it's a hidden or system entry*/
    	if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) || (ffd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
    	{
    		continue;
    	}

    	/* don't add parent or current folder link for compatibility with FatFS */
    	if (strcmp(ffd.cFileName, "..") == 0 || strcmp(ffd.cFileName, ".") == 0)
    	{
    		continue;
    	}

    	/* ignore if not a folder and we want folders only */
    	if (folders_only && !(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    	{
    		continue;
    	}

        mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1, ffd.cFileName);

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
        	/* It is a folder */
        	list_box_settings_entries[i].icon = folder_entry_icon;
		}
		else
		{
        	/* It is a file. */
            list_box_settings_entries[i].icon = file_entry_icon;
		}

        i++;
        if (i == max_entries)
        {
        	break;
        }
	}
	while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);

	return i;
}

struct tm app_get_time_date(void)
{
	struct tm tm;
	time_t t;

	time(&t);
	memcpy(&tm, localtime(&t), sizeof(struct tm));
	tm.tm_year += 1900;
	return tm;
}

void app_set_time_date(struct tm tm)
{
	/* do nothing for windows build */
}
