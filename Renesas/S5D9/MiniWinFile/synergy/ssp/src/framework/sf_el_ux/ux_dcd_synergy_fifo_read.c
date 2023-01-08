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

static VOID ux_dcd_synergy_fifo_read_software_copy (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            VOID * p_fifo,
                                            ULONG  fifo_sel);

static VOID ux_dcd_synergy_fifo_read_software_copy_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            VOID * p_fifo,
                                            ULONG  fifo_sel);

#if defined(R_USBHS_BASE)
static VOID ux_dcd_synergy_fifo_read_software_copy_32bit (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            VOID * p_fifo,
                                            ULONG  fifo_sel);
#endif

static VOID ux_dcd_synergy_fifo_read_last_bytes (UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            VOID * p_fifo);

static VOID ux_dcd_synergy_read_dma_configure (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            ULONG fifo_sel,
                                            ULONG ep_buff_size);

static VOID ux_dcd_synergy_read_dma_set_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            ULONG fifo_sel,
                                            ULONG ep_buff_size);
#if defined(R_USBHS_BASE)
static VOID ux_dcd_synergy_read_dma_set_32bit (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            ULONG fifo_sel,
                                            ULONG ep_buff_size);
#endif

static VOID ux_dcd_synergy_fifo_dma_start_read (UX_DCD_SYNERGY * dcd_synergy,
                                            UCHAR * p_payload_buffer,
                                            VOID  * p_fifo,
                                            VOID * p_fifo_ctrl,
                                            VOID * p_fifo_sel);
typedef union local_buffer_u {
    ULONG   input;
    UCHAR   output[4];
} local_buffer_t;

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_dcd_synergy_fifo_read                          PORTABLE C        */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function reads a buffer from FIFO C D0 or D1                   */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    dcd_synergy                 Pointer to synergy controller           */ 
/*    ed                                 Register to the ed               */ 
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

/*******************************************************************************************************************//**
 * @brief  This function reads from the hardware FIFO C and stores in the destination buffer.
 *
 * @param[in,out]  dcd_synergy            : Pointer to a DCD control block
 * @param[in,out]  ed                     : Pointer to a physical Endpoint(ED) control block
 *
 * @retval UX_ERROR                        FIFO is not accessible.
 * @retval UX_SYNERGY_DCD_FIFO_READ_OVER   FIFO read overflow.
 * @retval UX_SYNERGY_DCD_FIFO_READ_SHORT  Short packet is received.
 * @retval UX_SYNERGY_DCD_FIFO_READING     Continue reading FIFO.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_fifoc_read(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed)
{
    ULONG   fifo_access_status;
    ULONG   max_packet_size;
    UINT    status;
    ULONG   fifo_sel;
    VOID  * fifo_addr;
    ULONG   fifo_ctrl;
    UX_DCD_SYNERGY_PAYLOAD_TRANSFER payload;

    /* As this is explicit function for reading the control pipe - directly assign the variables of control pipe */
    fifo_sel  =  UX_SYNERGY_DCD_CFIFOSEL;
    fifo_addr =  (VOID *)(dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_CFIFO);
    fifo_ctrl = UX_SYNERGY_DCD_CFIFOCTR;

    /* Get the Fifo access status for the endpoint.  */
    fifo_access_status =  ux_dcd_synergy_fifo_port_change(dcd_synergy, ed, 0);

    /* Check Status.  */
    if (fifo_access_status == (ULONG)UX_ERROR)
    {
        /* We have an error. Abort.  */
        return (UINT)UX_ERROR;
    }

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_dcd_synergy_ed_endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;

    /* Isolate the payload length.  */
    payload.payload_length = fifo_access_status & UX_SYNERGY_DCD_FIFOCTR_DTLN;

    /* Save the payload length in the ED. This is needed to check for end of transfer.  */
    ed -> ux_dcd_synergy_ed_actual_length =  payload.payload_length;

    /* Set NAK.  */
    ux_dcd_synergy_endpoint_nak_set(dcd_synergy, ed);

    /* Check for overwrite.  */
    if (ed -> ux_dcd_synergy_ed_payload_length < payload.payload_length)
    {
        /* Set Status to read overflow.  */
        status = UX_SYNERGY_DCD_FIFO_READ_OVER;

        /* Set the payload length to the size wanted by the caller.  */
        payload.payload_length = ed -> ux_dcd_synergy_ed_payload_length;
    }
    else
    {
        /* Check for short packet.  */
        if ((payload.payload_length == 0UL) || ((UINT)(payload.payload_length % max_packet_size) != 0U))
        {
            /* We have a short packet.  */
            status = UX_SYNERGY_DCD_FIFO_READ_SHORT;
        }
        else
        {
            /* Continue reading.  */
            status = UX_SYNERGY_DCD_FIFO_READING;
        }
    }

    /* Check if received packet is 0 length packet.  */
    if (0UL != payload.payload_length)
    {
        /* Get the payload buffer address.  */
        payload.payload_buffer =  ed->ux_dcd_synergy_ed_payload_address;

        /* Transfer data by software copy. */
        ux_dcd_synergy_fifo_read_software_copy (dcd_synergy, &payload, fifo_addr, fifo_sel);
    }

    /* Clear the FIFO buffer memory. */
    ux_dcd_synergy_register_write(dcd_synergy, fifo_ctrl, UX_SYNERGY_DCD_FIFOCTR_BCLR);

    /* Return status about buffer transfer.  */
    return (status);
}

