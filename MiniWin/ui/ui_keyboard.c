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

#include <miniwin.h>
#include <string.h>
#include <stdio.h>
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const char keyboards[4][3][11] = {
{"QWERTYUIOP ", "ASDFGHJKL\b ", " ZXCVBNM .,"},
{"qwertyuiop ", "asdfghjkl\b ", " zxcvbnm .,"},
{"1234567890 ", "!\"#$%^&*@\b ", "()+-/=., <>"},
{"1234567890 ", "|;:'~<>\\%\b ", "{}?`[]+- */"}
};

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern volatile uint32_t mw_tick_counter;
extern const uint8_t mw_bitmaps_backspace_key[];
extern const uint8_t mw_bitmaps_shift_key[];
extern const uint8_t mw_bitmaps_num_key[];
extern const uint8_t mw_bitmaps_sym_key[];
extern const uint8_t mw_bitmaps_let_key[];

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_util_rect_t invalid_rect;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void keyboard_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void keyboard_message_function(const mw_message_t *message);
static void process_keypress(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void keyboard_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_keyboard_data_t *this_keyboard = (mw_ui_keyboard_data_t*)mw_get_control_instance_data(control_handle);
	uint8_t row;
	uint8_t column;
	mw_hal_lcd_colour_t highlighted_colour;
	mw_hal_lcd_colour_t lowlighted_colour;

	/* draw the keys */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_clear_pattern();
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_font(MW_GL_FONT_9);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	for (row = 0; row < 3; row ++)
	{
		for (column = 0; column < 11; column++)
		{
			/* set colour of key box fill according to pressed state */
			if (this_keyboard->is_key_pressed &&
					row == this_keyboard->key_pressed_row &&
					column == this_keyboard->key_pressed_column)
			{
				mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
			}
			else
			{
				mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
			}

			/* set colour of text according to control enabled state */
			if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED)
			{
				mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
			}
			else
			{
				mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
			}

			/* draw key rectangle */
			mw_gl_rectangle(draw_info,
					column * MW_UI_KEYBOARD_KEY_SIZE,
					row * MW_UI_KEYBOARD_KEY_SIZE,
					MW_UI_KEYBOARD_KEY_SIZE,
					MW_UI_KEYBOARD_KEY_SIZE);

			/* draw 3d effect */
			if (this_keyboard->is_key_pressed &&
					row == this_keyboard->key_pressed_row &&
					column == this_keyboard->key_pressed_column)
			{
				highlighted_colour = MW_HAL_LCD_BLACK;
				lowlighted_colour = MW_HAL_LCD_GREY2;
			}
			else
			{
				highlighted_colour = MW_HAL_LCD_WHITE;
				lowlighted_colour = MW_HAL_LCD_GREY7;
			}
			mw_gl_set_fg_colour(highlighted_colour);
			mw_gl_vline(draw_info,
					column * MW_UI_KEYBOARD_KEY_SIZE + 1,
					row * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(row + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2);
			mw_gl_hline(draw_info,
					column * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(column + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2,
					row * MW_UI_KEYBOARD_KEY_SIZE + 1);
			mw_gl_set_fg_colour(lowlighted_colour);
			mw_gl_vline(draw_info,
					(column + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2,
					row * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(row + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2);
			mw_gl_hline(draw_info,
					column * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(column + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2,
					(row + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2);

			/* draw key character */
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
			if (this_keyboard->is_key_pressed &&
					row == this_keyboard->key_pressed_row &&
					column == this_keyboard->key_pressed_column)
			{
				mw_gl_character(draw_info,
						column * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET + 1,
						row * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET + 1,
						keyboards[this_keyboard->keyboard_display][row][column]);
			}
			else
			{
				mw_gl_character(draw_info,
						column * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET,
						row * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET,
						keyboards[this_keyboard->keyboard_display][row][column]);
			}
		}

		/* draw keys on all keyboards */
		if (this_keyboard->is_key_pressed &&
				this_keyboard->key_pressed_row == 1 &&
				this_keyboard->key_pressed_column == 9)
		{
			mw_gl_monochrome_bitmap(draw_info,
					9 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
					1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					mw_bitmaps_backspace_key);
		}
		else
		{
			mw_gl_monochrome_bitmap(draw_info,
					9 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					mw_bitmaps_backspace_key);
		}

		/* draw keyboard change keys on letters keyboard */
		if (this_keyboard->keyboard_display == KEYBOARD_UPPER_CHARS ||
				 this_keyboard->keyboard_display == KEYBOARD_LOWER_CHARS)
		{
			if (this_keyboard->is_key_pressed &&
					this_keyboard->key_pressed_row == 0 &&
					this_keyboard->key_pressed_column == 10)
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_num_key);
			}
			else
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_num_key);
			}

			if (this_keyboard->is_key_pressed &&
					this_keyboard->key_pressed_row == 1 &&
					this_keyboard->key_pressed_column == 10)
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_sym_key);
			}
			else
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_sym_key);
			}

			if (this_keyboard->is_key_pressed &&
					this_keyboard->key_pressed_row == 2 &&
					this_keyboard->key_pressed_column == 0)
			{
				mw_gl_monochrome_bitmap(draw_info,
						0 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						2 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_shift_key);
			}
			else
			{
				mw_gl_monochrome_bitmap(draw_info,
						0 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						2 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_shift_key);
			}
		}
		else if (this_keyboard->keyboard_display == KEYBOARD_NUMBERS)
		{
			if (this_keyboard->is_key_pressed &&
					this_keyboard->key_pressed_row == 0 &&
					this_keyboard->key_pressed_column == 10)
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_let_key);
			}
			else
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_let_key);
			}

			if (this_keyboard->is_key_pressed &&
					this_keyboard->key_pressed_row == 1 &&
					this_keyboard->key_pressed_column == 10)
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_sym_key);
			}
			else
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_sym_key);
			}
		}
		else
		{
			if (this_keyboard->is_key_pressed &&
					this_keyboard->key_pressed_row == 0 &&
					this_keyboard->key_pressed_column == 10)
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_let_key);
			}
			else
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_let_key);
			}

			if (this_keyboard->is_key_pressed &&
					this_keyboard->key_pressed_row == 1 &&
					this_keyboard->key_pressed_column == 10)
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET + 1,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_num_key);
			}
			else
			{
				mw_gl_monochrome_bitmap(draw_info,
						10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
						mw_bitmaps_num_key);
			}
		}
	}
}

