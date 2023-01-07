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

/*********************************************************************************************************************
 * File Name    : r_spi_api.h
 * Description  : This file provides data definitions, data structures and function prototype for SPI interface.
 ********************************************************************************************************************/

#ifndef R_SPI_API_H
#define R_SPI_API_H

/*****************************************************************************************************************//**
 * @ingroup Interface_Library
 * @defgroup SPI_API SPI Interface
 * @brief Interface for SPI communications.
 *
 * @section SPI_SUMMARY Summary
 * The SPI Interface  provides access to the SPI bus API. The Interface implements the @ref SCI_SPI HAL layer driver
 * module.
 *
 * Implemented by:
 * - @ref SPI
 * - @ref SCI_SPI
 *
 * Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * SPI Interface description: @ref HALSPIInterface
 * @{
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Includes
 ********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/*********************************************************************************************************************
 * Macro definitions
 ********************************************************************************************************************/
#define SPI_API_VERSION_MAJOR (2U)
#define SPI_API_VERSION_MINOR (0U)

/*********************************************************************************************************************
 * Typedef definitions
 ********************************************************************************************************************/
/** Data bit width */
typedef enum e_spi_bit_width
{
    SPI_BIT_WIDTH_8_BITS  = (1),        ///< Data bit width is 8 bits byte
    SPI_BIT_WIDTH_16_BITS = (2),        ///< Data bit width is 16 bits word
    SPI_BIT_WIDTH_32_BITS = (4)         ///< Data bit width is 32 bits long word
} spi_bit_width_t;

/** Master or slave operating mode */
typedef enum e_spi_mode
{
    SPI_MODE_MASTER,        ///< Channel operates as SPI master
    SPI_MODE_SLAVE          ///< Channel operates as SPI slave
} spi_mode_t;

/** Clock phase */
typedef enum e_spi_clk_phase
{
    SPI_CLK_PHASE_EDGE_ODD,    ///< 0: Data sampling on odd edge, data variation on even edge
    SPI_CLK_PHASE_EDGE_EVEN    ///< 1: Data variation on odd edge, data sampling on even edge
} spi_clk_phase_t;

/** Clock polarity */
typedef enum e_spi_clk_polarity
{
    SPI_CLK_POLARITY_LOW,     ///< 0: Clock polarity is low when idle
    SPI_CLK_POLARITY_HIGH     ///< 1: Clock polarity is high when idle
} spi_clk_polarity_t;

/** Mode fault error flag. This error occurs when the device is setup as a master, but the SSLA line does not seem to be
 *  controlled by the master. This usually happens when the connecting device is also acting as master.
 *  A similar situation can also happen when configured as a slave. */
typedef enum e_spi_mode_fault
{
    SPI_MODE_FAULT_ERROR_ENABLE,   ///< Mode fault error flag on
    SPI_MODE_FAULT_ERROR_DISABLE   ///< Mode fault error flag off
} spi_mode_fault_t;

/** Bit-order */
typedef enum e_spi_bit_order
{
    SPI_BIT_ORDER_MSB_FIRST,   ///< Send MSB first in transmission
    SPI_BIT_ORDER_LSB_FIRST    ///< Send LSB first in transmission
} spi_bit_order_t;

/** SPI events */
typedef enum e_spi_event
{
    SPI_EVENT_TRANSFER_COMPLETE = 1,    ///< The data transfer was completed
    SPI_EVENT_TRANSFER_ABORTED,         ///< The data transfer was aborted
    SPI_EVENT_ERR_MODE_FAULT,           ///< Mode fault error
    SPI_EVENT_ERR_READ_OVERFLOW,        ///< Read overflow error
    SPI_EVENT_ERR_PARITY,               ///< Parity error
    SPI_EVENT_ERR_OVERRUN,              ///< Overrun error
    SPI_EVENT_ERR_FRAMING,              ///< Framing error
    SPI_EVENT_ERR_MODE_UNDERRUN         ///< Underrun error
} spi_event_t;

/** Used by control block only. */
typedef enum e_spi_operation
{
    SPI_OPERATION_DO_TX    = 0x1,    /**< perform SPI transmission operation */
    SPI_OPERATION_DO_RX    = 0x2,    /**< perform SPI reception operation */
    SPI_OPERATION_DO_TX_RX = 0x3     /**< perform SPI Transmission and reception operation */
} spi_operation_t;

/** Common callback parameter definition */
typedef struct st_spi_callback_args
{
    uint32_t     channel;         ///< Device channel number
    spi_event_t  event;           ///< Event code
    void const * p_context;       ///< Context provided to user during callback
} spi_callback_args_t;

