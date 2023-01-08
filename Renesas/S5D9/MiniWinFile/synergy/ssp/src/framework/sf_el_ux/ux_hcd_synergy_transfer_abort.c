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
/*    ux_hcd_synergy_transfer_abort                       PORTABLE C      */
/*                                                           5.7 SP7      */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function will abort transactions attached to a transfer       */ 
/*     request.                                                           */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */ 
/*    transfer_request                      Pointer to transfer request   */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_host_stack_delay_ms               Delay                         */ 
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
/*  06-01-2014     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.7    */ 
/*  12-15-2016     TCRG                     Modified comment(s),          */ 
/*                                            added new error trap        */
/*                                            function support,           */
/*                                            resulting in version 5.7 SP7*/ 
/*                                                                        */ 
/**************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function will abort transactions attached to a transfer request.
 *
 * @param[in]      hcd_synergy         : Pointer to a HCD control block
 * @param[in,out]  transfer_request    : Pointer to transfer request
 *
 * @retval UX_SUCCESS                    Transactions attached to transfer request are aborted successfully.
 * @retval UX_ENDPOINT_HANDLE_UNKNOWN    Endpoint is not initialized properly.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_transfer_abort(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request)
{
    (void) hcd_synergy;

    UX_ENDPOINT    * endpoint;
    UX_SYNERGY_ED  * ed;
    UX_SYNERGY_TD  * head_td;
    UX_SYNERGY_TD  * tail_td;
    ULONG            fifo_ctrl;
    ULONG            synergy_register;

TX_INTERRUPT_SAVE_AREA

    /* Get the pointer to the endpoint associated with the transfer request.  */
    endpoint =  (UX_ENDPOINT *) transfer_request -> ux_transfer_request_endpoint;
    
    /* From the endpoint container, get the address of the physical endpoint.  */
    ed =  (UX_SYNERGY_ED *) endpoint -> ux_endpoint_ed;
    
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

    /* Critical section, even ISR cannot be disrupted.  */
    TX_DISABLE

    /* Check if we are using endpoint 0.  */
    if (ed -> ux_synergy_endpoint_index == 0UL)
    {
        /* Set the current fifo port on endpoint 0.  */
        ux_hcd_synergy_current_endpoint_change(hcd_synergy, ed, (ULONG)UX_SYNERGY_HC_CFIFOSEL_ISEL);

        /* Set the BCLR flag.  */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR, (USHORT)UX_SYNERGY_HC_FIFOCTR_BCLR);
    }
    else
    {    
        /* Select pipe.  */
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)ed -> ux_synergy_pipe_index);

        /* Read PIPE CTR for current FIFO.  */
        synergy_register =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR +
                                                         ((ed -> ux_synergy_pipe_index - 1UL) * 2UL));
    
        /* Check if PID BUF on.  */
        if ((synergy_register & (ULONG)UX_SYNERGY_HC_PIPECTR_PID_MASK) == (ULONG)UX_SYNERGY_HC_PIPECTR_PIDBUF)
        {
            /* Set PID to NAK. */
            ux_hcd_synergy_register_clear(hcd_synergy,
                                          UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                          (USHORT)UX_SYNERGY_HC_DCPCTR_PID_MASK);

            /* Set ACLRM bit to 1 to clear the FIFO buffer. */
            ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR +
                    ((ed -> ux_synergy_pipe_index - 1UL) * 2UL), (USHORT)UX_SYNERGY_HC_PIPECTR_ACLRM);

            /* Now reset the ACLRM bit. */
            ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                            (USHORT)UX_SYNERGY_HC_PIPECTR_ACLRM);

            /* Set the current fifo port.  */
            ux_hcd_synergy_current_endpoint_change(hcd_synergy, ed, 0UL);

            /* We need to select the FIFO registers.  */
            switch (ed -> ux_synergy_fifo_index)
            {
                case (ULONG)UX_SYNERGY_HC_FIFO_D0 :

                    /* Set fifo_sel and fifo_addr fields to FIFO_D0 */
                    fifo_ctrl =  UX_SYNERGY_HC_D0FIFOCTR;
                    break; 

                case (ULONG)UX_SYNERGY_HC_FIFO_D1 :

                    /* Set fifo_sel and fifo_addr fields to FIFO_D1 */
                    fifo_ctrl =  UX_SYNERGY_HC_D1FIFOCTR;
                    break;

                default: /* UX_SYNERGY_HC_FIFO_C */

                    /* Set fifo_sel and fifo_addr fields to FIFO_C */
                    fifo_ctrl =  UX_SYNERGY_HC_CFIFOCTR;
                    break;
            }

            /* Read FIFO CTR for current FIFO.  */
            synergy_register =  ux_hcd_synergy_register_read(hcd_synergy, fifo_ctrl);

            /* Now check the status of the FRDY bit.  */
            if ((synergy_register & (ULONG)UX_SYNERGY_HC_FIFOCTR_FRDY) == (ULONG)UX_SYNERGY_HC_FIFOCTR_FRDY)
            {
                /* Set the BCLR flag.  */
                ux_hcd_synergy_register_set(hcd_synergy, fifo_ctrl, (USHORT)UX_SYNERGY_HC_FIFOCTR_BCLR);
            }
        }
    }

    /* Free the INTs now.  */
    TX_RESTORE

    /* Remove the reset bit in the ED.  */
    ed -> ux_synergy_ed_status = (ULONG)(~UX_SYNERGY_ED_SKIP);

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
 /*******************************************************************************************************************//**
  * @} (end addtogroup sf_el_ux)
  **********************************************************************************************************************/

