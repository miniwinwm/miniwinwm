/*

MIT License

Copyright (c) John Blaiklock 20123 miniwin Embedded Window Manager

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

#ifdef _RENESAS_SYNERGY_

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>
#include "miniwin_thread.h"
#include "hal/hal_touch.h"

/****************
*** CONSTANTS ***
****************/

#define TOUCH_RECAL                      IOPORT_PORT_00_PIN_06

/************
*** TYPES ***
************/

static mw_hal_touch_state_t touch_state = MW_HAL_TOUCH_STATE_UP;
static int16_t touch_x;
static int16_t touch_y;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

void touch_panel_v2_callback(sf_touchpanel_v2_callback_args_t *p_args)
{
    sf_touch_panel_v2_payload_t const * const p_payload= &p_args->payload;

    switch (p_payload->event_type)
    {
        /* New touch event reported. */
        case SF_TOUCH_PANEL_V2_EVENT_DOWN:
            touch_state = MW_HAL_TOUCH_STATE_DOWN;
            touch_x = p_payload->x;
            touch_y = p_payload->y;
            break;

        /* Touch released. */
        case SF_TOUCH_PANEL_V2_EVENT_UP:
            touch_state = MW_HAL_TOUCH_STATE_UP;
            break;

        /* Touch has not moved since last touch event. */
        /* Touch has moved since last touch event. */
        case SF_TOUCH_PANEL_V2_EVENT_HOLD:
        case SF_TOUCH_PANEL_V2_EVENT_MOVE:
            touch_x = p_payload->x;
            touch_y = p_payload->y;
            break;

        /* No valid touch event happened. */
        /* Invalid touch data */
        case SF_TOUCH_PANEL_V2_EVENT_NONE:
        case SF_TOUCH_PANEL_V2_EVENT_INVALID:
        default:
            break;
    }
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
}

bool mw_hal_touch_is_recalibration_required(void)
{
    ioport_level_t pin_level;
    (void)g_ioport.p_api->pinRead(TOUCH_RECAL, &pin_level);

    if (pin_level == IOPORT_LEVEL_HIGH)
    {
        return false;
    }

    return true;
}

mw_hal_touch_state_t mw_hal_touch_get_state()
{
	return touch_state;
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
    *x = (uint16_t)touch_x;
    *y = (uint16_t)touch_y;

    return touch_state == MW_HAL_TOUCH_STATE_DOWN;
}

#endif
