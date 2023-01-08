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
/*    ux_hcd_synergy_request_transfer                     PORTABLE C      */ 
/*                                                           5.7 SP7      */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function is the handler for all the transactions on the USB.  */
/*     The transfer request passed as parameter contains the endpoint and */ 
/*     the device descriptors in addition to the type of transaction de   */ 
/*     be executed. This function routes the transfer request to          */ 
/*     according to the type of transfer to be executed.                  */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */ 
/*    transfer_request                      Pointer to transfer request   */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_hcd_synergy_request_bulk_transfer         Request bulk transfer  */ 
/*    ux_hcd_synergy_request_control_transfer      Request control        */ 
/*                                                    transfer            */ 
/*    ux_hcd_synergy_request_interrupt_transfer    Request interrupt      */ 
/*                                                    transfer            */ 
/*    ux_hcd_synergy_request_isochronous_transfer  Request isochronous    */ 
/*                                                    transfer            */ 
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
/*  06-01-2014     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.7    */ 
/*  12-15-2016     TCRG                     Modified comment(s),          */ 
/*                                           check for device insertion   */ 
/*                                            at driver level before      */ 
/*                                            proceeding with transfer,   */ 
/*                                            resulting in version 5.7 SP7*/ 
/*                                                                        */ 
/**************************************************************************/ 

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function is the handler for all the transactions on the USB.
 *         The transfer request passed as parameter contains the endpoint and
 *         the device descriptors in addition to the type of transaction de
 *         be executed. This function routes the transfer request to
 *         according to the type of transfer to be executed.
 *
 *
 * @param[in]      hcd_synergy         : Pointer to a HCD control block
 * @param[in,out]  transfer_request    : Pointer to transfer request
 *
 * @retval UX_ERROR                 Error while Isolating the endpoint type and routing the transfer request.
 * @retval UX_NO_DEVICE_CONNECTED   No device attached.
 *
 * @return                          See @ref Common_Error_Codes for other possible return codes or causes.
 *                                  This function calls:
 *                                  * ux_hcd_synergy_request_control_transfer()
 *                                  * ux_hcd_synergy_request_bulk_transfer()
 *                                  * ux_hcd_synergy_request_interrupt_transfer()
 *                                  * ux_hcd_synergy_request_isochronous_transfer()
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_request_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request)
{
    UX_ENDPOINT     *endpoint;
    UINT            status;
    
    /* Now check the low level filter.  */
    if (hcd_synergy -> ux_synergy_device_attached == (ULONG)UX_TRUE)
    {
        /* Get the pointer to the Endpoint.  */
        endpoint =  (UX_ENDPOINT *) transfer_request -> ux_transfer_request_endpoint;

        /* We reset the actual length field of the transfer request as a safety measure.  */
        transfer_request -> ux_transfer_request_actual_length =  0UL;
    
        /* Isolate the endpoint type and route the transfer request.  */
        switch ((endpoint -> ux_endpoint_descriptor.bmAttributes) & (ULONG)UX_MASK_ENDPOINT_TYPE)
        {
        case (ULONG)UX_CONTROL_ENDPOINT:

            status =  ux_hcd_synergy_request_control_transfer(hcd_synergy, transfer_request);
            break;

        case (ULONG)UX_BULK_ENDPOINT:

            status =  ux_hcd_synergy_request_bulk_transfer(hcd_synergy, transfer_request);
            break;

        case (ULONG)UX_INTERRUPT_ENDPOINT:

            status =  ux_hcd_synergy_request_interrupt_transfer(hcd_synergy, transfer_request);
            break;

        case (ULONG)UX_ISOCHRONOUS_ENDPOINT:
        default:
            status =  ux_hcd_synergy_request_isochronous_transfer(hcd_synergy, transfer_request);
            break;
        }
    }
    else
    {
        /* Error, no device attached.  */
        status = (UINT)UX_NO_DEVICE_CONNECTED;
    }

    return (status);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

