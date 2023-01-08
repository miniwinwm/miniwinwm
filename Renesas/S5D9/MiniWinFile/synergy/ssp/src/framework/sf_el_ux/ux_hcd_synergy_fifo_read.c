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
#include "ux_utility.h"
#include "r_transfer_api.h"

static VOID ux_hcd_synergy_fifo_read_software_copy(UX_HCD_SYNERGY *hcd_synergy,
                                                   UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                   UX_HCD_SYNERGY_FIFO *fifo);

static VOID ux_hcd_synergy_fifo_read_software_copy_16bit(UX_HCD_SYNERGY *hcd_synergy,
                                                         UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                         UX_HCD_SYNERGY_FIFO *fifo);

static VOID ux_hcd_synergy_fifo_read_software_copy_8bit(UX_HCD_SYNERGY *hcd_synergy,
                                                        UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                        UX_HCD_SYNERGY_FIFO *fifo);

static VOID ux_hcd_synergy_fifo_read_dma_start(UX_HCD_SYNERGY *hcd_synergy,
                                               UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                               UX_HCD_SYNERGY_FIFO *fifo);

#if defined(R_USBHS_BASE)
static VOID ux_hcd_synergy_fifo_read_dma_set_32bit(UX_HCD_SYNERGY *hcd_synergy,
                                                   UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                   UX_HCD_SYNERGY_FIFO *fifo);
#endif

static VOID ux_hcd_synergy_fifo_read_dma_set_16bit_or_8bit(UX_HCD_SYNERGY *hcd_synergy,
                                                            UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                            UX_HCD_SYNERGY_FIFO *fifo);



