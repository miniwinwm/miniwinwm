/*LDRA_INSPECTED 119 S */
/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

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

/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** USBX Component                                                        */ 
/**                                                                       */
/**   SYNERGY Controller Driver                                           */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_hcd_synergy.h"
#include "ux_system.h"
#include "ux_utility.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_fifo_port_change                    PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function change the endpoint in the FIFO                       */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*    ed                                    Register to the ed            */ 
/*    direction                             Direction to switch           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Synergy Controller Driver                                           */
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  10-10-2012     TCRG                     Initial Version 5.6           */ 
/*                                                                        */ 
/**************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function change the endpoint in the FIFO.
 *
 * @param[in]  hcd_synergy : Pointer to a HCD control block
 * @param[in]  ed          : Pointer to Synergy ED structure
 * @param[in]  direction   : Direction to transfer
 **********************************************************************************************************************/
VOID  ux_hcd_synergy_current_endpoint_change(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG direction)
{
    ULONG   synergy_register;

    /* Select the fifo.  */
    switch (ed -> ux_synergy_fifo_index)
    {
        case UX_SYNERGY_HC_FIFO_D0       :

            /* Read the current D0FIFOSEL register.  */
            synergy_register = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_D0FIFOSEL);

            /*Clear the reading/writing width and the previous endpoint index */
            synergy_register &= (ULONG) (~((ULONG)UX_SYNERGY_HC_DFIFOSEL_CURPIPE_MASK |
                    (ULONG)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK));

            /* Set the current endpoint index (pipe) in the D0FIFOSEL register.  */
            synergy_register |= ((USHORT)ed -> ux_synergy_pipe_index | direction);

            /* Write back the register.  */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_D0FIFOSEL,(USHORT)synergy_register);
            break;

        case UX_SYNERGY_HC_FIFO_D1       :

            /* Read the current D1FIFOSEL register.  */
            synergy_register =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_D1FIFOSEL);

            synergy_register &=(ULONG) (~((ULONG)UX_SYNERGY_HC_DFIFOSEL_CURPIPE_MASK |
                    (ULONG)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK));

            /* Set the current endpoint index (pipe) in the D0FIFOSEL register.  */
            synergy_register |= ((USHORT)ed -> ux_synergy_pipe_index | direction);

            /* Write back the register.  */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_D1FIFOSEL,(USHORT)synergy_register);

            break;

        case UX_SYNERGY_HC_FIFO_C        :

            /* Read the current CFIFOSEL register.  */
            synergy_register =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_CFIFOSEL);

            /* Clear the ISEL field, the reading/writing width and the previous endpoint index.  */
            synergy_register &= ~(UX_SYNERGY_HC_CFIFOSEL_CURPIPE_MASK | UX_SYNERGY_HC_CFIFOSEL_ISEL |
                    UX_SYNERGY_HC_CFIFOSEL_MBW_MASK);

            /* Add the current direction and the new endpoint index.  */
            synergy_register |= (ed -> ux_synergy_pipe_index | direction);

            /* Write back the register.  */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_CFIFOSEL, (USHORT)synergy_register);

            break;

        default                     :
            break;
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/


