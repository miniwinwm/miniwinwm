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
#include "ux_utility.h"
#include "ux_device_stack.h"
#include "sf_el_ux_dcd_common.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                RELEASE       */
/*                                                                        */
/*    ux_dcd_synergy_transfer_request                      PORTABLE C     */
/*                                                            5.6         */
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will initiate a transfer to a specific endpoint.      */
/*    If the endpoint is IN, the endpoint register will be set to accept  */
/*    the request.                                                        */
/*                                                                        */
/*    If the endpoint is IN, the endpoint FIFO will be filled with the    */
/*    buffer and the endpoint register set.                               */
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
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_dcd_synergy_register_read             Read register              */
/*    ux_dcd_synergy_register_set              Set register               */
/*    ux_dcd_synergy_register_write            Write register             */
/*    _ux_utility_semaphore_get                Get semaphore              */ 
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
 * @brief  This function will initiate a transfer to a specific endpoint.
 *         If the endpoint is IN, the endpoint register will be set to accept the request.
 *         If the endpoint is IN, the endpoint FIFO will be filled with the buffer and the endpoint
 *         register set.
 *
 * @param[in,out]  dcd_synergy       : Pointer to a DCD control block
 * @param[in,out]  transfer_request  : Pointer to transfer request
 *
 * @retval UX_SUCCESS                                 Transfer to a specific endpoint is initiated successfully.
 * @retval ux_slave_transfer_request_completion_code  Pointer to structure UX_SLAVE_TRANSFER(transfer request completion code).
 * @retval UX_TRANSFER_ERROR                          Transfer is completed with error.
 *
 * @return               See @ref Common_Error_Codes for other possible return codes or causes.
 *                       This function calls:
 *                       * ux_dcd_synergy_buffer_write()
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_transfer_request(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_TRANSFER *transfer_request)
{
    UX_DCD_SYNERGY_ED * ed;
    UCHAR             * fifo_buffer;
    ULONG               fifo_length;
    UX_SLAVE_ENDPOINT * endpoint;
    UINT                status;
    ULONG               pipectr_reg;
    ULONG               read_counter;
    UINT                number_of_dma_packets = 0;
    UINT                number_of_bytes_to_transfer = 0;
    UINT                remaining_bytes = 0;
    ULONG               synergy_register = 0;


#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Macro for saving and restoring the interrupts to support concurrent access*/
    TX_INTERRUPT_SAVE_AREA
#endif
    /* Get the pointer to the logical endpoint from the transfer request.  */
    endpoint =  transfer_request -> ux_slave_transfer_request_endpoint;

    /* Get the physical endpoint from the logical endpoint.  */
    ed =  (UX_DCD_SYNERGY_ED *) endpoint -> ux_slave_endpoint_ed;

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts. */
    TX_DISABLE
#endif
    /* Set PID to NAK. Isolate Control endpoint and others.  */
    if (ed -> ux_dcd_synergy_ed_index == 0UL)
    {
        /* Set PID to NAK for Control Endpoint.  */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_DCPCTR, UX_SYNERGY_DCD_PIPECTR_PID_MASK);
    }
    else
    {
        pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));

        read_counter = 0UL;
        while ( pipectr_reg & UX_SYNERGY_DCD_DCPCTR_INBUFM )
        {
            pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                    UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));
            if( (transfer_request->ux_slave_transfer_request_timeout != (ULONG)UX_WAIT_FOREVER) && (read_counter > UX_SYNERGY_DCD_DFIFOSEL_MBW_32) )
            {
                /* Clear the PIPEMASK, MBW field, the reading/writing width and the previous endpoint index.*/
                synergy_register &= ~((ULONG)(UX_SYNERGY_DCD_CFIFOSEL_CURPIPE_MASK | UX_SYNERGY_DCD_CFIFOSEL_MBW_MASK));

                /* Add the current direction and the new endpoint index.  */
                synergy_register |= ed->ux_dcd_synergy_ed_index;

                if( UX_SYNERGY_DCD_FIFO_D0 == ed -> ux_dcd_synergy_ed_fifo_index )
                {
                    /** Set the ACLRM bit to 1 and then to 0 for clearing FIFO buffers. */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_PIPECTR_ACLRM);
                    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_PIPECTR_ACLRM);

                    ux_dcd_synergy_register_set(dcd_synergy, (ULONG) UX_SYNERGY_DCD_D0FIFOSEL, (USHORT)ed->ux_dcd_synergy_ed_index);

                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
                    ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_D0FIFOSEL, (USHORT) synergy_register);
                }

                else if( UX_SYNERGY_DCD_FIFO_D1 == ed -> ux_dcd_synergy_ed_fifo_index )
                {
                    /** Clear the D1 FIFO buffer memory. */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D1FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
                    ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_D1FIFOSEL, (USHORT) synergy_register);
                }
                else
                {
                    /** Clear the CFIFO buffer memory. */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
                    ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL, (USHORT) synergy_register);
                }
            }

            read_counter++;
        }

        /* Set PID to NAK for non Control Endpoints.  */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_PIPECTR_PID_MASK);
    }

    /* Clear the BRDY and BEMP status for this pipe.  */
    ux_dcd_synergy_usb_status_register_clear (dcd_synergy, UX_SYNERGY_DCD_BEMPSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));
    ux_dcd_synergy_usb_status_register_clear (dcd_synergy, UX_SYNERGY_DCD_BRDYSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif
    /** Clean the pending semaphore due to timeout on this transfer request. */
    if( UX_TRUE == ed->ux_dcd_synergy_transfer_request_status )
    {
        ed->ux_dcd_synergy_transfer_request_status = UX_FALSE;

        if( ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore.tx_semaphore_count > 0UL )
        {
            _ux_utility_semaphore_get(&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore,
                    transfer_request -> ux_slave_transfer_request_timeout);
        }
    }

    /* Check for transfer direction.  */
    if (transfer_request -> ux_slave_transfer_request_phase == (ULONG)UX_TRANSFER_PHASE_DATA_OUT)
    {
        /* Data Out. So we expect a IN transaction from the host. So Device is "writing" the data
         * If device is not using DMA, or using control pipe or data pipe with <= endpoint
         * buffer size use the old logic */
        if ((dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx == NULL) /* if DMA is not configured for this pipe */
                || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_CD) /* or if the pipe is control pipe */
                || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_C0) /* or if the data pipe using CFIFO */
                || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_C1) /* or if the data pipe using CFIFO */
                ||  /* or if data-pipe configured for DMA, using D0/ D1 FIFO and
                        size is less than or equal to end-point size */
                        (
                        ((ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_D0)
                        || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_D1))
                        &&
                        ((transfer_request -> ux_slave_transfer_request_requested_length) <=
                        (endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)))
                       )
        {
            /* Get the size of the transfer, used for a IN transaction only.  */
            fifo_length =  transfer_request -> ux_slave_transfer_request_requested_length;

            /* Keep the FIFO length in the endpoint.  */
            ed -> ux_dcd_synergy_ed_payload_length =  fifo_length;

            /* Check if the endpoint size is bigger that data requested. */
            if(fifo_length > endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)
            {
                /* Adjust the transfer size.  */
                fifo_length =  endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
            }

            /* Point the FIFO buffer to the current transfer request buffer address.  */
            fifo_buffer =  transfer_request -> ux_slave_transfer_request_data_pointer;

            /* Keep the FIFO length in the endpoint.  */
            ed -> ux_dcd_synergy_ed_payload_address =  fifo_buffer;

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif
            /* Set the current fifo port.  */
            ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, UX_SYNERGY_DCD_CFIFOSEL_ISEL);

            /* Clear the FIFO buffer memory. */
            if((UX_SYNERGY_DCD_FIFO_CD == ed->ux_dcd_synergy_ed_fifo_index) || (UX_SYNERGY_DCD_FIFO_C1 == ed->ux_dcd_synergy_ed_fifo_index) || (UX_SYNERGY_DCD_FIFO_C0 == ed->ux_dcd_synergy_ed_fifo_index))
            {
            	ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            }

