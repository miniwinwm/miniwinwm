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
#include "ux_dcd_synergy.h"
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
/*    ux_dcd_synergy_current_endpoint_change              PORTABLE C      */
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
/*    dcd_synergy                        Pointer to synergy controller    */ 
/*    ed                                 Register to the ed               */ 
/*    direction                          Direction to switch              */ 
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
/*    SYNERGY Controller Driver                                           */
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
 * @brief  This function configures the FIFO as per the request specified in endpoint descriptor.
 *
 * @param[in]  dcd_synergy  Pointer to a DCD control block
 * @param[in]  ed           Pointer to a physical Endpoint(ED) control block
 * @param[in]  direction    Endpoint direction
 **********************************************************************************************************************/
VOID  ux_dcd_synergy_current_endpoint_change(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, ULONG direction)
{
    ULONG   synergy_register;

    /* Select the fifo.  */
    switch (ed -> ux_dcd_synergy_ed_fifo_index)
    {
        /* fall through for C0 and C1 pipes as both are handled similarly.*/
        case UX_SYNERGY_DCD_FIFO_C0:
        case UX_SYNERGY_DCD_FIFO_C1:
            /* Set the current endpoint index (pipe) in CFIFOSEL register.  */
            /* Read the current CFIFOSEL register.  */
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL);

            /* Clear the PIPEMASK, MBW field, the reading/writing width and the previous endpoint index.*/
            synergy_register &= ~((ULONG)(UX_SYNERGY_DCD_CFIFOSEL_CURPIPE_MASK | UX_SYNERGY_DCD_CFIFOSEL_MBW_MASK));

            /* Add the current direction and the new endpoint index.  */
            synergy_register |= ed->ux_dcd_synergy_ed_index;

            /* Write back the register.  */
            ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL, (USHORT) synergy_register);
            break;

        case UX_SYNERGY_DCD_FIFO_D0:

            /* Set the current endpoint index (pipe) in the D0FIFOSEL register.  */
            /* Read the current CFIFOSEL register.  */
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_D0FIFOSEL);

            /* Clear the PIPEMASK, MBW field, the reading/writing width and the previous endpoint index.*/
            synergy_register &= ~((ULONG)(UX_SYNERGY_DCD_CFIFOSEL_CURPIPE_MASK | UX_SYNERGY_DCD_CFIFOSEL_MBW_MASK));

            /* Add the current direction and the new endpoint index.  */
            synergy_register |= ed->ux_dcd_synergy_ed_index;

            /* Write back the register.  */
            ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_D0FIFOSEL, (USHORT) synergy_register);
            break;

        case UX_SYNERGY_DCD_FIFO_D1:

            /* Set the current endpoint index (pipe) in the D1FIFOSEL register.  */
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_D1FIFOSEL);

            /* Clear the PIPEMASK, MBW field, the reading/writing width and the previous endpoint index.*/
            synergy_register &= ~((ULONG)(UX_SYNERGY_DCD_CFIFOSEL_CURPIPE_MASK | UX_SYNERGY_DCD_CFIFOSEL_MBW_MASK));

            /* Add the current direction and the new endpoint index.  */
            synergy_register |= ed->ux_dcd_synergy_ed_index;

            /* Set the current endpoint index (pipe) in the D1FIFOSEL register.  */
            ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_D1FIFOSEL, (USHORT) synergy_register);
            break;        

        case UX_SYNERGY_DCD_FIFO_CD:

            /* Read the current CFIFOSEL register.  */
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL);

            /* Clear the ISEL field, the reading/writing width and the previous endpoint index.  */
            synergy_register &= ~((ULONG)(UX_SYNERGY_DCD_CFIFOSEL_CURPIPE_MASK | UX_SYNERGY_DCD_CFIFOSEL_ISEL |
                                          UX_SYNERGY_DCD_CFIFOSEL_MBW_MASK));

            /* Add the current direction and the new endpoint index.  */
            synergy_register |= (ed -> ux_dcd_synergy_ed_index | direction);

            /* Write back the register.  */
            ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL, (USHORT)synergy_register);

            break;

        default:
            break;
    }
    
    /*  we need to wait at least 450 ns now.  
       Reading a register takes 60 ns, so do this 8 times. */
        
    for (int32_t loop_index = 0; loop_index < 4; loop_index++)
    {
        synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_SYSCFG);
        synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_SYSSTS);
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
