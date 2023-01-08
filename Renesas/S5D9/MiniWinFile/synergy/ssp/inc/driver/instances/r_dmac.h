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
 * File Name    : r_dmac.h
 * Description  : DMAC extension of transfer interface.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup HAL_Library
 * @defgroup DMAC DMAC
 * @brief DMA Controller (DMAC).
 *
 * @section DMAC_SUMMARY Summary
 * Extends the @ref TRANSFER_API.
 *
 * The Direct Memory Access (DMA) Controller allows data transfers to occur in place of or in addition to any interrupt. It
 * also supports data transfers using software start.
 *
 * @note The transfer length is limited to 1024 (10 bits) in ::TRANSFER_MODE_BLOCK and ::TRANSFER_MODE_REPEAT.
 * @note This driver supports only ::TRANSFER_IRQ_END from transfer_irq_t.
 * @{
 **********************************************************************************************************************/

#ifndef R_DMAC_H
#define R_DMAC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DMAC_CODE_VERSION_MAJOR (2U)
#define DMAC_CODE_VERSION_MINOR (0U)

/** Length limited to 1024 transfers for repeat and block mode */
#define DMAC_REPEAT_BLOCK_MAX_LENGTH (0x400)

/** Length limited to 65535 transfers for normal mode */
#define DMAC_NORMAL_MAX_LENGTH (0xFFFF)

/** Reserved memory area for dummy write transfer as per Hardware user manual */
#define DUMMY_ADDRESS ((void *) 0x40005500)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Control block used by driver. DO NOT INITIALIZE - this structure will be initialized in transfer_api_t::open. */
typedef struct st_dmac_instance_ctrl
{
    uint32_t     id;           ///< Driver ID
    elc_event_t  trigger;      ///< Transfer activation event.  Matches event returned by transfer_api_t::infoGet.
    IRQn_Type    irq;          ///< Transfer activation IRQ.
    uint8_t      channel;      ///< Channel number
    uint8_t      ir_flag_stat; ///< Status of IR bit in DELSR register
    int32_t      offset_byte;  ///< Value of offset in bytes for offset addressing mode.

    /** Callback for transfer end interrupt. */
    void (* p_callback)(transfer_callback_args_t * cb_data);

    /** Placeholder for user data.  Passed to the user p_callback in ::transfer_callback_args_t. */
    void const * p_context;

    /** Pointer to base register. */
    void       * p_reg;
} dmac_instance_ctrl_t;

/** DMAC transfer configuration extension. This extension is required. */
typedef struct st_transfer_on_dmac_cfg
{
    uint8_t      channel;    ///< Channel number, does not apply to all HAL drivers.
    int32_t     offset_byte;///< Value of offset in bytes for offset addressing mode.
} transfer_on_dmac_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const transfer_api_t g_transfer_on_dmac;
/** @endcond */

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* R_DMAC_H */

/*******************************************************************************************************************//**
 * @} (end defgroup DMAC)
 **********************************************************************************************************************/
