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
 * File Name    : sf_external_irq_api.h
 * Description  : AMS API for ThreadX-aware external interrupt applications. Allows for external interrupt use.
 **********************************************************************************************************************/

#ifndef SF_EXTERNAL_IRQ_API_H
#define SF_EXTERNAL_IRQ_API_H

/*******************************************************************************************************************//**
 * @ingroup SF_Interface_Library
 * @defgroup SF_EXTERNAL_IRQ_API External IRQ Framework Interface
 * @brief RTOS-integrated External IRQ Framework Interface.
 *
 * @section SF_EXTERNAL_IRQ_API_SUMMARY Summary
 * This module is a ThreadX-aware external IRQ Framework Interface for external inputs such as
 * switches or other binary signals. The Interface is implemented by @ref SF_EXTERNAL_IRQ.
 *
 *
 *  Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * External IRQ Framework Interface description: @ref FrameworkExternalIRQInterface
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
/* Include driver API and ThreadX API */
#include "r_external_irq_api.h"
#include "tx_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SF_EXTERNAL_IRQ_API_VERSION_MAJOR (2U)
#define SF_EXTERNAL_IRQ_API_VERSION_MINOR (0U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** External interrupt control block.  Allocate an instance specific control block to pass into the
 * external interrupt framework API calls.
 * @par Implemented as
 * - sf_external_irq_instance_ctrl_t
 */
typedef void sf_external_irq_ctrl_t;

/** Options for what should happen when the external interrupt expires. */
typedef enum e_sf_external_irq_event
{
    /** Nothing happens during expiration.  Can be used for data transfer.
     */
    SF_EXTERNAL_IRQ_EVENT_NONE,

    /** Posts to internal semaphore. Select this if using ::SF_EXTERNAL_IRQ_Wait. */
    SF_EXTERNAL_IRQ_EVENT_SEMAPHORE_PUT,
} sf_external_irq_event_t;

/** Configuration for RTOS integrated external interrupt driver */
typedef struct st_sf_external_irq_cfg
{
    /** All info needed to work with lower layer */
    external_irq_instance_t const  * p_lower_lvl_irq;
    sf_external_irq_event_t        event; ///< Select what happens when the external IRQ is triggered.
} sf_external_irq_cfg_t;

/** External IRQ framework API structure.  External IRQ implementations  use the following API. */
typedef struct st_sf_external_irq_api
{
    /** Create the semaphore, then handle driver initialization at the HAL layer.
     * @par Implemented as
     *  - SF_EXTERNAL_IRQ_Open()
     *
     * @param[in,out] p_ctrl   Pointer to a structure allocated by user. The device control structure is
     *                         initialized in this function.
     * @param[in]     p_cfg    Pointer to configuration structure. All elements of the structure must be set by user.
     */
    ssp_err_t (* open)(sf_external_irq_ctrl_t        * const p_ctrl,
                       sf_external_irq_cfg_t const * const   p_cfg);

    /** Wait for the next external interrupt expiration, then return.
     * @pre Call ::SF_EXTERNAL_IRQ_Open to configure the external IRQ before using this function. During
     * ::SF_EXTERNAL_IRQ_Open, set sf_external_irq_cfg_t::sf_external_irq_event_t to
     *::SF_EXTERNAL_IRQ_EVENT_SEMAPHORE_PUT.
     *
     * @par Implemented as
     *  - SF_EXTERNAL_IRQ_Wait()
     *
     * @param[in]   p_ctrl       Handle set in ::SF_EXTERNAL_IRQ_Open.
     * @param[in]   timeout      ThreadX timeout. Select TX_NO_WAIT, a value in system clock counts between 1 and
     *                           0xFFFFFFFF, or TX_WAIT_FOREVER.
     */
    ssp_err_t (* wait)(sf_external_irq_ctrl_t        * const p_ctrl,
                       ULONG const                           timeout);

    /** Get version and store it in provided pointer p_version.
     * @par Implemented as
     *  - SF_EXTERNAL_IRQ_VersionGet()
     *
     * @param[out]  p_version  Code and API version used stored here.
     */
    ssp_err_t (* versionGet)(ssp_version_t     * const p_version);

    /** Close channel at HAL layer and release the RTOS services.
     * @par Implemented as
     *  - SF_EXTERNAL_IRQ_Close()
     *
     * @param[in]    p_ctrl    Pointer to device control block initialized in Open call for this external interrupt.
     */
    ssp_err_t (* close)(sf_external_irq_ctrl_t      * const p_ctrl);
} sf_external_irq_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_sf_external_irq_instance
{
    sf_external_irq_ctrl_t       * p_ctrl;   ///< Pointer to the control structure for this instance
    sf_external_irq_cfg_t const  * p_cfg;    ///< Pointer to the configuration structure for this instance
    sf_external_irq_api_t const  * p_api;    ///< Pointer to the API structure for this instance
} sf_external_irq_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup SF_EXTERNAL_IRQ_API)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* SF_EXTERNAL_IRQ_API_H */
