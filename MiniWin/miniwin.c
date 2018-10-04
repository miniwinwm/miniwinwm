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
#include <miniwin_message_queue.h>
#include <miniwin_settings.h>
#include <miniwin_touch.h>
#include <string.h>
#include "hal/hal_init.h"
#include "hal/hal_touch.h"
#include "ui/ui_common.h"

/****************
*** CONSTANTS ***
****************/

const mw_gl_draw_info_t draw_info_root = {0, 0, {0, 0, MW_HAL_LCD_WIDTH, MW_HAL_LCD_HEIGHT}};	/**< Fixed draw info structure for root window */

/************
*** TYPES ***
************/

/**
 * Enumeration of the touch event types
 */
typedef enum
{
	TOUCH_EVENT_DOWN,       						/**< a touch down event has occurred */
	TOUCH_EVENT_UP,         						/**< a touch up event has occurred */
	TOUCH_EVENT_DRAG,								/**< a drag event has occurred */
	TOUCH_EVENT_HOLD_DOWN,							/**< a hold down event has occurred */
	TOUCH_EVENT_NONE        						/**< no touch event outstanding */
} touch_event_t;

/**
 * Window re-dimensioning state - re-dimensioning is when a window is moved or resized
 */
typedef enum
{
	WINDOW_BEING_RESIZED,							/**< window is in process of being resized */
	WINDOW_BEING_MOVED,								/**< window in the process of being moved */
	WINDOW_NOT_BEING_REDIMENSIONED					/**< neither of the above */
} window_redimensioning_state_t;

/**
 * Operations that is specified when the system timer has fired
 */
typedef enum
{
	SYSTEM_TIMER_EVENT_MENU_BAR_REDRAW,				/**< Menu bar animation redraw required when timer expires */
	SYSTEM_TIMER_EVENT_PAINT_ALL					/**< Paint all required when timer expires */
} system_timer_event_t;

/**
 * WIndow timer information structure
 */
typedef struct
{
	uint32_t next_fire_time;        				/**< the time for the timer to go off in window manager ticks; this is an absolute value, not relative */
	uint8_t recipient_id;           				/**< the window or control id of the recipient of the timer fired message */
	mw_message_recipient_type_t recipient_type;   	/**< the type of recipient of timer fired message */
} window_timer_t;

/**
 * System timer information structure
 */
typedef struct
{
	uint32_t next_fire_time;        				/**< the time for the timer to go off in window manager ticks; this is an absolute value, not relative */
	system_timer_event_t system_timer_event;		/**< the operation to execute when timer fires */
	uint32_t data;									/**< any extra data to specify the operation */
} system_timer_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint8_t mw_bitmaps_close_icon[];
extern const uint8_t mw_bitmaps_maximise_icon[];
extern const uint8_t mw_bitmaps_minimise_icon[];
extern const uint8_t mw_bitmaps_resize_icon[];
extern volatile uint32_t mw_tick_counter;

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_window_t mw_all_windows[MW_MAX_WINDOW_COUNT];    	/**< Array of structures describing all the windows */
static mw_control_t mw_all_controls[MW_MAX_CONTROL_COUNT]; 	/**< Array of structures describing all the controls */
static window_timer_t mw_all_timers[MW_MAX_TIMER_COUNT];   	/**< Array of structures describing containing information on all the timers */
static uint8_t window_with_focus = MW_ROOT_WINDOW_ID;		/**< The window at the front with focus receiving touch events within its rect */
static int16_t vertical_edges[(MW_MAX_WINDOW_COUNT) * 2];	/**< Scratch area to store array of vertical window edges, used in various places, for window analysis when repainting */
static int16_t horizontal_edges[(MW_MAX_WINDOW_COUNT) * 2]; /**< Scratch area to store array of horizontal window edges, used in various places, for window analysis when repainting */
static system_timer_t system_timer;							/**< a timer used by the window manager for its own asynchronous events */
static bool in_client_window_paint_function;				/**< set true when calling a client window paint function, false after exiting the client window paint function */

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/* new window functions */
static uint8_t find_empty_window_slot();
static void set_window_details(const mw_util_rect_t *rect,
		char* title,
		mw_paint_func_p paint_function,
		uint8_t window_ref,
		mw_message_func_p message_function,
		char **menu_bar_items,
		uint8_t menu_bar_items_count,
		uint16_t window_flags,
		void *instance_data);
static bool check_window_dimensions(uint16_t new_width,
		uint16_t new_height,
		uint16_t flags);
static void calculate_new_window_size_details(uint8_t window_ref, const mw_util_rect_t *rect);

/* new control functions */
static uint8_t find_empty_control_slot();
static void set_control_details(const mw_util_rect_t *rect,
		mw_paint_func_p paint_func,
		uint8_t control_ref,
		mw_message_func_p message_func,
		uint8_t parent,
		uint16_t control_flags,
		void *instance_data);

/* root window functions */
static void root_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info);
static void root_message_function(const mw_message_t *message);

/* minimized window functions */
static uint8_t find_icon_number_for_window(uint8_t window_ref);
static void find_minimsed_icon_location(uint8_t icon_number, int16_t *x, int16_t *y);
static bool check_for_restore_touch(int16_t x_touch, int16_t y_touch);
static void draw_min_restore_window_effect(uint8_t window_ref);
static void draw_minimised_icons(void);

/* find functions */
static uint8_t find_next_z_order(uint8_t z_order);
static uint8_t find_highest_z_order();
static uint8_t find_window_point_is_in(int16_t point_x, int16_t point_y);
static uint8_t find_control_point_is_in(uint8_t window_ref, int16_t point_x, int16_t point_y);
static void find_rect_window_intersections(const mw_util_rect_t *r, uint16_t *horiz_edges_count, uint16_t *vert_edges_count);
static uint8_t find_highest_z_order_at_point(int16_t x, int16_t y);
static uint8_t find_number_of_displayed_windows();
static bool find_if_rect_is_completely_on_screen(const mw_util_rect_t *rect);
static bool find_if_window_is_overlapped(uint8_t window_ref);

/* window frame draw functions */
static void draw_title_bar(uint8_t window_ref, const mw_gl_draw_info_t *draw_info);
static void draw_titlebar_text(uint8_t window_ref, const mw_gl_draw_info_t *draw_info);
static void draw_menu_bar(const mw_gl_draw_info_t *draw_info, uint8_t window_ref);
static void draw_horizontal_window_scroll_bar(const mw_gl_draw_info_t *draw_info, uint8_t window_ref);
static void draw_vertical_window_scroll_bar(const mw_gl_draw_info_t *draw_info, uint8_t window_ref);

/* paint window/client functions */
static void paint_window_frame_and_client_with_z_order(uint8_t z_order);
static void do_paint_window_frame(uint8_t window_ref, uint8_t components);
static void do_paint_window_frame2(uint8_t window_ref, uint8_t components, const mw_util_rect_t *invalid_rect);
static void do_paint_window_client(uint8_t window_ref);
static void do_paint_window_client_rect(uint8_t window_ref, const mw_util_rect_t *invalid_rect);
static void do_paint_window_client2(uint8_t window_ref, const mw_util_rect_t *invalid_rect);

/* paint control functions */
static void paint_all_controls_in_window(uint8_t window_ref);
static void paint_all_controls_in_window_rect(uint8_t window_ref, const mw_util_rect_t *invalid_rect);
static void do_paint_control_rect(uint8_t control_ref, const mw_util_rect_t *invalid_rect);
static void do_paint_control(uint8_t control_ref);
static void do_paint_control2(uint8_t control_ref, const mw_util_rect_t *invalid_rect);

/* other functions */
static window_redimensioning_state_t process_touch_event(void);
static void do_paint_all();
static void set_focus(void);
static void rationalize_z_orders();
static void draw_redimensioning_window_outline(uint8_t window_ref);
static void set_system_timer(uint32_t timer_data, system_timer_event_t event, uint32_t fire_time);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Find an empty slot in the array of window identifiers for a new window.
 *
 * @return The slot for the new window if one is avaialble or MAX_WINDOW_COUNT if no slot available
 */
static uint8_t find_empty_window_slot()
{
	uint8_t i;

	/* loop through all the windows */
	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* an empty slot is identified by is_used being zero */
	    if (!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED))
	    {
			/* empty slot found */
	        return i;
		}
	}

	return MW_MAX_WINDOW_COUNT;
}

/**
 * Set a windows's details. This is only called when a window is created.
 *
 * @param rect The rect of the window's total area, including border and title bar
 * @param title The text of the title; must not be longer than MAX_TITLE_SIZE
 * @param paint_function Pointer to paint function
 * @param window_ref Position in array of all windows of this window
 * @param message_function Pointer to message handling function
 * @param menu_bar_items Pointer to array holding menu bar item text labels
 * @param menu_bar_items_count Number of entries in above array
 * @param window_flags Flags describing the window and its state
 * @param instance_data Optional pointer to any extra window data that is instance specific, can be NULL if no instance data
*/
static void set_window_details(const mw_util_rect_t *rect,
		char* title,
		mw_paint_func_p paint_func,
		uint8_t window_ref,
		mw_message_func_p message_func,
		char **menu_bar_items,
		uint8_t menu_bar_items_count,
		uint16_t window_flags,
		void *instance_data)
{
	/* check pointers */
	MW_ASSERT(rect);
	MW_ASSERT(title);
	MW_ASSERT(paint_func);
	MW_ASSERT(message_func);
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);
	if (window_flags & MW_WINDOW_HAS_MENU_BAR)
	{
		MW_ASSERT(menu_bar_items);
		MW_ASSERT(*menu_bar_items);
		MW_ASSERT(menu_bar_items_count > 0);
	}

	/* copy in all details to this window's struct in the array of all windows */
	mw_util_safe_strcpy(mw_all_windows[window_ref].title, MW_MAX_TITLE_SIZE, title);
	mw_all_windows[window_ref].paint_func = paint_func;
	mw_all_windows[window_ref].message_func = message_func;
	mw_all_windows[window_ref].window_flags = window_flags | MW_WINDOW_FLAG_IS_USED;
	mw_all_windows[window_ref].menu_bar_items = menu_bar_items;
	mw_all_windows[window_ref].menu_bar_items_count = menu_bar_items_count;
	mw_all_windows[window_ref].menu_bar_item_enables = MW_ALL_ITEMS_ENABLED;
	mw_all_windows[window_ref].window_flags &= ~MW_WINDOW_MENU_BAR_ITEM_IS_SELECTED;
	mw_all_windows[window_ref].horiz_scroll_pos = 0;
	mw_all_windows[window_ref].vert_scroll_pos = 0;
	mw_all_windows[window_ref].instance_data = instance_data;

	/* calculate client area location and size from the chosen features */
	calculate_new_window_size_details(window_ref, rect);
}

/**
 * Check that proposed new window width and height are allowed given the window options 
 *
 * @param new_width The proposed new window width
 * @param new_height The proposed new window height 
 * @param flags The flags used when creating the window that contain its options
 * @return True if allowed else false 
 */
static bool check_window_dimensions(uint16_t new_width,
		uint16_t new_height,
		uint16_t flags)
{
	uint16_t window_minimum_width;
	uint16_t window_minimum_height;

	/* starting point for minimum window width is 1 pixel */
	window_minimum_width = 1;
	if (flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
	{
		/* if a title bar is present then minimum width must give space for the title bar icons */
		window_minimum_width = (MW_TITLE_BAR_ICON_OFFSET * 4 + 1);
	}
	else
	{
		/* no title bar present */
		if (flags & MW_WINDOW_FLAG_HAS_BORDER)
		{
			/* border present so add twice border width */
			window_minimum_width += (MW_BORDER_WIDTH * 2);
		}
		
		/* check for vertical scroll bar */ 
		if (flags & MW_WINDOW_HAS_VERT_SCROLL_BAR)
		{
			/* vertical scroll bar present so add scroll bar width */
			window_minimum_width += MW_SCROLL_BAR_NARROW_DIMESION;
		}
	}

	/* starting point for minimum window height is 1 pixel */
	window_minimum_height = 1;
	if (flags & MW_WINDOW_FLAG_HAS_BORDER)
	{
		/* has border */
		if (flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
		{
			/* title bar present so add title bar height and one border thickness */
			window_minimum_height += (MW_TITLE_BAR_HEIGHT + MW_BORDER_WIDTH);
		}
		else
		{
			/* border present but no title bar so add twice border width */
			window_minimum_height += (MW_BORDER_WIDTH * 2);
		}
	}
	else
	{
		/* no border present */
		if (flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
		{
			/* title bar present so add title bar height */
			window_minimum_height += MW_TITLE_BAR_HEIGHT;
		}
	}
	
	/* check for horizontal scroll bar */
	if (flags & MW_WINDOW_HAS_HORIZ_SCROLL_BAR)
	{
		/* horizontal scroll bar present so add scroll bar height */
		window_minimum_height += MW_SCROLL_BAR_NARROW_DIMESION;
	}
	
	/* check for menu bar */
	if (flags & MW_WINDOW_HAS_MENU_BAR)
	{
		/* menu bar present so add its height */
		window_minimum_height += MW_MENU_BAR_HEIGHT;
	}

	/* now check the new dimensions with the minimums allowed */
	if (new_width < window_minimum_width)
	{
		return false;
	}
	if (new_height < window_minimum_height)
	{
		return false;
	}

	/* requested new dimensions acceptable */
	return true;
}

/**
 * Set a window's client rect from its window rect and border/title bar details
 *
 * @param window_ref The window to set the client rect for
 * @param rect The window's window rect
 */
static void calculate_new_window_size_details(uint8_t window_ref, const mw_util_rect_t *rect)
{
	uint8_t border_width;

	MW_ASSERT(rect);
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	/* set the window rect from that passed in first */
	memcpy(&(mw_all_windows[window_ref].window_rect), rect, sizeof(mw_util_rect_t));

	/* find out border width; depends on if there is a border */
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER)
	{
		border_width = MW_BORDER_WIDTH;
	}
	else
	{
		border_width = 0;
	}

	/* set client rect x */
	mw_all_windows[window_ref].client_rect.x = rect->x + border_width;

	/* set client rect y */
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
	{
		mw_all_windows[window_ref].client_rect.y = rect->y + MW_TITLE_BAR_HEIGHT;
	}
	else
	{
		mw_all_windows[window_ref].client_rect.y = rect->y + border_width;
	}
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_MENU_BAR)
	{
		mw_all_windows[window_ref].client_rect.y += MW_MENU_BAR_HEIGHT;
	}

	/* set client rect width */
	mw_all_windows[window_ref].client_rect.width = rect->width - 2 * border_width;
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_VERT_SCROLL_BAR)
	{
		mw_all_windows[window_ref].client_rect.width -= MW_SCROLL_BAR_NARROW_DIMESION;
	}

	/* set client rect height */
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
	{
		mw_all_windows[window_ref].client_rect.height = rect->height - MW_TITLE_BAR_HEIGHT - border_width;
	}
	else
	{
		mw_all_windows[window_ref].client_rect.height = rect->height - 2 * border_width;
	}
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_MENU_BAR)
	{
		mw_all_windows[window_ref].client_rect.height -= MW_MENU_BAR_HEIGHT;
	}
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_HORIZ_SCROLL_BAR)
	{
		mw_all_windows[window_ref].client_rect.height -= MW_SCROLL_BAR_NARROW_DIMESION;
	}
}

/**
 * Find an empty slot in the array of control identifiers for a new control.
 *
 * @return The slot for the new control if one is avaialble or MAX_CONTROL_COUNT if no slot available
 */
static uint8_t find_empty_control_slot()
{
	uint8_t i;

	/* loop through all controls */
	for (i = 0; i < MW_MAX_CONTROL_COUNT; i++)
	{
		/* an empty slot is identified by is_used being zero */	
	    if (!(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_USED))
	    {
			/* an empty slot has been found */
	        return i;
		}
	}

	return MW_MAX_CONTROL_COUNT;
}

/**
 * Set a control's details. This is only called when a control is created.
 *
 * @param rect The rect of the control's area, position relative ti parent window's client area
 * @param paint_function Pointer to paint function
 * @param control_ref Position in array of all controls of this control
 * @param message_function Pointer to message handling function
 * @param parent The window reference of the control's parent window
 * @param control_flags Flags describing the control and its state
 * @param instance_data Void pointer to control specific data structure containing extra control specific configuration data for this instance
 */
static void set_control_details(const mw_util_rect_t *rect,
		mw_paint_func_p paint_func,
		uint8_t control_ref,
		mw_message_func_p message_func,
		uint8_t parent,
		uint16_t control_flags,
		void *instance_data)
{
	/* check pointers */
	MW_ASSERT(rect);
	MW_ASSERT(paint_func);
	MW_ASSERT(message_func);
	MW_ASSERT(control_ref < MW_MAX_CONTROL_COUNT);
	MW_ASSERT(instance_data);

	/* copy in all details to this control's structs in the array of all controls */
	mw_all_controls[control_ref].control_flags = control_flags | MW_CONTROL_FLAG_IS_USED;
	mw_all_controls[control_ref].paint_func = paint_func;
	mw_all_controls[control_ref].message_func = message_func;
	mw_all_controls[control_ref].parent = parent;
	mw_all_controls[control_ref].instance_data = instance_data;

	/* now make rect's x,y relative to screen rather than window */
	mw_all_controls[control_ref].control_rect.x = rect->x + mw_all_windows[parent].client_rect.x;
	mw_all_controls[control_ref].control_rect.y = rect->y + mw_all_windows[parent].client_rect.y;
	
	/* set control rect's width and height */
	mw_all_controls[control_ref].control_rect.width = rect->width;
	mw_all_controls[control_ref].control_rect.height = rect->height;
}

