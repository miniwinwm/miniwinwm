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
#include <fcntl.h>
#include <time.h>
#include "miniwin.h"
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

/**********************
*** LOCAL VARIABLES ***
**********************/

static int file_descriptor;
static char root_folder[MAX_FOLDER_AND_FILENAME_LENGTH];

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
		(unsigned int)MW_ROOT_WIDTH,
		(unsigned int)MW_ROOT_HEIGHT,
		5, 
		depth,
		InputOutput, 
		visual, 
		CWBackPixel,
		&frame_attributes);

	XStoreName(display, frame_window, "MiniWin Sim");

	XSelectInput(display, frame_window, ExposureMask | StructureNotifyMask);

	graphical_context = XCreateGC(display, frame_window, 0U, NULL);

	XMapWindow(display, frame_window);
	(void)XFlush(display);
}

char *app_get_root_folder_path(void)
{
	return (root_folder);
}

void app_main_loop_process(void)
{
}

bool app_file_open(char *path_and_filename)
{
	file_descriptor = open(path_and_filename, O_RDONLY);
	if (file_descriptor == -1)
	{
		return (false);
	}
	return (true);
}

bool app_file_create(char *path_and_filename)
{
	file_descriptor = creat(path_and_filename, S_IWUSR | S_IRUSR);
	if (file_descriptor == -1)
	{
		return (false);
	}
	return (true);
}

uint32_t app_file_size(void)
{
	off_t size;

	size = lseek(file_descriptor, 0, SEEK_END);
	lseek(file_descriptor, 0, SEEK_SET);

	return ((uint32_t)size);
}

uint8_t app_file_getc(void)
{
	uint8_t byte;

	app_file_read(&byte, 1U);

	return (byte);
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
	(void)read(file_descriptor, (char *)buffer, (unsigned int)count);
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
	(void)write(file_descriptor, (char *)buffer, (unsigned int)count);
}

uint32_t app_file_seek(uint32_t position)
{
	if ((off_t)-1 == lseek(file_descriptor, (off_t)position, SEEK_SET))
	{
		return (1U);
	}
	return (0U);
}

void app_file_close(void)
{
	(void)close(file_descriptor);
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
				if (folders_only)
				{
					continue;
				}

	            list_box_settings_entries[i].icon = file_entry_icon;
	            (void)mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1, directory_entry->d_name);
				i++;
			}
			else if (directory_entry->d_type == DT_DIR)
			{
				/* it is a folder */
				if (strcmp(directory_entry->d_name, ".") == 0)
				{
					continue;
				}
				if (strcmp(directory_entry->d_name, "..") == 0)
				{
					continue;
				}
	        	list_box_settings_entries[i].icon = folder_entry_icon;
	        	(void)mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILENAME_LENGTH + 1, directory_entry->d_name);
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
		(void)closedir(directory);
	}

	return (i);
}

struct tm app_get_time_date(void)
{
	struct tm tm;
	time_t t;

	(void)time(&t);
	(void)memcpy(&tm, localtime(&t), sizeof(struct tm));
	tm.tm_year += 1900;
	tm.tm_mon++;

	return (tm);
}

void app_set_time_date(struct tm tm)
{
	/* do nothing for linux build */
}
