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

extern const uint8_t mw_bitmaps_file_icon_small[];
extern const uint8_t mw_bitmaps_folder_icon_small[];

/**********************
*** LOCAL VARIABLES ***
**********************/

static FILE *in_file;

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
}

char *app_get_root_folder_path(void)
{
	return "c:/";
}

void app_main_loop_process(void)
{
}

bool app_file_open(char *path_and_file_name)
{
	bool result = false;

	in_file = fopen(path_and_file_name, "rb");

	if (in_file != NULL)
	{
		result = true;
	}

	return result;
}

uint32_t app_file_size(void)
{
	uint32_t size;

	fseek(in_file, 0L, SEEK_END);
	size = (uint32_t)ftell(in_file);
	fseek(in_file, 0L, SEEK_SET);

	return size;
}

uint8_t app_file_getc(void)
{
	return (uint8_t)fgetc(in_file);
}

void app_file_fread(uint8_t *buffer, uint32_t count)
{
	fread(buffer, 1, count, in_file);
}

uint32_t app_file_seek(uint32_t position)
{
	return (uint32_t)fseek(in_file, position, SEEK_SET);
}

void app_file_close(void)
{
	fclose(in_file);
}

uint8_t find_directory_entries(char* path,
		mw_ui_list_box_entry *list_box_settings_entries,
		uint8_t max_entries)
{
	TCHAR szDir[MAX_FOLDER_AND_FILE_NAME_LENGTH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	uint8_t i;

	i = 0;
	mw_util_safe_strcpy(szDir, MAX_FOLDER_AND_FILE_NAME_LENGTH - 2, path);
	strcat(szDir, TEXT("\\*"));

	/* Find the first file in the directory */
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

        mw_util_safe_strcpy(list_box_settings_entries[i].label, MAX_FILE_NAME_LENGTH + 1, ffd.cFileName);

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
        	/* It is a directory */
        	list_box_settings_entries[i].icon = mw_bitmaps_folder_icon_small;
		}
		else
		{
        	/* It is a file. */
            list_box_settings_entries[i].icon = mw_bitmaps_file_icon_small;
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
