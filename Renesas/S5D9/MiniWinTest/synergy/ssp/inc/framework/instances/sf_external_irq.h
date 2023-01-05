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
 * File Name    : sf_external_irq.h
 * Description  : AMS API for ThreadX-aware external interrupt applications. Allows for external interrupt use.
 **********************************************************************************************************************/

#ifndef SF_EXTERNAL_IRQ_H
#define SF_EXTERNAL_IRQ_H

/*******************************************************************************************************************//**
 * @ingroup SF_Library
 * @defgroup SF_EXTERNAL_IRQ External IRQ Framework
 * @brief RTOS-integrated external IRQ Framework.
 *
 * @section SF_EXTERNAL_IRQ_SUMMARY Summary
 * This module is a ThreadX-aware external IRQ Framework for external inputs such as switches or other
 * binary signals.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
/* Include driver API and ThreadX API */
#include "sf_external_irq_api.h"
#include "tx_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SF_EXTERNAL_IRQ_CODE_VERSION_MAJOR (2U)
#define SF_EXTERNAL_IRQ_CODE_VERSION_MINOR (0U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when
 * sf_external_irq_api_t::open is called */
typedef struct st_sf_external_irq_instance_ctrl
{
    uint32_t                  open;          ///< Used by driver to check if control block is valid.
    TX_SEMAPHORE              semaphore;     ///< Semaphore used for ::SF_EXTERNAL_IRQ_Wait.
    external_irq_instance_t const * p_lower_lvl_irq;  ///< Pointer to lower level driver instance.
    bool                      callback_used; ///< Used by driver to check if wait can be used.
} sf_external_irq_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sf_external_irq_api_t g_sf_external_irq_on_sf_external_irq;
/** @endcond */

/*******************************************************************************************************************//**
 * @} (end defgroup SF_EXTERNAL_IRQ)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* SF_EXTERNAL_IRQ_H */
