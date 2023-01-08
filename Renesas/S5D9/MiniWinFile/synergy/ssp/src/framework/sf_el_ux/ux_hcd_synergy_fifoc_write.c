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

#if defined(R_USBHS_BASE)
static VOID ux_hcd_synergy_fifo_write_software_copy_32bit(UX_HCD_SYNERGY *hcd_synergy,
        ULONG payload_length, UCHAR *payload_buffer, VOID * fifo_addr, ULONG fifo_sel);
#endif

static VOID ux_hcd_synergy_fifo_write_software_copy_16bit(UX_HCD_SYNERGY *hcd_synergy,
        ULONG payload_length, UCHAR *payload_buffer, VOID * fifo_addr, ULONG fifo_sel);

static VOID ux_hcd_synergy_fifo_write_software_copy_8bit(UX_HCD_SYNERGY *hcd_synergy,
        ULONG payload_length, UCHAR *payload_buffer, VOID * fifo_addr, ULONG fifo_sel);

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_fifod_write                          PORTABLE C      */
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
/*    hcd_synergy                        Pointer to Synergy controller    */
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
 * @brief  This function writes a buffer to FIFOC.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to Synergy ED structure
 *
 * @retval UX_ERROR                        Unable to access FIFO successfully.
 * @retval UX_SYNERGY_HC_FIFO_WRITE_END    Writing at ends.
 * @retval UX_SYNERGY_HC_FIFO_WRITE_SHORT  Writing short data.
 * @retval UX_SYNERGY_HC_FIFO_WRITING      Doing multiple writes.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_fifoc_write(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed)
{
    UX_SYNERGY_TD * td;
    ULONG           fifo_access_status;
    ULONG           max_packet_size;
    ULONG           data_buffer_size;
    ULONG           payload_length;
    UINT            status;
    UCHAR         * payload_buffer;
    ULONG           synergy_register;
    VOID          * cfifo_ptr;
    ULONG           cfifo_sel;

    /* Check if we are using endpoint 0.  */
    if (ed -> ux_synergy_endpoint_index == 0UL)
    {
        /* Get the Fifo access status for endpoint 0.  */
        fifo_access_status =  ux_hcd_synergy_fifo_port_change(hcd_synergy, ed, UX_SYNERGY_HC_CFIFOSEL_ISEL);
    }
    else
    {
        /* Get the Fifo access status for non endpoint 0.  */
        fifo_access_status =  ux_hcd_synergy_fifo_port_change(hcd_synergy, ed, 0UL);
    }

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
        payload_length =  td -> ux_synergy_td_length;

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
            payload_length = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD;
        }
        else
#endif
        {
            /* Payload length is the buffer size.  */
            payload_length = data_buffer_size;
        }
    }      

    /* Get the payload buffer address.  */
    payload_buffer =  td -> ux_synergy_td_buffer;

    /*Initialize the CFIFO pointer*/
    cfifo_ptr = (VOID *)(hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_CFIFO);

    /* CFIFO port selection register offset */
    cfifo_sel = UX_SYNERGY_HC_CFIFOSEL;

    /* Use software copy for data transfer to CFIFO */
    ux_hcd_synergy_fifo_write_software_copy(hcd_synergy, payload_length, payload_buffer, cfifo_ptr, cfifo_sel);

    /* Check status. If we have a short packet, we need to set the BVAL flag  in the Fifo controller. */
    if (status != (UINT)UX_SYNERGY_HC_FIFO_WRITING)
    {
        /* Read the current FIFO control register.  */
        synergy_register = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR);

        /* Check if the BVAL bit is already set.  */
        if ((synergy_register & UX_SYNERGY_HC_FIFOCTR_BVAL) == 0UL)
        {
            /* No so set it.  This will enable the Buffer Memory Valid flag.
               This bit is set to 1 when data has been written to the FIFO and
               this is a short packet or zero packet or a full packet but not the
               end of the transmission.  */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR, UX_SYNERGY_HC_FIFOCTR_BVAL);
        }
    }

    /* Return status about buffer transfer.  */
    return (UINT)status;
}


/******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO write by software copy.  Call a suitable subroutine for selected USB controller hardware.
 *
 * @param[in]      hcd_synergy      Pointer to the HCD control block
 * @param[in]      payload_length   Payload length
 * @param[in]      payload_buffer   Payload buffer address
 * @param[in]      fifo_addr        FIFO register address
 * @param[in]      fifo_sel         FIFO select register
 **********************************************************************************************************************/
