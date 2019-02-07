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

/***************
*** INCLUDES ***
***************/

#include <stdio.h>
#include "dialogs/dialog_common.h"
#include "miniwin.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Window data structure
 */
typedef struct
{
	mw_handle_t button_ok_handle;								/**< Handle of left button */
	mw_handle_t button_cancel_handle;							/**< Handle of right button */
	mw_handle_t owner_window_handle;							/**< Window handle to send response message to */
	mw_handle_t horiz_scroll_bar_red_handle;					/**< Red component scroll bar */
	mw_handle_t horiz_scroll_bar_green_handle;					/**< Green component scroll bar */
	mw_handle_t horiz_scroll_bar_blue_handle;					/**< Blue component scroll bar */
	mw_handle_t colour_chooser_dialog_window_handle;			/**< Handle of two button dialog window */
	mw_hal_lcd_colour_t displayed_colour;						/**< The currently displayed colour */
	mw_ui_button_data_t button_ok_data;							/**< Instance data of left button */
	mw_ui_button_data_t button_cancel_data;						/**< Instance data of right button */
	mw_ui_scroll_bar_horiz_data_t horiz_scroll_bar_red_data;	/**< Instance data of red horiz scroll bar */
	mw_ui_scroll_bar_horiz_data_t horiz_scroll_bar_green_data;	/**< Instance data of green horiz scroll bar */
	mw_ui_scroll_bar_horiz_data_t horiz_scroll_bar_blue_data;	/**< Instance data of blue horiz scroll bar */
	bool large_size;											/**< True for large size false for standard size */
} mw_dialog_colour_chooser_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_dialog_colour_chooser_data_t mw_dialog_colour_chooser_data;
static mw_util_rect_t paint_rect_large = {60, 5, 110, 30};
static mw_util_rect_t paint_rect = {40, 5, 90, 20};

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void mw_dialog_colour_chooser_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);
static void mw_dialog_colour_chooser_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Window paint routine, called by window manager.
 *
 * @param window_handle The window identifier in the array of windows
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
static void mw_dialog_colour_chooser_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	char text_buffer[12U];

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_window_client_rect(window_handle).width,
			mw_get_window_client_rect(window_handle).height);

	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	mw_gl_set_solid_fill_colour(mw_dialog_colour_chooser_data.displayed_colour);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	(void)sprintf(text_buffer, "0x%06X", (unsigned int)mw_dialog_colour_chooser_data.displayed_colour);

	if (mw_dialog_colour_chooser_data.large_size)
	{
		mw_gl_rectangle(draw_info, 60, 5, 30, 30);
		mw_gl_set_font(MW_GL_TITLE_FONT);
		mw_gl_string(draw_info, 100, 15, text_buffer);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_RED);
		mw_gl_rectangle(draw_info, 5, 40, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_rectangle(draw_info, 5, 75, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLUE);
		mw_gl_rectangle(draw_info, 5, 110, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION, MW_SCROLL_BAR_LARGE_NARROW_DIMENSION);
	}
	else
	{
		mw_gl_rectangle(draw_info, 40, 5, 30, 20);
		mw_gl_set_font(MW_GL_FONT_9);
		mw_gl_string(draw_info, 80, 10, text_buffer);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_RED);
		mw_gl_rectangle(draw_info, 5, 30, MW_SCROLL_BAR_NARROW_DIMENSION, MW_SCROLL_BAR_NARROW_DIMENSION);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREEN);
		mw_gl_rectangle(draw_info, 5, 50, MW_SCROLL_BAR_NARROW_DIMENSION, MW_SCROLL_BAR_NARROW_DIMENSION);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_BLUE);
		mw_gl_rectangle(draw_info, 5, 70, MW_SCROLL_BAR_NARROW_DIMENSION, MW_SCROLL_BAR_NARROW_DIMENSION);
	}
}

