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
#include "ux_dcd_synergy.h"
#include "sf_el_ux_dcd_common.h"

#define MAX_BUFFER_READY_STATUS_RETRIES 2000UL

VOID ux_dcd_synergy_write_dma_configure (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            ULONG fifo_sel,
                                            ULONG endpoint_size);

static VOID ux_dcd_synergy_write_dma_set_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            ULONG fifo_sel,ULONG endpoint_size);
#if defined(R_USBHS_BASE)
static VOID ux_dcd_synergy_write_dma_set_32bit (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            ULONG fifo_sel,ULONG endpoint_size);
#endif

VOID ux_dcd_synergy_fifo_dma_start_write (UX_DCD_SYNERGY * dcd_synergy,
                                                    UCHAR * p_payload_buffer,
                                                    VOID  * p_fifo_add,
                                                    VOID * p_fifo_ctrl,
                                                    VOID * p_fifo_sel);
/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_dcd_synergy_fifod_write                          PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function writes a buffer to FIFOD0 or FIFOD1                   */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    dcd_synergy                 Pointer to synergy controller           */ 
/*    ed                                    Register to the ed            */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                                              */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    None                                                                */ 
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
 * @brief  This function writes a buffer to FIFOD0 or FIFOD1.
 *
 * @param[in,out]  dcd_synergy             : Pointer to a DCD control block
 * @param[in,out]  ed                      : Pointer to a physical Endpoint(ED) control block
 *
 * @retval UX_ERROR                         FIFO is not accessible.
 * @retval UX_SYNERGY_DCD_FIFO_WRITE_END    Write ends of FIFO.
 * @retval UX_SYNERGY_DCD_FIFO_WRITING      Continue multiple write to FIFO.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_fifod_write(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed)
{
    ULONG    fifo_access_status;
    ULONG    max_packet_size;
    ULONG    data_buffer_size;
    UINT     status;
    VOID   * fifo_addr;
    ULONG    fifo_ctrl;
    ULONG    fifo_sel;
    ULONG    synergy_register;
    UX_DCD_SYNERGY_PAYLOAD_TRANSFER payload;

    /* Get the Fifo access status.  */
    fifo_access_status =  ux_dcd_synergy_fifo_port_change(dcd_synergy, ed, 0);

    /* Check Status.  */
    if (fifo_access_status == (ULONG)UX_ERROR)
    {
        /* We have an error. Abort.  */
        return (UINT)UX_ERROR;
    }

    /* Get the data buffer size.  */
    data_buffer_size = ux_dcd_synergy_data_buffer_size(dcd_synergy, ed);

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_dcd_synergy_ed_endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;

    /* Check if this transfer takes more than one packet.  */
    if (ed -> ux_dcd_synergy_ed_payload_length <= max_packet_size)
    {
        /* Set the payload to the TD payload length.  */
        payload.payload_length =  ed -> ux_dcd_synergy_ed_payload_length;

        /* Set Status to write ends.  */
        status = UX_SYNERGY_DCD_FIFO_WRITE_END;
    }
    else
    {
        /* We are doing a multi write.  */
        status = (UINT)UX_SYNERGY_DCD_FIFO_WRITING;

        /* Payload length is the buffer size.  */
        payload.payload_length = data_buffer_size;
    }      

    /* We need to select the FIFO registers.  */
    switch (ed -> ux_dcd_synergy_ed_fifo_index)
    {
    /* fall through for C0 and C1 pipes as both are handled similarly.*/
    case  UX_SYNERGY_DCD_FIFO_C0      :
    case  UX_SYNERGY_DCD_FIFO_C1      :
        /* Set fifo_sel and fifo_addr fields to FIFO_C */
        fifo_sel  =  UX_SYNERGY_DCD_CFIFOSEL;
        fifo_addr =  (VOID *)(dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_CFIFO);
        fifo_ctrl = UX_SYNERGY_DCD_CFIFOCTR;
        break;

    case  UX_SYNERGY_DCD_FIFO_D0     :
        /* Set fifo_sel and fifo_addr fields to FIFO_D0 */
        fifo_sel  =  UX_SYNERGY_DCD_D0FIFOSEL;
        fifo_addr =  (VOID *)(dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_D0FIFO);
        fifo_ctrl =  UX_SYNERGY_DCD_D0FIFOCTR;
        break;

    case  UX_SYNERGY_DCD_FIFO_D1     :
        /* Set fifo_sel and fifo_addr fields to FIFO_D1 */
        fifo_sel  =  UX_SYNERGY_DCD_D1FIFOSEL;
        fifo_addr = (VOID *)(dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_D1FIFO);
        fifo_ctrl =  UX_SYNERGY_DCD_D1FIFOCTR;
        break;

    default :
        /* Set fifo_sel and fifo_addr fields to FIFO_C */
        fifo_sel  =  UX_SYNERGY_DCD_CFIFOSEL;
        fifo_addr =  (VOID *)(dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_CFIFO);
        fifo_ctrl = UX_SYNERGY_DCD_CFIFOCTR;
        break;
    }

    /* Get the payload buffer address.  */
    payload.payload_buffer =  ed -> ux_dcd_synergy_ed_payload_address;

    /* Memorize packet length.  */
    ed -> ux_dcd_synergy_ed_packet_length = payload.payload_length;

    /* Transfer data by software copy. */
    ux_dcd_synergy_fifo_write_software_copy (dcd_synergy, &payload, fifo_addr, fifo_sel);

    /* Check status. If we have a short packet or zero packet, we need to set
     * the BVAL flag in the FIFO controller.  */
    if (ed -> ux_dcd_synergy_ed_payload_length < max_packet_size)
    {
        /* Read the current FIFO control register.  */
        synergy_register = ux_dcd_synergy_register_read(dcd_synergy, fifo_ctrl);

        /* Check if the BVAL bit is already set.  */
        if ((synergy_register & UX_SYNERGY_DCD_FIFOCTR_BVAL) == 0)
        {
            /* No so set it.  This will enable the Buffer Memory Valid flag.
             * This bit is set to 1 when data has been written to the FIFO and
             * this is a short packet or zero packet but not the
             * end of the transmission.  */
            ux_dcd_synergy_register_set(dcd_synergy, fifo_ctrl, UX_SYNERGY_DCD_FIFOCTR_BVAL);
        }
    }

    /* Return status about buffer transfer.  */
    return (status);
}