#if !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)

            else if(UX_SYNERGY_DCD_FIFO_D0 == ed->ux_dcd_synergy_ed_fifo_index)
            {
            	ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            }
            else if( UX_SYNERGY_DCD_FIFO_D1 == ed->ux_dcd_synergy_ed_fifo_index)
            {
            	ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D1FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            }
#endif

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

            /* Check status.  */
            if (status != (UINT)UX_ERROR)
            {
                /* Adjust the FIFO length in the endpoint.  */
                ed -> ux_dcd_synergy_ed_payload_length -=  fifo_length;

                /* Adjust the data pointer.  */
                transfer_request -> ux_slave_transfer_request_current_data_pointer += fifo_length;

                /* Update the length of the data transmitted.  */
                transfer_request -> ux_slave_transfer_request_actual_length += fifo_length;

                /* Adjust the transfer length remaining.  */
                transfer_request -> ux_slave_transfer_request_in_transfer_length -= fifo_length;

                /* Set PID to BUF. Isolate Control endpoint and others.  */
                if (ed -> ux_dcd_synergy_ed_index == 0UL)
                {
                    /* Set PID to BUF for Control Endpoint.  */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR, UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                }
                else
                {
                    /* Set PID to BUF for non Control Endpoints.  */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                                ((ed -> ux_dcd_synergy_ed_index - 1) * 2),
                                                UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                }
            }

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

            /* If the end-point is a Control end-point, all this is happening under Interrupt and
             * there is no thread to suspend.  */
            if (ed -> ux_dcd_synergy_ed_index != 0UL)
            {
                /* We should wait for the semaphore to wake us up.  */
#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
                status =  _ux_utility_semaphore_get(&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore,
                        transfer_request -> ux_slave_transfer_request_timeout);
#else
                status =  _ux_utility_semaphore_get(&transfer_request -> ux_slave_transfer_request_semaphore,
                        transfer_request -> ux_slave_transfer_request_timeout);
#endif
/* Check the completion code. */
                if (status != (UINT)UX_SUCCESS)
                {
                    ed->ux_dcd_synergy_transfer_request_status = UX_TRUE;


                    pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                            UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));

                    while ( (transfer_request->ux_slave_transfer_request_status != (ULONG)UX_TRANSFER_STATUS_ABORT) && ( ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore.tx_semaphore_count < 1UL) )
                    {
                        pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                                UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));
                    }

                    transfer_request->ux_slave_transfer_request_status =  (ULONG)UX_TRANSFER_STATUS_ABORT;
                    return (status);
                }

                /* Check the transfer request completion code. We may have had a BUS reset or
                   a device disconnection.  */
                if (transfer_request -> ux_slave_transfer_request_completion_code != (ULONG)UX_SUCCESS)
                {
                    return (UINT)(transfer_request -> ux_slave_transfer_request_completion_code);
                }
            }
        }
        /* Use the new DMA logic */
        else
        {
            /* Current DMA configuration,  can transfer 1024 blocks - in one DMA call
             * with current end point size being fixed at 64 bytes for FS - this leads to 64K bytes
             * of transfer at a time. Also for HS end point size being fixed at 512 bytes - this leads to 512K
             * bytes of transfer at a time.So calculate how many times the DMA to be done */
            dcd_synergy->ux_dcd_synergy_dma_packets =
                    (UINT)((transfer_request -> ux_slave_transfer_request_requested_length)/
                            ((endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) * 1024));

            /* Adjust number of packets.
             * i.e. MaxPacketSize (64 bytes in FS and 512 bytes in HS) to MaxPacketSize*1024 (64K in FS and 512K in HS) number_of_dma_packets = 1
             * from 64K+1 in FS (512K+1 in HS) to 128K in FS (1024K i.e. 1MB + 1 in HS) number_of_dma_packets = 2 and so on...
             */
            dcd_synergy->ux_dcd_synergy_dma_packets = dcd_synergy->ux_dcd_synergy_dma_packets + 1;

            for (number_of_dma_packets=0U; number_of_dma_packets < dcd_synergy->ux_dcd_synergy_dma_packets;
                    number_of_dma_packets++)
            {
                if (transfer_request ->ux_slave_transfer_request_in_transfer_length <
                        ((endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) * 1024))
                {
                    number_of_bytes_to_transfer =
                            (UINT)(transfer_request ->ux_slave_transfer_request_in_transfer_length);

                    /* Make sure we call DMA only with multiple of endpoint size */
                    remaining_bytes =
                       (UINT)(number_of_bytes_to_transfer % (UINT)(endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize));

                    number_of_bytes_to_transfer = number_of_bytes_to_transfer - remaining_bytes;
                }
                else
                {
                    number_of_bytes_to_transfer =
                            (UINT)((endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) * 1024);
                }

                /* When the data size is just one packet (64 bytes in FS and 512 bytes in HS) more than 1 DMA configuration i.e.
                 * 64K to next 64 byte in FS (512K to next 512 bytes), in 2nd iteration onwards in for loop - data would be
                 * transferred by CPU and number_of_bytes_to_transfer would be 0 */
                if (number_of_bytes_to_transfer != 0U)
                {
                    /* Set the current fifo port.  */
                    ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, UX_SYNERGY_DCD_CFIFOSEL_ISEL);

                    /* Clear the FIFO buffer memory. */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);

                    fifo_buffer =  transfer_request -> ux_slave_transfer_request_current_data_pointer;

                    /* Keep the FIFO length in the endpoint.  */
                    ed -> ux_dcd_synergy_ed_payload_address =  fifo_buffer;

                    /* Call the new API for DMA transfer */
                    status = ux_dcd_synergy_fifod_write_dma (dcd_synergy, ed, number_of_bytes_to_transfer);
                    if (UX_SYNERGY_DCD_FIFO_WRITE_ERROR == status)
                    {
                        return ( UX_SYNERGY_DCD_TIMEOUT_ERROR);
                    }

                    ed -> ux_dcd_synergy_ed_payload_length -=  number_of_bytes_to_transfer;

                    /* Adjust the data pointer.  */
                    transfer_request -> ux_slave_transfer_request_current_data_pointer += number_of_bytes_to_transfer;

                    /* Adjust the transfer length remaining.  */
                    transfer_request -> ux_slave_transfer_request_in_transfer_length -= number_of_bytes_to_transfer;

                    /* Update the length of the data transmitted.  */
                    transfer_request -> ux_slave_transfer_request_actual_length += number_of_bytes_to_transfer;
                }
            }