/*******************************************************************************************************************//**
 * @brief  This function reads from the hardware FIFO D0 or D1 and stores in the destination buffer.
 *
 * @param[in,out]  dcd_synergy            : Pointer to a DCD control block
 * @param[in,out]  ed                     : Pointer to a physical Endpoint(ED) control block
 *
 * @retval UX_ERROR                        FIFO is not accessible.
 * @retval UX_SYNERGY_DCD_FIFO_READ_OVER   FIFO read overflow.
 * @retval UX_SYNERGY_DCD_FIFO_READ_SHORT  Short packet is received.
 * @retval UX_SYNERGY_DCD_FIFO_READING     Continue reading FIFO.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_fifo_read(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed)
{
    ULONG   fifo_access_status;
    ULONG   max_packet_size;
    UINT    status;
    ULONG   fifo_sel;
    VOID  * fifo_addr;
    ULONG   fifo_ctrl;
    UX_DCD_SYNERGY_PAYLOAD_TRANSFER payload;

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

    /* Get the Fifo access status for the endpoint.  */
    fifo_access_status =  ux_dcd_synergy_fifo_port_change(dcd_synergy, ed, 0);

    /* Check Status.  */
    if (fifo_access_status == (ULONG)UX_ERROR)
    {
        /* We have an error. Abort.  */
        return (UINT)UX_ERROR;
    }

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_dcd_synergy_ed_endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;

    /* Isolate the payload length.  */
    payload.payload_length = fifo_access_status & UX_SYNERGY_DCD_FIFOCTR_DTLN;

    /* Save the payload length in the ED. This is needed to check for end of transfer.  */
    ed -> ux_dcd_synergy_ed_actual_length =  payload.payload_length;

    /* Set NAK.  */
    ux_dcd_synergy_endpoint_nak_set(dcd_synergy, ed);

    /* Check for overwrite.  */
    if (ed -> ux_dcd_synergy_ed_payload_length < payload.payload_length)
    {
        /* Set Status to read overflow.  */
        status = UX_SYNERGY_DCD_FIFO_READ_OVER;

        /* Set the payload length to the size wanted by the caller.  */
        payload.payload_length = ed -> ux_dcd_synergy_ed_payload_length;
    }
    else
    {
        /* Check for short packet.  */
        if ((payload.payload_length == 0UL) || ((UINT)(payload.payload_length % max_packet_size) != 0U))
        {
            /* We have a short packet.  */
            status = UX_SYNERGY_DCD_FIFO_READ_SHORT;
        }
        else
        {
            /* Continue reading.  */
            status = UX_SYNERGY_DCD_FIFO_READING;
        }
    }

    /* Check if received packet is 0 length packet.  */
    if (0UL != payload.payload_length)
    {
        /* Get the payload buffer address.  */
        payload.payload_buffer =  ed->ux_dcd_synergy_ed_payload_address;

        /* Transfer data by software copy. */
        ux_dcd_synergy_fifo_read_software_copy (dcd_synergy, &payload, fifo_addr, fifo_sel);
    }

    /* Clear the FIFO buffer memory. */
    ux_dcd_synergy_register_write(dcd_synergy, fifo_ctrl, UX_SYNERGY_DCD_FIFOCTR_BCLR);

    /* Return status about buffer transfer.  */
    return (status);
}
/*******************************************************************************************************************//**
 * @brief  This function reads the data from HW D0/ D1 FIFO using DMA
 *
 * @param[in,out]  dcd_synergy            : Pointer to a DCD control block
 * @param[in,out]  ed                     : Pointer to a physical Endpoint(ED) control block
 * @param[in,out]  dma_bytes_to_transfer  : No of bytes to be transferred using DMA
 *
 * @retval UX_ERROR                        FIFO is not accessible.
 * @retval UX_SYNERGY_DCD_FIFO_READ_OVER   FIFO read overflow.
 * @retval UX_SYNERGY_DCD_FIFO_READ_SHORT  Short packet is received.
 * @retval UX_SYNERGY_DCD_FIFO_READING     Continue reading FIFO.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_fifo_read_dma (UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, UINT dma_bytes_to_transfer)
{
    ULONG   fifo_sel;
    VOID  * fifo_addr;
    ULONG   fifo_ctrl;
    UX_DCD_SYNERGY_PAYLOAD_TRANSFER payload;
    UINT sem_rx_get_status;
    ULONG endpoint_buffer_size;

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Macro for saving and restoring the interrupts to support concurrent access*/
    TX_INTERRUPT_SAVE_AREA
