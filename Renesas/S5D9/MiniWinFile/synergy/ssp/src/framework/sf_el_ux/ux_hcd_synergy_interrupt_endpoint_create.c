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
/*    ux_hcd_synergy_interrupt_endpoint_create            PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function will create an interrupt endpoint. The interrupt      */ 
/*    endpoint has an interval of operation from 1 to 255. The Synergy    */
/*    has no hardware scheduler but we still build an interrupt tree      */ 
/*    similar to the OHCI controller.                                     */
/*                                                                        */
/*    This routine will match the best interval for the Synergy           */
/*    hardware. It will also determine the best node to hook the          */ 
/*    endpoint based on the load that already exists on the horizontal    */ 
/*    ED chain.                                                           */
/*                                                                        */
/*    For the ones curious about this coding. The tricky part is to       */
/*    understand how the interrupt matrix is constructed. We have used    */ 
/*    eds with the skip bit on to build a frame of anchor eds. Each ED    */ 
/*    creates a node for an appropriate combination of interval frequency */ 
/*    in the list.                                                        */ 
/*                                                                        */
/*    After obtaining a pointer to the list with the lowest traffic, we   */
/*    traverse the list from the highest interval until we reach the      */ 
/*    interval required. At that node, we anchor our real ED to the node  */ 
/*    and link the ED that was attached to the node to our ED.            */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy Controller */
/*    endpoint                              Pointer to endpoint           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_hcd_synergy_ed_obtain                Obtain ED                   */
/*    ux_hcd_synergy_regular_td_obtain        Obtain regular TD           */
/*    ux_hcd_synergy_least_traffic_list_get   Get least traffic list      */
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
 * @brief  This function will create an interrupt endpoint. The interrupt
 *         endpoint has an interval of operation from 1 to 255. The Synergy
 *         has no hardware scheduler but we still build an interrupt tree
 *         similar to the OHCI controller.
 *
 *         This routine will match the best interval for the Synergy
 *         hardware. It will also determine the best node to hook the
 *         endpoint based on the load that already exists on the horizontal
 *         ED chain.
 *
 *         The tricky part is to understand how the interrupt matrix is constructed.
 *         We have used eds with the skip bit on to build a frame of anchor eds.
 *         Each ED creates a node for an appropriate combination of interval
 *         frequency in the list.
 *
 *         After obtaining a pointer to the list with the lowest traffic, we
 *         traverse the list from the highest interval until we reach the
 *         interval required. At that node, we anchor our real ED to the node
 *         and link the ED that was attached to the node to our ED.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  endpoint    : Pointer to an Endpoint control block
 *
 * @retval UX_SUCCESS            Interrupt endpoint created successfully.
 * @retval UX_ERROR              Available pipe is not found for interrupt endpoint.
 * @retval UX_NO_ED_AVAILABLE    Failed to obtain an ED for new endpoint.
 * @retval UX_NO_TD_AVAILABLE    Failed to obtain a TD for terminating the ED transfer chain.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_interrupt_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint)
{
    UX_SYNERGY_ED     * ed;
    UX_SYNERGY_ED     * ed_list;
    UX_SYNERGY_ED     * next_ed;
    UX_SYNERGY_TD     * td;
    UINT                interval;
    UINT                interval_index;
    UINT                interval_synergy;
    ULONG               buffer_index;
    ULONG               pipe_index ;
    ULONG               current_pipe_index ;
    ULONG               endpoint_number;
    ULONG               endpoint_direction;
    ULONG               pipe_type;
    ULONG               device_address;
    ULONG               max_packet_size;

    TX_INTERRUPT_SAVE_AREA

    /* Set first buffer number. */
    buffer_index = 4UL;
    pipe_index = 0UL;
    
    /* Browse Pipes from 6 to 9 which can be interrupt.  */
    for (current_pipe_index = 6UL; current_pipe_index < 10UL; current_pipe_index++)
    {
        /* Select pipe 6 - 9.  */
        ux_hcd_synergy_register_write( hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)current_pipe_index);
       
        /* Check whether pipe is in use.  */
        pipe_type =  ( (UX_SYNERGY_HC_PIPECFG_TYPE_MASK & ux_hcd_synergy_register_read(hcd_synergy,
                UX_SYNERGY_HC_PIPECFG)) >> 14 ) ;
    
        /* Not in use, choose this one.  */
        if (pipe_type == 0UL)
        {
            /* Set the pipe index.  */
            pipe_index = current_pipe_index;

            /* We are done with pipe selection.  */
            break;
        }            

        /* Next buffer.  */
        buffer_index++;
    }

    /* Check if we found an available pipe for interrupt endpoint.  */
    if (pipe_index == 0UL)
    {
        return (UINT)UX_ERROR;
    }

    /* We need to take into account the nature of the HCD to define the max size
       of any transfer in the transfer request.  */
    endpoint -> ux_endpoint_transfer_request.ux_transfer_request_maximum_length = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD;
    
    /* Obtain a ED for this new endpoint. This ED will live as long as
       the endpoint is active and will be the container for the tds.  */
    ed =  ux_hcd_synergy_ed_obtain(hcd_synergy);
    if (ed == UX_NULL)
    {
        return (UINT)UX_NO_ED_AVAILABLE;
    }

    /* Store the pipe index.  */
    ed -> ux_synergy_pipe_index = pipe_index;
    
    /* Obtain a dummy TD for terminating the ED transfer chain.  */
    td =  ux_hcd_synergy_regular_td_obtain(hcd_synergy);
    if (td == UX_NULL)
    {
        ed -> ux_synergy_ed_status = (ULONG)UX_UNUSED;
        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Attach the ED to the endpoint container.  */
    endpoint -> ux_endpoint_ed =  (VOID *)ed;
    
    /* Now do the opposite, attach the ED container to the physical ED.  */
    ed -> ux_synergy_ed_endpoint =  endpoint;

    /* Hook the TD to both the tail and head of the ED.  */
    ed -> ux_synergy_ed_tail_td =  td;
    ed -> ux_synergy_ed_head_td =  td;

    /* Get the list index with the least traffic.  */
    ed_list =  ux_hcd_synergy_least_traffic_list_get(hcd_synergy);
    
    /* Get the interval for the endpoint and match it to a synergy list. We match anything 
       that is > 32ms to the 32ms interval list, the 32ms list is list 0, 16ms list is 1...
       the 1ms list is number 5.  */
    interval         = (UINT)endpoint -> ux_endpoint_descriptor.bInterval;
    interval_index   = 0x10U;
    interval_synergy = 1U;

    /* Do a sanity check if the frequency is 0. That should not happen, so treat it as 1.  */
    if (interval == 0U)
    {
        interval =  1U;
    }

    /* If the frequency is beyond the OHCI framework, make it the maximum of 32.  */
    if (interval >= 32U)
    {
        interval_synergy =  0U;
    }
    else
    {
        /* We parse the interval from the high bits. This gives us the first power of 2 entry in the tree.  */
    	/* When we find the first bit of the interval the current value of interval_synergy is set to the the list
    	 * index.  */
        while ((interval_index != 0U) && !(interval & interval_index))
        {
            /* Go down the tree one entry.  */
            interval_synergy++;
            
            /* And shift the bit of the device interval to check.  */
            interval_index =  interval_index >> 1U;
        }
    }

    /* Now we need to scan the list of eds from the lowest load entry until we reach 
       the appropriate interval node. The depth index is the interval_synergy value 
       and the 1st entry is pointed by the ED list entry.  */
    while (interval_synergy)
    {
        ed_list =  ed_list -> ux_synergy_ed_next_ed;
        while (!(ed_list -> ux_synergy_ed_status & UX_SYNERGY_ED_STATIC))
        {
            ed_list =  ed_list -> ux_synergy_ed_next_ed;
        }
        --interval_synergy;
    }       

    /* We found the node entry of the ED pointer that will be the anchor for this interrupt 
       endpoint. Now we attach this endpoint to the anchor and rebuild the chain .  */
    next_ed = ed_list -> ux_synergy_ed_next_ed;

    /* Check for end of tree which happens for devices with interval of 1. In this case
       there might not be a next_ed.  */
    if (next_ed != UX_NULL)
    {
        next_ed -> ux_synergy_ed_previous_ed =  ed;
    }

    ed -> ux_synergy_ed_next_ed =           next_ed;
    ed -> ux_synergy_ed_previous_ed =       ed_list;
    ed_list -> ux_synergy_ed_next_ed =      ed;

    /* Configure the  endpoint  hardware, pick up buffer size. Number is fixed. */
    ed -> ux_synergy_buffer_number =  buffer_index;
    ed -> ux_synergy_buffer_size =  0UL;
    
    /* Get the endpoint number.  */
    endpoint_number =  (endpoint -> ux_endpoint_descriptor.bEndpointAddress & 0xF ) ;
    
    /* Store the endpoint index for quick retrieval.  */
    ed -> ux_synergy_endpoint_index = endpoint_number;
    
    /* Get the endpoint direction.  */
    endpoint_direction = endpoint -> ux_endpoint_descriptor.bEndpointAddress & UX_ENDPOINT_DIRECTION;
    
    /* Check if IN or OUT.  */
    if (endpoint_direction == (ULONG)UX_ENDPOINT_IN)
    {
        /* Reset the endpoint direction as bit 4 of PIPECFG is 0 for IN.  */
        endpoint_direction = 0UL;
    }
    else
    {
        /* Set the direction to OUT.  */
        endpoint_direction = (ULONG)UX_SYNERGY_HC_PIPECFG_DIR;
    }

    /* Set PID to NAK. */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + (ed -> ux_synergy_pipe_index * 2UL),
                                                (USHORT)UX_SYNERGY_HC_DCPCTR_PIDNAK);
     
    /* Critical section, even ISR cannot be disrupted.  */
    TX_DISABLE

    /* Select the endpoint register to map all registers.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)pipe_index);

    /* Set Pipe configuration registers.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPECFG,
                                                (USHORT)( UX_SYNERGY_HC_PIPECFG_TYPE_INTERRUPT
                                                        | UX_SYNERGY_HC_PIPECFG_SHTNAK
                                                        | endpoint_direction
                                                        | endpoint_number));

    /* Get the device address. It needs to be stored in the PIPEMAXP register.  */
    device_address = ed ->
            ux_synergy_ed_endpoint -> ux_endpoint_device -> ux_device_address << UX_SYNERGY_HC_PIPEMAXP_DEVSEL_SHIFT;

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed ->
            ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;
    
    /* Inititalize the PIPEMAX register.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPEMAXP, (USHORT)(device_address | max_packet_size));
    
    /* Free the INTs now.  */
    TX_RESTORE

    /* For interrupt use FIFO D0 or D1 for DMA transfer, use FIFO_C for CPU transfer. */
    if((hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx != NULL) &&
            (endpoint_direction != 0UL) && (ed->ux_synergy_endpoint_index != 0UL))
    {
        ed -> ux_synergy_fifo_index = UX_SYNERGY_HC_FIFO_D0;
    }
    else if((hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx != NULL) &&
            (endpoint_direction == 0UL) && (ed->ux_synergy_endpoint_index != 0UL))
    {
        ed -> ux_synergy_fifo_index = UX_SYNERGY_HC_FIFO_D1;
    }
    else
    {
        ed -> ux_synergy_fifo_index = UX_SYNERGY_HC_FIFO_C;
    }

    /* Memorise the endpoint in the HCD structure. */
    hcd_synergy -> ux_hcd_synergy_ed_ptr[ed -> ux_synergy_pipe_index] = ed;

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
