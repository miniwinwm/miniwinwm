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
#include "ui/ui_keyboard.h"

/****************
*** CONSTANTS ***
****************/

static const char keyboards[4][3][11] = {
{"QWERTYUIOP ", "ASDFGHJKL  ", " ZXCVBNM   "},
{"qwertyuiop ", "asdfghjkl  ", " zxcvbnm   "},
{"1234567890 ", "!\"#$%^&*@  ", "()+-/=.,   "},
{"|;:'~<>\\[] ", "{}?`       ", "           "}
};

static const mw_util_rect_t input_text_rect = {0, 0, MW_UI_KEYBOARD_WIDTH, MW_UI_KEYBOARD_KEY_SIZE};
static const mw_util_rect_t all_keys_rect = {0, MW_UI_KEYBOARD_KEY_SIZE, MW_UI_KEYBOARD_WIDTH, 3 * MW_UI_KEYBOARD_KEY_SIZE};

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
extern const uint8_t mw_bitmaps_ok_key[];
extern const uint8_t mw_bitmaps_cancel_key[];
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

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_ui_keyboard_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_keyboard_data_t *this_keyboard = (mw_ui_keyboard_data_t*)mw_get_control_instance_data(control_ref);
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
			if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAG_IS_ENABLED)
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
					(row + 1) * MW_UI_KEYBOARD_KEY_SIZE,
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
					(row + 1) * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(row + 2) * MW_UI_KEYBOARD_KEY_SIZE - 2);
			mw_gl_hline(draw_info,
					column * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(column + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2,
					(row + 1) * MW_UI_KEYBOARD_KEY_SIZE + 1);
			mw_gl_set_fg_colour(lowlighted_colour);
			mw_gl_vline(draw_info,
					(column + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2,
					(row + 1) * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(row + 2) * MW_UI_KEYBOARD_KEY_SIZE - 2);
			mw_gl_hline(draw_info,
					column * MW_UI_KEYBOARD_KEY_SIZE + 1,
					(column + 1) * MW_UI_KEYBOARD_KEY_SIZE - 2,
					(row + 2) * MW_UI_KEYBOARD_KEY_SIZE - 2);

			/* draw key character */
			mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
			if (this_keyboard->is_key_pressed &&
					row == this_keyboard->key_pressed_row &&
					column == this_keyboard->key_pressed_column)
			{
				mw_gl_character(draw_info,
						column * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET + 1,
						(row + 1) * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET + 1,
						keyboards[this_keyboard->keyboard_display][row][column]);
			}
			else
			{
				mw_gl_character(draw_info,
						column * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET,
						(row + 1) * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_TEXT_OFFSET,
						keyboards[this_keyboard->keyboard_display][row][column]);
			}
		}

		/* draw keys on all keyboards */
		mw_gl_monochrome_bitmap(draw_info,
				9 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
				2 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
				MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
				MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
				mw_bitmaps_backspace_key);

		mw_gl_monochrome_bitmap(draw_info,
				10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
				3 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
				MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
				MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
				mw_bitmaps_ok_key);

		mw_gl_monochrome_bitmap(draw_info,
				9 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
				3 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
				MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
				MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
				mw_bitmaps_cancel_key);

		/* draw keyboard change keys on letters keyboard */
		if (this_keyboard->keyboard_display == KEYBOARD_UPPER_CHARS ||
				 this_keyboard->keyboard_display == KEYBOARD_LOWER_CHARS)
		{
			mw_gl_monochrome_bitmap(draw_info,
					10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					mw_bitmaps_num_key);

			mw_gl_monochrome_bitmap(draw_info,
					10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					2 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					mw_bitmaps_sym_key);

			mw_gl_monochrome_bitmap(draw_info,
					0 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					3 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					mw_bitmaps_shift_key);
		}
		else if (this_keyboard->keyboard_display == KEYBOARD_NUMBERS)
		{
			mw_gl_monochrome_bitmap(draw_info,
					10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					1 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					mw_bitmaps_let_key);

			mw_gl_monochrome_bitmap(draw_info,
					10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					2 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
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
					mw_bitmaps_let_key);

			mw_gl_monochrome_bitmap(draw_info,
					10 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					2 * MW_UI_KEYBOARD_KEY_SIZE + MW_UI_KEYBOARD_KEY_BITMAP_OFFSET,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					MW_UI_KEYBOARD_KEY_BITMAP_SIZE,
					mw_bitmaps_num_key);
		}
	}

	/* draw the box the text is displayed in */
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_rectangle(draw_info, 0, 0, MW_UI_KEYBOARD_WIDTH, MW_UI_KEYBOARD_KEY_SIZE);

	/* draw 3d effect */
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info,
			1,
			1,
			MW_UI_KEYBOARD_KEY_SIZE - 2);
	mw_gl_hline(draw_info,
			1,
			MW_UI_KEYBOARD_WIDTH - 2,
			1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info,
			MW_UI_KEYBOARD_WIDTH - 2,
			1,
			MW_UI_KEYBOARD_KEY_SIZE - 2);
	mw_gl_hline(draw_info,
			1,
			MW_UI_KEYBOARD_WIDTH - 2,
			MW_UI_KEYBOARD_KEY_SIZE - 2);

	/* draw text */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_string(draw_info, 3, 4, this_keyboard->entry_buffer);

	/* draw cursor */
	if (this_keyboard->draw_cursor)
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		mw_gl_vline(draw_info,
				2 + this_keyboard->cursor_position * MW_GL_STANDARD_CHARACTER_WIDTH,
				2,
				MW_GL_STANDARD_CHARACTER_HEIGHT + 4);
	}
}

