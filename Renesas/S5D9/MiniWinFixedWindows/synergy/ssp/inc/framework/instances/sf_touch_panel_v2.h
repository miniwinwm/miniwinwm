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
 * File Name    : sf_touch_panel_v2.h
 * Description  : RTOS integrated touch panel API extension for touch panel chips.
 **********************************************************************************************************************/

#ifndef SF_TOUCH_PANEL_V2_H
#define SF_TOUCH_PANEL_V2_H

/*******************************************************************************************************************//**
 * @ingroup SF_Library
 * @defgroup SF_TOUCH_PANEL_V2 Touch Panel V2 Framework
 * @brief RTOS-integrated touch panel V2 Framework implementation touch chips.
 *
 * @section SF_TOUCH_PANEL_V2_SUMMARY Summary
 * This is a ThreadX touch panel framework implemented for external touch controllers with IRQ pins used to notify
 * the application when new data is available.
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
/* Include driver API and ThreadX API */
#include "sf_touch_panel_v2_api.h"
#include "sf_touch_panel_chip_api.h"
#include "tx_api.h"
#include "sf_touch_panel_v2_cfg.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SF_TOUCH_PANEL_V2_CODE_VERSION_MAJOR (2U)
#define SF_TOUCH_PANEL_V2_CODE_VERSION_MINOR (0U)

#define SF_TOUCH_PANEL_V2_RESET_PIN_UNUSED   (0xFFFF)

/** Stack size for touch panel thread. */
#define SF_TOUCH_PANEL_V2_STACK_SIZE         (SF_TOUCH_PANEL_V2_CFG_THREAD_STACK_SIZE)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Instance control block. DO NOT INITIALIZE. Initialization occurs when sf_touch_panel_v2_api_t::open is called */
typedef struct st_sf_touch_panel_v2_instance_ctrl
{
    uint32_t                     open;               ///< Used by driver to check if control block is valid.
    uint16_t                     hsize_pixels;       ///< Horizontal size of screen in pixels.
    uint16_t                     vsize_pixels;       ///< Vertical size of screen in pixels.
    sf_touch_panel_v2_payload_t  payload;            ///< Pointer to buffer used to store payload.
    TX_MUTEX                     mutex;              ///< Mutex used to protect access to shared resources.
    TX_EVENT_FLAGS_GROUP         flags;              ///< Event flags for internal communication.
    TX_THREAD                    thread;             ///< Main touch panel thread.
    TX_SEMAPHORE                 semaphore;          ///< Semaphore used for ::SF_TOUCH_PANEL_V2_TouchDataGet.

    /** Stack for touch panel thread */
    uint8_t  stack[SF_TOUCH_PANEL_V2_STACK_SIZE] BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
    sf_touch_panel_chip_instance_t const  * p_chip;  ///< Pointer to touch chip.

    /** The frequency to report repeat (SF_TOUCH_PANEL_V2_EVENT_DOWN or SF_TOUCH_PANEL_V2_EVENT_HOLD) touch events in
     * Hertz. @note This will be converted to RTOS ticks in the driver and rounded up to the nearest integer
     * value of RTOS ticks. */
    uint16_t                  update_hz;
    uint16_t                  rotation_angle;        ///< Touch coordinate rotation angle(0/90/180/270)
    void (* p_callback)(sf_touchpanel_v2_callback_args_t * p_args);
    void const                * p_context;           ///< Pointer to user callback context data
    sf_touch_panel_v2_calibrate_factors_t calibration_factor;
    bool                     calibrate;              ///< Used to check if calibration is required or not.
} sf_touch_panel_v2_instance_ctrl_t;

typedef struct st_sf_touch_panel_v2_extend_cfg
{
    sf_touch_panel_chip_instance_t const  * p_chip;  ///< Chip specific functions and definitions
} sf_touch_panel_v2_extend_cfg_t;
/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sf_touch_panel_v2_api_t      g_sf_touch_panel_v2_on_sf_touch_panel_v2;
/** @endcond */

/*******************************************************************************************************************//**
 * @} (end defgroup SF_TOUCH_PANEL_V2)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* SF_TOUCH_PANEL_V2_H */
