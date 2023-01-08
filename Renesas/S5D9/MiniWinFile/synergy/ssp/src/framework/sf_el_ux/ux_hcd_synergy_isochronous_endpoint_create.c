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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "ux_api.h"
#include "ux_hcd_synergy.h"

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static UINT ux_hcd_synergy_isochronous_endpoint_available_pipe_get (UX_HCD_SYNERGY * hcd_synergy,
                                                                      ULONG * pipe_index);

static ULONG ux_hcd_synergy_isochronous_endpoint_fifo_size_get (UX_HCD_SYNERGY *hcd_synergy);

static UINT ux_hcd_synergy_isochronous_endpoint_max_packet_size_check (UX_HCD_SYNERGY *hcd_synergy,
                                                                       ULONG max_packet_size,
                                                                       ULONG pipe_index);

static void ux_hcd_synergy_isochronous_endpoint_create_pipe_config (UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed);

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @brief  This function creates an isochronous endpoint.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  endpoint    : Pointer to an Endpoint control block
 *
 * @retval UX_SUCCESS            Isochronous endpoint is created successfully.
 * @retval UX_NO_ED_AVAILABLE    Failed to obtain an ED terminating the ED transfer chain.
 * @retval UX_NO_TD_AVAILABLE    Failed to obtain a TD for new endpoint.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_isochronous_endpoint_create(UX_HCD_SYNERGY * hcd_synergy, UX_ENDPOINT * endpoint)
{
    UINT                status;
    UX_SYNERGY_ED     * ed;
    UX_SYNERGY_ED     * head_ed;
    UX_SYNERGY_ISO_TD * td;
    ULONG               pipe_index = 0UL;

    TX_INTERRUPT_SAVE_AREA

    status = ux_hcd_synergy_isochronous_endpoint_available_pipe_get (hcd_synergy, &pipe_index);
    if (UX_SUCCESS != status)
    {
        return status;
    }

    status = ux_hcd_synergy_isochronous_endpoint_max_packet_size_check (hcd_synergy,
                                    endpoint -> ux_endpoint_descriptor.wMaxPacketSize, pipe_index);
    if (UX_SUCCESS != status)
    {
        return status;
    }

    /* Obtain a ED for this new endpoint. This ED will live as long as the endpoint is
       active and will be the container for the TDs.  */
    ed =  ux_hcd_synergy_ed_obtain(hcd_synergy);
    if (ed == UX_NULL)
    {
        return (UINT)UX_NO_ED_AVAILABLE;
    }

    /* Configure the  endpoint  hardware, pick up buffer size & number. */
    ed -> ux_synergy_buffer_size   = (ULONG)UX_SYNERGY_MAX_ISO_PAYLOAD / (ULONG)UX_SYNERGY_HC_MAX_BUF_SIZE;
    ed -> ux_synergy_buffer_number = (ULONG)UX_SYNERGY_HC_PIPE1_BUF_START_NUM +
            ((pipe_index - 1UL) * (ed -> ux_synergy_buffer_size) * 2);

    /* Obtain a dummy isochronous TD for terminating the ED transfer chain.  */
    td =  ux_hcd_synergy_isochronous_td_obtain(hcd_synergy);
    if (UX_NULL == td)
    {
        /* No more TD was available.  */
        ed -> ux_synergy_ed_status = (ULONG)UX_UNUSED;
        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Store the pipe index.  */
    ed -> ux_synergy_pipe_index = pipe_index;

    /* We need to take into account the nature of the HCD to define the max size
       of any transfer in the transfer request.  */
    endpoint -> ux_endpoint_transfer_request.ux_transfer_request_maximum_length
                = ux_hcd_synergy_isochronous_endpoint_fifo_size_get(hcd_synergy);

    /* Attach the ED to the endpoint container.  */
    endpoint -> ux_endpoint_ed =  (VOID *) ed;

    /* Now do the opposite, attach the ED container to the physical ED.  */
    ed -> ux_synergy_ed_endpoint =  endpoint;

    /* Hook the TD to both the tail and head of the ED.  */
    ed -> ux_synergy_ed_tail_td =  (UX_SYNERGY_TD *) ((void *) td);
    ed -> ux_synergy_ed_head_td =  (UX_SYNERGY_TD *) ((void *) td);

    /* Attach this ED to the iso list.  */
    head_ed =  hcd_synergy -> ux_hcd_synergy_iso_head_ed;
    ed -> ux_synergy_ed_next_ed =  head_ed;
    hcd_synergy -> ux_hcd_synergy_iso_head_ed =  ed;

    /* Build the back chaining pointer. The previous head ED needs to know about the inserted ED. */
    if (head_ed != UX_NULL)
    {
        head_ed -> ux_synergy_ed_previous_ed =  ed;
    }

    /* Set PID to NAK. */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
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

    /* Configure a PIPE of USB controller.  */
    ux_hcd_synergy_isochronous_endpoint_create_pipe_config (hcd_synergy, ed);

    /* Memorise the endpoint in the HCD structure. */
    hcd_synergy -> ux_hcd_synergy_ed_ptr[ed -> ux_synergy_pipe_index] = ed;

    /* Enable the auto FIFO buffer clear mode. */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_D1FIFOSEL, (USHORT)UX_SYNERGY_HC_DFIFOSEL_DCLRM);

    /* Free the INTs now.  */
    TX_RESTORE

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private Functions
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_isochronous_endpoint_create() to get the number of available PIPE
 *  for an isochronous endpoint.
 *
 * @param[in]      hcd_synergy : Pointer to a HCD control block
 * @param[out]     pipe_index  : Memory to return the PIPE index. Index would be 1 or 2 for the isochronous transfer.
 *
 * @retval UX_SUCCESS            PIPE was available for new isochronous endpoint.
 * @retval UX_ERROR              No more PIPE was available for new isochronous endpoint.
 **********************************************************************************************************************/
static UINT ux_hcd_synergy_isochronous_endpoint_available_pipe_get (UX_HCD_SYNERGY * hcd_synergy,
                                                                      ULONG * pipe_index)
{
    UINT    status = UX_SUCCESS;
    ULONG   pipe_type;
    ULONG   curr_pipe_index = 1UL;

    /* Obtain the first available pipe. */
    while (curr_pipe_index <= 2UL)
    {
        /* Select pipe 1 or 2.  */
        ux_hcd_synergy_register_write( hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)curr_pipe_index);

        /* Check whether pipe is in use.  */
        pipe_type =  ( (UX_SYNERGY_HC_PIPECFG_TYPE_MASK &
                        ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_PIPECFG)) >> 14 );

        /* Not in use, choose this one.  */
        if (pipe_type == 0UL)
        {
            break;
        }

        /* Increment the current index.  */
        curr_pipe_index++;
    }

    /* Check if we found an available pipe for isochronous endpoint.  */
    if (curr_pipe_index > 2UL)
    {
        status = (UINT)UX_ERROR;
    }

    *pipe_index = curr_pipe_index;

    return status;
}