#endif

    /* Below 2 functions are taken from tranfser_request.c as it would be easy to use TX_DISABLE and TX_RESTORE */

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

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Restore interrupts.  */
    TX_RESTORE
#endif

    /* We need to select the FIFO registers.  */
    switch (ed -> ux_dcd_synergy_ed_fifo_index)
    {
        case  UX_SYNERGY_DCD_FIFO_CD      :
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

    /* Make a note of pipe number used for read. Initialize to 0.
     * This is used in callback for setting the NAK for read pipe */
    dcd_synergy->read_pipe_number = 0UL;

    /* Isolate the payload length.  */
    payload.payload_length = dma_bytes_to_transfer;

    /* Check if received packet is 0 length packet.  */
    if (0UL != payload.payload_length)
    {
        /* Get the payload buffer address.  */
        payload.payload_buffer =  ed->ux_dcd_synergy_ed_payload_address;

        /* Find the endpoint buffer size, so accordingly the DMA is configured... */
        endpoint_buffer_size = ed->ux_dcd_synergy_ed_endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
    /* Entering critical area. Disable interrupts.  */
    TX_DISABLE
#endif

        /* Setup DMA transfer. */
        ux_dcd_synergy_read_dma_configure (dcd_synergy, &payload, fifo_sel, endpoint_buffer_size);

        /* Enable the BRDY interrupt. This is used to count the number of packets transferred */
        ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);

        /* Start DMA transfer by software control. */
        ux_dcd_synergy_fifo_dma_start_read (dcd_synergy, (UCHAR *)(payload.payload_buffer),
        		fifo_addr, (VOID *) fifo_ctrl, (VOID *) fifo_sel);

#if defined(UX_DEVICE_COMPOSITE_ENABLE)
        /* Restore interrupts.  */
        TX_RESTORE
#endif

        /* Wait till DMA transfer is done. */
        sem_rx_get_status = _ux_utility_semaphore_get(&dcd_synergy->dma_rx_completion_semaphore, UX_WAIT_FOREVER);
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
        /* Entering critical area. Disable interrupts.  */
        TX_DISABLE
#endif
        ux_dcd_synergy_register_clear (dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_DREQE);
#if defined(UX_DEVICE_COMPOSITE_ENABLE)
        /* Restore interrupts.  */
        TX_RESTORE
#endif
        if (sem_rx_get_status != (UINT)UX_SUCCESS)
        {
        	return (UINT)UX_ERROR;
        }
    }
    /* Clear the FIFO buffer memory. */
    ux_dcd_synergy_register_write(dcd_synergy, fifo_ctrl, UX_SYNERGY_DCD_FIFOCTR_BCLR);

    return (UX_SUCCESS);
}



