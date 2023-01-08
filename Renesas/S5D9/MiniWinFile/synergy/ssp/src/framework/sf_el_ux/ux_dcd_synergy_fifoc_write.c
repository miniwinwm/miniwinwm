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

static VOID ux_dcd_synergy_fifo_write_software_copy_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                                UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                VOID * p_fifo,
                                                ULONG  fifo_sel);
#if defined(R_USBHS_BASE)
static VOID ux_dcd_synergy_fifo_write_software_copy_32bit (UX_DCD_SYNERGY *dcd_synergy,
                                                UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                VOID * p_fifo,
                                                ULONG  fifo_sel);
#endif

#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
VOID ux_dcd_synergy_write_dma_set (UX_DCD_SYNERGY *dcd_synergy,
                                            UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                            ULONG fifo_sel);

VOID ux_dcd_synergy_fifo_write_dma_start (UX_DCD_SYNERGY * dcd_synergy,
                                            UCHAR * payload_buffer,
                                            VOID * p_fifo);
#endif

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_dcd_synergy_fifod_write                         PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function writes a buffer to FIFOC                              */ 
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

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function writes a data from a buffer into USB FIFO using CPU.
 *
 * @param[in,out]  dcd_synergy             : Pointer to a DCD control block
 * @param[in,out]  ed                      : Pointer to a physical Endpoint(ED) control block
 *
 * @retval UX_ERROR                         FIFO is not accessible.
 * @retval UX_SYNERGY_DCD_FIFO_WRITE_END    Status for fifo write ends.
 * @retval UX_SYNERGY_DCD_FIFO_WRITING      Status for fifo multiple writes.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_fifoc_write(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed)
{
    ULONG   fifo_access_status;
    ULONG   max_packet_size;
    ULONG   data_buffer_size;
    UINT    status;
    VOID  * cfifo_ptr;
    UX_DCD_SYNERGY_PAYLOAD_TRANSFER payload;

    /* Configure CFIFO for required endpoint. */
    fifo_access_status =  ux_dcd_synergy_fifo_port_change(dcd_synergy, ed, UX_SYNERGY_DCD_CFIFOSEL_ISEL);

    /* Check Status.  */
    if (fifo_access_status == (ULONG)UX_ERROR)
    {
        /* We have an error. Abort.  */
        return (UINT)UX_ERROR;
    }

    /* Get the data buffer size.  */
    data_buffer_size = ed -> ux_dcd_synergy_ed_endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;

    /* Get the max packet size for this endpoint.  */
    max_packet_size = ed -> ux_dcd_synergy_ed_endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;

    /* Check if this transfer takes more than one packet.  */
    if (ed -> ux_dcd_synergy_ed_payload_length <= max_packet_size)
    {
        /* Set the payload to the TD payload length.  */
        payload.payload_length =  ed -> ux_dcd_synergy_ed_payload_length;

        /* Set Status to write ends.  */
        status = (UINT)UX_SYNERGY_DCD_FIFO_WRITE_END;
    }
    else
    {
        /* We are doing a multi write.  */
        status = (UINT)UX_SYNERGY_DCD_FIFO_WRITING;

        /* Payload length is the buffer size.  */
        payload.payload_length = data_buffer_size;

    }

    /* Get the payload buffer address.  */
    payload.payload_buffer =  ed -> ux_dcd_synergy_ed_payload_address;

    /* Memorize packet length.  */
    ed -> ux_dcd_synergy_ed_packet_length = payload.payload_length;

    /* Initialize the CFIFO register address. */
    cfifo_ptr = (VOID *)(dcd_synergy->ux_dcd_synergy_base + UX_SYNERGY_DCD_CFIFO);

    /* Transfer data by software copy. */
    ux_dcd_synergy_fifo_write_software_copy (dcd_synergy, &payload, cfifo_ptr, UX_SYNERGY_DCD_CFIFOSEL);

    /* Check status. If we have a short packet, we need to set
       the BVAL flag in the Fifo controller. */
    if (status != UX_SYNERGY_DCD_FIFO_WRITING)
    {
        /* This is short packet. Set the BVAL bit */
        ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BVAL);
    }

    /* Return status about buffer transfer.  */
    return (status);
}


/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO write by software copy.  Call a subroutine for selected USB controller hardware.
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 * @param[in]      fifo_sel         FIFO select register
 **********************************************************************************************************************/
VOID ux_dcd_synergy_fifo_write_software_copy (UX_DCD_SYNERGY *dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    VOID * p_fifo,
                                                    ULONG  fifo_sel)
{
#if defined(R_USBHS_BASE)
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        /* Transfer data by software copy. */
        ux_dcd_synergy_fifo_write_software_copy_32bit (dcd_synergy, p_payload, p_fifo, fifo_sel);
    }
    else
