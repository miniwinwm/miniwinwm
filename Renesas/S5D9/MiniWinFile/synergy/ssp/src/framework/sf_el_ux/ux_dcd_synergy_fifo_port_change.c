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
/*    ux_dcd_synergy_fifo_port_change                     PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function change the port of the FIFO                           */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    dcd_synergy                    Pointer to synergy controller        */ 
/*    ed                                    Register to the ed            */ 
/*    direction                             Direction to switch           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    fifo_access_status                                                  */ 
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
 * @brief  This function configures the FIFO port.
 *
 * @param[in]  dcd_synergy        Pointer to a DCD control block
 * @param[in]  ed                 Pointer to a physical Endpoint(ED) control block
 * @param[in]  direction          Direction to switch
 *
 * @retval UX_ERROR               Unable to change fifo port.
 * @return synergy_register       Current endpoint index(pipe)
 **********************************************************************************************************************/
ULONG  ux_dcd_synergy_fifo_port_change(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, ULONG direction)
{
    ULONG   synergy_register;
    ULONG    loop_index = 0;
    /* Set the current fifo port.  */
    ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, direction);

    /* it may take several tries to perform this function.  */
    while( loop_index < UX_SYNERGY_DCD_FIFO_MAX_TRY )
    {
        loop_index++;
        /* Select the fifo.  */
        switch (ed -> ux_dcd_synergy_ed_fifo_index)
        {
        case UX_SYNERGY_DCD_FIFO_D0:
            /* Read D0FIFOCTR register to find the FRDY bit is ready or not..  */
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR);
            break;

        case UX_SYNERGY_DCD_FIFO_D1:
            /* Read D1FIFOCTR register to find the FRDY bit is ready or not..  */
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_D1FIFOCTR);
            break;
            /* fall through for CD, C0 and C1 pipes as both are handled similarly.*/
        case UX_SYNERGY_DCD_FIFO_CD:
        case UX_SYNERGY_DCD_FIFO_C0:
        case UX_SYNERGY_DCD_FIFO_C1:
            /* Read CFIFOCTR register to find the FRDY bit is ready or not.  */
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR);
            break;

        default:
            /* We should never get here.  */
            synergy_register = 0UL;

        }

        /* Now check the status of the FRDY bit.  */
        if ((synergy_register & UX_SYNERGY_DCD_FIFOCTR_FRDY) == UX_SYNERGY_DCD_FIFOCTR_FRDY)
        {
            return (synergy_register);
        }
    }
    /* Return to caller with an error. */
    return (ULONG)UX_ERROR;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