/**
 * Root paint function. Calls user root window paint function then performs any system root window paint tasks
 *
 * @param window_ref Always ROOT_WINDOW_ID for root window
 * @param draw_info Draw info structure describing offset and clip region
 */
static void root_paint_function(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(window_ref == MW_ROOT_WINDOW_ID);

	/* call user root window paint */
	mw_user_root_paint_function(draw_info);
}

/**
 * Handle a message passed to the root window; if not consumed here pass on to user root window message handler
 *
 * @param message The message to be processed
 *
 */
static void root_message_function(const mw_message_t *message)
{
	bool consumed = false;

	MW_ASSERT(message);

	/* check if the messages sent to the root window is to be consumed by the system */
	switch (message->message_id)
	{
	case MW_TOUCH_DOWN_MESSAGE:
		consumed = check_for_restore_touch(message->message_data >> 16, message->message_data & 0x0000ffffL);
		break;

	default:
		break;
	}

	/* if the system did not consume the message pass it on to the user root window message handler */
	if (!consumed)
	{
		mw_user_root_message_function(message);
	}
}

/**
 * Find a window icon reference number for a window. The window icons are plotted by icon
 * reference number along rows along the bottom of the root window, working right along
 * each row then by rows up the screen.
 *
 * @param window_ref The window to find the icon number for
 * @return The icon number
 */
static uint8_t find_icon_number_for_window(uint8_t window_ref)
{
	uint8_t i;
	uint8_t icon_number = 0;

	/* loop through all windows */
	for (i = 1; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* ignore unused invisible maximised windows */
		if (!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) ||
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) ||
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			continue;
		}

		if (i == window_ref)
		{
			break;
		}

		icon_number++;
	}

	return icon_number;
}

/**
 * Find the icon location on the desktop for icon number next starting at 0
 *
 * @param icon_number The icon number to look for
 * @param X the returned left edge of the icon
 * @param Y the returned top edge of the icon
 */
static void find_minimsed_icon_location(uint8_t icon_number, int16_t *x, int16_t *y)
{
	MW_ASSERT(x);
	MW_ASSERT(y);

	/* column position starts at left of screen and works right across screen */
	*x = (icon_number % MW_DESKTOP_ICONS_PER_ROW) * MW_DESKTOP_ICON_WIDTH;
	
	/* row position starts at bottom of screen and works up screen */
	*y = MW_HAL_LCD_HEIGHT - ((1 + (icon_number / MW_DESKTOP_ICONS_PER_ROW)) * MW_DESKTOP_ICON_HEIGHT);
}

/**
 * Check if a touch down event occurred on a minimised window icon; if it did restore the window
 *
 * @param x_touch The x coordinate of the touch down event to check
 * @param y_touch The y coordinate of the touch down event to check
 * @return If the touch down event was consumed
 */
static bool check_for_restore_touch(int16_t x_touch, int16_t y_touch)
{
	uint8_t i;
	uint8_t minimised_window_count = 0;
	mw_util_rect_t r;
	bool touch_consumed = false;

	/* set unchanging values of icon rect */
	r.width = MW_DESKTOP_ICON_WIDTH;
	r.height = MW_DESKTOP_ICON_HEIGHT;

	/* loop through all user windows */
	for (i = 1; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* ignore unused invisible maximised windows */
		if (!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) ||
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) ||
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			continue;
		}

		/* find the top left location of the next icon */
		find_minimsed_icon_location(minimised_window_count, &r.x, &r.y);
		minimised_window_count++;

		/* check if the touch point is in the next icon location */
		if (mw_util_is_point_in_rect(&r, x_touch, y_touch))
		{
			/* it is, so now restore the window, starting off by drawing the restore animation effect */
			draw_min_restore_window_effect(i);
			
			/* clear minimised status for this window */
			mw_all_windows[i].window_flags &= ~MW_WINDOW_FLAG_IS_MINIMISED;
			
			/* restored windows get brought to the font and given focus */
			mw_bring_window_to_front(i);
			
			/* set the system timer to clear the restored window animation effect */
			set_system_timer(MW_UNUSED_MESSAGE_PARAMETER,
					SYSTEM_TIMER_EVENT_PAINT_ALL,
					mw_tick_counter + MW_WINDOW_MIN_MAX_EFFECT_TIME);
					
			/* let the window know that it has been restored */
			mw_post_message(MW_WINDOW_RESTORED,
					MW_UNUSED_MESSAGE_PARAMETER,
					i,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_WINDOW_MESSAGE);
					
			/* this touch point has now been consumed so won't be passed on to user root message function */
			touch_consumed = true;
			break;
		}
	}

	return touch_consumed;
}

/**
 * Draw the minimising/restoring effect between a window and an icon.
 *
 * @param window_ref The window that is being minimised or restored
 */
static void draw_min_restore_window_effect(uint8_t window_ref)
{
	int16_t x;
	int16_t y;
	uint8_t icon_number = find_icon_number_for_window(window_ref);

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	find_minimsed_icon_location(icon_number, &x, &y);

	mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_line(MW_GL_LARGE_DASH_LINE);
	mw_gl_line(&draw_info_root,
			mw_all_windows[window_ref].window_rect.x,
			mw_all_windows[window_ref].window_rect.y,
			x,
			y);
	mw_gl_line(&draw_info_root,
			mw_all_windows[window_ref].window_rect.x + mw_all_windows[window_ref].window_rect.width,
			mw_all_windows[window_ref].window_rect.y,
			x + MW_DESKTOP_ICON_WIDTH,
			y);
	mw_gl_line(&draw_info_root,
			mw_all_windows[window_ref].window_rect.x,
			mw_all_windows[window_ref].window_rect.y,
			mw_all_windows[window_ref].window_rect.x +  mw_all_windows[window_ref].window_rect.width,
			mw_all_windows[window_ref].window_rect.y);
}

/**
 * Draw icons at the bottom of the root window for the used visible but minimised windows.
 */
static void draw_minimised_icons(void)
{
	uint8_t i;
	mw_util_rect_t r;
	uint8_t minimised_window_count = 0;
	uint16_t horiz_edges_count;
	uint16_t vert_edges_count;
	uint16_t horizontal_edge_counter;
	uint16_t vertical_edge_counter;
	mw_gl_draw_info_t draw_info;

	/* set unchanging values of icon rect */
	r.width = MW_DESKTOP_ICON_WIDTH;
	r.height = MW_DESKTOP_ICON_HEIGHT;

	/* loop through all user windows */
	for (i = 1; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* ignore unused invisible maximised windows */
		if (!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) ||
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE)
				|| !(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			continue;
		}

		/* window needs an icon so find its location to draw */
		find_minimsed_icon_location(minimised_window_count, &r.x, &r.y);
		draw_info.origin_x = r.x;
		draw_info.origin_y = r.y;
		minimised_window_count++;

		find_rect_window_intersections(&r, &horiz_edges_count, &vert_edges_count);

		/* draw rectangle and label */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_clear_pattern();
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_GREY5);
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

		for (horizontal_edge_counter = 0; horizontal_edge_counter < horiz_edges_count - 1; horizontal_edge_counter++)
		{
			draw_info.clip_rect.y = horizontal_edges[horizontal_edge_counter] - draw_info.origin_y;

			/* iterate through vertical edges along current row */
			for(vertical_edge_counter = 0; vertical_edge_counter < vert_edges_count - 1; vertical_edge_counter++)
			{
				/* get next rect in current row to examine */
				draw_info.clip_rect.x = vertical_edges[vertical_edge_counter] - draw_info.origin_x;

				/* find its z order */
				if (find_highest_z_order_at_point(vertical_edges[vertical_edge_counter],
						horizontal_edges[horizontal_edge_counter]) == 0)
				{
					draw_info.clip_rect.height = horizontal_edges[horizontal_edge_counter + 1] - horizontal_edges[horizontal_edge_counter];
					draw_info.clip_rect.width = vertical_edges[vertical_edge_counter + 1] - vertical_edges[vertical_edge_counter];

					mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
					mw_gl_rectangle(&draw_info, 0, 0, MW_DESKTOP_ICON_WIDTH, MW_DESKTOP_ICON_HEIGHT);
					mw_gl_string(&draw_info, 4, 6, mw_all_windows[i].title);

					/* draw 3d effect */
					mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
					mw_gl_vline(&draw_info, 1, 1, MW_DESKTOP_ICON_HEIGHT - 2);
					mw_gl_hline(&draw_info, 1, MW_DESKTOP_ICON_WIDTH - 2, 1);
					mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
					mw_gl_vline(&draw_info, MW_DESKTOP_ICON_WIDTH - 2, 2, MW_DESKTOP_ICON_HEIGHT - 2);
					mw_gl_hline(&draw_info, 2, MW_DESKTOP_ICON_WIDTH - 2, MW_DESKTOP_ICON_HEIGHT - 2);
				}
			}
		}
	}
}

/**
 * Find the next z order in the visible used maximised windows that is above the specified z order
 *
 * @param z_order The z order above which we're are looking for
 * @return The next found z order or MAX_Z_ORDER if no z order found
 */
static uint8_t find_next_z_order(uint8_t z_order)
{
	uint8_t next_z_order = MW_MAX_Z_ORDER;
	uint8_t i;

	/* loop through all user windows */
	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* ignore unused windows invisible minimised*/
		if ((mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) &&
				(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) &&
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			/* check if this window's z order is > z order searching against & < previous max z order */
			if (mw_all_windows[i].z_order < next_z_order && mw_all_windows[i].z_order > z_order)
			{
				/* it is, save it */
				next_z_order = mw_all_windows[i].z_order;
			}
		}
	}

	return next_z_order;
}

/**
 * Find the highest z order of all used visible maximised user windows.
 *
 * @return The highest z order found
 */
static uint8_t find_highest_z_order()
{
	uint8_t highest_z_order = 0;
	uint8_t i;

	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* ignore unused windows */
		if ((mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) &&
				(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) &&
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			if (mw_all_windows[i].z_order > highest_z_order)
			{
				/* new highest z order found so save it */
				highest_z_order = mw_all_windows[i].z_order;
			}
		}
	}

	return highest_z_order;
}

/**
 * Find the window a point is in; this is the window with the highest z order at the specified point
 *
 * @param touch_x The x coordinate of the touch point
 * @param touch_y The y coordinate of the touch point
 * return The window id
 */
static uint8_t find_window_point_is_in(int16_t touch_x, int16_t touch_y)
{
	uint8_t window_to_receive_message = MW_ROOT_WINDOW_ID;
	uint8_t i;
	uint8_t highest_z_order = 0;

	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* ignore unused invisible or minimised windows */
		if (!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) ||
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) ||
				(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			continue;
		}

		/* find the window that the touch event occurred in by finding highest z order at touch location; it may be root window where it happened */
		if (mw_util_is_point_in_rect(&mw_all_windows[i].window_rect, touch_x, touch_y))
		{
			if (mw_all_windows[i].z_order > highest_z_order)
			{
				highest_z_order = mw_all_windows[i].z_order;
				window_to_receive_message = i;
			}
		}
	}

	return window_to_receive_message;
}

/**
 * Look at all controls in a window and find which control a specified point is in, if any
 *
 * @param window_ref The window to check controls for
 * @param point_x The x coordinate of the point
 * @param point_y The y coordinate of the point
 * @return The control ref if a control was found else MW_MAX_CONTROL_COUNT
 */
static uint8_t find_control_point_is_in(uint8_t window_ref, int16_t point_x, int16_t point_y)
{
	int16_t i;
	uint8_t control_found = MW_MAX_CONTROL_COUNT;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	/* loop through all controls */
	for (i = MW_MAX_CONTROL_COUNT - 1; i >= 0; i--)
	{
		/* ignore unused controls and controls with a different parent window to that identified above */
		if (!(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_USED) ||
				mw_all_controls[i].parent != window_ref)
		{
			continue;
		}

		/* check next control's rect, enabled and visibility */
		if (mw_util_is_point_in_rect(&mw_all_controls[i].control_rect, point_x, point_y) &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_VISIBLE) &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_ENABLED))
		{
			/* a control has been identified that this touch message occurred in */
			control_found = i;
			break;
		}
	}

	return control_found;
}

/**
 * Fill the horizontal and vertical edges arrays with the edges of a rect and all windows that overlap it
 *
 * @param window_ref The rect under inspection
 * @param horiz_edges_count The number of edges found and entered in horizontal edges array
 * @param vert_edges_count The number of edges found and entered in vertical edges array
 * @note The entries are sorted
 */
static void find_rect_window_intersections(const mw_util_rect_t *r, uint16_t *horiz_edges_count, uint16_t *vert_edges_count)
{
	uint8_t i;
	uint16_t edges;
	bool self_left_found = false;
	bool self_right_found = false;
	bool self_top_found = false;
	bool self_bottom_found = false;

	MW_ASSERT(horiz_edges_count);
	MW_ASSERT(vert_edges_count);
	MW_ASSERT(r);

	/* clear the number of edges found */
	*horiz_edges_count = 0;
	*vert_edges_count = 0;

	/* loop through all windows */
	for (i = 0; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* ignore unused invisible or minimised windows */
		if (!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) ||
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) ||
				(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			continue;
		}
        
        /* check here if the latest window i overlaps with the rect r, if not then continue */
		if (!mw_util_do_rects_coincide(r, &mw_all_windows[i].window_rect))
		{
			continue;
		}

		/* test window left edge against rect r's horizontal range */
		if (mw_all_windows[i].window_rect.x >= r->x &&
				mw_all_windows[i].window_rect.x < r->x + r->width)
		{
			/* check window's left edge against screen edges */
			if (mw_all_windows[i].window_rect.x >= 0 &&
					mw_all_windows[i].window_rect.x < MW_HAL_LCD_WIDTH)
			{
				/* it's within both so add left edge */
				vertical_edges[*vert_edges_count] = mw_all_windows[i].window_rect.x;
				(*vert_edges_count)++;
			}
		}

		/* test window right edge against rect r's horizontal range */
		if (mw_all_windows[i].window_rect.x + mw_all_windows[i].window_rect.width - 1 >= r->x &&
				mw_all_windows[i].window_rect.x + mw_all_windows[i].window_rect.width - 1 < r->x + r->width)
		{
			/* check window's right edge against screen edges */
			if (mw_all_windows[i].window_rect.x + mw_all_windows[i].window_rect.width >= 0 &&
					mw_all_windows[i].window_rect.x + mw_all_windows[i].window_rect.width <= MW_HAL_LCD_WIDTH)
			{
				/* it's within both so add right edge */
				vertical_edges[*vert_edges_count] = mw_all_windows[i].window_rect.x + mw_all_windows[i].window_rect.width;
				(*vert_edges_count)++;
			}
		}

		/* test window top edge against rect r's horizontal range */
		if (mw_all_windows[i].window_rect.y >= r->y &&
				mw_all_windows[i].window_rect.y < r->y + r->height)
		{
			/* check window's top edge against screen edges */		
			if (mw_all_windows[i].window_rect.y >= 0 &&
					mw_all_windows[i].window_rect.y < MW_HAL_LCD_HEIGHT)
			{
				/* it's within both so add top edge */			
				horizontal_edges[*horiz_edges_count] = mw_all_windows[i].window_rect.y;
				(*horiz_edges_count)++;
			}
		}

		/* test window bottom edge against rect r's horizontal range */
		if (mw_all_windows[i].window_rect.y + mw_all_windows[i].window_rect.height - 1 >= r->y &&
				mw_all_windows[i].window_rect.y + mw_all_windows[i].window_rect.height - 1 < r->y + r->height)
		{
			/* check window's bottom edge against screen edges */				
			if (mw_all_windows[i].window_rect.y + mw_all_windows[i].window_rect.height >= 0 &&
					mw_all_windows[i].window_rect.y + mw_all_windows[i].window_rect.height <= MW_HAL_LCD_HEIGHT)
			{
				/* it's within both so add bottom edge */			
				horizontal_edges[*horiz_edges_count] = mw_all_windows[i].window_rect.y + mw_all_windows[i].window_rect.height;
				(*horiz_edges_count)++;
			}
		}
	}

	/* find if the vertical edges of the window being compared against the rect are in the array of found edges */
	for(edges = 0; edges < *vert_edges_count; edges++)
	{
		/* left edge */
		if (vertical_edges[edges] == r->x)
		{
			self_left_found = true;
		}
		/* right edge */
		if (vertical_edges[edges] == r->x + r->width)
		{
			self_right_found = true;
		}
	}

	/* repeat for horizontal edges */
	for(edges = 0; edges < *horiz_edges_count; edges++)
	{
		/* top edge */
		if (horizontal_edges[edges] == r->y)
		{
			self_top_found = true;
		}
		/* bottom edge */
		if (horizontal_edges[edges] == r->y + r->height)
		{
			self_bottom_found = true;
		}
	}

	/* if our own window edges were not found add them, clipping to the edge of the screen first */
	if (!self_left_found)
	{
		vertical_edges[*vert_edges_count] = r->x < 0 ? 0 : r->x;
		(*vert_edges_count)++;
	}

	if (!self_right_found)
	{
		vertical_edges[*vert_edges_count] = r->x + r->width > MW_HAL_LCD_WIDTH ? MW_HAL_LCD_WIDTH : r->x + r->width;
		(*vert_edges_count)++;
	}

	if (!self_top_found)
	{
		horizontal_edges[*horiz_edges_count] = r->y < 0 ? 0 : r->y;
		(*horiz_edges_count)++;
	}

	if (!self_bottom_found)
	{
		horizontal_edges[*horiz_edges_count] = r->y + r->height > MW_HAL_LCD_HEIGHT ? MW_HAL_LCD_HEIGHT : r->y + r->height;
		(*horiz_edges_count)++;
	}

	/* sort the arrays of intersections */
	qsort(vertical_edges, *vert_edges_count, sizeof(uint16_t), mw_util_compare_int16_t);
	qsort(horizontal_edges, *horiz_edges_count, sizeof(uint16_t), mw_util_compare_int16_t);
}

