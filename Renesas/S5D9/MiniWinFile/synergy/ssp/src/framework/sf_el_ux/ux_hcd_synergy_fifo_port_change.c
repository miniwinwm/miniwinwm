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
/*    ux_hcd_synergy_fifo_port_change                     PORTABLE C      */
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
/*    hcd_synergy                           Pointer to Synergy controller */
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
 * @brief  This function change the port of the FIFO.
 *
 * @param[in]  hcd_synergy : Pointer to a HCD control block
 * @param[in]  ed          : Pointer to Synergy ED structure
 * @param[in]  direction   : Direction to transfer
 *
 * @retval synergy_register      Content of FIFO control register.
 * @retval UX_ERROR              Port not changed successfully or unable to access FIFO.
 **********************************************************************************************************************/
ULONG  ux_hcd_synergy_fifo_port_change(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG direction)
{
    ULONG   loop_index;
    ULONG   synergy_register;

    /* Set the current fifo port.  */
    ux_hcd_synergy_current_endpoint_change(hcd_synergy, ed, direction);

    /* it make take several tries to perform this function.  */
    for (loop_index = 0UL; loop_index < 4UL; loop_index++)
    {
        /* Select the fifo.  */
        switch (ed -> ux_synergy_fifo_index)
        {
            case UX_SYNERGY_HC_FIFO_D0       :
                
                /* Read the current endpoint index (pipe) in the D0FIFOSEL register.  */
                synergy_register =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_D0FIFOCTR);
                break;        
            
            case UX_SYNERGY_HC_FIFO_D1       :
            
                /* Read the current endpoint index (pipe) in the D1FIFOSEL register.  */
                synergy_register =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_D1FIFOCTR);
                break;        
    
            case UX_SYNERGY_HC_FIFO_C        :
    
                /* Set the current endpoint index (pipe) in the CFIFOSEL register.  */
                synergy_register =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR);
                break;
    
            default                     :

                /* We should never get here.  */
                synergy_register = 0UL;
        }
        
        /* Now check the status of the FRDY bit.  */
        if ((synergy_register & UX_SYNERGY_HC_FIFOCTR_FRDY) == UX_SYNERGY_HC_FIFOCTR_FRDY)
        {
            return (synergy_register);
        }
    }

    /* Return to caller with an error. */
    return (UINT)UX_ERROR;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

