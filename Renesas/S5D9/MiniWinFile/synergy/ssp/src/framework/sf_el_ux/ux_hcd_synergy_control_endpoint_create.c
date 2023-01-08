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
/*    ux_hcd_synergy_control_endpoint_create              PORTABLE C      */
/*                                                           5.7          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function will create a control endpoint.                       */
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
/*    ux_hcd_synergy_ed_obtain                Obtain synergy ED           */ 
/*    ux_hcd_synergy_regular_td_obtain        Obtain synergy regular TD   */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Synergy Controller Driver                                           */
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*                                                                        */ 
/*  06-01-2014     TCRG                     Initial Version 5.7           */ 
/*                                                                        */ 
/**************************************************************************/ 

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function will create a control endpoint.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  endpoint    : Pointer to an Endpoint control block
 *
 * @retval UX_SUCCESS            Control endpoint created successfully.
 * @retval UX_NO_ED_AVAILABLE    Failed to obtain an ED for control endpoint.
 * @retval UX_NO_TD_AVAILABLE    Failed to obtain a TD for control endpoint.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_control_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint)
{
    UX_SYNERGY_ED   * ed;
    UX_SYNERGY_ED   * head_ed;
    UX_SYNERGY_TD   * td;
    UX_DEVICE       * device;
    ULONG             device_address_register = 0;

    /* Get the device associated with the endpoint.  */
    device = endpoint -> ux_endpoint_device;

    /* We need to take into account the nature of the HCD to define the max size
       of any transfer in the transfer request.  */
    endpoint -> ux_endpoint_transfer_request.ux_transfer_request_maximum_length =  UX_SYNERGY_MAX_CONTROL_PAYLOAD;

    /* Obtain a ED for this new endpoint. This ED will live as long as the endpoint is active 
       and will be the container for the tds.  */
    ed =  ux_hcd_synergy_ed_obtain(hcd_synergy);
    if (ed == UX_NULL)
    {
        return (UINT)UX_NO_ED_AVAILABLE;
    }

    /* Obtain a dummy TD for terminating the ED transfer chain.  */
    td =  ux_hcd_synergy_regular_td_obtain(hcd_synergy);
    if (td == UX_NULL)
    {
        /* No more TD.  */
        ed -> ux_synergy_ed_status = (ULONG)UX_UNUSED;
        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Attach the ED to the endpoint container.  */
    endpoint -> ux_endpoint_ed =  (VOID *) ed;

    /* Now do the opposite, attach the ED container to the physical ED.  */
    ed -> ux_synergy_ed_endpoint =  endpoint;

    /* Hook the TD to both the tail and head of the ED.  */
    ed -> ux_synergy_ed_tail_td =  td;
    ed -> ux_synergy_ed_head_td =  td;

    /* Attach this ED to the asynch list.  */
    head_ed =  hcd_synergy -> ux_hcd_synergy_asynch_head_ed;
    ed -> ux_synergy_ed_next_ed =  head_ed;
    hcd_synergy -> ux_hcd_synergy_asynch_head_ed =  ed;

    /* Build the back chaining pointer. The previous head ED needs to know about the
       inserted ED. */
    if (head_ed != UX_NULL)
    {
        head_ed -> ux_synergy_ed_previous_ed =  ed;
    }

    /* Configure the  endpoint  hardware. Pick up buffer size & number. Set FIFO to C.  */
    ed -> ux_synergy_buffer_number = 0UL;
    ed -> ux_synergy_buffer_size   = (endpoint ->  ux_endpoint_descriptor.wMaxPacketSize) / 64UL;
    ed -> ux_synergy_fifo_index    = (ULONG)UX_SYNERGY_HC_FIFO_C;
    ed -> ux_synergy_pipe_index    = 0UL;

    /* Control endpoint is always created on Device Address 0.  
    This address will change later when a SET_ADDRESS is done. */

    /* Control endpoint is always created on Device Address 0.  This device may be behind a hub.
       Store the speed, the hub address and the bub port. This address will change later when
       a SET_ADDRESS is done. */   

    if (device -> ux_device_parent != NULL)
    {
        /* This device has a parent, therefore it is behind a hub.  */
        device_address_register = ((device -> ux_device_parent ->
                ux_device_address << UX_SYNERGY_HC_DEVADD_UPPHUB_SHIFT) |
                (device -> ux_device_port_location << UX_SYNERGY_HC_DEVADD_HUBPORT_SHIFT));
    }

    /* Check the speed and update the DEVADD conf register.  */
    switch(device -> ux_device_speed)
    {
        case (ULONG)UX_FULL_SPEED_DEVICE:
            device_address_register |= (ULONG)UX_SYNERGY_HC_DEVADD_SPEED_FULL;
            break;

        case (ULONG)UX_HIGH_SPEED_DEVICE:
#ifndef UX_HOST_DISABLE_HS
            device_address_register |= (ULONG)UX_SYNERGY_HC_DEVADD_SPEED_HIGH;
#else
            device_address_register |= (ULONG)UX_SYNERGY_HC_DEVADD_SPEED_FULL;
#endif
            break;

        default:
            device_address_register |= (ULONG)UX_SYNERGY_HC_DEVADD_SPEED_LOW;
            break;
    }

    ed -> ux_synergy_devaddm_val = (USHORT)device_address_register;

    /* Memorise the endpoint in the HCD structure. */
    hcd_synergy -> ux_hcd_synergy_ed_ptr[0] = ed;

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

