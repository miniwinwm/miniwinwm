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

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_util_rect_t invalid_rect = {0, 0, 0, 1};

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void tabs_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info);
static void tabs_message_function(const mw_message_t *message);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Control paint routine, called by window manager.
 *
 * @param control_handle The control identifier in the array of controls
 * @param draw_info Draw info structure describing offset and clip region
 */
static void tabs_paint_function(mw_handle_t control_handle, const mw_gl_draw_info_t *draw_info)
{
	int16_t tab_start_x;
	int16_t tab_width;
	int16_t i;
	int16_t corner_radius;
	int16_t tabs_height;
	mw_ui_tabs_data_t *this_tabs = (mw_ui_tabs_data_t*)mw_get_control_instance_data(control_handle);

	MW_ASSERT(draw_info != (void*)0, "Null pointer argument");

	if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		mw_gl_set_font(MW_GL_TITLE_FONT);
		corner_radius = MW_UI_TABS_CORNER_LARGE_RADIUS;
		tabs_height = MW_UI_TABS_LARGE_HEIGHT;
	}
	else
	{
		mw_gl_set_font(MW_GL_FONT_9);
		corner_radius = MW_UI_TABS_CORNER_RADIUS;
		tabs_height = MW_UI_TABS_HEIGHT;
	}

	if (this_tabs->number_of_tabs > 0)
	{
		tab_width = mw_get_control_rect(control_handle).width / this_tabs->number_of_tabs;
	}
	else
	{
		MW_ASSERT((bool)false, "Bad number of tabs");
		return;
	}

    /* fill the background rectangle which shows above tabs */
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_set_solid_fill_colour(this_tabs->background_colour);
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_get_control_rect(control_handle).width,
			MW_UI_TABS_Y_OFFSET + corner_radius);

	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_solid_fill_colour(this_tabs->foreground_colour);
	mw_gl_set_text_rotation(MW_GL_TEXT_ROTATION_0);
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);

	/* draw each tab */
	for (i = 0; i < this_tabs->number_of_tabs; i++)
	{
		/* calculate the start x coordinate of next tab */
		tab_start_x = tab_width * i;

		/* fill in main block */
		mw_gl_rectangle(draw_info,
				tab_start_x,
				MW_UI_TABS_Y_OFFSET + corner_radius,
				tab_width,
				mw_get_control_rect(control_handle).height - (MW_UI_TABS_Y_OFFSET + corner_radius));

		/* fill in block above main block between curved corners */
		mw_gl_rectangle(draw_info,
				tab_start_x + corner_radius,
				MW_UI_TABS_Y_OFFSET,
				tab_width - 2 * corner_radius,
				corner_radius);

		/* fill in left curved corner */
		mw_gl_segment(draw_info, tab_start_x + corner_radius, corner_radius + MW_UI_TABS_Y_OFFSET, corner_radius + 1, 270, 360);

		/* draw left edge */
		mw_gl_vline(draw_info, tab_start_x, corner_radius + MW_UI_TABS_Y_OFFSET, tabs_height - 1);

		/* draw border of left curved corner */
		mw_gl_arc(draw_info, tab_start_x + corner_radius, corner_radius + MW_UI_TABS_Y_OFFSET, corner_radius, 270, 360);

		/* right hand tab needs special case as it may be a 1 to number of tabs pixels wider than others */
		if (i == this_tabs->number_of_tabs - 1)
		{
			/* fill in right curved corner of right tab */
			mw_gl_segment(draw_info,
					mw_get_control_rect(control_handle).width - 1 - corner_radius,
					corner_radius + MW_UI_TABS_Y_OFFSET,
					corner_radius + 1,
					0,
					90);

			/* draw border of right curved corner of right tab */
			mw_gl_arc(draw_info,
					mw_get_control_rect(control_handle).width - 1 - corner_radius,
					corner_radius + MW_UI_TABS_Y_OFFSET,
					corner_radius,
					0,
					90);
		}
		else
		{
			/* fill in right curved corner of not right tab */
			mw_gl_segment(draw_info,
					tab_start_x + tab_width - corner_radius,
					corner_radius + MW_UI_TABS_Y_OFFSET,
					corner_radius + 1,
					0,
					90);

			/* draw border of right curved corner of not right tab */
			mw_gl_arc(draw_info,
					tab_start_x + tab_width - corner_radius,
					corner_radius + MW_UI_TABS_Y_OFFSET,
					corner_radius,
					0,
					90);
		}

		/* draw bottom line of each tab */
		if (i != (int16_t)this_tabs->selection)
		{
			mw_gl_hline(draw_info, i * tab_width, (i + 1) * tab_width, tabs_height - 1);
		}

		/* draw top line of each tab */
		mw_gl_hline(draw_info, i * tab_width + corner_radius, (i + 1) * tab_width - corner_radius, MW_UI_TABS_Y_OFFSET);

		/* draw label in each tab */
		if ((mw_get_control_flags(control_handle) & MW_CONTROL_FLAG_IS_ENABLED) == 0U)
		{
			mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
		}
		mw_gl_string(draw_info, tab_start_x + MW_UI_TABS_LABEL_X_OFFSET, MW_UI_TABS_LABEL_Y_OFFSET, this_tabs->tabs_labels[i]);
	}

	/* draw the right hand edge of the last tab */
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_vline(draw_info, mw_get_control_rect(control_handle).width - 1, corner_radius + 2, tabs_height - 1);
}

