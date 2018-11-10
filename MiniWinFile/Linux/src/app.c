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
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
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

Display *display;
Window frame_window;
GC graphical_context;

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
		260,
		320,
		5,
		depth,
		InputOutput,
		visual,
		CWBackPixel,
		&frame_attributes);

	graphical_context = XCreateGC( display, frame_window, 0, 0 );

	XMapWindow(display, frame_window);
	XFlush(display);
}

char *app_get_root_folder_path(void)
{
	return getenv("HOME");
}

void app_main_loop_process(void)
{
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
	DIR *directory;
	struct dirent *directory_entry;
	uint8_t i;

	i = 0;
	directory = opendir(path);
	if (directory)
	{
		while ((directory_entry = readdir(directory)) != NULL)
		{
			if (directory_entry->d_type == DT_REG)
			{
				/* it is a file */
	            list_box_settings_entries[i].icon = file_entry_icon;
	            mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1, directory_entry->d_name);
				i++;
			}
			else if (directory_entry->d_type == DT_DIR)
			{
				/* it is a folder */
				if (folders_only)
				{
					continue;
				}
				if (strcmp(directory_entry->d_name, ".") == 0)
				{
					continue;
				}
				if (strcmp(directory_entry->d_name, "..") == 0)
				{
					continue;
				}
	        	list_box_settings_entries[i].icon = folder_entry_icon;
	            mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1, directory_entry->d_name);
				i++;
			}
			else
			{
				continue;
			}

	        if (i == max_entries)
	        {
	        	break;
	        }
		}
		closedir(directory);
	}

	return i;
}

struct tm app_get_time_date(void)
{
	struct tm tm;
	time_t t;

	time(&t);
	memcpy(&tm, localtime(&t), sizeof(struct tm));
	tm.tm_year += 1900;
	tm.tm_mon++;

	return tm;
}

void app_set_time_date(struct tm tm)
{
	/* do nothing for windows build */
}