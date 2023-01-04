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
 * File Name    : r_sci_spi.c
 * Description  : This module contains API functions and HLD layer functions for SCI simple SPI module.
 *                The API functions includes an open() function to initialize and power on the SPI bus,
 *                a close() function to power down and shut off the channel, read(), Write() and Write/read()
 *                function to access and transfer data to and from the SPI bus.
 *                HDL layer functions includes functions like r_sci_spi_baud_set() to set the baud rate,
 *                r_sci_spi_write_read_common for write and read data from the SPI bus and r_sci_spi_tx_rx_common()
 *                function as the transmit and reception handler and r_sci_spi_spei_isr_common.
 ********************************************************************************************************************/
/*********************************************************************************************************************
 * Includes
 ********************************************************************************************************************/
#include <string.h>

#include "bsp_api.h"
#include "r_spi_api.h"
#include "r_sci_spi.h"
#include "r_sci_spi_cfg.h"
#include "r_sci_spi_private_api.h"
#include "r_cgc.h"
#include "r_cgc_api.h"
#include "hw/hw_sci_spi_private.h"
#include "hw/hw_sci_common.h"

/*********************************************************************************************************************
 * Macro definitions
 ********************************************************************************************************************/
/** Macro for error logger. */
#ifndef SCI_SPI_ERROR_RETURN
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define SCI_SPI_ERROR_RETURN(a, err)  SSP_ERROR_RETURN((a), (err), &g_module_name[0], NULL)
#endif

#define SCI_SPI_SPMR_SSN_PIN_ENABLE_SET       (0x01U)   /* Enables the SSN pin function -- SSE bit. */
#define SCI_SPI_SPMR_SSN_PIN_ENABLE_SET       (0x01U)   /* Enables the SSN pin function -- SSE bit */
#define SCI_SPI_SPMR_CTS_ENABLE_SET           (0x02U)   /* Enables the CTS function -- CTSE bit */
#define SCI_SPI_SPMR_SLAVE_MODE               (0x04U)   /* Select the slave operation mode -- MSS bit */
#define SCI_SPI_SPMR_MODE_FAULT_ENABLE        (0x10U)   /* Enable Mode fault error detection -- MFF bit */
#define SCI_SPI_SPMR_CKPOL_INVERTED           (0x40U)   /* Clock polarity is inverted -- CKPOL bit */
#define SCI_SPI_SPMR_CKPH_DELAYED             (0x80U)   /* Clock is delayed -- CKPH bit */


#define SCI_SPI_SPMR_DEF                      (SCI_SPI_SPMR_SSN_PIN_ENABLE | SCI_SPI_SPMR_CKPOL_INVERTED \
                                |              SCI_SPI_SPMR_CKPH_DELAYED)

#define SCI_SPI_NUM_DIVISORS_SYNC             (4U)   /* Number of synchronous divisors */
#define SCI_SPI_BRR_MAX                       (255U) /* Maximum Bit Rate Register (BRR) */
#define SCI_SPI_BRR_MIN                       (0U)   /* Minimum Bit Rate Register (BRR) */

#define SCI_SPI_BYTE_DATA                     (0x01U)  /* Bit width is a byte */
#define SCI_SPI_WORD_DATA                     (0x02U)  /* Bit width is 2 bytes */
#define SCI_SPI_LONG_DATA                     (0x04U)  /* Bit width is 4 bytes */

/* Fixed data that is transmitted during receive-only operations. Change as needed. */
#define SCI_SPI_DUMMY_TXDATA                  (0xFFU)

/** "SCIS" in ASCII, used to determine if channel is open. */
#define SCI_SPI_OPEN                          (0x53434953ULL)
#define MOSI_VALUE_OF_SPI_READ                (0xFFFFFFFFU)

/*********************************************************************************************************************
 * Typedef definitions.
 ********************************************************************************************************************/
/*******************************************************************************************************************
 * Private global variables.
 ******************************************************************************************************************/
/* Name of module used by error logger macro. */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "sci_spi";
#endif

/** SPI HAL module version data structure */
static const ssp_version_t g_sci_spi_version =
{
    .api_version_major  = SPI_API_VERSION_MAJOR,
    .api_version_minor  = SPI_API_VERSION_MINOR,
    .code_version_major = SCI_SPI_CODE_VERSION_MAJOR,
    .code_version_minor = SCI_SPI_CODE_VERSION_MINOR
};

/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const spi_api_t   g_spi_on_sci =
{
    .open      = R_SCI_SPI_Open,
    .read      = R_SCI_SPI_Read,
    .write     = R_SCI_SPI_Write,
    .writeRead = R_SCI_SPI_WriteRead,
    .close     = R_SCI_SPI_Close,
    .versionGet= R_SCI_SPI_VersionGet
};

/* Baud rate divisor information(SPI mode). */
static const baud_setting_t sync_baud[SCI_SPI_NUM_DIVISORS_SYNC] =
{
/* Divisor, BGDM, ABCS, ABCSE, n. */
    {   4U, 1U, 1U, 1U, 0U },
    {  16U, 1U, 1U, 1U, 1U },
    {  64U, 1U, 1U, 1U, 2U },
    { 256U, 1U, 1U, 1U, 3U }
};

/*********************************************************************************************************************
 * Private function declarations.
 ********************************************************************************************************************/
/* Common routine used by SCI SPI API write or read functions. */
static ssp_err_t        r_sci_spi_write_read_common (sci_spi_instance_ctrl_t        * const p_ctrl,
                                                     void                     const *       p_src,
                                                     void                     const *       p_dest,
                                                     uint32_t                         const length,
                                                     spi_bit_width_t                  const bit_width,
                                                     spi_operation_t                        tx_rx_mode);

/* Sets the SCI bit rate registers (BRR) for a given frequency. */
static ssp_err_t        r_sci_spi_baud_set          (R_SCI0_Type * p_sci_reg,
                                                     uint32_t      bitrate);

/* Configures SCI SPI related transfer drivers (if enabled). */
static ssp_err_t        r_sci_spi_transfer_open     (spi_cfg_t const * const p_cfg, ssp_feature_t * p_ssp_feature);

static inline ssp_err_t r_sci_irq_cfg               (ssp_feature_t * p_feature, 
                                                     ssp_signal_t    signal, 
                                                     uint8_t         ipl,
                                                     void          * p_ctrl, 
                                                     IRQn_Type     * p_irq);

void                    sci_spi_txi_isr             (void);

void                    sci_spi_rxi_isr             (void);

void                    sci_spi_tei_isr             (void);

void                    sci_spi_eri_isr             (void);

static ssp_err_t        r_sci_spi_set_valid_interrupts_priority   (sci_spi_instance_ctrl_t * p_ctrl,
                                                                   spi_cfg_t const * const p_cfg);
static void             r_sci_spi_bit_rate_modulation             (R_SCI0_Type * p_sci_reg,
                                                                   spi_cfg_t const * const p_cfg);
static uint8_t          r_sci_spi_set_register                    (spi_cfg_t const * const p_cfg);
static void             r_sci_spi_set_msb_lsb                     (R_SCI0_Type * p_sci_reg,
                                                                   spi_cfg_t const * const p_cfg);
static void             r_sci_spi_set_tx_rx_interrupt             (R_SCI0_Type * p_sci_reg,
                                                                   sci_spi_instance_ctrl_t * const p_ctrl,
                                                                   spi_operation_t tx_rx_mode );
static ssp_err_t        r_sci_spi_open_receive_interface          (spi_cfg_t const * const p_cfg,
                                                                   ssp_feature_t * p_ssp_feature);
static ssp_err_t        r_sci_spi_open_transmit_interface         (spi_cfg_t const * const p_cfg,
                                                                   ssp_feature_t * p_ssp_feature);

static ssp_err_t r_sci_spi_tx_transfer_reset(sci_spi_instance_ctrl_t * const p_ctrl,
                                           spi_operation_t                 tx_rx_mode,
                                           uint32_t                *       p_data_reg,
                                           uint32_t                  const length );

static ssp_err_t r_sci_spi_transfer_reset(sci_spi_instance_ctrl_t * const p_ctrl,
                                        spi_operation_t                 tx_rx_mode,
                                        uint32_t                  const length );

