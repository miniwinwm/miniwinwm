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

#ifndef MINIWIN_USER_H
#define MINIWIN_USER_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/*************************
*** EXTERNAL VARIABLES ***
*************************/

extern mw_handle_t window_file_handle;
extern mw_handle_t window_file_tree_handle;
extern mw_handle_t button_open_handle;
extern mw_handle_t button_set_clock_handle;
extern mw_handle_t button_create_handle;
extern mw_handle_t label_time_handle;
extern mw_handle_t label_date_handle;
extern mw_handle_t tree_handle;
extern mw_handle_t label_path_handle;
extern mw_handle_t scroll_bar_vert_handle;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Add a file to a folder
 *
 * @param parent_folder The folder to add the file to
 * @param name The file's name excluding path
 */
void tree_container_add_file_to_folder(mw_handle_t parent_folder, char *filename);

#ifdef __cplusplus
}
#endif

#endif
