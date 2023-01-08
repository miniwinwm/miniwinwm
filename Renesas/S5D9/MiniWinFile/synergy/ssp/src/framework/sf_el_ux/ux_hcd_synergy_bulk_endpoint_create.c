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

#if !defined(UX_SYNERGY_BULK_PIPE_START_INDEX)
#define UX_SYNERGY_BULK_PIPE_START_INDEX    (1UL)
#endif

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_bulk_endpoint_create                PORTABLE C       */ 
/*                                                           5.7 SP7      */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function will create a bulk endpoint.                          */
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
/*    ux_hcd_synergy_ed_obtain                Obtain Synergy ED           */ 
/*    ux_hcd_synergy_regular_td_obtain        Obtain Synergy regular TD   */ 
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
/*                                                                        */ 
/**************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function will create a bulk endpoint.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  endpoint    : Pointer to a USBX Endpoint Container structure
 *
 * @retval UX_ERROR             PIPE is not available for bulk endpoint creation .
 * @retval UX_SUCCESS           Bulk endpoints created successfully.
 * @retval UX_NO_ED_AVAILABLE   ED for bulk endpoint is not available.
 * @retval UX_NO_TD_AVAILABLE   Dummy TD for terminating the ED transfer chain is not available.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_bulk_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint)
{
    UX_SYNERGY_ED     * ed;
    UX_SYNERGY_ED     * head_ed;
    UX_SYNERGY_TD     * td;
    ULONG               pipe_index;
    ULONG               current_pipe_index;
    ULONG               endpoint_number;
    ULONG               endpoint_direction;
    ULONG               pipe_type;
    ULONG               device_address;
    ULONG               max_packet_size;

TX_INTERRUPT_SAVE_AREA

    /* Obtain the first available pipe. */
    current_pipe_index = UX_SYNERGY_BULK_PIPE_START_INDEX;
    pipe_index = 0UL;

    while (current_pipe_index <= 5UL)
    {
        /* Select pipe 1 - 5.  */
        ux_hcd_synergy_register_write( hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)current_pipe_index);
       
        /* Check whether pipe is in use.  */
        pipe_type =  ( (UX_SYNERGY_HC_PIPECFG_TYPE_MASK &
                        ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_PIPECFG)) >> 14 );
    
        /* Not in use, choose this one.  */
        if (pipe_type == 0UL)
        {
            pipe_index = current_pipe_index;
            break;
        }

        /* Increment the current index.  */
        current_pipe_index++;
    }

    /* Check if we found an available pipe for bulk endpoint.  */
    if (pipe_index == 0UL)
    {
        return (UINT)UX_ERROR;
    }

    /* Obtain a ED for this new endpoint. This ED will live as long as the endpoint is active 
       and will be the container for the TDs.  */
    ed =  ux_hcd_synergy_ed_obtain(hcd_synergy);
    if (ed == UX_NULL)
    {
        return (UINT)UX_NO_ED_AVAILABLE;
    }

    /* Obtain a dummy TD for terminating the ED transfer chain.  */
    td =  ux_hcd_synergy_regular_td_obtain(hcd_synergy);
    if (UX_NULL == td)
    {
        /* No more TD.  */
        ed -> ux_synergy_ed_status = (ULONG)UX_UNUSED;
        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Store the pipe index.  */
    ed -> ux_synergy_pipe_index = pipe_index;

    /* We need to take into account the nature of the HCD to define the max size
       of any transfer in the transfer request.  */
    endpoint -> ux_endpoint_transfer_request.ux_transfer_request_maximum_length = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD;

    /* Attach the ED to the endpoint container.  */
    endpoint -> ux_endpoint_ed =  (VOID *) ed;

    /* Now do the opposite, attach the ED container to the physical ED.  */
    ed -> ux_synergy_ed_endpoint =  endpoint;
    
    /* Hook the TD to both the tail and head of the ED.  */
    ed -> ux_synergy_ed_tail_td =  td;
    ed -> ux_synergy_ed_head_td =  td;

    /* Attach this ED to the bulk list.  */
    head_ed =  hcd_synergy -> ux_hcd_synergy_asynch_head_ed;
    ed -> ux_synergy_ed_next_ed =  head_ed;
    hcd_synergy -> ux_hcd_synergy_asynch_head_ed =  ed;

    /* Build the back chaining pointer. The previous head ED needs to know about the
       inserted ED. */
    if (head_ed != UX_NULL)
    {
        head_ed -> ux_synergy_ed_previous_ed =  ed;
    }
        
    /* Configure the  endpoint  hardware, pick up buffer size & number. */
    ed -> ux_synergy_buffer_size   = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD / (ULONG)UX_SYNERGY_HC_MAX_BUF_SIZE;
    ed -> ux_synergy_buffer_number = (ULONG)UX_SYNERGY_HC_PIPE1_BUF_START_NUM +
            ((pipe_index - 1UL) * (ed -> ux_synergy_buffer_size) * 2);
    
    if ( ed -> ux_synergy_buffer_number > (ULONG)UX_SYNERGY_HC_MAX_BUF_NUM)
    {
        return (UINT)UX_ERROR;
    }
         
    /* Get the endpoint number.  */
    endpoint_number =  (endpoint -> ux_endpoint_descriptor.bEndpointAddress & 0xFUL);
    
    /* Store the endpoint index for quick retrieval.  */
    ed -> ux_synergy_endpoint_index = endpoint_number;
    
    /* Check if the endpoint direction is IN or OUT.  */
    if ((ULONG)UX_ENDPOINT_IN == (endpoint -> ux_endpoint_descriptor.bEndpointAddress & (ULONG)UX_ENDPOINT_DIRECTION))
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
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                (USHORT)UX_SYNERGY_HC_DCPCTR_PIDNAK);

    /* Set ACLRM bit to 1 to clear the FIFO buffer. */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                (USHORT)UX_SYNERGY_HC_PIPECTR_ACLRM);

    /* Now reset the ACLRM bit. */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                (USHORT)UX_SYNERGY_HC_PIPECTR_ACLRM);
    /* Critical section, even ISR cannot be disrupted.  */
    TX_DISABLE

    /* Select the endpoint register to map all registers.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)pipe_index);

    /* Set Pipe configuration registers. */