/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_fifo_read                            PORTABLE C      */
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
/*    hcd_synergy                           Pointer to Synergy controller */
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
 * @brief This function read data from the FIFO configured for the PIPE(FIFO C, D0 or D1).
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in]      ed          : Pointer to Synergy ED structure
 *
 * @retval UX_ERROR                        Unable to access FIFO successfully.
 * @retval UX_SYNERGY_HC_FIFO_READ_OVER    Status set to read overflow.
 * @retval UX_SYNERGY_HC_FIFO_READ_SHORT   Short packet to read.
 * @retval UX_SYNERGY_HC_FIFO_READING      Continue reading buffer.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_fifo_read(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed)
{
    UX_SYNERGY_TD * td;
    ULONG           fifo_access_status;
    ULONG           max_packet_size;
    UINT            status;
    UX_HCD_SYNERGY_PAYLOAD_TRANSFER payload;
    UX_HCD_SYNERGY_FIFO fifo;

    /* We need to select the FIFO registers.  */
    switch (ed -> ux_synergy_fifo_index)
    {
        case (ULONG)UX_SYNERGY_HC_FIFO_D0 :

            /* Set fifo_sel and fifo_addr fields to FIFO_D0 */
            fifo.fifo_sel  =  UX_SYNERGY_HC_D0FIFOSEL;
            fifo.fifo_addr =  (VOID *)(hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_D0FIFO);
            fifo.fifo_ctrl =  UX_SYNERGY_HC_D0FIFOCTR;
            break;

        case (ULONG)UX_SYNERGY_HC_FIFO_D1 :

            /* Set fifo_sel and fifo_addr fields to FIFO_D1 */
            fifo.fifo_sel  =  UX_SYNERGY_HC_D1FIFOSEL;
            fifo.fifo_addr =  (VOID *)(hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_D1FIFO);
            fifo.fifo_ctrl =  UX_SYNERGY_HC_D1FIFOCTR;
            break;

        default :

            /* Set fifo_sel and fifo_addr fields to FIFO_C */
            fifo.fifo_sel  =  UX_SYNERGY_HC_CFIFOSEL;
            fifo.fifo_addr =  (VOID *)(hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_CFIFO);
            fifo.fifo_ctrl =  UX_SYNERGY_HC_CFIFOCTR;
            break;
    }

    /* Get the FIFO access status for the endpoint.  */
    fifo_access_status =  ux_hcd_synergy_fifo_port_change(hcd_synergy, ed, 0);

    /* Check Status.  */
    if (fifo_access_status == (ULONG)UX_ERROR)
    {
        /* We have an error. Abort.  */
        return (UINT)UX_ERROR;
    }

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* Isolate the payload length.  */
    payload.payload_length = fifo_access_status & UX_SYNERGY_HC_FIFOCTR_DTLN;

    /* Get the TD used for this transfer.  */
    td =  ed->ux_synergy_ed_head_td;

    /* Save the payload length in the TD. This is needed to check for end of transfer.  */
    td -> ux_synergy_td_actual_length =  payload.payload_length;

    /* Set NAK.  */
    ux_hcd_synergy_endpoint_nak_set(hcd_synergy, ed);

    /* Check for overwrite.  */
    if (td -> ux_synergy_td_length < payload.payload_length)
    {
        /* Set Status to read overflow.  */
        status = (UINT)UX_SYNERGY_HC_FIFO_READ_OVER;

        /* Set the payload length to the size wanted by the caller.  */
        payload.payload_length = td -> ux_synergy_td_length;
    }

    else
    {
        /* Check for short packet.  */
        if ((payload.payload_length == 0UL) || ((payload.payload_length % max_packet_size) != 0UL))
        {
            /* We have a short packet.  */
            status = (UINT)UX_SYNERGY_HC_FIFO_READ_SHORT;
        }
        else
        {
            /* Continue reading.  */
            status = (UINT)UX_SYNERGY_HC_FIFO_READING;
        }
    }

    /* Check for 0 length packet.  */
    if (payload.payload_length == 0UL)
    {
        /* Set the BCLR flag.  */
        ux_hcd_synergy_register_set(hcd_synergy, fifo.fifo_ctrl, (USHORT)UX_SYNERGY_HC_FIFOCTR_BCLR);
    }
    else
    {
        /* Get the payload buffer address.  */
        payload.payload_buffer =  td -> ux_synergy_td_buffer;

        /* Check we can use DMA for data transfer.
         * check the payload length is less than 4, then do software copy. Because in case of 32-bit DMA, transfer length
         * will be zero which makes the DMA semaphore_rx wait forever. Same for 16-bit DMA also if payload length is less than 2.*/
        if((hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx != NULL) &&
                (ed -> ux_synergy_fifo_index == (ULONG)UX_SYNERGY_HC_FIFO_D1) && (payload.payload_length >= sizeof(UINT)))
        {
            /* Wait untill last DMA transfer completes */
            _ux_utility_semaphore_get(&hcd_synergy->ux_hcd_synergy_semaphore_rx, UX_WAIT_FOREVER);

            /* Transfer data by DMA */
            ux_hcd_synergy_fifo_read_dma_start(hcd_synergy, &payload, &fifo);
        }
        else
        {
            /* Use software copy for data transfer */
            ux_hcd_synergy_fifo_read_software_copy(hcd_synergy, &payload, &fifo);
        }
    }

    /* Return status about buffer transfer.  */
    return(status);
}

/******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO read by software copy.  Call a suitable subroutine for selected USB controller hardware.
 *
 * @param[in]      hcd_synergy      Pointer to the HCD control block
 * @param[in]      payload          Pointer to the Payload block
 * @param[in]      fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_read_software_copy(UX_HCD_SYNERGY *hcd_synergy,
                                                   UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                   UX_HCD_SYNERGY_FIFO *fifo)
{
    /* Currently we support 16-bit and 8-bit FIFO access width */
    if(((UINT)payload->payload_buffer % 2) == 0)
    {
        /* 16-bit software copy */
        ux_hcd_synergy_fifo_read_software_copy_16bit(hcd_synergy, payload, fifo);
    }
    else
    {
        /* 8-bit software copy */
        ux_hcd_synergy_fifo_read_software_copy_8bit(hcd_synergy, payload, fifo);
    }
}

