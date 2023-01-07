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

/***********************************************************************************************************************
 * File Name    : r_sci_spi.h
 * Description  : SCI HAL driver for simple SPI interface.
 **********************************************************************************************************************/



#ifndef R_SCI_SPI_H
#define R_SCI_SPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_spi_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/*****************************************************************************************************************//**
 * @ingroup HAL_Library
 * @defgroup SCI_SPI Simple SPI on SCI
 * @brief Driver for the Simple SPI on SCI.
 *
 * This module supports simple SPI serial communication using the microcontroller's SCI peripheral.
 * The Interface is defined in r_spi_api.h.
 * This module implements @ref SPI_API.
 * @{
 ********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SCI_SPI_CODE_VERSION_MAJOR (2U)
#define SCI_SPI_CODE_VERSION_MINOR (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** SPI instance control block. DO NOT INITIALIZE. */
typedef struct st_sci_spi_instance_ctrl
{
    uint8_t  channel;                                   ///< Channel number to be used
    uint32_t channel_opened;                            ///< Internal flag to indicate the peripheral was initialized
    transfer_instance_t const * p_transfer_tx;          ///< To use SPI DTC/DMA write transfer
    transfer_instance_t const * p_transfer_rx;          ///< To use SPI DTC/DMA read transfer
    void  (* p_callback)(spi_callback_args_t * p_args); ///< Pointer to user callback function
    void const * p_context;                             ///< Pointer to the higher level device context
    void      * p_reg;                                  ///< Base register for this channel
    IRQn_Type   rxi_irq;                                ///< Receive IRQ number
    IRQn_Type   txi_irq;                                ///< Transmit IRQ number
    IRQn_Type   tei_irq;                                ///< Transmit end IRQ number
    IRQn_Type   eri_irq;                                ///< Error IRQ number

    void              * p_src;
    void              * p_dest;
    uint32_t          tx_count;
    uint32_t          rx_count;
    uint32_t          xfr_length;
    transfer_addr_mode_t tx_dtc_addr_mode; /* Addressing mode of opened TX transfer instance. */
    uint8_t           bytes_per_transfer;  /* Source buffer bytes per transfer: 1, 2, or 4. */
    bool              do_tx;               /* State flag for transmit operation. */
    spi_operation_t   transfer_mode;       /* Transmit only, receive only, or transmit-receive. */
    bsp_lock_t        resource_lock_tx_rx; /**< Resource lock for transmission/reception */
} sci_spi_instance_ctrl_t;

/** SCI SPI extended configuration */
typedef struct st_sci_spi_extended_cfg
{
    bool            bitrate_modulation;      /**< Bitrate Modulation Function enable or disable     */
} sci_spi_extended_cfg;
/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** Filled in Interface API structure for this Instance. */
extern const spi_api_t g_spi_on_sci;

/*******************************************************************************************************************//**
 * @} (end defgroup SCI_SPI)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* R_SCI_SPI_H */


