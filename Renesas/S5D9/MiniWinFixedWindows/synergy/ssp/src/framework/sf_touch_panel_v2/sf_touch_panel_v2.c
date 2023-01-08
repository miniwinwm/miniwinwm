/***********************************************************************************************************************
 * Copyright [2018-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : sf_touch_panel_v2.c
 * Description  : Touch Panel Framework V2 (SF_TOUCH_PANEL_V2) Module for touch chip driver.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "sf_touch_panel_v2.h"
#include "sf_touch_panel_v2_private_api.h"

/*******************************************************************************************************************//**
 * @addtogroup SF_TOUCH_PANEL_V2
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/** Macro for error logger. */
#ifndef SF_TOUCH_PANEL_V2_ERROR_RETURN
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define SF_TOUCH_PANEL_V2_ERROR_RETURN(a, err) SSP_ERROR_RETURN((a), (err), &g_module_name[0], &g_version)
#endif

#ifndef SF_TOUCH_PANEL_V2_ERROR_LOG
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define SF_TOUCH_PANEL_V2_ERROR_LOG(err) SSP_ERROR_LOG((err), g_module_name, &g_version)
#endif

#define SF_TOUCH_PANEL_V2_PRV_RTOS_TICKS_SEC (TX_TIMER_TICKS_PER_SECOND)

/** "TPNL" in ASCII, used to identify touch panel handle */
#define SF_TOUCH_PANEL_V2_OPEN (0x54504e4cU)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_sf_touch_panel_v2_private_flags
{
    SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_STOP  = 1,
    SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_START = 2
} sf_touch_panel_v2_private_flags_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (1 == SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE)
static ssp_err_t sf_touch_panel_v2_open_param_check (sf_touch_panel_v2_instance_ctrl_t * const p_ctrl,
                                                     sf_touch_panel_v2_cfg_t const * const p_cfg);
#endif

#if (1 == SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE)
static ssp_err_t sf_touch_panel_v2_calibrate_param_check (sf_touch_panel_v2_ctrl_t             * const p_api_ctrl,
                                                          sf_touch_panel_v2_calibrate_t const  * const p_display,
                                                          sf_touch_panel_v2_calibrate_t const  * const p_touchscreen);
#endif
static void sf_touch_panel_v2_thread (ULONG thread_input);

static bool sf_touch_panel_v2_check_event_to_be_sent (sf_touch_panel_v2_instance_ctrl_t * p_ctrl,
                                                      sf_touch_panel_v2_event_t event, ULONG last_updated_time);

