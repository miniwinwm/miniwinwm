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
#include "ux_host_stack.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_periodic_endpoint_destroy            PORTABLE C      */ 
/*                                                           5.7          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function will destroy an interrupt or isochronous endpoint.   */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */ 
/*    endpoint                              Pointer to endpoint           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
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
/*  10-10-2012     TCRG                     Initial Version 5.7           */ 
/*                                                                        */ 
/**************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function will destroy an isochronous endpoint.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  endpoint    : Pointer to an Endpoint control block
 *
 * @retval UX_SUCCESS                    Isochronous endpoint is destroyed successfully.
 * @retval UX_ENDPOINT_HANDLE_UNKNOWN    Physical endpoint has not been initialized properly.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_periodic_endpoint_destroy(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint)
{
    UX_SYNERGY_ED      * ed;
    UX_SYNERGY_ED      * previous_ed;
    UX_SYNERGY_ED      * next_ed;
    UX_SYNERGY_TD      * tail_td;
    UX_SYNERGY_TD      * head_td;
    
    /* From the endpoint container fetch the synergy ED descriptor.  */
    ed =  (UX_SYNERGY_ED*) endpoint -> ux_endpoint_ed;

    /* Check if this physical endpoint has been initialized properly!  */
    if (ed == UX_NULL)
    {

        /* Error trap. */
        _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_THREAD, (UINT)UX_SYSTEM_CONTEXT_HCD, (UINT)UX_ENDPOINT_HANDLE_UNKNOWN);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_ENDPOINT_HANDLE_UNKNOWN, endpoint, 0, 0, UX_TRACE_ERRORS, 0, 0)

        return (UINT)UX_ENDPOINT_HANDLE_UNKNOWN;
    }

    /* The endpoint may be active. If so, set the skip bit.  */
    ed -> ux_synergy_ed_status |=  UX_SYNERGY_ED_SKIP;
    
    /* Wait for the controller to finish the current frame processing.  */
    _ux_host_stack_delay_ms(1UL);

    /* Get the previous ED in the list for this ED.  */
    previous_ed =  ed -> ux_synergy_ed_previous_ed;

    /* Get the next ED in the list for this ED.  */
    next_ed =  ed -> ux_synergy_ed_next_ed;

    /* The previous ED points now to the ED after the ED we are removing.  */
    previous_ed -> ux_synergy_ed_next_ed =  next_ed;

    if ((endpoint -> ux_endpoint_descriptor.bmAttributes & (ULONG)UX_MASK_ENDPOINT_TYPE)
                                                                    == (ULONG)UX_ISOCHRONOUS_ENDPOINT)
    {

        /* If the previous ED is NULL, we are at trying to remove the head ED.  */
        if (previous_ed == UX_NULL)
        {
            /* Store the new endpoint in the Control list.  */
            hcd_synergy -> ux_hcd_synergy_iso_head_ed =  next_ed;
        }

        /* Reset the current ed processed and force the scheduler to restart from the beginning
           of the list.  */
        hcd_synergy -> ux_hcd_synergy_iso_current_ed =  UX_NULL;
    }

    /* There may not be any next endpoint.  But if there is one, link it
       to the previous ED. */
    if (next_ed != UX_NULL)
    {
        /* Update the previous ED pointer in the next ED.  */
        next_ed -> ux_synergy_ed_previous_ed =  previous_ed;
    }

    /* Remove all the tds from this ED and leave the head and tail pointing to the dummy TD.  */
    head_td =  ed -> ux_synergy_ed_head_td;
    tail_td =  ed -> ux_synergy_ed_tail_td;

    /* Free all tds attached to the ED.  */
    while (head_td != tail_td)
    {
        /* Mark the current head TD as free. */
        head_td -> ux_synergy_td_status = (ULONG)UX_UNUSED;

        /* Update the head TD with the next TD.  */
        ed -> ux_synergy_ed_head_td =  head_td -> ux_synergy_td_next_td;

        /* Now the new head_td is the next TD in the chain.  */
        head_td =  ed -> ux_synergy_ed_head_td;
    }

    /* We need to free the dummy TD that was attached to the ED.  */
    tail_td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
	
	 /* Select pipe.  */
    ux_hcd_synergy_register_write( hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)ed -> ux_synergy_pipe_index);

    /* Disable endpoint in the CFG register.  */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PIPECFG, (USHORT)UX_SYNERGY_HC_PIPECFG_TYPE_MASK);

    /* Now we can safely make the ED free.  */
    ed -> ux_synergy_ed_status = (ULONG)UX_UNUSED;

    /* Decrement the number of interrupt endpoints active. When the counter
       reaches 0, the periodic scheduler will be turned off.  */
    hcd_synergy -> ux_hcd_synergy_periodic_scheduler_active--;

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