/**
 * Control message handler called by the window manager.
 *
 * @param message The message to be processed
 */
static void tabs_message_function(const mw_message_t *message)
{
	int16_t tab_width;
	mw_ui_tabs_data_t *this_tabs;

	MW_ASSERT(message != (void*)0, "Null pointer argument");

	this_tabs = (mw_ui_tabs_data_t *)mw_get_control_instance_data(message->recipient_handle);

	switch (message->message_id)
	{
	case MW_TOUCH_DOWN_MESSAGE:
		if (this_tabs->number_of_tabs > 0)
		{
			tab_width = mw_get_control_rect(message->recipient_handle).width / this_tabs->number_of_tabs;
			this_tabs->selection = (uint8_t)((message->message_data >> 16) / (uint32_t)tab_width);

			/* only get bottom line of tabs control repainted, rest hasn't changed */
			if ((mw_get_control_flags(message->recipient_handle) & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
			{
				invalid_rect.y = MW_UI_TABS_LARGE_HEIGHT - 1;
			}
			else
			{
				invalid_rect.y = MW_UI_TABS_HEIGHT - 1;
			}
			invalid_rect.width = mw_get_control_rect(message->recipient_handle).width;
			mw_paint_control_rect(message->recipient_handle, &invalid_rect);

			mw_post_message(MW_TAB_SELECTED_MESSAGE,
					message->recipient_handle,
					mw_get_control_parent_window_handle(message->recipient_handle),
					(uint32_t)this_tabs->selection,
					NULL,
					MW_WINDOW_MESSAGE);
		}
		else
		{
			MW_ASSERT((bool)false, "Bad number of tabs");
		}
		break;

	case MW_CONTROL_PARENT_WINDOW_RESIZED_MESSAGE:
		if (this_tabs->automatic == true)
		{
			(void)mw_resize_control(message->recipient_handle,
					mw_get_window_client_rect(mw_get_control_parent_window_handle(message->recipient_handle)).width,
					mw_get_control_rect(message->recipient_handle).height);
		}
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_ui_tabs_add_new(int16_t x,
		int16_t y,
		int16_t width,
		mw_handle_t parent_handle,
		uint16_t flags,
		mw_ui_tabs_data_t *tabs_instance_data)
{
	mw_util_rect_t r;
	int16_t i;

	/* check for null parameters */
	if (tabs_instance_data == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (MW_INVALID_HANDLE);
	}

	/* check for number of tabs */
	if (tabs_instance_data->number_of_tabs < 1)
	{
		MW_ASSERT((bool)false, "Invalid argument");
		return (MW_INVALID_HANDLE);
	}

	/* check for null pointers in tab labels */
	for (i = 0; i < tabs_instance_data->number_of_tabs; i++)
	{
		if (tabs_instance_data->tabs_labels[i] == NULL)
		{
			MW_ASSERT((bool)false, "Null pointer value in array");
			return (MW_INVALID_HANDLE);
		}
	}

	if ((flags & MW_CONTROL_FLAG_LARGE_SIZE) == MW_CONTROL_FLAG_LARGE_SIZE)
	{
		if (tabs_instance_data->automatic == true)
		{
			mw_util_set_rect(&r, 0, 0, mw_get_window_client_rect(parent_handle).width, MW_UI_TABS_LARGE_HEIGHT);
		}
		else
		{
			mw_util_set_rect(&r, x, y, width, MW_UI_TABS_LARGE_HEIGHT);
		}
	}
	else
	{
		if (tabs_instance_data->automatic == true)
		{
			mw_util_set_rect(&r, 0, 0, mw_get_window_client_rect(parent_handle).width, MW_UI_TABS_HEIGHT);
		}
		else
		{
			mw_util_set_rect(&r, x, y, width, MW_UI_TABS_HEIGHT);
		}
	}

	tabs_instance_data->selection = 0U;

	return (mw_add_control(&r,
			parent_handle,
			tabs_paint_function,
			tabs_message_function,
			flags,
			tabs_instance_data));
}

uint8_t mw_ui_tabs_get_selection(mw_handle_t tabs_handle)
{
	mw_ui_tabs_data_t *tabs_data = (mw_ui_tabs_data_t *)mw_get_control_instance_data(tabs_handle);

	if (tabs_data != NULL)
	{
		return (tabs_data->selection);
	}

	return (0U);
}