/*******************************************************************************************************************//**
 * @brief  USBX DCD DMA read setup function. Call a subroutine for selected USB controller hardware.
 *
 * @param[in]      dcd_synergy  Pointer to the DCD control block
 * @param[in,out]  p_payload    Pointer to a payload transfer structure
 * @param[in]      fifo_sel     FIFO select register
 * @param[in]      ep_buff_size Buffer size
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_read_dma_configure (UX_DCD_SYNERGY *dcd_synergy,
                                                   UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                   ULONG fifo_sel,
                                                   ULONG ep_buff_size)
{
#if defined(R_USBHS_BASE)
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        /* Set DMA transfer for 32-bit USB hardwares. */
        ux_dcd_synergy_read_dma_set_32bit (dcd_synergy, p_payload, fifo_sel, ep_buff_size);
    }
    else
#endif
    {
        /* Set DMA transfer for 16-bit USB hardwares. */
        ux_dcd_synergy_read_dma_set_16bit (dcd_synergy, p_payload, fifo_sel, ep_buff_size);
    }
}

/*******************************************************************************************************************//**
 * @brief  USBX DCD DMA read setup function for USB hardwares with 16-bit FIFO
 *
 * @param[in]      dcd_synergy  Pointer to the DCD control block
 * @param[in,out]  p_payload    Pointer to a payload transfer structure
 * @param[in]      fifo_sel     FIFO select register
 * @param[in]      ep_buff_size Buffer size
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_read_dma_set_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                                   UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                   ULONG fifo_sel,
                                                   ULONG ep_buff_size)
{

    if(0 == ((UINT)p_payload->payload_buffer % 2U))
    {
        /* Transfer data in 2bytes unit if buffer is aligned to 16-bit address. */
        p_payload -> transfer_width = 2U;
        p_payload -> transfer_times = (UINT)(ep_buff_size / 2U);

        /* Number of such width * times to be sent */
        p_payload -> transfer_blocks = (UINT)((p_payload->payload_length) / ( ep_buff_size));

        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->size   = TRANSFER_SIZE_2_BYTE;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->length = (uint16_t)p_payload -> transfer_times;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->num_blocks = (uint16_t) p_payload -> transfer_blocks;

        /* Set FIFO access width to 16 bits. */
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_16);
    }
    else
    {
        /* Transfer data in 1byte unit if buffer is aligned to 8-bit address. */
        p_payload -> transfer_width = 1U;
        p_payload -> transfer_times = (UINT)ep_buff_size;

        /* Number of such width * times to be sent */
        p_payload -> transfer_blocks = (UINT)((p_payload->payload_length) / ( ep_buff_size));

        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->size   = TRANSFER_SIZE_1_BYTE;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->length = (uint16_t) p_payload -> transfer_times;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->num_blocks = (uint16_t) p_payload -> transfer_blocks;

        /* Set FIFO access width to 8 bits. */
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_8);
    }
}

#if defined(R_USBHS_BASE)
/******************************************************************************************************************//**
 * @brief  USBX DCD DMA read setup function for USB hardwares with 32-bit FIFO
 *
 * @param[in]      dcd_synergy  Pointer to the DCD control block
 * @param[in,out]  p_payload    Pointer to a payload transfer structure
 * @param[in]      fifo_sel     FIFO select register
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_read_dma_set_32bit (UX_DCD_SYNERGY * dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    ULONG fifo_sel,
                                                    ULONG ep_buff_size)
{
    if(0 == ((UINT)p_payload->payload_buffer % 4U))
    {
        /* Transfer data in 4bytes unit if buffer is aligned to 32-bit address. */
        p_payload -> transfer_width = 4U;
        p_payload -> transfer_times = (UINT)(ep_buff_size / 4U);
        /* Number of such width * times to be sent */
        p_payload -> transfer_blocks = (UINT)((p_payload->payload_length) / ( ep_buff_size));

        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->size   = TRANSFER_SIZE_4_BYTE;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->length = (uint16_t)p_payload -> transfer_times;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->num_blocks = (uint16_t)p_payload -> transfer_blocks;

        /* Set FIFO access width to 32 bits. */
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_32);
    }
    else
    {
        ux_dcd_synergy_read_dma_set_16bit (dcd_synergy, p_payload, fifo_sel, ep_buff_size);
    }
}
#endif

