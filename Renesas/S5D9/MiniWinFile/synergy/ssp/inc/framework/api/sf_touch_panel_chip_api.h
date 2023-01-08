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
 * File Name    : sf_touch_panel_chip_api.h
 * Description  : RTOS integrated touch panel chip framework API.
 **********************************************************************************************************************/

#ifndef SF_TOUCH_PANEL_CHIP_API_H
#define SF_TOUCH_PANEL_CHIP_API_H

/*******************************************************************************************************************//**
 * @ingroup SF_Interface_Library
 * @defgroup SF_TOUCH_PANEL_CHIP_API Touch chip Interface
 * @brief RTOS-integrated Touch chip Interface.
 *
 * @section SF_TOUCH_PANEL_CHIP_SUMMARY Summary
 * This module is a ThreadX-aware Touch chip interface which gets the data from the touch chip.
 * This Interface is implemented by @ref SF_TOUCH_PANEL_V2.
 *
 * Interfaces used:
 * - @ref SF_TOUCH_PANEL_V2_API
 *
 * Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * Touch Panel chip Framework Interface description: @ref FrameworkTouchPanelInterface
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "sf_touch_panel_v2_api.h"
/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SF_TOUCH_PANEL_CHIP_API_VERSION_MAJOR (2U)
#define SF_TOUCH_PANEL_CHIP_API_VERSION_MINOR (0U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Touch panel chip framework control block. Allocate an instance specific control block to pass into the
 * touch panel chip framework API calls.
 * @par Implemented as
 * - sf_touch_panel_chip_sx8654_instance_ctrl_t
 * - sf_touch_panel_chip_ft5x06_instance_ctrl_t
 */
typedef void sf_touch_panel_chip_ctrl_t;

/** Configuration for RTOS integrated touch driver. */
typedef struct st_sf_touch_panel_chip_cfg
{
    void const  * p_extend;
} sf_touch_panel_chip_cfg_t;

/**Touch panel chip API structure. Touch panel chip implementations use the following API. */
typedef struct st_sf_touch_panel_chip_api
{
    /** @brief  Initializes the touch chip.
     * @param[in,out] p_ctrl     Pointer to a structure allocated by user. This control structure is initialized in
     *                           this function.
     * @param[in]     p_cfg      Pointer to configuration structure. All elements of the structure must be set by user.
     */
    ssp_err_t (* open)(sf_touch_panel_chip_ctrl_t * const p_ctrl, sf_touch_panel_chip_cfg_t const * const p_cfg);

    /** @brief  Reads the touch chip and fills in the touch payload data.
     * @param[in,out] p_ctrl     Pointer to a structure allocated by user. This control structure is initialized in
     *                           this function.
     * @param[out]    p_payload  Pointer to the payload data structure. Touch data provided should be processed to
     *                           logical pixel values.
     */
    ssp_err_t (* payloadGet)(sf_touch_panel_chip_ctrl_t * const p_ctrl, sf_touch_panel_v2_payload_t * p_payload);

    /** @brief  Resets the touch chip.
     * @param[in,out] p_ctrl     Pointer to a structure allocated by user. This control structure is initialized in
     *                           this function.
     */
    ssp_err_t (* reset)(sf_touch_panel_chip_ctrl_t * const p_ctrl);

    /** @brief  Close the touch chip.
     * @param[in,out] p_ctrl     Pointer to a structure allocated by user. This control structure is initialized in
     *                           this function.
     */
    ssp_err_t (* close)(sf_touch_panel_chip_ctrl_t * const p_ctrl);

    /** @brief Gets the chip version and stores it in provided pointer p_version.
     * @param[out]  p_version  Code and API version used are stored here.
     *
     */
    ssp_err_t (* versionGet)(ssp_version_t     * const p_version);

} sf_touch_panel_chip_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_sf_touch_panel_chip_instance
{
    sf_touch_panel_chip_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    sf_touch_panel_chip_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    sf_touch_panel_chip_api_t const * p_api;     ///< Pointer to the API structure for this instance
} sf_touch_panel_chip_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup SF_TOUCH_PANEL_CHIP_API)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* SF_TOUCH_PANEL_CHIP_API_H */
