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

#include <string.h>
#include <stdio.h>
#include "miniwin.h"
#include "ui/ui_common.h"
#include "dialogs/dialog_common.h"

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
	uint16_t circle_x;				/**< X coordinate of user touch point which is where to draw circle */
	uint16_t circle_y;				/**< Y coordinate of user touch point which is where to draw circle */
	bool draw_circle;				/**< If the screen has been touched and need to draw the circle */
	uint8_t i;						/**< Value shown in label and progress bar progress */
	char transfer_buffer[10];		/**< Buffer to transfer data to label */
	uint8_t lines_to_scroll;		/**< Number of lines list box is scrolled */
	bool large_controls;			/**< If to show large controls */
} window_test_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern volatile uint32_t mw_tick_counter;
extern mw_handle_t label_1_handle;
extern mw_handle_t progress_bar_1_handle;
extern mw_handle_t list_box_1_handle;
extern mw_handle_t check_box_1_handle;
extern mw_handle_t arrow_1_handle;
extern mw_handle_t button_1_handle;
extern mw_handle_t scroll_bar_vert_1_handle;
extern mw_handle_t scroll_bar_vert_2_handle;
extern mw_handle_t scroll_bar_horiz_1_handle;
extern mw_handle_t list_box_3_handle;
extern mw_handle_t radio_button_1_handle;
extern mw_handle_t check_box_1_large_handle;
extern mw_handle_t arrow_1_large_handle;
extern mw_handle_t button_1_large_handle;
extern mw_handle_t radio_button_1_large_handle;
extern mw_handle_t scroll_bar_vert_1_large_handle;
extern mw_handle_t scroll_bar_vert_2_large_handle;
extern mw_handle_t scroll_bar_horiz_1_large_handle;
extern mw_handle_t label_1_large_handle;
extern mw_handle_t list_box_3_large_handle;
extern mw_ui_scroll_bar_vert_data_t scroll_bar_vert_1_data;
extern mw_ui_scroll_bar_vert_data_t scroll_bar_vert_2_data;
extern mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_1_data;
extern mw_ui_list_box_data_t list_box_3_data;
extern mw_ui_scroll_bar_vert_data_t scroll_bar_vert_1_large_data;
extern mw_ui_scroll_bar_vert_data_t scroll_bar_vert_2_large_data;
extern mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_1_large_data;
extern mw_ui_list_box_data_t list_box_3_large_data;

/**********************
*** LOCAL VARIABLES ***
**********************/

static window_test_data_t window_test_data;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void window_test_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(draw_info, "Null pointer parameter");

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
	if(window_test_data.draw_circle)
	{
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_circle(draw_info, window_test_data.circle_x, window_test_data.circle_y, 25);
	}
}