#if defined(UX_DEVICE_COMPOSITE_ENABLE)
/* Entering critical area. Disable interrupts.  */
TX_DISABLE
#endif
            /* Clear the BRDY and BEMP status for this pipe.  */
            ux_dcd_synergy_usb_status_register_clear (dcd_synergy, UX_SYNERGY_DCD_BEMPSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));
            ux_dcd_synergy_usb_status_register_clear (dcd_synergy, UX_SYNERGY_DCD_BRDYSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
/* Restore interrupts.  */
TX_RESTORE
#endif
            if (remaining_bytes != 0U)
            {
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
/* Entering critical area. Disable interrupts.  */
TX_DISABLE
#endif
                /* Get the size of the transfer, used for a IN transaction only.  */
                fifo_length =  transfer_request -> ux_slave_transfer_request_in_transfer_length;

                /* Keep the FIFO length in the endpoint.  */
                ed -> ux_dcd_synergy_ed_payload_length =  fifo_length;

                /* Check if the endpoint size is bigger that data requested. */
                if(fifo_length > endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)
                {
                    /* Adjust the transfer size.  */
                    fifo_length =  endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
                }

                /* Point the FIFO buffer to the current transfer request buffer address.  */
                fifo_buffer =  transfer_request -> ux_slave_transfer_request_current_data_pointer;

                /* Keep the FIFO length in the endpoint.  */
                ed -> ux_dcd_synergy_ed_payload_address =  fifo_buffer;

                /* Set the current fifo port.  */
                ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, UX_SYNERGY_DCD_CFIFOSEL_ISEL);

                /* Clear the FIFO buffer memory. */
                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);

                /* Point the FIFO buffer to the current transfer request buffer address.  */
                fifo_buffer =  transfer_request -> ux_slave_transfer_request_current_data_pointer;

                /* Keep the FIFO length in the endpoint.  */
                ed -> ux_dcd_synergy_ed_payload_address =  fifo_buffer;

                /* Write the buffer to the pipe.  */
                status =  ux_dcd_synergy_buffer_write(dcd_synergy, ed);

                /* Check status.  */
                if (status != (UINT)UX_ERROR)
                {
                    /* Adjust the FIFO length in the endpoint.  */
                    ed -> ux_dcd_synergy_ed_payload_length -=  fifo_length;

                    /* Adjust the data pointer.  */
                    transfer_request -> ux_slave_transfer_request_current_data_pointer += fifo_length;

                    /* Update the length of the data transmitted.  */
                    transfer_request -> ux_slave_transfer_request_actual_length += fifo_length;

                    /* Adjust the transfer length remaining.  */
                    transfer_request -> ux_slave_transfer_request_in_transfer_length -= fifo_length;

                    /* Set PID to BUF. Isolate Control endpoint and others.  */
                    if (ed -> ux_dcd_synergy_ed_index == 0UL)
                    {
                        /* Set PID to BUF for Control Endpoint.  */
                        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR, UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                    }
                    else
                    {
                        /* Set PID to BUF for non Control Endpoints.  */
                        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                                    ((ed -> ux_dcd_synergy_ed_index - 1) * 2),
                                                    UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                    }
                }
                else
                {
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

                    /* We have an error on the write to the FIFO.  */
                    return (UINT)UX_ERROR;
                }

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

                /* If the endpoint is a Control endpoint, all this is happening under Interrupt and there is no
                   thread to suspend.  */
                if (ed -> ux_dcd_synergy_ed_index != 0UL)
                {
                    /* We should wait for the semaphore to wake us up.  */
#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
                    status =  _ux_utility_semaphore_get(&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore,
                            transfer_request -> ux_slave_transfer_request_timeout);
#else
                    status =  _ux_utility_semaphore_get(&transfer_request -> ux_slave_transfer_request_semaphore,
                            transfer_request -> ux_slave_transfer_request_timeout);
#endif
                    /* Check the completion code. */
                    if (status != (UINT)UX_SUCCESS)
                    {
                        ux_dcd_synergy_transfer_abort(dcd_synergy, transfer_request);
                        return (status);
                    }

                    /* Check the transfer request completion code. We may have had a BUS reset or
                     * a device disconnection.  */
                    if (transfer_request ->ux_slave_transfer_request_completion_code != (ULONG)UX_SUCCESS)
                    {
                        return (UINT)(transfer_request -> ux_slave_transfer_request_completion_code);
                    }
                }
            }
            /* Update completion code and status */
            else
            {
                /* Set the completion code to no error.  */
                transfer_request -> ux_slave_transfer_request_completion_code = (ULONG)UX_SUCCESS;
                /* The transfer is completed.  */
                transfer_request -> ux_slave_transfer_request_status = (ULONG)UX_TRANSFER_STATUS_COMPLETED;
            }

            return (UINT)UX_SUCCESS;
        }
    }
    else
    {
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif
        /* To begin with disable BEMP and BRDY interrupts */
        ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);

        ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif
        if ((dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx == NULL) /* if DMA is not configured for this pipe */
                || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_CD) /* or if the pipe is control pipe */
                || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_C0) /* or if the data pipe using CFIFO */
                || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_C1) /* or if the data pipe using CFIFO */
                ||  /* or if data-pipe configured for DMA, using D0/ D1 FIFO and
                        size is less than or equal to end-point size */
                        (
                        ((ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_D0)
                        || (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_D1))
                        &&
                        ((transfer_request -> ux_slave_transfer_request_requested_length) <=
                        (endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)))
                       )
        {
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif
            if (ed -> ux_dcd_synergy_ed_index != 0UL)
            {
                /* Clear and disable transaction counter.  */
                ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_PIPESEL, (USHORT)(ed -> ux_dcd_synergy_ed_index));
                ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPECFG, (USHORT)UX_SYNERGY_DCD_PIPECFG_BFRE);
                ux_dcd_synergy_register_set(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)),  (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRCLR);
                ux_dcd_synergy_register_clear(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)), (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRENB);
            }

            /* We have a request for a OUT transaction from the host.
             * Set the current endpoint fifo. */
            ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, 0);

            /* Clear the FIFO buffer memory. */
            if((UX_SYNERGY_DCD_FIFO_CD == ed->ux_dcd_synergy_ed_fifo_index) || (UX_SYNERGY_DCD_FIFO_C1 == ed->ux_dcd_synergy_ed_fifo_index) || (UX_SYNERGY_DCD_FIFO_C0 == ed->ux_dcd_synergy_ed_fifo_index))
            {
            	ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            }