/** SPI interface configuration */
typedef struct st_spi_cfg
{
    uint8_t            channel;                                   ///< Channel number to be used
    uint8_t            rxi_ipl;                                   ///< Receive interrupt priority
    uint8_t            txi_ipl;                                   ///< Transmit interrupt priority
    uint8_t            tei_ipl;                                   ///< Transmit end interrupt priority
    uint8_t            eri_ipl;                                   ///< Error interrupt priority
    spi_mode_t         operating_mode;                            ///< Select master or slave operating mode
    spi_clk_phase_t    clk_phase;                                 ///< Data sampling on odd or even clock edge
    spi_clk_polarity_t clk_polarity;                              ///< Clock level when idle
    spi_mode_fault_t   mode_fault;                                ///< Mode fault error (master/slave conflict) flag
    spi_bit_order_t    bit_order;                                 ///< Select to transmit MSB/LSB first
    uint32_t           bitrate;                                   ///< Bits Per Second
    transfer_instance_t const * p_transfer_tx;                    ///< To use SPI DTC/DMA write transfer, link a DTC/DMA instance here.  Set to NULL if unused.
    transfer_instance_t const * p_transfer_rx;                    ///< To use SPI DTC/DMA read transfer, link a DTC/DMA instance here.  Set to NULL if unused.
    void            (* p_callback)(spi_callback_args_t * p_args); ///< Pointer to user callback function
    void const       * p_context;                                 ///< User defined context passed to callback function
    void const       * p_extend;                                  ///< Extended SPI hardware dependent configuration
} spi_cfg_t;

/** SPI control block.  Allocate an instance specific control block to pass into the SPI API calls.
 * @par Implemented as
 * - sci_spi_instance_ctrl_t
 * - rspi_instance_ctrl_t
 */
typedef void spi_ctrl_t;

/** Shared Interface definition for SPI */
typedef struct st_spi_api
{
    /** Initialize a channel for SPI communication mode.
     * @par Implemented as
     * - R_RSPI_Open()
     * - R_SCI_SPI_Open()
     *
     * @param[in, out] p_ctrl Pointer to user-provided storage for the control block.
     * @param[in]      p_cfg  Pointer to SPI configuration structure.
     */
    ssp_err_t (* open)(spi_ctrl_t                    * p_ctrl,
                       spi_cfg_t               const * const p_cfg);

    /** Receive data from an SPI device.
     * @par Implemented as
     * - R_RSPI_Read()
     * - R_SCI_SPI_Read()
     *
     * @param[in]  p_ctrl    Pointer to the control block for the channel.
     * @param[in]  length    Number of units of data to be transferred (unit size specified by the
     *                       bit_width).
     * @param[in]  bit_width Data bit width to be transferred.
     * @param[out] p_dest    Pointer to destination buffer into which data will be copied that is received from a SPI
     *                       device. It is the responsibility of the caller to ensure that adequate space is available
     *                       to hold the requested data count.
     */
    ssp_err_t (* read)(spi_ctrl_t                * const p_ctrl,
                       void const                * p_dest,
                       uint32_t const              length,
                       spi_bit_width_t const       bit_width);

    /** Transmit data to an SPI device.
     * @par Implemented as
     * - R_RSPI_Write()
     * - R_SCI_SPI_Write()
     *
     * @param[in]  p_ctrl    Pointer to the control block for the channel.
     * @param[in]  p_src     Pointer to a source data buffer from which data will be transmitted to a SPI device.
     *                       The argument must not be NULL.
     * @param[in]  length    Number of units of data to be transferred (unit size specified by the
     *                       bit_width).
     * @param[in]  bit_width Data bit width to be transferred.
     */
    ssp_err_t (* write)(spi_ctrl_t                * const p_ctrl,
                        void const                * p_src,
                        uint32_t const              length,
                        spi_bit_width_t const       bit_width);

    /** Simultaneously transmit data to an SPI device while receiving data from a SPI device (full duplex).
     * @par Implemented as
     * - R_RSPI_WriteRead()
     * - R_SCI_SPI_WriteRead()
     *
     * @param[in]  p_ctrl    Pointer to the control block for the channel.
     * @param[in]  p_src     Pointer to a source data buffer from which data will be transmitted to a SPI device.
     *                       The argument must not be NULL.
     * @param[out] p_dest    Pointer to destination buffer into which data will be copied that is received from a SPI
     *                       device. It is the responsibility of the caller to ensure that adequate space is available
     *                       to hold the requested data count. The argument must not be NULL.
     * @param[in]  length    Number of units of data to be transferred (unit size specified by the bit_width).
     * @param[in]  bit_width Data bit width to be transferred.
     */
    ssp_err_t (* writeRead)(spi_ctrl_t                * const p_ctrl,
                            void const                * p_src,
                            void const                * p_dest,
                            uint32_t const              length,
                            spi_bit_width_t const       bit_width);

    /** Remove power to the SPI channel designated by the handle and disable the associated interrupts.
     * @par Implemented as
     * - R_RSPI_Close()
     * - R_SCI_SPI_Close()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the channel.
     */
    ssp_err_t (* close)(spi_ctrl_t * const p_ctrl);

    /** Get the version information of the underlying driver.
     * @par Implemented as
     * - R_RSPI_VersionGet()
     * - R_SCI_SPI_VersionGet()
     *
     * @param[out]  p_version pointer to memory location to return version number
     */
    ssp_err_t (* versionGet)(ssp_version_t * p_version);
} spi_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_spi_instance
{
    spi_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    spi_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    spi_api_t const * p_api;     ///< Pointer to the API structure for this instance
} spi_instance_t;

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* End of R_SPI_API_H */

/*****************************************************************************************************************//**
 * @} (end defgroup SPI_API)
 ********************************************************************************************************************/
