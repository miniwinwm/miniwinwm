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
/**   Synergy Controller Driver                                           */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define UX_SOURCE_CODE


/* Include necessary system files.  */

#include "ux_api.h"
#include "ux_dcd_synergy.h"
#include "ux_device_stack.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    ux_dcd_synergy_transfer_abort                         PORTABLE C    */
/*                                                             5.6        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will terminate a transfer.                            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_synergy                           Pointer to device controller  */
/*    transfer_request                      Pointer to transfer request   */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    success                                                             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    ux_dcd_synergy_register_write       Write register                  */
/*    ux_dcd_synergy_register_clear       clear register                  */
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
 * @brief  This function will terminate the transfer.
 *
 * @param[in]  dcd_synergy       : Pointer to a DCD control block
 * @param[in]  transfer_request  : Pointer to transfer request
 *
 * @retval UX_SUCCESS              Transfer Abort is initiated successfully.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_transfer_abort(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_TRANSFER *transfer_request)
{

    UX_DCD_SYNERGY_ED            *ed;
    UX_SLAVE_ENDPOINT       *endpoint;
    ULONG   synergy_register;

    /* Get the pointer to the logical endpoint from the transfer request.  */
    endpoint =  transfer_request -> ux_slave_transfer_request_endpoint;

    /* Keep the physical endpoint address in the endpoint container.  */
    ed =  (UX_DCD_SYNERGY_ED *) endpoint -> ux_slave_endpoint_ed;

    /* Set PIPEx FIFO in in status. */
    ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_PIPESEL, (USHORT) ed -> ux_dcd_synergy_ed_index);

    /* Check the type of endpoint.  */
    if (ed -> ux_dcd_synergy_ed_index != 0UL)
    {
        /* Set NAK.  */
        ux_dcd_synergy_endpoint_nak_set(dcd_synergy, ed);

        /** Set the ACLRM bit to 1 and then to 0 for clearing FIFO buffers. */
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_PIPECTR_ACLRM);
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR + ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_PIPECTR_ACLRM);

        /** Clear the FIFO buffer memory. */
        synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR);
        while( !((ULONG)UX_SYNERGY_DCD_FIFOCTR_FRDY == (ULONG)(synergy_register & (ULONG)UX_SYNERGY_DCD_FIFOCTR_FRDY)) && (UX_WAIT_FOREVER != (UINT)transfer_request->ux_slave_transfer_request_timeout) )
        {
            synergy_register =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR);
        }
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);

#if !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
#endif
        /* Set the current fifo port.  */
        ux_dcd_synergy_current_endpoint_change(dcd_synergy, ed, 0);

        /* Disable the Ready interrupt.  */
        ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);

        /* Disable the Buffer empty interrupt.  */
        ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);

        /* Disable the Buffer Not Ready interrupt.  */
        ux_dcd_synergy_buffer_notready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
        /* Clear the enabled interrupts.  */
        ux_dcd_synergy_usb_status_register_clear (dcd_synergy, UX_SYNERGY_DCD_BEMPSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));
        ux_dcd_synergy_usb_status_register_clear (dcd_synergy, UX_SYNERGY_DCD_BRDYSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));
        ux_dcd_synergy_usb_status_register_clear (dcd_synergy, UX_SYNERGY_DCD_NRDYSTS, (USHORT)(1UL << ed -> ux_dcd_synergy_ed_index));

#if !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
        /* Using semaphore per pipe - finally make the pending pipe to reset
           Wake up the device driver who is waiting on a semaphore.  */
        if(UX_WAIT_FOREVER == (UINT)transfer_request->ux_slave_transfer_request_timeout )
        {
            _ux_utility_semaphore_put (&ed->ux_dcd_synergy_ep_slave_transfer_request_semaphore);
        }
        if( (UX_TRANSFER_STATUS_PENDING == (INT)transfer_request -> ux_slave_transfer_request_status ) &&
                (UX_TRANSFER_PHASE_DATA_OUT == (INT)transfer_request->ux_slave_transfer_request_phase) &&
                (UX_NULL != dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx ) )
        {
            _ux_utility_semaphore_put(&dcd_synergy->dma_tx_completion_semaphore);
        }
#endif
    }

    /* This function never fails.  */
    return(UX_SUCCESS);
}
 /*******************************************************************************************************************//**
  * @} (end addtogroup sf_el_ux)
  **********************************************************************************************************************/
