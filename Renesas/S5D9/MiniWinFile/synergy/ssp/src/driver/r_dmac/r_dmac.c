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
 * File Name    : r_dmac.c
 * Description  : DMAC implementation of the transfer interface.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_dmac.h"
#include "r_dmac_cfg.h"
#include "hw/hw_dmac_private.h"
#include "r_dmac_private_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/** Driver ID (DMAC in ASCII) */
#define DMAC_ID (0x444d4143)

/** Macro for error logger. */
#ifndef DMAC_ERROR_RETURN
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define DMAC_ERROR_RETURN(a, err) SSP_ERROR_RETURN((a), (err), &g_module_name[0], &g_dmac_version)
#endif

/** Length limited to 1024 transfers for repeat and block mode */
#define DMAC_REPEAT_BLOCK_MAX_LENGTH (0x400)

#define DMAC_PRV_MASK_ALIGN_2_BYTES     (0x1U)
#define DMAC_PRV_MASK_ALIGN_4_BYTES     (0x3U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Internal driver storage for p_callback, used by ISRs. */
typedef struct st_dmac_callback
{
    /** Callback for transfer end interrupt. Set to NULL for no CPU interrupt. */
    void (* p_callback)(transfer_callback_args_t * cb_data);

    /** Placeholder for user data.  Passed to the user p_callback in ::transfer_callback_args_t. */
    void const * p_context;
} dmac_callback_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void dmac_int_isr (void);

/* Convenience functions */
#if DMAC_CFG_PARAM_CHECKING_ENABLE
static ssp_err_t dma_open_assert_check       (dmac_instance_ctrl_t * const p_ctrl,
                                              transfer_cfg_t const * const p_cfg);
static ssp_err_t dma_reset_assert_check      (dmac_instance_ctrl_t * const p_ctrl,
                                              uint16_t const num_transfers);
static ssp_err_t dma_blockreset_assert_check (dmac_instance_ctrl_t  * const p_ctrl,
                                              uint16_t const length);
#endif
static void dma_transfer_config              (transfer_cfg_t const * const p_cfg,
                                              R_DMAC0_Type * const         p_dmac_regs,
                                              dmac_instance_ctrl_t * const p_ctrl);
static void dma_ir_flag_clear                (dmac_instance_ctrl_t * const p_ctrl);

static ssp_err_t dma_offset_value_set        (dmac_instance_ctrl_t * const p_ctrl,
                                              transfer_cfg_t const * const p_cfg);

static ssp_err_t dma_vector_info_get        (dmac_instance_ctrl_t * const p_ctrl,
                                              transfer_cfg_t const * const p_cfg,
                                              ssp_feature_t * feature);

#if DMAC_CFG_PARAM_CHECKING_ENABLE
static ssp_err_t r_dmac_enable_alignment_check(void const * p_src, void const * p_dest, transfer_size_t size);
#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "dmac";
#endif

#if defined(__GNUC__)
/* This structure is affected by warnings from a GCC compiler bug. This pragma suppresses the warnings in this 
 * structure only.*/
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
/** Version data structure used by error logger macro. */
static const ssp_version_t g_dmac_version =
{
    .api_version_minor  = TRANSFER_API_VERSION_MINOR,
    .api_version_major  = TRANSFER_API_VERSION_MAJOR,
    .code_version_major = DMAC_CODE_VERSION_MAJOR,
    .code_version_minor = DMAC_CODE_VERSION_MINOR
};
#if defined(__GNUC__)
/* Restore warning settings for 'missing-field-initializers' to as specified on command line. */
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic pop
#endif

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** DMAC implementation of transfer API. */
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const transfer_api_t g_transfer_on_dmac =
{
    .open                    = R_DMAC_Open,
    .reset                   = R_DMAC_Reset,
    .infoGet                 = R_DMAC_InfoGet,
    .start                   = R_DMAC_Start,
    .stop                    = R_DMAC_Stop,
    .enable                  = R_DMAC_Enable,
    .disable                 = R_DMAC_Disable,
    .close                   = R_DMAC_Close,
    .versionGet              = R_DMAC_VersionGet,
    .blockReset              = R_DMAC_BlockReset,
    .Stop_ActivationRequest  = R_DMAC_Stop_ActivationRequest
};

/** Stores pointer to DMA base address. */
static R_DMA_Type * gp_dma_regs = NULL;

/** Stores pointer to ICU base address. */
static R_ICU_Type * gp_icu_regs = NULL;