/**
 * Find z order of highest shown window at a point, which may be root window
 *
 * @param x X coordinate of point
 * @param y Y coordinate of point
 * @return The z order
 */
static uint8_t find_highest_z_order_at_point(int16_t x, int16_t y)
{
	return mw_all_windows[find_window_point_is_in(x, y)].z_order;
}

/**
 * Find the number of visible user windows. A window must be a used and not minimised to be counted.
 * Root window is not included in the count.
 *
 * @return The number of windows used and visible
 */
static uint8_t find_number_of_displayed_windows()
{
	uint8_t displayed_windows = 0;
	uint8_t i;

	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
		if ((mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) &&
				(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) &&
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			displayed_windows++;
		}
	}

	return displayed_windows;
}

/**
 * Find if a window is overlapped by any other
 *
 * @param window_ref The window to check
 * @return true or false
 */
static bool find_if_window_is_overlapped(uint8_t window_ref)
{
	uint8_t i;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	/* iterate through all windows */
	for (i = 0; i < MW_MAX_WINDOW_COUNT;i++)
	{
		if (!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED) ||
				(!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE)) ||
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_MINIMISED) ||
				mw_all_windows[i].z_order < mw_all_windows[window_ref].z_order)
		{
			continue;
		}

		if (mw_util_do_rects_coincide(&mw_all_windows[i].window_rect, &mw_all_windows[window_ref].window_rect))
		{
			return true;
		}
	}

	return false;
}

/**
 * FInd if a specified rect is completely on the screen
 *
 * @param rect The rect to check
 * @return If completely on screen true wlse false
 */
static bool find_if_rect_is_completely_on_screen(const mw_util_rect_t *rect)
{
	return (rect->x >= 0 &&
			rect->y >= 0 &&
			rect->x + rect->width <= MW_HAL_LCD_WIDTH &&
			rect->y + rect->height <= MW_HAL_LCD_HEIGHT);
}

/**
 * Draw a window's title bar including text
 *
 * @param window_ref Position in array of all windows of this window
 * @param draw_info Reference frame origin coordinates and clip region rect
 */
static void draw_title_bar(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);
	MW_ASSERT(draw_info);

    /* set title bar colour according to focus/modal state */
	if (window_ref != window_with_focus)
	{
		/* not focused colour */
		mw_gl_set_solid_fill_colour(MW_TITLE_BAR_COLOUR_NO_FOCUS);
	}
	else
	{
		if (mw_all_windows[window_ref].window_flags & MW_WINDOW_IS_MODAL)
		{
			/* modal colour */
			mw_gl_set_solid_fill_colour(MW_TITLE_BAR_COLOUR_MODAL);
		}
		else
		{
			/* normal focused colour */
			mw_gl_set_solid_fill_colour(MW_TITLE_BAR_COLOUR_FOCUS);
		}
	}
    
    /* draw the filled box */
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			0,
			0,
			mw_all_windows[window_ref].window_rect.width,
			MW_TITLE_BAR_HEIGHT);

	/* draw the icons if the window has focus and isn't modal */
	if (window_with_focus == window_ref && !(mw_all_windows[window_with_focus].window_flags & MW_WINDOW_IS_MODAL))
	{
		/* window close icon */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_colour(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_CAN_BE_CLOSED ? MW_HAL_LCD_WHITE : MW_HAL_LCD_GREY5);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_monochrome_bitmap(draw_info,
				mw_all_windows[window_ref].window_rect.width - MW_TITLE_BAR_ICON_OFFSET,
				2,
				MW_TITLE_BAR_ICON_SIZE,
				MW_TITLE_BAR_ICON_SIZE,
				mw_bitmaps_close_icon);

		/* resize icon */
		mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_monochrome_bitmap(draw_info,
				2,
				2,
				MW_TITLE_BAR_ICON_SIZE,
				MW_TITLE_BAR_ICON_SIZE,
				mw_bitmaps_resize_icon);

		/* maximise icon */
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
		mw_gl_set_bg_colour(MW_HAL_LCD_WHITE);
		mw_gl_monochrome_bitmap(draw_info,
				mw_all_windows[window_ref].window_rect.width - (MW_TITLE_BAR_ICON_OFFSET * 2),
				2,
				MW_TITLE_BAR_ICON_SIZE,
				MW_TITLE_BAR_ICON_SIZE,
				mw_bitmaps_maximise_icon);

		/* minimise icon */
		mw_gl_set_bg_colour(MW_HAL_LCD_WHITE);
		mw_gl_monochrome_bitmap(draw_info,
				mw_all_windows[window_ref].window_rect.width - (MW_TITLE_BAR_ICON_OFFSET * 3),
				2,
				MW_TITLE_BAR_ICON_SIZE,
				MW_TITLE_BAR_ICON_SIZE,
				mw_bitmaps_minimise_icon);

		/* only draw the title if there's space remaining */
		if (mw_all_windows[window_ref].window_rect.width - (MW_TITLE_BAR_ICON_OFFSET * 4) - MW_TITLE_X_OFFSET > mw_gl_large_string_width(mw_all_windows[window_ref].title))
		{
			draw_titlebar_text(window_ref, draw_info);
		}
	}
	else
	{
		/* window doesn't have focus, no icons, so always draw the text; set colour according to focus and modality state */				
		draw_titlebar_text(window_ref, draw_info);
	}
}

/**
 * Draw title bar text in colour according to window state.
 *
 * @param window_ref Position in array of all windows of this window
 * @param draw_info Reference frame origin coordinates and clip region rect
 */
static void draw_titlebar_text(uint8_t window_ref, const mw_gl_draw_info_t *draw_info)
{
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);
	MW_ASSERT(draw_info);

	if (window_ref != window_with_focus)
	{
		mw_gl_set_fg_colour(MW_TITLE_TEXT_COLOUR_NO_FOCUS);
	}
	else
	{
		if (mw_all_windows[window_ref].window_flags & MW_WINDOW_IS_MODAL)
		{
			mw_gl_set_fg_colour(MW_TITLE_TEXT_COLOUR_MODAL);
		}
		else
		{
			mw_gl_set_fg_colour(MW_TITLE_TEXT_COLOUR_NO_FOCUS);
		}
	}		
	
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
	mw_gl_large_string(draw_info, MW_TITLE_X_OFFSET, MW_TITLE_Y_OFFSET, mw_all_windows[window_ref].title);
}

/**
 * Draw a menu bar
 *
 * @param draw_info Draw info structure describing offset and clip region
 * @param window_ref The window this menu bar is draw in
 */
static void draw_menu_bar(const mw_gl_draw_info_t *draw_info, uint8_t window_ref)
{
	uint16_t next_pos;
	uint8_t i;

	MW_ASSERT(draw_info);
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	mw_gl_set_border(MW_GL_BORDER_OFF);
	mw_gl_clear_pattern();
	mw_gl_rectangle(draw_info,
			mw_all_windows[window_ref].client_rect.x - mw_all_windows[window_ref].window_rect.x,
			mw_all_windows[window_ref].client_rect.y - mw_all_windows[window_ref].window_rect.y - MW_MENU_BAR_HEIGHT,
			mw_all_windows[window_ref].client_rect.width,
			MW_MENU_BAR_HEIGHT);

    /* set up text transparency */
	mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);

    /* draw each item */
	next_pos = 0;
	for (i = 0; i < mw_all_windows[window_ref].menu_bar_items_count; i++)
	{
        /* check if this item is selected */
		if ((mw_all_windows[window_ref].window_flags & MW_WINDOW_MENU_BAR_ITEM_IS_SELECTED) &&
				mw_all_windows[window_ref].menu_bar_selected_item == i)
		{
            /* it is so draw rectangle background for this item in control down colour */
			mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
			mw_gl_rectangle(draw_info,
					next_pos,
					mw_all_windows[window_ref].client_rect.y - mw_all_windows[window_ref].window_rect.y - MW_MENU_BAR_HEIGHT,
					(strlen(mw_all_windows[window_ref].menu_bar_items[i]) + 2) * MW_GL_STANDARD_CHARACTER_WIDTH,
					MW_MENU_BAR_HEIGHT);
		}

		/* set up text colour on enabled state - from control and individual items bitfield */
	    if (mw_all_windows[window_ref].window_flags & MW_WINDOW_MENU_BAR_ENABLED &&
	    		mw_util_get_bit(mw_all_windows[window_ref].menu_bar_item_enables, i))
	    {
	        mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	    }
	    else
	    {
	        mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	    }

        /* draw the menu item text */
		mw_gl_string(draw_info,
				next_pos + MW_GL_STANDARD_CHARACTER_WIDTH,
				MW_MENU_BAR_LABEL_Y_OFFSET +
					mw_all_windows[window_ref].client_rect.y -
					mw_all_windows[window_ref].window_rect.y -
					MW_MENU_BAR_HEIGHT,
				mw_all_windows[window_ref].menu_bar_items[i]);

		next_pos += (strlen(mw_all_windows[window_ref].menu_bar_items[i]) + 2) * MW_GL_STANDARD_CHARACTER_WIDTH;
	}
}

/**
 * Draw a horizontal window scroll bar
 *
 * @param draw_info Draw info structure describing offset and clip region
 * @param window_ref The window this scroll bar is draw in
 */
static void draw_horizontal_window_scroll_bar(const mw_gl_draw_info_t *draw_info, uint8_t window_ref)
{
	int16_t scroll_bar_horiz_slider_left;

	MW_ASSERT(draw_info);
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_clear_pattern();
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	if (mw_all_windows[window_ref].window_flags & MW_WINDOWS_HORIZ_SCROLL_BAR_ENABLED)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	}
	mw_gl_rectangle(draw_info,
			mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0,
			mw_all_windows[window_ref].window_rect.height -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			mw_all_windows[window_ref].client_rect.width,
			MW_SCROLL_BAR_NARROW_DIMESION);

	/* there is always space to draw slider */
	mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);

	scroll_bar_horiz_slider_left = (mw_all_windows[window_ref].client_rect.width - MW_SCROLL_BAR_SLIDER_SIZE) *
		mw_all_windows[window_ref].horiz_scroll_pos / UINT8_MAX;

	scroll_bar_horiz_slider_left += (mw_all_windows[window_ref].client_rect.x -
		mw_all_windows[window_ref].window_rect.x);

	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_rectangle(draw_info,
			scroll_bar_horiz_slider_left,
			mw_all_windows[window_ref].window_rect.height -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			MW_SCROLL_BAR_SLIDER_SIZE,
			MW_SCROLL_BAR_NARROW_DIMESION);

	/* draw 3D effect */
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info,
			scroll_bar_horiz_slider_left + 1,
			2 +
				mw_all_windows[window_ref].window_rect.height -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			mw_all_windows[window_ref].window_rect.height -
				2 -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0));
	mw_gl_hline(draw_info,
			scroll_bar_horiz_slider_left + 1,
			scroll_bar_horiz_slider_left + MW_SCROLL_BAR_SLIDER_SIZE - 2,
			1 +
				mw_all_windows[window_ref].window_rect.height -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info,
			scroll_bar_horiz_slider_left + MW_SCROLL_BAR_SLIDER_SIZE - 2,
			2 +
				mw_all_windows[window_ref].window_rect.height -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			mw_all_windows[window_ref].window_rect.height -
				3 -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0));
	mw_gl_hline(draw_info,
			scroll_bar_horiz_slider_left + 2,
			scroll_bar_horiz_slider_left + MW_SCROLL_BAR_SLIDER_SIZE - 2,
			mw_all_windows[window_ref].window_rect.height -
				2 -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0));
}

/**
 * Draw a vertical window scroll bar
 *
 * @param draw_info Draw info structure describing offset and clip region
 * @param window_ref The window this scroll bar is draw in
 */
static void draw_vertical_window_scroll_bar(const mw_gl_draw_info_t *draw_info, uint8_t window_ref)
{
	int16_t scroll_bar_horiz_slider_top;

	MW_ASSERT(draw_info);
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_clear_pattern();
	mw_gl_set_solid_fill_colour(MW_CONTROL_UP_COLOUR);
	if (mw_all_windows[window_ref].window_flags & MW_WINDOWS_HORIZ_SCROLL_BAR_ENABLED)
	{
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	}
	else
	{
		mw_gl_set_fg_colour(MW_CONTROL_DISABLED_COLOUR);
	}

	mw_gl_rectangle(draw_info,
			(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) +
				mw_all_windows[window_ref].client_rect.width,
			mw_all_windows[window_ref].client_rect.y - mw_all_windows[window_ref].window_rect.y,
			MW_SCROLL_BAR_NARROW_DIMESION,
			mw_all_windows[window_ref].client_rect.height);

	/* there is always space to draw slider */
	mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);

	scroll_bar_horiz_slider_top = (mw_all_windows[window_ref].client_rect.height - MW_SCROLL_BAR_SLIDER_SIZE) *
			mw_all_windows[window_ref].vert_scroll_pos / UINT8_MAX;

	scroll_bar_horiz_slider_top += (mw_all_windows[window_ref].client_rect.y - mw_all_windows[window_ref].window_rect.y);

	mw_gl_set_border(MW_GL_BORDER_ON);
	mw_gl_set_line(MW_GL_SOLID_LINE);
	mw_gl_rectangle(draw_info,
			mw_all_windows[window_ref].window_rect.width -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			scroll_bar_horiz_slider_top,
			MW_SCROLL_BAR_NARROW_DIMESION,
			MW_SCROLL_BAR_SLIDER_SIZE);

	/* draw 3D effect */
	mw_gl_set_fg_colour(MW_HAL_LCD_WHITE);
	mw_gl_vline(draw_info,
			2 +
				mw_all_windows[window_ref].window_rect.width -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			1 + scroll_bar_horiz_slider_top,
			scroll_bar_horiz_slider_top + MW_SCROLL_BAR_NARROW_DIMESION - 2);
	mw_gl_hline(draw_info,
			2 +
				mw_all_windows[window_ref].window_rect.width -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			mw_all_windows[window_ref].window_rect.width -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				2,
			scroll_bar_horiz_slider_top + 1);
	mw_gl_set_fg_colour(MW_HAL_LCD_GREY7);
	mw_gl_vline(draw_info,
			MW_SCROLL_BAR_NARROW_DIMESION +
				mw_all_windows[window_ref].window_rect.width -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION -
				2,
				2 + scroll_bar_horiz_slider_top,
				scroll_bar_horiz_slider_top + MW_SCROLL_BAR_NARROW_DIMESION - 2);
	mw_gl_hline(draw_info,
			2 +
				mw_all_windows[window_ref].window_rect.width -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				MW_SCROLL_BAR_NARROW_DIMESION,
			mw_all_windows[window_ref].window_rect.width -
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER ? MW_BORDER_WIDTH : 0) -
				2,
			scroll_bar_horiz_slider_top + MW_SCROLL_BAR_SLIDER_SIZE - 2);
}

/**
 * Paint the window with the specified z order. There will be only one window for each z order.
 *
 * @param z_order The z order of the window to paint
 */
static void paint_window_frame_and_client_with_z_order(uint8_t z_order)
{
	uint8_t window_ref;

	/* iterate through all user windows */
	for (window_ref = MW_ROOT_WINDOW_ID; window_ref < MW_MAX_WINDOW_COUNT; window_ref++)
	{
		/* only look at windows that are used */
		if ((mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) &&
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED) &&
				!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			/* check if next window is required z order */
			if (mw_all_windows[window_ref].z_order == z_order)
			{
				/* it is so paint it */
				do_paint_window_frame(window_ref, MW_WINDOW_FRAME_COMPONENT_ALL);
				do_paint_window_client(window_ref);
			  	if (window_ref > MW_ROOT_WINDOW_ID)
			  	{
			  		/* paint all the controls; these are always on top of the client area */
			  		paint_all_controls_in_window(window_ref);
			  	}
				break;
			}
		}
	}
}

/**
 * The first half of the implementation of painting a window frame but not its client area
 *
 * @param window_ref Position in array of all windows of this window
 * @note The first half of the window painting process is identifying the rects the window needs breaking
 *       up into according to the other windows overlapping it
 */
