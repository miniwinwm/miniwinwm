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

#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

static const char key_codes[] = 				"789456123-0\b";	/**< The actual characters represented by each key going across columns then down rows */
#define MW_UI_KEYPAD_KEY_TEXT_OFFSET 			7					/**< Start position relative to square for character */
#define MW_UI_KEYPAD_KEY_TEXT_LARGE_OFFSET 		14					/**< Start position relative to large square for large character */
#define MW_UI_KEYPAD_KEY_BITMAP_SIZE			16U					/**< Backspace symbol bitmap size */
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

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void keypad_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void keypad_message_function(const mw_message_t *message);
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
static void keypad_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_keypad_data_t *this_keypad = (mw_ui_keypad_data_t*)mw_get_control_instance_data(control_handle);
	mw_hal_lcd_colour_t highlighted_colour;
	mw_hal_lcd_colour_t lowlighted_colour;
	uint8_t row;
	uint8_t column;
	int8_t text_offset;
	int8_t bitmap_offset;
	uint8_t c;

	if (mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		text_offset = MW_UI_KEYPAD_KEY_TEXT_LARGE_OFFSET;
		bitmap_offset = MW_UI_KEYPAD_KEY_BITMAP_LARGE_OFFSET;
	}
	else
	{
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

	for (row = 0U; row < 4U; row++)
	{
		for (column = 0U; column < 3U; column++)
		{
			/* set colour of key box fill according to pressed state */
			if (this_keypad->is_key_pressed && row == this_keypad->key_pressed_row && column == this_keypad->key_pressed_column)
			{
				mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
			}
			else
			{
				mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
			}

			/* set fg colour according to control enabled state */
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
					column * this_keypad->key_size,
					row * this_keypad->key_size,
					this_keypad->key_size,
					this_keypad->key_size);

			/* draw key text character */
			c = key_codes[(row * 3) + column];
			if (this_keypad->is_key_pressed && row == this_keypad->key_pressed_row && column == this_keypad->key_pressed_column)
			{
				if (c == '\b')
				{
					mw_gl_monochrome_bitmap(draw_info,
							(column * this_keypad->key_size) + bitmap_offset + 1U,
							(row * this_keypad->key_size) + bitmap_offset + 1U,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							mw_bitmaps_backspace_key);
				}
				else
				{
					mw_gl_character(draw_info,
							(column * this_keypad->key_size) + text_offset + 1U,
							(row * this_keypad->key_size) + text_offset + 1U,
							c);
				}
			}
			else
			{
				if (c == '\b')
				{
					mw_gl_monochrome_bitmap(draw_info,
							(column * this_keypad->key_size) + bitmap_offset,
							(row * this_keypad->key_size) + bitmap_offset,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							MW_UI_KEYPAD_KEY_BITMAP_SIZE,
							mw_bitmaps_backspace_key);
				}
				else
				{
					mw_gl_character(draw_info,
							(column * this_keypad->key_size) + text_offset,
							(row * this_keypad->key_size) + text_offset,
							c);
				}
			}

			/* draw 3d effect */
			if (this_keypad->is_key_pressed && row == this_keypad->key_pressed_row && column == this_keypad->key_pressed_column)
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
					(column * this_keypad->key_size) + 1U,
					(row * this_keypad->key_size) + 1U,
					((row + 1U) * this_keypad->key_size) - 2U);
			mw_gl_hline(draw_info,
					(column * this_keypad->key_size) + 1U,
					((column + 1U) * this_keypad->key_size) - 2U,
					(row * this_keypad->key_size) + 1);

			mw_gl_set_fg_colour(lowlighted_colour);
			mw_gl_vline(draw_info,
					((column + 1U) * this_keypad->key_size) - 2U,
					(row * this_keypad->key_size) + 1U,
					((row + 1U) * this_keypad->key_size) - 2U);
			mw_gl_hline(draw_info,
					(column * this_keypad->key_size) + 1U,
					((column + 1U) * this_keypad->key_size) - 2U,
					((row + 1U) * this_keypad->key_size) - 2U);
		}
	}

	/* special handling for negative sign which can be disabled */
	if (!this_keypad->enable_negative)
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		mw_gl_character(draw_info,
				(0U * this_keypad->key_size) + text_offset,
				(3U * this_keypad->key_size) + text_offset,
				'-');
	}
}

/**
 * Process a keypress, either as a new touch down or a hold down from a previous touch down
 *
 * @param message Message passed in from message handler that calls this function
 */
