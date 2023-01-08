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

static VOID ux_hcd_synergy_iso_queue_process_timeout (UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed,
                                                                                        ULONG ed_index);

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function process the isochronous transactions that happened in the last frame.
 *
 * @param[in]  hcd_synergy : Pointer to a HCD control block
 **********************************************************************************************************************/
VOID  ux_hcd_synergy_iso_queue_process(UX_HCD_SYNERGY *hcd_synergy)
{
    UX_SYNERGY_ED     * ed;
    ULONG               ed_index;

    /* Find the endpoint responsible for interrupt, map that to ed 
       find td that was scheduled, find out what happened on the transaction
       update the transaction. */
    
    /* Parse through the list of EDs */
    for (ed_index = 1UL ; ed_index <= 2UL ; ed_index++)
    {
        /* Check for an  event on the transaction. */
        if(hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index])
        { 
            /* There was something for the endpoint.  Load the ED that had a transmission.  */
            ed = hcd_synergy -> ux_hcd_synergy_ed_ptr[ed_index];

            /* Check the endpoint is for isochrnous transfer. */
            if ((ULONG)UX_ISOCHRONOUS_ENDPOINT ==
                    (ed->ux_synergy_ed_endpoint->ux_endpoint_descriptor.bmAttributes & (ULONG)UX_MASK_ENDPOINT_TYPE))
            {
                /* Check if the irq  was a Buffer Ready.  */
                if( hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index] & UX_SYNERGY_HC_ED_BRDY)
                {
                    /* Process buffer ready interrupt. */
                    ux_hcd_synergy_iso_queue_process_brdy(hcd_synergy, ed);
                }

                if( hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index] & UX_SYNERGY_HC_ED_NRDY )
                {
                    /* Process buffer not ready interrupt. */
                    ux_hcd_synergy_iso_queue_process_nrdy(hcd_synergy, ed);
                }

                if( hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index] & UX_SYNERGY_HC_ED_BEMP )
                {
                    /* Process buffer empty interrupt. */
                    ux_hcd_synergy_iso_queue_process_bemp(hcd_synergy, ed);
                }

                if( hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index] & UX_SYNERGY_HC_ED_EOFERR )
                {
                    /* No definition */
                }

                if( hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index] &  UX_SYNERGY_HC_ED_TIMEOUT )
                {
                    ux_hcd_synergy_iso_queue_process_timeout(hcd_synergy, ed, ed_index);
                }
            }
        }
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private Functions
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_iso_queue_process() to handle timeout error processing.
 *
 * @param[in]  hcd_synergy : Pointer to a HCD control block
 * @param[in]  ed          : Pointer to a Endpoint descriptor for Synergy target
 * @param[in]  ed_index    : Endpoint index
 **********************************************************************************************************************/
static VOID  ux_hcd_synergy_iso_queue_process_timeout (UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed,
                                                                                        ULONG ed_index)
{
    UX_SYNERGY_ISO_TD * td;
    UX_SYNERGY_ISO_TD * next_td;
    UX_TRANSFER       * transfer_request;

    /* Clear the status flag. */
    hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index] =
            hcd_synergy -> ux_hcd_synergy_ed_irq[ed_index] & (~UX_SYNERGY_HC_ED_TIMEOUT);

    /* Get the TD associated with this transfer. */
    td = (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_head_td;

    /* Get the transfer request associated with the TD.  */
    transfer_request =  td -> ux_synergy_iso_td_transfer_request;

    /* Ensure the interrupt was valid.  */
    if (td -> ux_synergy_iso_td_status & UX_SYNERGY_TD_ACK_PENDING)
    {
        /* Remove all the TDs attached.  */
        while (td != (UX_SYNERGY_ISO_TD *) ed -> ux_synergy_ed_tail_td)
        {

            /* Memorize this TD.  */
            next_td =  td -> ux_synergy_iso_td_next_td;

            /* Take it out of the chain.  */
            ed -> ux_synergy_ed_head_td = (UX_SYNERGY_TD *) next_td;

            /* We can now free the TD.  */
            td -> ux_synergy_iso_td_status =  (ULONG)UX_UNUSED;

            /* Next TD.  */
            td =  next_td;
        }

        /* Set the error code to TIMEOUT.  */
        transfer_request -> ux_transfer_request_completion_code = (UINT)UX_TRANSFER_NO_ANSWER;

        /* Wake up the class if necessary.  */
        if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
        {
            transfer_request -> ux_transfer_request_completion_function(transfer_request);
        }
    } 
}