/* Read-only variable for writing blank data when doing Read operations using DTC. */
static const uint32_t g_dummy = (0xFFFFFFFFU);

/*******************************************************************************************************************
 * Functions.
 ******************************************************************************************************************/

/*****************************************************************************************************************//**
 * @addtogroup SCI_SPI
 * @{
 ********************************************************************************************************************/

/*****************************************************************************************************************//**
 * @brief   Initialize a channel for SPI communication mode.
 * Implements spi_api_t::open.
 *          This function performs the following tasks:
 *          Performs parameter checking and processes error conditions.
 *          Applies power to the SPI channel.
 *          Disables interrupts.
 *          Initializes the associated registers with default value and the user-configurable options.
 *          Provides the channel handle for use with other API functions.
 *          Updates user-configurable file if necessary.
 *
 * @retval     SSP_SUCCESS                 Channel initialized successfully.
 * @retval     SSP_ERR_ASSERTION           One of the following invalid parameter passed.
 *                                         - Pointer p_api_ctrl is NULL
 *                                         - Pointer p_cfg is NULL
 * @retval     SSP_ERR_IN_USE              Channel currently in operation; Close channel first.
 * @retval     SSP_ERR_HW_LOCKED           The lock could not be acquired. The channel is busy.
 *
 * See @ref Common_Error_Codes or functions called by this function
 *                                         for other possible return codes. This function calls:
 *                                        * fmi_api_t::productFeatureGet
 * 
 * @note  This function is reentrant.
 * @note  The bit-rate argument in p_cfg ranges from 2500 to 7.5m for Simple SPI at PCLK=120 MHz. For RSPI, BRDV is
 *        fixed at 0 to get the maximum bit rate. The range is 10.0 mbps to 30.0 mbps at PCLK=120.0 MHz.
 ********************************************************************************************************************/
ssp_err_t R_SCI_SPI_Open (spi_ctrl_t                       * p_api_ctrl,
                          spi_cfg_t                  const * const p_cfg)
{
    sci_spi_instance_ctrl_t * p_ctrl  = (sci_spi_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t        err = SSP_SUCCESS;
    uint32_t                  channel = 0;
    uint8_t                   temp;

/* Perform parameter checking. */
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_cfg);
    SSP_ASSERT(NULL != p_ctrl);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    ssp_feature_t ssp_feature = {{(ssp_ip_t) 0U}};
    ssp_feature.channel = p_cfg->channel;
    ssp_feature.unit = 0U;
    ssp_feature.id = SSP_IP_SCI;
    fmi_feature_info_t info = {0U};
    err = g_fmi_on_fmi.productFeatureGet(&ssp_feature, &info);
    SCI_SPI_ERROR_RETURN(SSP_SUCCESS == err, err);

    /** Attempt to acquire lock for this SCI SPI channel. Prevents re-entrancy conflict. */
    err = R_BSP_HardwareLock(&ssp_feature);
    SCI_SPI_ERROR_RETURN((SSP_SUCCESS == err), SSP_ERR_HW_LOCKED);

    memset(p_ctrl, 0, sizeof(sci_spi_instance_ctrl_t));
    p_ctrl->p_reg = info.ptr;
    R_SCI0_Type * p_sci_reg = (R_SCI0_Type *) p_ctrl->p_reg;

    /** set valid interrupts with user provided priority. */
    err = r_sci_spi_set_valid_interrupts_priority(p_ctrl, p_cfg);
    if (SSP_SUCCESS != err)
    {
        R_BSP_HardwareUnlock(&ssp_feature);
        return (err);
    }

    channel = p_cfg->channel;

    /** Turn on power. */
    R_BSP_ModuleStart(&ssp_feature);
    /* Sets registers to reset values. */
    HW_SCI_RegisterReset(p_sci_reg);

    /* Disable interrupts. */
    HW_SCI_RxIrqDisable(p_sci_reg);
    HW_SCI_TxIrqDisable(p_sci_reg);
    HW_SCI_TeIrqDisable(p_sci_reg);

    R_BSP_IrqStatusClear(p_ctrl->txi_irq);
    R_BSP_IrqStatusClear(p_ctrl->rxi_irq);
    R_BSP_IrqStatusClear(p_ctrl->eri_irq);
    R_BSP_IrqStatusClear(p_ctrl->tei_irq);

    NVIC_ClearPendingIRQ(p_ctrl->txi_irq);
    NVIC_ClearPendingIRQ(p_ctrl->rxi_irq);
    NVIC_ClearPendingIRQ(p_ctrl->eri_irq);
    NVIC_ClearPendingIRQ(p_ctrl->tei_irq);

    NVIC_EnableIRQ(p_ctrl->txi_irq);
    NVIC_EnableIRQ(p_ctrl->rxi_irq);
    NVIC_EnableIRQ(p_ctrl->eri_irq);
    NVIC_EnableIRQ(p_ctrl->tei_irq);

    /** Don't use FIFO mode -- set FCRL_b.FM = 0. */
    HW_SCI_FifoDisable(p_sci_reg);

    /** Select SPI mode - set SCMR.SMIF=0, SIMR1.IICM=0, SMR.CM=1, SPMR.SSE=1. */
    HW_SCI_SPIModeSelect(p_sci_reg);

    /* Enable or disable bitrate modulation. */
    r_sci_spi_bit_rate_modulation (p_sci_reg, p_cfg);

    /** Set baud rate in SCI channel for the SPI channel. */
    err= r_sci_spi_baud_set(p_sci_reg, p_cfg->bitrate);
    if (SSP_SUCCESS != err)
    {
        /* If setting failed, unlock channel. */
        R_BSP_HardwareUnlock(&ssp_feature);
        /* Could not calculate settings for the requested baud rate. */
        SSP_ASSERT(false);
    }

    /** Open the SCI SPI transfer interface if available. */
    err = r_sci_spi_transfer_open(p_cfg, &ssp_feature);
    if (SSP_SUCCESS != err)
    {
        R_BSP_HardwareUnlock(&ssp_feature);
        SSP_ERROR_LOG((err), (&g_module_name[0]), (&g_sci_spi_version));
        return (err);
    }

    /* Sets the CKE bit in the SCR register. */
    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        /* Select external clock for SLAVE SPI Mode */
        HW_SCI_BaudRateGenExternalClkSelect(p_sci_reg);
    }
    else
    {
        /* Select internal clock for MASTER SPI Mode */
        HW_SCI_BaudRateGenInternalClkSelect(p_sci_reg);
    }

    /* Sets registers based on user configuration. */
    temp = r_sci_spi_set_register (p_cfg);

    /* Set the hardware LLD with the temp value. */
    HW_SCI_SPIModeSet(p_sci_reg, temp);

    /* Set MSB/LSB based on user configuration. */
    r_sci_spi_set_msb_lsb   (p_sci_reg, p_cfg);

    /** Peripheral Initialized. */
    /** Set control block for SCI channel to SPI mode operation. */
    p_ctrl->p_callback     = p_cfg->p_callback;
    p_ctrl->p_context      = p_cfg->p_context;
    p_ctrl->channel        = (uint8_t)channel;

    /* Update info to the handle. */
    p_ctrl->p_transfer_rx  = p_cfg->p_transfer_rx;
    p_ctrl->p_transfer_tx  = p_cfg->p_transfer_tx;
    p_ctrl->tx_dtc_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_ctrl->channel_opened = SCI_SPI_OPEN;

    return err;
}

/* End of function R_SCI_SPI_Open(). */

