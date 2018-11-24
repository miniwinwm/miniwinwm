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
#include "window_tt_font.h"
#include "window_tt_font_text_box.h"

/****************
*** CONSTANTS ***
****************/

const char *test_text = "A kitten is a juvenile cat. After being born, " \
		"kittens are totally dependent on their mother for survival and " \
		"they do not normally open their eyes until after seven to ten days. " \
		"After about two weeks, kittens quickly develop and begin to explore " \
		"the world outside the nest. After a further three to four weeks, " \
		"they begin to eat solid food and grow adult teeth. Domestic kittens " \
		"are highly social animals and usually enjoy human companionship.";

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/* windows */
mw_handle_t window_deja_vu_font_handle;
mw_handle_t window_blkchcry_bw_font_handle;
mw_handle_t window_blkchcry_font_handle;

/* controls */
mw_handle_t text_box_handle;
mw_handle_t button_handle;
mw_handle_t window_tt_font_text_box_handle;
mw_handle_t vert_scroll_bar_handle;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const struct mf_rlefont_s mf_rlefont_DejaVuSans12;
extern const struct mf_rlefont_s mf_rlefont_BLKCHCRY16;
extern const struct mf_rlefont_s mf_rlefont_BLKCHCRY16bw;

/**********************
*** LOCAL VARIABLES ***
**********************/

/* windows instance data */
static window_tt_font_data_t window_deja_vu_font_data;
static window_tt_font_data_t window_blkchcry_bw_font_data;
static window_tt_font_data_t window_blkchcry_font_data;
static window_tt_font_text_box_data_t window_tt_font_text_box_data;

/* controls instance data */
static mw_ui_scrollable_text_box_data_t mw_ui_scrollable_text_box_data;
static mw_ui_button_data_t button_data;
static mw_ui_scroll_bar_vert_data_t vert_scroll_bar_data;

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
	mw_gl_rectangle(draw_info, 0, 0, MW_ROOT_WIDTH, MW_ROOT_HEIGHT);
}

void mw_user_root_message_function(const mw_message_t *message)
{
	(void)message;
}

void mw_user_init(void)
{
	mw_util_rect_t r;

	/* create window containing a text box control */
	mw_util_set_rect(&r, 0, 10, 210, 190);
	window_tt_font_text_box_handle = mw_add_window(&r,
			"Text box",
			window_tt_font_text_box_paint_function,
			window_tt_font_text_box_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
				MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE,
			&window_tt_font_text_box_data);

	/* create text box control */
	mw_util_set_rect(&r, 10, 10, 170, 130);
	mw_ui_scrollable_text_box_data.bg_colour = MW_HAL_LCD_WHITE;
	mw_ui_scrollable_text_box_data.fg_colour = MW_HAL_LCD_BLACK;
	mw_ui_scrollable_text_box_data.text = test_text;
	mw_ui_scrollable_text_box_data.justification = MW_GL_TT_FULLY_JUSTIFIED;
	mw_ui_scrollable_text_box_data.tt_font = &mf_rlefont_DejaVuSans12;
	text_box_handle = mw_ui_scrollable_text_box_add_new(&r,
			window_tt_font_text_box_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&mw_ui_scrollable_text_box_data);

	/* create button */
	mw_util_safe_strcpy(button_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, "Change");
	button_handle = mw_ui_button_add_new(10,
			150,
			window_tt_font_text_box_handle,
			MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
			&button_data);

	/* create vertical scroll bar */
	vert_scroll_bar_handle = mw_ui_scroll_bar_vert_add_new(180,
			10,
			130,
			window_tt_font_text_box_handle,
			MW_CONTROL_FLAG_IS_VISIBLE,
			&vert_scroll_bar_data);

	mw_util_set_rect(&r, 0, 10, 210, 150);
	window_deja_vu_font_data.text = test_text;
	window_deja_vu_font_data.rle_font = &mf_rlefont_DejaVuSans12;
	window_deja_vu_font_data.bw_font = false;
	window_deja_vu_font_data.fg_colour = MW_HAL_LCD_BLUE;
	window_deja_vu_font_data.bg_colour = MW_HAL_LCD_WHITE;
	window_deja_vu_font_data.justification = MW_GL_TT_FULLY_JUSTIFIED;
	window_deja_vu_font_handle = mw_add_window(&r,
			"Deja Vu",
			window_tt_font_paint_function,
			window_tt_font_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED |
				MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_LARGE_SIZE,
			&window_deja_vu_font_data);

	mw_util_set_rect(&r, 15, 60, 210, 150);
	window_blkchcry_bw_font_data.text = test_text;
	window_blkchcry_bw_font_data.rle_font = &mf_rlefont_BLKCHCRY16;
	window_blkchcry_bw_font_data.bw_font = false;
	window_blkchcry_bw_font_data.fg_colour = MW_HAL_LCD_BLACK;
	window_blkchcry_bw_font_data.bg_colour = MW_HAL_LCD_YELLOW;
	window_blkchcry_bw_font_data.justification = MW_GL_TT_LEFT_JUSTIFIED;
	window_blkchcry_bw_font_handle = mw_add_window(&r,
			"B-Chncry bw",
			window_tt_font_paint_function,
			window_tt_font_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED |
				MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_LARGE_SIZE,
			&window_blkchcry_bw_font_data);

	mw_util_set_rect(&r, 30, 110, 210, 150);
	window_blkchcry_font_data.text = test_text;
	window_blkchcry_font_data.rle_font = &mf_rlefont_BLKCHCRY16bw;
	window_blkchcry_font_data.bw_font = true;
	window_blkchcry_font_data.fg_colour = MW_HAL_LCD_BLACK;
	window_blkchcry_font_data.bg_colour = MW_HAL_LCD_YELLOW;
	window_blkchcry_font_data.justification = MW_GL_TT_LEFT_JUSTIFIED;
	window_blkchcry_font_handle = mw_add_window(&r,
			"B-Chncry",
			window_tt_font_paint_function,
			window_tt_font_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR | MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED |
				MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR | MW_WINDOW_FLAG_CAN_BE_CLOSED | MW_WINDOW_FLAG_IS_VISIBLE |
				MW_WINDOW_FLAG_LARGE_SIZE,
			&window_blkchcry_font_data);

	mw_paint_all();
}