/*******************************************************************************************************************//**
 * @brief  This function writes a buffer to FIFOD0 or FIFOD1 using DMA.
 *
 * @param[in,out]  dcd_synergy             : Pointer to a DCD control block
 * @param[in,out]  ed                      : Pointer to a physical Endpoint(ED) control block
 * @param[in,out]  dma_bytes_to_transfer   : No of bytes to be transferred using DMA
 *
 * @retval UX_ERROR                          FIFO is not accessible.
 * @retval UX_SYNERGY_DCD_FIFO_WRITE_END     Write ends of FIFO.
 * @retval UX_SYNERGY_DCD_FIFO_WRITING       Continue multiple write to FIFO.
 * @retval UX_SYNERGY_DCD_FIFO_WRITE_ERROR   Return error if timeout occurs or endpoint reset occurs.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_fifod_write_dma (UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, UINT dma_bytes_to_transfer)
{
    ULONG    fifo_access_status;
    VOID   * fifo_addr;
    ULONG    fifo_ctrl;
    ULONG    fifo_sel;
    UX_DCD_SYNERGY_PAYLOAD_TRANSFER payload;
    ULONG pipectr_reg;
    USHORT pipe_number;
    ULONG endpoint_buf_size;
    ULONG buf_ready_wait_count;
    UINT sem_get_status;
    UX_SLAVE_ENDPOINT   *endpoint;

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Macro for saving and restoring the interrupts to support concurrent access*/
    TX_INTERRUPT_SAVE_AREA