static void sf_touch_panel_v2_touch_event_post (sf_touch_panel_v2_instance_ctrl_t * p_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "sf_touch_panel_v2";
#endif

#if defined(__GNUC__)
/* This structure is affected by warnings from the GCC compiler bug gcc.gnu.org/bugzilla/show_bug.cgi?id=60784
 * This pragma suppresses the warnings in this structure only, and will be removed when the SSP compiler is updated to
 * v5.3.*/
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
/** Version data structure used by error logger macro. */
static const ssp_version_t g_version =
{
    .api_version_minor  = SF_TOUCH_PANEL_V2_API_VERSION_MINOR,
    .api_version_major  = SF_TOUCH_PANEL_V2_API_VERSION_MAJOR,
    .code_version_major = SF_TOUCH_PANEL_V2_CODE_VERSION_MAJOR,
    .code_version_minor = SF_TOUCH_PANEL_V2_CODE_VERSION_MINOR
};
#if defined(__GNUC__)
/* Restore warning settings for 'missing-field-initializers' to as specified on command line. */
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic pop
#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const sf_touch_panel_v2_api_t g_sf_touch_panel_v2_on_sf_touch_panel_v2 =
{
    .open         = SF_TOUCH_PANEL_V2_Open,
    .calibrate    = SF_TOUCH_PANEL_V2_Calibrate,
    .start        = SF_TOUCH_PANEL_V2_Start,
    .stop         = SF_TOUCH_PANEL_V2_Stop,
    .touchDataGet = SF_TOUCH_PANEL_V2_TouchDataGet,
    .reset        = SF_TOUCH_PANEL_V2_Reset,
    .close        = SF_TOUCH_PANEL_V2_Close,
    .versionGet   = SF_TOUCH_PANEL_V2_VersionGet,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/


/*******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::open.
 *
 * @retval SSP_SUCCESS           Touch panel thread created and lower level drivers opened successfully.
 * @retval SSP_ERR_ASSERTION     A pointer parameter was NULL, or a lower level driver reported this error.
 * @retval SSP_ERR_INTERNAL      The touch panel thread or event flags could not be created, or a lower level driver
 *                               reported this error.
 * @retval SSP_ERR_ALREADY_OPEN  Touch panel framework is already configured.
 * @return                       See @ref Common_Error_Codes or lower level drivers for other possible return codes.
 *                               This function calls:
 *                                 * sf_touch_panel_chip_api_t::open
 *                                 * sf_touch_panel_chip_api_t::reset
 * @note This function is reentrant for any panel.
 **********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_Open (sf_touch_panel_v2_ctrl_t      * const p_api_ctrl,
                                  sf_touch_panel_v2_cfg_t const * const p_cfg)
{
    ssp_err_t err = SSP_SUCCESS;
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl = (sf_touch_panel_v2_instance_ctrl_t *) p_api_ctrl;

#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    err = sf_touch_panel_v2_open_param_check(p_api_ctrl, p_cfg);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif /* if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE */

    SF_TOUCH_PANEL_V2_ERROR_RETURN(SF_TOUCH_PANEL_V2_OPEN != p_ctrl->open, SSP_ERR_ALREADY_OPEN);

    sf_touch_panel_v2_extend_cfg_t const * const p_cfg_extend = p_cfg->p_extend;
    p_ctrl->p_chip = p_cfg_extend->p_chip;
    sf_touch_panel_chip_ctrl_t * const      p_chip_ctrl = p_ctrl->p_chip->p_ctrl;
    sf_touch_panel_chip_cfg_t const * const p_chip_cfg  = p_ctrl->p_chip->p_cfg;

    /** Store user configurations in control block. */
    p_ctrl->p_callback     = p_cfg->p_callback;
    p_ctrl->hsize_pixels   = p_cfg->hsize_pixels;
    p_ctrl->vsize_pixels   = p_cfg->vsize_pixels;
    p_ctrl->update_hz      = p_cfg->update_hz;
    p_ctrl->rotation_angle = p_cfg->rotation_angle;
    p_ctrl->p_context      = p_cfg->p_context;
    p_ctrl->calibrate      = 0U;
    UINT tx_err = TX_SUCCESS;

    /** Create a mutex to protect access to the control structure and the lower level hardware. */
    tx_err = tx_mutex_create(&p_ctrl->mutex, NULL, TX_INHERIT);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(TX_SUCCESS == tx_err, SSP_ERR_INTERNAL);

    /** Open the lower level driver. */
    err = p_ctrl->p_chip->p_api->open(p_chip_ctrl, p_chip_cfg);
    if (SSP_SUCCESS != err)
    {
        /** Delete RTOS services used and log the error */
        /* The return codes are not checked here because delete calls cannot fail when called with
         * created RTOS objects. These objects were successfully created in this function. */
        tx_mutex_delete(&p_ctrl->mutex);
        SF_TOUCH_PANEL_V2_ERROR_LOG(err);
        return err;
    }

    /** Reset the touch chip. */
    err = p_ctrl->p_chip->p_api->reset(p_chip_ctrl);
    if (SSP_SUCCESS != err)
    {
        /* The return codes are not checked because valid parameters are passed here and the Close API does not
         * return an error except for parameter checking */
        p_ctrl->p_chip->p_api->close(p_chip_ctrl);

        /** Delete RTOS services used and log the error */
        /* The return codes are not checked here because delete calls cannot fail when called with
         * created RTOS objects. These objects were successfully created in this function. */
        tx_mutex_delete(&p_ctrl->mutex);
        SF_TOUCH_PANEL_V2_ERROR_LOG(err);
        return err;
    }

    /** Create event flags for internal communication. */
    tx_err = tx_event_flags_create(&p_ctrl->flags, NULL);

    /** Create semaphore for use with touchDataGet function*/
    tx_err |= tx_semaphore_create(&p_ctrl->semaphore, NULL, 0);

    if (TX_SUCCESS != tx_err)
    {
        p_ctrl->p_chip->p_api->close(p_chip_ctrl);
        /** Delete RTOS services used */
        /* The return codes are not checked here because delete calls cannot fail when called with
         * created RTOS objects. These objects were successfully created in this function. */
        tx_event_flags_delete(&p_ctrl->flags);
        tx_mutex_delete(&p_ctrl->mutex);
        tx_semaphore_delete(&p_ctrl->semaphore);
        SF_TOUCH_PANEL_V2_ERROR_LOG(SSP_ERR_INTERNAL);
        return SSP_ERR_INTERNAL;
    }

    /** Create main touch panel thread. */
    tx_err = tx_thread_create(&p_ctrl->thread,
                              (CHAR *) "Touch Panel Thread",
                              sf_touch_panel_v2_thread,
                              (ULONG) p_ctrl,
                              &p_ctrl->stack,
                              SF_TOUCH_PANEL_V2_STACK_SIZE,
                              p_cfg->priority,
                              p_cfg->priority,
                              TX_NO_TIME_SLICE,
                              TX_AUTO_START);

    if (TX_SUCCESS != tx_err)
    {
        p_ctrl->p_chip->p_api->close(p_chip_ctrl);
        /** Delete RTOS services used */
        /* The return codes are not checked here because delete calls cannot fail when called with
         * created RTOS objects. These objects were successfully created in this function. */
        tx_event_flags_delete(&p_ctrl->flags);
        tx_mutex_delete(&p_ctrl->mutex);
        tx_semaphore_delete(&p_ctrl->semaphore);
        SF_TOUCH_PANEL_V2_ERROR_LOG(SSP_ERR_INTERNAL);
        return SSP_ERR_INTERNAL;
    }

    /** Mark control block open so other tasks know it is valid */
    p_ctrl->open = SF_TOUCH_PANEL_V2_OPEN;

    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::calibrate.
 *
 * @retval SSP_SUCCESS               Touch panel calibrated successfully.
 * @retval SSP_ERR_ASSERTION         A pointer parameter was NULL.
 * @retval SSP_ERR_CALIBRATE_FAILED  Failed to calibrate
 * @retval SSP_ERR_NOT_OPEN          Touch panel is not configured. Call SF_TOUCH_PANEL_V2_Open.
 * @retval SSP_ERR_INVALID_ARGUMENT  Set of display or touch screen coordinates passed are invalid.
 * @return See @ref Common_Error_Codes or lower level drivers for other possible return codes.
 * @note This function is reentrant for any panel.
 **********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_Calibrate (sf_touch_panel_v2_ctrl_t             * const p_api_ctrl,
                                       sf_touch_panel_v2_calibrate_t const  * const p_display,
                                       sf_touch_panel_v2_calibrate_t const  * const p_touchscreen,
                                       ULONG const  timeout)
{
    ssp_err_t err = SSP_SUCCESS;
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl = (sf_touch_panel_v2_instance_ctrl_t *) p_api_ctrl;

#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    err = sf_touch_panel_v2_calibrate_param_check(p_api_ctrl, p_display, p_touchscreen);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SSP_SUCCESS == err, err);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SF_TOUCH_PANEL_V2_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif /* if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE */

    for (uint8_t i = 0U; i < 3U; i++)
    {
        SF_TOUCH_PANEL_V2_ERROR_RETURN(p_display[i].x <= (int32_t)p_ctrl->hsize_pixels, SSP_ERR_INVALID_ARGUMENT);
        SF_TOUCH_PANEL_V2_ERROR_RETURN(p_display[i].y <= (int32_t)p_ctrl->vsize_pixels, SSP_ERR_INVALID_ARGUMENT);
        SF_TOUCH_PANEL_V2_ERROR_RETURN(p_touchscreen[i].x <= (int32_t)p_ctrl->hsize_pixels, SSP_ERR_INVALID_ARGUMENT);
        SF_TOUCH_PANEL_V2_ERROR_RETURN(p_touchscreen[i].y <= (int32_t)p_ctrl->vsize_pixels, SSP_ERR_INVALID_ARGUMENT);
    }

/* Calibration function overcomes the problems in the touch panel like: Scalar, rotation and Mechanical shifts.
* The required coefficients are calculated using 3 sets of expected display coordinates and the obtained touch
* screen coordinates passed to the function.
* These coefficients are used to calculate the calibrated coordinates, every time a new touch event is generated.
* The following equation is used to obtain the calibrated coordinates:
*
*                                                   /-                -\
*              /-         -\     /-            -\   |                  |         __          __
*              |           |     |              |   |   Xtouch_screen  |        |              |
*              |  Xdisplay |     | A    B    C  |   |                  |        |      1       |
*              |           |  =  |              | * |   Ytouch_screen  |  *     | ____________ |
*              |  Ydisplay |     | D    E    F  |   |                  |        |              |
*              |           |     |              |   |        1         |        |  Determinant |
*              \-         -/     \-            -/   |                  |        |__          __|
*                                                   \-                -/
*
*   where,
*
*        [ Xtouch_screen , Ytouch_screen ]   represents the obtained coordinates from the touch screen.
*
*        [Xdisplay , Ydisplay]               represents the expected coordinates of the display.
*
*        /-   -\
*        |A,B,C|                             represents the coefficients used to translate the actual touch screen
*        |D,E,F|                             coordinates into the corresponding expected display coordinates.
*        \-   -/
*
*        Determinant                         Determinant of the matrix.
*/

    /** Timeout not used in this implementation. */
    SSP_PARAMETER_NOT_USED (timeout);

    /*
    *        Determinant = ((Xtouch_screen1 - Xtouch_screen3) * (Ytouch_screen2 - Ytouch_screen3)) -
    *                      ((Xtouch_screen2 - Xtouch_screen3) * (Ytouch_screen1 - Ytouch_screen3))
    *
    *        where,
    *
    *        [Xdisplay1 , Ydisplay1],
    *        [Xdisplay2 , Ydisplay2],
    *        [Xdisplay3 , Ydisplay3]                 Represents the 3 set of expected coordinates of the display.
    *
    *        [Xtouch_screen1 , Ytouch_screen1],
    *        [Xtouch_screen2 , Ytouch_screen2],
    *        [Xtouch_screen3 , Ytouch_screen3]       Represents the 3 set of obtained coordinates from the touch screen.
    *
    */
    p_ctrl->calibration_factor.determinant =
                         ((p_touchscreen[0].x - p_touchscreen[2].x) * (p_touchscreen[1].y - p_touchscreen[2].y)) -
                         ((p_touchscreen[1].x - p_touchscreen[2].x) * (p_touchscreen[0].y - p_touchscreen[2].y));

    if( p_ctrl->calibration_factor.determinant == 0 )
    {
        err = SSP_ERR_CALIBRATE_FAILED;
    }
    else
    {
        /*
        *        A coefficient = ((Xdisplay1 - Xdisplay3) * (Ytouch_screen2 - Ytouch_screen3)) -
        *                        ((Xdisplay2 - Xdisplay3) * (Ytouch_screen1 - Ytouch_screen3))
        */
        p_ctrl->calibration_factor.a_coefficient =
            ((p_display[0].x - p_display[2].x) * (p_touchscreen[1].y - p_touchscreen[2].y)) -
            ((p_display[1].x - p_display[2].x) * (p_touchscreen[0].y - p_touchscreen[2].y));

        /*
        *        B coefficient = ((Ytouch_screen1 - Ytouch_screen3) * (Xdisplay2 - Xdisplay3)) -
        *                        ((Xdisplay1 - Xdisplay3) * (Ytouch_screen2 - Ytouch_screen3))
        */
        p_ctrl->calibration_factor.b_coefficient =
            ((p_touchscreen[0].x - p_touchscreen[2].x) * (p_display[1].x - p_display[2].x)) -
            ((p_display[0].x - p_display[2].x) * (p_touchscreen[1].x - p_touchscreen[2].x));

        /*
        *        C coefficient = (((Ytouch_screen3 * Xdisplay2) - (Ytouch_screen2 * Xdisplay3)) * Ytouch_screen1) +
        *                        (((Ytouch_screen1 * Xdisplay3) - (Ytouch_screen3 * Xdisplay1)) * Ytouch_screen2) +
        *                        (((Ytouch_screen2 * Xdisplay1) - (Ytouch_screen1 * Xdisplay2)) * Ytouch_screen3)
        */
        p_ctrl->calibration_factor.c_coefficient =
            (((p_touchscreen[2].x * p_display[1].x) - (p_touchscreen[1].x * p_display[2].x)) * p_touchscreen[0].y) +
            (((p_touchscreen[0].x * p_display[2].x) - (p_touchscreen[2].x * p_display[0].x)) * p_touchscreen[1].y) +
            (((p_touchscreen[1].x * p_display[0].x) - (p_touchscreen[0].x * p_display[1].x)) * p_touchscreen[2].y);

        /*
        *        D coefficient = ((Ydisplay1 - Ydisplay3) * (Ytouch_screen2 - Ytouch_screen3)) -
        *                        ((Ydisplay2 - Ydisplay3) * (Ytouch_screen1 - Ytouch_screen3))
        */
        p_ctrl->calibration_factor.d_coefficient =
            ((p_display[0].y - p_display[2].y) * (p_touchscreen[1].y - p_touchscreen[2].y)) -
            ((p_display[1].y - p_display[2].y) * (p_touchscreen[0].y - p_touchscreen[2].y));

        /*
        *
        *        E coefficient = ((Ytouch_screen1 - Ytouch_screen3) * (Ydisplay2 - Ydisplay3)) -
        *                        ((Ydisplay1 - Ydisplay3) * (Ytouch_screen2 - Ytouch_screen3))
        */
        p_ctrl->calibration_factor.e_coefficient =
            ((p_touchscreen[0].x - p_touchscreen[2].x) * (p_display[1].y - p_display[2].y)) -
            ((p_display[0].y - p_display[2].y) * (p_touchscreen[1].x - p_touchscreen[2].x));

        /*
        *        F coefficient = (((Ytouch_screen3 * Ydisplay2) - (Ytouch_screen2 * Ydisplay3)) * Ytouch_screen1) +
        *                        (((Ytouch_screen1 * Ydisplay3) - (Ytouch_screen3 * Ydisplay1)) * Ytouch_screen2) +
        *                        (((Ytouch_screen2 * Ydisplay1) - (Ytouch_screen1 * Ydisplay2)) * Ytouch_screen3)
        */
        p_ctrl->calibration_factor.f_coefficient =
            (((p_touchscreen[2].x * p_display[1].y) - (p_touchscreen[1].x * p_display[2].y)) * p_touchscreen[0].y) +
            (((p_touchscreen[0].x * p_display[2].y) - (p_touchscreen[2].x * p_display[0].y)) * p_touchscreen[1].y) +
            (((p_touchscreen[1].x * p_display[0].y) - (p_touchscreen[0].x * p_display[1].y)) * p_touchscreen[2].y);
    }
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SSP_SUCCESS == err, err);
    p_ctrl->calibrate = 1U;
    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::start.
 *
 * @retval SSP_SUCCESS           Enabled touch panel thread to scan for new touch events.
 * @retval SSP_ERR_ASSERTION     A pointer parameter was NULL.
 * @retval SSP_ERR_NOT_OPEN      Touch panel is not configured. Call SF_TOUCH_PANEL_V2_Open.
 * @note This function is reentrant for any panel.
 **********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_Start (sf_touch_panel_v2_ctrl_t * const p_api_ctrl)
{
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl = (sf_touch_panel_v2_instance_ctrl_t *) p_api_ctrl;

#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_api_ctrl);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SF_TOUCH_PANEL_V2_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    /** Set start flag. */
    /* The return code is not checked here because event flag set is called with valid input arguments */
    tx_event_flags_set(&p_ctrl->flags, SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_START, TX_OR);

    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::touchDataGet.
 *
 * @retval SSP_SUCCESS           Touch panel data read successfully.
 * @retval SSP_ERR_ASSERTION     A pointer parameter was NULL.
 * @retval SSP_ERR_NOT_OPEN      Touch panel is not configured. Call SF_TOUCH_PANEL_V2_Open.
 * @retval SSP_ERR_TIMEOUT       Time out occurs while waiting for semaphore.
 * @retval SSP_ERR_WAIT_ABORTED  Suspension was aborted by another thread.
 * @note This function is reentrant for any panel.
 * @note The function will pend until new touch event data is available or it will timeout.
 **********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_TouchDataGet (sf_touch_panel_v2_ctrl_t * const p_api_ctrl,
                                          sf_touch_panel_v2_payload_t * p_payload, ULONG const timeout)
{
    UINT tx_err = TX_SUCCESS;
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl = (sf_touch_panel_v2_instance_ctrl_t *) p_api_ctrl;

#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_api_ctrl);
    SSP_ASSERT(NULL != p_payload);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SF_TOUCH_PANEL_V2_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    tx_err = tx_semaphore_get(&p_ctrl->semaphore, timeout);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(TX_NO_INSTANCE != tx_err, SSP_ERR_TIMEOUT);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(TX_SUCCESS == tx_err, SSP_ERR_WAIT_ABORTED);

    p_payload->x          = p_ctrl->payload.x;
    p_payload->y          = p_ctrl->payload.y;
    p_payload->event_type = p_ctrl->payload.event_type;

    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::stop.
 *
 * @retval SSP_SUCCESS           Disabled touch panel thread from scanning the touch events.
 * @retval SSP_ERR_ASSERTION     A pointer parameter was NULL.
 * @retval SSP_ERR_NOT_OPEN      Touch panel is not configured. Call SF_TOUCH_PANEL_V2_Open.
 * @note This function is reentrant for any panel.
 **********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_Stop (sf_touch_panel_v2_ctrl_t * const p_api_ctrl)
{
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl = (sf_touch_panel_v2_instance_ctrl_t *) p_api_ctrl;

#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_api_ctrl);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SF_TOUCH_PANEL_V2_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    /** Set stop flag. */
    /* The return code is not checked here because event flag set is called with valid input arguments */
    tx_event_flags_set(&p_ctrl->flags, SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_STOP, TX_OR);

    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::reset.
 *
 * @retval SSP_SUCCESS           Touch chip reset successful.
 * @retval SSP_ERR_ASSERTION     Parameter p_api_ctrl was NULL, or a lower level driver reported this error.
 * @retval SSP_ERR_IN_USE        Mutex was not available, or a lower level driver reported this error.
 * @retval SSP_ERR_NOT_OPEN      Touch panel is not configured. Use Open API to configure.
 * @return See @ref Common_Error_Codes or lower level drivers for other possible return codes.
 *                               This function calls:
 *                               * sf_touch_panel_chip_api_t::reset
 * @note This function is reentrant for any panel.
 **********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_Reset (sf_touch_panel_v2_ctrl_t * const p_api_ctrl)
{
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl = (sf_touch_panel_v2_instance_ctrl_t *) p_api_ctrl;

#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_api_ctrl);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SF_TOUCH_PANEL_V2_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    sf_touch_panel_chip_ctrl_t * const p_chip_ctrl = p_ctrl->p_chip->p_ctrl;
    /** Obtain mutex since this accesses shared resources. */
    ULONG wait_option = TX_NO_WAIT;
    ssp_err_t err     = SSP_SUCCESS;
    UINT tx_err       = TX_SUCCESS;

    tx_err = tx_mutex_get(&p_ctrl->mutex, wait_option);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(TX_SUCCESS == tx_err, SSP_ERR_IN_USE);

    /** Call hardware specific reset function. */
    err = p_ctrl->p_chip->p_api->reset(p_chip_ctrl);

    /** Release mutex. */
    /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
     * current thread. The mutex is owned by the current thread because this call follows a successful call to
     * mutex get */
    tx_mutex_put(&p_ctrl->mutex);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SSP_SUCCESS == err, err);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::close.
 *
 * @retval SSP_SUCCESS           Touch panel instance successfully closed.
 * @retval SSP_ERR_ASSERTION     Parameter p_api_ctrl was NULL, or a lower level driver reported this error.
 * @retval SSP_ERR_NOT_OPEN      Touch panel is not configured. Call SF_TOUCH_PANEL_V2_Open.
 * @note This function is reentrant.
 **********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_Close (sf_touch_panel_v2_ctrl_t * const p_api_ctrl)
{
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl = (sf_touch_panel_v2_instance_ctrl_t *) p_api_ctrl;

#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_api_ctrl);
    SF_TOUCH_PANEL_V2_ERROR_RETURN(SF_TOUCH_PANEL_V2_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    sf_touch_panel_chip_ctrl_t * const p_chip_ctrl = p_ctrl->p_chip->p_ctrl;

    /* The return codes are not checked here because Close API should not return an error except for
     * parameter checking */

    /** Close the lower level driver. */
    p_ctrl->p_chip->p_api->close(p_chip_ctrl);

    /** Suspend internal thread. */
    tx_thread_suspend(&p_ctrl->thread);
    /** Delete RTOS services used */
    tx_event_flags_delete(&p_ctrl->flags);
    tx_mutex_delete(&p_ctrl->mutex);
    tx_thread_terminate(&p_ctrl->thread);
    tx_thread_delete(&p_ctrl->thread);
    tx_semaphore_delete(&p_ctrl->semaphore);

    /** Mark control block close */
    p_ctrl->open = 0U;

    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_v2_api_t::versionGet.
 *
 * @retval SSP_SUCCESS           Version returned successfully.
 * @retval SSP_ERR_ASSERTION     Parameter p_version was null.
 *********************************************************************************************************************/
ssp_err_t SF_TOUCH_PANEL_V2_VersionGet (ssp_version_t * const p_version)
{
#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_version);
#endif

    *p_version = g_version;

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end defgroup SF_TOUCH_PANEL_V2)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Publishes touch data to the user callback.
 *
 * @param[in] thread_input  Pointer to touch panel control structure (sf_touch_panel_v2_instance_ctrl_t).
 **********************************************************************************************************************/
static void sf_touch_panel_v2_thread (ULONG thread_input)
{
    sf_touch_panel_v2_instance_ctrl_t * p_ctrl    = (sf_touch_panel_v2_instance_ctrl_t *) thread_input;
    ULONG last_updated_time                       = tx_time_get();
    ssp_err_t err                                 = SSP_SUCCESS;

    ULONG actual_flags = 0U;

    /* Wait for start flag. The return code is not checked here because event flag get is called
     * with valid input arguments */
    tx_event_flags_get(&p_ctrl->flags, SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_START,
                       TX_OR_CLEAR, &actual_flags, TX_WAIT_FOREVER);

    while (1)
    {
        actual_flags = 0U;

        /** Get the touch event data from the touch driver */
        err = p_ctrl->p_chip->p_api->payloadGet(p_ctrl->p_chip->p_ctrl, &(p_ctrl->payload));
        if (SSP_SUCCESS == err)
        {
            /** Check the touch coordinate got from the touch driver */
            if (((int16_t)(p_ctrl->hsize_pixels) < p_ctrl->payload.x) || ((int16_t)p_ctrl->vsize_pixels < p_ctrl->payload.y))
            {
                /* Notify users if the touch panel returns the coordinate beyond the touch panel screen size */
                p_ctrl->payload.event_type = SF_TOUCH_PANEL_V2_EVENT_INVALID;
            }
        }
        else if (SSP_ERR_WAIT_ABORTED == err)
        {
            /* Suspension was aborted by another thread */
            tx_thread_suspend(&p_ctrl->thread);
        }
        else
        {
            /* Error in touch chip. Error handling should happen at the lower layer, so this is just a notification. */
            p_ctrl->payload.event_type = SF_TOUCH_PANEL_V2_EVENT_INVALID;
            SF_TOUCH_PANEL_V2_ERROR_LOG(err);
        }
        /** Check for touch control stop flag. If it is received, wait for touch control start flag. */
        /* The return code check is not required because actual flag will not be set to
         * SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_STOP in error condition and the actual flag
         * status is checked in next statement */
        tx_event_flags_get(&p_ctrl->flags, (ULONG)SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_STOP,
                           TX_OR_CLEAR, &actual_flags, TX_NO_WAIT);
        if (actual_flags & (ULONG)SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_STOP)
        {
            /* Wait for start flag. The return code is not checked here because event flag get is called
             * with valid input arguments */
            tx_event_flags_get(&p_ctrl->flags, SF_TOUCH_PANEL_V2_PRIVATE_FLAGS_START,
                               TX_OR_CLEAR, &actual_flags, TX_WAIT_FOREVER);
        }
        else
        {
            /** Check if new touch event is to be sent. */
            if (true == sf_touch_panel_v2_check_event_to_be_sent(p_ctrl, p_ctrl->payload.event_type, last_updated_time))
            {
                /** Store time, used to prevent too many events from being generated */
                last_updated_time = tx_time_get();

                /** Post a touch data to the user callback */
                sf_touch_panel_v2_touch_event_post(p_ctrl);
            }
            /* The return code is not checked here because semaphore ceiling put is called with
             * valid input arguments */
            tx_semaphore_ceiling_put(&p_ctrl->semaphore, (ULONG)1);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief   sf_touch_panel_v2_check_event_to_be_sent : Check a touch event to be sent or not.
 *
 * This function checks if new touch event is to be sent or not. DOWN and UP will always be sent. HOLD, MOVE and
 * INVALID will be sent if user specified dormant time elapsed after previous event was sent.
 *
 * @param[in]  p_ctrl       : Pointer to SF_TOUCH_PANEL_V2 instance structure
 * @param[in]  event        : Touch event
 * @param[in]  last_updated_time : Last time when touch event was updated.
 *
 * @retval  true    - Send the event.
 * @retval  false   - Do not send the event.
***********************************************************************************************************************/
static bool sf_touch_panel_v2_check_event_to_be_sent (sf_touch_panel_v2_instance_ctrl_t * p_ctrl,
                                                      sf_touch_panel_v2_event_t event, ULONG last_updated_time)
{
    bool  send_event = true;
    ULONG current_time;

    if (((SF_TOUCH_PANEL_V2_EVENT_HOLD    == event)  ||
         (SF_TOUCH_PANEL_V2_EVENT_MOVE    == event)) ||
         (SF_TOUCH_PANEL_V2_EVENT_INVALID == event))
    {
        /** Only send repeat events as requested by user. */
        current_time = tx_time_get();
        if (current_time <= (last_updated_time + (SF_TOUCH_PANEL_V2_PRV_RTOS_TICKS_SEC / (p_ctrl->update_hz))))
        {
            send_event = false;
        }
    }
    return send_event;
}

/*******************************************************************************************************************//**
 * @brief   sf_touch_panel_v2_touch_event_post : Post new touch data.
 *
 * This function posts a touch data to the user callback.
 *
 * @param[in]  p_ctrl : Pointer to SF_TOUCH_PANEL_V2 instance structure
***********************************************************************************************************************/
static void sf_touch_panel_v2_touch_event_post (sf_touch_panel_v2_instance_ctrl_t * p_ctrl)
{
    int16_t                 temp_value = 0;
    int16_t                 x_value = 0;
    int16_t                 y_value = 0;

    if (p_ctrl->calibrate == 1)
    {
        /* Using the coefficients calculated in the calibration function, the calibrated coordinates are obtained
         * by the below equation:
         *
         *      Xdisplay = ((A * Xtouch_screen) + (B * Ytouch_screen) + C) / Determinant
         *
         *      Ydisplay = ((D * Xtouch_screen) +(E * Ytouch_screen) + F) / Determinant
         */

        x_value = p_ctrl->payload.x;
        y_value = p_ctrl->payload.y;

        p_ctrl->payload.x = (int16_t)(( (p_ctrl->calibration_factor.a_coefficient * (int32_t)x_value) +
                (p_ctrl->calibration_factor.b_coefficient * (int32_t)y_value) +
                 p_ctrl->calibration_factor.c_coefficient) / p_ctrl->calibration_factor.determinant);

        p_ctrl->payload.y = (int16_t)(((p_ctrl->calibration_factor.d_coefficient * (int32_t)x_value) +
                (p_ctrl->calibration_factor.e_coefficient * (int32_t)y_value) +
                 p_ctrl->calibration_factor.f_coefficient) / p_ctrl->calibration_factor.determinant);

        if(p_ctrl->payload.x < 0)
        {
            p_ctrl->payload.x = 0;
        }
        if(p_ctrl->payload.y < 0)
        {
            p_ctrl->payload.y = 0;
        }
        if((p_ctrl->payload.x) > ((int16_t)(p_ctrl->hsize_pixels)))
        {
            p_ctrl->payload.x = (int16_t)p_ctrl->hsize_pixels;
        }
        if((p_ctrl->payload.y) > ((int16_t)(p_ctrl->vsize_pixels)))
        {
            p_ctrl->payload.y = (int16_t)p_ctrl->vsize_pixels;
        }
    }

    /** Rotate touch coordinate clockwise. */
    switch (p_ctrl->rotation_angle)
    {
        case 90U:
            temp_value = p_ctrl->payload.y;
            p_ctrl->payload.y = p_ctrl->payload.x;
            p_ctrl->payload.x = (int16_t)(p_ctrl->vsize_pixels - temp_value);
            break;

        case 180U:
            p_ctrl->payload.x = (int16_t)(p_ctrl->hsize_pixels - p_ctrl->payload.x);
            p_ctrl->payload.y = (int16_t)(p_ctrl->vsize_pixels - p_ctrl->payload.y);
            break;

        case 270U:
            temp_value = p_ctrl->payload.x;
            p_ctrl->payload.x = p_ctrl->payload.y;
            p_ctrl->payload.y = (int16_t)(p_ctrl->hsize_pixels - temp_value);
            break;

        default:
            /* Do nothing */
            break;
    }

    if (NULL != p_ctrl->p_callback)
    {
        sf_touchpanel_v2_callback_args_t args;
        args.payload = p_ctrl->payload;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args); /* Invoke callback */
    }
}

#if (1 == SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE)
/*******************************************************************************************************************//**
 * @brief   sf_touch_panel_v2_open_param_check : SF_TOUCH_PANEL_V2 open parameter check
 *
 * This function validates the parameters given to open function.
 *
 * @param[in]  p_ctrl : Pointer to SF_TOUCH_PANEL_V2 instance structure
 * @param[in]  p_cfg  : Pointer to SF_TOUCH_PANEL_V2 configuration structure
 *
 * @retval  SSP_SUCCESS       - Successful
 * @retval  SSP_ERR_ASSERTION - NULL pointer error
***********************************************************************************************************************/
static ssp_err_t sf_touch_panel_v2_open_param_check (sf_touch_panel_v2_instance_ctrl_t * const p_ctrl,
                                                     sf_touch_panel_v2_cfg_t const * const p_cfg)
{
    SSP_ASSERT(NULL != p_ctrl);
    SSP_ASSERT(NULL != p_cfg);
    SSP_ASSERT(NULL != p_cfg->p_extend);

    sf_touch_panel_v2_extend_cfg_t const * const p_cfg_extend = p_cfg->p_extend;

    SSP_ASSERT(NULL != p_cfg_extend->p_chip);

    return SSP_SUCCESS;
}
#endif

#if (1 == SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE)
/*******************************************************************************************************************//**
 * @brief   sf_touch_panel_v2_calibrate_param_check : SF_TOUCH_PANEL_V2 calibrate parameter check
 *
 * This function validates the parameters given to calibrate function.
 *
 * @param[in]  p_api_ctrl    : Pointer to SF_TOUCH_PANEL_V2 instance structure
 * @param[in]  p_display     : Expected coordinates of the display.
 * @param[in]  p_touchscreen : Actual coordinates obtained from the touch driver.
 *
 * @retval  SSP_SUCCESS       - Successful
 * @retval  SSP_ERR_ASSERTION - NULL pointer error
***********************************************************************************************************************/
static ssp_err_t sf_touch_panel_v2_calibrate_param_check (sf_touch_panel_v2_ctrl_t             * const p_api_ctrl,
                                                          sf_touch_panel_v2_calibrate_t const  * const p_display,
                                                          sf_touch_panel_v2_calibrate_t const  * const p_touchscreen)
{
    SSP_ASSERT(NULL != p_api_ctrl);
    SSP_ASSERT(NULL != p_display);
    SSP_ASSERT(NULL != p_touchscreen);

    return SSP_SUCCESS;
}
#endif