/*******************************************************************************************************************//**
 * @addtogroup DMAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Initialize transfer and enables transfer in ICU. Implements transfer_api_t::open.
 *
 * @retval SSP_SUCCESS              Successful open.  Transfer is configured and will start when trigger occurs.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_ENABLED      Auto-enable was requested, but enable failed.
 * @retval SSP_ERR_IRQ_BSP_DISABLED The IRQ associated with the activation source is not enabled in the BSP.
 * @retval SSP_ERR_INVALID_SIZE     Invalid offset value.
 * @retval SSP_ERR_IN_USE           The BSP hardware lock for the DMAC is not available.
 * @return                          See @ref Common_Error_Codes for other possible return codes.This function calls
 *                                  * fmi_api_t::productFeatureGet
 *                                  * fmi_api_t::eventInfoGet
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Open      (transfer_ctrl_t         * const p_api_ctrl,
                            transfer_cfg_t const * const    p_cfg)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t err = SSP_SUCCESS;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    err = dma_open_assert_check(p_ctrl,p_cfg);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif /* if DMAC_CFG_PARAM_CHECKING_ENABLE */

    bsp_feature_icu_t icu_feature = {0U};
    transfer_on_dmac_cfg_t * p_extend = (transfer_on_dmac_cfg_t *) p_cfg->p_extend;
    p_ctrl->channel = p_extend->channel;
    p_ctrl->offset_byte = p_extend->offset_byte;

    ssp_feature_t feature = {{(ssp_ip_t) 0U}};
    fmi_feature_info_t info = {0U};
    if (NULL == gp_icu_regs)
    {
        feature.id = SSP_IP_ICU;
        feature.channel = 0U;
        feature.unit = 0U;
        g_fmi_on_fmi.productFeatureGet(&feature, &info);
        gp_icu_regs = (R_ICU_Type *) info.ptr;
    }

    if (NULL == gp_dma_regs)
    {
        feature.id = SSP_IP_DMAC;
        feature.channel = 0U;
        feature.unit = 1U;
        g_fmi_on_fmi.productFeatureGet(&feature, &info);
        gp_dma_regs = (R_DMA_Type *) info.ptr;
    }

    feature.id = SSP_IP_DMAC;
    feature.channel = p_ctrl->channel;
    feature.unit = 0U;

    err = g_fmi_on_fmi.productFeatureGet(&feature, &info);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);

    /* Checking IR bit availability on MCU */
    R_BSP_FeatureICUGet(&icu_feature);
    p_ctrl->ir_flag_stat = icu_feature.has_ir_flag;

    p_ctrl->p_reg = info.ptr;
    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;

    /** Get the IRQ vectors, event info and set the NVIC priority for dmac. */
    err = dma_vector_info_get(p_ctrl,p_cfg, &feature);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);

    /** Acquire BSP hardware lock for channel used. */
    err = R_BSP_HardwareLock(&feature);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);

    /** Configure the DMAC according to the flowchart "Activating the DMAC" in chapter 16.3.7 of hardware
     *  manual NoSecurity_r01uh0488ej0040_sc32.pdf. */
    R_BSP_ModuleStart(&feature);
    uint8_t ch = p_ctrl->channel;

    dma_ir_flag_clear(p_ctrl);
    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_DISABLE);

    HW_DMAC_DestAddrUpdateModeSet(p_dmac_regs, p_cfg->p_info->dest_addr_mode);
    HW_DMAC_SrcAddrUpdateModeSet(p_dmac_regs, p_cfg->p_info->src_addr_mode);

    /** Set the offset value in offset addressing mode. */
    err = dma_offset_value_set(p_ctrl, p_cfg);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);

    /* Extended repeat area not supported. */
    HW_DMAC_DestExtendedRepeatAreaSet(p_dmac_regs, DMAC_EXTENDED_REPEAT_AREA_NONE);
    HW_DMAC_SrcExtendedRepeatAreaSet(p_dmac_regs, DMAC_EXTENDED_REPEAT_AREA_NONE);

    /** Configure DMA transfer and sources*/
    dma_transfer_config(p_cfg,p_dmac_regs,p_ctrl);

    /** @note Transfer escape interrupts not supported. */

    /** Update internal variables. */
    p_ctrl->channel = ch;
    p_ctrl->trigger = p_cfg->activation_source;

    /** Mark driver as open by initializing "DMAC" in its ASCII equivalent.*/
    p_ctrl->id      = DMAC_ID;

    /** If auto_enable is true, enable transfer and ELC events if software start is used. */
    if (p_cfg->auto_enable)
    {
        err = R_DMAC_Enable(p_ctrl);
    }
    HW_DMAC_Enable(gp_dma_regs);

    DMAC_ERROR_RETURN(SSP_SUCCESS == err, SSP_ERR_NOT_ENABLED);

    return SSP_SUCCESS;
} /* End of function R_DMAC_Open */

