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

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_request_interrupt_transfer           PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function performs an interrupt transfer request. An interrupt */ 
/*     transfer can only be as large as the MaxpacketField in the         */ 
/*     endpoint descriptor. This was verified at the USB layer and does   */ 
/*     not need to be reverified here.                                    */ 
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
 * @brief  This function performs an interrupt transfer request. An interrupt
 *         transfer can only be as large as the MaxpacketField in the
 *         endpoint descriptor. This was verified at the USB layer and does
 *         not need to be reverified here.
 *
 * @param[in]      hcd_synergy         : Pointer to a HCD control block
 * @param[in,out]  transfer_request    : Pointer to transfer request
 *
 * @retval UX_SUCCESS           Interrupt transfer request processed successfully.
 * @retval UX_NO_TD_AVAILABLE   Unavailable new TD.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_request_interrupt_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request)
{
    UX_ENDPOINT     * endpoint;
    UX_SYNERGY_ED   * ed;
    UX_SYNERGY_TD   * data_td;
    UX_SYNERGY_TD   * tail_td;

    /* Get the pointer to the Endpoint.  */
    endpoint =  (UX_ENDPOINT *) transfer_request -> ux_transfer_request_endpoint;

    /* Now get the physical ED attached to this endpoint.  */
    ed =  endpoint -> ux_endpoint_ed;

    /* Use the TD pointer by ed -> tail for the first TD of this transfer
        and chain from this one on.  */
    data_td =  ed -> ux_synergy_ed_tail_td;

    /* Set the direction of the transfer.  */
    if ((transfer_request -> ux_transfer_request_type & (UINT)UX_REQUEST_DIRECTION) == (UINT)UX_REQUEST_IN)
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

    /* Store the beginning of the buffer address in the TD.  */
    data_td -> ux_synergy_td_buffer =  transfer_request -> ux_transfer_request_data_pointer;

    /* Update the length of the transfer for this TD.  */
    data_td -> ux_synergy_td_length =  transfer_request -> ux_transfer_request_requested_length;

    /* Attach the endpoint and transfer request to the TD.  */
    data_td -> ux_synergy_td_transfer_request =  transfer_request;
    data_td -> ux_synergy_td_ed =  ed;

    /* At this stage, the Head and Tail in the ED are still the same and
       the synergy controller will skip this ED until we have hooked the new
       tail TD.  */
    tail_td =  ux_hcd_synergy_regular_td_obtain(hcd_synergy);
    if (tail_td == UX_NULL)
    {
        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Attach the tail TD to the last data TD.  */
    data_td -> ux_synergy_td_next_td =  tail_td;

    /* Store the new tail TD.  */
    ed -> ux_synergy_ed_tail_td =  tail_td;

    /* There is no need to wake up the Synergy controller on this transfer
       since periodic transactions will be picked up when the interrupt
       tree is scanned.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

