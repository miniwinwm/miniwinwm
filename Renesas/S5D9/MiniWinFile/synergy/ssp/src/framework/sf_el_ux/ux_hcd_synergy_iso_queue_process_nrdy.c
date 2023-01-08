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

#define UX_SOURCE_CODE

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "ux_api.h"
#include "ux_hcd_synergy.h"
#include "ux_utility.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function process the NRDY(Not Ready) Interrupt that occurred on a specific ED used for Isochronous
 *          transfer.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to an Endpoint control block
 **********************************************************************************************************************/
VOID  ux_hcd_synergy_iso_queue_process_nrdy(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED  *ed)
{
    UX_SYNERGY_ISO_TD * td;
    UX_SYNERGY_ISO_TD * next_td;
    UX_TRANSFER       * transfer_request;
    ULONG               response_pid;

    TX_INTERRUPT_SAVE_AREA

    /* Disable Interrupt */
    TX_DISABLE

    /* Clear the status flag.  */
    hcd_synergy -> ux_hcd_synergy_ed_irq[ed -> ux_synergy_pipe_index] =
            hcd_synergy -> ux_hcd_synergy_ed_irq[ed -> ux_synergy_pipe_index] & (~UX_SYNERGY_HC_ED_NRDY);

    /* Enable Interrupt */
    TX_RESTORE

    /* Get the TD associated with this transfer. */
    td = (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_head_td;

    /* Ensure the interrupt was valid.  */
    if ((td -> ux_synergy_iso_td_status & (ULONG)UX_SYNERGY_TD_ACK_PENDING) == 0)
    {
        return;
    }

    /* Get the transfer request associated with the TD.  */                          
    transfer_request =  td -> ux_synergy_iso_td_transfer_request;

    /* Select pipe.  */
    ux_hcd_synergy_register_write( hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)ed -> ux_synergy_pipe_index);

    /* Get the response PID from PIPExCTR.  */
    response_pid =  ux_hcd_synergy_register_read(hcd_synergy,
                                             UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL));

    /* Set PIPEx to NAK. The pipe stops sending tokens. */
    ux_hcd_synergy_register_clear(hcd_synergy,
            UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
            (USHORT)UX_SYNERGY_HC_DCPCTR_PID_MASK);

    /* Isolate the PD from the rest of the register bits.  */
    response_pid &= UX_SYNERGY_HC_DCPCTR_PID_MASK;

    /* Check what response we got. Obviously a bad one.  */
    if ((response_pid == UX_SYNERGY_HC_DCPCTR_PIDSTALL) || (response_pid == UX_SYNERGY_HC_DCPCTR_PIDSTALL2))
    {
        /* Set the error code to STALL.  */
        transfer_request -> ux_transfer_request_completion_code =  (UINT)UX_TRANSFER_STALLED;

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_TRANSFER_STALLED, transfer_request, 0, 0, UX_TRACE_ERRORS, 0, 0)
    }
    else
    {
        /* Set error to NO ANSWER.  */
        transfer_request -> ux_transfer_request_completion_code =  (UINT)UX_TRANSFER_NO_ANSWER;
    }

    /* Clean the tds attached to the ED.  */
    while (td != (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_tail_td)
    {
        /* Memorize this TD.  */
        next_td =  td -> ux_synergy_iso_td_next_td;

        /* Take it out of the chain.  */
        ed -> ux_synergy_ed_head_td = (UX_SYNERGY_TD *) next_td;

        /* We can now free the TD.  */
        td -> ux_synergy_iso_td_status = (ULONG)UX_UNUSED;

        /* Next TD.  */
        td =  next_td;
    }

    if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
    {
        transfer_request -> ux_transfer_request_completion_function(transfer_request);
    }

    _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);

    /* Return to caller.  */
    return;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