/******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO read - Software copy with 16-bit FIFO access
 *
 * @param[in]          hcd_synergy      Pointer to the HCD control block
 * @param[in,out]      payload          Pointer to the Payload block
 * @param[in]          fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_read_software_copy_16bit(UX_HCD_SYNERGY *hcd_synergy,
                                                         UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                         UX_HCD_SYNERGY_FIFO *fifo)
{
    UINT fifo_access_times;

    /* Calculate FIFO access times. */
    fifo_access_times = (UINT)(payload->payload_length / 2U);
    payload->payload_length    = payload->payload_length - ((ULONG)fifo_access_times * 2UL);

    /* Set FIFO access width to 16 bits. */
    ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
    ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_16);

    while (fifo_access_times != 0U)
    {
        /* Read 16 bits value.  */
        *(USHORT *)payload->payload_buffer =  *(volatile USHORT *) fifo->fifo_addr;

        /* Update the payload buffer address.  */
        payload->payload_buffer += sizeof(USHORT);

        /* And the remaining length.  */
        --fifo_access_times;
    }

    /* If we have a single byte to transfer */
    if(payload->payload_length != 0UL)
    {
        typedef union local_buffer_u
        {
            USHORT   input;
            UCHAR   output[2];
        } local_buffer_t;

        local_buffer_t local_buffer;

        /* Read 16-bit value at once from FIFO to the local buffer. */
        local_buffer.input =  *(volatile USHORT *) fifo->fifo_addr;

        /* Only pick up 8-bit value. */
        *(UCHAR *)payload->payload_buffer = local_buffer.output[0];
    }
    /* Need to clear the buffer once complete data is read out. */
    ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_ctrl, UX_SYNERGY_HC_FIFOCTR_BCLR );
}

/*******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO read - Software copy with 8-bit FIFO access
 *
 * @param[in]           hcd_synergy      Pointer to the HCD control block
 * @param[in, out]      payload          Pointer to the Payload block
 * @param[in]           fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_read_software_copy_8bit(UX_HCD_SYNERGY *hcd_synergy,
                                                        UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                        UX_HCD_SYNERGY_FIFO *fifo)
{
    /* Set FIFO access to 8 bits. */
    ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
    ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_8);

    while (payload->payload_length != 0UL)
    {
        /* Read 8 bits value.  */
        *(UCHAR *)payload->payload_buffer =  *(volatile UCHAR *) fifo->fifo_addr;

        /* Update the payload buffer address.  */
        payload->payload_buffer += sizeof(UCHAR);

        /* And the remaining length.  */
        payload->payload_length -= sizeof(UCHAR);
    }
    /* Need to clear the buffer once complete data is read out. */
    ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_ctrl, UX_SYNERGY_HC_FIFOCTR_BCLR );
}

/******************************************************************************************************************//**
 * @brief  USBX HCD DMA read setup function.
 *
 * @param[in,out]  hcd_synergy      Pointer to the HCD control block
 * @param[in,out]  payload          Pointer to the Payload block
 * @param[in]      fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_read_dma_start(UX_HCD_SYNERGY *hcd_synergy,
                                               UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                               UX_HCD_SYNERGY_FIFO *fifo)
{
    /* Set single DMA transfer */
    payload->transfer_block_count = 1U;

#if defined(R_USBHS_BASE)
    if ( (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base) && (((UINT)payload->payload_buffer % 4) == 0) )
    {
        /* Setup DMA 32-bit transfer */
        ux_hcd_synergy_fifo_read_dma_set_32bit(hcd_synergy, payload, fifo);
    }
    else
