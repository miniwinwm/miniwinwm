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

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_buffer_notready_interrupt            PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function enable or disable the NRDY interrupt for the pipe     */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*    ed                                    Endpoint                      */
/*    flag                                  Enable or Disable             */
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    none                                                                */ 
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
 * @brief  This function enable or disable the NRDY(Not Ready) interrupt for the pipe.
 *
 * @param[in]  hcd_synergy : Pointer to a HCD control block
 * @param[in]  ed          : Pointer to physical Endpoint(ED) control block
 * @param[in]  flag        : Check whether DCD synergy is enable or disable.
 **********************************************************************************************************************/
VOID  ux_hcd_synergy_buffer_notready_interrupt(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG flag)
{
    ULONG       synergy_register;
    ULONG       synergy_brdy_register;

    /* Read the Interrupt Enable register 0.  */
    synergy_register = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_INTENB0);

    /* Reset the BEMPE, NRDYE, BRDYE bits.  */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_INTENB0,
            (USHORT)(UX_SYNERGY_HC_INTENB0_BEMPE | UX_SYNERGY_HC_INTENB0_NRDYE | UX_SYNERGY_HC_INTENB0_BRDYE));

    /* Read the NRDY register.  */
    synergy_brdy_register = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_NRDYENB);

    /* Enable or Disable ?  */
    if (flag == (ULONG)UX_SYNERGY_ENABLE)
    {
        /* Set the appropriate endpoint number.  */
        synergy_brdy_register |= (ULONG)(1UL << ed -> ux_synergy_pipe_index);
    }
    else
    {
        /* Reset the appropriate endpoint number.  */
        synergy_brdy_register &= (ULONG) ~(1UL << ed -> ux_synergy_pipe_index);
    }

    /* Write the NRDY register.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_NRDYENB, (USHORT)synergy_brdy_register);

    /* Restore the INTENB0 register.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_INTENB0, (USHORT)synergy_register);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

