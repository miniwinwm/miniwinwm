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
#include "user/minwin_config.h"
#include "ui/ui_int_number_chooser.h"

/****************
*** CONSTANTS ***
****************/

static const mw_util_rect_t input_text_rect = {0, 0, MW_UI_INT_NUMBER_CHOOSER_WIDTH, MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE};

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

void mw_ui_int_number_chooser_paint_function(uint8_t control_ref, const mw_gl_draw_info_t *draw_info)
{
	mw_ui_int_number_chooser_data_t *this_int_number_chooser = (mw_ui_int_number_chooser_data_t*)mw_get_control_instance_data(control_ref);
	uint8_t i;
	char c;
	uint16_t cursor_x_coordinate;
	mw_hal_lcd_colour_t highlighted_colour;
	mw_hal_lcd_colour_t lowlighted_colour;

	/* draw the keys */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_clear_pattern();
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	for (i = 0; i < MW_UI_INT_NUMBER_CHOOSER_KEY_COUNT; i++)
	{
		/* set colour of key box fill according to pressed state */
		if (this_int_number_chooser->is_key_pressed && i == this_int_number_chooser->key_pressed_number)
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
				i * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE,
				MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE,
				MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE,
				MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE);

		/* draw 3d effect */
		if (this_int_number_chooser->is_key_pressed && i == this_int_number_chooser->key_pressed_number)
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
				i * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + 1,
				MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + 1,
				2 * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2);
		mw_gl_hline(draw_info,
				i * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + 1,
				(i + 1) * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2,
				MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + 1);
		mw_gl_set_fg_colour(lowlighted_colour);
		mw_gl_vline(draw_info,
				(i + 1) * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2,
				MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + 1,
				2 * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2);
		mw_gl_hline(draw_info,
				i * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + 1,
				(i + 1) * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2,
				2 * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2);

		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		if (i < 10)
		{
			/* set key text character for numbers */
			c = '0' + i;
		}
		else if (i == 10)
		{
			/* set key text character for '-', disabled if begative numbers not allowed */
			if (this_int_number_chooser->is_only_positive)
			{
				mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
			}
			c = '-';
		}
		else
		{
			c = ' ';
		}
		
		/* draw key text character */
		if (this_int_number_chooser->is_key_pressed && i == this_int_number_chooser->key_pressed_number)
		{
			mw_gl_character(draw_info,
					i * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_TEXT_OFFSET + 1,
					MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_TEXT_OFFSET + 1,
					c);
		}
		else
		{
			mw_gl_character(draw_info,
					i * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_TEXT_OFFSET,
					MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_TEXT_OFFSET,
					c);
		}
	}

	mw_gl_monochrome_bitmap(draw_info,
			11 * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_OFFSET,
			MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_OFFSET,
			MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_SIZE,
			MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_SIZE,
			mw_bitmaps_backspace_key);

	mw_gl_monochrome_bitmap(draw_info,
			12 * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_OFFSET,
			MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_OFFSET,
			MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_SIZE,
			MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_SIZE,
			mw_bitmaps_cancel_key);

	mw_gl_monochrome_bitmap(draw_info,
			13 * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_OFFSET,
			MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE + MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_OFFSET,
			MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_SIZE,
			MW_UI_INT_NUMBER_CHOOSER_KEY_BITMAP_SIZE,
			mw_bitmaps_ok_key);

	/* draw the box the number is displayed in */
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_rectangle(draw_info, 0, 0, MW_UI_INT_NUMBER_CHOOSER_WIDTH, MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE);

	/* draw 3d effect */
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info,
			1,
			1,
			MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2);
	mw_gl_hline(draw_info,
			1,
			MW_UI_INT_NUMBER_CHOOSER_WIDTH - 2,
			1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info,
			MW_UI_INT_NUMBER_CHOOSER_WIDTH - 2,
			1,
			MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2);
	mw_gl_hline(draw_info,
			1,
			MW_UI_INT_NUMBER_CHOOSER_WIDTH - 2,
			MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE - 2);

	cursor_x_coordinate = 2 + this_int_number_chooser->cursor_position * MW_GL_STANDARD_CHARACTER_WIDTH;

	/* draw the number */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	if (this_int_number_chooser->is_negative && strcmp(this_int_number_chooser->number_buffer, "0") !=0)
	{
		/* draw negative sign and number */
		mw_gl_character(draw_info, 3, 4, '-');
		mw_gl_string(draw_info, 3 + MW_GL_STANDARD_CHARACTER_WIDTH, 4, this_int_number_chooser->number_buffer);
		cursor_x_coordinate += MW_GL_STANDARD_CHARACTER_WIDTH;
	}
	else
	{
		/* draw number only */
		mw_gl_string(draw_info, 3, 4, this_int_number_chooser->number_buffer);
	}

	/* draw cursor */
	if (this_int_number_chooser->draw_cursor)
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		mw_gl_vline(draw_info,
				cursor_x_coordinate,
				2,
				MW_GL_STANDARD_CHARACTER_HEIGHT + 4);
	}
}

