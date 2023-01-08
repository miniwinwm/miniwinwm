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

static ULONG  ux_hcd_synergy_request_iso_transfer_get_direction (UX_TRANSFER * transfer_request);

static UX_SYNERGY_ISO_TD * ux_hcd_synergy_isochronous_td_get(UX_HCD_SYNERGY * hcd_synergy,
                                                             UX_SYNERGY_ISO_TD * start_data_td);

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function performs an isochronous transfer request.
 *
 * @param[in]      hcd_synergy         : Pointer to a HCD control block
 * @param[in,out]  transfer_request    : Pointer to transfer request
 *
 * @retval UX_SUCCESS           Isochronous transfer request processed successfully.
 * @retval UX_NO_TD_AVAILABLE   Unavailable new TD.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_request_isochronous_transfer(UX_HCD_SYNERGY * hcd_synergy, UX_TRANSFER * transfer_request)
{
    UX_ENDPOINT           * endpoint;
    UX_SYNERGY_ISO_TD     * data_td;
    UX_SYNERGY_ISO_TD     * start_data_td;
    UX_SYNERGY_ISO_TD     * previous_td;
    UX_SYNERGY_ISO_TD     * tail_td;
    UX_SYNERGY_ED         * ed;
    ULONG                   transfer_request_payload_length;
    ULONG                   isoch_packet_payload_length;
    UCHAR                 * data_pointer;
    ULONG                   current_frame_number = 0UL;
    ULONG                   max_packet_size;

    TX_INTERRUPT_SAVE_AREA
    
    /* Get the pointer to the Endpoint.  */
    endpoint =  (UX_ENDPOINT *) transfer_request -> ux_transfer_request_endpoint;

    /* Now get the physical ED attached to this endpoint.  */
    ed =  endpoint -> ux_endpoint_ed;

    /* If the transfer_request specifies a max packet length other than the endpoint
       size, we force the transfer request value into the endpoint.  */
    if (transfer_request -> ux_transfer_request_packet_length == 0UL)
    {
        transfer_request -> ux_transfer_request_packet_length =
                                        (ULONG) endpoint -> ux_endpoint_descriptor.wMaxPacketSize;
    }

    /* Remember the packet length.  */
    isoch_packet_payload_length =  transfer_request -> ux_transfer_request_packet_length;

    /* Disable Interrupt */
    TX_DISABLE

    /* Use the TD pointer by ed -> tail for the first TD of this transfer and chain from this one on.  */
    data_td =  (UX_SYNERGY_ISO_TD *) ((void *) ed -> ux_synergy_ed_tail_td);
    previous_td =  data_td;

    /* Reset the first obtained data TD in case there is a TD shortage while building the list of tds.  */
    start_data_td =  UX_NULL;

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* Calculate the frame number to be used to send this payload. If there are no current transfers, 
       we take the current frame number and add a safety value (2-5) to it. If here is pending transactions,
       we use the frame number stored in the transfer request.  */
    if (ed -> ux_synergy_ed_tail_td == ed -> ux_synergy_ed_head_td)
    {
        ux_hcd_synergy_frame_number_get(hcd_synergy, &current_frame_number);
        ed -> ux_synergy_ed_frame =  current_frame_number + UX_SYNERGY_FRAME_DELAY;
    }
    else
    {
        current_frame_number =  ed -> ux_synergy_ed_frame;
    }

    /* Load the start buffer address and Urb length to split the urb in multiple TD transfer.  */
    transfer_request_payload_length =  transfer_request -> ux_transfer_request_requested_length;
    data_pointer =  transfer_request -> ux_transfer_request_data_pointer;
    
    while (transfer_request_payload_length != 0UL)
    {
        /* Set the direction of the TD.  */
        data_td -> ux_synergy_iso_td_direction = ux_hcd_synergy_request_iso_transfer_get_direction(transfer_request);

        if (transfer_request_payload_length > max_packet_size)
        {
            /* Set the max packet size of this endpoint. */
            isoch_packet_payload_length = max_packet_size;
        }
        else
        {
            isoch_packet_payload_length =  transfer_request_payload_length;
        }

        /* Set the frame number.  */
        ed -> ux_synergy_ed_frame =  current_frame_number;

        /* Set the buffer address.  */
        data_td -> ux_synergy_iso_td_buffer =  data_pointer;

        /* Update the length of the transfer for this TD.  */
        data_td -> ux_synergy_iso_td_length =  isoch_packet_payload_length;

        /* Attach the endpoint and transfer request to the TD.  */
        data_td -> ux_synergy_iso_td_transfer_request =  transfer_request;
        data_td -> ux_synergy_iso_td_ed =  ed;

        /* Adjust the data payload length and the data payload pointer.  */
        transfer_request_payload_length -=  isoch_packet_payload_length;
        data_pointer +=  isoch_packet_payload_length;

        /* Prepare the next frame for the next TD in advance.  */
        current_frame_number++;

        /* Check if there will be another transaction.  */
        if (transfer_request_payload_length != 0UL)
        {
            /* Get a new TD to hook this payload.  */
            data_td = ux_hcd_synergy_isochronous_td_get(hcd_synergy, start_data_td);
            if (data_td == UX_NULL)
            {
                /* Enable Interrupt */
                TX_RESTORE

                return (UINT)UX_NO_TD_AVAILABLE;
            }

            /* the first obtained TD in the chain has to be remembered.  */
            if (start_data_td == UX_NULL)
            {
                start_data_td =  data_td;
            }

            /* Attach this new TD to the previous one.  */                                
            previous_td -> ux_synergy_iso_td_next_td =  data_td;
            previous_td =  data_td;
        }
    }
        
    /* Memorize the next frame number for this ED.  */
    ed -> ux_synergy_ed_frame =  current_frame_number;

    /* At this stage, the Head and Tail in the ED are still the same and the synergy controller 
       will skip this ED until we have hooked the new tail TD.  */
    tail_td = ux_hcd_synergy_isochronous_td_get(hcd_synergy, start_data_td);
    if (tail_td == UX_NULL)
    {
        /* Enable Interrupt */
        TX_RESTORE

        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Attach the tail TD to the last data TD.  */
    data_td -> ux_synergy_iso_td_next_td =  tail_td;

    /* At this stage, the Head and Tail in the ED are still the same and
       the Synergy controller will skip this ED until we have hooked the new
       tail TD.  */
    ed -> ux_synergy_ed_tail_td =  (UX_SYNERGY_TD *) ((void *) tail_td);

    /* Enable Interrupt */
    TX_RESTORE

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private Functions
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_request_isochronous_transfer() to get the direction of transfer
 * request.
 *
 * @param[in]  transfer_request     Pointer to a Transfer request
 * @retval     UX_SYNERGY_TD_IN     Transfer is IN direction
 * @retval     UX_SYNERGY_TD_OUT    Transfer is OUT direction
 **********************************************************************************************************************/
static ULONG  ux_hcd_synergy_request_iso_transfer_get_direction (UX_TRANSFER * transfer_request)
{
    ULONG direction;

    /* Set the direction of the TD.  */
    if ((transfer_request -> ux_transfer_request_type & (UINT)UX_REQUEST_DIRECTION) == (UINT)UX_REQUEST_IN)
    {
        direction =  UX_SYNERGY_TD_IN;
    }
    else
    {
        direction =  UX_SYNERGY_TD_OUT;
    }

    return direction;
}

/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_request_isochronous_transfer() to get a new Transfer Descriptor
 * for an isochrnous transfer request.
 *
 * @param[in]  hcd_synergy          Pointer to a HCD control block
 * @param[in]  start_data_td        Start of TD
 * @retval     NULL                 Failed to get a new Transfer Descriptor
 * @retval     Non-NULL             Address of Transfer Descriptor obtained
 **********************************************************************************************************************/
static UX_SYNERGY_ISO_TD * ux_hcd_synergy_isochronous_td_get(UX_HCD_SYNERGY * hcd_synergy,
                                                             UX_SYNERGY_ISO_TD * start_data_td)
{
    UX_SYNERGY_ISO_TD * td;
    UX_SYNERGY_ISO_TD * next_data_td;

    /* Get a new TD to hook this payload.  */
    td =  ux_hcd_synergy_isochronous_td_obtain(hcd_synergy);
    if (td == UX_NULL)
    {
        /* If there was already a TD chain in progress, free it.  */
        if (start_data_td != UX_NULL)
        {
            td =  start_data_td;

            while (NULL != td)
            {
                next_data_td =  td -> ux_synergy_iso_td_next_td;
                td -> ux_synergy_iso_td_status = (ULONG)UX_UNUSED;
                td =  next_data_td;
            }
        }
    }

    return td;
}


