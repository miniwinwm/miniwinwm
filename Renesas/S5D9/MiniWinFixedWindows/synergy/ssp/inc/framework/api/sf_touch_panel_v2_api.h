/***********************************************************************************************************************
 * Copyright [2015-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
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
 * File Name    : sf_touch_panel_v2_api.h
 * Description  : RTOS integrated touch panel framework API.
 **********************************************************************************************************************/

#ifndef SF_TOUCH_PANEL_V2_API_H
#define SF_TOUCH_PANEL_V2_API_H

/*******************************************************************************************************************//**
 * @ingroup SF_Interface_Library
 * @defgroup SF_TOUCH_PANEL_V2_API Touch Panel Framework Interface
 * @brief RTOS-integrated Touch Panel Framework Interface.
 *
 * @section SF_TOUCH_PANEL_V2_API_SUMMARY Summary
 * This module is a ThreadX-aware Touch Panel V2 Framework which scans for touch events and posts them to the user
 * callback.
 * This Interface is implemented by @ref SF_TOUCH_PANEL_V2.
 *
 * Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * Touch Panel V2 Framework Interface description: @ref FrameworkTouchPanelV2Interface
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "tx_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SF_TOUCH_PANEL_V2_API_VERSION_MAJOR (2U)
#define SF_TOUCH_PANEL_V2_API_VERSION_MINOR (0U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Touch panel framework control block. Allocate an instance specific control block to pass into the
 * touch panel framework API calls.
 * @par Implemented as
 * - sf_touch_panel_v2_instance_ctrl_t
 */
typedef void sf_touch_panel_v2_ctrl_t;

/** Touch event list. */
typedef enum st_sf_touch_panel_v2_event
{
    SF_TOUCH_PANEL_V2_EVENT_INVALID,         ///< Invalid touch data
    SF_TOUCH_PANEL_V2_EVENT_HOLD,            ///< Touch has not moved since last touch event.
    SF_TOUCH_PANEL_V2_EVENT_MOVE,            ///< Touch has moved since last touch event.
    SF_TOUCH_PANEL_V2_EVENT_DOWN,            ///< New touch event reported.
    SF_TOUCH_PANEL_V2_EVENT_UP,              ///< Touch released.
    SF_TOUCH_PANEL_V2_EVENT_NONE             ///< No valid touch event happened.
} sf_touch_panel_v2_event_t;

/** Touch data payload */
typedef struct st_sf_touch_panel_v2_payload
{
    int16_t                    x;            ///< X coordinate.
    int16_t                    y;            ///< Y coordinate.
    sf_touch_panel_v2_event_t  event_type;   ///< Touch event type.
} sf_touch_panel_v2_payload_t;

/** User callback*/
typedef struct st_sf_touchpanel_v2_callback_args
{
    sf_touch_panel_v2_payload_t    payload;       ///< Touch data and event provided to the user during callback
    void const                   * p_context;     ///< Context provided to user during callback
} sf_touchpanel_v2_callback_args_t;

/** Configuration for RTOS integrated touch panel framework. */
typedef struct st_sf_touch_panel_v2_cfg
{
    uint16_t           hsize_pixels;    ///< Horizontal size of screen in pixels.
    uint16_t           vsize_pixels;    ///< Vertical size of screen in pixels.
    UINT               priority;        ///< Priority of the touch panel thread.
    /** The frequency to report repeat (SF_TOUCH_PANEL_V2_EVENT_DOWN or SF_TOUCH_PANEL_V2_EVENT_HOLD) touch events in
     * Hertz. @note This will be converted to RTOS ticks in the driver and rounded up to the nearest integer
     * value of RTOS ticks. */
    uint16_t           update_hz;
    uint16_t           rotation_angle;  ///< Touch coordinate rotation angle(0/90/180/270)

    /** Pointer to hardware specific extension. */
    void const         * p_extend;
    void (* p_callback)(sf_touchpanel_v2_callback_args_t * p_args);
    void const         * p_context;     ///< User defined context passed into callback function
} sf_touch_panel_v2_cfg_t;

/** Calibration data passed to SF_TOUCH_PANEL_V2_Calibrate. */
typedef struct st_sf_touch_panel_v2_calibrate
{
    int32_t  x;             ///< Expected x coordinate.
    int32_t  y;             ///< Expected y coordinate.
    /** Pointer to hardware specific extension. */
    void const  * p_extend;
} sf_touch_panel_v2_calibrate_t;

