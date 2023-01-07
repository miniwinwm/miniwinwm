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
* File Name    : r_flash_hp.h
* Description  : HLD Interface for the High-Performance Flash peripheral on SC32 MCUs.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#ifndef R_FLASH_HP_H
#define R_FLASH_HP_H

#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

#include "r_flash_api.h"
#include "r_flash_cfg.h"

/*******************************************************************************************************************//**
 * @ingroup HAL_Library
 * @defgroup FLASH_HP High-performance Flash
 * @brief Driver for the High-performance Flash Memory (S7G2 and S5D9).
 *
 * This module supports the Flash interface for the High Performance FLASH peripheral.
 * @{
 **********************************************************************************************************************/


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define FLASH_HP_CODE_VERSION_MAJOR   (2U)
#define FLASH_HP_CODE_VERSION_MINOR   (0U)

/* S5D9, S5D5 and S5D3 MCUs uses RV40F Phase 2 Flash technology. */
/* This macro will eventually be migrated to bsp_feature.h. */
#if defined(BSP_MCU_GROUP_S5D9) || defined(BSP_MCU_GROUP_S5D5) || defined(BSP_MCU_GROUP_S5D3)
#define FLASH_HP_VERSION_PHASE_2
#endif

/* If Code Flash programming is enabled, then all API functions must execute out of RAM. */
#if (FLASH_CFG_PARAM_CODE_FLASH_PROGRAMMING_ENABLE == 1)
#if defined(__ICCARM__)
#pragma section=".code_in_ram"
#endif
#define PLACE_IN_RAM_SECTION            BSP_PLACE_IN_SECTION_V2(".code_in_ram")
#else
#define PLACE_IN_RAM_SECTION
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/** Flash HP instance control block. DO NOT INITIALIZE. */
typedef struct st_flash_hp_instance_ctrl
{
    uint32_t opened;               ///< To check whether api has been opened or not.
    R_FACI_Type * p_reg;           ///< Base address of flash registers
    void               (*p_callback)(flash_callback_args_t *p_args);   /// User Callback function.
    bsp_cache_state_t cache_state; ///< Used to disable and then restore Flash Cache while API is open.
    IRQn_Type irq;                 ///< Flash ready interrupt number
    IRQn_Type err_irq;             ///< Flash error interrupt number
} flash_hp_instance_ctrl_t;

/**********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const flash_api_t g_flash_on_flash_hp;
/** @endcond */

/*******************************************************************************************************************//**
 * @} (end defgroup FLASH_HP)
***********************************************************************************************************************/
#if !defined(BSP_MCU_GROUP_S7G2) && !defined(FLASH_HP_VERSION_PHASE_2)
#error "r_flash_hp is not a supported module for this board type."
#endif

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif // R_FLASH_HP_H

