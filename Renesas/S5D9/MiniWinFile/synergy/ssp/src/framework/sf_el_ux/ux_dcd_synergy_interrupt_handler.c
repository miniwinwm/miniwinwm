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
#include "ux_system.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    ux_dcd_synergy_interrupt_handler                      PORTABLE C    */
/*                                                             5.6        */
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is the interrupt handler for the synergy controller.  */
/*    The controller will trigger an interrupt when something happens on  */
/*    an endpoint whose mask has been set in the interrupt enable         */
/*    register.                                                           */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_dcd_synergy_initialize_complete      Complete initialization     */
/*    ux_dcd_synergy_register_read            Read register               */
/*    ux_dcd_synergy_register_write           Write register              */
/*    ux_dcd_synergy_transfer_callback        Process callback            */
/*    ux_device_stack_disconnect             Disconnect device            */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    USBX Device Stack                                                   */ 
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
 * @brief  This function is the interrupt handler for the synergy controller.
 *
 *         The controller will trigger an interrupt when something happens on
 *         an endpoint whose mask has been set in the interrupt enable register.
 * 
  *********************************************************************************************************************/
VOID  ux_dcd_synergy_interrupt_handler(VOID)
{
    ULONG                   synergy_interrupt;
    UX_SLAVE_TRANSFER     * transfer_request;
    UX_DCD_SYNERGY_ED     * ed;
    UX_SLAVE_ENDPOINT     * endpoint;
    UX_SLAVE_DCD          * dcd;
    UX_DCD_SYNERGY        * dcd_synergy;
    UX_SLAVE_DEVICE       * device;
    ULONG                   synergy_register1;
    ULONG                   synergy_register2;
    ULONG                   synergy_register3;
    ULONG                   synergy_dvstctr;
    ULONG                   bempsts;
    ULONG                   nrdysts;
    ULONG                   brdysts;
    ULONG                   bempenb;
    ULONG                   nrdyenb;
    ULONG                   brdyenb;
    ULONG                   bemp_bit;
    ULONG                   nrdy_bit;
    ULONG                   brdy_bit;
    ULONG                   pipe_count;

    /** Get the pointer to the DCD.  */
    dcd =  &_ux_system_slave -> ux_system_slave_dcd;

    /** Get the pointer to the synergy DCD.  */
    dcd_synergy = (UX_DCD_SYNERGY *) dcd -> ux_slave_dcd_controller_hardware;

    /** Get the pointer to the device.  */
    device =  &_ux_system_slave -> ux_system_slave_device;

    /** Read the interrupt status register from the controller.  */
    synergy_interrupt =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0);

    /** Check if we have an RESUME.  */
    if (synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_RESM)
    {
        /* Check the status change callback.  */
        if(_ux_system_slave -> ux_system_slave_change_function != UX_NULL)
        {
            /* Inform the application if a callback function was programmed.  */
            _ux_system_slave -> ux_system_slave_change_function(UX_DEVICE_RESUMED);
        }

        /* Clear RESUME.  */
        ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_INTSTS0, (USHORT)(~UX_SYNERGY_DCD_INTSTS0_RESM));
    }

    /** Check the source of the interrupt. Is it VBUS transition?  */
    if (synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_VBINT)
    {
        /* Clear VBUSINT.  */
        ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_INTSTS0, (USHORT)(~UX_SYNERGY_DCD_INTSTS0_VBINT));

        /* Check the state of VBUS. Attached or Detached.  */
        do {
            /* Read 3 times the current status and wait for all read to be equal to avoid jitter.  */
            synergy_register1 = ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0) & UX_SYNERGY_DCD_INTSTS0_VBSTS;
            synergy_register2 = ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0) & UX_SYNERGY_DCD_INTSTS0_VBSTS;
            synergy_register3 = ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0) & UX_SYNERGY_DCD_INTSTS0_VBSTS;

        } while( ( synergy_register1 != synergy_register2 ) || ( synergy_register1 != synergy_register3 ) );

        /* VBUS is stable. Check if on/off.  */        
        if (synergy_register1 & UX_SYNERGY_DCD_INTSTS0_VBSTS)
        {
#if defined(R_USBHS_BASE)
            if (R_USBHS_BASE == dcd->ux_slave_dcd_io)
            {
                /* Enables single-ended receiver operation. */
                ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_CNEN);
            }
#endif
            /* Pull up D+ and open D- This will generate a RESET from the host.  */
            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_DPRPU);
        }
        else
        {
#if defined(R_USBHS_BASE)
            if (R_USBHS_BASE == dcd->ux_slave_dcd_io)
            {
                /* Disables single-ended receiver operation. */
                ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_CNEN);
            }