static void do_paint_window_frame(uint8_t window_ref, uint8_t components)
{
	uint16_t vertical_edge_counter;
	uint16_t horizontal_edge_counter;
	int16_t previous_rect_left;
	uint16_t previous_rect_width;
	bool rect_waiting_to_be_painted;
	uint16_t horiz_edges_count;
	uint16_t vert_edges_count;
	mw_util_rect_t rect_current;
	mw_util_rect_t rect_previous;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

    /* check if this window is used, visible and not minimised; if not give up */
	if (!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED) ||
			(!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE)) ||
			(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_MINIMISED) ||
			window_ref == MW_ROOT_WINDOW_ID)
	{
		return;
	}

	/* check if this window has focus which means it's at the front; if so and it's completely
	 * on screen just paint it all */
	if (window_ref == window_with_focus && find_if_rect_is_completely_on_screen(&mw_all_windows[window_ref].window_rect))
	{
		memcpy(&rect_current, &mw_all_windows[window_ref].window_rect, sizeof(mw_util_rect_t));
		do_paint_window_frame2(window_ref, components, &rect_current);
	}
	else
	{
		find_rect_window_intersections(&mw_all_windows[window_ref].window_rect, &horiz_edges_count, &vert_edges_count);

		/* iterate through horizontal edges, i.e. row at a time */
		for (horizontal_edge_counter = 0; horizontal_edge_counter < horiz_edges_count - 1; horizontal_edge_counter++)
		{
			rect_waiting_to_be_painted = false;
			rect_current.y = horizontal_edges[horizontal_edge_counter];
			rect_current.height = (horizontal_edges[horizontal_edge_counter + 1] - rect_current.y);

			/* iterate through vertical edges along current row */
			for(vertical_edge_counter = 0; vertical_edge_counter < vert_edges_count - 1; vertical_edge_counter++)
			{
				/* get next rect in current row to examine */
				rect_current.x = vertical_edges[vertical_edge_counter];
				rect_current.width = (vertical_edges[vertical_edge_counter + 1] - rect_current.x);

				/* find its z order */
				if (find_highest_z_order_at_point(rect_current.x, rect_current.y) > mw_all_windows[window_ref].z_order)
				{
					if (rect_waiting_to_be_painted)
					{
						do_paint_window_frame2(window_ref, components, &rect_previous);
						rect_waiting_to_be_painted = false;
					}
					continue;
				}

				previous_rect_left = rect_previous.x;
				previous_rect_width = rect_previous.width;
				memcpy(&rect_previous, &rect_current, sizeof(mw_util_rect_t));

				if (rect_waiting_to_be_painted)
				{
					rect_previous.x = previous_rect_left;
					rect_previous.width += previous_rect_width;
				}
				rect_waiting_to_be_painted = true;
			}

			if (rect_waiting_to_be_painted)
			{
				do_paint_window_frame2(window_ref, components,  &rect_previous);
			}
		}
	}
}

/**
 * The second half of the implementation of painting a window but not its client area
 *
 * @param window_ref Position in array of all windows of this window
 * @param invalid_rect Rect describing the area of the window that will be painted this time
 * @note The second half of the window painting process the painting of the window features excluding
 *       the client area, i.e. title bar and borders. This function is called multiple times with
 *       different clip rects.
 */
static void do_paint_window_frame2(uint8_t window_ref, uint8_t components, const mw_util_rect_t *invalid_rect)
{
	mw_gl_draw_info_t draw_info;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);
	MW_ASSERT(invalid_rect);

	draw_info.clip_rect.x = invalid_rect->x - mw_all_windows[window_ref].window_rect.x;
	draw_info.clip_rect.y = invalid_rect->y - mw_all_windows[window_ref].window_rect.y;
	draw_info.clip_rect.width = invalid_rect->width;
	draw_info.clip_rect.height = invalid_rect->height;
	draw_info.origin_x = mw_all_windows[window_ref].window_rect.x;
	draw_info.origin_y = mw_all_windows[window_ref].window_rect.y;

	/* draw border, fixed width of 1 for now */
  	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_BORDER &&
  			(components & MW_WINDOW_FRAME_COMPONENT_BORDER))
  	{
  		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
  		mw_gl_set_line(MW_GL_SOLID_LINE);

        /* draw two shorter left/right sides */
  		if (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
  		{
  			mw_gl_vline(&draw_info,
  					0,
  					MW_TITLE_BAR_HEIGHT,
  					mw_all_windows[window_ref].window_rect.height - 1);
  			mw_gl_vline(&draw_info,
  					mw_all_windows[window_ref].window_rect.width - 1,
  					MW_TITLE_BAR_HEIGHT,
  					mw_all_windows[window_ref].window_rect.height - 1);
  		}
  		else
  		{
            /* draw two full length left/right sides and top line */
            mw_gl_hline(&draw_info,
            		0,
                    mw_all_windows[window_ref].window_rect.width - 1,
                    0);
            mw_gl_vline(&draw_info,
                    0,
                    0,
                    mw_all_windows[window_ref].window_rect.height - 1);
            mw_gl_vline(&draw_info,
                    mw_all_windows[window_ref].window_rect.width - 1,
                    0,
                    mw_all_windows[window_ref].window_rect.height - 1);
  		}

  		/* draw bottom line */
		mw_gl_hline(&draw_info,
				0,
				mw_all_windows[window_ref].window_rect.width - 1,
				mw_all_windows[window_ref].window_rect.height - 1);
  	}

	/* draw title bar if this window has one */
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_HAS_TITLE_BAR &&
			(components & MW_WINDOW_FRAME_COMPONENT_TITLE_BAR))
	{
		draw_title_bar(window_ref, &draw_info);
	}

	/* draw menu bar */
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_MENU_BAR &&
			(components & MW_WINDOW_FRAME_COMPONENT_MENU_BAR))
	{
		draw_menu_bar(&draw_info, window_ref);
	}

	/* draw no, 1 or both scroll bars */
	if ((mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_HORIZ_SCROLL_BAR) &&
			(mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_VERT_SCROLL_BAR))
	{
		/* draw horizontal and vertical scroll bars */
		if (components & MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR)
		{
			draw_horizontal_window_scroll_bar(&draw_info, window_ref);
		}
		if (components & MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR)
		{
			draw_vertical_window_scroll_bar(&draw_info, window_ref);
		}

		/* fill in that little square at bottom right */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_CONTROL_DOWN_COLOUR);
		mw_gl_set_border(MW_GL_BORDER_OFF);
		mw_gl_clear_pattern();
		mw_gl_rectangle(&draw_info,
				(mw_all_windows[window_ref].client_rect.x - mw_all_windows[window_ref].window_rect.x) +
					mw_all_windows[window_ref].client_rect.width,
				(mw_all_windows[window_ref].client_rect.y - mw_all_windows[window_ref].window_rect.y) +
					mw_all_windows[window_ref].client_rect.height,
				MW_SCROLL_BAR_NARROW_DIMESION,
				MW_SCROLL_BAR_NARROW_DIMESION);
	}
	else if (mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_HORIZ_SCROLL_BAR &&
				(components & MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR))
	{
		/* draw horizontal scroll bar only */
		draw_horizontal_window_scroll_bar(&draw_info, window_ref);
	}
	else if (mw_all_windows[window_ref].window_flags & MW_WINDOW_HAS_VERT_SCROLL_BAR &&
				(components & MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR))
	{
		/* draw vertical scroll bar only */
		draw_vertical_window_scroll_bar(&draw_info, window_ref);
	}
}

/**
 * The first half of the implementation of painting a window's client area
 *
 * @param window_ref Position in array of all windows of this window
 * @note The first half of the window painting process is identifying the rects the client area needs breaking
 *       up into according to the other windows overlapping it
 */
static void do_paint_window_client(uint8_t window_ref)
{
	uint16_t vertical_edge_counter;
	uint16_t horizontal_edge_counter;
	int16_t previous_rect_left;
	uint16_t previous_rect_width;
	bool rect_waiting_to_be_painted;
	uint16_t horiz_edges_count;
	uint16_t vert_edges_count;
	mw_util_rect_t rect_current;
	mw_util_rect_t rect_previous;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

    /* check if this window is used, visible and not minimised; if not give up */
	if (!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED) ||
			(!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE)) ||
			(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
	{
		return;
	}

	/* check if this window has focus which means it's at the front and it's completely on screen;
	 * if so just paint it all */
	if (window_ref == window_with_focus && find_if_rect_is_completely_on_screen(&mw_all_windows[window_ref].client_rect))
	{
		memcpy(&rect_current, &mw_all_windows[window_ref].client_rect, sizeof(mw_util_rect_t));
		do_paint_window_client2(window_ref, &rect_current);
	}
	else
	{
		find_rect_window_intersections(&mw_all_windows[window_ref].client_rect, &horiz_edges_count, &vert_edges_count);

		/* iterate through horizontal edges, i.e. row at a time */
		for (horizontal_edge_counter = 0; horizontal_edge_counter < horiz_edges_count - 1; horizontal_edge_counter++)
		{
			rect_waiting_to_be_painted = false;
			rect_current.y = horizontal_edges[horizontal_edge_counter];
			rect_current.height = (horizontal_edges[horizontal_edge_counter + 1] - rect_current.y);

			/* iterate through vertical edges along current row */
			for(vertical_edge_counter = 0; vertical_edge_counter < vert_edges_count - 1; vertical_edge_counter++)
			{
				/* get next rect in current row to examine */
				rect_current.x = vertical_edges[vertical_edge_counter];
				rect_current.width = (vertical_edges[vertical_edge_counter + 1] - rect_current.x);

				/* find its z order */
				if (find_highest_z_order_at_point(rect_current.x, rect_current.y) > mw_all_windows[window_ref].z_order)
				{
					if (rect_waiting_to_be_painted)
					{
						do_paint_window_client2(window_ref, &rect_previous);
						rect_waiting_to_be_painted = false;
					}
					continue;
				}

				previous_rect_left = rect_previous.x;
				previous_rect_width = rect_previous.width;
				memcpy(&rect_previous, &rect_current, sizeof(mw_util_rect_t));

				if (rect_waiting_to_be_painted)
				{
					rect_previous.x = previous_rect_left;
					rect_previous.width += previous_rect_width;
				}
				rect_waiting_to_be_painted = true;
			}

			if (rect_waiting_to_be_painted)
			{
				do_paint_window_client2(window_ref, &rect_previous);
			}
		}
	}

	if (window_ref == MW_ROOT_WINDOW_ID)
	{
		draw_minimised_icons();
	}
}

/**
 * The first half of the implementation of painting a window's client area but only with a specified rectangle
 *
 * @param window_ref Position in array of all windows of this window
 * @param invalid_rect Rect describing the area of the client that will be painted 
 * @note The first half of the window painting process is identifying the sub-rects the client area rect needs breaking
 *       up into according to the other windows overlapping it
 */
static void do_paint_window_client_rect(uint8_t window_ref, const mw_util_rect_t *invalid_rect)
{
	uint16_t vertical_edge_counter;
	uint16_t horizontal_edge_counter;
	int16_t previous_rect_left;
	uint16_t previous_rect_width;
	bool rect_waiting_to_be_painted;
	uint16_t horiz_edges_count;
	uint16_t vert_edges_count;
	mw_util_rect_t rect_current;
	mw_util_rect_t rect_previous;
	mw_util_rect_t invalid_rect_copy;
	int16_t overlap;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);
	MW_ASSERT(invalid_rect);

    /* check if this window is used, visible and not minimised; if not give up */
	if (!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED) ||
			(!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE)) ||
			(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_MINIMISED) ||
			window_ref == MW_ROOT_WINDOW_ID)
	{
		return;
	}

	/* create a local copy of the invalid rect as it's going to be changed here */
	memcpy(&invalid_rect_copy, invalid_rect, sizeof(mw_util_rect_t));

	/* adjust coordinates reference from client area to screen */
	invalid_rect_copy.x += mw_all_windows[window_ref].client_rect.x;
	invalid_rect_copy.y += mw_all_windows[window_ref].client_rect.y;

	/* check for any areas of the invalid rect outside of the window's client area and if found clip them */
	if (invalid_rect_copy.x < mw_all_windows[window_ref].client_rect.x)
	{
		overlap = mw_all_windows[window_ref].client_rect.x - invalid_rect_copy.x;
		invalid_rect_copy.x = mw_all_windows[window_ref].client_rect.x;
		invalid_rect_copy.width -= overlap;
	}
	if (invalid_rect_copy.y < mw_all_windows[window_ref].client_rect.y)
	{
		overlap = mw_all_windows[window_ref].client_rect.y - invalid_rect_copy.y;
		invalid_rect_copy.y = mw_all_windows[window_ref].client_rect.y;
		invalid_rect_copy.height -= overlap;
	}
	if (invalid_rect_copy.x + invalid_rect_copy.width > mw_all_windows[window_ref].client_rect.x +
			mw_all_windows[window_ref].client_rect.width)
	{
		overlap = (invalid_rect_copy.x + invalid_rect_copy.width) -
				(mw_all_windows[window_ref].client_rect.x + mw_all_windows[window_ref].client_rect.width);
		invalid_rect_copy.width -= overlap;
	}
	if (invalid_rect_copy.y + invalid_rect_copy.height > mw_all_windows[window_ref].client_rect.y + mw_all_windows[window_ref].client_rect.width)
	{
		{
			overlap = (invalid_rect_copy.y + invalid_rect_copy.height) -
					(mw_all_windows[window_ref].client_rect.y + mw_all_windows[window_ref].client_rect.height);
			invalid_rect_copy.height -= overlap;
		}
	}

	/* check there's anything left to do */
	if (invalid_rect_copy.width == 0 || invalid_rect_copy.height == 0)
	{
		return;
	}

	/* check if this window has focus which means it's at the front and it's completely on screen;
	 * if so just paint the whole invalid rect in one go */
	if (window_ref == window_with_focus && find_if_rect_is_completely_on_screen(&invalid_rect_copy))
	{
		do_paint_window_client2(window_ref, &invalid_rect_copy);
	}
	else
	{
		find_rect_window_intersections(&invalid_rect_copy, &horiz_edges_count, &vert_edges_count);

		/* iterate through horizontal edges, i.e. row at a time */
		for (horizontal_edge_counter = 0; horizontal_edge_counter < horiz_edges_count - 1; horizontal_edge_counter++)
		{
			rect_waiting_to_be_painted = false;
			rect_current.y = horizontal_edges[horizontal_edge_counter];
			rect_current.height = (horizontal_edges[horizontal_edge_counter + 1] - rect_current.y);

			/* iterate through vertical edges along current row */
			for(vertical_edge_counter = 0; vertical_edge_counter < vert_edges_count - 1; vertical_edge_counter++)
			{
				/* get next rect in current row to examine */
				rect_current.x = vertical_edges[vertical_edge_counter];
				rect_current.width = (vertical_edges[vertical_edge_counter + 1] - rect_current.x);

				/* find its z order */
				if (find_highest_z_order_at_point(rect_current.x, rect_current.y) > mw_all_windows[window_ref].z_order)
				{
					if (rect_waiting_to_be_painted)
					{
						do_paint_window_client2(window_ref, &rect_previous);
						rect_waiting_to_be_painted = false;
					}
					continue;
				}

				previous_rect_left = rect_previous.x;
				previous_rect_width = rect_previous.width;
				memcpy(&rect_previous, &rect_current, sizeof(mw_util_rect_t));

				if (rect_waiting_to_be_painted)
				{
					rect_previous.x = previous_rect_left;
					rect_previous.width += previous_rect_width;
				}
				rect_waiting_to_be_painted = true;
			}

			if (rect_waiting_to_be_painted)
			{
				do_paint_window_client2(window_ref, &rect_previous);
			}
		}
	}
}

/**
 * The second half of the implementation of painting a window's client area
 *
 * @param window_ref Position in array of all windows of this window
 * @param invalid_rect Rect describing the area of the client that will be painted this time
 * @note The second half of the client painting process the painting of the window's client area
 *       is performed by calling the window's paint function. This function is called multiple times with
 *       different clip rects.
 */
static void do_paint_window_client2(uint8_t window_ref, const mw_util_rect_t *invalid_rect)
{
	mw_gl_draw_info_t client_draw_info;

	MW_ASSERT(window_ref < MW_MAX_CONTROL_COUNT);
	MW_ASSERT(invalid_rect);

	client_draw_info.clip_rect.x = invalid_rect->x - mw_all_windows[window_ref].client_rect.x;
	client_draw_info.clip_rect.y = invalid_rect->y - mw_all_windows[window_ref].client_rect.y;
	client_draw_info.clip_rect.width = invalid_rect->width;
	client_draw_info.clip_rect.height = invalid_rect->height;
	client_draw_info.origin_x = mw_all_windows[window_ref].client_rect.x;
	client_draw_info.origin_y = mw_all_windows[window_ref].client_rect.y;

	/* set flag indicating in a client window paint function */
	in_client_window_paint_function = true;

	/* call client window paint function */
	mw_all_windows[window_ref].paint_func(window_ref, &client_draw_info);

	/* reset flag indicating in a client window paint function */
	in_client_window_paint_function = false;
}

/**
 * Paint all controls in a window.
 *
 * @param window_ref position in array of all windows of this window
 */
static void paint_all_controls_in_window(uint8_t window_ref)
{
	uint8_t i;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

    /* iterate through all controls */
	for (i = 0; i < MW_MAX_CONTROL_COUNT; i++)
	{
        /* ignore controls not used, not visible and not belonging to specified window */
		if (mw_all_controls[i].parent == window_ref &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_USED) &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_VISIBLE))
		{
			do_paint_control(i);
		}
	}
}

/**
 * Paint all controls in a window only within a specified rect.
 *
 * @param window_ref Position in array of all windows of this window
 * @param invalid_rect Rect describing the area of the client that will be painted this time
 */