/**
 * Window message handler called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
static void mw_dialog_colour_chooser_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
				message->recipient_handle,
				mw_dialog_colour_chooser_data.horiz_scroll_bar_red_handle,
				mw_dialog_colour_chooser_data.displayed_colour >> 16U,
				NULL,
				MW_CONTROL_MESSAGE);
		mw_paint_control(mw_dialog_colour_chooser_data.horiz_scroll_bar_red_handle);

		mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
				message->recipient_handle,
				mw_dialog_colour_chooser_data.horiz_scroll_bar_green_handle,
				(mw_dialog_colour_chooser_data.displayed_colour & 0xff00U) >> 8U,
				NULL,
				MW_CONTROL_MESSAGE);
		mw_paint_control(mw_dialog_colour_chooser_data.horiz_scroll_bar_green_handle);

		mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
				message->recipient_handle,
				mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_handle,
				mw_dialog_colour_chooser_data.displayed_colour & 0xffU,
				NULL,
				MW_CONTROL_MESSAGE);
		mw_paint_control(mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_handle);
		break;

	case MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:
		if (message->sender_handle == mw_dialog_colour_chooser_data.horiz_scroll_bar_red_handle)
		{
			mw_dialog_colour_chooser_data.displayed_colour &= 0x00ffffU;
			mw_dialog_colour_chooser_data.displayed_colour |= (message->message_data << 16U);
		}
		else if (message->sender_handle == mw_dialog_colour_chooser_data.horiz_scroll_bar_green_handle)
		{
			mw_dialog_colour_chooser_data.displayed_colour &= 0xff00ffU;
			mw_dialog_colour_chooser_data.displayed_colour |= (message->message_data << 8U);
		}
		else if (message->sender_handle == mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_handle)
		{
			mw_dialog_colour_chooser_data.displayed_colour &= 0xffff00U;
			mw_dialog_colour_chooser_data.displayed_colour |= (message->message_data);
		}
		if (mw_dialog_colour_chooser_data.large_size)
		{
			mw_paint_window_client_rect(mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle, &paint_rect_large);
		}
		else
		{
			mw_paint_window_client_rect(mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle, &paint_rect);
		}
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		{
			/* remove all controls and window */
			mw_remove_window(mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle);

			/* a window has changed visibility so repaint all */
			mw_paint_all();

			/* find which button was pressed */
			if (message->sender_handle == mw_dialog_colour_chooser_data.button_ok_handle)
			{
				/* post cancel response to receiving window */
				mw_post_message(MW_DIALOG_COLOUR_CHOOSER_OK_MESSAGE,
						message->recipient_handle,
						mw_dialog_colour_chooser_data.owner_window_handle,
						mw_dialog_colour_chooser_data.displayed_colour,
						NULL,
						MW_WINDOW_MESSAGE);
			}
			else
			{
				/* post cancel response to receiving window */
				mw_post_message(MW_DIALOG_COLOUR_CHOOSER_CANCEL_MESSAGE,
						message->recipient_handle,
						mw_dialog_colour_chooser_data.owner_window_handle,
						MW_UNUSED_MESSAGE_PARAMETER,
						NULL,
						MW_WINDOW_MESSAGE);
			}
		}
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_create_window_dialog_colour_chooser(int16_t x,
		int16_t y,
		char *title,
		mw_hal_lcd_colour_t start_colour,
		bool large_size,
		mw_handle_t owner_window_handle)
{
	mw_util_rect_t rect;

	/* check pointer parameters */
	if (title == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (MW_INVALID_HANDLE);
	}

	/* set width and height */
	if (large_size)
	{
		rect.width = 217;
		rect.height = 200;
	}
	else
	{
		rect.width = 152;
		rect.height = 130;
	}

	/* check start position */
	if (x + rect.width > MW_ROOT_WIDTH || x < 0)
	{
		return (MW_INVALID_HANDLE);
	}
	if (y + rect.height > MW_ROOT_HEIGHT || y < 0)
	{
		return (MW_INVALID_HANDLE);
	}

	/* check response window handle */
	if (!mw_is_window_handle_valid(owner_window_handle))
	{
		return (MW_INVALID_HANDLE);
	}

	mw_dialog_colour_chooser_data.large_size = large_size;
	mw_dialog_colour_chooser_data.owner_window_handle = owner_window_handle;
	rect.x = x;
	rect.y = y;
	mw_dialog_colour_chooser_data.displayed_colour = start_colour;

	mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle = mw_add_window(&rect,
			title,
			mw_dialog_colour_chooser_paint_function,
			mw_dialog_colour_chooser_message_function,
			NULL,
			0U,
			MW_WINDOW_FLAG_HAS_BORDER | MW_WINDOW_FLAG_HAS_TITLE_BAR |
					MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_IS_MODAL | (large_size ? MW_WINDOW_FLAG_LARGE_SIZE : 0),
			NULL);

	/* check if window could be created */
	if (mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle == MW_INVALID_HANDLE)
	{
		/* it couldn't so exit */
		return (MW_INVALID_HANDLE);
	}

	/* set controls data */
	(void)mw_util_safe_strcpy(mw_dialog_colour_chooser_data.button_ok_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "OK");
	(void)mw_util_safe_strcpy(mw_dialog_colour_chooser_data.button_cancel_data.button_label,
			MW_UI_BUTTON_LABEL_MAX_CHARS, "Cancel");

	if (large_size)
	{
		mw_dialog_colour_chooser_data.horiz_scroll_bar_red_handle = mw_ui_scroll_bar_horiz_add_new(35,
				40,
				175,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_colour_chooser_data.horiz_scroll_bar_red_data);

		mw_dialog_colour_chooser_data.horiz_scroll_bar_green_handle = mw_ui_scroll_bar_horiz_add_new(35,
				75,
				175,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_colour_chooser_data.horiz_scroll_bar_green_data);

		mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_handle = mw_ui_scroll_bar_horiz_add_new(35,
				110,
				175,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_data);

		mw_dialog_colour_chooser_data.button_ok_handle = mw_ui_button_add_new(5,
				140,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_colour_chooser_data.button_ok_data);

		mw_dialog_colour_chooser_data.button_cancel_handle = mw_ui_button_add_new(110,
				140,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED | MW_CONTROL_FLAG_LARGE_SIZE,
				&mw_dialog_colour_chooser_data.button_cancel_data);
	}
	else
	{
		mw_dialog_colour_chooser_data.horiz_scroll_bar_red_handle = mw_ui_scroll_bar_horiz_add_new(23,
				30,
				120,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_colour_chooser_data.horiz_scroll_bar_red_data);

		mw_dialog_colour_chooser_data.horiz_scroll_bar_green_handle = mw_ui_scroll_bar_horiz_add_new(23,
				50,
				120,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_colour_chooser_data.horiz_scroll_bar_green_data);

		mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_handle = mw_ui_scroll_bar_horiz_add_new(23,
				70,
				120,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_data);

		mw_dialog_colour_chooser_data.button_ok_handle = mw_ui_button_add_new(10,
				90,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_colour_chooser_data.button_ok_data);

		mw_dialog_colour_chooser_data.button_cancel_handle = mw_ui_button_add_new(85,
				90,
				mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle,
				MW_CONTROL_FLAG_IS_VISIBLE | MW_CONTROL_FLAG_IS_ENABLED,
				&mw_dialog_colour_chooser_data.button_cancel_data);
	}

	/* check if controls could be created */
	if (mw_dialog_colour_chooser_data.button_ok_handle == MW_INVALID_HANDLE ||
			mw_dialog_colour_chooser_data.button_cancel_handle == MW_INVALID_HANDLE ||
			mw_dialog_colour_chooser_data.horiz_scroll_bar_red_handle == MW_INVALID_HANDLE ||
			mw_dialog_colour_chooser_data.horiz_scroll_bar_green_handle == MW_INVALID_HANDLE ||
			mw_dialog_colour_chooser_data.horiz_scroll_bar_blue_handle == MW_INVALID_HANDLE)
	{
		/* remove all controls and window */
		mw_remove_window(mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle);

		return (MW_INVALID_HANDLE);
	}

	/* owner window needs its title bar redrawing */
	mw_paint_window_frame(owner_window_handle, MW_WINDOW_FRAME_COMPONENT_TITLE_BAR);

	/* this window needs painting; it is coming up at the front so paint only this one */
	mw_paint_window_frame(mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle, MW_WINDOW_FRAME_COMPONENT_ALL);
	mw_paint_window_client(mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle);

	return (mw_dialog_colour_chooser_data.colour_chooser_dialog_window_handle);
}