/*****************************************************************************************************************//**
 * @brief   Receive data from an SPI device.
 * Implements spi_api_t::read.
 *          The function performs the following tasks:
 *          - Performs parameter checking and processes error conditions.
 *          - Disable Interrupts.
 *          - Set-up data bit width per user request.
 *          - Enable transmitter.
 *          - Enable receiver.
 *          - Enable interrupts.
 *          - Start data transmission with dummy data via transmit buffer empty interrupt.
 *          - Copy data from source buffer to the SPI data register for transmission.
 *          - Receive data from receive buffer full interrupt occurs and copy data to the buffer of destination.
 *          - Complete data reception via receive buffer full interrupt and transmitting dummy data.
 *          - Disable transmitter.
 *          - Disable receiver.
 *          - Disable interrupts.
 *
 * @retval     SSP_SUCCESS              Read operation successfully completed.
 * @retval     SSP_ERR_ASSERTION        One of the following invalid parameters passed
 *                                      - Pointer p_api_ctrl is NULL
 *                                      - Bit width is not 8 bits
 *                                      - Length is equal to 0
 *                                      - Pointer to destination is NULL
 * @retval     SSP_ERR_HW_LOCKED        The lock could not be acquired. The channel is busy.
 * @retval     SSP_ERR_NOT_OPEN         The channel has not been opened. Open the channel first.
 * 
 * See @ref Common_Error_Codes or functions called by this function
 *                                      for other possible return codes. This function calls:
 *                                      * transfer_api_t::reset
 * @note  This function is reentrant.
 ********************************************************************************************************************/
ssp_err_t  R_SCI_SPI_Read (spi_ctrl_t          * const p_api_ctrl,
                            void const                  * p_dest,
                            uint32_t const              length,
                            spi_bit_width_t const       bit_width)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t                 result;

/* Perform parameter checking. */
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    /* Check bit_width parameter, in simple SPI, only 8 bits operation is allowed. */
    SSP_ASSERT(SPI_BIT_WIDTH_8_BITS == bit_width);
    /* Check the data length, should not be 0. */
    SSP_ASSERT(0 != length);
    /* Check the destination, should not be NULL. */
    SSP_ASSERT(NULL != p_dest);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    /** Configure module to receive data from a SPI device. */
    result = r_sci_spi_write_read_common(p_ctrl, NULL, p_dest, length, bit_width, SPI_OPERATION_DO_RX);

    return result;
}

/* End of function R_SCI_SPI_Read(). */

/*****************************************************************************************************************//**
 * @brief   Transmit data to a SPI  device.
 * Implements spi_api_t::write.
 *          - The function performs the following tasks:
 *          - Performs parameter checking and processes error conditions.
 *          - Disable Interrupts.
 *          - Setup data bit width per user request.
 *          - Enable transmitter.
 *          - Enable receiver.
 *          - Enable interrupts.
 *          - Start data transmission with data via transmit buffer empty interrupt.
 *          - Copy data from source buffer to the SPI data register for transmission.
 *          - Receive data from receive buffer full interrupt occurs and do nothing with the received data.
 *          - Complete data transmission via receive buffer full interrupt.
 *          - Disable transmitter.
 *          - Disable receiver.
 *          - Disable interrupts.
 *
 * @retval     SSP_SUCCESS               Write operation successfully completed.
 * @retval     SSP_ERR_ASSERTION         One of the following invalid parameters passed
 *                                       - Pointer p_api_ctrl is NULL
 *                                       - Pointer to source is NULL
 *                                       - Length is equal to 0
 *                                       - Bit width is not equal to 8 bits
 * @retval     SSP_ERR_HW_LOCKED         The lock could not be acquired. The channel is busy.
 * @retval     SSP_ERR_NOT_OPEN          The channel has not been opened. Open the channel first.
 * 
 * See @ref Common_Error_Codes or functions called by this function
 *                                       for other possible return codes. This function calls:
 *                                       * transfer_api_t::reset
 * @note  This function is reentrant.
 ********************************************************************************************************************/
ssp_err_t   R_SCI_SPI_Write (spi_ctrl_t          * const p_api_ctrl,
                              void const                  * p_src,
                              uint32_t const              length,
                              spi_bit_width_t const       bit_width)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t                 result;

/* Perform parameter checking. */
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    /* Check bit_width parameter, in simple SPI, only 8 bits operation is allowed. */
    SSP_ASSERT(SPI_BIT_WIDTH_8_BITS == bit_width);
    /* Check the data length, should not be 0. */
    SSP_ASSERT(0 != length);
    /* Check the source, should not be NULL. */
    SSP_ASSERT(NULL != p_src);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    /** Configure module to transmit data to a SPI device. */
    result = r_sci_spi_write_read_common(p_ctrl, p_src, NULL, length, bit_width, SPI_OPERATION_DO_TX);

    return result;
}

/* End of function R_SCI_SPI_Write(). */

/*****************************************************************************************************************//**
 * @brief   Simultaneously transmit data to SPI device while receiving data from SPI device
 *          (full duplex).
 * Implements spi_api_t::writeRead.
 *          The function performs the following tasks:
 *          - Performs parameter checking and processes error conditions.
 *          - Disable Interrupts.
 *          - Setup data bit width per user request.
 *          - Enable transmitter.
 *          - Enable receiver.
 *          - Enable interrupts.
 *          - Start data transmission using transmit buffer empty interrupt.
 *          - Copy data from source buffer to the SPI data register for transmission.
 *          - Receive data from receive buffer full interrupt occurs and copy data to the buffer of destination.
 *          - Complete data transmission and reception via receive buffer full interrupt.
 *          - Disable transmitter.
 *          - Disable receiver.
 *          - Disable interrupts.
 *
 * @retval     SSP_SUCCESS            Write operation successfully completed.
 * @retval     SSP_ERR_ASSERTION      One of the following invalid parameters passed
 *                                       - Pointer p_api_ctrl is NULL
 *                                       - Pointer to source is NULL
 *                                       - Pointer to destination is NULL
 *                                       - Length is equal to 0
 *                                       - Bit width is not equal to 8 bits
 * @retval     SSP_ERR_HW_LOCKED      The lock could not be acquired. The channel is busy.
 * @retval     SSP_ERR_NOT_OPEN       The channel has not been opened. Open the channel first.
 * 
 * See @ref Common_Error_Codes or functions called by this function
 *                                    for other possible return codes. This function calls:
 *                                    * transfer_api_t::reset
 * @note  This function is reentrant.
 ********************************************************************************************************************/
ssp_err_t  R_SCI_SPI_WriteRead (spi_ctrl_t     * const p_api_ctrl,
                                 void const             * p_src,
                                 void const             * p_dest,
                                 uint32_t const         length,
                                 spi_bit_width_t const  bit_width)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t                 result;

/* Perform parameter checking. */
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    /* Check bit_width parameter, in simple SPI, only 8 bits operation is allowed. */
    SSP_ASSERT(SPI_BIT_WIDTH_8_BITS == bit_width);
    /* Check the data length, should not be 0. */
    SSP_ASSERT(0 != length);
    /* Check the source, should not be NULL. */
    SSP_ASSERT(NULL != p_src);
    /* Check the destination, should not be NULL. */
    SSP_ASSERT(NULL != p_dest);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    /** Configure module for full duplex operation. */
    result = r_sci_spi_write_read_common(p_ctrl, p_src, p_dest, length, bit_width, SPI_OPERATION_DO_TX_RX);

    return result;
}

/* End of function R_SCI_SPI_WriteRead(). */


/*****************************************************************************************************************//**
 * @brief   Initiates writ or read process. Common routine used by RSPI API write or read functions.
 * @param[in]  p_ctrl                      Pointer to the control block.
 * @param[in]  p_src                       Pointer to data buffer which need to be sent.
 * @param[out] p_dest                      Pointer to buffer where received data will be stored.
 * @param[in]  length                      Number of data transactions to be performed.
 * @param[in]  bit_width                   Size of data for each transaction.
 * @param[in]  tx_rx_mode                  Mode of the data transaction.
 *
 * @retval     SSP_SUCCESS                 Operation successfully completed.
 * @retval     SSP_ERR_HW_LOCKED           The lock could not be acquired. The channel is busy.
 * @retval     SSP_ERR_NOT_OPEN            The channel has not been opened. Open the channel first.
 * 
 * See @ref Common_Error_Codes or functions called by this function
 *                                         for other possible return codes. This function calls:
 *                                         * transfer_api_t::reset
 * @note  This function is reentrant.
 ********************************************************************************************************************/