#endif
    {
        /* Transfer data by software copy. */
        ux_dcd_synergy_fifo_write_software_copy_16bit (dcd_synergy, p_payload, p_fifo, fifo_sel);
    }
}

#if defined(R_USBHS_BASE)
/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO write - Software copy for USB hardwares with 32-bit FIFO
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 * @param[in]      fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_fifo_write_software_copy_32bit (UX_DCD_SYNERGY *dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    VOID * p_fifo,
                                                    ULONG  fifo_sel)
{
    if (dcd_synergy -> ux_dcd_synergy_base == R_USBHS_BASE)
    {
        if(0 == ((UINT)p_payload -> payload_buffer % 4U))
        {
            /* Calculate FIFO access times. */
            p_payload -> transfer_times = (UINT)((p_payload -> payload_length) / (4U));
            p_payload -> transfer_width = 4U;
            p_payload -> payload_length = p_payload -> payload_length - (p_payload -> transfer_times * 4);

            /* Set the width to 32-bit. */
            ux_dcd_synergy_register_set(dcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_MBW_32);

            while (0U != p_payload -> transfer_times)
            {
                /* Write 32 bit value to FIFO. */
                *(volatile ULONG *) p_fifo = *(ULONG *)(p_payload -> payload_buffer);

                /* Update the payload buffer address. */
                p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(ULONG);

                --p_payload -> transfer_times;
            }

            ux_dcd_synergy_fifo_write_last_bytes (p_payload, p_fifo, dcd_synergy -> ux_dcd_synergy_base);
        }
        else
        {
            ux_dcd_synergy_fifo_write_software_copy_16bit (dcd_synergy, p_payload, p_fifo, fifo_sel);
        }
    }
}
#endif

/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO write - Software copy for USB hardwares with 16-bit FIFO
 *
 * @param[in]      dcd_synergy      Pointer to the DCD control block
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 * @param[in]      fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_dcd_synergy_fifo_write_software_copy_16bit (UX_DCD_SYNERGY *dcd_synergy,
                                                    UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                    VOID * p_fifo,
                                                    ULONG  fifo_sel)
{
    if(0 == ((UINT)p_payload -> payload_buffer % 2U))
    {
        /* Calculate FIFO access times. */
        p_payload -> transfer_times = (UINT)((p_payload -> payload_length) / (2U));
        p_payload -> transfer_width = 2U;
        p_payload -> payload_length = p_payload -> payload_length - (p_payload -> transfer_times * 2U);

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
            /* Write 16 bit value to FIFO. */
            *(volatile USHORT *) p_fifo = *(USHORT *)(p_payload -> payload_buffer);

            /* Update the payload buffer address. */
            p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(USHORT);

            --p_payload -> transfer_times;
        }

        ux_dcd_synergy_fifo_write_last_bytes (p_payload, p_fifo, dcd_synergy -> ux_dcd_synergy_base);
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

        while (0UL != p_payload -> payload_length)
        {
            /* Write 8 bit value to FIFO. */
            *(volatile UCHAR *) p_fifo = *(UCHAR *)(p_payload -> payload_buffer);

            /* Update the payload buffer address. */
            p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(UCHAR);

            /* And the remaining length. */
            p_payload -> payload_length = p_payload -> payload_length - (INT)sizeof(UCHAR);
        }
    }
}

/******************************************************************************************************************//**
 * @brief  USBX DCD FIFO write - Copy last bytes to FIFO by software if the rest bytes are less than FIFO access width
 *
 * @param[in,out]  p_payload        Pointer to a payload transfer structure
 * @param[in]      p_fifo           FIFO register address
 * @param[in]      usb_base         USB controller hardware base address
 **********************************************************************************************************************/
VOID ux_dcd_synergy_fifo_write_last_bytes (UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload,
                                                     VOID * p_fifo,
                                                     ULONG  usb_base)
{
#if defined(R_USBHS_BASE)
    /* USBHS controller needs address offset (+3) for 8-bit access to the FIFO. */
    if (usb_base == R_USBHS_BASE)
    {
        p_fifo =  (VOID *)((ULONG)p_fifo + 3UL);
    }
#else
    SSP_PARAMETER_NOT_USED(usb_base);
#endif

    while (0UL != p_payload -> payload_length)
    {
        /* Write data by byte to FIFO. */
        *(volatile UCHAR *)p_fifo = *(UCHAR *)p_payload->payload_buffer;

        /* Update the payload buffer address. */
        p_payload -> payload_buffer = p_payload -> payload_buffer + (INT)sizeof(UCHAR);

        p_fifo = (VOID *)((UCHAR *)p_fifo - (INT)sizeof(UCHAR));

        p_payload -> payload_length -= 1UL;
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