#endif

    if(ed == UX_NULL)
    {
        return (UINT)UX_ERROR;
    }

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif
    endpoint = ed->ux_dcd_synergy_ed_endpoint;
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

    /* Get the Fifo access status.  */
    fifo_access_status =  ux_dcd_synergy_fifo_port_change(dcd_synergy, ed, 0);

    /* Check Status.  */
    if (fifo_access_status == (ULONG)UX_ERROR)
    {
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif
        /* We have an error. Abort.  */
        return (UINT)UX_ERROR;
    }

    payload.payload_length = dma_bytes_to_transfer;

    /* We need to select the FIFO registers.  */
    if (ed -> ux_dcd_synergy_ed_fifo_index == UX_SYNERGY_DCD_FIFO_D0)
    {
        fifo_addr =  (VOID *) (dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_D0FIFO);
        fifo_ctrl =  UX_SYNERGY_DCD_D0FIFOCTR;
        fifo_sel  =  UX_SYNERGY_DCD_D0FIFOSEL;
    }
    else
    {
        fifo_addr =  (VOID *) (dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_D1FIFO);
        fifo_ctrl =  UX_SYNERGY_DCD_D1FIFOCTR;
        fifo_sel  =  UX_SYNERGY_DCD_D1FIFOSEL;
    }

    /* Get the payload buffer address.  */
    payload.payload_buffer =  ed -> ux_dcd_synergy_ed_payload_address;

    /* Find the endpoint buffer size, so accordingly the DMA is configured... */
    endpoint_buf_size = ed->ux_dcd_synergy_ed_endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;

    /** Setup DMA transfer. */
    ux_dcd_synergy_write_dma_configure (dcd_synergy, &payload, fifo_sel, endpoint_buf_size);

    /** Start DMA transfer by software control. */
    ux_dcd_synergy_fifo_dma_start_write (dcd_synergy, (UCHAR *)(payload.payload_buffer), fifo_addr,
            (VOID *) fifo_ctrl, (VOID *) fifo_sel);
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

    /** Wait till DMA transfer is done. */
    sem_get_status = _ux_utility_semaphore_get(&dcd_synergy->dma_tx_completion_semaphore, endpoint->ux_slave_endpoint_transfer_request.ux_slave_transfer_request_timeout);

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif
    /* Clear DREQE bit */
    ux_dcd_synergy_register_clear (dcd_synergy, UX_SYNERGY_DCD_D0FIFOSEL, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_DREQE);

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

    /** Return error, if semaphore timeouts or endpoint reset occurs. */
    if ( (sem_get_status != (UINT)UX_SUCCESS ) || (UX_TRANSFER_BUS_RESET == (UINT)endpoint->ux_slave_endpoint_transfer_request.ux_slave_transfer_request_completion_code) )
    {
        endpoint->ux_slave_endpoint_transfer_request.ux_slave_transfer_request_completion_code = (ULONG)UX_SUCCESS;
        return (UX_SYNERGY_DCD_FIFO_WRITE_ERROR);
    }


    pipe_number = (USHORT) ux_dcd_synergy_register_read (dcd_synergy, fifo_sel);

    /* Pipe number is only last 4 bits */
    pipe_number = pipe_number & 0x000f;

    /** Wait for certain time - if the buffer is not ready return error */
    buf_ready_wait_count = 0UL;
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif
    do
    {
        pipectr_reg = ux_dcd_synergy_register_read(dcd_synergy,UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL));
        buf_ready_wait_count++;
        /* If bufer is not ready after MAX_BUFFER_READY_STATUS_RETRIES
         * after DMA is done - return error - indicating something wrong */
        if (buf_ready_wait_count > MAX_BUFFER_READY_STATUS_RETRIES)
        {
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif
            return (UX_SYNERGY_DCD_FIFO_WRITE_ERROR);
        }
    }while (pipectr_reg & UX_SYNERGY_DCD_DCPCTR_INBUFM);

    /** Clear the DELSR.n.IR flag by starting the dummy DMA transfer. */
    dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_api->Stop_ActivationRequest(dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl);
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
            ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_PIPECTR_PID_MASK);