/*******************************************************************************************************************//**
 * @brief  Reset transfer source, destination, and number of transfers.
 *
 * @retval SSP_SUCCESS              Transfer reset successfully.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_ENABLED      DMAC is not enabled. A valid source and destination must be
 *                                  provided in either open() or reset().
 * @retval SSP_ERR_IN_USE           Transfer is in progress. Wait for transfer to complete.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Reset (transfer_ctrl_t         * const   p_api_ctrl,
                        void const * volatile             p_src,
                        void                   * volatile p_dest,
                        uint16_t const                    num_transfers)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t err = SSP_SUCCESS;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    err = dma_reset_assert_check(p_ctrl,num_transfers);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif

    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    if (HW_DMAC_StatusGet(p_dmac_regs))
    {
        return SSP_ERR_IN_USE;
    }

    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_DISABLE);
    if (NULL != p_src)
    {
        HW_DMAC_SrcStartAddrSet(p_dmac_regs, p_src);
    }

    if (NULL != p_dest)
    {
        HW_DMAC_DestStartAddrSet(p_dmac_regs, p_dest);
    }

    if ((TRANSFER_MODE_NORMAL != HW_DMAC_ModeGet(p_dmac_regs)))
    {
        HW_DMAC_BlockNumberSet(p_dmac_regs, num_transfers);
    }
    else
    {
        HW_DMAC_TransferNumberSet(p_dmac_regs, num_transfers);
    }

    /** Enables transfers on this activation source. */
    err = R_DMAC_Enable(p_ctrl);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, SSP_ERR_NOT_ENABLED);

    return SSP_SUCCESS;
} /* End of function R_DMAC_Reset */

/*******************************************************************************************************************//**
 * @brief  Start transfer. Implements transfer_api_t::start.
 *
 * @retval SSP_SUCCESS              Transfer started written successfully.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 * @retval SSP_ERR_UNSUPPORTED      Handle was not configured for software activation.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Start     (transfer_ctrl_t         * const p_api_ctrl,
                            transfer_start_mode_t           mode)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
#endif

    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    DMAC_ERROR_RETURN ((ELC_EVENT_ELC_SOFTWARE_EVENT_0 == p_ctrl->trigger) ||
            (ELC_EVENT_ELC_SOFTWARE_EVENT_1 == p_ctrl->trigger),SSP_ERR_UNSUPPORTED);

    /** Set autoclear bit and software start bit. */
    HW_DMAC_SoftwareStartAutoClear(p_dmac_regs, mode);
    HW_DMAC_SoftwareStart(p_dmac_regs);

    return SSP_SUCCESS;
} /* End of function R_DMAC_Start */

/*******************************************************************************************************************//**
 * @brief  Stop transfer. Implements transfer_api_t::stop.
 *
 * @retval SSP_SUCCESS              Transfer stopped written successfully.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Stop       (transfer_ctrl_t         * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
#endif

    /** Reset auto clear bit and clear software transfer request. */
    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    HW_DMAC_SoftwareStartAutoClear(p_dmac_regs, TRANSFER_START_MODE_SINGLE);
    HW_DMAC_SoftwareStop(p_dmac_regs);

    return SSP_SUCCESS;
} /* End of function R_DMAC_Stop */

/*******************************************************************************************************************//**
 * @brief  Enable transfer. Implements transfer_api_t::enable.
 *
 * @retval SSP_SUCCESS              Counter value written successfully.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Enable (transfer_ctrl_t         * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
#endif

    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;

#if DMAC_CFG_PARAM_CHECKING_ENABLE
    void const * p_src = HW_DMAC_SrcStartAddrGet(p_dmac_regs);
    SSP_ASSERT(NULL != p_src);
    void const * p_dest = HW_DMAC_DestStartAddrGet(p_dmac_regs);
    SSP_ASSERT(NULL != p_dest);

    transfer_size_t size = HW_DMAC_TransferSizeGet(p_dmac_regs);
    ssp_err_t err = r_dmac_enable_alignment_check(p_src, p_dest, size);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif

    /** Enable transfer. */
    HW_ICU_DmacEnable(gp_icu_regs, p_ctrl->channel, p_ctrl->trigger);
    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_ENABLE);

    return SSP_SUCCESS;
} /* End of function R_DMAC_Enable */

