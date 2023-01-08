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

static VOID  ux_hcd_synergy_iso_queue_brdy_out_transaction(UX_SYNERGY_ED * ed);

static VOID  ux_hcd_synergy_iso_queue_brdy_in_transaction(UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed);

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function process the BRDY(Buffer Ready)interrupt that occurred on a specific ED used for isochronous
 *          transfer.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to an Endpoint control block
 *********************************************************************************************************************/
VOID  ux_hcd_synergy_iso_queue_process_brdy(UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed)
{
    UX_SYNERGY_ISO_TD * td;

    TX_INTERRUPT_SAVE_AREA

    /* Disable Interrupt */
    TX_DISABLE

    /* Clear the status flag.  */
    hcd_synergy -> ux_hcd_synergy_ed_irq[ed -> ux_synergy_pipe_index] =
            hcd_synergy -> ux_hcd_synergy_ed_irq[ed -> ux_synergy_pipe_index] &
            (~(UX_SYNERGY_HC_ED_BRDY | UX_SYNERGY_HC_ED_BEMP));

    /* Enable Interrupt */
    TX_RESTORE

    /* Get the TD associated with this transfer. */
    td = (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_head_td;
    
    /* Ensure the interrupt was valid.  */
    if ((td -> ux_synergy_iso_td_status & UX_SYNERGY_TD_ACK_PENDING) == 0)
    {
        return;
    }

    /* Select pipe.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)ed -> ux_synergy_pipe_index);

    /* Set PIPEx to NAK. The pipe stops sending tokens. */
    ux_hcd_synergy_register_clear(hcd_synergy,  UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                (USHORT)UX_SYNERGY_HC_DCPCTR_PID_MASK);

    /* Check the direction.  */
    if (td -> ux_synergy_iso_td_direction ==  UX_SYNERGY_TD_OUT)
    {
        ux_hcd_synergy_iso_queue_brdy_out_transaction(ed);
    }
    else
    {
        ux_hcd_synergy_iso_queue_brdy_in_transaction(hcd_synergy, ed);
    }
}

/***********************************************************************************************************************
 Private Functions
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_iso_queue_process_brdy() to perform BRDY interrupt processing for
 * OUT direction PIPE used for isochrnous transfer.
 *
 * @param[in,out]  ed          : Pointer to an Endpoint control block
 **********************************************************************************************************************/
static VOID  ux_hcd_synergy_iso_queue_brdy_out_transaction(UX_SYNERGY_ED * ed)
{
    UX_SYNERGY_ISO_TD * td;
    UX_TRANSFER       * transfer_request;

    /* Get the TD associated with this transfer. */
    td = (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_head_td;

    /* Get the transfer request associated with the TD.  */
    transfer_request =  td -> ux_synergy_iso_td_transfer_request;

    /* Add the length transmitted to the total.  */
    transfer_request -> ux_transfer_request_actual_length +=  td -> ux_synergy_iso_td_length;

    /* Check the transmission is complete.  */
    if (transfer_request -> ux_transfer_request_actual_length == transfer_request -> ux_transfer_request_requested_length)
    {
        /* Set the transfer code to completed.  */
        transfer_request -> ux_transfer_request_completion_code = (UINT)UX_SUCCESS;

        /* Check if there is a callback.  */
        if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
        {
            /* Yes, so execute it.  */
            transfer_request -> ux_transfer_request_completion_function(transfer_request);
        }
    }

    /* Take the TD out of the Endpoint.  */
    ed -> ux_synergy_ed_head_td = (UX_SYNERGY_TD *) td -> ux_synergy_iso_td_next_td;

    /* We can now free the TD used in this PTD.  */
    td -> ux_synergy_iso_td_status = (ULONG)UX_UNUSED;
}

/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_iso_queue_process_brdy() to perform BRDY interrupt processing for
 * IN direction PIPE used for isochrnous transfer.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to an Endpoint control block
 **********************************************************************************************************************/
static VOID  ux_hcd_synergy_iso_queue_brdy_in_transaction(UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed)
{
    UX_SYNERGY_ISO_TD * td;
    UX_SYNERGY_ISO_TD * next_td;
    UX_TRANSFER       * transfer_request;
    ULONG               actual_length;

    /* This is an IN transfer.  We need to read the buffer into the
       transfer_request memory buffer.  */
    ux_hcd_synergy_buffer_read(hcd_synergy, ed);

    /* Get the TD associated with this transfer. */
    td = (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_head_td;

    /* Get the transfer request associated with the TD.  */
    transfer_request =  td -> ux_synergy_iso_td_transfer_request;

    /* We need to read the length received.  */
    actual_length =  td -> ux_synergy_iso_td_actual_length;

    /* Update the received length.  */
    transfer_request -> ux_transfer_request_actual_length +=  actual_length;

    /* Check the received length and see if we have a short packet or if we are finished with this transfer.  */
    if (   (transfer_request -> ux_transfer_request_actual_length ==
                transfer_request -> ux_transfer_request_requested_length)
        || (actual_length == 0UL)
        || ((actual_length % ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize) != 0UL))
    {
        /* Remove all the TDs attached.  */
        while ((td != (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_tail_td) &&
               (td -> ux_synergy_iso_td_transfer_request == transfer_request))
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

        /* Set the transfer code to completed.  */
        transfer_request -> ux_transfer_request_completion_code = (UINT)UX_SUCCESS;

        /* Check if DMA is used for data transfer. If used, we need to wait here until the transfer completes. */
        if ((hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx != NULL) &&
            (ed -> ux_synergy_fifo_index == (ULONG)UX_SYNERGY_HC_FIFO_D1) &&
            (actual_length >= sizeof(UINT))
        ){
            /* Wait until DMA transfer completes. */
            _ux_utility_semaphore_get(&hcd_synergy->ux_hcd_synergy_semaphore_rx, UX_WAIT_FOREVER);

            /* Semaphore needs to be put to be ready for next DMA transfer. */
            _ux_utility_semaphore_put(&hcd_synergy->ux_hcd_synergy_semaphore_rx);
        }

        /* Check if there is a callback.  */
        if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
        {
            /* Yes, so execute it.  */
            transfer_request -> ux_transfer_request_completion_function(transfer_request);
        }
    }
    else
    {
        /* Take the TD out of the Endpoint.  */
        ed -> ux_synergy_ed_head_td = (UX_SYNERGY_TD *) td -> ux_synergy_iso_td_next_td;

        /* We can now free the TD used in this PTD.  */
        td -> ux_synergy_iso_td_status = (ULONG)UX_UNUSED;
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/


