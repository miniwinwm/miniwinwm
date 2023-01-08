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


/* Include necessary system files.  */

#include "ux_api.h"
#include "ux_dcd_synergy.h"
#include "ux_device_stack.h"
#include "ux_utility.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                RELEASE       */
/*                                                                        */
/*    ux_dcd_synergy_transfer_callback                     PORTABLE C     */
/*                                                            5.6         */
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is invoked under ISR when an event happens on a       */
/*    specific endpoint.                                                  */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_synergy                         Pointer to device controller    */
/*    transfer_request                    Pointer to transfer request     */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */ 
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_dcd_synergy_register_clear           Clear register              */
/*    ux_dcd_synergy_register_read            Read register               */
/*    ux_dcd_synergy_register_write           Write register              */
/*    ux_dcd_synergy_register_set             Set register                */
/*    _ux_device_stack_control_request_process Process control request    */ 
/*    _ux_utility_semaphore_get               Get semaphore               */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    SYNERGY Controller Driver                                           */
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
 * @brief  This function is invoked under ISR when an event happens on a specific endpoint.
 *
 * @param[in,out]  dcd_synergy       : Pointer to a DCD control block
 * @param[in,out]  transfer_request  : Pointer to USBX Device Transfer Request structure
 * @param[in,out]  interrupt_status  : Check if we have SETUP condition or BRDY or BEMP interrupt.
 * @param[in,out]  ctsq_mask         : Mask to isolate the CTSQ field.
 *
 * @retval UX_SUCCESS         Function is invoked under ISR successfully.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_transfer_callback(UX_DCD_SYNERGY *dcd_synergy,
            UX_SLAVE_TRANSFER *transfer_request, ULONG interrupt_status, ULONG ctsq_mask)
{
    UX_SLAVE_ENDPOINT * endpoint;
    UX_DCD_SYNERGY_ED * ed;
    UCHAR             * data_pointer;
    ULONG               fifo_length;
    UINT                status;

    /* Get the pointer to the logical endpoint from the transfer request.  */
    endpoint =  transfer_request -> ux_slave_transfer_request_endpoint;

    /* Get the synergy endpoint.  */
    ed =  (UX_DCD_SYNERGY_ED *) endpoint -> ux_slave_endpoint_ed;

    /* Get the pointer to the data buffer of the transfer request.  */
    data_pointer =  transfer_request -> ux_slave_transfer_request_data_pointer;

    /* Check if we have a SETUP condition.  */
    if (interrupt_status ==  UX_SYNERGY_DCD_INTSTS0_CTRT)
    {
        /* Isolate the CTSQ field.  */
        switch (ctsq_mask)
        {
        case UX_SYNERGY_DCD_INTSTS0_CTSQ_CTSE :
            /* There is an error in the state machine for SETUP transaction, revert to Idle and
            * wait for next SETUP.  */
            ed -> ux_dcd_synergy_ed_state =  UX_DCD_SYNERGY_ED_STATE_IDLE;
            /* Done here.  */
            return (UINT)UX_ERROR;

        case UX_SYNERGY_DCD_INTSTS0_CTSQ_SETUP :
            return(UX_SUCCESS);

        case UX_SYNERGY_DCD_INTSTS0_CTSQ_CRDS :
        case UX_SYNERGY_DCD_INTSTS0_CTSQ_CWDS :
        case UX_SYNERGY_DCD_INTSTS0_CTSQ_CWNDSS :
            /* We must have a valid SETUP packet.  This happens in 3 state machines : CRDS, CWDS, CWNDSS. */
            /* Clear VALID field.  */
            ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_INTSTS0, (USHORT)(~UX_SYNERGY_DCD_INTSTS0_VALID));
            
            /* We are in the SETUP phase.
             *   Read the USBREQ, USBVAL, USBINDX and USBLENG registers to build the SETUP packet.  */
            /* Set the data pointer to the Transfer request setup area.  */
            data_pointer = transfer_request -> ux_slave_transfer_request_setup;

            /* Store the request field.  */
            _ux_utility_short_put(data_pointer,
                    (USHORT) ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_USBREQ));
        
            /* Store the Value field.  */
            _ux_utility_short_put(data_pointer + UX_SETUP_VALUE,
                    (USHORT) ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_USBVAL));
        
            /* Store the Index field.  */
            _ux_utility_short_put(data_pointer + UX_SETUP_INDEX,
                    (USHORT) ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_USBINDX));
        
            /* Store the Length field.  */            
            _ux_utility_short_put(data_pointer + UX_SETUP_LENGTH,
                    (USHORT) ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_USBLENG));

            /* Clear the length of the data received.  */
            transfer_request -> ux_slave_transfer_request_actual_length =  0UL;
            
            /* Mark the phase as SETUP.  */
            transfer_request -> ux_slave_transfer_request_type = (ULONG)UX_TRANSFER_PHASE_SETUP;
            
            /* Mark the transfer as successful.  */
            transfer_request -> ux_slave_transfer_request_completion_code = (ULONG)UX_SUCCESS;
            
            /* Check if the transaction is IN call the Control Transfer dispatcher.  */
            if (*transfer_request -> ux_slave_transfer_request_setup & (UCHAR)UX_REQUEST_IN)
            {
                _ux_device_stack_control_request_process(transfer_request);
            }
            else
            {
                /* We are in a OUT transaction. Check if there is a data payload. If so, wait for the payload
                   to be delivered.  */
                if ((*(transfer_request -> ux_slave_transfer_request_setup + 6U) == 0U) &&
                    (*(transfer_request -> ux_slave_transfer_request_setup + 7U) == 0U))
                {
                    /* Call the Control Transfer dispatcher.  */
                    _ux_device_stack_control_request_process(transfer_request);
                }
                else
                {
                    /* The next transfer is Data coming from the host.  */
                    transfer_request -> ux_slave_transfer_request_phase = (ULONG)UX_TRANSFER_PHASE_DATA_IN;
        
                    /* Get the length we expect from the SETUP packet.  */
                    transfer_request -> ux_slave_transfer_request_requested_length =
                            _ux_utility_short_get(transfer_request -> ux_slave_transfer_request_setup + 6U);
                    
                    /* Reset what we have received so far.  */
                    transfer_request -> ux_slave_transfer_request_actual_length = 0UL;
                    
                    /* And reprogram the current buffer address to the beginning of the buffer.  */
                    transfer_request -> ux_slave_transfer_request_current_data_pointer =
                            transfer_request -> ux_slave_transfer_request_data_pointer;
            
                    /* Set PID to NAK for Control Endpoint.  */
                    ux_dcd_synergy_register_clear(dcd_synergy,
                            UX_SYNERGY_DCD_DCPCTR, (USHORT)UX_SYNERGY_DCD_PIPECTR_PID_MASK);

                    /* Clear the BRDY and BEMP status for this pipe.  */
                    ux_dcd_synergy_usb_status_register_clear (dcd_synergy,
                            UX_SYNERGY_DCD_BEMPSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));
                    ux_dcd_synergy_usb_status_register_clear (dcd_synergy,
                            UX_SYNERGY_DCD_BRDYSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));

                    /* We have a request for a OUT transaction from the host.  */
                    /* Clear the FIFO buffer memory. */
                    ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);

                    /* Set the current endpoint fifo.  */
                    ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, 0);
                
                    /* Enable the BRDY interrupt.  */
                    ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                       
                    /* Set PID to BUF for Control Endpoint.  */
                    ux_dcd_synergy_register_set(dcd_synergy,
                            UX_SYNERGY_DCD_DCPCTR, (USHORT)UX_SYNERGY_DCD_PIPECTR_PIDBUF);

                    /* Waiting for data on control endpoint.  */
                    ed -> ux_dcd_synergy_ed_state =  UX_DCD_SYNERGY_ED_STATE_DATA_RX;
                }                            
            }
            
            /* Check if the transaction is OUT and there is no data payload.  */
            if (((*transfer_request -> ux_slave_transfer_request_setup & (UCHAR)UX_REQUEST_IN) == 0U) &&
                 (*(transfer_request -> ux_slave_transfer_request_setup + 6U) == 0U) &&
                 (*(transfer_request -> ux_slave_transfer_request_setup + 7U) == 0U))
            {
                /* In the case of a SETUP followed by NO data payload, we let the controller reply to the next 
                   zero length IN packet. Reset the length to transfer. */
                transfer_request -> ux_slave_transfer_request_in_transfer_length =  0UL;
                transfer_request -> ux_slave_transfer_request_requested_length   =  0UL;
            
                /* Set the phase of the transfer to data OUT for status.  */
                transfer_request -> ux_slave_transfer_request_phase = (ULONG)UX_TRANSFER_PHASE_DATA_OUT;
        
                /* Control endpoint is status.  */
                ed -> ux_dcd_synergy_ed_state = (ULONG)UX_DCD_SYNERGY_ED_STATE_STATUS_TX;

                /* Set PID to BUF and CCPL for Control Endpoint to indicate STATUS phase.  */
                ux_dcd_synergy_register_set(dcd_synergy,
                        UX_SYNERGY_DCD_DCPCTR, (UX_SYNERGY_DCD_DCPCTR_PIDBUF | UX_SYNERGY_DCD_DCPCTR_CCPL));
            }            
            else
            {
                /* Check if data transfer is OUT.  */
                if ((*transfer_request -> ux_slave_transfer_request_setup & (UCHAR)UX_REQUEST_IN) == 0U)
                {
                    /* Set the state to RX.  */
                    ed -> ux_dcd_synergy_ed_state =  UX_DCD_SYNERGY_ED_STATE_DATA_RX;
                }
                else
                {
                   /* Set the state to TX.  */
                   ed -> ux_dcd_synergy_ed_state =  UX_DCD_SYNERGY_ED_STATE_DATA_TX;
                }
            }
            break;
        default:
            /* Currently CRSS and CWSS condition are not considered */
            break;
        }
    }
    else
    {
        /* Check if we have a BRDY/BEMP interrupt.  */
        if ((interrupt_status == UX_SYNERGY_DCD_INTSTS0_BRDY) || (interrupt_status == UX_SYNERGY_DCD_INTSTS0_BEMP))
        {
            /* Check Direction.  */
            if (transfer_request -> ux_slave_transfer_request_phase == (ULONG)UX_TRANSFER_PHASE_DATA_IN)
            {
                if(UX_TRUE == ed->ux_dcd_synergy_transfer_request_status)
                {
                    /* Abort the transfer as the semaphore expired/timeout.  */
                    ux_dcd_synergy_transfer_abort(dcd_synergy, transfer_request);
                    transfer_request->ux_slave_transfer_request_status = (ULONG)UX_TRANSFER_STATUS_ABORT;
                    ed->ux_dcd_synergy_transfer_request_status = UX_FALSE;
                }
                if ((dcd_synergy->ux_dcd_synergy_using_dma == (UCHAR)0xff) && (dcd_synergy->ux_dcd_synergy_dma_ep_index == ed -> ux_dcd_synergy_ed_index))
                {
                        /* Set PID to NAK for non Control End-points.  */
                        ux_dcd_synergy_register_clear(dcd_synergy,
                                UX_SYNERGY_DCD_PIPE1CTR  + ((dcd_synergy->read_pipe_number - 1UL) * 2UL),
                                UX_SYNERGY_DCD_PIPECTR_PID_MASK);
                        ux_dcd_synergy_register_clear (dcd_synergy, UX_SYNERGY_DCD_D1FIFOSEL, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_DREQE);
                        /* Disable the Ready interrupt.  */
                        ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
                        dcd_synergy->ux_dcd_synergy_number_of_dma_ep_packets = (ULONG)0;
                        dcd_synergy->ux_dcd_synergy_using_dma = (UCHAR)0;
                        dcd_synergy->ux_dcd_synergy_dma_ep_index = (ULONG)0;
                }

                else
                {
                    /* Get the size of the transfer, used for a IN transaction only.  */
                    fifo_length =  transfer_request -> ux_slave_transfer_request_requested_length;

                    /* Keep the FIFO length in the endpoint.  */
                    ed -> ux_dcd_synergy_ed_payload_length =  fifo_length;

                    /* Check if the endpoint size is bigger that data requested. */
                    if (fifo_length > endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)
                    {
                        /* Adjust the transfer size.  */
                        ed -> ux_dcd_synergy_ed_payload_length =  endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
                    }

                    /* Point the FIFO buffer to the current transfer request buffer address.  */
                    ed -> ux_dcd_synergy_ed_payload_address =
                            transfer_request -> ux_slave_transfer_request_current_data_pointer;

                    /* Check for control pipe fifoc read status*/
                    if (ed -> ux_dcd_synergy_ed_index == 0UL)
                    {
                        status = ux_dcd_synergy_fifoc_read(dcd_synergy, ed);
                        if (status == UX_SYNERGY_DCD_FIFO_READING)
                        {
                            /* Enable the Ready interrupt.  */
                            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                        }
                        else
                        {
                            /* Disable the Ready interrupt.  */
                            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
                        }
                        status = (UINT)UX_SUCCESS;
                    }
                    else
                    {
                        status = ux_dcd_synergy_fifo_read(dcd_synergy, ed);
                        if (status == UX_SYNERGY_DCD_FIFO_READING)
                        {
                            /* Enable the Ready interrupt.  */
                            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                        }
                        else
                        {
                            /* Disable the Ready interrupt.  */
                            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
                        }
                        status = (UINT)UX_SUCCESS;
                    }

                    /* Get the actual length received.  */
                    fifo_length = ed -> ux_dcd_synergy_ed_actual_length;

                    /* Adjust the data pointer.  */
                    transfer_request -> ux_slave_transfer_request_current_data_pointer += fifo_length;

                    /* Adjust the transfer length remaining.  */
                    transfer_request -> ux_slave_transfer_request_in_transfer_length -= fifo_length;

                    /* Update the length of the data transmitted.  */
                    transfer_request -> ux_slave_transfer_request_actual_length += fifo_length;

                    /* Are we done with this transfer ? */
                    if ((transfer_request -> ux_slave_transfer_request_actual_length ==
                            transfer_request -> ux_slave_transfer_request_requested_length) ||
                            (fifo_length != endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize))
                    {
                        /* Set the completion code to no error.  */
                        transfer_request -> ux_slave_transfer_request_completion_code = (ULONG)UX_SUCCESS;

                        /* Disable the Ready interrupt.  */
                        ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);

                        /* Check what type of endpoint we are using, Control or non Control.  */
                        if (ed -> ux_dcd_synergy_ed_index != 0UL)
                        {
                            /* The transfer is completed.  */
                            transfer_request -> ux_slave_transfer_request_status = (ULONG)UX_TRANSFER_STATUS_COMPLETED;

                            /* Non control endpoint operation, use semaphore.  */
#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
                            _ux_utility_semaphore_put (&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore);
#else
                            _ux_utility_semaphore_put(&transfer_request -> ux_slave_transfer_request_semaphore);
#endif
                        }
                        else
                        {
                            /* Check the phase for control endpoint.  */
                            if (ed -> ux_dcd_synergy_ed_state ==  UX_DCD_SYNERGY_ED_STATE_DATA_RX)
                            {
                                /* We are using a Control endpoint on a OUT transaction and there was a payload.  */
                                _ux_device_stack_control_request_process(transfer_request);

                                /* Set the state to STATUS phase TX.  */
                                ed -> ux_dcd_synergy_ed_state =  UX_DCD_SYNERGY_ED_STATE_STATUS_TX;

                                /* We are using a Control endpoint,
                                 * if there is a callback, invoke it. We are still under ISR.  */
                                if (transfer_request -> ux_slave_transfer_request_completion_function)
                                {
                                    transfer_request ->
                                    ux_slave_transfer_request_completion_function (transfer_request);
                                }

                                /* In the case of a SETUP with data transitioning to STATUS let the controller
                                 *  reply to the next zero length IN packet. Reset the length to transfer. */
                                transfer_request -> ux_slave_transfer_request_in_transfer_length =  0UL;
                                transfer_request -> ux_slave_transfer_request_requested_length   =  0UL;

                                /* Set the phase of the transfer to data OUT for status.  */
                                transfer_request -> ux_slave_transfer_request_phase = (ULONG)UX_TRANSFER_PHASE_DATA_OUT;

                                /* Control endpoint is status.   */
                                ed -> ux_dcd_synergy_ed_state = (ULONG)UX_DCD_SYNERGY_ED_STATE_STATUS_TX;

                                /* Set PID to BUF and CCPL for Control Endpoint to indicate STATUS phase.  */
                                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR,
                                        (USHORT)(UX_SYNERGY_DCD_DCPCTR_PIDBUF | UX_SYNERGY_DCD_DCPCTR_CCPL));
                            }
                        }
                    }
                    else
                    {
                        /* Set PID to BUF. Isolate Control endpoint and others.  */
                        if (ed -> ux_dcd_synergy_ed_index == 0UL)
                        {
                            /* Set PID to BUF for Control Endpoint.  */
                            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR,
                                                        (USHORT)UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                        }
                        else
                        {
                            /* Set PID to BUF for non Control Endpoints.  Continue to receive.  */
                            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                                        ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL),
                                                        (USHORT)UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                        }
                    }
                }
            }
            else
            {
                /** Abort the transfer as the semaphore expired/timeout.  */
                if(UX_TRUE == ed->ux_dcd_synergy_transfer_request_status)
                {
                    ULONG      pipectr_reg;
                    pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                            UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));

                    while ( pipectr_reg & UX_SYNERGY_DCD_DCPCTR_INBUFM )
                    {
                        pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                                UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));
                    }

                    ux_dcd_synergy_transfer_abort(dcd_synergy, transfer_request);
                    transfer_request->ux_slave_transfer_request_status = (ULONG)UX_TRANSFER_STATUS_ABORT;
                    ed->ux_dcd_synergy_transfer_request_status = UX_FALSE;

                }

                else
                {
                  /* Check if we have data to send.  */
                  if (transfer_request -> ux_slave_transfer_request_in_transfer_length == 0UL)
                  {
                    /* There is no data to send but we may need to send a Zero Length Packet.  */
                    if (transfer_request -> ux_slave_transfer_request_force_zlp == (ULONG)UX_TRUE)
                    {
                        /* Reset the FIFO payload length.  */
                        ed -> ux_dcd_synergy_ed_payload_length =  0UL;

                        /* Check for control pipe fifoc write status*/
                        if (ed -> ux_dcd_synergy_ed_index == 0UL)
                        {
                            status =  ux_dcd_synergy_fifoc_write(dcd_synergy, ed);
                            if (status == UX_SYNERGY_DCD_FIFO_WRITING)
                            {
                                /* Enable the Ready interrupt.  */
                                ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                            }
                            else
                            {
                                /* Disable the Ready interrupt.  */
                                ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
                            }
                            /* Enable the Buffer empty interrupt.  */
                           ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                           status = (UINT)UX_SUCCESS;
                        }
                        else
                        {
                            /* Write the empty buffer to the pipe.  */
                            status = ux_dcd_synergy_fifod_write(dcd_synergy, ed);
                            if (status == UX_SYNERGY_DCD_FIFO_WRITING)
                            {
                                /* Enable the Ready interrupt.  */
                                ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                            }
                            else
                            {
                                /* Disable the Ready interrupt.  */
                                ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
                                /* Enable the Buffer empty interrupt.  */
                               ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                            }
                           status = (UINT)UX_SUCCESS;
                        }
                        /* Check status.  */
                        if (status != (UINT)UX_ERROR)
                        {                           
                            /* Set PID to BUF. Isolate Control endpoint and others.  */
                            if (ed -> ux_dcd_synergy_ed_index == 0UL)
                            {
                                /* Set PID to BUF for Control Endpoint.  */
                                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR,
                                                            (USHORT)UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                            }
                            else
                            {
                                /* Set PID to BUF for non Control Endpoints.  */
                                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                                            ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL),
                                                            (USHORT)UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                            }
                        }

                        /* Reset the ZLP condition.  */
                        transfer_request -> ux_slave_transfer_request_force_zlp = (ULONG)UX_FALSE;
                    }
                    else
                    {
                        /* Set the completion code to no error.  */
                        transfer_request -> ux_slave_transfer_request_completion_code = (ULONG)UX_SUCCESS;

                        /* Disable the Buffer empty interrupt.  */
                        ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);

                        /* Check what type of endpoint we are using, Control or non Control.  */
                        if (ed -> ux_dcd_synergy_ed_index != 0UL)
                        {
                            /* The transfer is completed.  */
                            transfer_request -> ux_slave_transfer_request_status = (ULONG)UX_TRANSFER_STATUS_COMPLETED;

                            /* Non control endpoint operation, use semaphore.  */
#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
                            _ux_utility_semaphore_put (&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore);
#else
                            _ux_utility_semaphore_put(&transfer_request -> ux_slave_transfer_request_semaphore);
#endif
                        }                            
                        else 
                        {
                            /* We get here when we may have a transition from DATA phase to STATUS phase
                             * on a control transfer.  */
                            if(ed -> ux_dcd_synergy_ed_state == (ULONG)UX_DCD_SYNERGY_ED_STATE_DATA_TX)
                            {
                                /* We need to complete the Control transfer by a status phase.  */
                                transfer_request -> ux_slave_transfer_request_in_transfer_length =  0UL;
                                transfer_request -> ux_slave_transfer_request_requested_length   =  0UL;
                
                                /* Set the phase of the transfer to data OUT for status.  */
                                transfer_request -> ux_slave_transfer_request_phase = (ULONG)UX_TRANSFER_PHASE_DATA_OUT;
                
                                /* Control endpoint is status.   */
                                ed -> ux_dcd_synergy_ed_state = (ULONG)UX_DCD_SYNERGY_ED_STATE_STATUS_TX;

                                /* Set PID to BUF and CCPL for Control Endpoint to indicate STATUS phase.  */
                                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR,
                                        (UX_SYNERGY_DCD_DCPCTR_PIDBUF | UX_SYNERGY_DCD_DCPCTR_CCPL));
                            }

                            /* We are using a Control endpoint,
                             * if there is a callback, invoke it. We are still under ISR.  */
                            if (transfer_request -> ux_slave_transfer_request_completion_function)
                            {
                                transfer_request -> ux_slave_transfer_request_completion_function (transfer_request);
                            }
                        }
                    }
                }
                else
                {
                    /* Get the size of the transfer, used for a IN transaction only.  */
                    fifo_length =  transfer_request -> ux_slave_transfer_request_in_transfer_length;
    
                    /* Check if the endpoint size is bigger that data requested. */
                    if (fifo_length > endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)
                    {            
                        /* Adjust the transfer size.  */
                        fifo_length =  endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
                    }

                    /* Save the amount of bytes to transfer here.  */
                    ed -> ux_dcd_synergy_ed_packet_length = fifo_length;

                    /* Point the FIFO buffer to the current transfer request buffer address.  */
                    ed -> ux_dcd_synergy_ed_payload_address =  transfer_request ->
                            ux_slave_transfer_request_current_data_pointer;

                    /* Check for control pipe fifoc write status*/
                    if (ed -> ux_dcd_synergy_ed_index == 0UL)
                    {
                        status =  ux_dcd_synergy_fifoc_write(dcd_synergy, ed);

                        if (status == UX_SYNERGY_DCD_FIFO_WRITING)
                        {
                            /* Enable the Ready interrupt.  */
                            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                        }
                        else
                        {
                            /* Disable the Ready interrupt.  */
                            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
                        }
                        /* Enable the Buffer empty interrupt.  */
                       ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
                       status = (UINT)UX_SUCCESS;
                    }
                    else
                    {
                        ux_dcd_synergy_fifod_write(dcd_synergy, ed);

                        /* Enable the Buffer empty interrupt.  */
                        ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);

                        status = (UINT)UX_SUCCESS;
                    }

                   /* Keep the FIFO length in the endpoint.  */
                    ed -> ux_dcd_synergy_ed_payload_length -=  fifo_length;
            
                    /* Adjust the data pointer.  */
                    transfer_request -> ux_slave_transfer_request_current_data_pointer += fifo_length;
                    
                    /* Adjust the transfer length remaining.  */
                    transfer_request -> ux_slave_transfer_request_in_transfer_length -= fifo_length;

                    /* Update the length of the data transmitted.  */
                    transfer_request -> ux_slave_transfer_request_actual_length += fifo_length;

                    /* Check status.  */
                    if (status != (UINT)UX_ERROR)
                    {                           
                        /* Set PID to BUF. Isolate Control endpoint and others.  */
                        if (ed -> ux_dcd_synergy_ed_index == 0UL)
                        {
                            /* Set PID to BUF for Control Endpoint.  */
                            ux_dcd_synergy_register_set(dcd_synergy,
                                                        UX_SYNERGY_DCD_DCPCTR, (USHORT)UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                        }
                        else
                        {
                            /* Set PID to BUF for non Control Endpoints.  */
                            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                                        ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL),
                                                        (USHORT)UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                        }
                    }
                  }
                }
            }
        }
    }

    /* We are done.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

