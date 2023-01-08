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

static VOID ux_hcd_synergy_fifod_write_dma_start(UX_HCD_SYNERGY *hcd_synergy,
                                                 UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                 UX_HCD_SYNERGY_FIFO *fifo);
#if defined(R_USBHS_BASE)
static VOID ux_hcd_synergy_fifod_write_dma_set_32bit(UX_HCD_SYNERGY *hcd_synergy,
                                                     UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                     UX_HCD_SYNERGY_FIFO *fifo);
#endif

static VOID ux_hcd_synergy_fifod_write_dma_set_16bit_or_8bit(UX_HCD_SYNERGY *hcd_synergy,
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
/*    ux_hcd_synergy_fofod_write                          PORTABLE C      */
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
 * @brief  This function writes a buffer data to FIFOD0 or FIFOD1.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to Synergy ED structure
 *
 * @retval UX_ERROR                        Unable to access FIFO successfully.
 * @retval UX_SYNERGY_HC_FIFO_WRITE_END    Writing at ends.
 * @retval UX_SYNERGY_HC_FIFO_WRITE_SHORT  Writing short data.
 * @retval UX_SYNERGY_HC_FIFO_WRITING      Doing multiple writes.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_fifod_write(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed)
{
    UX_SYNERGY_TD * td;
    ULONG           fifo_access_status;
    ULONG           max_packet_size;
    ULONG           data_buffer_size;
    UINT            status;
    ULONG           synergy_register;
    UX_HCD_SYNERGY_PAYLOAD_TRANSFER payload;
    UX_HCD_SYNERGY_FIFO fifo;

    /* Get the Fifo access status.  */
    fifo_access_status =  ux_hcd_synergy_fifo_port_change(hcd_synergy, ed, 0UL);

    /* Check Status.  */
    if (fifo_access_status == (ULONG)UX_ERROR)
    {
        /* We have an error. Abort.  */
        return (UINT)UX_ERROR;
    }

    /* Get the data buffer size.  */
    data_buffer_size = ux_hcd_synergy_data_buffer_size(hcd_synergy, ed);

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* Get the TD used for this transfer.  */
    td =  ed->ux_synergy_ed_head_td;

    /* Check if this transfer takes more than one packet.  */
    if (td -> ux_synergy_td_length <= max_packet_size) 
    {
        /* Set the payload to the TD payload length.  */
        payload.payload_length =  td -> ux_synergy_td_length;

        /* Set Status to write ends.  */
        status = (UINT)UX_SYNERGY_HC_FIFO_WRITE_END;

        /* Check for 0 packet.  */
        if ((td -> ux_synergy_td_length == 0UL) || ((td -> ux_synergy_td_length % max_packet_size ) != 0UL))
        {
            /* Set Status to write short.  */
            status = (UINT)UX_SYNERGY_HC_FIFO_WRITE_SHORT;
        }
    }
    else
    {
        /* We are doing a multi write.  */
        status = (UINT)UX_SYNERGY_HC_FIFO_WRITING;

#if defined(R_USBHS_BASE)
        /* Payload length is the FIFO size.  */
        if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
        {
            payload.payload_length = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD;
        }
        else
#endif
        {
            /* Payload length is the buffer size.  */
            payload.payload_length = data_buffer_size;
        }
    }      

    /* We need to select the FIFO registers.  */
    if (ed -> ux_synergy_fifo_index == UX_SYNERGY_HC_FIFO_D0)
    {
        /* Set fifo_sel and fifo_addr fields to FIFO_D0 */
        fifo.fifo_sel  =  UX_SYNERGY_HC_D0FIFOSEL;
        fifo.fifo_addr =  (VOID *) (hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_D0FIFO);
        fifo.fifo_ctrl =  UX_SYNERGY_HC_D0FIFOCTR;
    }
    else
    {
        /* Set fifo_sel and fifo_addr fields to FIFO_D1 */
        fifo.fifo_sel  =  UX_SYNERGY_HC_D1FIFOSEL;
        fifo.fifo_addr =  (VOID *) (hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_D1FIFO);
        fifo.fifo_ctrl =  UX_SYNERGY_HC_D1FIFOCTR;
    }

    /* Get the payload buffer address.  */
    payload.payload_buffer =  td -> ux_synergy_td_buffer;

    /* Clear FIFO before the use to discard possible remaining data in the previous transfer.  */
    ux_hcd_synergy_register_set(hcd_synergy, fifo.fifo_ctrl, UX_SYNERGY_HC_FIFOCTR_BCLR );

    /* Check we can use DMA for data transfer.  */
    if(hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx != 0U)
    {
        /* Transfer data by DMA */
        ux_hcd_synergy_fifod_write_dma_start(hcd_synergy, &payload, &fifo);
    }
    else
    {
        /* Use software copy for data transfer. */
        ux_hcd_synergy_fifo_write_software_copy(hcd_synergy, payload.payload_length, payload.payload_buffer, fifo.fifo_addr, fifo.fifo_sel);
    }

    /* Check status. If we have a short packet, we need to set the BVAL flag in the USB controller. */
    if (status != (UINT)UX_SYNERGY_HC_FIFO_WRITING)
    {
        /* Read the current FIFO control register.  */
        synergy_register = ux_hcd_synergy_register_read(hcd_synergy, fifo.fifo_ctrl);

        /* Check if the BVAL bit is already set.  */
        if ((synergy_register & UX_SYNERGY_HC_FIFOCTR_BVAL) == 0UL)
        {
            /* No so set it.  This will enable the Buffer Memory Valid flag.
               This bit is set to 1 when data has been written to the FIFO and
               this is a short packet or zero packet or a full packet but not the
               end of the transmission.  */
            ux_hcd_synergy_register_set(hcd_synergy, fifo.fifo_ctrl, UX_SYNERGY_HC_FIFOCTR_BVAL);
        }
    }

    /* Return status about buffer transfer.  */
    return (UINT)status;
}

/******************************************************************************************************************//**
 * @brief  USBX HCD DMA write setup function.  Call a suitable subroutine for selected USB controller hardware.
 *
 * @param[in,out]  hcd_synergy      Pointer to the HCD control block
 * @param[in,out]  payload          Pointer to the Payload block
 * @param[in]      fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifod_write_dma_start(UX_HCD_SYNERGY *hcd_synergy,
                                                 UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                 UX_HCD_SYNERGY_FIFO *fifo)
{
    /* Set single DMA transfer */
    payload->transfer_block_count = 1U;

    /* Set transfer size.  */
#if defined(R_USBHS_BASE)
    if ( (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base) && (((UINT)payload->payload_buffer % 4) == 0) )
    {
        /* Setup DMA 32-bit transfer */
        ux_hcd_synergy_fifod_write_dma_set_32bit(hcd_synergy, payload, fifo);
    }
    else
#endif
    {
        /* Setup DMA 16 or 8 bit transfer */
        ux_hcd_synergy_fifod_write_dma_set_16bit_or_8bit(hcd_synergy, payload, fifo);
    }

    /* Check if we have DMA transfer length is non-zero value, else do software copy */
    if(hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length != 0U)
    {
        /* Setup DMA. */
        hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_api->blockReset(
                hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl,
                payload->payload_buffer,
                fifo->fifo_addr,
                hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length,
                hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->size,
                (uint16_t)payload->transfer_block_count);

        /* Trigger DMA by software control. */
        hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_api->start(
                hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl,
                TRANSFER_START_MODE_REPEAT);

        /* Wait until current DMA transfer completes. */
        _ux_utility_semaphore_get(&hcd_synergy->ux_hcd_synergy_semaphore_tx, UX_WAIT_FOREVER);
    }

    /* Update the payload buffer address after DMA transfer */
    payload->payload_buffer += ((ULONG)hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length
                                    * (payload->transfer_width) * (payload->transfer_block_count) );

    if(payload->payload_length != 0UL)
    {
         /* Reset the fifo address*/
         fifo->fifo_addr =  (VOID *) (hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_D0FIFO);
         ux_hcd_synergy_fifo_write_software_copy_remaining_bytes(hcd_synergy, payload->payload_length,
                                                                   payload->payload_buffer, fifo->fifo_addr);
    }
}