#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif
    return (UX_SYNERGY_DCD_FIFO_WRITE_END);
}
/******************************************************************************************************************//**
 * @brief  USBX DCD DMA write setup function. Call a subroutine for selected USB controller hardware.
 *
 * @param[in]      dcd_synergy  Pointer to the DCD control block
 * @param[in,out]  p_payload    Pointer to a payload transfer structure
 * @param[in]      fifo_sel     FIFO select register
 * @param[in]      endpoint_size Endpoint size
 **********************************************************************************************************************/
VOID ux_dcd_synergy_write_dma_configure (UX_DCD_SYNERGY *dcd_synergy,
                                                   UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                   ULONG fifo_sel,
                                                   ULONG endpoint_size)
{
#if defined(R_USBHS_BASE)
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        /* Set DMA transfer for 32-bit USB hardwares. */
        ux_dcd_synergy_write_dma_set_32bit (dcd_synergy, p_payload, fifo_sel, endpoint_size);
    }
    else
#endif
    {
        /* Set DMA transfer for 16-bit USB hardwares. */
        ux_dcd_synergy_write_dma_set_16bit (dcd_synergy, p_payload, fifo_sel, endpoint_size);
    }
}

/******************************************************************************************************************//**
 * @brief  USBX DCD DMA write setup function for USB hardwares with 16-bit FIFO
 *
 * @param[in]      dcd_synergy   Pointer to the DCD control block
 * @param[in,out]  p_payload     Pointer to a payload transfer structure
 * @param[in]      fifo_sel      FIFO select register
 * @param[in]     endpoint_size Endpoint size
**********************************************************************************************************************/
static VOID ux_dcd_synergy_write_dma_set_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                                   UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                   ULONG fifo_sel,
                                                   ULONG endpoint_size)
{
    if(0 == ((UINT)p_payload->payload_buffer % 2U))
    {
        /* Transfer data in 2bytes unit if buffer is aligned to 16-bit address. */
        p_payload -> transfer_width = 2U;
        p_payload -> transfer_times = (UINT)(endpoint_size / 2UL);

        /* Number of such width * times to be sent */
        p_payload -> transfer_blocks = (UINT)((p_payload->payload_length) / (endpoint_size));


        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->size   = TRANSFER_SIZE_2_BYTE;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->length = (uint16_t)p_payload -> transfer_times;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->num_blocks = (uint16_t) p_payload -> transfer_blocks;
        /* Set FIFO access width to 16 bits. */
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_16);
    }
    else
    {
        /* Transfer data in 1byte unit if buffer is aligned to 8-bit address. */
        p_payload -> transfer_width = 1U;
        p_payload -> transfer_times = (UINT)endpoint_size;
        p_payload -> transfer_blocks = (UINT)((p_payload->payload_length) / (endpoint_size));

        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->size   = TRANSFER_SIZE_1_BYTE;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->length = (uint16_t) p_payload -> transfer_times;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->num_blocks = (uint16_t) p_payload -> transfer_blocks;
        /* Set FIFO access width to 8 bits. */
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_8);
    }
}

#if defined(R_USBHS_BASE)
/******************************************************************************************************************//**
 * @brief  USBX DCD DMA write setup function for USB hardwares with 32-bit FIFO
 *
 * @param[in]      dcd_synergy  Pointer to the DCD control block
 * @param[in,out]  p_payload    Pointer to a payload transfer structure
 * @param[in]      fifo_sel     FIFO select register
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_write_dma_set_32bit (UX_DCD_SYNERGY * dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    ULONG fifo_sel,
                                                    ULONG endpoint_size)
{
    if(0 == ((UINT)p_payload->payload_buffer % 4U))
    {
        /* Transfer data in 4bytes unit if buffer is aligned to 32-bit address. */
        p_payload -> transfer_width = 4U;
        p_payload -> transfer_times = (UINT)(endpoint_size / 4UL);

        /* Number of such width * times to be sent */
        p_payload -> transfer_blocks = (UINT)((p_payload->payload_length) / (endpoint_size));
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->size   = TRANSFER_SIZE_4_BYTE;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->length = (uint16_t)p_payload -> transfer_times;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->num_blocks = (uint16_t)p_payload -> transfer_blocks;
        /* Set FIFO access width to 32 bits. */
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_32);
    }
    else
    {
        ux_dcd_synergy_write_dma_set_16bit (dcd_synergy, p_payload, fifo_sel, endpoint_size);
    }
}
#endif

