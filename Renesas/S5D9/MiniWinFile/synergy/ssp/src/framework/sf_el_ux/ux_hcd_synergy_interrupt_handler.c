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
#include "ux_system.h"
#include "ux_utility.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_interrupt_handler                    PORTABLE C      */
/*                                                           5.7 SP7      */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function is the interrupt handler for the Synergy interrupts. */
/*     Normally an interrupt occurs from the controller when there is     */ 
/*     either a EOF signal and there has been transfers within the frame  */ 
/*     or when there is a change on one of the downstream ports.          */
/*                                                                        */
/*     All we need to do in the ISR is scan the controllers to find out   */ 
/*     which one has issued a IRQ. If there is work to do for this        */ 
/*     controller we need to wake up the corresponding thread to take     */ 
/*     care of the job.                                                   */ 
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
/*    ux_hcd_synergy_register_read           Read Synergy HCOR register   */
/*    ux_hcd_synergy_register_write          Write Synergy HCOR register  */
/*    _ux_utility_semaphore_put              Put producer semaphore       */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    ThreadX Interrupt Handler                                           */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  10-10-2012     TCRG                     Initial Version 5.6           */ 
/*  06-01-2014     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.7    */ 
/*  12-15-2016     TCRG                     Modified comment(s),          */ 
/*                                            added code for overcurrent  */
/*                                            protection,                 */
/*                                            resulting in version 5.7 SP7*/ 
/*                                                                        */ 
/**************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function is the interrupt handler for the Synergy USB HS controller.
 *         Normally an interrupt occurs from the controller when there is
 *         either a EOF signal and there has been transfers within the frame
 *         or when there is a change on one of the downstream ports.
 *
 *         All we need to do in the ISR is scan the controllers to find out
 *         which one has issued a IRQ. If there is work to do for this
 *         controller we need to wake up the corresponding thread to take
 *         care of the job.
 *
 * @param[in]  hcd_index : HCD number
 **********************************************************************************************************************/