static void paint_all_controls_in_window_rect(uint8_t window_ref, const mw_util_rect_t *invalid_rect)
{
	uint8_t i;

	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

    /* iterate through all controls */
	for (i = 0; i < MW_MAX_CONTROL_COUNT; i++)
	{
        /* ignore controls not used, not visible and not belonging to specified window */
		if (mw_all_controls[i].parent == window_ref &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_USED) &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_VISIBLE))
		{
			do_paint_control_rect(i, invalid_rect);
		}
	}
}

/**
 * The first half of the implementation of painting a control's client area
 *
 * @param control_ref Position in array of all controls of this control
 * @param invalid_rect Rect describing the area of the client that will be painted this time
 * @note The first half of the control painting process is identifying the rects the control's area needs breaking
 *       up into according to the other windows overlapping it
 */
static void do_paint_control_rect(uint8_t control_ref, const mw_util_rect_t *invalid_rect)
{
	uint16_t vertical_edge_counter;
	uint16_t horizontal_edge_counter;
	int16_t previous_rect_left;
	uint16_t previous_rect_width;
	bool rect_waiting_to_be_painted;
	uint16_t horiz_edges_count;
	uint16_t vert_edges_count;
	mw_util_rect_t rect_current;
	mw_util_rect_t rect_previous;
	mw_util_rect_t invalid_rect_copy;

	MW_ASSERT(control_ref < MW_MAX_CONTROL_COUNT);
	MW_ASSERT(invalid_rect);

    /* check if this control is used, visible and not parent window not minimised; if not give up */
	if (!(mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_VISIBLE) ||
			!(mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_USED) ||
			(mw_all_windows[mw_all_controls[control_ref].parent].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
	{
		return;
	}

	invalid_rect_copy.x = mw_all_controls[control_ref].control_rect.x + invalid_rect->x;
	if (invalid_rect_copy.x > mw_all_controls[control_ref].control_rect.x + mw_all_controls[control_ref].control_rect.width)
	{
		return;
	}

	invalid_rect_copy.y = mw_all_controls[control_ref].control_rect.y + invalid_rect->y;
	if (invalid_rect_copy.y > mw_all_controls[control_ref].control_rect.y + mw_all_controls[control_ref].control_rect.height)
	{
		return;
	}

	invalid_rect_copy.width = invalid_rect->width;
	if (invalid_rect_copy.x + invalid_rect_copy.width >
		mw_all_controls[control_ref].control_rect.x + mw_all_controls[control_ref].control_rect.width)
	{
		invalid_rect_copy.width -= ((invalid_rect_copy.x + invalid_rect_copy.width) -
									(mw_all_controls[control_ref].control_rect.x + mw_all_controls[control_ref].control_rect.width));
	}

	invalid_rect_copy.height = invalid_rect->height;
	if (invalid_rect_copy.y + invalid_rect_copy.height >
		mw_all_controls[control_ref].control_rect.y + mw_all_controls[control_ref].control_rect.height)
	{
		invalid_rect_copy.height -= ((invalid_rect_copy.y + invalid_rect_copy.height) -
									(mw_all_controls[control_ref].control_rect.y + mw_all_controls[control_ref].control_rect.height));
	}

	find_rect_window_intersections(&invalid_rect_copy, &horiz_edges_count, &vert_edges_count);

	/* iterate through horizontal edges, i.e. row at a time */
	for (horizontal_edge_counter = 0; horizontal_edge_counter < horiz_edges_count - 1; horizontal_edge_counter++)
	{
		rect_waiting_to_be_painted = false;
		rect_current.y = horizontal_edges[horizontal_edge_counter];
		rect_current.height = (horizontal_edges[horizontal_edge_counter + 1] - rect_current.y);

		/* iterate through vertical edges along current row */
		for(vertical_edge_counter = 0; vertical_edge_counter < vert_edges_count - 1; vertical_edge_counter++)
		{
			/* get next rect in current row to examine */
			rect_current.x = vertical_edges[vertical_edge_counter];
			rect_current.width = (vertical_edges[vertical_edge_counter + 1] - rect_current.x);

			/* find z order of containing window */
			if (find_highest_z_order_at_point(rect_current.x, rect_current.y) !=
					mw_all_windows[mw_all_controls[control_ref].parent].z_order)
			{
				if (rect_waiting_to_be_painted)
				{
					do_paint_control2(control_ref, &rect_previous);
					rect_waiting_to_be_painted = false;
				}
				continue;
			}

			previous_rect_left = rect_previous.x;
			previous_rect_width = rect_previous.width;
			memcpy(&rect_previous, &rect_current, sizeof(mw_util_rect_t));

			if (rect_waiting_to_be_painted)
			{
				rect_previous.x = previous_rect_left;
				rect_previous.width += previous_rect_width;
			}
			rect_waiting_to_be_painted = true;
		}

		if (rect_waiting_to_be_painted)
		{
			do_paint_control2(control_ref, &rect_previous);
		}
	}
}

/**
 * The first half of the implementation of painting a control's client area
 *
 * @param control_ref Position in array of all controls of this control
 * @note The first half of the control painting process is identifying the rects the control's area needs breaking
 *       up into according to the other windows overlapping it
 */
static void do_paint_control(uint8_t control_ref)
{
	uint16_t vertical_edge_counter;
	uint16_t horizontal_edge_counter;
	int16_t previous_rect_left;
	uint16_t previous_rect_width;
	bool rect_waiting_to_be_painted;
	uint16_t horiz_edges_count;
	uint16_t vert_edges_count;
	mw_util_rect_t rect_current;
	mw_util_rect_t rect_previous;

	MW_ASSERT(control_ref < MW_MAX_CONTROL_COUNT);

    /* check if this control is used, visible and not parent window not minimised; if not give up */
	if (!(mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_VISIBLE) ||
			!(mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_USED) ||
			(mw_all_windows[mw_all_controls[control_ref].parent].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
	{
		return;
	}

	find_rect_window_intersections(&mw_all_controls[control_ref].control_rect, &horiz_edges_count, &vert_edges_count);

	/* iterate through horizontal edges, i.e. row at a time */
	for (horizontal_edge_counter = 0; horizontal_edge_counter < horiz_edges_count - 1; horizontal_edge_counter++)
	{
		rect_waiting_to_be_painted = false;
		rect_current.y = horizontal_edges[horizontal_edge_counter];
		rect_current.height = (horizontal_edges[horizontal_edge_counter + 1] - rect_current.y);

		/* iterate through vertical edges along current row */
		for(vertical_edge_counter = 0; vertical_edge_counter < vert_edges_count - 1; vertical_edge_counter++)
		{
			/* get next rect in current row to examine */
			rect_current.x = vertical_edges[vertical_edge_counter];
			rect_current.width = (vertical_edges[vertical_edge_counter + 1] - rect_current.x);

			/* find z order of containing window */
			if (find_highest_z_order_at_point(rect_current.x, rect_current.y) !=
					mw_all_windows[mw_all_controls[control_ref].parent].z_order)
			{
				if (rect_waiting_to_be_painted)
				{
					do_paint_control2(control_ref, &rect_previous);
					rect_waiting_to_be_painted = false;
				}
				continue;
			}

			previous_rect_left = rect_previous.x;
			previous_rect_width = rect_previous.width;
			memcpy(&rect_previous, &rect_current, sizeof(mw_util_rect_t));

			if (rect_waiting_to_be_painted)
			{
				rect_previous.x = previous_rect_left;
				rect_previous.width += previous_rect_width;
			}
			rect_waiting_to_be_painted = true;
		}

		if (rect_waiting_to_be_painted)
		{
			do_paint_control2(control_ref, &rect_previous);
		}
	}
}

/**
 * The second half of the implementation of painting a control's client area
 *
 * @param control_ref Position in array of all controls of this control
 * @param invalid_rect Rect describing the area of the client that will be painted this time
 * @note The second half of the client painting process the painting of the control's area
 *       is performed by calling the control's paint function. This function is called multiple times with
 *       different clip rects.
 */
static void do_paint_control2(uint8_t control_ref, const mw_util_rect_t *invalid_rect)
{
	mw_gl_draw_info_t client_draw_info;
	uint8_t parent_window_ref;
	int16_t client_area_overspill;

	MW_ASSERT(control_ref < MW_MAX_CONTROL_COUNT);
	MW_ASSERT(invalid_rect);

	client_draw_info.clip_rect.x = invalid_rect->x - mw_all_controls[control_ref].control_rect.x;
	client_draw_info.clip_rect.y = invalid_rect->y - mw_all_controls[control_ref].control_rect.y;
	client_draw_info.clip_rect.width = invalid_rect->width;
	client_draw_info.clip_rect.height = invalid_rect->height;
	client_draw_info.origin_x = mw_all_controls[control_ref].control_rect.x;
	client_draw_info.origin_y = mw_all_controls[control_ref].control_rect.y;

	/* control rect paint area is relative to window edges but control must be drawn relative to window client area
	 * edges so reduce clip width if paint area over-spills border; controls cannot over-spill title bar */
	parent_window_ref = mw_all_controls[control_ref].parent;
	client_area_overspill = (client_draw_info.origin_x + client_draw_info.clip_rect.width) -
			(mw_all_windows[parent_window_ref].client_rect.x + mw_all_windows[parent_window_ref].client_rect.width);

	/* check for overspill greater than clip rect width as this would mean a negative width to draw */
	if (client_area_overspill >= client_draw_info.clip_rect.width)
	{
		/* its greater, nothing to draw so give up */
		return;
	}

	/* there is overspill so adjust clip width for it */
	if (client_area_overspill > 0)
	{
		client_draw_info.clip_rect.width -= client_area_overspill;
	}

	client_area_overspill = (client_draw_info.origin_y + client_draw_info.clip_rect.height) -
			(mw_all_windows[parent_window_ref].client_rect.y + mw_all_windows[parent_window_ref].client_rect.height);

	/* check for overspill greater than clip rect height as this would mean a negative height to draw */
	if (client_area_overspill >= client_draw_info.clip_rect.height)
	{
		/* its greater, nothing to draw so give up */
		return;
	}

	/* there is overspill so adjust clip height for it */
	if (client_area_overspill > 0)
	{
		client_draw_info.clip_rect.height -= client_area_overspill;
	}

	mw_all_controls[control_ref].paint_func(control_ref, &client_draw_info);
}

/**
 * Check if a touch event has been raised and if so process it or send it to the appropriate recipient.
 *
 * @return One of window_redimensioning_state_t depending on if window is being resized, moved or neither
 */
static window_redimensioning_state_t process_touch_event(void)
{
	static mw_hal_touch_state_t old_touch_state = MW_HAL_TOUCH_STATE_UP;
	static window_redimensioning_state_t window_redimensioning_state = WINDOW_NOT_BEING_REDIMENSIONED;
	static uint8_t window_being_redimensioned;
	static int16_t touch_x_old;
	static int16_t touch_y_old;
	static uint32_t last_process_time = 0;
	int16_t touch_x;
	int16_t touch_y;
	int16_t difference_x = 0;
	int16_t difference_y = 0;
	uint8_t window_to_receive_message = MW_ROOT_WINDOW_ID;
	uint8_t control_to_receive_message;
	int16_t client_x;
	int16_t client_y;
	uint8_t touch_message;
	touch_event_t touch_event = TOUCH_EVENT_NONE;
	mw_hal_touch_state_t touch_state;
	bool is_window_overlapped;

	/* check if it's time to process another touch event yet */
	if (mw_tick_counter - last_process_time < MW_TOUCH_INTERVAL_TICKS)
	{
		return window_redimensioning_state;
	}

	/* it is time, so remember the time now */
	last_process_time = mw_tick_counter;

	/* get the current touch state and measurements from the screen */
	touch_state = mw_touch_get_display_touch((uint16_t *)&touch_x, (uint16_t *)&touch_y);

	/* check for a touch state change from the last time round and create an up or down event if the state has changed */
	if (touch_state == MW_HAL_TOUCH_STATE_DOWN && old_touch_state == MW_HAL_TOUCH_STATE_UP)
	{
		touch_event = TOUCH_EVENT_DOWN;
	}
	else if (touch_state == MW_HAL_TOUCH_STATE_UP && old_touch_state == MW_HAL_TOUCH_STATE_DOWN)
	{
		touch_event = TOUCH_EVENT_UP;
	}
	else
	{
		/* no up or down touch state change detected so temporarily set to none, may be set to drag later */
		touch_event = TOUCH_EVENT_NONE;
	}

	/* cache current touch state for next time round */
	old_touch_state = touch_state;

	/* if the touch state is down but there is no outstanding touch event pending then check for a touch drag */
	if (touch_state == MW_HAL_TOUCH_STATE_DOWN && touch_event == TOUCH_EVENT_NONE)
	{
		/* work out the touch differences from last time to determine if a drag has occurred */
		difference_x = touch_x - touch_x_old;
		difference_y = touch_y - touch_y_old;

		/* check if there has been movement since last time above the threshold for a drag */
		if (abs(difference_x) > MW_DRAG_THRESHOLD_PIXELS || abs(difference_y) > MW_DRAG_THRESHOLD_PIXELS)
		{
			/* drag event happened */
			touch_event = TOUCH_EVENT_DRAG;

			/* cache current touch points for next time round */
			touch_x_old = touch_x;
			touch_y_old = touch_y;
		}
		else
		{
			/* hold down event happened */
			touch_event = TOUCH_EVENT_HOLD_DOWN;
		}
	}

	/* check for any outstanding touch event */
	if (touch_event == TOUCH_EVENT_NONE)
	{
		/* no touch event to process so return */
		return window_redimensioning_state;
	}

	if (touch_event == TOUCH_EVENT_DOWN)
	{
		/* there's been a touch down event, cache the points for any subsequent drag or touch up next time round */
		touch_x_old = touch_x;
		touch_y_old = touch_y;

		/* need to send a touch down message as there has been a touch down event */
		touch_message = MW_TOUCH_DOWN_MESSAGE;
	}
	else if (touch_event == TOUCH_EVENT_HOLD_DOWN)
	{
		/* need to send a touch hold down message as there has been a touch hold down event */
		touch_message = MW_TOUCH_HOLD_DOWN_MESSAGE;
	}
	else if (touch_event == TOUCH_EVENT_UP)
	{
		/* check if a window is being redimensioned */
		if (window_redimensioning_state != WINDOW_NOT_BEING_REDIMENSIONED)
		{
			/* it is but re-dimensioning has now ended by the touch up event */
			window_redimensioning_state = WINDOW_NOT_BEING_REDIMENSIONED;
			mw_paint_all();

			/* touch up event now consumed */
			return WINDOW_NOT_BEING_REDIMENSIONED;
		}

		/* there's been a touch up event, can't read screen so use last recorded position */
		touch_x = touch_x_old;
		touch_y = touch_y_old;

		/* need to send a touch up message as there has been a touch up event */
		touch_message = MW_TOUCH_UP_MESSAGE;
	}
	else
	{
		/* touch event is TOUCH_EVENT_DRAG, check if a window redimensioning is ongoing */
		if (window_redimensioning_state == WINDOW_BEING_MOVED)
		{
			/* a window is being moved */
			mw_reposition_window(window_being_redimensioned,
					mw_all_windows[window_being_redimensioned].window_rect.x + difference_x,
					mw_all_windows[window_being_redimensioned].window_rect.y + difference_y);

			/* draw the new position as a dashed outline */
			draw_redimensioning_window_outline(window_being_redimensioned);

			/* touch drag event now consumed */
			return WINDOW_BEING_MOVED;
		}

		if (window_redimensioning_state == WINDOW_BEING_RESIZED)
		{
			/* a window is being resized */
			if (mw_resize_window(window_being_redimensioned,
					mw_all_windows[window_being_redimensioned].window_rect.width - difference_x,
					mw_all_windows[window_being_redimensioned].window_rect.height - difference_y))
			{
				/* resize was allowed, reposition window as resize from top left causes a window reposition too */
				mw_reposition_window(window_being_redimensioned,
						mw_all_windows[window_being_redimensioned].window_rect.x + difference_x,
						mw_all_windows[window_being_redimensioned].window_rect.y + difference_y);

				/* draw the new size and position as a dashed outline */
				draw_redimensioning_window_outline(window_being_redimensioned);
			}

			/* touch drag event now consumed */
			return WINDOW_BEING_RESIZED;
		}

		/* there's been a touch drag event that's not redimensioning so need to send a drag message */
		touch_message = MW_TOUCH_DRAG_MESSAGE;
	}

	/* mark the touch event as consumed as it has been translated into a touch message type now */
	touch_event = TOUCH_EVENT_NONE;

	/* find window this touch event occurred in */
	window_to_receive_message = find_window_point_is_in(touch_x, touch_y);

	/* now send touch message to appropriate window first checking root window */
	if (window_to_receive_message == MW_ROOT_WINDOW_ID)
	{
		/* only send if there's not a modal window showing */
		if (!mw_is_any_window_modal())
		{
			/* touch on root window so send it straight away */
			mw_post_message(touch_message,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_ROOT_WINDOW_ID,
					(((uint32_t)touch_x) << 16) | touch_y,
					MW_WINDOW_MESSAGE);
		}

		return window_redimensioning_state;
	}

	/* check if the window the touch was in does not have focus */
	if (window_to_receive_message != window_with_focus)
	{
		/* it doesn't but only give touched window focus if there's not a modal window showing */
		if (mw_is_any_window_modal())
		{
			/* there's a modal window showing so ignore this touch event */
			return window_redimensioning_state;
		}

		/* paint frame of window losing focus */
		mw_paint_window_frame(window_with_focus, MW_WINDOW_FRAME_COMPONENT_ALL);

		/* find if this window is overlapped now before giving it focus which brings it to the front */
		is_window_overlapped = find_if_window_is_overlapped(window_to_receive_message);

		/* bring touched window to front which will give it focus */
		mw_bring_window_to_front(window_to_receive_message);

		/* paint frame of window gaining focus */
		mw_paint_window_frame(window_to_receive_message, MW_WINDOW_FRAME_COMPONENT_ALL);

		/* paint client of window gaining focus if it was overlapped by any other window */
		if (is_window_overlapped)
		{
			mw_paint_window_client(window_to_receive_message);
		}

		/* check if the touch event should now be passed on to the window */
		if (!(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_TOUCH_FOCUS_AND_EVENT))
		{
			/* it shouldn't so this touch event has now been consumed */
			return window_redimensioning_state;
		}
	}

	/* check for touch on border */
	if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_FLAG_HAS_BORDER)
	{
		/* check for a touch on bottom border */
		if (touch_y >= mw_all_windows[window_to_receive_message].window_rect.y +
				mw_all_windows[window_to_receive_message].window_rect.height - MW_BORDER_WIDTH)
		{
			return window_redimensioning_state;
		}

		if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
		{
			/* check for a touch on left border */
			if (touch_x < mw_all_windows[window_to_receive_message].window_rect.x + MW_BORDER_WIDTH &&
					touch_y > MW_TITLE_BAR_HEIGHT)
			{
				return window_redimensioning_state;
			}

			/* check for a touch on right border */
			if ((touch_x >= mw_all_windows[window_to_receive_message].window_rect.x +
					mw_all_windows[window_to_receive_message].window_rect.width - MW_BORDER_WIDTH) &&
					touch_y > MW_TITLE_BAR_HEIGHT)
			{
				return window_redimensioning_state;
			}
		}
		else
		{
			/* check for a touch on top border */
			if (touch_y < mw_all_windows[window_to_receive_message].window_rect.y + MW_BORDER_WIDTH)
			{
				return window_redimensioning_state;
			}

			/* check for a touch on left border */
			if (touch_x < mw_all_windows[window_to_receive_message].window_rect.x + MW_BORDER_WIDTH)
			{
				return window_redimensioning_state;
			}

			/* check for a touch on right border */
			if (touch_x >= mw_all_windows[window_to_receive_message].window_rect.x +
					mw_all_windows[window_to_receive_message].window_rect.width - MW_BORDER_WIDTH)
			{
				return window_redimensioning_state;
			}
		}
	}

	/* touch occurred in a window with focus so find out if it occurred in
	 * dead zone in bottom right corner of window with both scroll bars */

	if ((mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_HAS_VERT_SCROLL_BAR) &&
			(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_HAS_HORIZ_SCROLL_BAR))
	{
		if (touch_x > mw_all_windows[window_to_receive_message].client_rect.x +
				mw_all_windows[window_to_receive_message].client_rect.width &&
				touch_y > mw_all_windows[window_to_receive_message].client_rect.y +
								mw_all_windows[window_to_receive_message].client_rect.height)
		{
			return window_redimensioning_state;
		}
	}

	/* check if touch occurred in vertical scroll bar */
	if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_HAS_VERT_SCROLL_BAR)
	{
		if (touch_x > mw_all_windows[window_to_receive_message].client_rect.x +
				mw_all_windows[window_to_receive_message].client_rect.width &&
				touch_y >= mw_all_windows[window_to_receive_message].client_rect.y)
		{
			/* check if scroll bar disabled */
			if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOWS_VERT_SCROLL_BAR_ENABLED)
			{
				/* enabled so post message and redraw scroll bar */
				if (touch_message == MW_TOUCH_DOWN_MESSAGE || touch_message == MW_TOUCH_DRAG_MESSAGE)
				{
					int16_t scaled_touch_y;
					uint8_t new_scroll_position;

					/* scale touch point to middle 90% of scroll bar length */
					scaled_touch_y = mw_ui_common_scale_scroll_bar_touch_point(mw_all_windows[window_to_receive_message].client_rect.height,
							touch_y - mw_all_windows[window_to_receive_message].client_rect.y);

					new_scroll_position = (uint8_t)(UINT8_MAX * scaled_touch_y / mw_all_windows[window_to_receive_message].client_rect.height);
					if (new_scroll_position != mw_all_windows[window_to_receive_message].vert_scroll_pos)
					{
						/* only repaint if the scroll slider position has changed */
						mw_all_windows[window_to_receive_message].vert_scroll_pos = new_scroll_position;

						/* just paint vertical scroll bar */
						mw_paint_window_frame(window_to_receive_message, MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR);

						mw_post_message(MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE,
								MW_UNUSED_MESSAGE_PARAMETER,
								window_to_receive_message,
								mw_all_windows[window_to_receive_message].vert_scroll_pos,
								MW_WINDOW_MESSAGE);
					}
				}
			}
			return window_redimensioning_state;
		}
	}

	/* check if touch occurred in horizontal scroll bar */
	if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_HAS_HORIZ_SCROLL_BAR)
	{
		if (touch_y > mw_all_windows[window_to_receive_message].client_rect.y +
				mw_all_windows[window_to_receive_message].client_rect.height &&
				touch_x >= mw_all_windows[window_to_receive_message].client_rect.x)
		{
			/* check if scroll bar disabled */
			if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOWS_HORIZ_SCROLL_BAR_ENABLED)
			{
				/* enabled so post message and redraw scroll bar */
				if (touch_message == MW_TOUCH_DOWN_MESSAGE || touch_message == MW_TOUCH_DRAG_MESSAGE)
				{
					int16_t scaled_touch_x;
					uint8_t new_scroll_position;

					/* scale touch point to middle 90% of scroll bar length */
					scaled_touch_x = mw_ui_common_scale_scroll_bar_touch_point(mw_all_windows[window_to_receive_message].client_rect.width,
							touch_x - mw_all_windows[window_to_receive_message].client_rect.x);

					new_scroll_position = (uint8_t)(UINT8_MAX * scaled_touch_x / mw_all_windows[window_to_receive_message].client_rect.width);
					if (new_scroll_position != mw_all_windows[window_to_receive_message].horiz_scroll_pos)
					{
						/* only repaint if the scroll slider position has changed */
						mw_all_windows[window_to_receive_message].horiz_scroll_pos = new_scroll_position;

						/* just paint horizontal scroll bar */
						mw_paint_window_frame(window_to_receive_message, MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR);

						mw_post_message(MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE,
								MW_UNUSED_MESSAGE_PARAMETER,
								window_to_receive_message,
								mw_all_windows[window_to_receive_message].horiz_scroll_pos,
								MW_WINDOW_MESSAGE);
					}
				}
			}
			return window_redimensioning_state;
		}
	}

	/* check if touch occurred on menu bar */
	if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_HAS_MENU_BAR)
	{
		if (touch_y < mw_all_windows[window_to_receive_message].client_rect.y &&
				touch_y > (mw_all_windows[window_to_receive_message].client_rect.y - MW_MENU_BAR_HEIGHT) &&
				(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_MENU_BAR_ENABLED))
		{
			if (touch_message == MW_TOUCH_DOWN_MESSAGE)
			{
				/* loop through the menu items checking the position of the touch point with the running total of the position of the text labels */
				uint16_t next_menu_item_text_left_pos = 0;
				uint8_t i;

				for (i = 0; i < mw_all_windows[window_to_receive_message].menu_bar_items_count; i++)
				{
					if ((touch_x - mw_all_windows[window_to_receive_message].client_rect.x) >= next_menu_item_text_left_pos &&
							(touch_x - mw_all_windows[window_to_receive_message].client_rect.x) <
								next_menu_item_text_left_pos + (int16_t)(strlen(mw_all_windows[window_to_receive_message].menu_bar_items[i]) + 2) * MW_GL_STANDARD_CHARACTER_WIDTH)
					{
						/* check if this particular line is enabled */
						if (mw_util_get_bit(mw_all_windows[window_to_receive_message].menu_bar_item_enables, i))
						{
							/* relevant text label found so cache this in window structure */
							mw_all_windows[window_to_receive_message].window_flags |= MW_WINDOW_MENU_BAR_ITEM_IS_SELECTED;
							mw_all_windows[window_to_receive_message].menu_bar_selected_item = i;

							/* just paint menu bar */
							mw_paint_window_frame(window_to_receive_message, MW_WINDOW_FRAME_COMPONENT_MENU_BAR);

							/* set system timer to animate menu bar item */
							set_system_timer(window_to_receive_message,
									SYSTEM_TIMER_EVENT_MENU_BAR_REDRAW,
									mw_tick_counter + MW_CONTROL_DOWN_TIME);
						}
						break;
					}

					/* increment the running total of the position of the text labels */
					next_menu_item_text_left_pos += (strlen(mw_all_windows[window_to_receive_message].menu_bar_items[i]) + 2) * MW_GL_STANDARD_CHARACTER_WIDTH;
				}
			}

			return window_redimensioning_state;
		}
	}

	/* find out if it occurred in a control */
	control_to_receive_message = find_control_point_is_in(window_to_receive_message, touch_x, touch_y);

	/* check if touch was identified to have occurred in a control */
	if (control_to_receive_message != MW_MAX_CONTROL_COUNT)
	{
		/* touch occurred in a control so send touch message to that control */
		client_x = touch_x - mw_all_controls[control_to_receive_message].control_rect.x;
		client_y = touch_y - mw_all_controls[control_to_receive_message].control_rect.y;

		mw_post_message(touch_message,
				MW_UNUSED_MESSAGE_PARAMETER,
				control_to_receive_message,
				(((uint32_t)client_x) << 16) | client_y,
				MW_CONTROL_MESSAGE);
		return window_redimensioning_state;
	}

	/* touch event did not occur in a control so check if it occurred in window's title bar */
	if (touch_y < mw_all_windows[window_to_receive_message].client_rect.y)
	{
		/* touch was above client rect */
		if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_FLAG_HAS_TITLE_BAR)
		{
			/* touch event occurred on title bar so check if it occurred on close icon */
			if (touch_x > (mw_all_windows[window_to_receive_message].window_rect.x +
					mw_all_windows[window_to_receive_message].window_rect.width) - MW_TITLE_BAR_ICON_OFFSET)
			{
				/* touch event was on close icon; ignore touch if window is modal */
				if (touch_message == MW_TOUCH_DOWN_MESSAGE  &&
						!(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_IS_MODAL))
				{
					/* it was touch down and window isn't modal so close window if it's allowed */
					if (mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_FLAG_CAN_BE_CLOSED)
					{
						/* it's allowed, close it */
						mw_remove_window(window_to_receive_message);
						mw_paint_all();
					}
				}
			}
			/* check if touch occurred on maximise icon */
			else if (touch_x > (mw_all_windows[window_to_receive_message].window_rect.x +
					mw_all_windows[window_to_receive_message].window_rect.width) - (2 * MW_TITLE_BAR_ICON_OFFSET))
			{
				/* touch event was on maximise icon; ignore if window is modal */
				if (touch_message == MW_TOUCH_DOWN_MESSAGE &&
						!(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_IS_MODAL))
				{
					/* it was touch down and window isn't modal so maximise window */
					mw_resize_window(window_to_receive_message, MW_HAL_LCD_WIDTH, MW_HAL_LCD_HEIGHT);
					mw_reposition_window(window_to_receive_message, 0, 0);
					mw_paint_all();
				}
			}
			/* check if touch occurred on minimise icon */
			else if (touch_x > (mw_all_windows[window_to_receive_message].window_rect.x +
					mw_all_windows[window_to_receive_message].window_rect.width) - (3 * MW_TITLE_BAR_ICON_OFFSET))
			{
				/* touch event was on minimise icon; ignore if window is modal */
				if (touch_message == MW_TOUCH_DOWN_MESSAGE &&
						!(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_IS_MODAL))
				{
					/* if window isn't modal so minimise window */
					draw_min_restore_window_effect(window_to_receive_message);
					mw_all_windows[window_to_receive_message].window_flags |= MW_WINDOW_FLAG_IS_MINIMISED;
					set_focus();
					set_system_timer(MW_UNUSED_MESSAGE_PARAMETER,
							SYSTEM_TIMER_EVENT_PAINT_ALL,
							mw_tick_counter + MW_WINDOW_MIN_MAX_EFFECT_TIME);
					mw_post_message(MW_WINDOW_MINIMISED,
							MW_UNUSED_MESSAGE_PARAMETER,
							window_to_receive_message,
							MW_UNUSED_MESSAGE_PARAMETER,
							MW_WINDOW_MESSAGE);
				}
			}
			/* check if touch occurred on resize icon */
			else if (touch_x - mw_all_windows[window_to_receive_message].window_rect.x < MW_TITLE_BAR_ICON_SIZE)
			{
				/* touch event was on resize icon; ignore if window is modal */
				if (touch_message == MW_TOUCH_DOWN_MESSAGE && !(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_IS_MODAL))
				{
					/* window isn't modal so start resize process */
					window_redimensioning_state = WINDOW_BEING_RESIZED;
					window_being_redimensioned = window_to_receive_message;
				}
			}
			else
			{
				/* check for touch anywhere else on title bar which will start a window move */
				if (touch_message == MW_TOUCH_DOWN_MESSAGE && !(mw_all_windows[window_to_receive_message].window_flags & MW_WINDOW_IS_MODAL))
				{
					/* touch is elsewhere on title bar so start move process */
					window_redimensioning_state = WINDOW_BEING_MOVED;
					window_being_redimensioned = window_to_receive_message;
				}
			}
		}

		return window_redimensioning_state;
	}

	/* touch event occurred on client rect */
	client_x = touch_x - mw_all_windows[window_to_receive_message].client_rect.x;
	client_y = touch_y - mw_all_windows[window_to_receive_message].client_rect.y;
	mw_post_message(touch_message,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_to_receive_message,
			(((uint32_t)client_x) << 16) | client_y,
			MW_WINDOW_MESSAGE);

	return window_redimensioning_state;
}

