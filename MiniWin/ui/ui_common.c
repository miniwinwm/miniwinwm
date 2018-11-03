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
#include <miniwin_debug.h>
#include "user/minwin_config.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_ui_common_post_number_to_control(mw_handle_t control_handle, uint32_t number)
{
	/* check handle for not being invalid handle */
	if (!mw_is_control_handle_valid(control_handle))
	{
		MW_ASSERT(false, "Invalid control handle");
		return;
	}

	mw_post_message(MW_TRANSFER_DATA_1_MESSAGE,
			0,
			control_handle,
			number,
			MW_CONTROL_MESSAGE);
}

void mw_ui_common_post_pointer_to_control(mw_handle_t control_handle, void *pointer)
{
	/* check pointer for non-null */
	if (!pointer)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	/* check handle for not being invalid handle */
	if (!mw_is_control_handle_valid(control_handle))
	{
		MW_ASSERT(false, "Invalid control handle");
		return;
	}

	mw_post_message(MW_TRANSFER_DATA_1_PTR_MESSAGE,
			0,
			control_handle,
			(uint32_t)pointer,
			MW_CONTROL_MESSAGE);
}

uint16_t mw_ui_common_scale_scroll_bar_touch_point(uint16_t scroll_bar_length, int16_t touch_point)
{
	touch_point -= MW_SCROLL_BAR_SLIDER_SIZE / 2;
	if (touch_point < 0)
	{
		touch_point = 0;
	}
	else if (touch_point > scroll_bar_length - MW_SCROLL_BAR_SLIDER_SIZE)
	{
		touch_point = scroll_bar_length - MW_SCROLL_BAR_SLIDER_SIZE;
	}

	return (scroll_bar_length * touch_point) / (scroll_bar_length - MW_SCROLL_BAR_SLIDER_SIZE);
}
