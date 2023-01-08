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

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    ux_dcd_synergy_endpoint_reset                         PORTABLE C    */
/*                                                             5.6        */
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will reset a physical endpoint.                       */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_synergy                         Pointer to device controller    */
/*    endpoint                            Pointer to endpoint container   */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */ 
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_dcd_synergy_register_read        Read register                   */
/*    ux_dcd_synergy_register_write       Write register                  */
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
 * @brief  This function will reset a physical endpoint.
 *
 * @param[in]  dcd_synergy     Pointer to a DCD control block
 * @param[in]  endpoint        Pointer to a Device Controller Endpoint structure.
 *
 * @retval UX_SUCCESS          Endpoint is reset successfully.
 * @retval UX_NO_ED_AVAILABLE  Device Controller Endpoint structure pointer is NULL
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_endpoint_reset(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_ENDPOINT *endpoint)
{
    UX_DCD_SYNERGY_ED   * ed;
    ULONG fifo_register_content;
    UX_SLAVE_TRANSFER  * p_slave_transfer;

    p_slave_transfer = &endpoint->ux_slave_endpoint_transfer_request;

    if(endpoint == UX_NULL)
    {
        return (UINT) UX_NO_ED_AVAILABLE;
    }

    /* Get the physical endpoint address in the endpoint container.  */
    ed =  (UX_DCD_SYNERGY_ED *) endpoint -> ux_slave_endpoint_ed;

    /* Reset PID on this endpoint.  */
    switch (ed -> ux_dcd_synergy_ed_index)
    {
        case 0UL :
            /* Set NAK in DCPCTR register. This will reset the STALL condition.  */
            ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_DCPCTR, UX_SYNERGY_DCD_DCPCTR_PID_MASK);

            /* Set SQCLR in PIPExCTR register. This will reset data toggle.  */
            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_DCPCTR, UX_SYNERGY_DCD_DCPCTR_SQCLR);

            /* Select the control pipe and */
            ux_dcd_synergy_register_write (dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL, UX_SYNERGY_DCD_CFIFOSEL_CURPIPE_MASK);

            /* Make BCLR = 1 in CFIFOCTR register and this resets the control FIFO from CPU side */
            ux_dcd_synergy_register_set (dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);

            break;        
        
        default : 
            /* Set NAK in PIPExCTR register. This will reset the STALL condition.  */
            ux_dcd_synergy_register_clear(dcd_synergy,
                                          UX_SYNERGY_DCD_PIPE1CTR +((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL),
                                          UX_SYNERGY_DCD_DCPCTR_PID_MASK);
            
            /* Set SQCLR in PIPExCTR register. This will reset data toggle.  */
            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PIPE1CTR +
                                          ((ed -> ux_dcd_synergy_ed_index - 1UL) * 2UL), UX_SYNERGY_DCD_DCPCTR_SQCLR);

            /* If this pipe is using D0FIFO, Clear the D0FIFO buffer memory from CPU side */
            fifo_register_content = ux_dcd_synergy_register_read(dcd_synergy, (ULONG)UX_SYNERGY_DCD_D0FIFOSEL);
            if ((fifo_register_content & 0x0FUL) == ed -> ux_dcd_synergy_ed_index)
            {
                /* Make BCLR = 1 in D0FIFOCTR register and this resets the D0FIFO from CPU side */
                ux_dcd_synergy_register_set (dcd_synergy, UX_SYNERGY_DCD_D0FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            }

            /* If not, check for D1FIFO or CFIFO */
             else
             {
            	 fifo_register_content = ux_dcd_synergy_register_read(dcd_synergy, (ULONG)UX_SYNERGY_DCD_D1FIFOSEL);
            	 /* If using D1FIFO */
            	 if ((fifo_register_content & 0x0FUL) == ed -> ux_dcd_synergy_ed_index)
            	 {
            		 /* Make BCLR = 1 in D1FIFOCTR register and this resets the D1FIFO from CPU side */
            		 ux_dcd_synergy_register_set (dcd_synergy, UX_SYNERGY_DCD_D1FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            	 }
            	 /* else, this is CFIFO */
            	 else
            	 {
            		 /* Select the required pipe and */
            		 /* Read the CFIFOSEL register content */
            		 fifo_register_content = ux_dcd_synergy_register_read (dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL);
            		 /* Clear the pipe number field */
            		 fifo_register_content = fifo_register_content & 0xFFF0UL;
            		 /* Modify pipe number field with required pipe number */
            		 fifo_register_content = fifo_register_content | ed -> ux_dcd_synergy_ed_index;
            		 /* Update the CFIFOSEL register so correct pipe is addressed  */
            		 ux_dcd_synergy_register_write (dcd_synergy, UX_SYNERGY_DCD_CFIFOSEL,(USHORT)(fifo_register_content));
            		 /*Make BCLR = 1 in CFIFOCTR register and this resets the CFIFO for the selected pipe from CPU side */
            		 ux_dcd_synergy_register_set (dcd_synergy, UX_SYNERGY_DCD_CFIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
            	 }
             }

            /** Abort the transfer request on this endpoint. */
            if ((UX_DCD_SYNERGY_CDC_CONTROL_INTERFACE ==
            		(INT)endpoint->ux_slave_endpoint_device->ux_slave_device_descriptor.bDeviceClass) &&
                    (UX_TRANSFER_STATUS_PENDING == (INT)p_slave_transfer->ux_slave_transfer_request_status))
            {
                _ux_device_stack_transfer_abort(p_slave_transfer, p_slave_transfer->ux_slave_transfer_request_completion_code);
            }
            break;        
    }

    /* Set the state of the endpoint to not stalled.  */
    ed -> ux_dcd_synergy_ed_status &=  ~UX_DCD_SYNERGY_ED_STATUS_STALLED;

    /* This function never fails.  */
    return (UX_SUCCESS);
}


/*******************************************************************************************************************//**
 * @brief  This function is called when the device wants to wake up the host.
 *
 * @param[in]  dcd_synergy     Pointer to a DCD control block
 * @param[in]  parameter       Pointer to a remote wakeup parameter.
 *
 * @retval UX_SUCCESS          Remote wakeup signaled to the USB HOST successfully.
 * @retval UX_ERROR            Remote wakeup signal failed from DEVICE to the USB HOST.
 **********************************************************************************************************************/
UINT ux_dcd_synergy_remote_wakeup (UX_DCD_SYNERGY *dcd_synergy,  ULONG *parameter)
{
    ULONG   synergy_interrupt;

    SSP_PARAMETER_NOT_USED(parameter);

    /* Read the interrupt status register from the controller.  */
    synergy_interrupt =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0);
    synergy_interrupt &= (ULONG)UX_SYNERGY_DCD_INTSTS0_DVSQ_MASK;

    /* Check the DVSQ state. */
    if (UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_CONFIGURED == synergy_interrupt)
    {
        _ux_utility_delay_ms(5U);
        /* Signal remote wakeup to the HOST.  */
        ux_dcd_synergy_register_set (dcd_synergy, UX_SYNERGY_DCD_DVSTCTR, UX_SYNERGY_DCD_DVSTCTR_WKUP);
        return ((UINT)UX_SUCCESS);
    }
    else
    {
        return ((UINT)UX_ERROR);
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