/*******************************************************************************************************************//**
 * @brief  Disable transfer. Implements transfer_api_t::disable.
 *
 * @retval SSP_SUCCESS              Counter value written successfully.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Disable (transfer_ctrl_t         * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
#endif

    /** Disable transfer. */
    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    /* 0 is not a valid ELC event number, so this will not cause a different event to start a transfer. */
    HW_ICU_DmacEnable(gp_icu_regs, p_ctrl->channel, (elc_event_t) 0);
    dma_ir_flag_clear(p_ctrl);
    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_DISABLE);

    return SSP_SUCCESS;
} /* End of function R_DMAC_Disable */

/*******************************************************************************************************************//**
 * @brief  Set driver specific information in provided pointer. Implements transfer_api_t::infoGet.
 *
 * @retval SSP_SUCCESS              Counter value written successfully.
 * @retval SSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_InfoGet (transfer_ctrl_t       * const p_api_ctrl,
                          transfer_properties_t * const p_info)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    SSP_ASSERT(NULL != p_info);
#endif

    /** If a transfer is active, store it in p_in_progress. */
    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    p_info->in_progress = HW_DMAC_StatusGet(p_dmac_regs);

    /** Store maximum transfer length. */
    transfer_mode_t mode = HW_DMAC_ModeGet(p_dmac_regs);
    if (TRANSFER_MODE_NORMAL == mode)
    {
        p_info->transfer_length_max = DMAC_NORMAL_MAX_LENGTH;
    }
    else
    {
        p_info->transfer_length_max = DMAC_REPEAT_BLOCK_MAX_LENGTH;
    }
    /** Store remaining transfer length. */
    if (TRANSFER_MODE_BLOCK == mode)
    {
        p_info->transfer_length_remaining = HW_DMAC_BlockNumberGet(p_dmac_regs);
    }
    else if(TRANSFER_MODE_REPEAT == mode)
    {
        p_info->transfer_length_remaining = HW_DMAC_BlockNumberGet(p_dmac_regs);
    }
    else
    {
        p_info->transfer_length_remaining = HW_DMAC_TransferNumberGet(p_dmac_regs);
    }

    return SSP_SUCCESS;
} /* End of function R_DMAC_StatusGet */

/*******************************************************************************************************************//**
 * @brief      Disable transfer and clean up internal data. Implements transfer_api_t::close.
 *
 * @retval SSP_SUCCESS           Successful close.
 * @retval SSP_ERR_ASSERTION     An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 * @retval SSP_ERR_IN_USE        Transfer is in progress. Wait for transfer to complete.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Close     (transfer_ctrl_t         * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
#endif

    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    if (HW_DMAC_StatusGet(p_dmac_regs))
    {
        return SSP_ERR_IN_USE;
    }

    /** Disable DMAC transfers, disable DMAC interrupts, and remove DMAC trigger from ICU register. */
    /* 0 is not a valid ELC event number, so this will not cause a different event to start a transfer. */
    HW_ICU_DmacEnable(gp_icu_regs, p_ctrl->channel, (elc_event_t) 0);
    dma_ir_flag_clear(p_ctrl);
    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_DISABLE);

    if (SSP_INVALID_VECTOR != p_ctrl->irq)
    {
        NVIC_DisableIRQ(p_ctrl->irq);
        ssp_vector_info_t * p_vector_info;
        R_SSP_VectorInfoGet(p_ctrl->irq, &p_vector_info);
        *(p_vector_info->pp_ctrl) = NULL;
    }

    /** Clear ID so control block can be reused. */
    p_ctrl->id = 0U;

    /** Release BSP hardware lock on this channel */
    ssp_feature_t feature = {{(ssp_ip_t) 0U}};
    feature.id = SSP_IP_DMAC;
    feature.channel = p_ctrl->channel;
    feature.unit = 0U;
    R_BSP_HardwareUnlock(&feature);

    return SSP_SUCCESS;
} /* End of function R_DMAC_Close */

/*******************************************************************************************************************//**
 * @brief      Set driver version based on compile time macros.
 *
 * @retval SSP_SUCCESS              Successful close.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_VersionGet (ssp_version_t     * const p_version)
{
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    /** Verify parameters are valid */
    SSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_dmac_version.version_id;

    return SSP_SUCCESS;
} /* End of function R_DMAC_VersionGet */