/** Calibration factors calculated in order to calibrate the touch data. */
typedef struct st_sf_touch_panel_v2_calibrate_factors
{
    int32_t  a_coefficient;
    int32_t  b_coefficient;
    int32_t  c_coefficient;
    int32_t  d_coefficient;
    int32_t  e_coefficient;
    int32_t  f_coefficient;
    int32_t  determinant;
} sf_touch_panel_v2_calibrate_factors_t;

/** Touch panel V2 API structure. Touch panel V2 implementations use the following API. */
typedef struct st_sf_touch_panel_v2_api
{
    /** @brief  Create required RTOS objects, call lower level module for hardware specific initialization, and create a
     * thread to post touch data to user application.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_Open()
     *
     * @param[in,out] p_ctrl   Pointer to a structure allocated by user. This control structure is initialized in
     *                         this function.
     * @param[in]     p_cfg    Pointer to configuration structure. All elements of the structure must be set by user.
     */
    ssp_err_t (* open)(sf_touch_panel_v2_ctrl_t      * const p_ctrl,
                       sf_touch_panel_v2_cfg_t const * const p_cfg);

    /** @brief  Begin calibration routine based on provided expected and actual coordinates.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_Calibrate()
     *
     * @param[in]   p_ctrl         Handle set in sf_touch_panel_v2_api_t::open.
     * @param[in]   p_display      Expected coordinates of the display.
     * @param[in]   p_touchscreen  Actual coordinates obtained from the touch driver.
     * @param[in]   timeout        ThreadX timeout. Select TX_NO_WAIT, a value in system clock counts between 1 and
     *                             0xFFFFFFFF, or TX_WAIT_FOREVER.
     */
    ssp_err_t (* calibrate)(sf_touch_panel_v2_ctrl_t            * const p_ctrl,
                            sf_touch_panel_v2_calibrate_t const * const p_display,
                            sf_touch_panel_v2_calibrate_t const * const p_touchscreen,
                            ULONG const timeout);

    /** @brief  Start scanning for touch events.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_Start()
     *
     * @param[in]   p_ctrl       Handle set in sf_touch_panel_v2_api_t::open.
     */
    ssp_err_t (* start)(sf_touch_panel_v2_ctrl_t       * const p_ctrl);

    /** @brief  Reads the touch data and fills in the touch payload data.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_TouchDataGet()
     *
     * @param[in,out] p_ctrl     Pointer to a structure allocated by user. This control structure is initialized in
     *                           this function.
     * @param[out]    p_payload  Pointer to the payload to data structure. Touch data provided should be processed to
     *                           logical pixel values.
     * @param[in]     timeout    ThreadX timeout. Select TX_NO_WAIT, a value in system clock counts between 1 and
     *                           0xFFFFFFFF, or TX_WAIT_FOREVER.
     */
    ssp_err_t (* touchDataGet)(sf_touch_panel_v2_ctrl_t * const p_ctrl,
                               sf_touch_panel_v2_payload_t * p_payload,
                               ULONG const timeout);

    /** @brief  Stop scanning for touch events.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_Stop()
     *
     * @param[in]   p_ctrl       Handle set in sf_touch_panel_v2_api_t::open.
     */
    ssp_err_t (* stop)(sf_touch_panel_v2_ctrl_t       * const p_ctrl);

    /** @brief  Reset touch chip if reset pin is provided.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_Reset()
     *
     * @note This does not include calibration.  Use sf_touch_panel_v2_api_t::calibrate from the application after
     * this function if calibration is required after reset.
     *
     * @param[in]   p_ctrl       Handle set in sf_touch_panel_v2_api_t::open.
     */
    ssp_err_t (* reset)(sf_touch_panel_v2_ctrl_t       * const p_ctrl);

    /** @brief Terminate touch thread and close channel at HAL layer.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_Close()
     *
     * @param[in]   p_ctrl       Handle set in sf_touch_panel_v2_api_t::open.
     */
    ssp_err_t (* close)(sf_touch_panel_v2_ctrl_t      * const p_ctrl);

    /** @brief Gets version and stores it in provided pointer p_version.
     * @par Implemented as
     *  - SF_TOUCH_PANEL_V2_VersionGet()
     *
     * @param[out]  p_version  Code and API version used stored here.
     */
    ssp_err_t (* versionGet)(ssp_version_t     * const p_version);
} sf_touch_panel_v2_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_sf_touch_panel_v2_instance
{
    sf_touch_panel_v2_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    sf_touch_panel_v2_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    sf_touch_panel_v2_api_t const * p_api;     ///< Pointer to the API structure for this instance
} sf_touch_panel_v2_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup SF_TOUCH_PANEL_V2_API)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* SF_TOUCH_PANEL_V2_API_H */