#if defined(R_USBHS_BASE)
/******************************************************************************************************************//**
 * @brief  USBX HCD DMA FIFO write - DMA transfer with 32-bit FIFO access.
 *
 * @param[in,out]  hcd_synergy      Pointer to the HCD control block
 * @param[in,out]  payload          Pointer to the Payload block
 * @param[in]      fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifod_write_dma_set_32bit(UX_HCD_SYNERGY *hcd_synergy,
                                                     UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                     UX_HCD_SYNERGY_FIFO *fifo)
{
     payload->transfer_width = 4U;
     hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->size   = TRANSFER_SIZE_4_BYTE;
     hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length = (uint16_t)(payload->payload_length / 4U);
     payload->payload_length -=  (ULONG)(hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length * 4U);

     ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
     ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_32);
}
#endif

/******************************************************************************************************************//**
 * @brief  USBX HCD DMA FIFO write - DMA transfer with 16 or 8 bit FIFO access.
 *
 * @param[in,out]      hcd_synergy      Pointer to the HCD control block
 * @param[in,out]      payload          Pointer to the Payload block
 * @param[in,out]      fifo             Pointer to the fifo block
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifod_write_dma_set_16bit_or_8bit(UX_HCD_SYNERGY *hcd_synergy,
                                                              UX_HCD_SYNERGY_PAYLOAD_TRANSFER *payload,
                                                              UX_HCD_SYNERGY_FIFO *fifo)
{
    if(((UINT)payload->payload_buffer % 2) == 0)
    {
        /* We use 16 bits to transfer.  */
        payload->transfer_width = 2U;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->size   = TRANSFER_SIZE_2_BYTE;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length = (uint16_t)(payload->payload_length / 2U);
        payload->payload_length -= (ULONG)(hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length * 2U);

        /* Set FIFO access width to 16 bits. */
        ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
        ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_16);

