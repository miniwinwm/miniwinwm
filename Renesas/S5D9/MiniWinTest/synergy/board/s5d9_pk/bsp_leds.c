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
* File Name    : bsp_leds.c
* Description  : This module has information about the LEDs on this board.
***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_PK_S5D9_LEDS
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#if defined(BSP_BOARD_S5D9_PK)

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
/** Array of LED IOPORT pins. */
static const ioport_port_pin_t g_bsp_prv_leds[] =
{
    IOPORT_PORT_06_PIN_00,  ///< LED1_G
    IOPORT_PORT_06_PIN_01,  ///< LED2_R
    IOPORT_PORT_06_PIN_02,  ///< LED2_Y
};

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
/** Structure with LED information for this board. Recommended to get this information through R_BSP_LedsGet() function
 * instead of using this structure directly to remove dependency on structure name. */
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const bsp_leds_t g_bsp_leds =
{
    .led_count  = (uint16_t)(((uint16_t)sizeof(g_bsp_prv_leds) / (uint16_t)sizeof(g_bsp_prv_leds[0U]))),
    .p_leds     = &g_bsp_prv_leds[0]
};

#endif

/** @} (end addtogroup BSP_PK_S5D9_LEDS) */