#if !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)

            else if(UX_SYNERGY_DCD_FIFO_D0 == ed->ux_dcd_synergy_ed_fifo_index)
            {
            	ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            }
            else if( UX_SYNERGY_DCD_FIFO_D1 == ed->ux_dcd_synergy_ed_fifo_index)
            {
            	ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D1FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            }
#endif

            /* Enable the BRDY interrupt.  */
            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);

            /* Set PID to BUF. Isolate Control endpoint and others.  */
            if (ed -> ux_dcd_synergy_ed_index == 0UL)
            {
                /* Set PID to BUF for Control Endpoint.  */
                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR, UX_SYNERGY_DCD_PIPECTR_PIDBUF);
            }
            else
            {
                /* Set PID to BUF for non Control Endpoints.  */
                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                            ((ed -> ux_dcd_synergy_ed_index - 1) * 2),
                                            UX_SYNERGY_DCD_PIPECTR_PIDBUF);
            }

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

            /* If the end-point is a Control end-point, all this is happening under Interrupt and there is no
             * thread to suspend.  */
            if (ed -> ux_dcd_synergy_ed_index != 0UL)
            {
                /* We should wait for the semaphore to wake us up.  */
#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
                status =  _ux_utility_semaphore_get(&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore,
                        transfer_request -> ux_slave_transfer_request_timeout);
#else
                status =  _ux_utility_semaphore_get(&transfer_request -> ux_slave_transfer_request_semaphore,
                        transfer_request -> ux_slave_transfer_request_timeout);
#endif
                /* Check the completion code. */
                if ((UINT)UX_SUCCESS != status)
                {
                    ed->ux_dcd_synergy_transfer_request_status = UX_TRUE;
                    pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                            UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));

                    while( (transfer_request->ux_slave_transfer_request_status != (ULONG)UX_TRANSFER_STATUS_ABORT) && ( ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore.tx_semaphore_count < 1UL) )
                    {
                        pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                                UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));
                    }

                    transfer_request->ux_slave_transfer_request_status = (ULONG)UX_TRANSFER_STATUS_ABORT;
                    return (status);
                }

                /* Check the transfer request completion code. We may have had a BUS reset or
                 * a device disconnection.  */
                if (transfer_request -> ux_slave_transfer_request_completion_code != (ULONG)UX_SUCCESS)
                {
                    return (UINT)(transfer_request -> ux_slave_transfer_request_completion_code);
                }

                /* Check the transfer request status. The transfer is completed with error. This may happen when
                 * requested length is than actual reception bytes(length) from the USB host which is nothing
                 * but user buffer overflowed */
                if (transfer_request -> ux_slave_transfer_request_status == (ULONG)UX_TRANSFER_ERROR)
                {
                    return (UINT)(transfer_request -> ux_slave_transfer_request_status);
                }
            }
        }
        /* Use the new DMA logic */
        else
        {

            dcd_synergy->ux_dcd_synergy_dma_packets =
                    (UINT)((transfer_request -> ux_slave_transfer_request_requested_length)/
                            ((endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) * 1024));

            /* Adjust number of packets.
             * i.e. MaxPacketSize (64 bytes in FS and 512 bytes in HS) to MaxPacketSize*1024 (64K in FS and 512K in HS) number_of_dma_packets = 1
             * from 64K+1 in FS (512K+1 in HS) to 128K in FS (1024K i.e. 1MB + 1 in HS) number_of_dma_packets = 2 and so on...
             */
            dcd_synergy->ux_dcd_synergy_dma_packets = dcd_synergy->ux_dcd_synergy_dma_packets + 1;

            for (number_of_dma_packets = 0U; number_of_dma_packets < dcd_synergy->ux_dcd_synergy_dma_packets;
                    number_of_dma_packets++)
            {
                if (transfer_request ->ux_slave_transfer_request_in_transfer_length <
                        ((endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) * 1024))
                {
                    number_of_bytes_to_transfer =
                            (UINT)(transfer_request ->ux_slave_transfer_request_in_transfer_length);

                   /* Make sure we call DMA only with multiple of endpoint size */
                    remaining_bytes =
                       number_of_bytes_to_transfer % ((UINT)(endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize));

                    number_of_bytes_to_transfer = number_of_bytes_to_transfer - remaining_bytes;
                }
                else
                {
                    number_of_bytes_to_transfer =
                            ((UINT)((endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) * 1024));
                }

                /* When the data size is just one packet (64 bytes in FS and 512 bytes in HS) more than 1 DMA configuration i.e.
                 * 64K to next 64 byte in FS (512K to next 512 bytes), in 2nd iteration onwards in for loop - data would be
                 * transferred by CPU and number_of_bytes_to_transfer would be 0 */
                dcd_synergy->ux_dcd_synergy_number_of_dma_ep_packets = (ULONG)number_of_bytes_to_transfer / endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
                dcd_synergy->ux_dcd_synergy_using_dma = 0xff;
                dcd_synergy->ux_dcd_synergy_dma_ep_index = ed -> ux_dcd_synergy_ed_index;
                /* Enable the BRDY interrupt. This is used to count the number of packets transferred */
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
                /* Entering critical area. Disable interrupts.  */
                TX_DISABLE
#endif
                /* Set transaction counter to number of transfers to receive. */
                ux_dcd_synergy_register_set(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL)* 4UL)), (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRCLR);
                ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_PIPESEL, (USHORT)(ed -> ux_dcd_synergy_ed_index));
                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPECFG, (USHORT)UX_SYNERGY_DCD_PIPECFG_BFRE);

                ux_dcd_synergy_register_write(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRN + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)), (USHORT)(dcd_synergy->ux_dcd_synergy_number_of_dma_ep_packets));
                ux_dcd_synergy_register_set(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)), (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRENB);
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
               /* Restore interrupts.  */
                TX_RESTORE