void mw_ui_int_number_chooser_message_function(const mw_message_t *message)
{
	mw_ui_int_number_chooser_data_t *this_int_number_chooser = (mw_ui_int_number_chooser_data_t*)mw_get_control_instance_data(message->recipient_id);
	uint32_t chosen_number;

	MW_ASSERT(message);

	switch (message->message_id)
	{
	case MW_CONTROL_CREATED_MESSAGE:
		/* initialise the control */		
		this_int_number_chooser->is_key_pressed = false;
		this_int_number_chooser->is_negative = false;
		strcpy(this_int_number_chooser->number_buffer, "0");
		this_int_number_chooser->draw_cursor = false;
		this_int_number_chooser->cursor_position = 0;
		break;

	case MW_CONTROL_GAINED_FOCUS_MESSAGE:
		this_int_number_chooser->timer_id = mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND, message->recipient_id, MW_CONTROL_MESSAGE);
		break;

	case MW_CONTROL_LOST_FOCUS_MESSAGE:
		mw_cancel_timer(this_int_number_chooser->timer_id);
		break;

	case MW_TRANSFER_DATA_1_MESSAGE:
		/* handle a transfer data message, which contains new number */
		if ((int32_t)message->message_data < 0)
		{
			this_int_number_chooser->is_negative = true;
			sprintf(this_int_number_chooser->number_buffer, "%u", abs(message->message_data));
		}
		else
		{
			this_int_number_chooser->is_negative = false;
			sprintf(this_int_number_chooser->number_buffer, "%u", (unsigned int)message->message_data);
		}
		this_int_number_chooser->cursor_position = strlen(this_int_number_chooser->number_buffer);
		break;

	case MW_WINDOW_TIMER_MESSAGE:
		if (this_int_number_chooser->is_key_pressed)
		{
			/* set key pressed to false */
			this_int_number_chooser->is_key_pressed = false;

			/* repaint pressed key area only */
			invalid_rect.x = this_int_number_chooser->key_pressed_number * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
			invalid_rect.y = MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
			invalid_rect.width = MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
			invalid_rect.height = MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
			mw_paint_control_rect(message->recipient_id, &invalid_rect);
		}
		else
		{
			this_int_number_chooser->draw_cursor = !this_int_number_chooser->draw_cursor;

			/* repaint cursor area only */
			invalid_rect.x = 2 + this_int_number_chooser->cursor_position * MW_GL_STANDARD_CHARACTER_WIDTH;
			if (this_int_number_chooser->is_negative)
			{
				invalid_rect.x += MW_GL_STANDARD_CHARACTER_WIDTH;
			}
			invalid_rect.y = 2;
			invalid_rect.width = 1;
			invalid_rect.height = MW_GL_STANDARD_CHARACTER_HEIGHT + 4;
			mw_paint_control_rect(message->recipient_id, &invalid_rect);
		}

		/* reset timer for cursor */
		this_int_number_chooser->timer_id = mw_set_timer(mw_tick_counter + MW_CURSOR_PERIOD_TICKS,
				message->recipient_id,
				MW_CONTROL_MESSAGE);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		/* handle a touch down event within this control */
		if (mw_get_control_flags(message->recipient_id) & MW_CONTROL_FLAG_IS_ENABLED)
		{
		    /* check if the y coordinate of the touch point is in the row of keys */
			if ((message->message_data & 0xffff) > MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE)
			{
				/* set up for key up redraw after timer expired */
				mw_cancel_timer(this_int_number_chooser->timer_id);
				mw_set_timer(mw_tick_counter + MW_CONTROL_DOWN_TIME, message->recipient_id, MW_CONTROL_MESSAGE);
				this_int_number_chooser->is_key_pressed = true;
				
				/* get the key number pressed from the x touch coordinate */
				this_int_number_chooser->key_pressed_number = (message->message_data >> 16) / MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
				switch (this_int_number_chooser->key_pressed_number)
				{
				case 0:
					/* if the text buffer only contains a single '0' don't add another */
					if (strcmp(this_int_number_chooser->number_buffer, "0") == 0)
					{
						break;
					}
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
					/* check buffer has space for another character */
					if (strlen(this_int_number_chooser->number_buffer) < MW_UI_INT_NUMBER_CHOOSER_MAX_CHARS)
					{
						/* if buffer contains only '0' then clear it */
						if (strcmp(this_int_number_chooser->number_buffer, "0") == 0)
						{
							this_int_number_chooser->number_buffer[0] = '\0';
							this_int_number_chooser->cursor_position = 0;
						}

						/* add character for latest pressed key */
						memmove(&this_int_number_chooser->number_buffer[this_int_number_chooser->cursor_position + 1],
								&this_int_number_chooser->number_buffer[this_int_number_chooser->cursor_position],
								strlen(this_int_number_chooser->number_buffer) - this_int_number_chooser->cursor_position + 1);
						this_int_number_chooser->number_buffer[this_int_number_chooser->cursor_position] = this_int_number_chooser->key_pressed_number + '0';
						this_int_number_chooser->cursor_position++;
					}
				break;

				case 10:		/* '-' */
					/* - key pressed, just set flag, don't add - character to start of string */
					if (!this_int_number_chooser->is_only_positive)
					{
						this_int_number_chooser->is_negative = !this_int_number_chooser->is_negative;
					}
					break;

				case 11:
					/* backspace key pressed, only enact if there is anything to delete */
					if (this_int_number_chooser->cursor_position > 0)
					{
						memmove(&this_int_number_chooser->number_buffer[this_int_number_chooser->cursor_position - 1],
								&this_int_number_chooser->number_buffer[this_int_number_chooser->cursor_position],
								strlen(this_int_number_chooser->number_buffer) - this_int_number_chooser->cursor_position + 1);

						this_int_number_chooser->cursor_position--;
					}

					/* if all characters deleted add a single non-negative '0' */
					if (strlen(this_int_number_chooser->number_buffer) == 0)
					{
						this_int_number_chooser->is_negative = false;
						strcpy(this_int_number_chooser->number_buffer, "0");
						this_int_number_chooser->cursor_position = 1;
					}
					break;

				case 12:
					/* post cancel control response message */
					mw_post_message(MW_INT_NUMBER_CHOOSER_CANCEL_MESSAGE,
						message->recipient_id,
						mw_get_control_parent_window(message->recipient_id),
						MW_UNUSED_MESSAGE_PARAMETER,
						MW_WINDOW_MESSAGE);
					break;

				case 13:
				    /* ok key so read the entered value (as a positive only) and post result response message */
					sscanf(this_int_number_chooser->number_buffer, "%d", (int *)&chosen_number);

					/* check if the - key has been pressed */
					if (this_int_number_chooser->is_negative)
					{
					    /* number is negative */
						chosen_number = -chosen_number;
					}

					/* post ok control response message */
					mw_post_message(MW_INT_NUMBER_CHOOSER_OK_MESSAGE,
						message->recipient_id,
						mw_get_control_parent_window(message->recipient_id),
						(uint32_t)chosen_number,
						MW_WINDOW_MESSAGE);
					break;

				default:
					break;
				}

				/* repaint pressed key area only */
				invalid_rect.x = this_int_number_chooser->key_pressed_number * MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
				invalid_rect.y = MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
				invalid_rect.width = MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
				invalid_rect.height = MW_UI_INT_NUMBER_CHOOSER_KEY_SIZE;
				mw_paint_control_rect(message->recipient_id, &invalid_rect);
			}
			else
			{
				this_int_number_chooser->cursor_position = (message->message_data >> 16) / MW_GL_STANDARD_CHARACTER_WIDTH;
				if (this_int_number_chooser->is_negative)
				{
					(this_int_number_chooser->cursor_position)--;
				}
				if (this_int_number_chooser->cursor_position > strlen(this_int_number_chooser->number_buffer))
				{
					this_int_number_chooser->cursor_position = strlen(this_int_number_chooser->number_buffer);
				}
			}

			/* repaint text entry area only */
			mw_paint_control_rect(message->recipient_id, &input_text_rect);
		}
		break;

		default:
			break;
	}
}

uint8_t mw_ui_int_number_chooser_add_new(uint16_t x,
		uint16_t y,
		uint8_t parent,
		uint32_t flags,
		mw_ui_int_number_chooser_data_t *int_number_chooser_instance_data)
{
	mw_util_rect_t r;

	mw_util_set_rect(&r, x, y, MW_UI_INT_NUMBER_CHOOSER_WIDTH, MW_UI_INT_NUMBER_CHOOSER_HEIGHT);

	return mw_add_control(&r,
			parent,
			mw_ui_int_number_chooser_paint_function,
			mw_ui_int_number_chooser_message_function,
			flags,
			int_number_chooser_instance_data);
}