/*******************************************************************************************************************//**
 * @brief  Reset transfer source, destination, length and number of transfers for block transfer.
 *
 * @retval SSP_SUCCESS              Transfer reset successfully.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_IN_USE           Transfer is in progress. Wait for transfer to complete.
 * @retval SSP_ERR_NOT_ENABLED      DMAC is not enabled. A valid source and destination must
 *                                  be provided in either open() or blockReset().
 **********************************************************************************************************************/
ssp_err_t R_DMAC_BlockReset (transfer_ctrl_t              * const p_api_ctrl,
                                void             const * volatile p_src,
                                void                   * volatile p_dest,
                                uint16_t                    const length,
                                transfer_size_t                   size,
                                uint16_t                    const num_transfers)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t err = SSP_SUCCESS;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    err = dma_blockreset_assert_check(p_ctrl,length);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif

    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    if (HW_DMAC_StatusGet(p_dmac_regs))
    {
        return SSP_ERR_IN_USE;
    }

    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_DISABLE);
    if (NULL != p_src)
    {
        HW_DMAC_SrcStartAddrSet(p_dmac_regs, p_src);
    }

    if (NULL != p_dest)
    {
        HW_DMAC_DestStartAddrSet(p_dmac_regs, p_dest);
    }

    HW_DMAC_BlockNumberSet(p_dmac_regs, num_transfers);
    HW_DMAC_TransferNumberSet(p_dmac_regs, length);
    HW_DMAC_TransferReloadSet(p_dmac_regs, length);
    HW_DMAC_TransferSizeSet(p_dmac_regs, size);

    /** Enables transfers on this activation source. */
    err = R_DMAC_Enable(p_ctrl);
    DMAC_ERROR_RETURN(SSP_SUCCESS == err, SSP_ERR_NOT_ENABLED);

    return SSP_SUCCESS;
} /* End of function R_DMAC_BlockReset */

/*******************************************************************************************************************//**
 * @brief       Clears the DMA activation request with a DMA dummy transfer as per flowchart in the hardware manual.
 *              Implements transfer_api_t::Stop_ActivationRequest.
 *              This function to be used only in scenario when a DMA activation request source might occur in the next request
 *              after a DMA transfer completes. If this happens, the DMA transfer starts and the DMA activation
 *              request is held in DMAC.
 *
 * @retval SSP_SUCCESS           Successful transfer.
 * @retval SSP_ERR_ASSERTION     An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
ssp_err_t R_DMAC_Stop_ActivationRequest(transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t  * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(DMAC_ID == p_ctrl->id, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
#endif
    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;

    /** Clear the DMA activation request with a DMA dummy transfer as per flowchart in the hardware manual. */
    /** Disable DMAC transfer. */
    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_DISABLE);
    /** Disable the IRQ pin as a DMACm request source */
    NVIC_DisableIRQ(p_ctrl->irq);
    /** Set the DMAC transfer size */
    HW_DMAC_TransferSizeSet (p_dmac_regs, TRANSFER_SIZE_4_BYTE);
    /** Set source and destination address to 4000_5500 as per hardware manual.  */
    HW_DMAC_SrcStartAddrSet (p_dmac_regs, DUMMY_ADDRESS);
    HW_DMAC_DestStartAddrSet (p_dmac_regs, DUMMY_ADDRESS);
    /** Set number of transfer operations */
    HW_DMAC_TransferNumberSet(p_dmac_regs, TRANSFER_SIZE_2_BYTE);
    HW_DMAC_TransferReloadSet(p_dmac_regs, TRANSFER_SIZE_1_BYTE);
    /** Disable DMAC transfer. */
    HW_DMAC_TransferEnableDisable(p_dmac_regs, DMAC_TRANSFER_ENABLE);
    /** Wait for the DMAC transfer end*/
    while(HW_DMAC_StatusGet(p_dmac_regs))
    {

    }
    NVIC_EnableIRQ(p_ctrl->irq);

    return SSP_SUCCESS;
}/* End of function R_DMAC_Stop_ActivationRequest */
/*******************************************************************************************************************//**
 * @} (end addtogroup DMAC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 * @brief      Channel 0 ISR.
 *
 * Saves p_context if RTOS is used, clears the interrupt flag, calls p_callback if one was provided in the open
 * function, and restores p_context if RTOS is used.
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @brief      DMAC ISR.
 *
 * Saves context if RTOS is used, clears the interrupt flag, calls p_callback if one was provided in the open
 * function, and restores context if RTOS is used.
 **********************************************************************************************************************/