static void process_keypress(const mw_message_t *message)
{
	mw_ui_keypad_data_t *this_keypad = (mw_ui_keypad_data_t*)mw_get_control_instance_data(message->recipient_handle);

	/* special handling for negative key which can be disabled */
	if (!(this_keypad->key_pressed_row == 3U && this_keypad->key_pressed_column == 0U && !this_keypad->enable_negative))
	{
		/* post message for keypress */
		mw_post_message(MW_KEY_PRESSED_MESSAGE,
				message->recipient_handle,
				mw_get_control_parent_window_handle(message->recipient_handle),
				(uint32_t)key_codes[(this_keypad->key_pressed_row * 3U) + this_keypad->key_pressed_column],
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_WINDOW_MESSAGE);

		/* repaint pressed key area only */
		this_keypad->invalid_rect.x = this_keypad->key_pressed_column * this_keypad->key_size;
		this_keypad->invalid_rect.y = this_keypad->key_pressed_row * this_keypad->key_size;
		mw_paint_control_rect(message->recipient_handle, &this_keypad->invalid_rect);
	}
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void keypad_message_function(const mw_message_t *message)
{
	mw_ui_keypad_data_t *this_keypad = (mw_ui_keypad_data_t*)mw_get_control_instance_data(message->recipient_handle);

	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */		
		this_keypad->is_key_pressed = false;
		this_keypad->holding_down = false;
		this_keypad->timer_handle = MW_INVALID_HANDLE;
		if (mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_LARGE_SIZE)
		{
			this_keypad->key_size = MW_UI_KEYPAD_KEY_LARGE_SIZE;
		}
		else
		{
			this_keypad->key_size = MW_UI_KEYPAD_KEY_SIZE;
		}
		this_keypad->invalid_rect.width = this_keypad->key_size;
		this_keypad->invalid_rect.height = this_keypad->key_size;
		break;

	case MW_TOUCH_DRAG_MESSAGE:
	case MW_TOUCH_HOLD_DOWN_MESSAGE:
		if (!(mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED))
		{
			break;
		}

		if (!this_keypad->is_key_pressed)
		{
			break;
		}

		mw_cancel_timer(this_keypad->timer_handle);
		this_keypad->holding_down = true;
		if (mw_tick_counter - this_keypad->touch_down_time > MW_HOLD_DOWN_DELAY_TICKS)
		{
			process_keypress(message);
		}
		break;

	case MW_TIMER_MESSAGE:
		/* set key pressed to false */
		this_keypad->is_key_pressed = false;

		/* repaint pressed key area only */
		mw_paint_control_rect(message->recipient_handle, &this_keypad->invalid_rect);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */
		if (!(mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_IS_ENABLED))
		{
			break;
		}

		/* get key pressed number */
		this_keypad->key_pressed_column = (message->message_data >> 16U) / this_keypad->key_size;
		this_keypad->key_pressed_row = (message->message_data & 0xffffU) / this_keypad->key_size;

		this_keypad->touch_down_time = mw_tick_counter;
		this_keypad->timer_handle = mw_set_timer(mw_tick_counter + MW_KEY_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
		this_keypad->is_key_pressed = true;
		process_keypress(message);
		break;


	case MW_TOUCH_UP_MESSAGE:
		if (this_keypad->holding_down)
		{
			this_keypad->holding_down = false;
			this_keypad->timer_handle = mw_set_timer(mw_tick_counter + MW_KEY_DOWN_TIME, message->recipient_handle, MW_CONTROL_MESSAGE);
		}
		break;

	default:
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_keypad_add_new(int16_t x,
		int16_t y,
		mw_handle_t parent_handle,
		uint32_t flags,
		mw_ui_keypad_data_t *keypad_instance_data)
{
	mw_util_rect_t r;

	if (flags & MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_util_set_rect(&r, x, y, MW_UI_KEYPAD_KEY_LARGE_SIZE * 3, MW_UI_KEYPAD_KEY_LARGE_SIZE * 4);
	}
	else
	{
		mw_util_set_rect(&r, x, y, MW_UI_KEYPAD_KEY_SIZE * 3, MW_UI_KEYPAD_KEY_SIZE * 4);
	}

	return mw_add_control(&r,
			parent_handle,
			keypad_paint_function,
			keypad_message_function,
			flags,
			keypad_instance_data);
}