static ssp_err_t  r_sci_spi_write_read_common (sci_spi_instance_ctrl_t        * const p_ctrl,
                                                void const                * p_src,
                                                void const                * p_dest,
                                                uint32_t const            length,
                                                spi_bit_width_t const     bit_width,
                                                spi_operation_t           tx_rx_mode)
{
    ssp_err_t result;

    /** Check that the channel is open. If not return error. */
    SCI_SPI_ERROR_RETURN(SCI_SPI_OPEN == p_ctrl->channel_opened, SSP_ERR_NOT_OPEN);

    /** Attempt to acquire lock for this transfer operation. Prevents re-entrance conflict. */
    SCI_SPI_ERROR_RETURN(SSP_SUCCESS == R_BSP_SoftwareLock(&p_ctrl->resource_lock_tx_rx), SSP_ERR_HW_LOCKED);

    /* Disable interrupts. */
    R_SCI0_Type * p_sci_reg = (R_SCI0_Type *) p_ctrl->p_reg;
    HW_SCI_RxIrqDisable(p_sci_reg);
    HW_SCI_TxIrqDisable(p_sci_reg);
    HW_SCI_TeIrqDisable(p_sci_reg);

    /** Setup the control block. */
    p_ctrl->xfr_length         = length;
    p_ctrl->tx_count           = 0U;
    p_ctrl->rx_count           = 0U;
    p_ctrl->bytes_per_transfer = bit_width;
    p_ctrl->p_src              = (void *) p_src;
    p_ctrl->p_dest             = (void *) p_dest;
    p_ctrl->transfer_mode      = tx_rx_mode;

    result = SSP_SUCCESS;

    p_ctrl->do_tx = (bool)((uint8_t) tx_rx_mode & (uint8_t) SPI_OPERATION_DO_TX);

    /* Clear error sources: mode fault error bit should be cleared in the SPMR register. */
    HW_SCI_SPIModeFaultClear(p_sci_reg);

    /* Clear interrupt status for Transmit(TXI), Receive(RXI), Error(ERI). */
    R_BSP_IrqStatusClear(p_ctrl->tei_irq);
    R_BSP_IrqStatusClear(p_ctrl->txi_irq);
    R_BSP_IrqStatusClear(p_ctrl->rxi_irq);
    R_BSP_IrqStatusClear(p_ctrl->eri_irq);

    /** Reset the write transfer with source and destination pointers. */
    result = r_sci_spi_transfer_reset(p_ctrl, tx_rx_mode, length);
    if (SSP_SUCCESS != result)
    {
        R_BSP_SoftwareUnlock(&p_ctrl->resource_lock_tx_rx);
        return result;
    }

    /** Enable transmit and receive interrupts. */
    r_sci_spi_set_tx_rx_interrupt(p_sci_reg, p_ctrl, tx_rx_mode );

    return result;
}

/* End of function r_sci_spi_write_read_common(). */

/*****************************************************************************************************************//**
 * @brief   Handle the closing of a channel by the following task.
 *          Implements spi_api_t::close
 *          Power off the channel.
 *          Disables all the associated interrupts.
 *          Update channel status.
 *
 * @retval     SSP_SUCCESS              Channel successfully closed.
 * @retval     SSP_ERR_ASSERTION        The parameter p_api_ctrl is NULL.
 * @retval     SSP_ERR_NOT_OPEN         The channel has not been opened. Open the channel first.
 * @note  This function is reentrant.
 ********************************************************************************************************************/
ssp_err_t  R_SCI_SPI_Close (spi_ctrl_t * const p_api_ctrl)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;

/* Perform parameter checking. */
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    /** Check to see if the channel is currently initialized. */
    if ((SCI_SPI_OPEN) != (p_ctrl->channel_opened))
    {
        /* This channel is not open so need not be closed. */
        SSP_ERROR_LOG((SSP_ERR_NOT_OPEN), (&g_module_name[0]), (&g_sci_spi_version));
        return SSP_ERR_NOT_OPEN;
    }

    p_ctrl->channel_opened = 0U;

    /* Disable interrupts. */
    R_SCI0_Type * p_sci_reg = (R_SCI0_Type *) p_ctrl->p_reg;
    HW_SCI_RxIrqDisable(p_sci_reg);
    HW_SCI_TxIrqDisable(p_sci_reg);
    HW_SCI_TeIrqDisable(p_sci_reg);

    NVIC_DisableIRQ(p_ctrl->txi_irq);
    NVIC_DisableIRQ(p_ctrl->rxi_irq);
    NVIC_DisableIRQ(p_ctrl->eri_irq);
    NVIC_DisableIRQ(p_ctrl->tei_irq);

    /** Turn off power. */
    ssp_feature_t ssp_feature = {{(ssp_ip_t) 0U}};
    ssp_feature.channel = p_ctrl->channel;
    ssp_feature.unit = 0U;
    ssp_feature.id = SSP_IP_SCI;
    R_BSP_ModuleStop(&ssp_feature);

    /** Close transfer block. */
    if (NULL != p_ctrl->p_transfer_rx)
    {
        p_ctrl->p_transfer_rx->p_api->close(p_ctrl->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_transfer_tx)
    {
        p_ctrl->p_transfer_tx->p_api->close(p_ctrl->p_transfer_tx->p_ctrl);
    }

    /* Release the software lock. */
    R_BSP_SoftwareUnlock(&p_ctrl->resource_lock_tx_rx);

    /** Release lock for this channel. */
    R_BSP_HardwareUnlock(&ssp_feature);

    return SSP_SUCCESS;
}

/* End of function R_SCI_SPI_Close(). */

/***************************************************************************************************************//**
 * @brief   Get the version information of the underlying driver.
 * Implements spi_api_t::versionGet.
 *
 * @retval     SSP_SUCCESS         Successful version get.
 * @retval     SSP_ERR_ASSERTION   The parameter p_version is NULL.
 * @note     This function is reentrant.
 ******************************************************************************************************************/
ssp_err_t R_SCI_SPI_VersionGet (ssp_version_t * p_version)
{
/* Perform parameter checking. */
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_version);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    p_version->version_id = g_sci_spi_version.version_id;

    return SSP_SUCCESS;
}

/* End of function R_SCI_SPI_VersionGet(). */

/***************************************************************************************************************//**
 * @} (end addtogroup SCI_SPI)
 ******************************************************************************************************************/

/*****************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info.
 * @param[in]     p_feature       SSP feature.
 * @param[in]     signal          SSP signal ID.
 * @param[in]     ipl             Interrupt priority level.
 * @param[in]     p_ctrl          Pointer to driver control block.
 * @param[out]    p_irq           Pointer to IRQ for this signal, set here.
 *
 * @retval        SSP_SUCCESS     Interrupt enabled.
 * 
 * See @ref Common_Error_Codes or functions called by this function
 *                                for other possible return codes. This function calls:
 *                                * fmi_api_t::eventInfoGet
 ********************************************************************************************************************/
static inline ssp_err_t r_sci_irq_cfg(ssp_feature_t * p_feature,
                                      ssp_signal_t signal,
                                      uint8_t ipl,
                                      void * p_ctrl,
                                      IRQn_Type * p_irq)
{
    fmi_event_info_t event_info = {(IRQn_Type) 0U};
    ssp_vector_info_t * p_vector_info;
    ssp_err_t err = g_fmi_on_fmi.eventInfoGet(p_feature, signal, &event_info);
    *p_irq = event_info.irq;

    if (SSP_SUCCESS == err)
    {
        NVIC_SetPriority(*p_irq, ipl);
        R_SSP_VectorInfoGet(*p_irq, &p_vector_info);
        *(p_vector_info->pp_ctrl) = p_ctrl;
    }

    return err;
}

/*****************************************************************************************************************//**
 * @brief   This function is the ISR handler for R_SCI_SPI Transmit Buffer Empty interrupts.
 *
 *
 *
 ********************************************************************************************************************/
