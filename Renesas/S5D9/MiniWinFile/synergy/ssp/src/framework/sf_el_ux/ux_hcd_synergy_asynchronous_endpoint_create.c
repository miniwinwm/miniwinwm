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
/**   synergy Controller Driver                                                */
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
/*    ux_hcd_synergy_asynchronous_endpoint_create         PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function will create an asynchronous endpoint. The control     */
/*    and bulk endpoints fall into this category.                         */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*    endpoint                              Pointer to endpoint           */
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_hcd_synergy_ed_obtain              Obtain synergy ED             */
/*    ux_hcd_synergy_regular_td_obtain      Obtain synergy regular TD     */
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
 * @brief  This function will create an asynchronous endpoint. The control and bulk endpoints fall into
 *         this category.
 *
 * @param[in,out]  hcd_synergy  : Pointer to a HCD control block
 * @param[in,out]  endpoint     : Pointer to endpoint
 *
 * @retval UX_NO_ED_AVAILABLE   ED for new endpoint not available.
 * @retval UX_NO_TD_AVAILABLE   Dummy TD not available for terminating the ED transfer chain.
 * @retval UX_SUCCESS           Asynchronous endpoint created successfully.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_asynchronous_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint)
{
    UX_SYNERGY_ED       *ed;
    UX_SYNERGY_ED       *head_ed;
    UX_SYNERGY_TD       *td;

    /* We need to take into account the nature of the HCD to define the max size
       of any transfer in the transfer request.  */
    endpoint -> ux_endpoint_transfer_request.ux_transfer_request_maximum_length = (ULONG)UX_SYNERGY_MAX_BULK_PAYLOAD;
    
    /* Obtain a ED for this new endpoint. This ED will live as long as the endpoint is active 
       and will be the container for the tds.  */
    ed =  ux_hcd_synergy_ed_obtain(hcd_synergy);
    if (ed == UX_NULL)
    {
        return (UINT)UX_NO_ED_AVAILABLE;
    }

    /* Obtain a dummy TD for terminating the ED transfer chain.  */
    td =  ux_hcd_synergy_regular_td_obtain(hcd_synergy);
    if (td == UX_NULL)
    {
        ed -> ux_synergy_ed_status =  (ULONG)UX_UNUSED;
        return (UINT)UX_NO_TD_AVAILABLE;
    }

    /* Attach the ED to the endpoint container.  */
    endpoint -> ux_endpoint_ed =  (VOID *) ed;

    /* Now do the opposite, attach the ED container to the physical ED.  */
    ed -> ux_synergy_ed_endpoint =  endpoint;
    
    /* Hook the TD to both the tail and head of the ED.  */
    ed -> ux_synergy_ed_tail_td =  td;
    ed -> ux_synergy_ed_head_td =  td;
    
    /* Attach this ED to the asynch list.  */
    head_ed =  hcd_synergy -> ux_hcd_synergy_asynch_head_ed;
    ed -> ux_synergy_ed_next_ed =  head_ed;
    hcd_synergy -> ux_hcd_synergy_asynch_head_ed =  ed;

    /* Build the back chaining pointer. The previous head ED needs to know about the
       inserted ED. */
    if (head_ed != UX_NULL)
    {
        head_ed -> ux_synergy_ed_previous_ed =  ed;
    }

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