/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_isochronous_endpoint_create() to get the size of USB controller
 *  FIFO for an isochronous endpoint.
 *
 * @param[in]      hcd_synergy : Pointer to a HCD control block
 *
 * @retval fifo_size             Maximum size of USB controller FIFO for an isochronous endpoint.
 **********************************************************************************************************************/
static ULONG ux_hcd_synergy_isochronous_endpoint_fifo_size_get (UX_HCD_SYNERGY *hcd_synergy)
{
    ULONG   fifo_size = 0UL;

    /* Get the maximum packet size for the pipe supported by the USB controller.  */
    if (R_USBFS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        /* USBFS has fixed size FIFO for isochronous PIPEs.  */
        fifo_size = UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE1_to_2_FS;
    }
#if defined(R_USBHS_BASE)
    else
    {
        /* USBHS has configurable size of FIFO for isochronous PIPEs.  */
        fifo_size = UX_SYNERGY_MAX_ISO_PAYLOAD;
    }
#endif

    return fifo_size;
}

/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_isochronous_endpoint_create() to check the max packet size
 *  (wMaxPacketSize) of the isochronous endpoint on a USB device connected to the USB controller. wMaxPacketSize needs
 *  to be smaller than or equal to the max packet size of PIPE on the USB controller.
 *
 * @param[in]      hcd_synergy     : Pointer to a HCD control block
 * @param[in]      max_packet_size : wMaxPackeSize value of the isochronous endpoint on a USB device
 * @param[in]      pipe_index      : PIPE index obtained by ux_hcd_synergy_isochronous_endpoint_available_pipe_get()
 *
 * @retval UX_SUCCESS        wMaxPacketSize of USB device is smaller than or equal to the max packet size of PIPE.
 * @retval UX_ERROR          wMaxPacketSize is larger than PIPE max packet size, or FIFO size was not enough.
 **********************************************************************************************************************/
