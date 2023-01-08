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
#include "ux_utility.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_asynch_queue_process_sign            PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function process the SIGN event. Timeout on SETUP transfer     */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                    Pointer to Synergy controller        */
/*    ed                             Endpoint on which the event happened */
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
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
 * @brief  This function process the Setup transaction Error Interrupt.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to an Endpoint control block
 **********************************************************************************************************************/
VOID  ux_hcd_synergy_asynch_queue_process_sign(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED  *ed)
{
    (void) hcd_synergy;

    UX_SYNERGY_TD * td;
    UX_SYNERGY_TD * next_td;
    UX_TRANSFER   * transfer_request;

    /* Get the TD associated with this transfer. */
    td = ed -> ux_synergy_ed_head_td;
    
    /* Ensure the interrupt was valid.  */
    if ((td -> ux_synergy_td_status & UX_SYNERGY_TD_ACK_PENDING) == 0UL)
    {
        return;
    }
 
    /* Get the transfer request associated with the TD.  */                          
    transfer_request =  td -> ux_synergy_td_transfer_request;
                
    /* Remove all the TDs attached.  */
    while (td != ed -> ux_synergy_ed_tail_td)
    {
        /* Memorize this TD.  */
        next_td =  td -> ux_synergy_td_next_td;                     

        /* Take it out of the chain.  */
        ed -> ux_synergy_ed_head_td =  next_td;                     

        /* We can now free the TD.  */
        td -> ux_synergy_td_status =  (ULONG)UX_UNUSED;

        /* Next TD.  */
        td =  next_td;
    }
    
    /* Set the transfer code to NO ANSWER.  */
    transfer_request -> ux_transfer_request_completion_code =  (UINT)UX_TRANSFER_NO_ANSWER;

    /* Check if there is a callback.  */
    if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
    {
        /* Yes, so execute it.  */
        transfer_request -> ux_transfer_request_completion_function(transfer_request);
    }

    /* If trace is enabled, insert this event into the trace buffer.  */
    UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_TRANSFER_NO_ANSWER, transfer_request, 0, 0, UX_TRACE_ERRORS, 0, 0)

    /* Wake up the thread waiting for this event to complete.  */
    _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);               
            
    /* Return to caller.  */
    return;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