/******************************************************************************************************************//**
 * @brief  USBX DCD DMA FIFO write - DMA start function
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload_buffer Pointer to a payload buffer
 * @param[in]      p_fifo_add       FIFO register address
 * @param[in]      p_fifo_ctrl      FIFO port control register address
 * @param[in]      p_fifo_sel       FIFO port selection register address
 **********************************************************************************************************************/
VOID ux_dcd_synergy_fifo_dma_start_write (UX_DCD_SYNERGY * dcd_synergy,
                                                    UCHAR * p_payload_buffer,
                                                    VOID  * p_fifo_add,
                                                    VOID * p_fifo_ctrl,
                                                    VOID * p_fifo_sel)
{
    volatile USHORT   pipe_used_for_dma;
    uint16_t          transfer_length;
    uint16_t          num_blocks;

#if defined(R_USBHS_BASE)
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        if (TRANSFER_SIZE_4_BYTE == dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->size)
        {
            /* 32-bit FIFO access does not need address offset. */
        }
        else if (TRANSFER_SIZE_2_BYTE == dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->size)
        {
            /* USBHS controller needs address offset (+2) for 16-bit access to the FIFO. */
            p_fifo_add =  (VOID *)((ULONG)p_fifo_add + 2UL);
        }
        else
        {
            /* USBHS controller needs address offset (+3) for 8-bit access to the FIFO. */
            p_fifo_add =  (VOID *)((ULONG)p_fifo_add + 3UL);
        }
    }
#endif

    /* Follow the correct DMA HW sequence. This is the HW bug - need to follow the
     * below sequence to kick the DMA - as suggested by HW team.
     * A.i. Check DnFIFOCTR.FRDY and make sure the bit is read as '0'.
     * As DnFIFOCTR register is to be read for HW sake, it is not used anywhere
     * So just read it to read_pipe_number - which is overwritten in next steps
     * */
    dcd_synergy->read_pipe_number =  ux_dcd_synergy_register_read(dcd_synergy, (ULONG) p_fifo_ctrl);

    /* A.ii. Set 4'b0000 to DnFIFOSEL.CURPIPE
     *First notedown the pipe used */
    pipe_used_for_dma = (USHORT) (ux_dcd_synergy_register_read (dcd_synergy, (ULONG) p_fifo_sel));

    /* Pipe number is only last 4 bits */
    pipe_used_for_dma = pipe_used_for_dma & UX_SYNERGY_DCD_PIPESEL_NO_PIPE;

    ux_dcd_synergy_register_clear (dcd_synergy, (ULONG) p_fifo_sel, (USHORT) UX_SYNERGY_DCD_PIPESEL_NO_PIPE_USHORT);

    transfer_length = dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->length;
    num_blocks = dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->num_blocks;
    /* Setup DMA block transfer. */
    dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_api->blockReset(
    		dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl,
			p_payload_buffer, p_fifo_add, transfer_length,
			dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->size,
			num_blocks);

    /* A.iii. Set 1 to DnFIFOSEL.DREQE, and set DnFIFOSEL.MBW if required.
     *MBW is already set now... */
    ux_dcd_synergy_register_set(dcd_synergy, (ULONG) p_fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_DREQE);

    /* A.iv. Set a PIPE number to DnFIFOSEL.CURPIPE
     * Currently pipe 2 is used for IN (for write) */
    ux_dcd_synergy_register_set(dcd_synergy, (ULONG) p_fifo_sel, pipe_used_for_dma);

    /* B.i. Set "BUF" to PIPEnCTR.PID
     * This should trigger the DMA - finally*/
    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR + ((pipe_used_for_dma - 1UL) * 2UL), (USHORT)(UX_SYNERGY_DCD_PIPECTR_PIDBUF));
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