#endif
    {
        /* Setup DMA 16 or 8 bit transfer */
        ux_hcd_synergy_fifo_read_dma_set_16bit_or_8bit(hcd_synergy, payload, fifo);
    }

    /* Update the remaining bytes in payload to be transfered by software copy and the payload buffer
     * pointer. */
    hcd_synergy->remaining_payload_bytes = (uint16_t) payload->payload_length;
    hcd_synergy->payload_buffer = payload->payload_buffer;

    /* Check if we have DMA transfer length is non-zero value, else do software copy */
    if(hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length != 0U)
    {
        /* Calculate the buffer offset to be used in DMA completion callback for remaining transfer. */
        hcd_synergy->payload_buffer += ((UINT)hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length
                                         * (payload->transfer_block_count) * (UINT)(payload->transfer_width) );

        /* Setup DMA. */
        hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_api->blockReset(
                hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_ctrl,
                fifo->fifo_addr,
                payload->payload_buffer,
                hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length,
                hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->size,
                (uint16_t)payload->transfer_block_count);

        /* Trigger DMA by software control. */
        hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_api->start(
                hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_ctrl,
                TRANSFER_START_MODE_REPEAT);
    }
    else
    {
        /* We have just few bytes so perform software copy with 8-bit FIFO access size. */
        ux_hcd_synergy_fifo_read_software_copy_8bit(hcd_synergy, payload, fifo);
    }
}

#if defined(R_USBHS_BASE)
/******************************************************************************************************************//**
 * @brief  USBX HCD DMA FIFO read - DMA transfer with 32-bit FIFO access.
 *
 * @param[in,out]  hcd_synergy      Pointer to the HCD control block
 * @param[in,out]  payload          Pointer to the Payload block
 * @param[in]      fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_read_dma_set_32bit(UX_HCD_SYNERGY *hcd_synergy,
                                                   UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                   UX_HCD_SYNERGY_FIFO *fifo)
{
    payload->transfer_width = 4U;
    hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->size   = TRANSFER_SIZE_4_BYTE;
    hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length =
            (uint16_t)(payload->payload_length / 4U);
    payload->payload_length -= (ULONG)(hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length * 4U);

    ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
    ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_32);
}
#endif

/******************************************************************************************************************//**
 * @brief  USBX HCD DMA FIFO read - DMA transfer with 16 or 8 bit FIFO access.
 *
 * @param[in,out]  hcd_synergy      Pointer to the HCD control block
 * @param[in,out]  payload          Pointer to the Payload block
 * @param[in]      fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_read_dma_set_16bit_or_8bit(UX_HCD_SYNERGY *hcd_synergy,
                                                           UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                           UX_HCD_SYNERGY_FIFO *fifo)
{
    if(((UINT)payload->payload_buffer % 2) == 0)
    {
        /* We use 16 bits to transfer.  */
        payload->transfer_width = 2U;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->size = TRANSFER_SIZE_2_BYTE;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length =
                (uint16_t)(payload->payload_length / 2);
        payload->payload_length -= (ULONG)(hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length * 2);

        /* Set FIFO access width to 16 bits. */
        ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
        ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_16);
    }
    else
    {
        /* We use 8 bits to transfer.  */
        payload->transfer_width = 1U;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->size = TRANSFER_SIZE_1_BYTE;

        /* If payload length is greater than 1024, then number of transfer is set to 2. This is because DMA support maximum
         * transfer length up to 1024 for one block transfer*/
        if(payload->payload_length > 1024UL)
        {
            /* set number of transfer is 2 */
            payload->transfer_block_count = 2U;
            /* set the transfer length equal for each transfer */
            hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length = (uint16_t) ( payload->payload_length
                                                                                    / (payload->transfer_block_count) );
        }
        else
        {
            /* Set single transfer because transfer length is within DMA maximum transfer length i.e., 1024. */
            payload->transfer_block_count = 1U;
            hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->length = (uint16_t) payload->payload_length;
        }
        payload->payload_length = 0U;

        /* Set FIFO access width to 8 bits. */
        ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
        ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_8);
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