VOID ux_hcd_synergy_fifo_write_software_copy(UX_HCD_SYNERGY *hcd_synergy,
                                                        ULONG payload_length,
                                                        UCHAR *payload_buffer,
                                                        VOID * fifo_addr,
                                                        ULONG  fifo_sel)
{
#if defined(R_USBHS_BASE)
    if (hcd_synergy -> ux_hcd_synergy_base == R_USBHS_BASE)
    {
        /* 32-bit software copy */
        ux_hcd_synergy_fifo_write_software_copy_32bit(hcd_synergy, payload_length, payload_buffer, fifo_addr, fifo_sel);
    }
    else
#endif
    {
        /* 16-bit software copy */
        ux_hcd_synergy_fifo_write_software_copy_16bit(hcd_synergy, payload_length, payload_buffer, fifo_addr, fifo_sel);
    }
}

#if defined(R_USBHS_BASE)
/******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO write - Software copy with 32-bit FIFO access
 *
 * @param[in]          hcd_synergy      Pointer to the HCD control block
 * @param[in,out]      payload_length   Payload length
 * @param[in,out]      payload_buffer   Payload buffer address
 * @param[in]          fifo_addr        FIFO register address
 * @param[in]          fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_write_software_copy_32bit(UX_HCD_SYNERGY *hcd_synergy,
                                                            ULONG payload_length,
                                                            UCHAR *payload_buffer,
                                                            VOID * fifo_addr,
                                                            ULONG  fifo_sel)
{
    /* Check payload buffer alignment. */
    if(((UINT)payload_buffer % 4U) == 0)
    {
        UINT fifo_access_times;

        /* Calculate FIFO access times. */
        fifo_access_times = (UINT)(payload_length / 4UL);

        /* Calculate bytes to be remained in FIFO. */
        payload_length    = payload_length - ((ULONG)fifo_access_times * 4UL);

        /* Set FIFO access width to 32-bit. */
        ux_hcd_synergy_register_clear(hcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_HC_CFIFOSEL_MBW_MASK);
        ux_hcd_synergy_register_set(hcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_HC_CFIFOSEL_MBW_32);

        while (fifo_access_times != 0U)
        {
            /* Write 32 bit value to FIFO. */
            *(volatile ULONG *) fifo_addr =  *((ULONG *) payload_buffer);

            /* Update the payload buffer address. */
            payload_buffer = payload_buffer + sizeof(ULONG);

            --fifo_access_times;
        }

        /* Send remaining bytes after word access */
        if(payload_length != 0UL)
        {
            ux_hcd_synergy_fifo_write_software_copy_remaining_bytes(hcd_synergy, payload_length, payload_buffer,
                                                                    fifo_addr);
        }
    }
    else
    {
        /* 16-bit software copy */
        ux_hcd_synergy_fifo_write_software_copy_16bit(hcd_synergy, payload_length, payload_buffer, fifo_addr, fifo_sel);
    }
}
#endif

/******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO write - Software copy with 16-bit FIFO access
 *
 * @param[in]          hcd_synergy      Pointer to the HCD control block
 * @param[in,out]      payload_length   Payload length
 * @param[in,out]      payload_buffer   Payload buffer address
 * @param[in,out]      fifo_addr        FIFO register address
 * @param[in]          fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_write_software_copy_16bit(UX_HCD_SYNERGY *hcd_synergy,
                                                            ULONG payload_length,
                                                            UCHAR *payload_buffer,
                                                            VOID * fifo_addr,
                                                            ULONG  fifo_sel)
{
    /* Check payload buffer alignment. */
    if(((UINT)payload_buffer % 2U) == 0)
    {
        UINT fifo_access_times;

        /* Calculate FIFO access times. */
        fifo_access_times = (UINT)(payload_length / 2UL);
        payload_length    = payload_length - ((ULONG)fifo_access_times * 2UL);

        /* Set FIFO access width to 16-bit. */
        ux_hcd_synergy_register_clear(hcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_HC_CFIFOSEL_MBW_MASK);
        ux_hcd_synergy_register_set(hcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_HC_CFIFOSEL_MBW_16);

#if defined(R_USBHS_BASE)
        /* This needs for 16-bit write for USBHS. */
        if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
        {
            fifo_addr = (VOID *) ((ULONG)fifo_addr + 2UL);
        }
#endif

        while (fifo_access_times != 0U)
        {
            /* Write 16 bit value to FIFO. */
            *(volatile USHORT *) fifo_addr =  *(USHORT *)payload_buffer;

            /* Update the payload buffer address  */
            payload_buffer = payload_buffer + sizeof(USHORT);

            --fifo_access_times;
        }

        /* Write remaining bytes. */
        if(payload_length != 0UL)
        {
#if defined(R_USBHS_BASE)
        if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
        {
            /* Reset fifo address since byte address offset is taken care in below api */
            fifo_addr = (VOID *) ((ULONG)fifo_addr - 2UL);
        }
#endif
            ux_hcd_synergy_fifo_write_software_copy_remaining_bytes(hcd_synergy, payload_length, payload_buffer,
                                                                    fifo_addr);
        }
    }
    else
    {
        /* 8-bit software copy */
        ux_hcd_synergy_fifo_write_software_copy_8bit(hcd_synergy, payload_length, payload_buffer, fifo_addr, fifo_sel);
    }
}