#endif
            /* Open D+ and D-  */
            ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_DPRPU);

            /* Device is disconnected.  */
            _ux_device_stack_disconnect();
        }        
    }

    /** Check the source of the interrupt. Is it Device State transition (DVST) ?  */
    if (synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_DVST)
    {
        /* Clear DVST.  */
        ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_INTSTS0, (USHORT)(~UX_SYNERGY_DCD_INTSTS0_DVST));

        /* Check the DVSQ state. */
        switch(synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_DVSQ_MASK) 
        {
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_POWERED  :

                break;
                
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_DEFAULT  :

                /** We enter this state when there is a Bus Reset.  */
                /** If the device is marked as configured, the device is reset.  */
                if (device -> ux_slave_device_state == (ULONG)UX_DEVICE_CONFIGURED)
                {
                    _ux_device_stack_disconnect();
                }

                /** Decide what speed is used by the host, read DVSTCTR and isolate speed.  */
                synergy_dvstctr =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_DVSTCTR) & (ULONG)UX_SYNERGY_DCD_DVSTCTR_RHST;
                
                /* What speed ?  Either Full or High speed.  */
                switch(synergy_dvstctr)
                {
                     case    UX_SYNERGY_DCD_DVSTCTR_SPEED_LOW :

                        /* We are connected at full speed.  */
                        _ux_system_slave -> ux_system_slave_speed =  (ULONG)UX_LOW_SPEED_DEVICE;
                    
                         break;

                    case    UX_SYNERGY_DCD_DVSTCTR_SPEED_FULL :

                        /* We are connected at full speed.  */
                        _ux_system_slave -> ux_system_slave_speed =  (ULONG)UX_FULL_SPEED_DEVICE;
                        
                        break;

                    case    UX_SYNERGY_DCD_DVSTCTR_SPEED_HIGH :

                        /* We are connected at high speed.  */
                        _ux_system_slave -> ux_system_slave_speed =  (ULONG)UX_HIGH_SPEED_DEVICE;

                        break;                            
                                        
                    default :
                        break;
                }

                /* Complete the device initialization.  */
                ux_dcd_synergy_initialize_complete();

                /* Mark the device as attached now.  */
                device -> ux_slave_device_state = (ULONG)UX_DEVICE_ATTACHED;
                
                break;
            
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_ADDRESS :
            
                /* Internally decoded command : SET_ADDRESS, memorise the state.  */
                dcd -> ux_slave_dcd_device_address =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_USBADDR);
                break;
                
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_CONFIGURED :

                /* Internally decoded command : SET_CONFIGURATION, memorise the state.  */
                dcd_synergy -> ux_dcd_synergy_debug = (ULONG)UX_DEVICE_CONFIGURED;
                break;
                
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_POWERED :
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_DEFAULT :
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_ADDRESS :
            case    UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_CONFIGURED :
            default :
                /* If the device is attached or configured, Inform the application if a callback function was defined
                    otherwise we have a device disconnection signal */
                if (device -> ux_slave_device_state != (ULONG)UX_DEVICE_RESET)
                {
                    /* Inform the application if a callback function was programmed. */
                    if (_ux_system_slave -> ux_system_slave_change_function != UX_NULL)
                    {
                        /* Callback function with SUSPEND signal */
                        _ux_system_slave -> ux_system_slave_change_function(UX_DEVICE_SUSPENDED);
                    }
                    else
                    {   /* Remote wake-up is disabled, allow the device to disconnection */
                        if ((_ux_system_slave->ux_system_slave_remote_wakeup_enabled == (ULONG)UX_FALSE))
                        {
                            /* Device is reset, the behavior is the same as disconnection.  */
                            _ux_device_stack_disconnect();
                        }
                    }
                }

                break;        
        }
    }

    /** Check if we have a BEMP interrupt.  */
    if (synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_BEMP)
    {
        /* Check BEMP irq flags. */
        bempsts =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_BEMPSTS);
        bempenb =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_BEMPENB);
        bemp_bit = 1UL;

        /* Check pipes.  */
        for (pipe_count = 0UL; pipe_count <= UX_DCD_SYNERGY_MAX_PIPE; pipe_count++)
        {
            /* if flag set, we have something done. */
            if( (bempsts & bemp_bit) && (bempenb & bemp_bit) )
            { 
                /* Clear BEMP.  */
                ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_BEMPSTS, (USHORT)(~bemp_bit));

                /* Get the endpoint associated with this pipe.  */
                ed =  &dcd_synergy -> ux_dcd_synergy_ed[(dcd_synergy -> ux_dcd_synergy_pipe[pipe_count])];

                /* Get the endpoint to the endpoint.  */
                endpoint =  ed -> ux_dcd_synergy_ed_endpoint;
    
                /* Get the pointer to the transfer request.  */
                transfer_request =  &endpoint -> ux_slave_endpoint_transfer_request;
    
                /* Process the call back.  */
                ux_dcd_synergy_transfer_callback(dcd_synergy, transfer_request, UX_SYNERGY_DCD_INTSTS0_BEMP, 0);
            }
            /* Shift the BEMP bit.  */
            bemp_bit = bemp_bit << 1;
        }
    }                   

    /** Check if we have a BRDY interrupt.  */
    if (synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_BRDY)
    {
        /* Check BRDY IRQ flags. */
        brdysts =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_BRDYSTS);
        brdyenb =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_BRDYENB);
        brdy_bit = 1UL;

        /* Check pipes.  */
        for (pipe_count = 0UL; pipe_count <= UX_DCD_SYNERGY_MAX_PIPE; pipe_count++)
        {
            /* if flag set, we have something done. */
            if( (brdysts & brdy_bit) && (brdyenb & brdy_bit) )
            {
                /* Clear BRDY.  */
                ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_BRDYSTS, (USHORT)(~brdy_bit));

                /* Get the endpoint associated with this pipe.  */
                ed =  &dcd_synergy -> ux_dcd_synergy_ed[(dcd_synergy -> ux_dcd_synergy_pipe[pipe_count])];
                /* Get the endpoint to the endpoint.  */
                endpoint =  ed -> ux_dcd_synergy_ed_endpoint;
    
                /* Get the pointer to the transfer request.  */
                transfer_request =  &endpoint -> ux_slave_endpoint_transfer_request;
    
                /* Process the call back.  */
                ux_dcd_synergy_transfer_callback(dcd_synergy, transfer_request, UX_SYNERGY_DCD_INTSTS0_BRDY, 0);
            }

            /* Shift the BRDY bit.  */
            brdy_bit = brdy_bit << 1;
        }
    }                   

    /** Check if we have a NRDY interrupt.  */
    if (synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_NRDY)
    {
        /* Check NRDY IRQ flags. */
        nrdysts =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_NRDYSTS);
        nrdyenb =  ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_NRDYENB);
        nrdy_bit = 1UL;

        /* Check pipes.  */
        for (pipe_count = 0UL; pipe_count <= UX_DCD_SYNERGY_MAX_PIPE; pipe_count++)
        {
            /* if flag set, we have something done. */
            if( (nrdysts & nrdy_bit) && (nrdyenb & nrdy_bit))
            { 
                /* Clear NRDY.  */
                ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_NRDYSTS, (USHORT)(~nrdy_bit));

                /* Get the endpoint associated with this pipe.  */
                ed =  &dcd_synergy -> ux_dcd_synergy_ed[(dcd_synergy -> ux_dcd_synergy_pipe[pipe_count])];
                /* Get the endpoint to the endpoint.  */
                endpoint =  ed -> ux_dcd_synergy_ed_endpoint;
    
                /* Get the pointer to the transfer request.  */
                transfer_request =  &endpoint -> ux_slave_endpoint_transfer_request;
    
                /* Process the call back.  */
                ux_dcd_synergy_transfer_callback(dcd_synergy, transfer_request, UX_SYNERGY_DCD_INTSTS0_NRDY, 0);
            }
            /* Shift the NRDY bit.  */
            nrdy_bit = nrdy_bit << 1;
        }
    }

    /** Check if we have a SETUP transaction phase.  */
    if (synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_CTRT)
    {
        /* Get the physical endpoint associated with this endpoint.  SETUP is on endpoint 0.  */
        ed =  &dcd_synergy -> ux_dcd_synergy_ed[0];

        /* Get the endpoint to the endpoint.  */
        endpoint =  ed -> ux_dcd_synergy_ed_endpoint;
    
        /* Get the pointer to the transfer request.  */
        transfer_request =  &endpoint -> ux_slave_endpoint_transfer_request;

        /* Process the call back.  */
        ux_dcd_synergy_transfer_callback(dcd_synergy, transfer_request, UX_SYNERGY_DCD_INTSTS0_CTRT,
                                            synergy_interrupt & UX_SYNERGY_DCD_INTSTS0_CTSQ_MASK);

        /* Clear CTRT.  */
        ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_INTSTS0, (USHORT)(~UX_SYNERGY_DCD_INTSTS0_CTRT));
    }    
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
