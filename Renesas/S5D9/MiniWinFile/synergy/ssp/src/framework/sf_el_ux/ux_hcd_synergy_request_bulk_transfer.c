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

#if defined(R_USBHS_BASE)
static ULONG ux_hcd_synergy_set_transfer_counter(UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed, ULONG payload_length);
#endif

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_request_bulk_transfer                PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function performs a bulk transfer request. A bulk transfer    */ 
/*     can be larger than the size of the Synergy buffer so it may be     */
/*     required to chain multiple tds to accommodate this transfer        */ 
/*     request. A bulk transfer is non blocking, so we return before the  */ 
/*     transfer request is completed.                                     */ 
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
/*    ux_hcd_synergy_regular_td_obtain         Obtain regular TD          */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    synergy Controller Driver                                           */
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
 * @brief  This function performs a bulk transfer request. A bulk transfer
 *         can be larger than the size of the Synergy buffer so it may be
 *         required to chain multiple tds to accommodate this transfer
 *         request. A bulk transfer is non blocking, so we return before the
 *         transfer request is completed.
 *
 * @param[in]      hcd_synergy         : Pointer to a HCD control block
 * @param[in,out]  transfer_request    : Pointer to transfer request
 *
 * @retval UX_SUCCESS            Bulk transfer happened successfully.
 * @retval UX_NO_TD_AVAILABLE    Unavailable New TD.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_request_bulk_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request)
{
    UX_ENDPOINT       * endpoint;
    UX_SYNERGY_TD     * data_td;
    UX_SYNERGY_TD     * start_data_td;
    UX_SYNERGY_TD     * next_data_td;
    UX_SYNERGY_TD     * previous_td;
    UX_SYNERGY_TD     * tail_td;
    UX_SYNERGY_ED     * ed;
    ULONG               transfer_request_payload_length;
    ULONG               bulk_packet_payload_length;
    UCHAR             * data_pointer;
    ULONG               max_packet_size;

    /* Get the pointer to the Endpoint.  */
    endpoint =  (UX_ENDPOINT *) transfer_request -> ux_transfer_request_endpoint;

    /* Get the physical ED attached to the endpoint associated with this transfer request. */
    ed =  endpoint -> ux_endpoint_ed;

    /* Use the TD pointer by ed -> tail for the first TD of this transfer
        and chain from this one on.  */
    data_td =  ed -> ux_synergy_ed_tail_td;
    previous_td =  data_td;

    /* Reset the first obtained data TD in case there is a TD shortage while building 
       the list of tds.  */
    start_data_td =  NULL;

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* It may take more than one TD if the transfer_request length is more than the
       maximum length for a Synergy TD (this is irrelevant of the MaxPacketSize value
       in the endpoint descriptor). Synergy data payload has a maximum size of 4K.  */
    transfer_request_payload_length =  transfer_request -> ux_transfer_request_requested_length;

    data_pointer =  transfer_request -> ux_transfer_request_data_pointer;

#if defined(R_USBHS_BASE)
    /* A PIPE for IN transaction need to set valid number to PIPE transaction counter if the size of
     * FIFO buffer is configured to larger value than the max packet size of PIPE. */
    if ((ULONG)UX_ENDPOINT_IN == (endpoint -> ux_endpoint_descriptor.bEndpointAddress & (ULONG)UX_ENDPOINT_DIRECTION))
    {
        /* Set transaction counter.  */
        if (1UL != ux_hcd_synergy_set_transfer_counter(hcd_synergy, ed, transfer_request_payload_length))
        {
            max_packet_size = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD;
        }
    }
    else
    {
        if(((transfer_request_payload_length % (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD) == 0UL) && (max_packet_size > 64UL))
        {
            max_packet_size = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD;
        }
    }
#endif

    /** Perform bulk transfer. If transfer request payload length is zero, transfer it once. */
    do
    {
        if (transfer_request_payload_length > max_packet_size)
        {
            /* Set the max packet size of this endpoint. */
            bulk_packet_payload_length = max_packet_size;
        }
        else
        {
            bulk_packet_payload_length =  transfer_request_payload_length;
        }

        /* Store the beginning of the buffer address in the TD.  */
        data_td -> ux_synergy_td_buffer =  data_pointer;

        /* Update the length of the transfer for this TD.  */
        data_td -> ux_synergy_td_length =  bulk_packet_payload_length;

        /* Attach the endpoint and transfer_request to the TD.  */
        data_td -> ux_synergy_td_transfer_request =  transfer_request;
        data_td -> ux_synergy_td_ed =  ed;

        /* Adjust the data payload length and the data payload pointer.  */
        transfer_request_payload_length -=  bulk_packet_payload_length;
        data_pointer +=  bulk_packet_payload_length;

        /* The direction of the transaction is set in the TD.  */
        if ((ULONG)(transfer_request -> ux_transfer_request_type & UX_REQUEST_DIRECTION) == (ULONG)UX_REQUEST_IN)
        {
            data_td -> ux_synergy_td_direction =  UX_SYNERGY_TD_IN;
        }
        else
        {
            data_td -> ux_synergy_td_direction =  UX_SYNERGY_TD_OUT;
        }

        /* Mark the TD with the DATA phase.  */
        data_td -> ux_synergy_td_status |=  UX_SYNERGY_TD_DATA_PHASE;

        /* The Toggle value is in the ED.  */
        data_td -> ux_synergy_td_toggle =  UX_SYNERGY_TD_TOGGLE_FROM_ED;

        /* Check if there will be another transaction.  */
        if (transfer_request_payload_length != 0UL)
        {
            /* Get a new TD to hook this payload.  */
            data_td =  ux_hcd_synergy_regular_td_obtain(hcd_synergy);
            if (data_td == UX_NULL)
            {
                /* If there was already a TD chain in progress, free it.  */
                if (start_data_td != UX_NULL)
                {
                    data_td =  start_data_td;
                    while (data_td)
                    {
                        next_data_td =  data_td -> ux_synergy_td_next_td;
                        data_td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
                        data_td =  next_data_td;
                    }
                }
                return (UINT)UX_NO_TD_AVAILABLE;
            }

            /* the first obtained TD in the chain has to be remembered.  */
            if (start_data_td == UX_NULL)
            {
                start_data_td =  data_td;
            }

            /* Attach this new TD to the previous one.  */
            previous_td -> ux_synergy_td_next_td =  data_td;
            previous_td =  data_td;
        }
    } while (transfer_request_payload_length != 0UL);

    /* At this stage, the Head and Tail in the ED are still the same and the synergy
       controller will skip this ED until we have hooked the new tail TD.  */
    tail_td =  ux_hcd_synergy_regular_td_obtain(hcd_synergy);
    if (tail_td == UX_NULL)
    {
        /* If there was already a TD chain in progress, free it.  */
        if (start_data_td != UX_NULL)
        {
            data_td =  start_data_td;
            while (data_td)
            {
                next_data_td =  data_td -> ux_synergy_td_next_td;
                data_td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
                data_td =  next_data_td;
            }
        }

        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Attach the tail TD to the last data TD.  */
    data_td -> ux_synergy_td_next_td =  tail_td;

    /* Store the new tail TD.  */
    ed -> ux_synergy_ed_tail_td =  tail_td;

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}

#if defined(R_USBHS_BASE)
/*******************************************************************************************************************//**
 * @brief  This function set a transaction counter if this driver context uses USBHS and the max packet size of
 *         PIPE is larger than 64.
 *
 * @param[in]  hcd_synergy         : Pointer to a HCD control block
 * @param[in]  ed                  : Pointer to ED control block
 * @param[in]  payload_length      : Transfer request payload length
 *
 * @return transfer_counter         Transfer counter value.
 **********************************************************************************************************************/
static ULONG ux_hcd_synergy_set_transfer_counter(UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed, ULONG payload_length)
{
    ULONG   max_packet_size;
    ULONG   transfer_counter = 1UL;

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    if ((R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base) && (max_packet_size > 64UL))
    {
        /* Set transaction counter if this driver context uses USBHS and the max packet size of PIPE is larger than 64. */
        if((payload_length % (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD) == 0UL)
        {
            transfer_counter = ((ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD / max_packet_size);

            /* Set transaction counter to number of transfers. */
            ux_hcd_synergy_register_write(hcd_synergy,(ULONG)UX_SYNERGY_HC_PIPE1TRN + ((ed -> ux_synergy_pipe_index - 1UL) * 4UL),
                                           (USHORT) transfer_counter);
        }
        else
        {
            /* Set transaction counter to 1. */
            ux_hcd_synergy_register_write(hcd_synergy, (ULONG)UX_SYNERGY_HC_PIPE1TRN + ((ed -> ux_synergy_pipe_index - 1UL) * 4UL),
                                           (USHORT)1U);
        }
    }

    return transfer_counter;
}
#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
