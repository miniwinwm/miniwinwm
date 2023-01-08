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
 * File Name    : sf_i2c.h
 * Description  : I2C SSP framework driver header file
 **********************************************************************************************************************/

#ifndef SF_I2C_H
#define SF_I2C_H

/*******************************************************************************************************************//**
 * @ingroup SF_Library
 * @defgroup SF_I2C I2C Framework
 * @brief RTOS-integrated I2C Framework.
 *
 * @section SF_I2C_SUMMARY Summary
 * This is a ThreadX-aware I2C driver API. The API implements the @ref SF_I2C_API interface and can access several hardware
 * peripherals at the HAL layer.
 * The connection to the HAL layer is established by passing in a driver structure in SF_I2C_Open.
 * @section SF_I2C_API_INTERFACE Interface Used
 * @see SF_I2C_API
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
/* Includes driver interface. */
#include "r_i2c_api.h"
#include "sf_i2c_api.h"
#include "sf_i2c_cfg.h"
#include "tx_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SF_I2C_CODE_VERSION_MAJOR (2U)
#define SF_I2C_CODE_VERSION_MINOR (0U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** I2C instance control block. DO NOT INITIALIZE.  Initialization occurs when sf_i2c_api_t::open is called. */
typedef struct st_sf_i2c_instance_ctrl
{
    sf_i2c_bus_t                * p_bus;               ///< Bus using this device. Copy from configuration structure
    i2c_master_instance_t const * p_lower_lvl_i2c;     ///< I2C instance
    i2c_cfg_t                     lower_lvl_cfg;       ///< Used to reconfigure I2C driver
    i2c_ctrl_t                  * p_lower_lvl_ctrl;    ///< I2C peripheral control block
    sf_i2c_dev_state_t            dev_state;           ///< Device status
    bool                          restarted;           ///< Indicates whether device issued a restart
} sf_i2c_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sf_i2c_api_t g_sf_i2c_on_sf_i2c;
/** @endcond */

/*******************************************************************************************************************//**
 * @} (end defgroup SF_I2C)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* SF_I2C_H */