#if defined(R_USBHS_BASE)
    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        /* Enable double buffer for Read Pipe (IN)*/
        if (0 == endpoint_direction)
        {
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPECFG,
                                            (USHORT)(UX_SYNERGY_HC_PIPECFG_TYPE_BULK |
                                                     UX_SYNERGY_HC_PIPECFG_SHTNAK |
                                                     endpoint_direction |
                                                     endpoint_number |
                                                     UX_SYNERGY_HC_PIPECFG_CNTMD | UX_SYNERGY_HC_PIPECFG_DBLB));
        }
        else
        {
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPECFG,
                                            (USHORT)(UX_SYNERGY_HC_PIPECFG_TYPE_BULK |
                                                     UX_SYNERGY_HC_PIPECFG_SHTNAK |
                                                     endpoint_direction |
                                                     endpoint_number |
                                                     UX_SYNERGY_HC_PIPECFG_CNTMD));
        }

        /* Set the endpoint buffer info. */
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPEBUF,
                                       ((USHORT)((ed -> ux_synergy_buffer_size - 1UL) << UX_SYNERGY_HC_PIPEBUF_SHIFT) |
                                        (USHORT)ed -> ux_synergy_buffer_number));
    }
    else
#endif
    {
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPECFG,
                                       (USHORT)(UX_SYNERGY_HC_PIPECFG_TYPE_BULK |
                                                UX_SYNERGY_HC_PIPECFG_SHTNAK |
                                                endpoint_direction |
                                                endpoint_number));
    }
    
    /* Get the device address. It needs to be stored in the PIPEMAXP register.  */
    device_address = ed -> ux_synergy_ed_endpoint -> ux_endpoint_device -> ux_device_address << UX_SYNERGY_HC_PIPEMAXP_DEVSEL_SHIFT;

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /** Limit the max packet size to the size the HW supports. */
    if(((ULONG)UX_SYNERGY_HC_MAX_BUF_SIZE < (ULONG) max_packet_size ) && ((ULONG)R_USBFS_BASE == hcd_synergy->ux_hcd_synergy_base))
    {
    	ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize = (ULONG)UX_SYNERGY_HC_MAX_BUF_SIZE;
    	max_packet_size = (ULONG)UX_SYNERGY_HC_MAX_BUF_SIZE;
    }
    
    /* Initialize the PIPEMAX register.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPEMAXP, (USHORT)(device_address | max_packet_size));

    /* Initialize the Transaction Counter and Transaction Counter Enable Register */
#if defined(R_USBHS_BASE)
    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        /* Only a IN PIPE needs to enable Transaction Counter. */
        if (0 == endpoint_direction)
        {
            /* Disable and clear Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPE1TRE +
                                          (ULONG)((ed -> ux_synergy_pipe_index - 1UL) * 4UL), (USHORT)0U);

            /* Set default value (1) to Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPE1TRN +
                    (ULONG)((ed -> ux_synergy_pipe_index - 1UL) * 4UL), (USHORT)1U);

            /* Enable Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPE1TRE +
                    (ULONG)((ed -> ux_synergy_pipe_index - 1UL) * 4UL), (USHORT)UX_SYNERGY_HC_PIPETRE_TRENB);
        }
        else
        {
            /* Disable Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPE1TRE +
                                          (ULONG)((ed -> ux_synergy_pipe_index - 1UL) * 4UL), (USHORT)0U);
        }
    }
#endif

    /* For DMA bulk and interrupt, use FIFO_D0.  */
    if((hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx != NULL) &&
            (endpoint_direction != 0UL) && (ed->ux_synergy_endpoint_index != 0UL))
    {
        ed -> ux_synergy_fifo_index = (ULONG)UX_SYNERGY_HC_FIFO_D0;
    }
    else if((hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx != NULL) &&
            (endpoint_direction == 0UL) && (ed->ux_synergy_endpoint_index != 0UL))
    {
        ed -> ux_synergy_fifo_index = (ULONG)UX_SYNERGY_HC_FIFO_D1;
    }
    else
    {
        /* For bulk and interrupt, use FIFO_C.  */
        ed -> ux_synergy_fifo_index = (ULONG)UX_SYNERGY_HC_FIFO_C;
    }

    /* Memorise the endpoint in the HCD structure. */
    hcd_synergy -> ux_hcd_synergy_ed_ptr[ed -> ux_synergy_pipe_index] = ed;

    /* Enable the auto FIFO buffer clear mode (for READ pipe with double buffer support). */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_D1FIFOSEL, (USHORT)UX_SYNERGY_HC_DFIFOSEL_DCLRM);
    /* Free the INTs now.  */
    TX_RESTORE

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

