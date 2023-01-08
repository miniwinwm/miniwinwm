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
 * File Name    : sf_i2c_api.h
 * Description  : This file provides data definitions, data structures and function prototype for I2C Framework
 * interface.
 **********************************************************************************************************************/

#ifndef SF_I2C_API_H
#define SF_I2C_API_H

/*******************************************************************************************************************//**
 * @ingroup SF_Interface_Library
 * @defgroup SF_I2C_API I2C Framework
 * @brief RTOS-integrated I2C Framework Interface.
 *
 * @section SF_I2C_API_SUMMARY Summary
 * This is a ThreadX-aware I2C interface. It can be implemented by several hardware peripherals at the HAL layer through
 * the I2C interface @ref I2C_API.
 *
 * The connection to the HAL layer is established by passing in a driver structure in SF_I2C_Open().
 *
  * Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * SPI Framework Interface description: @ref FrameworkI2CInterface
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
/** Includes driver interface. */
#include "r_i2c_api.h"
#include "sf_i2c_cfg.h"
#include "tx_api.h"
#include "r_ioport.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SF_I2C_API_VERSION_MAJOR (2U)
#define SF_I2C_API_VERSION_MINOR (0U)

/*********************************************************************************************************************
 * Typedef definitions
 ********************************************************************************************************************/
/** SF I2C device state */
typedef enum e_sf_i2c_dev_state
{
    SF_I2C_DEV_STATE_CLOSED = 0,       ///< I2C device is closed
    SF_I2C_DEV_STATE_OPENED,           ///< I2C device is opened
} sf_i2c_dev_state_t;

/** I2C framework control block.  Allocate an instance specific control block to pass into the
 * I2C framework API calls.
 * @par Implemented as
 * - sf_i2c_instance_ctrl_t
 */
typedef void sf_i2c_ctrl_t;

/** Data structure defining a I2C bus. */
typedef struct st_sf_i2c_bus
{
    uint8_t                  channel;            ///< Channel
    TX_MUTEX               * p_lock_mutex;       ///< Lock mutex handle for this channel
    TX_MUTEX                 device_count_mutex; ///< Device count mutex handle for this device
    TX_EVENT_FLAGS_GROUP   * p_sync_eventflag;   ///< Pointer to the event flag object for I2C data transfer
    sf_i2c_ctrl_t         ** pp_curr_ctrl;       ///< Current device using the bus (by switching the address)
    uint8_t                * p_bus_name;         ///< User-supplied name to identify the bus. Useful for debugging
    i2c_api_master_t const * p_lower_lvl_api;    ///< Pointer to I2C HAL interface to be used in the framework
    uint8_t                  device_count;       ///< Number of devices on the bus; initialize to 0
    sf_i2c_ctrl_t         ** pp_curr_bus_ctrl;   ///< Device configured on the bus (low level configuration)
} sf_i2c_bus_t;

/** Configuration for Framework I2C driver */
typedef struct st_sf_i2c_cfg
{
    sf_i2c_bus_t     * p_bus;                          ///< Bus used by the device
    i2c_cfg_t const  * p_lower_lvl_cfg;                ///< Pointer to I2C HAL configuration
} sf_i2c_cfg_t;