static UINT ux_hcd_synergy_isochronous_endpoint_max_packet_size_check (UX_HCD_SYNERGY *hcd_synergy,
                                                                       ULONG max_packet_size,
                                                                       ULONG pipe_index)
{
    UINT    status = UX_SUCCESS;
    ULONG   max_packet_size_pipe = 0UL;
    ULONG   fifo_size;

    fifo_size = ux_hcd_synergy_isochronous_endpoint_fifo_size_get(hcd_synergy);

    /* Get the maximum packet size for the pipe supported by the USB controller.  */
    if (R_USBFS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        max_packet_size_pipe = UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE1_to_2_FS;
    }
#if defined(R_USBHS_BASE)
    else
    {
        max_packet_size_pipe = UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE1_to_2_HS;
    }

    /* Check the buffer not exceeding the total FIFO size. */
    if (((ULONG)UX_SYNERGY_HC_PIPE1_BUF_START_NUM +
         ((pipe_index - 1UL) * (fifo_size / (ULONG)UX_SYNERGY_HC_BUF_BLOCK_SIZE)))
         > (ULONG)UX_SYNERGY_HC_MAX_BUF_NUM)
    {
        /* Buffer was not allocated in the FIFO of USB controller. */
        status = (UINT)UX_ERROR;
    }
#else
    SSP_PARAMETER_NOT_USED(pipe_index);
    SSP_PARAMETER_NOT_USED(fifo_size);
#endif

    /* Check if wMaxPacketSize of USB device is not larger than the maximum payload size available
     * on the selected PIPE of USB controller.
     */
    if (max_packet_size_pipe < max_packet_size)
    {
        status = (UINT)UX_ERROR;
    }

    return status;
}

/*******************************************************************************************************************//**
 * @brief  This is the subroutine of ux_hcd_synergy_isochronous_endpoint_create() to configure the PIPE hardware of USB
 *  controller for an isochrnous endpoint.
 *
 * @param[in]      hcd_synergy     : Pointer to a HCD control block
 * @param[in]      ed              : Pointer to an Endpoint Descriptor for Synergy
 **********************************************************************************************************************/