/******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO write - Software copy with 8-bit FIFO access
 *
 * @param[in]          hcd_synergy      Pointer to the HCD control block
 * @param[in,out]      payload_length   Payload length
 * @param[in,out]      payload_buffer   Payload buffer address
 * @param[in,out]      fifo_addr        FIFO register address
 * @param[in]          fifo_sel         FIFO select register
 **********************************************************************************************************************/
static VOID ux_hcd_synergy_fifo_write_software_copy_8bit(UX_HCD_SYNERGY *hcd_synergy,
                                                            ULONG payload_length,
                                                            UCHAR *payload_buffer,
                                                            VOID * fifo_addr,
                                                            ULONG  fifo_sel)
{
    /* Set FIFO access width to 8-bit. */
    ux_hcd_synergy_register_clear(hcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_HC_CFIFOSEL_MBW_MASK);
    ux_hcd_synergy_register_set(hcd_synergy, fifo_sel, (USHORT)UX_SYNERGY_HC_CFIFOSEL_MBW_8);

#if defined(R_USBHS_BASE)
    /* This needs for 8-bit write for USBHS. */
    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        fifo_addr =  (VOID *) ((ULONG)fifo_addr + 3UL);
    }
#endif

    while (payload_length != 0UL)
    {
        /* Write 8 bit value to FIFO. */
        *(volatile UCHAR *) fifo_addr = *((UCHAR *)payload_buffer);

        /* Update the payload buffer address.  */
        payload_buffer = payload_buffer + sizeof(UCHAR);

        /* And the remaining length.  */
        payload_length = payload_length - sizeof(UCHAR);
    }
}

/******************************************************************************************************************//**
 * @brief  USBX HCD CPU FIFO write - Copy remaining bytes to FIFO by software if the rest bytes are less
 *                                   than FIFO access width
 *
 * @param[in]          hcd_synergy      Pointer to the HCD control block
 * @param[in,out]      payload_length   Payload length
 * @param[in,out]      payload_buffer   Payload buffer address
 * @param[in,out]      fifo_addr        FIFO register address
 **********************************************************************************************************************/
VOID ux_hcd_synergy_fifo_write_software_copy_remaining_bytes(UX_HCD_SYNERGY *hcd_synergy,
                                                                    ULONG payload_length,
                                                                    UCHAR *payload_buffer,
                                                                    VOID * fifo_addr)
{
    /* Rest of bytes are transfered with 8-bit width. */

#if defined(R_USBHS_BASE)
    /* This needs for 8-bit write for USBHS. */
    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        fifo_addr =  (VOID *) ((ULONG)fifo_addr + 3UL);
    }
#else
    {
        SSP_PARAMETER_NOT_USED(hcd_synergy);
    }
#endif

    while (payload_length != 0UL)
    {
        /* Write 8 bit value to FIFO. */
        *(volatile UCHAR *) fifo_addr =  *payload_buffer;

        /* Update the payload buffer address.  */
        payload_buffer += sizeof(UCHAR);

        /* And the remaining length.  */
        payload_length -= sizeof(UCHAR);

        /* Update the FIFO address. */
        fifo_addr = (VOID *)((UINT)fifo_addr - 1);
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