void sci_spi_txi_isr (void)
{
    /* Save context if RTOS is used. */
    SF_CONTEXT_SAVE;

    ssp_vector_info_t * p_vector_info = NULL;
    IRQn_Type irq = R_SSP_CurrentIrqGet();
    R_BSP_IrqStatusClear( irq );
    R_SSP_VectorInfoGet( irq, &p_vector_info );
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) *(p_vector_info->pp_ctrl);    

    if ((NULL == p_ctrl->p_transfer_rx) && (NULL == p_ctrl->p_transfer_tx))
    {
        /* If master mode then disable further TX interrupts on first transmit. */
        /* If slave mode then we do two transmits to fill the double buffer, then disable TX interrupts. */
        /* The receive interrupt will handle any remaining data. */
        if (((HW_SCI_SPIMasterCheck(p_ctrl->p_reg)) || (p_ctrl->tx_count > 0U))
            && (SPI_OPERATION_DO_TX != p_ctrl->transfer_mode))
        {
            /* Disable Tx interrupts. */
            HW_SCI_TxIrqDisable(p_ctrl->p_reg);
        }

        /* Transmit data. */
        if (p_ctrl->tx_count < p_ctrl->xfr_length)   /* Don't write transmit buffer more than length. */
        {
            if (p_ctrl->do_tx)
            {
                /* Transmit the data. TX data register accessed in byte. */
                HW_SCI_Write(p_ctrl->p_reg, ((uint8_t *) p_ctrl->p_src)[p_ctrl->tx_count]);
            }
            else /* Must be RX only mode, so transmit dummy data for clocking. */
            {
                /* TX data register accessed in bytes. */
                HW_SCI_Write(p_ctrl->p_reg, SCI_SPI_DUMMY_TXDATA);
            }
            p_ctrl->tx_count++;
        }
    }
    else
    {
        /* Set the transmit count to the transmit length. */
        p_ctrl->tx_count = p_ctrl->xfr_length;
    }

    /* If all data has been transmitted */
    if (p_ctrl->tx_count == p_ctrl->xfr_length)
    {
        /* Disable the transmit buffer empty interrupt. */
        HW_SCI_TxIrqDisable(p_ctrl->p_reg);

        /*Clear IR bit in an ICU.*/
        R_BSP_IrqStatusClear(p_ctrl->txi_irq);

        /*Clear Pending TXI interrupt request in NVIC if any.*/
        NVIC_ClearPendingIRQ(p_ctrl->txi_irq);

        /* If the current option is transmit only enable the transmit end interrupt. */
        if (SPI_OPERATION_DO_TX == p_ctrl->transfer_mode)
        {
            HW_SCI_TeIrqEnable(p_ctrl->p_reg);
        }
    }

    /* Restore context if RTOS is used. */
    SF_CONTEXT_RESTORE;
}

/*****************************************************************************************************************//**
 * @brief   This function is the ISR handler for R_SCI_SPI Receive Buffer Full interrupts.
 *
 *
 *
 ********************************************************************************************************************/
void sci_spi_rxi_isr (void)
{
    /* Save context if RTOS is used. */
    SF_CONTEXT_SAVE;

    ssp_vector_info_t * p_vector_info = NULL;
    IRQn_Type irq = R_SSP_CurrentIrqGet();
    R_BSP_IrqStatusClear( irq );
    R_SSP_VectorInfoGet( irq, &p_vector_info );
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) *(p_vector_info->pp_ctrl);

    if ((NULL == p_ctrl->p_transfer_rx) && (NULL == p_ctrl->p_transfer_tx))
    {
        ((uint8_t *)p_ctrl->p_dest)[p_ctrl->rx_count] = HW_SCI_Read(p_ctrl->p_reg);
        p_ctrl->rx_count++;

        if (p_ctrl->tx_count < p_ctrl->xfr_length)   /* Don't write transmit buffer more than length. */
        {
            if (p_ctrl->do_tx)
            {
                /* Transmit the data. TX data register accessed in byte. */
                HW_SCI_Write(p_ctrl->p_reg, ((uint8_t *) p_ctrl->p_src)[p_ctrl->tx_count]);
            }
            else /* Must be RX only mode, so transmit dummy data for clocking. */
            {
                /* TX data register accessed in bytes. */
                HW_SCI_Write(p_ctrl->p_reg, SCI_SPI_DUMMY_TXDATA);
            }
            p_ctrl->tx_count++;
        }
    }
    else
    {
        p_ctrl->rx_count = p_ctrl->xfr_length;
    }

    if (p_ctrl->rx_count == p_ctrl->xfr_length)
    {
        /* Last data was received. Disable interrupts and disable receiver. */

        /* Disable interrupts in SCI. */
        HW_SCI_RxIrqDisable(p_ctrl->p_reg);
        HW_SCI_TxIrqDisable(p_ctrl->p_reg);

        /* Disables receiver and transmitter. */
        HW_SCI_TransmitterReceiverDisable(p_ctrl->p_reg);

        if (NULL != p_ctrl->p_callback)
        {
            /* Transfer complete. Call the user callback function passing pointer to the result structure. */
            spi_callback_args_t sci_spi_cb_data;
            sci_spi_cb_data.channel = p_ctrl->channel;
            sci_spi_cb_data.event = SPI_EVENT_TRANSFER_COMPLETE;
            sci_spi_cb_data.p_context = p_ctrl->p_context;
            p_ctrl->p_callback(&sci_spi_cb_data);
        }

        /* Transfer is done, release the lock for this operation. */
        R_BSP_SoftwareUnlock(&p_ctrl->resource_lock_tx_rx);
    }

    /* Restore context if RTOS is used. */
    SF_CONTEXT_RESTORE;
}

/*****************************************************************************************************************//**
 * @brief   This function is the ISR handler for R_SCI_SPI Transmit End interrupts.
 *
 *
 *
 ********************************************************************************************************************/
void sci_spi_tei_isr (void)
{
    /* Save context if RTOS is used. */
    SF_CONTEXT_SAVE;

    ssp_vector_info_t * p_vector_info = NULL;
    IRQn_Type irq = R_SSP_CurrentIrqGet();
    R_SSP_VectorInfoGet( irq, &p_vector_info );
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) *(p_vector_info->pp_ctrl);

    /* Last data was transferred. Disable interrupts and disable receiver. */

    /* Disable interrupts in SCI. */
    HW_SCI_RxIrqDisable(p_ctrl->p_reg);
    HW_SCI_TxIrqDisable(p_ctrl->p_reg);
    HW_SCI_TeIrqDisable(p_ctrl->p_reg);

    /* Disables receiver and transmitter. */
    HW_SCI_TransmitterReceiverDisable(p_ctrl->p_reg);

    if (NULL != p_ctrl->p_callback)
    {
        /* Transfer complete. Call the user callback function passing pointer to the result structure. */
        spi_callback_args_t sci_spi_cb_data;
        sci_spi_cb_data.channel = p_ctrl->channel;
        sci_spi_cb_data.event = SPI_EVENT_TRANSFER_COMPLETE;
        sci_spi_cb_data.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&sci_spi_cb_data);
    }

    /* Transfer is done, release the lock for this operation. */
    R_BSP_SoftwareUnlock(&p_ctrl->resource_lock_tx_rx);

    R_BSP_IrqStatusClear( irq );
    /* Restore context if RTOS is used. */
    SF_CONTEXT_RESTORE;
}

/*****************************************************************************************************************//**
 * @brief   This function is common ISR handler for  R_SCI_SPI SPEI-error interrupts.
 *
 *
 *
 ********************************************************************************************************************/
void sci_spi_eri_isr (void)
{
    /* Save context if RTOS is used. */
    SF_CONTEXT_SAVE;

    ssp_vector_info_t * p_vector_info = NULL;
    R_SSP_VectorInfoGet(R_SSP_CurrentIrqGet(), &p_vector_info);
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) *(p_vector_info->pp_ctrl);
    R_SCI0_Type * p_sci_reg = (R_SCI0_Type *) p_ctrl->p_reg;
    uint8_t channel = p_ctrl->channel;

    spi_callback_args_t sci_spi_cb_data;

    /* Get the error status and return back through the caller function. */
    if (NULL != p_ctrl->p_callback)
    {
        sci_spi_cb_data.channel = channel;

        if (HW_SCI_OverRunErrorCheck(p_sci_reg))
        {
            sci_spi_cb_data.event = SPI_EVENT_ERR_OVERRUN;
        }
        else
        {
            sci_spi_cb_data.event =  SPI_EVENT_TRANSFER_ABORTED;
        }
        sci_spi_cb_data.p_context = p_ctrl->p_context;
        p_ctrl->p_callback((spi_callback_args_t *) &(sci_spi_cb_data));
    }

    /* Error condition occurs, release the software lock for this operation. */
    R_BSP_SoftwareUnlock(&p_ctrl->resource_lock_tx_rx);

    /* Clear error condition. */
    HW_SCI_ErrorConditionClear (p_sci_reg);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting. */
    R_BSP_IrqStatusClear(R_SSP_CurrentIrqGet());

    volatile uint32_t dummy;

    /* Give time for value to be updated. */
    dummy = R_ICU->IELSRn[(uint32_t)R_SSP_CurrentIrqGet()];
    SSP_PARAMETER_NOT_USED(dummy);

    /* Restore context if RTOS is used. */
    SF_CONTEXT_RESTORE;
}