static void ux_hcd_synergy_isochronous_endpoint_create_pipe_config (UX_HCD_SYNERGY * hcd_synergy, UX_SYNERGY_ED * ed)
{
    UX_ENDPOINT   * endpoint = ed -> ux_synergy_ed_endpoint;
    ULONG           pipe_number = ed->ux_synergy_pipe_index - 1UL;
    ULONG           endpoint_number;
    ULONG           endpoint_direction;
    ULONG           device_address;
    ULONG           max_packet_size;

    /* Get the endpoint number of connected USB device.  */
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

    /* Set Pipe configuration registers. */
#if defined(R_USBHS_BASE)
    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        /* Enable double buffer for Read Pipe (IN)*/
        if (0 == endpoint_direction)
        {
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPECFG,
                                            (USHORT)(UX_SYNERGY_HC_PIPECFG_TYPE_ISOCHRONOUS |
                                                     UX_SYNERGY_HC_PIPECFG_SHTNAK |
                                                     endpoint_direction |
                                                     endpoint_number |
                                                     UX_SYNERGY_HC_PIPECFG_DBLB));
        }
        else
        {
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPECFG,
                                            (USHORT)(UX_SYNERGY_HC_PIPECFG_TYPE_ISOCHRONOUS |
                                                     UX_SYNERGY_HC_PIPECFG_SHTNAK |
                                                     endpoint_direction |
                                                     endpoint_number));
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
                                       (USHORT)(UX_SYNERGY_HC_PIPECFG_TYPE_ISOCHRONOUS |
                                                UX_SYNERGY_HC_PIPECFG_SHTNAK |
                                                endpoint_direction |
                                                endpoint_number));
    }

    /* Get the device address. It needs to be stored in the PIPEMAXP register.  */
    device_address = endpoint -> ux_endpoint_device -> ux_device_address << UX_SYNERGY_HC_PIPEMAXP_DEVSEL_SHIFT;

    /* Get the max packet size for this endpoint.  */
    max_packet_size = endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* Initialize the PIPEMAX register.  */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPEMAXP, (USHORT)(device_address | max_packet_size));

#if defined(R_USBHS_BASE)
    /* Initialize the Transaction Counter and Transaction Counter Enable Register */
    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        /* Only a IN PIPE needs to enable Transaction Counter. */
        if (0 == endpoint_direction)
        {
            /* Disable and clear Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy,
                                          UX_SYNERGY_HC_PIPE1TRE + (ULONG)(pipe_number * 4UL), (USHORT)0U);

            /* Set default value (1) to Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy,
                                          UX_SYNERGY_HC_PIPE1TRN + (ULONG)(pipe_number * 4UL), (USHORT)1U);

            /* Enable Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy,
                                          UX_SYNERGY_HC_PIPE1TRE + (ULONG)(pipe_number * 4UL),
                                          (USHORT)UX_SYNERGY_HC_PIPETRE_TRENB);
        }
        else
        {
            /* Disable Transaction Counter. */
            ux_hcd_synergy_register_write(hcd_synergy,
                                          UX_SYNERGY_HC_PIPE1TRE + (ULONG)(pipe_number * 4UL), (USHORT)0U);
        }
    }
#endif

    /* Configure Interval Counter. Set the interval specified by a USB device. */
    ux_hcd_synergy_register_write(hcd_synergy,
                                  UX_SYNERGY_HC_PIPEPERI + (ULONG)(pipe_number * 4UL),
                                  (USHORT)(ed ->ux_synergy_ed_endpoint->ux_endpoint_descriptor.bInterval - 1));
 
    /* Enable the automatic buffer flush function for an Isochronous IN PIPE. */
    ux_hcd_synergy_register_set(hcd_synergy,
                                UX_SYNERGY_HC_PIPEPERI + (ULONG)(pipe_number * 4UL),
                                (USHORT)(1UL << 12));

    /* Save the kind of FIFO to be used for this PIPE. */
    if (0UL != endpoint_direction)
    {
        if (hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx != NULL)
        {
            /* Use D0FIFO for an OUT PIPE if DMA engine enabled. */
            ed -> ux_synergy_fifo_index = (ULONG)UX_SYNERGY_HC_FIFO_D0;
        }
        else
        {
            /* Use CFIFO for an OUT PIPE if DMA engine disabled. */
            ed -> ux_synergy_fifo_index = (ULONG)UX_SYNERGY_HC_FIFO_C;
        }
    }
    else
    {
        if (hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx != NULL)
        {
            /* Use D1FIFO for an IN PIPE if DMA engine enabled. */
            ed -> ux_synergy_fifo_index = (ULONG)UX_SYNERGY_HC_FIFO_D1;
        }
        else
        {
            /* Use CFIFO for an IN PIPE if DMA engine disabled. */
            ed -> ux_synergy_fifo_index = (ULONG)UX_SYNERGY_HC_FIFO_C;
        }
    }
}

