/***********************************************************************************************************************
 * Copyright [2017-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
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

#include "bsp_api.h"

#include "ux_api.h"
#include "ux_hcd_synergy.h"

void usbfs_int_isr (void);
void usbfs_resume_isr (void);
void ux_dcd_synergy_interrupt_handler(VOID);

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief All the USBFS interrupts are handled by this ISR.
 **********************************************************************************************************************/
void usbfs_int_isr (void)
{
    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE

    R_BSP_IrqStatusClear(R_SSP_CurrentIrqGet());

#if !defined(UX_SYSTEM_DEVICE_ONLY)
    _Bool host = false;
    UINT hcd_index = 0U;
#if UX_MAX_HCD > 1
    /** If there is more than one hcd, we need to parse the controller driver table, and call the
     *  appropriate interrupt handler.  */
    for (hcd_index = 0U; hcd_index < (UINT)(_ux_system_host->ux_system_host_max_hcd); hcd_index++)
    {
#endif
        if (R_USBFS_BASE == _ux_system_host->ux_system_host_hcd_array[hcd_index].ux_hcd_io)
        {
            ux_hcd_synergy_interrupt_handler(hcd_index);
            host = true;
#if UX_MAX_HCD > 1
            break;
#endif
        }
#if UX_MAX_HCD > 1
    }
#endif
    if (false == host)
    {
        ux_dcd_synergy_interrupt_handler();
    }

#else /* if !defined(UX_SYSTEM_DEVICE_ONLY) */
    ux_dcd_synergy_interrupt_handler();
#endif /* if !defined(UX_SYSTEM_DEVICE_ONLY) */

    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * @brief VBINT (VBUS interrupt), RESM (Resume interrupt), OVRCR (Over current input), BCHG (Change interrupt),
 *        and PDDETINT0 (Bus change interrupt) fire this ISR. This is only used for canceling following standby modes.
 *        * Canceling the software standby mode
 *        * Canceling deep standby mode
 **********************************************************************************************************************/
void usbfs_resume_isr (void)
{
    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE

    R_BSP_IrqStatusClear(R_SSP_CurrentIrqGet());

    /* Reserved. */

    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

