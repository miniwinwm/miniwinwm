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

#include <string.h>
#include "miniwin.h"
#include "miniwin_user.h"
#include "window_test.h"

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
	int16_t circle_x;				/**< X coordinate of user touch point which is where to draw circle */
	int16_t circle_y;				/**< Y coordinate of user touch point which is where to draw circle */
	bool draw_circle;				/**< If the screen has been touched and need to draw the circle */
	uint8_t i;						/**< Value shown in label and progress bar progress */
	char transfer_buffer[10];		/**< Buffer to transfer data to label */
	bool large_controls;			/**< If to show large controls */
	uint8_t vert_scroll_bar_large_position;
	uint8_t vert_scroll_bar_position;
} window_test_data_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

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
	MW_ASSERT(draw_info != (void*)0, "Null pointer parameter");

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
	if (window_test_data.draw_circle)
	{
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_YELLOW);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_circle(draw_info, window_test_data.circle_x, window_test_data.circle_y, 25);
	}
}

void window_test_message_function(const mw_message_t *message)
{
	uint32_t temp_uint32;
	static char dialog_2button_title[] = "Title";
	static char dialog_2button_message[] = "This is a message";
	static char ok_button_label[] = "OK";
	static char cancel_button_label[] = "Cancel";
	static char dialog_number_entry_title[] = "Number Entry";

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	switch (message->message_id)
	{
	case MW_WINDOW_CREATED_MESSAGE:
		window_test_data.draw_circle = false;
		window_test_data.i = 0;
		window_test_data.large_controls = false;
		(void)mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND, message->recipient_handle, MW_WINDOW_MESSAGE);
		window_test_data.vert_scroll_bar_large_position = 0;
		window_test_data.vert_scroll_bar_position = 0;
		break;

	case MW_TOUCH_DOWN_MESSAGE:
		temp_uint32 = message->message_data >> 16;
		window_test_data.circle_x = (int16_t)temp_uint32;
		window_test_data.circle_y = (int16_t)message->message_data;
		window_test_data.draw_circle = true;

		/* remove pop up list box if visible */
		if ((mw_get_control_flags(list_box_1_handle) & MW_CONTROL_FLAG_IS_VISIBLE) == MW_CONTROL_FLAG_IS_VISIBLE)
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
			(void)mw_resize_window(message->recipient_handle, 240, 310);

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
			(void)mw_resize_window(message->recipient_handle, 220, 140);

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
		if (message->message_data == 1U)
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
		else if (message->message_data == 2U)
		{
			wm_set_window_title(message->recipient_handle, (char*)&"Changed");
			mw_paint_window_frame(message->recipient_handle, MW_WINDOW_FRAME_COMPONENT_TITLE_BAR);
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_CHECKBOX_STATE_CHANGE_MESSAGE:
		/* a check box state has changed */
		if (message->sender_handle == check_box_1_handle)
		{
			if (message->message_data != 0U)
			{
				/* create a pop up 2 button dialog */
				(void)mw_create_window_dialog_two_button(20,
						50,
						150,
						dialog_2button_title,
						dialog_2button_message,
						ok_button_label,
						cancel_button_label,
						false,
						message->recipient_handle);
			}
		}
		else if (message->sender_handle == check_box_1_large_handle)
		{
			if (message->message_data != 0U)
			{
				/* create a pop up 2 button dialog */
				(void)mw_create_window_dialog_two_button(5,
						25,
						220,
						dialog_2button_title,
						dialog_2button_message,
						ok_button_label,
						cancel_button_label,
						true,
						message->recipient_handle);
			}
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:
		/* pop up list box item pressed */
		if (message->sender_handle == list_box_1_handle)
		{
			if (message->message_data == 0U)
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

	case MW_TOUCH_UP_MESSAGE:
		if (message->sender_handle == scroll_bar_vert_1_handle)
		{
			mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
					message->recipient_handle,
					scroll_bar_horiz_1_handle,
					window_test_data.vert_scroll_bar_position,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(scroll_bar_horiz_1_handle);
		}
		else if (message->sender_handle == scroll_bar_vert_1_large_handle)
		{
			mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
					message->recipient_handle,
					scroll_bar_horiz_1_large_handle,
					window_test_data.vert_scroll_bar_large_position,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(scroll_bar_horiz_1_large_handle);
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:
		if (message->sender_handle == scroll_bar_horiz_1_large_handle)
		{
			mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
					message->recipient_handle,
					scroll_bar_vert_1_large_handle,
					message->message_data,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(scroll_bar_vert_1_large_handle);
		}
		else if (message->sender_handle == scroll_bar_horiz_1_handle)
		{
			mw_post_message(MW_SCROLL_BAR_SET_SCROLL_MESSAGE,
					message->recipient_handle,
					scroll_bar_vert_1_handle,
					message->message_data,
					NULL,
					MW_CONTROL_MESSAGE);
			mw_paint_control(scroll_bar_vert_1_handle);
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE:
		if (message->sender_handle == scroll_bar_vert_2_handle)
		{
			mw_post_message(MW_LIST_BOX_SCROLL_BAR_POSITION_MESSAGE,
					message->recipient_handle,
					list_box_3_handle,
					message->message_data,
					NULL,
					MW_CONTROL_MESSAGE);
		}
		else if (message->sender_handle == scroll_bar_vert_2_large_handle)
		{
			mw_post_message(MW_LIST_BOX_SCROLL_BAR_POSITION_MESSAGE,
					message->recipient_handle,
					list_box_3_large_handle,
					message->message_data,
					NULL,
					MW_CONTROL_MESSAGE);
		}
		else if (message->sender_handle == scroll_bar_vert_1_large_handle)
		{
			window_test_data.vert_scroll_bar_large_position = (uint8_t)message->message_data;
		}
		else if (message->sender_handle == scroll_bar_vert_1_handle)
		{
			window_test_data.vert_scroll_bar_position = (uint8_t)message->message_data;
		}
		else
		{
			/* keep MISRA happy */
		}
		break;

	case MW_TIMER_MESSAGE:
		window_test_data.i++;
		if (window_test_data.i > 100U)
		{
			window_test_data.i = 0U;
		}
		(void)mw_util_safe_itoa((int32_t)window_test_data.i, window_test_data.transfer_buffer, 10, 10, false, 0, ' ');
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
				NULL,
				MW_CONTROL_MESSAGE);

		mw_paint_control(progress_bar_1_handle);
		(void)mw_set_timer(mw_tick_counter + MW_TICKS_PER_SECOND, message->recipient_handle, MW_WINDOW_MESSAGE);
		break;

	case MW_ARROW_PRESSED_MESSAGE:
		if (window_test_data.large_controls)
		{
			 (void)mw_create_window_dialog_number_entry(10,
					50,
					dialog_number_entry_title,
					true,
					-53,
					true,
					message->recipient_handle);
		}
		else
		{
			 (void)mw_create_window_dialog_number_entry(10,
					50,
					dialog_number_entry_title,
					false,
					53,
					false,
					message->recipient_handle);
		}
		break;

	case MW_SCROLLED_CONTROL_NEEDS_PAINTING_HINT_MESSAGE:
		mw_paint_control(message->sender_handle);
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}