/*****************************************************************************************************************//**
 * @brief   This function changes baud rate. It evaluates and determines the best possible settings for the baud rate
 * registers.
 * @param[in,out]    p_sci_reg                    Pointer to SCI SPI register.
 * @param[in]        bitrate                      bitrate[bps] e.g. 250,000; 500,00; 2,500,000(max), etc.
 *
 * @retval           SSP_SUCCESS                  Baud rate is set successfully.
 * @retval           SSP_ERR_ASSERTION            Baud rate is '0' or cannot set properly.
 * @note    The application must pause for 1 bit time after the BRR register is loaded
 *          before transmitting/receiving to allow time for the clock to settle.
 ******************************************************************************************************************/
static ssp_err_t r_sci_spi_baud_set (R_SCI0_Type * p_sci_reg,
                                      uint32_t      bitrate)
{
    uint32_t         i             = 0;
    uint32_t         brr           = SCI_SPI_BRR_MAX;
    uint32_t         temp_brr      = SCI_SPI_BRR_MIN;
    baud_setting_t   * p_baudinfo;
    volatile uint8_t clock_divisor = 0;
    ssp_err_t        result;
    uint32_t         clock_mhz = 0U;

    bsp_feature_sci_t sci_feature = {0U};
    R_BSP_FeatureSciGet(&sci_feature);
    result = g_cgc_on_cgc.systemClockFreqGet((cgc_system_clocks_t) sci_feature.clock, &clock_mhz);

    if (SSP_SUCCESS != result)
    {
        SSP_ERROR_LOG((SSP_ERR_ASSERTION), (&g_module_name[0]), (&g_sci_spi_version));
        return SSP_ERR_ASSERTION;
    }

    if (0 == bitrate)
    {
        SSP_ERROR_LOG((SSP_ERR_ASSERTION), (&g_module_name[0]), (&g_sci_spi_version));
        return SSP_ERR_ASSERTION;
    }

    p_baudinfo = (baud_setting_t *) sync_baud;

    /* FIND BEST_BRR_VALUE.
     *  In table sync_baud", divisor value is associated with
     *  the divisor coefficient and the n values (clock divisor) , so once best divisor value is found,
     *  baud rate related register setting values are decided.
     *  The formula to calculate BRR is as follows and it must be 255 or less.
     *  BRR = (PCLKA/(div_coefficient * baud)) - 1. */
    result = SSP_ERR_ASSERTION;
    for (i = 0U; i < SCI_SPI_NUM_DIVISORS_SYNC; i++)
    {
        temp_brr = clock_mhz / ((uint32_t)p_baudinfo[i].div_coefficient * bitrate);
        if ((SCI_SPI_BRR_MIN < temp_brr) && (temp_brr < (SCI_SPI_BRR_MAX + 1)))
        {
            brr           = temp_brr - 1U;
            clock_divisor = (uint8_t)i;
            /* Now set the bit rate register in the hardware. */
            HW_SCI_BitRateBRRSet(p_sci_reg, (uint8_t)brr, clock_divisor);
            result = SSP_SUCCESS;
            break;
        }
    }

    /* Check Bitrate Modulation function is enabled or not. */
    /* If it is enabled,set the MBBR register to correct the bit rate generated by the on-chip baud rate generator */
    if (HW_SCI_BitRateModulationCheck(p_sci_reg))
    {
        uint32_t temp_mbbr = 0;
        volatile uint32_t mddr = 0;

        /* Calculate the MBBR (M) value,
         * The formula to calculate MBBR (from the M and N relationship given in the HM) is as follows and it
         * must between 128 and 256.
         * MBBR = ((div_coefficient * baud * 256) * (BRR + 1)) / PCLKA. */
        temp_mbbr = ((uint32_t) p_baudinfo[clock_divisor].div_coefficient * bitrate * 256);
        mddr = (temp_mbbr * (brr+1)) / clock_mhz;

        /* Set MDDR register only for values between 128 and 255, do not set otherwise. */
        if ((mddr >= 128U) && (mddr <= 255U))
        {
            HW_SCI_UartBitRateModulationSet(p_sci_reg, (uint8_t)mddr);
        }
    }

    return result;
}
/* End of function r_sci_spi_baud_set(). */

/*****************************************************************************************************************//**
 * @brief Configures SCI SPI related transfer drivers (if enabled).
 * @param[in]     p_cfg                     Pointer to SCI SPI specific configuration structure.
 * @param[in]     p_ssp_feature             SSP feature.
 *
 * @retval        SSP_SUCCESS               Operation successfully completed.
 * @retval        SSP_ERR_ASSERTION         One of the following invalid parameters passed
 *                                          - Pointer p_cfg is NULL
 *                                          - Interrupt is not enabled
 * @retval        SSP_ERR_INVALID_ARGUMENT  DTC is used for data transmission but not used for data reception or
 *                                          vice versa.
 ********************************************************************************************************************/
static ssp_err_t    r_sci_spi_transfer_open     (spi_cfg_t const * const p_cfg, ssp_feature_t * p_ssp_feature)
{
#if (SCI_SPI_CFG_PARAM_CHECKING_ENABLE)
        SCI_SPI_ERROR_RETURN((p_cfg->p_transfer_rx==NULL)==(p_cfg->p_transfer_tx==NULL), SSP_ERR_INVALID_ARGUMENT);
#endif
    ssp_err_t result = SSP_SUCCESS;

    if (NULL != p_cfg->p_transfer_rx)
    {
        /* Open receive transfer module. */
        result =  r_sci_spi_open_receive_interface (p_cfg, p_ssp_feature);
        if (SSP_SUCCESS != result)
        {
            SSP_ERROR_LOG((result), (&g_module_name[0]), (&g_sci_spi_version));
            return result;
        }
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        /* Open transmit transfer module. */
        result =  r_sci_spi_open_transmit_interface (p_cfg, p_ssp_feature);
        if (SSP_SUCCESS != result)
        {
            p_cfg->p_transfer_rx->p_api->close(p_cfg->p_transfer_rx->p_ctrl);
            SSP_ERROR_LOG((result), (&g_module_name[0]), (&g_sci_spi_version));
            return result;
        }
    }

    return SSP_SUCCESS;
}

/*****************************************************************************************************************//**
 * @brief Sets valid interrupt priority
 *
 * @param[in]       p_ctrl          Pointer to control struct of specific device
 * @param[in]       p_cfg           Pointer to SCI SPI specific configuration structure
 *
 * @retval          SSP_SUCCESS     Interrupts enabled.
 * 
 * See @ref Common_Error_Codes for other possible return codes. This function calls
 *                                  * fmi_api_t::productFeatureGet
 ********************************************************************************************************************/
static ssp_err_t r_sci_spi_set_valid_interrupts_priority   (sci_spi_instance_ctrl_t * p_ctrl,
                                                             spi_cfg_t const * const p_cfg)
{
    ssp_err_t err;

    ssp_feature_t ssp_feature = {{(ssp_ip_t) 0U}};
    ssp_feature.channel = p_cfg->channel;
    ssp_feature.unit = 0U;
    ssp_feature.id = SSP_IP_SCI;

    err = r_sci_irq_cfg(&ssp_feature, SSP_SIGNAL_SCI_RXI, p_cfg->rxi_ipl, p_ctrl, &p_ctrl->rxi_irq);
    if (SSP_SUCCESS != err)
    {
        SSP_ERROR_LOG((err), (&g_module_name[0]), (&g_sci_spi_version));
        return err;
    }
    err = r_sci_irq_cfg(&ssp_feature, SSP_SIGNAL_SCI_TXI, p_cfg->txi_ipl, p_ctrl, &p_ctrl->txi_irq);
    if (SSP_SUCCESS != err)
    {
        SSP_ERROR_LOG((err), (&g_module_name[0]), (&g_sci_spi_version));
        return err;
    }
    err = r_sci_irq_cfg(&ssp_feature, SSP_SIGNAL_SCI_TEI, p_cfg->tei_ipl, p_ctrl, &p_ctrl->tei_irq);
    if (SSP_SUCCESS != err)
    {
        SSP_ERROR_LOG((err), (&g_module_name[0]), (&g_sci_spi_version));
        return err;
    }
    err = r_sci_irq_cfg(&ssp_feature, SSP_SIGNAL_SCI_ERI, p_cfg->eri_ipl, p_ctrl, &p_ctrl->eri_irq);
    if (SSP_SUCCESS != err)
    {
        SSP_ERROR_LOG((err), (&g_module_name[0]), (&g_sci_spi_version));
        return err;
    }

    return err;
}