/**
 * The actual implementation of paint all windows, including the root window, starting at root and going
 * up the z order. For each window painted its controls will be painted too.
 */
static void do_paint_all()
{
	uint8_t visible_windows;
	uint8_t windows_painted = 0;
	uint8_t next_z_order = 0;

	/* calculate number of displayed windows to paint, plus 1 for root window */
	visible_windows = find_number_of_displayed_windows() + 1;

	/* loop to paint that number of windows */
	while(windows_painted < visible_windows)
	{
		paint_window_frame_and_client_with_z_order(next_z_order);
		windows_painted++;

		/* move on to next z order */
		next_z_order++;
	}
}

/**
 * Set the front most used visible window with focus
 */
static void set_focus(void)
{
	uint8_t i;
	uint8_t highest_z_order_found = 0;
	uint8_t window_with_highest_z_order = MW_ROOT_WINDOW_ID;

	/* iterate through all windows */
	for (i = 0; i < MW_MAX_WINDOW_COUNT; i++)
	{
		/* check window is used, visible, not minimised and has a z order higher than current highest z order */
		if ((mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) &&
				(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) &&
				!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED) && mw_all_windows[i].z_order > highest_z_order_found)
		{
			/* new highest z order found so save it */
			highest_z_order_found = mw_all_windows[i].z_order;
			window_with_highest_z_order = i;
		}
	}

	/* send message to window that is going to lose focus */
	mw_post_message(MW_WINDOW_LOST_FOCUS_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_with_focus,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_WINDOW_MESSAGE);

	/* send message to all controls in the window that parent window lost focus */
	for (i = 0; i < MW_MAX_CONTROL_COUNT; i++)
	{
		/* check that control belongs to the window losing focus */
		if (mw_all_controls[i].parent == window_with_focus &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_USED))
		{
			mw_post_message(MW_CONTROL_LOST_FOCUS_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					i,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
		}
	}

	window_with_focus = window_with_highest_z_order;

	/* send message to window that is going to gain focus*/
	mw_post_message(MW_WINDOW_GAINED_FOCUS_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_with_focus,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_WINDOW_MESSAGE);

	/* send message to all controls in the window that parent window gained focus */
	for (i = 0; i < MW_MAX_CONTROL_COUNT; i++)
	{
		if (mw_all_controls[i].parent == window_with_focus &&
				(mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_USED))
		{
			mw_post_message(MW_CONTROL_GAINED_FOCUS_MESSAGE,
					MW_UNUSED_MESSAGE_PARAMETER,
					i,
					MW_UNUSED_MESSAGE_PARAMETER,
					MW_CONTROL_MESSAGE);
		}
	}
}

/**
 * Re-number the z orders so that they start at 1 and rise by 1 for each used window but keeping the ordering the same
 */