void dmac_int_isr (void)
{
    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE

    ssp_vector_info_t * p_vector_info = NULL;
    R_SSP_VectorInfoGet(R_SSP_CurrentIrqGet(), &p_vector_info);
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) *(p_vector_info->pp_ctrl);

    /** Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(R_SSP_CurrentIrqGet());

    if((NULL != p_ctrl) && (NULL != p_ctrl->p_callback))
    {
        /** Call user callback */
        transfer_callback_args_t args;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args);
    }

    /* Transfer is disabled during the interrupt if an interrupt is requested after each block. If not all transfers
     * are complete, reenable transfer here. */
    if (HW_DMAC_BlockNumberGet(p_ctrl->p_reg) > 0U)
    {
        HW_DMAC_TransferEnableDisable(p_ctrl->p_reg, DMAC_TRANSFER_ENABLE);
    }

    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
} /* End of function dmac_int_isr */

#if DMAC_CFG_PARAM_CHECKING_ENABLE
/*******************************************************************************************************************//**
 * @brief  Checks for any input parameter error.
 *
 * @param[in]   p_ctrl          Pointer to control structure.
 * @param[in]   length          Transfer length in block mode.
 *
 * @retval SSP_SUCCESS              Input Parameters are Valid.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 * @retval SSP_ERR_UNSUPPORTED      Set transfer Mode is not allowed.
 **********************************************************************************************************************/
static ssp_err_t dma_blockreset_assert_check(dmac_instance_ctrl_t * const p_ctrl,
                                             uint16_t const length)
{
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    DMAC_ERROR_RETURN(TRANSFER_MODE_BLOCK == HW_DMAC_ModeGet(p_ctrl->p_reg), SSP_ERR_UNSUPPORTED);
    SSP_ASSERT(0 != length);

    return SSP_SUCCESS;
} /* End of function dma_blockreset_assert_check */
#endif

#if DMAC_CFG_PARAM_CHECKING_ENABLE
/*******************************************************************************************************************//**
 * @brief  Checks for any input parameter error.
 *
 * @param[in]   p_ctrl          Pointer to control structure.
 * @param[in]   p_cfg           Pointer to configuration structure. All elements of the structure must be set by user.
 *
 * @retval SSP_SUCCESS              Input Parameters are Valid.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_IN_USE           DMAC is already open; perform R_DMAC_Close() first.
 **********************************************************************************************************************/