/**
 * Process a keypress, either as a new touch down or a hold down from a previous touch down
 *
 * @param message Message passed in from message handler that calls this function
 */
static void process_keypress(const mw_message_t *message)
{
	mw_ui_keyboard_data_t *this_keyboard = (mw_ui_keyboard_data_t*)mw_get_control_instance_data(message->recipient_handle);

	/* check for shift key pressed */
	if (this_keyboard->key_pressed_row == 2
			&& this_keyboard->key_pressed_column == 0 &&
			(this_keyboard->keyboard_display == KEYBOARD_UPPER_CHARS ||
			 this_keyboard->keyboard_display == KEYBOARD_LOWER_CHARS))
	{
		if (this_keyboard->keyboard_display == KEYBOARD_UPPER_CHARS)
		{
			this_keyboard->keyboard_display = KEYBOARD_LOWER_CHARS;
		}
		else
		{
			this_keyboard->keyboard_display = KEYBOARD_UPPER_CHARS;
		}
		this_keyboard->swap_keyboard = true;
	}
	/* check for upper keypad change key pressed */
	else if (this_keyboard->key_pressed_row == 0 && this_keyboard->key_pressed_column == 10)
	{
		if (this_keyboard->keyboard_display == KEYBOARD_LOWER_CHARS ||
				this_keyboard->keyboard_display == KEYBOARD_UPPER_CHARS)
		{
			this_keyboard->keyboard_display = KEYBOARD_NUMBERS;
		}
		else
		{
			this_keyboard->keyboard_display = KEYBOARD_UPPER_CHARS;
		}
		this_keyboard->swap_keyboard = true;
	}
	/* check for lower keypad change key pressed */
	else if (this_keyboard->key_pressed_row == 1 && this_keyboard->key_pressed_column == 10)
	{
		if (this_keyboard->keyboard_display == KEYBOARD_LOWER_CHARS ||
				this_keyboard->keyboard_display == KEYBOARD_UPPER_CHARS ||
				this_keyboard->keyboard_display == KEYBOARD_NUMBERS)
		{
			this_keyboard->keyboard_display = KEYBOARD_SYMBOLS;
		}
		else if (this_keyboard->keyboard_display == KEYBOARD_SYMBOLS)
		{
			this_keyboard->keyboard_display = KEYBOARD_NUMBERS;
		}
		this_keyboard->swap_keyboard = true;
	}
	/* else get the character that has been pressed */
	else
	{
		/* post message for keypress */
		mw_post_message(MW_KEY_PRESSED_MESSAGE,
				message->recipient_handle,
				mw_get_control_parent_window_handle(message->recipient_handle),
				(uint32_t)keyboards[this_keyboard->keyboard_display][this_keyboard->key_pressed_row][this_keyboard->key_pressed_column],
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);
	}

	/* repaint pressed key area only */
	invalid_rect.x = this_keyboard->key_pressed_column * MW_UI_KEYBOARD_KEY_SIZE;
	invalid_rect.y = this_keyboard->key_pressed_row * MW_UI_KEYBOARD_KEY_SIZE;
	invalid_rect.width = MW_UI_KEYBOARD_KEY_SIZE;
	invalid_rect.height = MW_UI_KEYBOARD_KEY_SIZE;
	mw_paint_control_rect(message->recipient_handle, &invalid_rect);
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void keyboard_message_function(const mw_message_t *message)
{
	mw_ui_keyboard_data_t *this_keyboard = (mw_ui_keyboard_data_t*)mw_get_control_instance_data(message->recipient_handle);

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */
		this_keyboard->is_key_pressed = false;
		this_keyboard->keyboard_display = KEYBOARD_UPPER_CHARS;
		this_keyboard->swap_keyboard = false;
		this_keyboard->holding_down = false;
		this_keyboard->timer_handle = MW_INVALID_HANDLE;
		break;

	case MW_TOUCH_DRAG_MESSAGE:
	case MW_TOUCH_HOLD_DOWN_MESSAGE:
		if (!(mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED))
		{
			break;
		}

		if (!this_keyboard->is_key_pressed)
		{
			break;
		}

		mw_cancel_timer(this_keyboard->timer_handle);
		this_keyboard->holding_down = true;
		if (mw_tick_counter - this_keyboard->touch_down_time > MW_HOLD_DOWN_DELAY_TICKS)
		{
			process_keypress(message);
		}
		break;

	case MW_TIMER_MESSAGE:
		/* set key pressed to false */
		this_keyboard->is_key_pressed = false;

		if (this_keyboard->swap_keyboard)
		{
			this_keyboard->swap_keyboard = false;
			mw_paint_control(message->recipient_handle);
		}
		else
		{
			/* repaint pressed key area only */
			invalid_rect.x = this_keyboard->key_pressed_column * MW_UI_KEYBOARD_KEY_SIZE;
			invalid_rect.y = this_keyboard->key_pressed_row * MW_UI_KEYBOARD_KEY_SIZE;
			invalid_rect.width = MW_UI_KEYBOARD_KEY_SIZE;
			invalid_rect.height = MW_UI_KEYBOARD_KEY_SIZE;
			mw_paint_control_rect(message->recipient_handle, &invalid_rect);
		}
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */
		if (!(mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED))
		{
			break;
		}

		/* get the key pressed from the touch coordinates */
		this_keyboard->key_pressed_row = (message->message_data & 0xffff) / MW_UI_KEYBOARD_KEY_SIZE;
		this_keyboard->key_pressed_column = (message->message_data >> 16) / MW_UI_KEYBOARD_KEY_SIZE;

		this_keyboard->touch_down_time = mw_tick_counter;
		this_keyboard->timer_handle = mw_set_timer(mw_tick_counter + MW_KEY_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
		this_keyboard->is_key_pressed = true;
		process_keypress(message);
		break;

	case MW_TOUCH_UP_MESSAGE:
		if (this_keyboard->holding_down)
		{
			this_keyboard->holding_down = false;
			this_keyboard->timer_handle = mw_set_timer(mw_tick_counter + MW_KEY_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
		}
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_keyboard_add_new(uint16_t x,
		uint16_t y,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_keyboard_data_t *keyboard_instance_data)
{
	mw_util_rect_t r;

	mw_util_set_rect(&r, x, y, MW_UI_KEYBOARD_WIDTH, MW_UI_KEYBOARD_HEIGHT);

	return mw_add_control(&r,
			parent_handle,
			keyboard_paint_function,
			keyboard_message_function,
			flags,
			keyboard_instance_data);
}