static void rationalize_z_orders(void)
{
	uint8_t number_of_windows_rationalized = 0;
	uint8_t next_z_order_existing = 0;
	uint8_t next_z_order_rationalized = MW_MIN_Z_ORDER;
	uint8_t i;
	uint8_t existing_window_count;
	
	/* find number of used windows */
	existing_window_count = find_number_of_displayed_windows();

	/* loop until number of windows rationalized is number of used windows */
	while(number_of_windows_rationalized < existing_window_count)
	{
		/* find the next z order beyond the last z order found */
		next_z_order_existing = find_next_z_order(next_z_order_existing);
		
		/* loop through all used user windows */
		for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
		{
			/* if this window's z order is equal to the next existing z order then make this window's z order the next available z order */
			if (mw_all_windows[i].z_order == next_z_order_existing && (mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED) &&
					(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) &&
					!(mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
			{
				mw_all_windows[i].z_order = next_z_order_rationalized;
				
				/* increment number of windows that have been rationalized */
				number_of_windows_rationalized++;
				break;
			}
		}
		
		/* increase the next available z order */		
		next_z_order_rationalized++;
	}

	/* set focus to front most used visible window */
	set_focus();
}

/**
 * Draw the dashed outline of the window being resized or moved
 *
 * @param window_ref The window to draw the outline of
 */
static void draw_redimensioning_window_outline(uint8_t window_ref)
{
	MW_ASSERT(window_ref < MW_MAX_WINDOW_COUNT);

	mw_gl_set_fill(MW_GL_NO_FILL);
	mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
	mw_gl_set_bg_colour(MW_HAL_LCD_WHITE);
	mw_gl_set_line(MW_GL_EQUAL_LARGE_DASH);
	mw_gl_set_bg_transparency(MW_GL_BG_NOT_TRANSPARENT);
	mw_gl_rectangle(&draw_info_root,
			mw_all_windows[window_ref].window_rect.x,
			mw_all_windows[window_ref].window_rect.y,
			mw_all_windows[window_ref].window_rect.width,
			mw_all_windows[window_ref].window_rect.height);
}

/**
 * Set the system timer details and time to fire
 *
 * @param timer_data The generic data parameter for handler to use
 * @param event The event type to trigger
 * @param fire_time The absolute time timer goes off
 */
static void set_system_timer(uint32_t timer_data, system_timer_event_t event, uint32_t fire_time)
{
	system_timer.data = timer_data;
	system_timer.system_timer_event = event;
	system_timer.next_fire_time = fire_time;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_init()
{
	uint8_t i;
	mw_util_rect_t r;
	MATRIX calibration_matrix;

	/* initialise the hardware drivers */
	mw_hal_init();

	/* load the settings from non vol storage */
	mw_settings_load();
	
	/* check settings for intialisation and calibration */
	if (!mw_settings_is_initialised() || !mw_settings_is_calibrated())
	{
		/* settings not initialised or not calibrated so kick off calibrate routine */
		mw_touch_calibrate(&calibration_matrix);
		
		/* set settings to defaults */
		mw_settings_set_to_defaults();
		
		/* save calibration metrics */
		mw_settings_set_calibration_matrix(&calibration_matrix);
		mw_settings_set_calibrated(true);
		
		/* save settings */
		mw_settings_save();
	}

	/* set up root window */
	mw_util_set_rect(&r, 0, 0, MW_ROOT_WIDTH, MW_ROOT_HEIGHT);
	set_window_details(&r,
			"",
			root_paint_function,
			MW_ROOT_WINDOW_ID,
			root_message_function,
			NULL,
			0,
			MW_WINDOW_FLAG_IS_VISIBLE | MW_WINDOW_FLAG_IS_USED,
			NULL);

	/* set root window z order at the bottom */
	mw_all_windows[MW_ROOT_WINDOW_ID].z_order = MW_ROOT_Z_ORDER;

	/* mark all user windows unused */
	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
	   mw_all_windows[i].window_flags &= ~MW_WINDOW_FLAG_IS_USED;
	}

	/* send root window window created message */
	mw_post_message(MW_WINDOW_CREATED_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_ROOT_WINDOW_ID,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_WINDOW_MESSAGE);

	/* initialise client window painting flag */
	in_client_window_paint_function = false;

	/* call the user init function to get all the user windows and controls created */
	mw_user_init();
}

bool mw_find_if_any_window_slots_free(void)
{
	return (find_empty_window_slot() != MW_MAX_WINDOW_COUNT);
}

uint8_t mw_add_window(mw_util_rect_t *rect,
		char* title,
		mw_paint_func_p paint_func,
		mw_message_func_p message_func,
		char **menu_bar_items,
		uint8_t menu_bar_items_count,
		uint32_t window_flags,
		void *instance_data)
{
	uint8_t new_window_id;

	/* check compulsory parameters */
	if (rect == NULL || paint_func == NULL || message_func == NULL || title == NULL)
	{
		MW_ASSERT(false);
		return MW_MAX_WINDOW_COUNT;
	}

	/* check for being called from within a client window paint function */
	if (in_client_window_paint_function)
	{
		MW_ASSERT(false);
		return MW_MAX_WINDOW_COUNT;
	}

	/* check optional parameters */
	if ((window_flags & MW_WINDOW_HAS_MENU_BAR) && (!menu_bar_items || !*menu_bar_items || menu_bar_items_count == 0))
	{
		MW_ASSERT(false);
		return MW_MAX_WINDOW_COUNT;
	}

	/* look for an empty slot in the array of windows */
	new_window_id = find_empty_window_slot();
	if (new_window_id == MW_MAX_WINDOW_COUNT)
	{
		/* no empty slot */	
		MW_ASSERT(false);
		return MW_MAX_WINDOW_COUNT;
	}

	/* sanity check on width compared to border thickness */
	if (rect->width < ((window_flags & MW_WINDOW_FLAG_HAS_BORDER) ? (MW_BORDER_WIDTH * 2) + 1 : 1))
	{
		MW_ASSERT(false);
		return MW_MAX_WINDOW_COUNT;
	}

	/* sanity check dimensions */
	if (!check_window_dimensions(rect->width,
			rect->height,
			window_flags))
	{
		MW_ASSERT(false);
		return MW_MAX_WINDOW_COUNT;
	}

	/* set the new window's details with a z order that will make it the front-most window */
   	set_window_details(rect,
   			title,
   			paint_func,
   			new_window_id,
   			message_func,
			menu_bar_items,
			menu_bar_items_count,
   			window_flags,
			instance_data);

   	/* bring this window to the front */
   	mw_bring_window_to_front(new_window_id);

	/* send window created message to this window's message function */
   	mw_post_message(MW_WINDOW_CREATED_MESSAGE,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			new_window_id,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			MW_WINDOW_MESSAGE);

	return new_window_id;
}

void mw_bring_window_to_front(uint8_t window_ref)
{
	uint8_t max_existing_z_order;

	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

    /* find the highest existing z order of all used windows */
	max_existing_z_order = find_highest_z_order();
    
    /* set the z order to the highest value plus 1 */
	mw_all_windows[window_ref].z_order = max_existing_z_order + 1;
    
    /* rationalize the z orders as there will now be a gap in the numbers */
	rationalize_z_orders();
}

void mw_send_window_to_back(uint8_t window_ref)
{
	uint8_t i;

	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

    /* increase all z orders by 1 */
	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
		mw_all_windows[i].z_order++;
	}
    
    /* set this window's z order to minimum */
	mw_all_windows[window_ref].z_order = MW_MIN_Z_ORDER;
    
    /* rationalize the z orders as there may now be a gap */
	rationalize_z_orders();
}

void mw_set_window_visible(uint8_t window_ref, bool visible)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	/* ignore if not used */
	if (!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED))
	{
		return;
	}

	/* ignore if no change */
	if (visible && (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE))
	{
		return;
	}
	if (!visible && !(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE))
	{
		return;
	}

	/* set window visibility */
	if (visible)
	{
		mw_all_windows[window_ref].window_flags |= MW_WINDOW_FLAG_IS_VISIBLE;
		mw_bring_window_to_front(window_ref);
	}
	else
	{
		mw_all_windows[window_ref].window_flags &= ~MW_WINDOW_FLAG_IS_VISIBLE;
	}
	rationalize_z_orders();

	/* send message to window that visibility has changed */
	mw_post_message(MW_WINDOW_VISIBILITY_CHANGED,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_ref,
			visible,
			MW_WINDOW_MESSAGE);

	/* update focus */
	set_focus();
}

void mw_set_window_minimised(uint8_t window_ref, bool minimised)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	/* ignore if not used or no change */
	if (mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED)
	{
		/* set window minimised state */
		if (minimised)
		{
			mw_all_windows[window_ref].window_flags |= MW_WINDOW_FLAG_IS_MINIMISED;
		}
		else
		{
			mw_all_windows[window_ref].window_flags &= ~MW_WINDOW_FLAG_IS_MINIMISED;
		}

		/* update focus */
		set_focus();
	}
}

void mw_reposition_window(uint8_t window_ref, int16_t new_x, int16_t new_y)
{
	mw_util_rect_t r;
	uint8_t i;

	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}
	
	/* check new_x and new_y for being on screen */
	if (new_x > MW_GL_MAX_X || new_y > MW_GL_MAX_Y || new_x < -mw_all_windows[window_ref].window_rect.width || new_y <  -mw_all_windows[window_ref].window_rect.height)
	{
		return;
	}

	/* fill in a temporary rect with the window's new position details */
	r.width = mw_all_windows[window_ref].window_rect.width;
	r.height = mw_all_windows[window_ref].window_rect.height;
	r.x = new_x;
	r.y = new_y;

	/* loop through all controls */
	for (i = 0; i < MW_MAX_CONTROL_COUNT; i++)
	{
		/* find controls that are used and have this window as parent */
		if (mw_all_controls[i].parent == window_ref && (mw_all_controls[i].control_flags & MW_CONTROL_FLAG_IS_USED))
		{
			/* move the control */
			mw_all_controls[i].control_rect.x += (new_x - mw_all_windows[window_ref].window_rect.x);
			mw_all_controls[i].control_rect.y += (new_y - mw_all_windows[window_ref].window_rect.y);
		}
	}

	/* update the window's client area */
	calculate_new_window_size_details(window_ref, &r);

	/* send a moved message to the window in case it needs to do anything */
	mw_post_message(MW_WINDOW_MOVED,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_ref,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_WINDOW_MESSAGE);
}

bool mw_resize_window(uint8_t window_ref, uint16_t new_width, uint16_t new_height)
{
	mw_util_rect_t r;

	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return false;
	}

	/* check the proposed new window dimensions to see if they are sensible */
	if (!check_window_dimensions(new_width,
			new_height,
			mw_all_windows[window_ref].window_flags))
	{
		return false;
	}

	/* fill in a temporary rect with the window's new position details */
	r.width = new_width;
	r.height = new_height;
	r.x = mw_all_windows[window_ref].window_rect.x;
	r.y = mw_all_windows[window_ref].window_rect.y;

	/* this does the setting of the window's new details */
	calculate_new_window_size_details(window_ref, &r);

	/* send a resize message to the window in case it needs to do anything */
	mw_post_message(MW_WINDOW_RESIZED,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_ref,
			((uint32_t)new_width) << 16 | new_height,
			MW_WINDOW_MESSAGE);

	return true;
}

uint8_t mw_find_window_with_focus(void)
{
	return window_with_focus;
}

bool mw_is_any_window_modal(void)
{
	uint8_t i;

	/* search through all windows */
	for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
	{
		if (mw_all_windows[i].window_flags & MW_WINDOW_IS_MODAL &&
				mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED)
		{
			return true;
		}
	}

	return false;
}

void mw_set_window_modal(uint8_t window_ref, bool modal)
{
	uint8_t i;

	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	if (!modal)
	{
		/* set non-modal */
		mw_all_windows[window_ref].window_flags &= ~MW_WINDOW_IS_MODAL;
	}
	else
	{
		/* can't set an invisible unused or minimised window modal */
		if (!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_VISIBLE) ||
				!(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_USED) ||
				(mw_all_windows[window_ref].window_flags & MW_WINDOW_FLAG_IS_MINIMISED))
		{
			return;
		}

		/* must not be a modal window already */
		for (i = MW_FIRST_USER_WINDOW_ID; i < MW_MAX_WINDOW_COUNT; i++)
		{
			if (mw_all_windows[i].window_flags & MW_WINDOW_FLAG_IS_USED &&
					(mw_all_windows[i].window_flags & MW_WINDOW_IS_MODAL))
			{
				return;
			}
		}

		/* this window is allowed to be set modal */
		mw_all_windows[window_ref].window_flags |= MW_WINDOW_IS_MODAL;
		
		/* a modal window must be at the front so bring it to the front */
		mw_bring_window_to_front(window_ref);
	}
}

void mw_set_menu_bar_enabled_state(uint8_t window_ref, bool enabled)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	if (enabled)
	{
		mw_all_windows[window_ref].window_flags |= MW_WINDOW_MENU_BAR_ENABLED;
	}
	else
	{
		mw_all_windows[window_ref].window_flags &= ~MW_WINDOW_MENU_BAR_ENABLED;
	}
}

void mw_set_menu_bar_items_enabled_state(uint8_t window_ref, uint16_t item_enables)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	mw_all_windows[window_ref].menu_bar_item_enables = item_enables;
}

void mw_set_window_horiz_scroll_bar_enabled_state(uint8_t window_ref, bool enabled)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	if (enabled)
	{
		/* set enabled */	
		mw_all_windows[window_ref].window_flags |= MW_WINDOWS_HORIZ_SCROLL_BAR_ENABLED;
	}
	else
	{
		/* set disabled */
		mw_all_windows[window_ref].window_flags &= ~MW_WINDOWS_HORIZ_SCROLL_BAR_ENABLED;
	}
}

void mw_set_window_vert_scroll_bar_enabled_state(uint8_t window_ref, bool enabled)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	if (enabled)
	{
		/* set enabled */
		mw_all_windows[window_ref].window_flags |= MW_WINDOWS_VERT_SCROLL_BAR_ENABLED;
	}
	else
	{
		/* set disabled */
		mw_all_windows[window_ref].window_flags &= ~MW_WINDOWS_VERT_SCROLL_BAR_ENABLED;
	}
}

void mw_paint_window_frame(uint8_t window_ref, uint8_t components)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}
	
    /* this is the public interface to getting a window frame painted;
     * it does not do the painting but adds a paint request message to the message queue */
	mw_post_message(MW_WINDOW_FRAME_PAINT_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_ref,
			components,
			MW_SYSTEM_MESSAGE);
}

void mw_paint_window_client(uint8_t window_ref)
{
	/* check that the window id is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}
	
    /* this is the public interface to getting a window client area only painted;
     * it does not do the painting but adds a paint request message to the message queue */
	mw_post_message(MW_WINDOW_CLIENT_PAINT_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_ref,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_SYSTEM_MESSAGE);
}

void mw_paint_window_client_rect(uint8_t window_ref, const mw_util_rect_t *rect)
{
	/* check window_ref is in range and pointer not null */
	if (window_ref >= MW_MAX_WINDOW_COUNT || !rect)
	{
		MW_ASSERT(false);
		return;
	}

    /* this is the public interface to getting a part of a  window client area only painted;
     * it does not do the painting but adds a paint request message to the message queue */
	mw_post_message(MW_WINDOW_CLIENT_PAINT_RECT_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			window_ref,
			(uint32_t)rect,
			MW_SYSTEM_MESSAGE);
}

void mw_remove_window(uint8_t window_ref)
{
	uint8_t i;

	/* check window_ref is in range */
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		return;
	}

	/* cannot remove root window */
	if (window_ref == MW_ROOT_WINDOW_ID)
	{
		MW_ASSERT(false);
		return;
	}

	/* remove all controls that have this window as a parent */
	for (i = 0; i < MW_MAX_CONTROL_COUNT; i++)
	{
		if (mw_all_controls[i].parent == window_ref)
		{
			mw_all_controls[i].control_flags &= ~MW_CONTROL_FLAG_IS_USED;
		}
	}

	/* cancel all outstanding timers for this window */
	for (i = 0; i < MW_MAX_TIMER_COUNT; i++)
	{
		if (mw_all_timers[i].next_fire_time > 0 &&
				mw_all_timers[i].recipient_type == MW_WINDOW_MESSAGE &&
				mw_all_timers[i].recipient_id == window_ref)

		{
			/* timers are one shot so mark this timer as unused again */
			mw_all_timers[i].next_fire_time = 0;
		}
	}

	/* send window removed message to window message function */
   	mw_post_message(MW_WINDOW_REMOVED_MESSAGE,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			window_ref,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			MW_WINDOW_MESSAGE);

	/* remove this window by marking it as unused */
	mw_all_windows[window_ref].window_flags &= ~MW_WINDOW_FLAG_IS_USED;

	/* rationalize the z orders in case they are irrational */
	rationalize_z_orders();
}

mw_util_rect_t mw_get_window_client_rect(uint8_t window_ref)
{
	mw_util_rect_t default_rect = {0, 0, 0, 0};

	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return default_rect;
	}

	return mw_all_windows[window_ref].client_rect;
}

void *mw_get_window_instance_data(uint8_t window_ref)
{
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return NULL;
	}

	return mw_all_windows[window_ref].instance_data;
}

bool mw_find_if_any_control_slots_free(void)
{
	return (find_empty_control_slot() != MW_MAX_CONTROL_COUNT);
}