#if defined(R_USBHS_BASE)
        /* This needs for 16-bit write for USBHS. */
        if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
        {
            fifo->fifo_addr = (VOID *) ((ULONG) fifo->fifo_addr + 2UL);
        }
#endif
    }
    else
    {
        /* We use 8 bits to transfer.  */
        payload->transfer_width = 1U;

        /* If payload length is greater than 1024, then number of transfer is set to 2. This is because DMA support maximum
         * transfer length up to 1024 for each transfer*/
        if(payload->payload_length > 1024UL)
        {
            /* set number of transfer is 2 */
            payload->transfer_block_count = 2U;
            /* set the transfer length equal for each transfer */
            hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length = (uint16_t) (payload->payload_length
                                                                                    / (payload->transfer_block_count) );
        }
        else
        {
            /* Set single transfer because transfer length is within DMA maximum transfer length i.e., 1024. */
            payload->transfer_block_count = 1U;
            hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length = (uint16_t) payload->payload_length;
        }
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->size = TRANSFER_SIZE_1_BYTE;
        payload->payload_length -= (ULONG) (hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->length * (payload->transfer_block_count) );

        /* Set FIFO access width to 8 bits. */
        ux_hcd_synergy_register_clear(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_MASK);
        ux_hcd_synergy_register_set(hcd_synergy, fifo->fifo_sel, (USHORT)UX_SYNERGY_HC_DFIFOSEL_MBW_8);

#if defined(R_USBHS_BASE)
        /* This needs for 8-bit write for USBHS. */
        if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
        {
            fifo->fifo_addr = (VOID *) ((ULONG) fifo->fifo_addr + 3UL);
        }
#endif
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
