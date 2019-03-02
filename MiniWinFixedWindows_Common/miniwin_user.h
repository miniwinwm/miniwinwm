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

#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/*************************
*** EXTERNAL VARIABLES ***
*************************/

extern mw_handle_t window_help_icon_handle;
extern mw_handle_t window_file_icon_handle;
extern mw_handle_t window_file_handle;
extern mw_handle_t window_date_icon_handle;
extern mw_handle_t window_time_icon_handle;
extern mw_handle_t window_settings_icon_handle;
extern mw_handle_t window_settings_handle;
extern mw_handle_t window_temp_icon_handle;
extern mw_handle_t window_temp_handle;
extern mw_handle_t button_temp_back_handle;
extern mw_handle_t button_settings_ok_handle;
extern mw_handle_t check_box_settings_handle;
extern mw_handle_t radio_button_settings_handle;
extern mw_handle_t list_box_settings_handle;
extern mw_handle_t label_settings_handle;
extern mw_handle_t arrow_settings_up;
extern mw_handle_t arrow_settings_down;
extern mw_handle_t list_box_file_handle;
extern mw_handle_t arrow_file_up_handle;
extern mw_handle_t arrow_file_down_handle;
extern mw_handle_t label_file_handle;
extern mw_handle_t button_file_ok_handle;
extern const uint8_t date_bitmap[];
extern const uint8_t date_down_bitmap[];
extern const uint8_t time_bitmap[];
extern const uint8_t time_down_bitmap[];
extern const uint8_t settings_bitmap[];
extern const uint8_t settings_down_bitmap[];
extern const uint8_t temp_bitmap[];
extern const uint8_t temp_down_bitmap[];
extern const uint8_t help_bitmap[];
extern const uint8_t help_down_bitmap[];
extern const uint8_t file_bitmap[];
extern const uint8_t file_down_bitmap[];
extern const mw_ui_list_box_entry list_box_file_entries_images[];
extern const size_t list_box_file_entries_images_count;
extern const mw_ui_list_box_entry list_box_file_entries_root[];
extern const size_t list_box_file_entries_root_count;
extern const mw_ui_list_box_entry list_box_file_entries_docs[];
extern const size_t list_box_file_entries_docs_count;
extern const mw_ui_list_box_entry list_box_settings_entries[];

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

#ifdef __cplusplus
}
#endif

#endif
