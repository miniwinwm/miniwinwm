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

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_entry                                PORTABLE C      */
/*                                                           5.7 SP7      */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function dispatch the HCD function internally to the Synergy   */
/*    controller driver.                                                  */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    HCD                                  Pointer to HCD                 */
/*    function                             Function for driver to perform */
/*    parameter                            Pointer to parameter(s)        */
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_hcd_synergy_asynch_queue_process          Process asynch queue   */
/*    ux_hcd_synergy_asynch_schedule               Schedule async work    */
/*    ux_hcd_synergy_asynchronous_endpoint_create  Create async endpoint  */
/*    ux_hcd_synergy_asynchronous_endpoint_destroy Destroy async endpoint */
/*    ux_hcd_synergy_controller_disable            Disable controller     */
/*    ux_hcd_synergy_endpoint_reset                Reset endpoint         */
/*    ux_hcd_synergy_frame_number_get              Get frame number       */
/*    ux_hcd_synergy_frame_number_set              Set frame number       */
/*    ux_hcd_synergy_interrupt_endpoint_create     Create endpoint        */
/*    ux_hcd_synergy_iso_queue_process             Process iso queue      */
/*    ux_hcd_synergy_iso_schedule                  Schedule iso work      */
/*    ux_hcd_synergy_isochronous_endpoint_create   Create iso endpoint    */
/*    ux_hcd_synergy_periodic_endpoint_destroy     Destroy endpoint       */
/*    ux_hcd_synergy_periodic_schedule             Schedule periodic      */
/*    ux_hcd_synergy_port_enable                   Enable port            */
/*    ux_hcd_synergy_port_disable                  Disable port           */
/*    ux_hcd_synergy_port_reset                    Reset port             */
/*    ux_hcd_synergy_port_resume                   Resume port            */
/*    ux_hcd_synergy_port_status_get               Get port status        */
/*    ux_hcd_synergy_port_suspend                  Suspend port           */
/*    ux_hcd_synergy_power_down_port               Power down port        */
/*    ux_hcd_synergy_power_on_port                 Power on port          */
/*    ux_hcd_synergy_request_transfer              Request transfer       */
/*    ux_hcd_synergy_transfer_abort                Abort transfer         */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Host Stack                                                          */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  10-10-2012     TCRG                     Initial Version 5.6           */ 
/*  06-01-2014     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.7    */ 
/*  12-15-2016     TCRG                     Modified comment(s),          */ 
/*                                            added new error trap        */
/*                                            function support,           */
/*                                            resulting in version 5.7 SP7*/ 
/*                                                                        */ 
/**************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function is the entry function to the USB driver from the USB stack.
 *
 * @param[in]  hcd         : Pointer to USBX Host Controller structure.
 * @param[in]  function    : Function for driver to perform
 * @param[in]  parameter   : Pointer to function parameter(s)
 *
 * @retval UX_SUCCESS                       HCD function is dispatched successfully.
 * @retval UX_CONTROLLER_UNKNOWN            Synergy controller is not known.
 * @retval UX_FUNCTION_NOT_SUPPORTED        Function not supported.
 * @return                 See @ref Common_Error_Codes for other possible return codes or causes.
 *                         This function calls:
 *                          * ux_hcd_synergy_controller_disable()
 *                          * ux_hcd_synergy_port_status_get()
 *                          * ux_hcd_synergy_port_enable()
 *                          * ux_hcd_synergy_port_disable()
 *                          * ux_hcd_synergy_power_on_port()
 *                          * ux_hcd_synergy_power_down_port()
 *                          * ux_hcd_synergy_port_suspend()
 *                          * ux_hcd_synergy_port_resume()
 *                          * ux_hcd_synergy_port_reset()
 *                          * ux_hcd_synergy_frame_number_get()
 *                          * ux_hcd_synergy_request_transfer()
 *                          * ux_hcd_synergy_transfer_abort()
 *                          * ux_hcd_synergy_control_endpoint_create()
 *                          * ux_hcd_synergy_bulk_endpoint_create()
 *                          * ux_hcd_synergy_interrupt_endpoint_create()
 *                          * ux_hcd_synergy_isochronous_endpoint_create()
 *                          * ux_hcd_synergy_asynchronous_endpoint_destroy()
 *                          * ux_hcd_synergy_periodic_endpoint_destroy()
 *                          * ux_hcd_synergy_endpoint_reset()
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_entry(UX_HCD *hcd, UINT function, VOID *parameter)
{
    UINT              status;
    UX_HCD_SYNERGY  * hcd_synergy;
    

    /* Check the status of the controller.  */
    if (hcd -> ux_hcd_status == (UINT)UX_UNUSED)
    {

        /* Error trap. */
        _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_THREAD, (UINT)UX_SYSTEM_CONTEXT_HCD, (UINT)UX_CONTROLLER_UNKNOWN);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_CONTROLLER_UNKNOWN, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

        return (UINT)UX_CONTROLLER_UNKNOWN;
    }
            
    /* Get the pointer to the Synergy HCD.  */
    hcd_synergy =  (UX_HCD_SYNERGY *) hcd -> ux_hcd_controller_hardware;

    /* look at the function and route it.  */
    switch(function)
    {

    case (UINT)UX_HCD_DISABLE_CONTROLLER:

        status =  ux_hcd_synergy_disable(hcd_synergy->ux_hcd_synergy_base);
        if((UINT)UX_SUCCESS != status)
        {
            break;
        }
        status =  ux_hcd_synergy_controller_disable(hcd_synergy);
        break;

    case (UINT)UX_HCD_UNINITIALIZE:

        status =  ux_hcd_synergy_uninitialize(hcd_synergy->ux_hcd_synergy_base);
        break;

    case (UINT)UX_HCD_GET_PORT_STATUS:

        status =  (UINT)ux_hcd_synergy_port_status_get(hcd_synergy, (ULONG) parameter);
        break;
    
    
    case (UINT)UX_HCD_ENABLE_PORT:
    
        status =  ux_hcd_synergy_port_enable(hcd_synergy, (ULONG) parameter);
        break;
    
    
    case (UINT)UX_HCD_DISABLE_PORT:

        status =  ux_hcd_synergy_port_disable(hcd_synergy, (ULONG) parameter);
        break;


    case (UINT)UX_HCD_POWER_ON_PORT:
        
        status =  ux_hcd_synergy_power_on_port(hcd_synergy, (ULONG) parameter);
        break;


    case (UINT)UX_HCD_POWER_DOWN_PORT:

        status =  ux_hcd_synergy_power_down_port(hcd_synergy, (ULONG) parameter);
        break;


    case (UINT)UX_HCD_SUSPEND_PORT:

        status =  ux_hcd_synergy_port_suspend(hcd_synergy, (ULONG) parameter);
        break;


    case (UINT)UX_HCD_RESUME_PORT:

        status =  ux_hcd_synergy_port_resume(hcd_synergy, (UINT) parameter);
        break;


    case (UINT)UX_HCD_RESET_PORT:

        status =  ux_hcd_synergy_port_reset(hcd_synergy, (ULONG) parameter);
        break;


    case (UINT)UX_HCD_GET_FRAME_NUMBER:

        status =  ux_hcd_synergy_frame_number_get(hcd_synergy, (ULONG *) parameter);
        break;


    case (UINT)UX_HCD_SET_FRAME_NUMBER:

        ux_hcd_synergy_frame_number_set(hcd_synergy, (ULONG) parameter);
        status = (UINT)UX_SUCCESS;
        break;


    case (UINT)UX_HCD_TRANSFER_REQUEST:

        status =  ux_hcd_synergy_request_transfer(hcd_synergy, (UX_TRANSFER *) parameter);
        break;


    case (UINT)UX_HCD_TRANSFER_ABORT:

        status =  ux_hcd_synergy_transfer_abort(hcd_synergy, (UX_TRANSFER *) parameter);
        break;


    case (UINT)UX_HCD_CREATE_ENDPOINT:

        switch ((((UX_ENDPOINT*) parameter) -> ux_endpoint_descriptor.bmAttributes) & UX_MASK_ENDPOINT_TYPE)
        {

        case (ULONG)UX_CONTROL_ENDPOINT:
        
            status =  ux_hcd_synergy_control_endpoint_create(hcd_synergy, (UX_ENDPOINT*) parameter);
            break;

        case (ULONG)UX_BULK_ENDPOINT:
        
            status =  ux_hcd_synergy_bulk_endpoint_create(hcd_synergy, (UX_ENDPOINT*) parameter);
            break;

            
        case (ULONG)UX_INTERRUPT_ENDPOINT:
        
            status =  ux_hcd_synergy_interrupt_endpoint_create(hcd_synergy, (UX_ENDPOINT*) parameter);
            break;


        case (ULONG)UX_ISOCHRONOUS_ENDPOINT:
        
            status =  ux_hcd_synergy_isochronous_endpoint_create(hcd_synergy, (UX_ENDPOINT*) parameter);
            break;

        default:

            /* If trace is enabled, insert this event into the trace buffer.  */
            UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_FUNCTION_NOT_SUPPORTED, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

            status = (UINT)UX_FUNCTION_NOT_SUPPORTED;
        }
        break;


    case (UINT)UX_HCD_DESTROY_ENDPOINT:

        switch ((((UX_ENDPOINT*) parameter) -> ux_endpoint_descriptor.bmAttributes) & UX_MASK_ENDPOINT_TYPE)
        {

        case (ULONG)UX_CONTROL_ENDPOINT:
        case (ULONG)UX_BULK_ENDPOINT:

            status =  ux_hcd_synergy_asynchronous_endpoint_destroy(hcd_synergy, (UX_ENDPOINT*) parameter);
            break;


        case (ULONG)UX_INTERRUPT_ENDPOINT:
        case (ULONG)UX_ISOCHRONOUS_ENDPOINT:

            status =  ux_hcd_synergy_periodic_endpoint_destroy(hcd_synergy, (UX_ENDPOINT*) parameter);
            break;

        default:

            /* Error trap. */
            _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_THREAD, (UINT)UX_SYSTEM_CONTEXT_HCD, (UINT)UX_FUNCTION_NOT_SUPPORTED);

            /* If trace is enabled, insert this event into the trace buffer.  */
            UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_FUNCTION_NOT_SUPPORTED, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

            status = (UINT)UX_FUNCTION_NOT_SUPPORTED;
        }
        break;


    case (ULONG)UX_HCD_RESET_ENDPOINT:

        status =  ux_hcd_synergy_endpoint_reset(hcd_synergy, (UX_ENDPOINT*) parameter);
        break;


    case (ULONG)UX_HCD_PROCESS_DONE_QUEUE:

        /* Check if a device is attached.  */
        if (hcd_synergy -> ux_synergy_device_attached == (ULONG)UX_TRUE)
        {
            ux_hcd_synergy_iso_queue_process(hcd_synergy);
            ux_hcd_synergy_asynch_queue_process(hcd_synergy);
            ux_hcd_synergy_iso_schedule(hcd_synergy);

            ux_hcd_synergy_periodic_schedule(hcd_synergy);
            ux_hcd_synergy_asynch_schedule(hcd_synergy);
        }
        status = (UINT)UX_SUCCESS;
        break;

    default:
    
        /* Error trap. */
        _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_THREAD, (UINT)UX_SYSTEM_CONTEXT_HCD, (UINT)UX_FUNCTION_NOT_SUPPORTED);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_FUNCTION_NOT_SUPPORTED, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

        /* Unknown request, return an error.  */
        status = (UINT)UX_FUNCTION_NOT_SUPPORTED;
        break;
    }        
    
    /* Return completion status.  */
    return (status);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

