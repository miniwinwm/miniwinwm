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
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

static const char key_codes[] = 				"789456123-0\b";	/**< The actual characters represented by each key going across columns then down rows */
#define MW_UI_KEYPAD_KEY_TEXT_OFFSET 			7					/**< Start position relative to square for character */
#define MW_UI_KEYPAD_KEY_TEXT_LARGE_OFFSET 		14					/**< Start position relative to large square for large character */
#define MW_UI_KEYPAD_KEY_BITMAP_SIZE			16					/**< Backspace symbol bitmap size */
#define MW_UI_KEYPAD_KEY_BITMAP_OFFSET 			2					/**< Start position relative to square for bitmap */
#define MW_UI_KEYPAD_KEY_BITMAP_LARGE_OFFSET	12					/**< Start position relative to large square for bitmap */

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

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_util_rect_t invalid_rect;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void mw_ui_keypad_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info);
static void mw_ui_keypad_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_ref The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void mw_ui_keypad_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_keypad_data_t *this_keypad = (mw_ui_keypad_data_t*)mw_get_control_instance_data(control_ref);
	mw_hal_lcd_colour_t highlighted_colour;
	mw_hal_lcd_colour_t lowlighted_colour;
	uint8_t row;
	uint8_t column;
	uint8_t key_size;
	uint8_t text_offset;
	uint8_t bitmap_offset;
	uint8_t c;

	if (mw_get_control_flags(control_ref) & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		key_size = MW_UI_KEYPAD_KEY_LARGE_SIZE;
		mw_gl_set_font(MW_GL_TITLE_FONT);
		text_offset = MW_UI_KEYPAD_KEY_TEXT_LARGE_OFFSET;
		bitmap_offset = MW_UI_KEYPAD_KEY_BITMAP_LARGE_OFFSET;
	}
	else
	{
		key_size = MW_UI_KEYPAD_KEY_SIZE;
		mw_gl_set_font(MW_GL_FONT_9);
		text_offset = MW_UI_KEYPAD_KEY_TEXT_OFFSET;
		bitmap_offset = MW_UI_KEYPAD_KEY_BITMAP_OFFSET;
	}

	/* draw the keys */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_clear_pattern();
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);

	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 3; column++)
		{
			/* set colour of key box fill according to pressed state */
			if (this_keypad->is_key_pressed && (row * 3) + column == this_keypad->key_pressed_number)
			{
				mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
			}
			else
			{
				mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
			}

			/* set fg colour according to control enabled state */
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
					column * key_size,
					row * key_size,
					key_size,
					key_size);

			/* draw key text character */
			c = key_codes[(row * 3) + column];
			if (this_keypad->is_key_pressed && (row * 3) + column == this_keypad->key_pressed_number)
			{
				if (c == '\b')
				{
					mw_gl_monochrome_bitmap(draw_info,
							(column * key_size) + bitmap_offset + 1,
							(row * key_size) + bitmap_offset + 1,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							mw_bitmaps_backspace_key);
				}
				else
				{
					mw_gl_character(draw_info,
							(column * key_size) + text_offset + 1,
							(row * key_size) + text_offset + 1,
							c);
				}
			}
			else
			{
				if (c == '\b')
				{
					mw_gl_monochrome_bitmap(draw_info,
							(column * key_size) + bitmap_offset,
							(row * key_size) + bitmap_offset,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							mw_bitmaps_backspace_key);
				}
				else
				{
					mw_gl_character(draw_info,
							(column * key_size) + text_offset,
							(row * key_size) + text_offset,
							c);
				}
			}

			/* draw 3d effect */
			if (this_keypad->is_key_pressed && (row * 3) + column == this_keypad->key_pressed_number)
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
					(column * key_size) + 1,
					(row * key_size) + 1,
					((row + 1) * key_size) - 2);
			mw_gl_hline(draw_info,
					(column * key_size) + 1,
					((column + 1) * key_size) - 2,
					(row * key_size) + 1);

			mw_gl_set_fg_colour(lowlighted_colour);
			mw_gl_vline(draw_info,
					((column + 1) * key_size) - 2,
					(row * key_size) + 1,
					((row + 1) * key_size) - 2);
			mw_gl_hline(draw_info,
					(column * key_size) + 1,
					((column + 1) * key_size) - 2,
					((row + 1) * key_size) - 2);
		}
	}

	/* special handling for negative sign which can be disabled */
	if (!this_keypad->enable_negative)
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		mw_gl_character(draw_info,
				(0 * key_size) + MW_UI_KEYPAD_KEY_TEXT_OFFSET,
				(3 * key_size) + MW_UI_KEYPAD_KEY_TEXT_OFFSET,
				'-');
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void mw_ui_keypad_message_function(const mw_message_t *message)
{
	mw_ui_keypad_data_t *this_keypad = (mw_ui_keypad_data_t*)mw_get_control_instance_data(message->recipient_id);
	uint8_t key_pressed_row;
	uint8_t key_pressed_column;
	uint8_t key_size;

	if (mw_get_control_flags(message->recipient_id) & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		key_size = MW_UI_KEYPAD_KEY_LARGE_SIZE;
	}
	else
	{
		key_size = MW_UI_KEYPAD_KEY_SIZE;
	}

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */		
		this_keypad->is_key_pressed = false;
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		/* set key pressed to false */
		this_keypad->is_key_pressed = false;

		/* repaint pressed key area only */
		invalid_rect.x = (this_keypad->key_pressed_number % 3) * key_size;
		invalid_rect.y = (this_keypad->key_pressed_number / 3) * key_size;
		invalid_rect.width = key_size;
		invalid_rect.height = key_size;
		mw_paint_control_rect(message->recipient_id, &invalid_rect);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */
		if (mw_get_control_flags(message->recipient_id) & MW_CONTROL_FLAG_IS_ENABLED)
		{
			/* get key pressed number */
			key_pressed_column = (message->message_data >> 16) / key_size;
			key_pressed_row = (message->message_data & 0xffff) / key_size;
			this_keypad->key_pressed_number = (key_pressed_row * 3) + key_pressed_column;

			/* special handling for negative key which can be disabled */
			if (!(this_keypad->key_pressed_number == 9 && !this_keypad->enable_negative))
			{
				/* set up for key up redraw after timer expired */
				mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_id, MW_CONTROL_MESSAGE);
				this_keypad->is_key_pressed = true;

				/* post message for keypress */
				mw_post_message(MW_KEY_PRESSED_MESSAGE,
						message->recipient_id,
						mw_get_control_parent_window(message->recipient_id),
						(uint32_t)key_codes[this_keypad->key_pressed_number],
						MW_WINDOW_MESSAGE);

				/* repaint pressed key area only */
				invalid_rect.x = key_pressed_column * key_size;
				invalid_rect.y = key_pressed_row * key_size;
				invalid_rect.width = key_size;
				invalid_rect.height = key_size;
				mw_paint_control_rect(message->recipient_id, &invalid_rect);
			}
			break;
		}

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

uint8_t mw_ui_keypad_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_keypad_data_t *keypad_instance_data)
{
	mw_util_rect_t r;

	if (flags & MW_CONTROL_FLAGS_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, MW_UI_KEYPAD_KEY_LARGE_SIZE * 3, MW_UI_KEYPAD_KEY_LARGE_SIZE * 4);
	}
	else
	{
		mw_util_set_rect(&r, x, y, MW_UI_KEYPAD_KEY_SIZE * 3, MW_UI_KEYPAD_KEY_SIZE * 4);
	}

	return mw_add_control(&r,
			parent,
			mw_ui_keypad_paint_function,
			mw_ui_keypad_message_function,
			flags,
			keypad_instance_data);
}
