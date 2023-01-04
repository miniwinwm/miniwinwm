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
* File Name    : r_riic.h
* Description  : I2C Bus (RIIC) Module instance header file.
***********************************************************************************************************************/


/*******************************************************************************************************************//**
 * @ingroup HAL_Library
 * @defgroup RIIC IIC
 * @brief Driver for the I2C Bus Interface (IIC).
 *
 * This module supports the Renesas Inter-Integrated Circuit (IIC) peripheral. It implements the following interfaces:
 *   - @ref I2C_API r_i2c_api.h
 * @{
***********************************************************************************************************************/

#ifndef R_RIIC_H
#define R_RIIC_H

#include "bsp_api.h"
#include "r_riic_cfg.h"
#include "r_i2c_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RIIC_MASTER_CODE_VERSION_MAJOR   (2U)
#define RIIC_MASTER_CODE_VERSION_MINOR   (0U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/** I2C Timeout mode parameter definition */
typedef enum e_riic_timeout_mode
{
    RIIC_TIMEOUT_MODE_LONG      = 0,     ///< Timeout Detection Time Select: Long Mode -> TMOS = 0
    RIIC_TIMEOUT_MODE_SHORT     = 1      ///< Timeout Detection Time Select: Short Mode -> TMOS = 1
} riic_timeout_mode_t;

/** I2C control structure. DO NOT INITIALIZE. */
typedef struct st_riic_instance_ctrl
{
    i2c_cfg_t   info;     ///< Information describing I2C device
    uint32_t    open;     ///< Flag to determine if the device is open
    void      * p_reg;    ///< Base register for this channel

    IRQn_Type   rxi_irq;  ///< Receive IRQ number
    IRQn_Type   txi_irq;  ///< Transmit IRQ number
    IRQn_Type   tei_irq;  ///< Transmit end IRQ number
    IRQn_Type   eri_irq;  ///< Error IRQ number

    /* Current transfer information. */
    uint8_t     *   p_buff;         /**< Holds the data associated with the transfer */
    uint32_t        total;          /**< Holds the total number of data bytes to transfer */
    uint32_t        remain;         /**< Tracks the remaining data bytes to transfer */
    uint32_t        loaded;         /**< Tracks the number of data bytes written to the register */

    uint8_t         addr_low;       /**< Holds the last address byte to issue */
    uint8_t         addr_high;      /**< Holds the first address byte to issue in 10-bit mode  */
    uint8_t         addr_total;     /**< Holds the total number of address bytes to transfer */
    uint8_t         addr_remain;    /**< Tracks the remaining address bytes to transfer */
    uint8_t         addr_loaded;    /**< Tracks the number of address bytes written to the register */

    volatile bool   read;           /**< Holds the direction of the data byte transfer */
    volatile bool   restart;        /**< Holds whether or not the restart should be issued when done */
    volatile bool   err;            /**< Tracks whether or not an error occurred during processing */
    volatile bool   restarted;      /**< Tracks whether or not a restart was issued during the previous transfer */
    volatile bool   dummy_read_completed;  /**< Tracks whether the dummy read is performed */
    volatile bool   activation_on_rxi; /**< Tracks whether the transfer is activated on RXI interrupt */
    volatile bool   activation_on_txi; /**< Tracks whether the transfer is activated on TXI interrupt */
    volatile bool   address_restarted;   /**< Tracks whether the restart condition is send on 10 bit read */
    volatile bsp_lock_t   resource_lock_tx_rx; /**< Resource lock for transmission/reception */
    riic_timeout_mode_t   timeout_mode;  /**< Holds the timeout mode value. i.e short mode or long mode */
    i2c_hw_err_event_t    actual_hwErr_event; /**< Holds error event value obtained through hardware */
} riic_instance_ctrl_t;

/** R_IIC extended configuration */
typedef struct st_riic_extended_cfg
{
    riic_timeout_mode_t timeout_mode;      ///< Timeout Detection Time Select: Long Mode = 0 and Short Mode = 1.
} riic_extended_cfg;

/**********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern i2c_api_master_t const g_i2c_master_on_riic;
/** @endcond */

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif // R_RIIC_H

/*******************************************************************************************************************//**
 * @} (end defgroup RIIC)
***********************************************************************************************************************/