static ssp_err_t dma_open_assert_check(dmac_instance_ctrl_t * const p_ctrl,
                                       transfer_cfg_t const * const p_cfg)
{
    SSP_ASSERT(NULL != p_ctrl);
    SSP_ASSERT(NULL != p_cfg);
    SSP_ASSERT(NULL != p_cfg->p_info);
    SSP_ASSERT(NULL != p_cfg->p_extend);

    if (TRANSFER_MODE_NORMAL != p_cfg->p_info->mode)
    {
        SSP_ASSERT(p_cfg->p_info->length <= DMAC_REPEAT_BLOCK_MAX_LENGTH);
    }

    DMAC_ERROR_RETURN(p_ctrl->id != DMAC_ID, SSP_ERR_IN_USE);

    return SSP_SUCCESS;
} /* End of function dma_open_assert_check */
#endif
/*******************************************************************************************************************//**
 * @brief  Configure the DMA Transfer Mode and Activation Source.
 *
 * @param[in]   p_cfg           Pointer to configuration structure. All elements of the structure must be set by user.
 * @param[in]   p_dmac_regs     Pointer to base address of DMAC register
 * @param[in]   p_ctrl          Pointer to control structure.

**********************************************************************************************************************/
static void dma_transfer_config(transfer_cfg_t const * const p_cfg,
                                R_DMAC0_Type * const         p_dmac_regs,
                                dmac_instance_ctrl_t * const p_ctrl)
{
    if ((ELC_EVENT_ELC_SOFTWARE_EVENT_0 == p_cfg->activation_source) ||
            (ELC_EVENT_ELC_SOFTWARE_EVENT_1 == p_cfg->activation_source))
    {
        HW_DMAC_SoftwareStartAutoClear(p_dmac_regs, TRANSFER_START_MODE_REPEAT);
        HW_DMAC_SoftwareStop(p_dmac_regs);
        HW_DMAC_TransferRequestSourceSet(p_dmac_regs, DMAC_TRANSFER_REQUEST_SOURCE_SOFTWARE);
    }
    else
    {
        HW_DMAC_TransferRequestSourceSet(p_dmac_regs, DMAC_TRANSFER_REQUEST_SOURCE_INTERRUPT);
    }

    HW_DMAC_TransferSizeSet(p_dmac_regs, p_cfg->p_info->size);
    HW_DMAC_RepeatAreaSet(p_dmac_regs, p_cfg->p_info->repeat_area);
    HW_DMAC_ModeSet(p_dmac_regs, p_cfg->p_info->mode);
    HW_DMAC_SrcStartAddrSet(p_dmac_regs, p_cfg->p_info->p_src);
    HW_DMAC_DestStartAddrSet(p_dmac_regs, p_cfg->p_info->p_dest);
    HW_DMAC_TransferNumberSet(p_dmac_regs, p_cfg->p_info->length);
    if (TRANSFER_MODE_NORMAL == p_cfg->p_info->mode)
    {
        HW_DMAC_TransferReloadSet(p_dmac_regs, 0);
    }
    else
    {
        HW_DMAC_TransferReloadSet(p_dmac_regs, p_cfg->p_info->length);
        HW_DMAC_BlockNumberSet(p_dmac_regs, p_cfg->p_info->num_blocks);
    }

    /** If p_callback is selected, enable interrupts and store the p_callback in an array for access by ISR. */
    if (NULL != p_cfg->p_callback)
    {
        HW_DMAC_ICUInterruptClear(p_ctrl->irq);
        HW_DMAC_TransferEndInterruptClear(p_dmac_regs);
        NVIC_ClearPendingIRQ(p_ctrl->irq);
        NVIC_EnableIRQ(p_ctrl->irq);
        HW_DMAC_TransferEndInterruptEnable(p_dmac_regs);
        HW_DMAC_EachInterruptEnable(p_dmac_regs, p_cfg->p_info->irq);
        p_ctrl->p_callback = p_cfg->p_callback;
        p_ctrl->p_context  = p_cfg->p_context;
    }
    else
    {
        HW_DMAC_TransferEndInterruptDisable(p_dmac_regs);
        HW_DMAC_EachInterruptEnable(p_dmac_regs, TRANSFER_IRQ_END);
    }
} /* End of function dma_transfer_config */

#if DMAC_CFG_PARAM_CHECKING_ENABLE
/*******************************************************************************************************************//**
 * @brief  Checks for any input parameter error.
 *
 * @param[in]   p_ctrl                  Pointer to control structure.
 * @param[in]   num_transfers           Number of transfers.
 *
 * @retval SSP_SUCCESS              Input Parameters are Valid.
 * @retval SSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval SSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
static ssp_err_t dma_reset_assert_check(dmac_instance_ctrl_t * const p_ctrl,
                                        uint16_t const num_transfers)
{
    SSP_ASSERT(NULL != p_ctrl);
    DMAC_ERROR_RETURN(p_ctrl->id == DMAC_ID, SSP_ERR_NOT_OPEN);
    SSP_ASSERT(NULL != p_ctrl->p_reg);

    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;
    if ((TRANSFER_MODE_NORMAL == HW_DMAC_ModeGet(p_dmac_regs)))
    {
        SSP_ASSERT(0 != num_transfers);
    }

    return SSP_SUCCESS;
}/* End of function dma_reset_assert_check */
#endif

#if DMAC_CFG_PARAM_CHECKING_ENABLE
/*******************************************************************************************************************//**
 * Alignment checking for source and destination pointers.
 *
 * @param[in]   p_src                  Pointer to transfer source
 * @param[in]   p_dest                 Pointer to transfer destination
 * @param[in]   size                   Number of bytes per transfer
 *
 * @retval      SSP_SUCCESS            Alignment on source and destination pointers is valid.
 * @retval      SSP_ERR_ASSERTION      Alignment on source and destination pointers is invalid.
 **********************************************************************************************************************/