#endif

                if (number_of_bytes_to_transfer != 0U)
                {
                    /* This is the new DMA read function...*/
                    status = ux_dcd_synergy_fifo_read_dma (dcd_synergy, ed, number_of_bytes_to_transfer);
                    if (ed -> ux_dcd_synergy_ed_index != 0UL)
                    {
                        /* Clear and disable transaction counter.  */
                        ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_PIPESEL, (USHORT)(ed -> ux_dcd_synergy_ed_index));
                        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPECFG, (USHORT)UX_SYNERGY_DCD_PIPECFG_BFRE);
                        ux_dcd_synergy_register_set(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)), (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRCLR);
                        ux_dcd_synergy_register_clear(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)), (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRENB);
                    }

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif

                    /* Set the BUF to NAK as it should not send ACK for any more received bytes */
                    pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                                                               UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));

                    while (pipectr_reg & UX_SYNERGY_DCD_DCPCTR_INBUFM )
                    {
                        pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,
                                                                   UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));
                    }

                    /* Set PID to NAK for non Control End-points.  */
                    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                            ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_PIPECTR_PID_MASK);

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

                    if (status != (UINT)UX_SUCCESS)
                    {
                        return status;
                    }
                    ed -> ux_dcd_synergy_ed_payload_length -=  number_of_bytes_to_transfer;

                    /* Adjust the data pointer.  */
                    transfer_request -> ux_slave_transfer_request_current_data_pointer += number_of_bytes_to_transfer;

                    /* Adjust the transfer length remaining.  */
                    transfer_request -> ux_slave_transfer_request_in_transfer_length -= number_of_bytes_to_transfer;

                    /* Update the length of the data transmitted.  */
                    transfer_request -> ux_slave_transfer_request_actual_length += number_of_bytes_to_transfer;
                }
            }

            if (remaining_bytes != 0U)
            {
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif

                if (ed -> ux_dcd_synergy_ed_index != 0UL)
                {
                    /* Clear and disable transaction counter.  */
                    ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_PIPESEL, (USHORT)(ed -> ux_dcd_synergy_ed_index));
                    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPECFG, (USHORT)UX_SYNERGY_DCD_PIPECFG_BFRE);
                    ux_dcd_synergy_register_set(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)), (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRCLR);
                    ux_dcd_synergy_register_clear(dcd_synergy, (ULONG)(UX_SYNERGY_DCD_PIPE1TRE + (ULONG)((ed -> ux_dcd_synergy_ed_index -1UL) * 4UL)), (USHORT)UX_SYNERGY_DCD_PIPE1TRE_TRENB);
                }
                /* We have a request for a OUT transaction from the host.  */
                /* Set the current endpoint fifo.  */
                ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, 0);

                /* Clear the FIFO buffer memory. */
                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D1FIFOCTR , UX_SYNERGY_DCD_FIFOCTR_BCLR);
                /* Enable the BRDY interrupt.  */
                ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);

                /* Set PID to BUF. Isolate Control endpoint and others.  */
                if (ed -> ux_dcd_synergy_ed_index == 0UL)
                {
                    /* Set PID to BUF for Control Endpoint.  */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR, UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                }
                else
                {
                    /* Set PID to BUF for non Control Endpoints.  */
                    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                                ((ed -> ux_dcd_synergy_ed_index - 1) * 2),
                                                UX_SYNERGY_DCD_PIPECTR_PIDBUF);
                }

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

                /* If the endpoint is a Control endpoint, all this is happening under Interrupt and there is no
                 * thread to suspend.  */
                if (ed -> ux_dcd_synergy_ed_index != 0UL)
                {
                    /* We should wait for the semaphore to wake us up.  */
#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
                    status =  _ux_utility_semaphore_get(&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore,
                                                    UX_WAIT_FOREVER);
#else
                    status =  _ux_utility_semaphore_get(&transfer_request -> ux_slave_transfer_request_semaphore,
                                                    UX_WAIT_FOREVER);
#endif
                    /* Check the completion code. */
                    if (status != (UINT)UX_SUCCESS)
                    {
                        return (status);
                    }

                    /* Check the transfer request completion code. We may have had a BUS reset or
                     * a device disconnection. */
                    if (transfer_request -> ux_slave_transfer_request_completion_code != (ULONG)UX_SUCCESS)
                    {
                        return (UINT)(transfer_request -> ux_slave_transfer_request_completion_code);
                    }

                    /* Check the transfer request status. The transfer is completed with error.
                     * This may happen when requested length is than actual reception bytes(length)
                     * from the USB host which is nothing but user buffer overflowed */
                    if (transfer_request -> ux_slave_transfer_request_status == (ULONG)UX_TRANSFER_ERROR)
                    {
                        return (UINT)(transfer_request -> ux_slave_transfer_request_status);
                    }
                }
            }
            /* Update completion code and status */
            else
            {
                /* Set the completion code to no error.  */
                transfer_request -> ux_slave_transfer_request_completion_code = (ULONG)UX_SUCCESS;
                /* The transfer is completed.  */
                transfer_request -> ux_slave_transfer_request_status = (ULONG)UX_TRANSFER_STATUS_COMPLETED;
            }
        }
    }

    /* Return to caller with success.  */
    return (UINT)UX_SUCCESS;
}

 /*******************************************************************************************************************//**
  * @} (end addtogroup sf_el_ux)
  **********************************************************************************************************************/