/*****************************************************************************************************************//**
 * @brief Enable or disable bitrate modulation.
 *
 * @param[in,out]       p_sci_reg                 Pointer to SCI SPI register.
 * @param[in]           p_cfg                     Pointer to SCI SPI specific configuration structure
 *
 * @retval              void
*********************************************************************************************************************/
static void r_sci_spi_bit_rate_modulation   (R_SCI0_Type * p_sci_reg, spi_cfg_t const * const p_cfg)
{
    sci_spi_extended_cfg * pextend;
    pextend = (sci_spi_extended_cfg *) p_cfg->p_extend;

    /* Enable bitrate modulation function. */
    if ((pextend) && (pextend->bitrate_modulation))
    {
        HW_SCI_BitRateModulationEnable(p_sci_reg, true);          /** enables the bitrate modulation function */
    }
    else
    {
        HW_SCI_BitRateModulationEnable(p_sci_reg, false);         /** disables the bitrate modulation function */
    }
}

/*****************************************************************************************************************//**
 * @brief Sets registers based on user configuration.
 *
 * @param[in]           p_cfg                     Pointer to SCI SPI specific configuration structure.
 *
 * @retval              temp_a                    Temporary register value.
*********************************************************************************************************************/
static uint8_t r_sci_spi_set_register   (spi_cfg_t const * const p_cfg)
{
    /* Process the user configuration to update the local configuration image. */
    /* Program the registers based on the user configuration file. */
    /* Update SPI Mode register -- SPMR selection. */
    uint8_t          temp_a =0U;

    /* Set MSS -- master/slave mode. */
    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        temp_a |= SCI_SPI_SPMR_SLAVE_MODE;

        /* Select to use SSLn input pin */
        temp_a |= SCI_SPI_SPMR_SSN_PIN_ENABLE_SET;
    }

    if (SPI_CLK_PHASE_EDGE_EVEN == p_cfg->clk_phase)
    {
        /* According to HM Rev0.70, in order to get  Phase= Data sampling on even edge, CKPH should be 0. */
        /* If CKPH =0, to get a low polarity during idle, CKPOL bit should be 1. (See Figure 34.69). */
        if (SPI_CLK_POLARITY_LOW == p_cfg->clk_polarity)
        {
            temp_a |= SCI_SPI_SPMR_CKPOL_INVERTED;
        }
    }

    else
    {
        /* According to HM Rev0.70, in order to get  Phase= Data sampling on odd edge, CKPH should be 1. */
        /* If CKPH =1, to get a high polarity during idle, CKPOL bit should be 1. (See Figure 34.69). */

        /* Set CKPH - clock phase ODD - CKPH = 1. */
        temp_a |= SCI_SPI_SPMR_CKPH_DELAYED;

        /* Set CKPOL - clock polarity. */
        if (SPI_CLK_POLARITY_HIGH == p_cfg->clk_polarity)
        {
            temp_a |= SCI_SPI_SPMR_CKPOL_INVERTED;
        }
    }

    return temp_a;
}

/*****************************************************************************************************************//**
 * @brief Set MSB/LSB based on user configuration.
 *
 * @param[in,out]       p_sci_reg                 Pointer to SCI SPI register.
 * @param[in]           p_cfg                     Pointer to SCI SPI specific configuration structure.
 *
 * @retval              void
*********************************************************************************************************************/
static void r_sci_spi_set_msb_lsb   (R_SCI0_Type * p_sci_reg, spi_cfg_t const * const p_cfg)
{
    /* Set MSB/LSB based on the user configuration file. */
    if (SPI_BIT_ORDER_MSB_FIRST == p_cfg->bit_order)
    {
        HW_SCI_TransferDirection(p_sci_reg, true);
    }
}

/*****************************************************************************************************************//**
 * @brief Enable transmit and receive interrupts.
 *
 * @param[in,out]       p_sci_reg                 Pointer to SCI SPI register.
 * @param[in]           p_ctrl                    Pointer to control struct of specific device.
 * @param[in]           tx_rx_mode                Mode of the data transaction.
 *
 * @retval              void.
 * ******************************************************************************************************************/
static void r_sci_spi_set_tx_rx_interrupt   (R_SCI0_Type * p_sci_reg,
                                             sci_spi_instance_ctrl_t * const p_ctrl,
                                             spi_operation_t tx_rx_mode )
{
    if (SPI_OPERATION_DO_TX == tx_rx_mode)
    {
        /* If a transfer module is enabled in a write only operation, enable the transmit interrupt only. */
        HW_SCI_TxIrqEnable(p_sci_reg);
        HW_SCI_TransmitterEnable(p_sci_reg);
    }
    else
    {
        /* Enable interrupts in ICU. */
        HW_SCI_RxIrqEnable(p_sci_reg);
        HW_SCI_TxIrqEnable(p_sci_reg);
        
        /** Enables transmitter and receiver at the same time. */
        HW_SCI_TransmitterReceiverEnable(p_sci_reg);
    }

    if ((NULL != p_ctrl->p_transfer_tx) || (NULL != p_ctrl->p_transfer_rx))
    {
        /* Perform a RDR register read to clear pending RX interrupt if any. */
        /* This is mostly required if a TX only (no RDR read) operation is performed first
         * and performs a read afterwards. */
        HW_SCI_Read(p_sci_reg);
    }
}

/*****************************************************************************************************************//**
 * This function resets the TX transfer interface.
 * @param[in]   p_ctrl              Pointer to driver control block
 * @param[in]   tx_rx_mode          Current transmit receive mode
 * @param[in]   p_data_reg          Data register of the module
 * @param[in]   length              Length of data to be transmitted/received
 *
 * @retval      SSP_SUCCESS         Transaction successful or Transfer interface not configured
 * @return                          See @ref Common_Error_Codes or functions called by this function
 *                                  for other possible return codes. This function calls:
 *                                  * transfer_api_t::disable
 *                                  * transfer_api_t::enable
 *                                  * transfer_api_t::reset
 *********************************************************************************************************************/
static ssp_err_t r_sci_spi_tx_transfer_reset (sci_spi_instance_ctrl_t * const p_ctrl,
                                              spi_operation_t                 tx_rx_mode,
                                              uint32_t                *       p_data_reg,
                                              uint32_t                  const length )
{
    ssp_err_t result = SSP_SUCCESS;
    transfer_addr_mode_t addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;

    /* If the current mode is receive only */
    if (tx_rx_mode == SPI_OPERATION_DO_RX)
    {
        /* Set the transmit location to a fixed source location. */
        p_ctrl->p_src = (void *)&g_dummy;
        addr_mode = TRANSFER_ADDR_MODE_FIXED;
    }

    /* If the mode has changed or DTC is configured for 8bit chained mode it needs reset. */
    if (p_ctrl->tx_dtc_addr_mode != addr_mode)
    {
        /* Close the transfer instance to reconfigure it. */
        result = p_ctrl->p_transfer_tx->p_api->disable(p_ctrl->p_transfer_tx->p_ctrl);
        SCI_SPI_ERROR_RETURN((SSP_SUCCESS == result), result);

        /* Reset the transfer config block with provided addresses and length. */
        p_ctrl->p_transfer_tx->p_cfg->p_info->src_addr_mode = addr_mode;
        p_ctrl->p_transfer_tx->p_cfg->p_info->p_src = p_ctrl->p_src;
        p_ctrl->p_transfer_tx->p_cfg->p_info->length = (uint16_t)length;
        p_ctrl->p_transfer_tx->p_cfg->p_info->p_dest = p_data_reg;

        result = p_ctrl->p_transfer_tx->p_api->enable(p_ctrl->p_transfer_tx->p_ctrl);
        p_ctrl->tx_dtc_addr_mode = addr_mode;
    }
    else
    {
        /* Reset the transfer instance if it does not need reconfigured. */
        result = p_ctrl->p_transfer_tx->p_api->reset(p_ctrl->p_transfer_tx->p_ctrl,
                                                 p_ctrl->p_src,
                                                 (void *)p_data_reg,
                                                 (uint16_t) length);
    }
    return result;
}