void mw_ui_keyboard_message_function(const mw_message_t *message)
{
	mw_ui_keyboard_data_t *this_keyboard = (mw_ui_keyboard_data_t*)mw_get_control_instance_data(message->recipient_id);
	char c;

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */
		this_keyboard->is_key_pressed = false;
		this_keyboard->entry_buffer[0] = '\0';
		this_keyboard->keyboard_display = KEYBOARD_UPPER_CHARS;
		this_keyboard->draw_cursor = false;
		this_keyboard->swap_keyboard = false;
		this_keyboard->cursor_position = 0;
		break;

	case MW_TRANSFER_DATA_1_PTR_MESSAGE:
		/* handle a transfer data pointer message, which contains new buffer text */
		if (message->message_data)
		{
			mw_util_safe_strcpy(this_keyboard->entry_buffer, MW_UI_KEYBOARD_MAX_CHARS + 1, (char *)message->message_data);
			this_keyboard->cursor_position = strlen(this_keyboard->entry_buffer);
		}
		else
		{
			MW_ASSERT(false, "Null pointer argument");
		}
		break;

	case MW_CONTROL_GAINED_FOCUS_MESSAGE:
		this_keyboard->timer_id = mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND, message->recipient_id, MW_CONTROL_MESSAGE);
		break;

	case MW_CONTROL_LOST_FOCUS_MESSAGE:
		mw_cancel_timer(this_keyboard->timer_id);
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		if (this_keyboard->is_key_pressed)
		{
			/* set key pressed to false */
			this_keyboard->is_key_pressed = false;

			if (this_keyboard->swap_keyboard)
			{
				this_keyboard->swap_keyboard = false;
				mw_paint_control_rect(message->recipient_id, &all_keys_rect);
			}
			else
			{
				/* repaint pressed key area only */
				invalid_rect.x = this_keyboard->key_pressed_column * MW_UI_KEYBOARD_KEY_SIZE;
				invalid_rect.y = (this_keyboard->key_pressed_row + 1) * MW_UI_KEYBOARD_KEY_SIZE;
				invalid_rect.width = MW_UI_KEYBOARD_KEY_SIZE;
				invalid_rect.height = MW_UI_KEYBOARD_KEY_SIZE;
				mw_paint_control_rect(message->recipient_id, &invalid_rect);
			}
		}
		else
		{
			/* repaint cursor area only */
			this_keyboard->draw_cursor = !this_keyboard->draw_cursor;
			invalid_rect.x = 2 + this_keyboard->cursor_position * MW_GL_STANDARD_CHARACTER_WIDTH;
			invalid_rect.y = 2;
			invalid_rect.width = 1;
			invalid_rect.height = MW_GL_STANDARD_CHARACTER_HEIGHT + 4;
			mw_paint_control_rect(message->recipient_id, &invalid_rect);
		}

		/* reset timer for cursor */
		this_keyboard->timer_id = mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS,
				message->recipient_id,
				MW_CONTROL_MESSAGE);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */
		if (!(mw_get_control_flags(message->recipient_id) & MW_CONTROL_FLAG_IS_ENABLED))
		{
			break;
		}

		/* check if the y coordinate of the touch point is in the row of keys */
		if ((message->message_data & 0xffff) > MW_UI_KEYBOARD_KEY_SIZE)
		{
			/* set up for key up redraw after timer expired */
			mw_cancel_timer(this_keyboard->timer_id);
			this_keyboard->timer_id = mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_id, MW_CONTROL_MESSAGE);
			this_keyboard->is_key_pressed = true;

			/* get the key pressed from the touch coordinates */
			this_keyboard->key_pressed_row = ((message->message_data & 0xffff) / MW_UI_KEYBOARD_KEY_SIZE) - 1;
			this_keyboard->key_pressed_column = (message->message_data >> 16) / MW_UI_KEYBOARD_KEY_SIZE;

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
			/* check for backspace */
			else if (this_keyboard->key_pressed_row == 1 && this_keyboard->key_pressed_column == 9)
			{
				if (this_keyboard->cursor_position > 0)
				{
					memmove(&this_keyboard->entry_buffer[this_keyboard->cursor_position - 1],
							&this_keyboard->entry_buffer[this_keyboard->cursor_position],
							strlen(this_keyboard->entry_buffer) - this_keyboard->cursor_position + 1);

					this_keyboard->cursor_position--;
				}
			}
			/* check for cancel */
			else if (this_keyboard->key_pressed_row == 2 && this_keyboard->key_pressed_column == 9)
			{
				mw_post_message(MW_KEYBOARD_CANCEL_MESSAGE,
						message->recipient_id,
						mw_get_control_parent_window(message->recipient_id),
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_WINDOW_MESSAGE);
			}
			/* check for ok */
			else if (this_keyboard->key_pressed_row == 2 && this_keyboard->key_pressed_column == 10)
			{
				mw_post_message(MW_KEYBOARD_OK_MESSAGE,
						message->recipient_id,
						mw_get_control_parent_window(message->recipient_id),
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_WINDOW_MESSAGE);
			}
			/* else get the character that has been pressed */
			else
			{
				if (strlen(this_keyboard->entry_buffer) < MW_UI_KEYBOARD_MAX_CHARS)
				{
					c = keyboards[this_keyboard->keyboard_display][this_keyboard->key_pressed_row][this_keyboard->key_pressed_column];
					memmove(&this_keyboard->entry_buffer[this_keyboard->cursor_position + 1],
							&this_keyboard->entry_buffer[this_keyboard->cursor_position],
							strlen(this_keyboard->entry_buffer) - this_keyboard->cursor_position + 1);
					this_keyboard->entry_buffer[this_keyboard->cursor_position] = c;
					this_keyboard->cursor_position++;
				}
			}

			/* repaint pressed key area only */
			invalid_rect.x = this_keyboard->key_pressed_column * MW_UI_KEYBOARD_KEY_SIZE;
			invalid_rect.y = (this_keyboard->key_pressed_row + 1) * MW_UI_KEYBOARD_KEY_SIZE;
			invalid_rect.width = MW_UI_KEYBOARD_KEY_SIZE;
			invalid_rect.height = MW_UI_KEYBOARD_KEY_SIZE;
			mw_paint_control_rect(message->recipient_id, &invalid_rect);
		}
		else
		{
			this_keyboard->cursor_position = (message->message_data >> 16) / MW_GL_STANDARD_CHARACTER_WIDTH;
			if (this_keyboard->cursor_position > strlen(this_keyboard->entry_buffer))
			{
				this_keyboard->cursor_position = strlen(this_keyboard->entry_buffer);
			}
		}

		/* repaint text entry area only */
		if (!this_keyboard->swap_keyboard)
		{
			mw_paint_control_rect(message->recipient_id, &input_text_rect);
		}
		break;

		default:
			break;
	}
}

uint8_t mw_ui_keyboard_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_keyboard_data_t *keyboard_instance_data)
{
	mw_util_rect_t r;

	mw_util_set_rect(&r, x, y, MW_UI_KEYBOARD_WIDTH, MW_UI_KEYBOARD_HEIGHT);

	return mw_add_control(&r,
			parent,
			mw_ui_keyboard_paint_function,
			mw_ui_keyboard_message_function,
			flags,
			keyboard_instance_data);
}