/** Shared Interface definition for I2C Framework*/
typedef struct st_sf_i2c_api
{
    /******************************************************************************************************************//**
     * @brief   Open a designated I2C device on a bus.
     * @par Implemented as
     *  - SF_I2C_Open()
     * @param[out]  p_ctrl  Control handle for I2C framework driver context for a device (Value returns from this
     *              function). This value must be cleared by user.
     * @param[in]   p_cfg   I2C configuration includes I2C bus and low level configuration
     *********************************************************************************************************************/
    ssp_err_t (* open)(sf_i2c_ctrl_t              * p_ctrl,
                       sf_i2c_cfg_t const * const p_cfg);

    /******************************************************************************************************************//**
     * @brief  Receive data from I2C device.
     * @par Implemented as
     *  - SF_I2C_Read()
     * @param[in]   p_ctrl      Pointer to previously opened I2C SF control structure.
     * @param[in]   p_dest      Pointer to location to store read data.
     * @param[in]   bytes       Number of bytes to read.
     * @param[in]   restart     Indicates whether the restart condition should be issued after reading.
     * @param[in]   timeout     ThreadX timeout. Options include TX_NO_WAIT (0x00000000), TX_WAIT_FOREVER (0xFFFFFFFF),
     *                          and timeout value (0x00000001 through 0xFFFFFFFE) in ThreadX tick counts.
     *********************************************************************************************************************/
    ssp_err_t (* read)(sf_i2c_ctrl_t           * const p_ctrl,
                       uint8_t                 * const p_dest,
                       uint32_t const                  bytes,
                       bool const                      restart,
                       uint32_t const                  timeout);

    /******************************************************************************************************************//**
     * @brief  Transmit data to I2C device.
     * @par Implemented as
     *  - SF_I2C_Write()
     * @param[in]   p_ctrl                     Pointer to previously opened I2C control structure.
     * @param[in]   p_src                      Pointer to location to get write data.
     * @param[in]   bytes                      Number of bytes to write.
     * @param[in]   restart                    Indicates whether the restart condition should be issued after writing.
     * @param[in]   timeout                    ThreadX timeout. Options include TX_NO_WAIT (0x00000000), TX_WAIT_FOREVER
     *										   (0xFFFFFFFF), and timeout value (0x00000001 through 0xFFFFFFFE) in
     *                                         ThreadX tick counts.
     *********************************************************************************************************************/
    ssp_err_t (* write)(sf_i2c_ctrl_t          * const p_ctrl,
                        uint8_t                * const p_src,
                        uint32_t const                 bytes,
                        bool const                     restart,
                        uint32_t const                 timeout);

    /******************************************************************************************************************//**
     * @brief   Abort any in-progress transfer and force the I2C peripheral into a ready state.
     * @par Implemented as
     *  - SF_I2C_Reset()
     *
     *  This function safely terminates any in-progress I2C transfer with the device. If a transfer is aborted, the
     *  user is be notified via callback with an abort event. Since the callback is optional, this function also
     *  returns a specific error code in this situation.
     * @param[in]   p_ctrl                  Pointer to device control block initialized in Open call for I2C driver.
     * @param[in]   timeout                 ThreadX timeout. Options include TX_NO_WAIT (0x00000000), TX_WAIT_FOREVER
     *										(0xFFFFFFFF), and timeout value (0x00000001 through 0xFFFFFFFE) in ThreadX
     *                                      tick counts.
     *********************************************************************************************************************/
    ssp_err_t (* reset)(sf_i2c_ctrl_t          * const p_ctrl,
                        uint32_t const                 timeout);

    /******************************************************************************************************************//**
     * @brief  Disable the I2C device designated by the control handle. Close the RTOS services used by the bus if
     *         no devices are connected to the bus.
     * @par Implemented as
     *  - SF_I2C_Close()
     * @param[in]  p_ctrl                  Control handle for I2C framework driver context for a device
     *********************************************************************************************************************/
    ssp_err_t (* close)(sf_i2c_ctrl_t * const p_ctrl);

    /******************************************************************************************************************//**
     * @brief  Lock the bus for a device. Locking allows devices to reserve a bus to themselves for a given
     *         period of time (i.e. between lock and unlock).
     *         This allows devices to complete several reads and writes on the bus without interrupt, which is
     *         required in some instances.
     * @par Implemented as
     *  - SF_I2C_Lock()
     * @param[in]  p_ctrl            Control handle for I2C framework driver context for a device
     *********************************************************************************************************************/
    ssp_err_t (* lock)(sf_i2c_ctrl_t * const p_ctrl);

    /******************************************************************************************************************//**
     * @brief  Unlock the bus from a particular device and make it available for other devices.
     *         This allows other devices to use bus for reads and writes on the bus.
     * @par Implemented as
     *  - SF_I2C_Unlock()
     * @param[in]  p_ctrl            Control handle for I2C framework driver context for a device
     *********************************************************************************************************************/
    ssp_err_t (* unlock)(sf_i2c_ctrl_t * const p_ctrl);

    /******************************************************************************************************************//**
     * @brief  Get I2C framework version.
     * @par Implemented as
     *  - SF_I2C_VersionGet()
     * @param[in]  p_ctrl    Handle for I2C framework control block for a device
     *********************************************************************************************************************/
    ssp_err_t (* version)(ssp_version_t   * const p_version);

    /******************************************************************************************************************//**
     * @brief  Lock the I2C bus for a device. Locking reserves exclusive access to the I2C driver.
     *         Here a wait option is provided to the user. This allows devices to complete several reads and writes on
     *         the bus without interrupt, which is required in some instances.
     * @par Implemented as
     *  - SF_I2C_LockWait()
     * @param[in]  p_ctrl      Control handle for I2C framework driver context for a device
     * @param[in]  timeout     ThreadX timeout. Options include TX_NO_WAIT (0x00000000), TX_WAIT_FOREVER (0xFFFFFFFF),
     *                         and timeout value (0x00000001 through 0xFFFFFFFE) in ThreadX tick counts.
     *********************************************************************************************************************/
    ssp_err_t (* lockWait)(sf_i2c_ctrl_t * const p_ctrl, uint32_t const timeout);
} sf_i2c_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_sf_i2c_instance
{
    sf_i2c_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    sf_i2c_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    sf_i2c_api_t const * p_api;     ///< Pointer to the API structure for this instance
} sf_i2c_instance_t;


/*******************************************************************************************************************//**
 * @} (end defgroup SF_I2C_API)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* SF_I2C_API_H */