/*****************************************************************************************************************//**
 * This function tries RX/TX using transfer interface, if configured, else returns success anyway for CPU to do it.
 * @param[in]   p_ctrl              Pointer to driver control block
 * @param[in ]  tx_rx_mode          Bit width value to set
 * @param[in ]  length              Bit width value to set
 *
 * @retval      SSP_ERR_ASSERTION   The Number of units of data to be transferred is more than 0xFFFFU.
 * @retval      SSP_ERR_NOT_OPEN    Invalid transfer device handle.
 * @retval      SSP_ERR_NOT_ENABLED Invalid transaction parameter
 * @retval      SSP_SUCCESS         Transaction successful or Transfer interface not configured
 *********************************************************************************************************************/
static ssp_err_t r_sci_spi_transfer_reset (sci_spi_instance_ctrl_t * const p_ctrl,
                                           spi_operation_t                 tx_rx_mode,
                                           uint32_t                  const length )
{
#if (SCI_SPI_CFG_PARAM_CHECKING_ENABLE)
    SCI_SPI_ERROR_RETURN(length <= 0xFFFFU, SSP_ERR_ASSERTION);
#endif
    ssp_err_t result = SSP_SUCCESS;
    uint32_t * p_data_reg;

    if (NULL != p_ctrl->p_transfer_tx)
    {
        /* Get the address of the data register. */
        p_data_reg = (uint32_t *) HW_SCI_SPIWriteAddrGet(p_ctrl->p_reg);

        /* Reset the transmit transfer instance. */
        result = r_sci_spi_tx_transfer_reset(p_ctrl, tx_rx_mode, p_data_reg, length);
        SCI_SPI_ERROR_RETURN((SSP_SUCCESS == result), result);
    }

    if ((NULL != p_ctrl->p_transfer_rx) && (SPI_OPERATION_DO_TX != tx_rx_mode))
    {
        p_data_reg = (uint32_t *) HW_SCI_SPIReadAddrGet(p_ctrl->p_reg);

        /* Reset the transfer instance if it does not need reconfigured. */
        result = p_ctrl->p_transfer_rx->p_api->reset(p_ctrl->p_transfer_rx->p_ctrl,
                                                     (void const *)p_data_reg,
                                                     (void *)p_ctrl->p_dest,
                                                     (uint16_t) length);
    }
    return result;
} /* End of function rspi_transfer_reset(). */

/*****************************************************************************************************************//**
 * @brief Open receive transfer module if enabled
 *
 * @param[in]     p_cfg                 Pointer to SCI SPI specific configuration structure
 * @param[in]     p_ssp_feature         SSP feature
 *
 * @retval        SSP_SUCCESS           Transfer module successfully opened.
 * @retval        SSP_ERR_ASSERTION     One of the following invalid parameters passed
 *                                       - Pointer p_cfg is NULL
 *                                       - Interrupt is not enabled
 * 
 * See @ref Common_Error_Codes or functions called by this function
 *                                      for other possible return codes. This function calls:
 *                                      * transfer_api_t::open
 * ******************************************************************************************************************/
static ssp_err_t r_sci_spi_open_receive_interface (spi_cfg_t const * const p_cfg, ssp_feature_t * p_ssp_feature)
{
    ssp_err_t result = SSP_SUCCESS;

    /** Set default transfer info and open receive transfer module, if enabled. */
/* Perform parameter checking. */
#if (SCI_SPI_CFG_PARAM_CHECKING_ENABLE)
    SSP_ASSERT(NULL != p_cfg->p_transfer_rx->p_api);
    SSP_ASSERT(NULL != p_cfg->p_transfer_rx->p_ctrl);
    SSP_ASSERT(NULL != p_cfg->p_transfer_rx->p_cfg);
    SSP_ASSERT(NULL != p_cfg->p_transfer_rx->p_cfg->p_info);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    transfer_info_t * p_info = p_cfg->p_transfer_rx->p_cfg->p_info;
    p_info->mode = TRANSFER_MODE_NORMAL;
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
    p_info->irq = TRANSFER_IRQ_END;
    p_info->size = TRANSFER_SIZE_1_BYTE;

    transfer_cfg_t cfg = *(p_cfg->p_transfer_rx->p_cfg);
    fmi_event_info_t event_info = {(IRQn_Type) 0U};
    g_fmi_on_fmi.eventInfoGet(p_ssp_feature, SSP_SIGNAL_SCI_RXI, &event_info);

/* Perform parameter checking. */
#if (SCI_SPI_CFG_PARAM_CHECKING_ENABLE)
    /* Check to make sure the interrupt is enabled. */
    SSP_ASSERT(SSP_INVALID_VECTOR != event_info.irq);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    cfg.activation_source = event_info.event;
    cfg.auto_enable = false;
    cfg.p_callback  = NULL;
    result = p_cfg->p_transfer_rx->p_api->open(p_cfg->p_transfer_rx->p_ctrl, &cfg);

    return result;
}

/*****************************************************************************************************************//**
 * @brief Open transmit transfer module if enabled
 *
 * @param[in]     p_cfg                 Pointer to SCI SPI specific configuration structure
 * @param[in]     p_ssp_feature         SSP feature
 *
 * @retval        SSP_SUCCESS           Transfer module successfully opened.
 * @retval        SSP_ERR_ASSERTION     One of the following invalid parameters passed
 *                                       - Pointer p_cfg is NULL
 *                                       - Interrupt is not enabled
 * 
 * See @ref Common_Error_Codes or functions called by this function
 *                                      for other possible return codes. This function calls:
 *                                      * transfer_api_t::open
 * ******************************************************************************************************************/
static ssp_err_t r_sci_spi_open_transmit_interface (spi_cfg_t const * const p_cfg, ssp_feature_t * p_ssp_feature)
{
    ssp_err_t result = SSP_SUCCESS;

    /** Set default transfer info and open transmit transfer module, if enabled. */
/* Perform parameter checking. */
#if (SCI_SPI_CFG_PARAM_CHECKING_ENABLE)
    SSP_ASSERT(NULL != p_cfg->p_transfer_tx->p_api);
    SSP_ASSERT(NULL != p_cfg->p_transfer_tx->p_ctrl);
    SSP_ASSERT(NULL != p_cfg->p_transfer_tx->p_cfg);
    SSP_ASSERT(NULL != p_cfg->p_transfer_tx->p_cfg->p_info);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    transfer_info_t * p_info = p_cfg->p_transfer_tx->p_cfg->p_info;
    p_info->mode = TRANSFER_MODE_NORMAL;
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
    p_info->src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->irq = TRANSFER_IRQ_END;
    p_info->size = TRANSFER_SIZE_1_BYTE;

    transfer_cfg_t cfg = *(p_cfg->p_transfer_tx->p_cfg);
    fmi_event_info_t event_info = { (IRQn_Type) 0U };
    g_fmi_on_fmi.eventInfoGet(p_ssp_feature, SSP_SIGNAL_SCI_TXI, &event_info);

/* Perform parameter checking. */
#if (SCI_SPI_CFG_PARAM_CHECKING_ENABLE)
    /* Check to make sure the interrupt is enabled. */
    SSP_ASSERT(SSP_INVALID_VECTOR != event_info.irq);
#endif
/* if SCI_SPI_CFG_PARAM_CHECKING_ENABLE. */

    cfg.activation_source = event_info.event;
    cfg.auto_enable = false;
    cfg.p_callback  = NULL;
    result = p_cfg->p_transfer_tx->p_api->open(p_cfg->p_transfer_tx->p_ctrl, &cfg);

    return result;
}

/* End of file. */
