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

#include "miniwin.h"
#include "W1.h"
#include "W2.h"

/****************
*** CONSTANTS ***
****************/

static const mw_ui_list_box_entry list_box_LB1_entries[] = {{"Fred", NULL}, {"Bert", NULL}, {"Pete", NULL}};

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/* windows */
mw_handle_t window_W1_handle;
mw_handle_t window_W2_handle;

/* controls */
mw_handle_t button_B1_handle;
mw_handle_t button_B2_handle;
mw_handle_t list_box_LB1_handle;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint8_t logo_array[];

/**********************
*** LOCAL VARIABLES ***
**********************/

/* controls instance data */
static mw_ui_button_data_t button_B1_data;
static mw_ui_button_data_t button_B2_data;
static mw_ui_list_box_data_t list_box_LB1_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_user_root_paint_function(const mw_gl_draw_info_t *draw_info)
{
    mw_gl_set_solid_fill_colour(MW_HAL_LCD_PURPLE);
    mw_gl_clear_pattern();
    mw_gl_set_border(MW_GL_BORDER_OFF);
    mw_gl_set_fill(MW_GL_FILL);

    /* draw root background around bitmap */
    mw_gl_rectangle(draw_info, 0, 0, MW_ROOT_WIDTH, 100);
    mw_gl_rectangle(draw_info, 0, 192, MW_ROOT_WIDTH, 128);
    mw_gl_rectangle(draw_info, 0, 100, 90, 92);
    mw_gl_rectangle(draw_info, 156, 100, 84, 92);

    /* draw bitmap */
    mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
    mw_gl_set_bg_colour(MW_HAL_LCD_PURPLE);
    mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
    mw_gl_monochrome_bitmap(draw_info, 90, 100, 66, 92, logo_array);
}

void mw_user_root_message_function(const mw_message_t *message)
{
    switch (message->message_id)
	{
	case MW_TOUCH_DOWN_MESSAGE:
		mw_set_window_visible(window_W2_handle, true);
		mw_reposition_window(window_W2_handle, message->message_data >> 16, message->message_data & 0xffff);
		mw_paint_all();
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		if (message->sender_handle == button_B2_handle)
		{
			mw_create_window_dialog_one_button(20,
					50,
					150,
					"Titulus",
					"Hoc nuntio",
					"Ita vero",
					false,
					message->recipient_handle);
		}
		break;

	default:
		break;
	}
}

void mw_user_init(void)
{
    mw_util_rect_t r;

    mw_util_set_rect(&r, 15, 35, 200, 180);
    window_W1_handle = mw_add_window(&r,
        "Window 1", 
        window_W1_paint_function,
        window_W1_message_function,
        NULL,
        0,
        0 | MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_IS_VISIBLE,
        NULL);

    mw_util_safe_strcpy(button_B1_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Button1");
    button_B1_handle = mw_ui_button_add_new(10,
        10,
        window_W1_handle,
        0 | MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
        &button_B1_data);

    mw_util_safe_strcpy(button_B2_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Button2");
    button_B2_handle = mw_ui_button_add_new(10,
        10,
        MW_ROOT_WINDOW_HANDLE,
        0 | MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
        &button_B2_data);

    mw_util_set_rect(&r, 0, 0, 50, 42);
    window_W2_handle = mw_add_window(&r,
        "", 
        window_W2_paint_function,
        window_W2_message_function,
        NULL,
        0,
        0,
        NULL);

    list_box_LB1_data.line_enables = MW_ALL_ITEMS_ENABLED;
    list_box_LB1_data.number_of_lines = 3;
    list_box_LB1_data.number_of_items = (sizeof(list_box_LB1_entries)/sizeof(mw_ui_list_box_entry));
    list_box_LB1_data.list_box_entries = list_box_LB1_entries;
    list_box_LB1_handle = mw_ui_list_box_add_new(0,
        0,
        50,
        window_W2_handle,
        0 | MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
        &list_box_LB1_data);

    mw_paint_all();
}