VOID  ux_hcd_synergy_interrupt_handler(UINT hcd_index)
{
    UX_HCD            * hcd;
    UX_HCD_SYNERGY    * hcd_synergy;
    ULONG               bempsts;
    ULONG               nrdysts;
    ULONG               brdysts;
    ULONG               bemp_bit;
    ULONG               nrdy_bit;
    ULONG               brdy_bit;
    ULONG               endpoint_count;
    ULONG               intenb0;
    ULONG               intenb1;

    /* Check type of controller.  */
    if (_ux_system_host -> ux_system_host_hcd_array[hcd_index].ux_hcd_controller_type == (UINT)UX_SYNERGY_CONTROLLER)
    {
        /* Get the pointers to the generic HCD and synergy specific areas.  */
        hcd =  &_ux_system_host -> ux_system_host_hcd_array[hcd_index];
        hcd_synergy =  (UX_HCD_SYNERGY *) hcd -> ux_hcd_controller_hardware;

        /* Increase the interrupt count. This indicates the controller is still alive.  */
        hcd_synergy -> ux_hcd_synergy_interrupt_count++;

        /** Check if the controller is operational, if not, skip it.  */
        if (hcd -> ux_hcd_status == (UINT)UX_HCD_STATUS_OPERATIONAL)
        {

           /* We get the current enabled interrupt. */
            intenb0 =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_INTENB0);
            intenb1 =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_INTENB1);

           /* We get the current interrupt status  registers and mask them with the interrupts enabled.  */
            hcd_synergy->ux_hcd_synergy_intsts0 =
                    ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_INTSTS0) & intenb0;
            hcd_synergy->ux_hcd_synergy_intsts1 =
                    ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_INTSTS1) & intenb1;

            /** Examine the source of interrupts.  Check for SOF signal.  */
            if (hcd_synergy->ux_hcd_synergy_intsts0 & (ULONG)UX_SYNERGY_HC_INTSTS0_SOFR)
            {
                /* Acknowledge interrupt  - wake up scheduler. */
                ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_INTSTS0, (USHORT)(~UX_SYNERGY_HC_INTSTS0_SOFR));

                /* We have a SOF signal, we should find out what happened during the last frame and see if  there is
                 * anything to do in the next frame.  */
                /* these interrupts are automatically acknowleged when all the pipe-buffer interrupts are handled */
                /* Wake up the scheduler but we cannot safely mark the queue empty yet. This will be done  when we find
                 *  that the scheduling queue is empty.  */
                hcd -> ux_hcd_thread_signal++;
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_hcd_semaphore);

            }

            /** Check for Over Current condition.  */
            if (hcd_synergy->ux_hcd_synergy_intsts1 & (ULONG)UX_SYNERGY_HC_INTSTS1_OVRCRE)
            {

                /* Acknowledge interrupt */
                ux_hcd_synergy_register_write(hcd_synergy,
                                              UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_OVRCRE));

                /* Error trap. */
                _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_INTERRUPT, (UINT)UX_SYSTEM_CONTEXT_HCD, (UINT)UX_OVER_CURRENT_CONDITION);

            }

            /** Check if we have a BEMP interrupt.  */
            if (hcd_synergy->ux_hcd_synergy_intsts0 & UX_SYNERGY_HC_INTSTS0_BEMP )
            {
                /* Check BEMP irq flags. */
                bempsts =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_BEMPSTS);
                bemp_bit = 1UL;

                /* 10 endpoints to check.  */
                for (endpoint_count = 0UL; endpoint_count <= 9UL; endpoint_count++)
                {
                    /* if flag set, mark BEMP in ed status */
                    if( bempsts & bemp_bit )
                    {
                        if (hcd_synergy -> ux_hcd_synergy_ed_ptr[endpoint_count])
                        {
                            hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] =
                                    hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] | UX_SYNERGY_HC_ED_BEMP ;
                        }
                        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_BEMPSTS, (USHORT)(~bemp_bit));
                    }
                    bemp_bit = bemp_bit << 1UL;
                }

                /* Increment the thread signal.  */
                hcd -> ux_hcd_thread_signal++;

                /* And wake up the HCD thread.  */
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_hcd_semaphore);
            }

            /** Do we have a BRDY interrupt ? */
            if (hcd_synergy->ux_hcd_synergy_intsts0 & (ULONG)UX_SYNERGY_HC_INTSTS0_BRDY )
            {
                /* Check BRDY irq flags. */
                brdysts =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_BRDYSTS);
                brdy_bit = 1UL;

                for (endpoint_count = 0UL; endpoint_count <= 9UL; endpoint_count++)
                {
                    /* If flag set, mark BRDY in ed status. */
                    if( brdysts & brdy_bit )
                    {
                        if (hcd_synergy -> ux_hcd_synergy_ed_ptr[endpoint_count] )
                        {
                            hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] =
                                    hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] | UX_SYNERGY_HC_ED_BRDY ;
                        }
                        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_BRDYSTS, (USHORT)(~brdy_bit));
                    }
                    brdy_bit = brdy_bit << 1UL;
                }

                /* Increment the thread signal.  */
                hcd -> ux_hcd_thread_signal++;

                /* And wake up the HCD thread.  */
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_hcd_semaphore);
            }

            /** Do we have a NRDY interrupt ?  */
            if (hcd_synergy->ux_hcd_synergy_intsts0 & (ULONG)UX_SYNERGY_HC_INTSTS0_NRDY )
            {
                /* Check NRDY irq flags. */
                nrdysts =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_NRDYSTS);
                nrdy_bit = 1UL;

                for (endpoint_count = 0UL; endpoint_count <= 9UL; endpoint_count++)
                {
                    /* If flag set, mark NRDY in ed status. */
                    if( nrdysts & nrdy_bit )
                    {
                        if (hcd_synergy -> ux_hcd_synergy_ed_ptr[endpoint_count] )
                        {
                            hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] =
                                    hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] | UX_SYNERGY_HC_ED_NRDY ;
                        }
                        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_NRDYSTS, (USHORT)(~nrdy_bit));
                    }
                    nrdy_bit = nrdy_bit << 1UL;
                }
                hcd -> ux_hcd_thread_signal++;
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_hcd_semaphore);
            }

            /** Check for attach signal.  */
            if (hcd_synergy->ux_hcd_synergy_intsts1 & (UX_SYNERGY_HC_INTSTS1_ATTCH) )
            {
                 /* Acknowledge interrupt. */
                ux_hcd_synergy_register_write(hcd_synergy,
                                              UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_ATTCH));

                /* By precaution, acknowledge interrupt for detach. */
                ux_hcd_synergy_register_write(hcd_synergy,
                        UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_DTCH));

                /* Check if the USB port is in use for low-speed communication. */
                if (UX_SYNERGY_HC_SYSSTS0_LNST_J_STATE_LS & ux_hcd_synergy_register_read(hcd_synergy,
                        UX_SYNERGY_HC_SYSSTS0))
                {
                    /* Switch the timing of token issue matching to low-speed mode. */
                    ux_hcd_synergy_register_set(hcd_synergy,
                                                UX_SYNERGY_HC_SOFCFG, (USHORT)UX_SYNERGY_HC_SOFCFG_TRNENSEL);

#if defined(R_USBHS_BASE)
                    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
                    {
                        /* Disable High-Speed Operation. */
                        ux_hcd_synergy_register_clear(hcd_synergy,
                                                      UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_HSE);
                    }
#endif
                }
                else
                {
                    ux_hcd_synergy_register_clear(hcd_synergy,
                                                  UX_SYNERGY_HC_SOFCFG, (USHORT)UX_SYNERGY_HC_SOFCFG_TRNENSEL);

#if defined(R_USBHS_BASE)
#ifndef UX_HOST_DISABLE_HS
                    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
                    {
                        /* Enable High-Speed Operation. */
                        ux_hcd_synergy_register_set(hcd_synergy,
                                                    UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_HSE);
                    }
#endif
#endif
                }

                /* Clear the ATTCH interrupt enabled.  */
                ux_hcd_synergy_register_clear(hcd_synergy,
                                                  UX_SYNERGY_HC_INTENB1, (USHORT)UX_SYNERGY_HC_INTENB1_ATTCHE);

                /* Enable the DTCH interrupt.  */
                ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_INTENB1, (USHORT)UX_SYNERGY_HC_INTENB1_DTCHE);

                /* Something happened on this port. Signal it to the root hub thread.  */
                hcd -> ux_hcd_root_hub_signal[0]++;

                /* Something is attached now.  */
                hcd_synergy -> ux_synergy_device_attached = (ULONG)UX_TRUE;

                /* Reset the address of the device connected to the root hub.  */
                ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPMAXP, 0U);

                /* Update the device address in the HCD structure.  We will force a resetting later. */
                hcd_synergy -> ux_hcd_synergy_root_hub_device_address = 0xFFFFFFFFUL;

                /* We only wake up the root hub thread if there has been device insertion/extraction.  */
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_enum_semaphore);
            }

            /** Is it a detach signal ? */
            if (hcd_synergy->ux_hcd_synergy_intsts1 & (ULONG)UX_SYNERGY_HC_INTSTS1_DTCH)
            {
                /* Acknowledge interrupt.  */
                ux_hcd_synergy_register_write(hcd_synergy,
                                              UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_DTCH));

                /* By precaution, acknowledge interrupt for attach. */
                ux_hcd_synergy_register_write(hcd_synergy,
                        UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_ATTCH));

                /* Clear the DTCH interrupt enabled.  */
                ux_hcd_synergy_register_clear(hcd_synergy,
                                                  UX_SYNERGY_HC_INTENB1, (USHORT)UX_SYNERGY_HC_INTENB1_DTCHE);

                /* Enable the ATTCH interrupt.  */
                ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_INTENB1, (USHORT)UX_SYNERGY_HC_INTENB1_ATTCHE);

                /* Mark all endpoints as transaction timeout. This is necessary because
                the Synergy USB IP does not detect an error if the device is removed. */
                for (endpoint_count = 0UL; endpoint_count <= 9UL; endpoint_count++)
                {
                    /* Check endpoint.  */
                    if (hcd_synergy -> ux_hcd_synergy_ed_ptr[endpoint_count] )
                    {
                        hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] =
                        		hcd_synergy -> ux_hcd_synergy_ed_irq[endpoint_count] | UX_SYNERGY_HC_ED_TIMEOUT ;
                    }
                }

                /* Wake up the HCD thread.  */
                hcd -> ux_hcd_thread_signal++;
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_hcd_semaphore);

                /* Something happened on this port. Signal it to the root hub thread.  */
                hcd -> ux_hcd_root_hub_signal[0]++;

                /* Something is getting detached now. */
                hcd_synergy -> ux_synergy_device_attached = (ULONG)UX_FALSE ;

                /* And the port is disabled.  */
                hcd_synergy -> ux_hcd_synergy_port_status = (ULONG)UX_SYNERGY_HC_PORT_DISABLED;

                /* We only wake up the root hub thread if there has been device insertion/extraction.  */
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_enum_semaphore);
            }

            /** Check for BCHG signal.  */
            if (hcd_synergy->ux_hcd_synergy_intsts1 & (ULONG)UX_SYNERGY_HC_INTSTS1_BCHG)
            {
                 /* Acknowledge interrupt. */
                ux_hcd_synergy_register_write(hcd_synergy,
                                              UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_BCHG));

                /* Attach only if nothing was previously attached and if the port is not enabled.  */
                if (   (hcd_synergy -> ux_synergy_device_attached == (ULONG)UX_FALSE)
                    && (hcd_synergy -> ux_hcd_synergy_port_status != (ULONG)UX_SYNERGY_HC_PORT_ENABLED)
                ){
                    /* Clear the BCHG interrupt enabled.  */
                    ux_hcd_synergy_register_clear(hcd_synergy,
                                                  UX_SYNERGY_HC_INTENB1, (USHORT)UX_SYNERGY_HC_INTENB1_BCHGE);

                    /* Enable the DTCH interrupt.  */
                    ux_hcd_synergy_register_set(hcd_synergy,
                            UX_SYNERGY_HC_INTENB1, (USHORT)UX_SYNERGY_HC_INTENB1_DTCHE);

                    /* Something happened on this port. Signal it to the root hub thread.  */
                    hcd -> ux_hcd_root_hub_signal[0]++;

                    /* Something is attached now.  */
                    hcd_synergy -> ux_synergy_device_attached = (ULONG)UX_TRUE;

                    /* Reset the address of the device connected to the root hub.  */
                    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPMAXP, 0U);

                    /* Update the device address in the HCD structure.  We will force a resetting later. */
                    hcd_synergy -> ux_hcd_synergy_root_hub_device_address = 0xFFFFFFFFUL;

                    /* We only wake up the root hub thread if there has been device insertion/extraction.  */
                    _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_enum_semaphore);
                }
            }

            /** Is it a EOFERR signal.  */
            if (hcd_synergy->ux_hcd_synergy_intsts1 & (ULONG)UX_SYNERGY_HC_INTSTS1_EOFERR)
            {
                /* Acknowledge interrupt.  */
                ux_hcd_synergy_register_write(hcd_synergy,
                                              UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_EOFERR));

                /* Something happened on this port. Signal it to the root hub thread.  */
                hcd -> ux_hcd_root_hub_signal[0]++;

                /* Something is getting detached now. */
                hcd_synergy -> ux_synergy_device_attached = (ULONG)UX_FALSE ;

                /* Port State machine is EOFERR.  */
                hcd_synergy -> ux_hcd_synergy_port_status = (ULONG)UX_SYNERGY_HC_PORT_INEOFERR;

                /* We wake up the root hub thread to fake device removal due to EOFERR.  */
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_enum_semaphore);
            }

            /** Did we get a SACK interrupt ?  */
            if (hcd_synergy->ux_hcd_synergy_intsts1 & (ULONG)UX_SYNERGY_HC_INTSTS1_SACK)
            {
                /*  Clear interrupt. */
                ux_hcd_synergy_register_write(hcd_synergy,
                                              UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_SACK));

                /* SACK can only happen on EP0.  */
                hcd_synergy -> ux_hcd_synergy_ed_irq[0] =
                        hcd_synergy -> ux_hcd_synergy_ed_irq[0] | UX_SYNERGY_HC_ED_SACK ;

                hcd -> ux_hcd_thread_signal++;
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_hcd_semaphore);
            }

            /** Did we get a SIGN interrupt ?  */
            if (hcd_synergy->ux_hcd_synergy_intsts1 & (ULONG)UX_SYNERGY_HC_INTSTS1_SIGN)
            {
                /*  Clear interrupt. */
                ux_hcd_synergy_register_write(hcd_synergy,
                                              UX_SYNERGY_HC_INTSTS1, (USHORT)(~UX_SYNERGY_HC_INTSTS1_SIGN));

                /* SIGN can only happen on EP0.  */
                hcd_synergy -> ux_hcd_synergy_ed_irq[0] =
                        hcd_synergy -> ux_hcd_synergy_ed_irq[0] | UX_SYNERGY_HC_ED_SIGN ;

                hcd -> ux_hcd_thread_signal++;
                _ux_utility_semaphore_put(&_ux_system_host -> ux_system_host_hcd_semaphore);
            }
        }
    }
}
 /*******************************************************************************************************************//**
  * @} (end addtogroup sf_el_ux)
  **********************************************************************************************************************/