/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO read - DMA start function
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload_buffer Pointer to a payload buffer
 * @param[in,out]  p_fifo           FIFO register address
 * @param[in]      p_fifo_ctrl      FIFO port control register address
 * @param[in]      p_fifo_sel       FIFO port selection register address
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_fifo_dma_start_read (UX_DCD_SYNERGY * dcd_synergy,
                                            UCHAR * p_payload_buffer,
                                            VOID  * p_fifo,
                                            VOID * p_fifo_ctrl,
                                            VOID * p_fifo_sel)
{
    volatile USHORT   pipe_used_for_dma;
    uint16_t          transfer_length;
    uint16_t          num_blocks;
#if defined(R_USBHS_BASE)
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        if (TRANSFER_SIZE_4_BYTE == dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->size)
        {
            /* 32-bit FIFO access does not need address offset. */
        }
        else if (TRANSFER_SIZE_2_BYTE == dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->size)
        {
            /* USBHS controller needs address offset (+2) for 16-bit access to the FIFO. */
            p_fifo =  (VOID *)((ULONG)p_fifo + 2UL);
        }
        else
        {
            /* USBHS controller needs address offset (+3) for 8-bit access to the FIFO. */
            p_fifo =  (VOID *)((ULONG)p_fifo + 3UL);
        }
    }
#endif


    /* Follow the correct DMA HW sequence. This is the HW bug - we need to follow the
     * below sequence to kick the DMA - as suggested by HW team.
     * A.i. Check DnFIFOCTR.FRDY and make sure the bit is read as '0'.
     * As DnFIFOCTR register is to be read for HW sake, it is not used anywhere
     * So just read it to read_pipe_number - which is overwritten in next steps
     * */
    dcd_synergy->read_pipe_number =  ux_dcd_synergy_register_read(dcd_synergy, (ULONG) p_fifo_ctrl);

    /* A.ii. Set 4'b0000 to DnFIFOSEL.CURPIPE
     * First notedown the pipe used */
    pipe_used_for_dma = (USHORT) (ux_dcd_synergy_register_read (dcd_synergy, (ULONG) p_fifo_sel));

    /* Pipe number is only last 4 bits */
    pipe_used_for_dma = pipe_used_for_dma & UX_SYNERGY_DCD_PIPESEL_NO_PIPE;
    /* Make a note of pipe used for read. This is used in callback for
     * setting the NAK for read pipe */
    dcd_synergy->read_pipe_number = (ULONG) pipe_used_for_dma;

    ux_dcd_synergy_register_clear (dcd_synergy, (ULONG) p_fifo_sel, (USHORT) UX_SYNERGY_DCD_PIPESEL_NO_PIPE_USHORT);

    /* Modified the sequence of DMA configuration as optimization is affecting the
     * functionality. Below block reset function moved from, before A.i to after A.ii */
    transfer_length = dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->length;
    num_blocks      = dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->num_blocks;
    /* Setup DMA block transfer. */
    dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_api->blockReset(
    		dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_ctrl,
			p_fifo, p_payload_buffer, transfer_length,
			dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->size,
			num_blocks);

   /* A.iii. Set 1 to DnFIFOSEL.DREQE, and set DnFIFOSEL.MBW if required.
    * MBW is already set now... */
    ux_dcd_synergy_register_set(dcd_synergy, (ULONG) p_fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_DREQE);


    /* A.iv. Set a PIPE number to DnFIFOSEL.CURPIPE
     * Currently pipe 2 is used for IN (for write) */
    ux_dcd_synergy_register_set(dcd_synergy, (ULONG) p_fifo_sel, pipe_used_for_dma);

    /* B.i. Set "BUF" to PIPEnCTR.PID
     * This should trigger the DMA - finally
     * Currently pipe 2 is used. So setting it to BUF */
    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR + ((pipe_used_for_dma - 1UL) * 2UL), (USHORT)(UX_SYNERGY_DCD_PIPECTR_PIDBUF));
}

/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO read by software copy.  Call a subroutine for selected USB controller hardware.
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 * @param[in]      fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_fifo_read_software_copy (UX_DCD_SYNERGY *dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    VOID * p_fifo,
                                                    ULONG  fifo_sel)
{
#if defined(R_USBHS_BASE)
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        /* Transfer data by software copy. */
        ux_dcd_synergy_fifo_read_software_copy_32bit (dcd_synergy, p_payload, p_fifo, fifo_sel);
    }
    else
#endif
    {
        /* Transfer data by software copy. */
        ux_dcd_synergy_fifo_read_software_copy_16bit (dcd_synergy, p_payload, p_fifo, fifo_sel);
    }
}