void wm_set_window_title(uint8_t window_ref, char *title_text)
{
	if (window_ref >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	mw_util_safe_strcpy(mw_all_windows[window_ref].title, MW_MAX_TITLE_SIZE, title_text);
}

uint8_t mw_add_control(mw_util_rect_t *rect,
		uint8_t parent,
		mw_paint_func_p paint_func,
		mw_message_func_p message_func,
		uint16_t control_flags,
		void *instance_data)
{
	uint8_t new_control_id;

	/* check for null parameters */
	if (rect == NULL || instance_data == NULL || paint_func == NULL || message_func == NULL)
	{
		MW_ASSERT(false);
		return MW_MAX_CONTROL_COUNT;
	}

	/* check for being called from within a client window paint function */
	if (in_client_window_paint_function)
	{
		MW_ASSERT(false);
		return MW_MAX_CONTROL_COUNT;
	}

	/* cannot add a control to an unused window or the root window so filter these out */
	if (!(mw_all_windows[parent].window_flags & MW_WINDOW_FLAG_IS_USED) || parent == MW_ROOT_WINDOW_ID)
	{
		MW_ASSERT(false);
		return MW_MAX_CONTROL_COUNT;
	}

	/* don't allow control to start above or to left of parent window client rect */
	if (rect->x < 0 || rect->y < 0)
	{
		MW_ASSERT(false);
		return MW_MAX_CONTROL_COUNT;
	}

	/* look for an empty slot in the array of controls */
	new_control_id = find_empty_control_slot();
	if (new_control_id == MW_MAX_CONTROL_COUNT)
	{
		/* no empty slot */
		MW_ASSERT(false);
		return MW_MAX_CONTROL_COUNT;
	}

	/* set this control's details */
   	set_control_details(rect,
   			paint_func,
   			new_control_id,
   			message_func,
   			parent,
   			control_flags,
			instance_data);

	/* send control created message to this control's message function */
   	mw_post_message(MW_CONTROL_CREATED_MESSAGE,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			new_control_id,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			MW_CONTROL_MESSAGE);

   	if (parent == window_with_focus)
   	{
   		/* send control a gained focus message if parent window has focus */
   	   	mw_post_message(MW_CONTROL_GAINED_FOCUS_MESSAGE,
   	   			MW_UNUSED_MESSAGE_PARAMETER,
   	   			new_control_id,
   	   			MW_UNUSED_MESSAGE_PARAMETER,
   	   			MW_CONTROL_MESSAGE);
   	}

	return new_control_id;
}

void mw_set_control_visible(uint8_t control_ref, bool visible)
{
	/* check that the control id is in range */
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	/* ignore if not used */
	if (!(mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_USED))
	{
		return;
	}

	/* ignore if no change */
	if (visible && (mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_VISIBLE))
	{
		return;
	}
	if (!visible && !(mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_VISIBLE))
	{
		return;
	}

	if (visible)
	{
		/* set visible */
		mw_all_controls[control_ref].control_flags |= MW_CONTROL_FLAG_IS_VISIBLE;

		/* post focus gained message to control */
		mw_post_message(MW_CONTROL_GAINED_FOCUS_MESSAGE,
				MW_UNUSED_MESSAGE_PARAMETER,
				control_ref,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_CONTROL_MESSAGE);
	}
	else
	{
		/* set invisible */
		mw_all_controls[control_ref].control_flags &= ~MW_CONTROL_FLAG_IS_VISIBLE;

		/* post focus lost message to control */
		mw_post_message(MW_CONTROL_LOST_FOCUS_MESSAGE,
				MW_UNUSED_MESSAGE_PARAMETER,
				control_ref,
				MW_UNUSED_MESSAGE_PARAMETER,
				MW_CONTROL_MESSAGE);
	}
}

void mw_set_control_enabled(uint8_t control_ref, bool enabled)
{
	/* check that the control id is in range */
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	/* ignore if control is not used */
	if (mw_all_controls[control_ref].control_flags & MW_CONTROL_FLAG_IS_USED)
	{
		if (enabled)
		{
			/* set enabled */
			mw_all_controls[control_ref].control_flags |= MW_CONTROL_FLAG_IS_ENABLED;
		}
		else
		{
			/* set disabled */
			mw_all_controls[control_ref].control_flags &= ~MW_CONTROL_FLAG_IS_ENABLED;
		}
	}
}

void mw_paint_control(uint8_t control_ref)
{
	/* check that the control id is in range */
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return;
	}
	
    /* this is the public interface to getting a control painted;
     * it does not do the painting but adds a paint request message to the message queue */
	mw_post_message(MW_CONTROL_PAINT_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			control_ref,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_SYSTEM_MESSAGE);
}

void mw_paint_control_rect(uint8_t control_ref, const mw_util_rect_t *rect)
{
	/* check that the control id is in range */
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

    /* this is the public interface to getting a control rect painted;
     * it does not do the painting but adds a paint request message to the message queue */
	mw_post_message(MW_CONTROL_PAINT_RECT_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			control_ref,
			(uint32_t)rect,
			MW_SYSTEM_MESSAGE);
}

void mw_remove_control(uint8_t control_ref)
{
	uint8_t i;

	/* check that the control id is in range */
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		return;
	}

	/* cancel all outstanding timers for this control */
	for (i = 0; i < MW_MAX_TIMER_COUNT; i++)
	{
		if (mw_all_timers[i].next_fire_time > 0 &&
				mw_all_timers[i].recipient_type == MW_CONTROL_MESSAGE &&
				mw_all_timers[i].recipient_id == control_ref)

		{
			/* timers are one shot so mark this timer as unused again */
			mw_all_timers[i].next_fire_time = 0;
		}
	}

	/* post control removed message to control message function */
   	mw_post_message(MW_CONTROL_REMOVED_MESSAGE,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			control_ref,
   			MW_UNUSED_MESSAGE_PARAMETER,
   			MW_CONTROL_MESSAGE);

	/* remove this control by marking it as unused */
   	mw_all_controls[control_ref].control_flags &= ~MW_CONTROL_FLAG_IS_USED;
}

mw_util_rect_t mw_get_control_rect(uint8_t control_ref)
{
	mw_util_rect_t default_rect = {0, 0, 0, 0};

	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return default_rect;
	}

	return mw_all_controls[control_ref].control_rect;
}

uint8_t mw_get_control_parent_window(uint8_t control_ref)
{
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return 0;
	}

	return mw_all_controls[control_ref].parent;
}

void *mw_get_control_instance_data(uint8_t control_ref)
{
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return NULL;
	}

	return mw_all_controls[control_ref].instance_data;
}

uint16_t mw_get_control_flags(uint8_t control_ref)
{
	if (control_ref >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return 0;
	}

	return mw_all_controls[control_ref].control_flags;
}

uint8_t mw_set_timer(uint32_t fire_time, uint8_t recipient_id, mw_message_recipient_type_t recipient_type)
{
	uint8_t i;

	/* reject fire time in the past */
	if (fire_time <= mw_tick_counter)
	{
		return MW_MAX_TIMER_COUNT;
	}

	/* reject any other recipient than window or control */
	if (recipient_type != MW_WINDOW_MESSAGE && recipient_type != MW_CONTROL_MESSAGE)
	{
		MW_ASSERT(false);
		return MW_MAX_TIMER_COUNT;
	}
	
	/* check that recipient id is in range for recipient type */
	if (recipient_type == MW_WINDOW_MESSAGE && recipient_id > MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return MW_MAX_TIMER_COUNT;
	}
	if (recipient_type == MW_CONTROL_MESSAGE && recipient_id > MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return MW_MAX_TIMER_COUNT;
	}	

	for (i = 0; i < MW_MAX_TIMER_COUNT; i++)
	{
		/* find an unused slot */
		if (mw_all_timers[i].next_fire_time == 0)
		{
			/* slot found, set details */
			mw_all_timers[i].next_fire_time = fire_time;
			mw_all_timers[i].recipient_id = recipient_id;
			mw_all_timers[i].recipient_type = recipient_type;
			return i;
		}
	}

	/* failed to find an empty timer slot */
	MW_ASSERT(false);

	return MW_MAX_TIMER_COUNT;
}

void mw_cancel_timer(uint8_t timer_id)
{
	uint8_t i;
	mw_message_t *message;

	/* sanity check on timer id */
	if (timer_id >= MW_MAX_TIMER_COUNT)
	{
		MW_ASSERT(false);
		return;
	}

	/* an unused timer has its fire time at zero */
	mw_all_timers[timer_id].next_fire_time = 0;

	/* mark any pending timer messages in message queue for this timer_id as cancelled */
	for (i = 0; i < MW_MESSAGE_QUEUE_SIZE; i++)
	{
		message = mw_message_queue_get_ref_to_item_at_position(i);
		MW_ASSERT(message);

		if (message->message_id == MW_WINDOW_TIMER_MESSAGE && message->message_data == timer_id)
		{
			/* this leaves the message in the message queue but marks it as to be ignored when the message is processed */
			message->message_recipient_type = MW_CANCELLED_MESSAGE;
		}
	}
}

void mw_post_message(uint8_t message_id, uint8_t sender_id, uint8_t recipient_id, uint32_t message_data, mw_message_recipient_type_t recipient_type)
{
	mw_message_t new_message;
	
	/* check recipient id for type makes sense */
	if (recipient_type == MW_WINDOW_MESSAGE && recipient_id >= MW_MAX_WINDOW_COUNT)
	{
		MW_ASSERT(false);
		return;
	}
	if (recipient_type == MW_CONTROL_MESSAGE && recipient_id >= MW_MAX_CONTROL_COUNT)
	{
		MW_ASSERT(false);
		return;
	}	

	/* fill in the message fields from supplied parameters */
	new_message.message_id = message_id;
	new_message.message_data = message_data;
	new_message.message_recipient_type = recipient_type;
	new_message.recipient_id = recipient_id;
	new_message.sender_id = sender_id;

	/* do not send messages to unused windows */
	if ((new_message.message_recipient_type == MW_WINDOW_MESSAGE && (mw_all_windows[new_message.recipient_id].window_flags & MW_WINDOW_FLAG_IS_USED)) ||
		(new_message.message_recipient_type == MW_CONTROL_MESSAGE && (mw_all_controls[new_message.recipient_id].control_flags & MW_CONTROL_FLAG_IS_USED)) ||
		new_message.message_recipient_type == MW_SYSTEM_MESSAGE)
	{
		/* add this message to the queue, asserting that there is space in the queue */
		MW_ASSERT(mw_message_queue_insert(&new_message));
	}
}

bool mw_process_message(void)
{
	uint8_t i;
	mw_message_t message;
	window_redimensioning_state_t redimensioning_window_state;

	/* handle any outstanding touch screen events */
	redimensioning_window_state = process_touch_event();

	/* only process timer event if not redimensioning a window */
	if (redimensioning_window_state == WINDOW_NOT_BEING_REDIMENSIONED)
	{
		/* process system timer */
		if (system_timer.next_fire_time > 0 && mw_tick_counter >= system_timer.next_fire_time)
		{
			system_timer.next_fire_time = 0;
			switch (system_timer.system_timer_event)
			{
			case SYSTEM_TIMER_EVENT_MENU_BAR_REDRAW:
				/* menu bar item needs drawing as back up */
				mw_all_windows[system_timer.data].window_flags &= ~MW_WINDOW_MENU_BAR_ITEM_IS_SELECTED;

				/* menu bar selected event is posted to owning window on up redraw so now post menu bar item select message to owning window */
				mw_post_message(MW_MENU_BAR_ITEM_PRESSED_MESSAGE,
						MW_UNUSED_MESSAGE_PARAMETER,
						system_timer.data,
						mw_all_windows[system_timer.data].menu_bar_selected_item,
						MW_WINDOW_MESSAGE);

				/* window frame needs repainting to update appearance of menu bar */
				mw_paint_window_frame(system_timer.data, MW_WINDOW_FRAME_COMPONENT_MENU_BAR);
				break;

			case SYSTEM_TIMER_EVENT_PAINT_ALL:
				mw_paint_all();
				break;

			default:
				break;
			}
		}

		/* iterate through all other timers and post a message to windows/controls on any expired timers */
		for (i = 0; i < MW_MAX_TIMER_COUNT; i++)
		{
			/* check fire time of this timer to current time */
			if (mw_all_timers[i].next_fire_time > 0 && mw_tick_counter >= mw_all_timers[i].next_fire_time)
			{
				/* timers are one shot so mark this timer as unused again */
				mw_all_timers[i].next_fire_time = 0;

				/* check recipient type */
				if (mw_all_timers[i].recipient_type == MW_WINDOW_MESSAGE)
				{
					/* check if recipient id is sensible */
					if (mw_all_timers[i].recipient_id < MW_MAX_WINDOW_COUNT)
					{
						/* check window is used */
						if (mw_all_windows[mw_all_timers[i].recipient_id].window_flags & MW_WINDOW_FLAG_IS_USED)
						{
							mw_post_message(MW_WINDOW_TIMER_MESSAGE,
									MW_UNUSED_MESSAGE_PARAMETER,
									mw_all_timers[i].recipient_id,
									i,
									MW_WINDOW_MESSAGE);
						}
					}
					else
					{
						/* bad recipient id */
						MW_ASSERT(false);
					}
				}
				else if (mw_all_timers[i].recipient_type == MW_CONTROL_MESSAGE)
				{
					/* check if recipient id is sensible */
					if (mw_all_timers[i].recipient_id < MW_MAX_CONTROL_COUNT)
					{
						/* check control is used */
						if (mw_all_controls[mw_all_timers[i].recipient_id].control_flags & MW_CONTROL_FLAG_IS_USED)
						{
							mw_post_message(MW_WINDOW_TIMER_MESSAGE,
									MW_UNUSED_MESSAGE_PARAMETER,
									mw_all_timers[i].recipient_id,
									i,
									MW_CONTROL_MESSAGE);
						}
					}
					else
					{
						/* bad recipient id */
						MW_ASSERT(false);
					}
				}
				else
				{
					/* bad recipient type */
					MW_ASSERT(false);
				}
			}
		}
	}

	/* handle next window message in the message queue if there is one */
	if (mw_message_queue_remove(&message))
	{
		/* sort on message recipient type */
		switch (message.message_recipient_type)
		{
		case MW_WINDOW_MESSAGE:
			/* recipient is a window */
			mw_all_windows[message.recipient_id].message_func(&message);
			break;
		
		case MW_CONTROL_MESSAGE:
			/* recipient is a control */
			mw_all_controls[message.recipient_id].message_func(&message);
			break;

		case MW_SYSTEM_MESSAGE:
			/* recipient is the system so implement message action here */
			switch (message.message_id)
			{
			/* sort on message type */
			case MW_WINDOW_PAINT_ALL_MESSAGE:
				/* paint all windows and their controls */
				do_paint_all();
				break;

			case MW_WINDOW_FRAME_PAINT_MESSAGE:
				/* paint a single window */
				do_paint_window_frame(message.recipient_id, message.message_data);
				break;

			case MW_WINDOW_CLIENT_PAINT_MESSAGE:
				/* paint a window's client and contained controls */
				do_paint_window_client(message.recipient_id);
			  	if (message.recipient_id > MW_ROOT_WINDOW_ID)
			  	{
			  		/* paint all the controls; these are always on top of the client area */
			  		paint_all_controls_in_window(message.recipient_id);
			  	}
				break;

			case MW_WINDOW_CLIENT_PAINT_RECT_MESSAGE:
				/* paint a window's client and contained controls */
				do_paint_window_client_rect(message.recipient_id, (mw_util_rect_t *)message.message_data);
			  	if (message.recipient_id > MW_ROOT_WINDOW_ID)
			  	{
			  		/* paint all the controls; these are always on top of the client area */
			  		paint_all_controls_in_window_rect(message.recipient_id, (mw_util_rect_t *)message.message_data);
			  	}
				break;

			case MW_CONTROL_PAINT_MESSAGE:
				/* paint a single control */
				do_paint_control(message.recipient_id);
				break;

			case MW_CONTROL_PAINT_RECT_MESSAGE:
				/* paint a single control's sub-region */
				do_paint_control_rect(message.recipient_id, (mw_util_rect_t *)message.message_data);
				break;

			default:
				MW_ASSERT(false);
				break;
			}
			break;

		case MW_CANCELLED_MESSAGE:
			/* do nothing */
			break;

		default:
			MW_ASSERT(false);
		}

		return true;
	}
	else
	{
		return false;
	}
}

void mw_paint_all()
{
    /* this is the public interface to getting all windows painted;
     * it does not do the painting but adds a paint request message to the message queue */
	mw_post_message(MW_WINDOW_PAINT_ALL_MESSAGE,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_UNUSED_MESSAGE_PARAMETER,
			MW_SYSTEM_MESSAGE);
}

void mw_show_busy(bool show)
{
	if (show)
	{
		/* show the busy message which is a configurable string in a red rectangle in the middle of the display on top of everything else */
		mw_gl_set_fill(MW_GL_FILL);
		mw_gl_set_solid_fill_colour(MW_HAL_LCD_RED);
		mw_gl_clear_pattern();
		mw_gl_set_border(MW_GL_BORDER_ON);
		mw_gl_set_line(MW_GL_SOLID_LINE);
		mw_gl_set_fg_colour(MW_HAL_LCD_BLACK);
		mw_gl_rectangle(&draw_info_root,
				(MW_HAL_LCD_WIDTH - (mw_gl_large_string_width(MW_BUSY_TEXT) + 30)) / 2,
				(MW_HAL_LCD_HEIGHT - 30) / 2,
				mw_gl_large_string_width(MW_BUSY_TEXT) + 30,
				30);
		mw_gl_set_bg_transparency(MW_GL_BG_TRANSPARENT);
		mw_gl_large_string(&draw_info_root,
				(MW_HAL_LCD_WIDTH - mw_gl_large_string_width(MW_BUSY_TEXT)) / 2,
				2 + (MW_HAL_LCD_HEIGHT - MW_GL_LARGE_CHARACTER_HEIGHT) / 2,
				MW_BUSY_TEXT);
	}
	else
	{
		/* don't know what was underneath the busy message so paint everything again */
		mw_paint_all();
	}
}