static ssp_err_t r_dmac_enable_alignment_check(void const * p_src, void const * p_dest, transfer_size_t size)
{
    if (TRANSFER_SIZE_2_BYTE == size)
    {
        SSP_ASSERT(0U == ((uint32_t) p_dest & DMAC_PRV_MASK_ALIGN_2_BYTES));
        SSP_ASSERT(0U == ((uint32_t) p_src & DMAC_PRV_MASK_ALIGN_2_BYTES));
    }
    if (TRANSFER_SIZE_4_BYTE == size)
    {
        SSP_ASSERT(0U == ((uint32_t) p_dest & DMAC_PRV_MASK_ALIGN_4_BYTES));
        SSP_ASSERT(0U == ((uint32_t) p_src & DMAC_PRV_MASK_ALIGN_4_BYTES));
    }

    return SSP_SUCCESS;
}
#endif

/*******************************************************************************************************************//**
 * Clearing the IR flag in DELSRn register
 *
 * @param[in]   p_ctrl                  Pointer to control structure
 **********************************************************************************************************************/
static void dma_ir_flag_clear(dmac_instance_ctrl_t * const p_ctrl)
{
	if(1U == p_ctrl->ir_flag_stat)
	{
		HW_ICU_DmacClear(gp_icu_regs, p_ctrl->channel);
	}
}/* End of function dma_ir_flag_clear */

/*******************************************************************************************************************//**
 * Setting the offset value in DMOFR register.
 *
 * @param[in]   p_ctrl                  Pointer to control structure
 * @param[in]   p_cfg                   Pointer to configuration structure. All elements of the structure must be set by user.

 * @retval SSP_SUCCESS                  Valid offset value is set in DMOFR register.
 * @retval SSP_ERR_INVALID_SIZE         Invalid offset value.
 **********************************************************************************************************************/
static ssp_err_t dma_offset_value_set (dmac_instance_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg)
{
    int32_t offset_value;
    ssp_err_t result = SSP_SUCCESS;
    R_DMAC0_Type * p_dmac_regs = (R_DMAC0_Type *) p_ctrl->p_reg;

    /** If the offset value is not equal to zero and greater than or equal to transfer size,
     * set the offset value in DMOFR Register. */
    if((0U != p_ctrl->offset_byte))
    {
        /* If the offset value is negative, convert the negative value into positive value and store it
         * to verify whether offset value is less than the transfer size. */
        if(p_ctrl->offset_byte < 0)
        {
            offset_value = (int32_t)((-1L) * p_ctrl->offset_byte);
        }
        else
        {
            offset_value = p_ctrl->offset_byte;
        }

        /* If the offset value is greater than or equal to transfer size, set the offset value in
         * DMOFR register. */
        if(offset_value >= p_cfg->p_info->size)
        {
            HW_DMAC_OffsetSet(p_dmac_regs, p_ctrl->offset_byte);
        }
        else
        {
            result = SSP_ERR_INVALID_SIZE;
        }
    }
    return result;
}/* End of function dma_offset_value_set */

/*******************************************************************************************************************//**
 * Get the interrupt event info, interrupt vector and set the NVIC priority for DMAC.
 *
 * @param[in]   p_ctrl                  Pointer to control structure
 * @param[in]   p_cfg                   Pointer to configuration structure. All elements of the structure must be set by user.
 * @param[in]   feature                 Pointer to feature structure.

 * @retval SSP_SUCCESS                  IRQ vector is valid and available in system.
 * @retval SSP_ERR_IRQ_BSP_DISABLED     The IRQ associated with the activation source is not enabled in the BSP.
 **********************************************************************************************************************/
static ssp_err_t dma_vector_info_get (dmac_instance_ctrl_t * const p_ctrl,
                                       transfer_cfg_t const * const p_cfg,
                                       ssp_feature_t * feature)
{
    ssp_err_t err = SSP_SUCCESS;
    p_ctrl->irq = SSP_INVALID_VECTOR;
    if (NULL != p_cfg->p_callback)
    {
        ssp_vector_info_t * p_vector_info;
        fmi_event_info_t event_info = {(IRQn_Type) 0U};
        err = g_fmi_on_fmi.eventInfoGet(feature, SSP_SIGNAL_DMAC_INT, &event_info);
        p_ctrl->irq = event_info.irq;
        DMAC_ERROR_RETURN(SSP_INVALID_VECTOR != p_ctrl->irq, SSP_ERR_IRQ_BSP_DISABLED);
        R_SSP_VectorInfoGet(p_ctrl->irq, &p_vector_info);
        NVIC_SetPriority(p_ctrl->irq, p_cfg->irq_ipl);
        *(p_vector_info->pp_ctrl) = p_ctrl;
    }
    return err;
}/* End of function dmac_vector_info_get */