#if defined(R_USBHS_BASE)
/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO read - Software copy for USB hardwares with 32-bit FIFO
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 * @param[in]      fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_fifo_read_software_copy_32bit (UX_DCD_SYNERGY *dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    VOID * p_fifo,
                                                    ULONG  fifo_sel)
{
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        if(0 == ((UINT)p_payload -> payload_buffer % 4U))
        {
            /* Calculate FIFO access times. */
            p_payload -> transfer_times = (UINT)(p_payload -> payload_length / 4U);
            p_payload -> transfer_width = 4U;
            p_payload -> payload_length = p_payload -> payload_length - (p_payload -> transfer_times * 4);

            /* Set the width to 32-bit. */
            ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_32);

            while (0U != p_payload -> transfer_times)
            {
                /* Read 32-bit value from FIFO. */
                *(ULONG *)(p_payload -> payload_buffer) =  *(volatile ULONG *) p_fifo;

                /* Update the payload buffer address. */
                p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(ULONG);

                --p_payload -> transfer_times;
            }

            ux_dcd_synergy_fifo_read_last_bytes (p_payload, p_fifo);
        }
        else
        {
            ux_dcd_synergy_fifo_read_software_copy_16bit (dcd_synergy, p_payload, p_fifo, fifo_sel);
        }
    }
}
#endif

/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO read - Software copy for USB hardwares with 16-bit FIFO
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 * @param[in]      fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_fifo_read_software_copy_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    VOID * p_fifo,
                                                    ULONG  fifo_sel)
{
    if(0 == ((UINT)p_payload -> payload_buffer % 2U))
    {
        /* Calculate FIFO access times. */
        p_payload -> transfer_times = (UINT)(p_payload -> payload_length / 2U);
        p_payload -> transfer_width = 2U;
        p_payload -> payload_length = p_payload -> payload_length - (p_payload -> transfer_times * 2);

        /* Set the width to 16-bit. */
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_16);

#if defined(R_USBHS_BASE)
        /* USBHS controller needs address offset (+2) for 16-bit access to the FIFO. */
        if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
        {
            p_fifo =  (VOID *)((ULONG)p_fifo + 2UL);
        }
#endif

        while (0U != p_payload -> transfer_times)
        {
            /* Read 16-bit value from FIFO. */
            *(USHORT *)(p_payload -> payload_buffer) =  *(volatile USHORT *) p_fifo;

            /* Update the payload buffer address. */
            p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(USHORT);

            --p_payload -> transfer_times;
        }

        ux_dcd_synergy_fifo_read_last_bytes (p_payload, p_fifo);
    }
    else
    {
        ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_8);

#if defined(R_USBHS_BASE)
        /* USBHS controller needs address offset (+3) for 8-bit access to the FIFO. */
        if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
        {
            p_fifo =  (VOID *)((ULONG)p_fifo + 3UL);
        }
#endif

        while (0U != p_payload -> payload_length)
        {
            /* Read 8-bit value from FIFO. */
            *(UCHAR *)(p_payload -> payload_buffer) = *(volatile UCHAR *) p_fifo;

            /* Update the payload buffer address  */
            p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(UCHAR);

            /* And the remaining length  */
            p_payload -> payload_length = p_payload -> payload_length - (INT)sizeof(UCHAR);
        }
    }
}

/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO read - Copy last bytes from FIFO by software if the rest bytes are less than FIFO access width
 *
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_fifo_read_last_bytes (UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                     VOID * p_fifo)
{
    local_buffer_t  local_buffer;
    INT             byte_count = 0;

    if (0U != p_payload -> payload_length)
    {
        /* Send remaining bytes by software copy. */
        if (4U == p_payload -> transfer_width)
        {
            /* Read data at once from FIFO. */
            local_buffer.input = *((volatile ULONG *)p_fifo);

            while ((INT)p_payload -> payload_length > byte_count)
            {
                /* Copy data to the payload buffer 1 byte each. */
                *(UCHAR *)(p_payload -> payload_buffer) = local_buffer.output[byte_count++];

                /* Update the payload buffer address  */
                p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(UCHAR);
            }
        }
        else
        {
            /* Read data at once from FIFO. */
            local_buffer.input = *(volatile USHORT *)p_fifo;

            while ((INT)p_payload -> payload_length > byte_count)
            {
                /* Copy data to the payload buffer 1 byte each. */
                *(UCHAR *)(p_payload -> payload_buffer) = local_buffer.output[byte_count++];

                /* Update the payload buffer address  */
                p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(UCHAR);
            }
        }
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