void window_test_message_function(const mw_message_t *message)
{
	MW_ASSERT(message, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_test_data.lines_to_scroll = 0;
		window_test_data.draw_circle = false;
		window_test_data.i = 0;
		window_test_data.large_controls = false;
		mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		window_test_data.circle_x = message->message_data >> 16;
		window_test_data.circle_y = message->message_data;
		window_test_data.draw_circle = true;

		/* remove pop up list box if visible */
		if (mw_get_control_flags(list_box_1_handle) & MW_CONTROL_FLAG_IS_VISIBLE)
		{
			mw_set_control_visible(list_box_1_handle, false);
			mw_set_menu_bar_enabled_state(message->recipient_handle, true);
			mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_MENU_BAR);
		}
		mw_paint_window_client(message->recipient_handle);
		mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_TITLE_BAR);
		break;

	case MW_BUTTON_PRESSED_MESSAGE:
		window_test_data.large_controls = !window_test_data.large_controls;

		if (window_test_data.large_controls)
		{
			mw_resize_window(message->recipient_handle, 240, 310);

			/* set all standard sized controls invisible and large controls visible */
			mw_set_control_visible(label_1_handle, false);
			mw_set_control_visible(list_box_3_handle, false);
			mw_set_control_visible(check_box_1_handle, false);
			mw_set_control_visible(button_1_handle, false);
			mw_set_control_visible(scroll_bar_vert_1_handle, false);
			mw_set_control_visible(scroll_bar_vert_2_handle, false);
			mw_set_control_visible(scroll_bar_horiz_1_handle, false);
			mw_set_control_visible(radio_button_1_handle, false);
			mw_set_control_visible(arrow_1_handle, false);

			mw_set_control_visible(label_1_large_handle, true);
			mw_set_control_visible(list_box_3_large_handle, true);
			mw_set_control_visible(check_box_1_large_handle, true);
			mw_set_control_visible(button_1_large_handle, true);
			mw_set_control_visible(scroll_bar_vert_1_large_handle, true);
			mw_set_control_visible(scroll_bar_vert_2_large_handle, true);
			mw_set_control_visible(scroll_bar_horiz_1_large_handle, true);
			mw_set_control_visible(radio_button_1_large_handle, true);
			mw_set_control_visible(arrow_1_large_handle, true);
		}
		else
		{
			mw_resize_window(message->recipient_handle, 220, 140);

			/* set all standard sized controls visible and large controls invisible */
			mw_set_control_visible(label_1_handle, true);
			mw_set_control_visible(list_box_3_handle, true);
			mw_set_control_visible(check_box_1_handle, true);
			mw_set_control_visible(button_1_handle, true);
			mw_set_control_visible(scroll_bar_vert_1_handle, true);
			mw_set_control_visible(scroll_bar_vert_2_handle, true);
			mw_set_control_visible(scroll_bar_horiz_1_handle, true);
			mw_set_control_visible(radio_button_1_handle, true);
			mw_set_control_visible(arrow_1_handle, true);

			mw_set_control_visible(label_1_large_handle, false);
			mw_set_control_visible(list_box_3_large_handle, false);
			mw_set_control_visible(check_box_1_large_handle, false);
			mw_set_control_visible(button_1_large_handle, false);
			mw_set_control_visible(scroll_bar_vert_1_large_handle, false);
			mw_set_control_visible(scroll_bar_vert_2_large_handle, false);
			mw_set_control_visible(scroll_bar_horiz_1_large_handle, false);
			mw_set_control_visible(radio_button_1_large_handle, false);
			mw_set_control_visible(arrow_1_large_handle, false);
		}


		/* repaint everything as window sizes have changed */
		mw_paint_all();
		break;

	case MW_MENU_BAR_ITEM_PRESSED_MESSAGE:
	    /* a menu bar item has been pressed */
		if (message->message_data == 1)
		{
			/* second item in menu bar pressed so set pop up list box visible */
			mw_set_control_visible(list_box_1_handle, true);

			/* disable menu bar while list box is showing */
			mw_set_menu_bar_enabled_state(message->recipient_handle, false);

			/* hide the progress bar while the pop up list box is showing as it is overlapped by the pop up list box */
			mw_set_control_visible(progress_bar_1_handle, false);

			/* repaint the window client as controls have changed */
			mw_paint_window_client(message->recipient_handle);

			/* repaint frame to update the menu bar */
			mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_MENU_BAR);
		}
		else if (message->message_data == 2)
		{
			wm_set_window_title(message->recipient_handle, "Changed");
			mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_TITLE_BAR);
		}
		break;

	case MW_CHECKBOX_STATE_CHANGE_MESSAGE:
		/* a check box state has changed */
		if (message->sender_handle == check_box_1_handle)
		{
			if (message->message_data)
			{
				/* create a pop up 2 button dialog */
				mw_create_window_dialog_two_button(20,
						50,
						150,
						"Title",
						"This is a message",
						"Ok",
						"Cancel",
						false,
						message->recipient_handle);
			}
		}
		else if (message->sender_handle == check_box_1_large_handle)
		{
			if (message->message_data)
			{
				/* create a pop up 2 button dialog */
				mw_create_window_dialog_two_button(5,
						25,
						220,
						"Title",
						"This is a message",
						"Ok",
						"Cancel",
						true,
						message->recipient_handle);
			}
		}
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		/* pop up list box item pressed */
		if (message->sender_handle == list_box_1_handle)
		{
			if (message->message_data == 0)
			{
				mw_send_window_to_back(message->recipient_handle);
				mw_paint_all();
			}
			/* re-show the progress bar when pop up list box gone */
			mw_set_control_visible(progress_bar_1_handle, true);

			/* hide the pop up list box */
			mw_set_control_visible(list_box_1_handle, false);

			/* re-enable menu */
			mw_set_menu_bar_enabled_state(message->recipient_handle, true);
			mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_MENU_BAR);
			mw_paint_window_client(message->recipient_handle);
		}
		break;

	case MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:
		/* horizontal scroll bar scrolled */
		if (window_test_data.large_controls)
		{
			mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
					message->recipient_handle,
					scroll_bar_vert_1_large_handle,
					scroll_bar_horiz_1_large_data.scroll_position,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(scroll_bar_vert_1_large_handle);
		}
		else
		{
			mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
					message->recipient_handle,
					scroll_bar_vert_1_handle,
					scroll_bar_horiz_1_data.scroll_position,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(scroll_bar_vert_1_handle);
		}
		break;

	case MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		/* vertical scroll bar scrolled */
		if (message->sender_handle == scroll_bar_vert_2_handle)
		{
			window_test_data.lines_to_scroll = (scroll_bar_vert_2_data.scroll_position *
					(list_box_3_data.number_of_items - list_box_3_data.number_of_lines)) /
					UINT8_MAX;
			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					list_box_3_handle,
					window_test_data.lines_to_scroll,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_3_handle);
		}
		else if (message->sender_handle == scroll_bar_vert_2_large_handle)
		{
			window_test_data.lines_to_scroll = (scroll_bar_vert_2_large_data.scroll_position *
					(list_box_3_large_data.number_of_items - list_box_3_large_data.number_of_lines)) /
					UINT8_MAX;
			mw_post_message(MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					list_box_3_large_handle,
					window_test_data.lines_to_scroll,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
			mw_paint_control(list_box_3_large_handle);
		}
		break;

	case MW_TIMER_MESSAGE:
		window_test_data.i++;
		if (window_test_data.i > 100)
		{
			window_test_data.i = 0;
		}
		sprintf(window_test_data.transfer_buffer, "%d", window_test_data.i);
		if (window_test_data.large_controls)
		{
			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_1_large_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)window_test_data.transfer_buffer,
					MW_CONTROL_MESSAGE);

			mw_paint_control(label_1_large_handle);
		}
		else
		{
			mw_post_message(MW_LABEL_SET_LABEL_TEXT_MESSAGE,
					message->recipient_handle,
					label_1_handle,
					MW_UNUSED_MESSAGE_PARAMETER,
					(void *)window_test_data.transfer_buffer,
					MW_CONTROL_MESSAGE);

			mw_paint_control(label_1_handle);
		}

		mw_post_message(MW_PROGRESS_BAR_SET_PROGRESS_MESSAGE,
				message->recipient_handle,
				progress_bar_1_handle,
				window_test_data.i,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_CONTROL_MESSAGE);

		mw_paint_control(progress_bar_1_handle);
		mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		if (window_test_data.large_controls)
		{
			 mw_create_window_dialog_number_entry(10,
					50,
					"Number entry",
					true,
					-53,
					true,
					message->recipient_handle);
		}
		else
		{
			 mw_create_window_dialog_number_entry(10,
					50,
					"Number entry",
					false,
					53,
					false,
					message->recipient_handle);
		}
		break;

	default:
		break;
	}
}
