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
/*    ux_hcd_synergy_least_traffic_list_get               PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function return a pointer to the first ED in the periodic     */ 
/*     tree that has the least traffic registered.                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    UX_SYNERGY_ED *                       Pointer to Synergy ED         */
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
 * @brief  This function return a pointer to the first ED in the periodic
 *         tree that has the least traffic registered.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 *
 * @retval min_bandwidth_ed    End descriptor interrupt Number(ed)
 **********************************************************************************************************************/
UX_SYNERGY_ED  *ux_hcd_synergy_least_traffic_list_get(UX_HCD_SYNERGY *hcd_synergy)
{
    UX_SYNERGY_ED     * min_bandwidth_ed;
    UX_SYNERGY_ED     * begin_ed;
    UX_SYNERGY_ED     * ed;
    UX_ENDPOINT       * endpoint;
    UINT                list_index;
    ULONG               min_bandwidth_used;
    ULONG               bandwidth_used;

    /* Set the min bandwidth used to a arbitrary maximum value.  */
    min_bandwidth_used =  0xFFFFFFFFUL;

    /* The first ED is the list candidate for now.  */
    min_bandwidth_ed =  hcd_synergy -> ux_hcd_synergy_interrupt_ed_list[0];
    
    /* All list will be scanned.  */
    for (list_index = 0U; list_index < 32U; list_index++)
    {
        /* Reset the bandwidth for this list.  */
        bandwidth_used =  0UL;

        /* Get the ED of the beginning of the list we parse now.  */
        ed =  hcd_synergy -> ux_hcd_synergy_interrupt_ed_list[list_index];

        /* We keep track of the first ED for the current list.  */
        begin_ed =  ed;

        /* Parse the eds in the list.  */
        while (ed -> ux_synergy_ed_next_ed != UX_NULL)
        {
            /* Check if this is a valid endpoint or an anchor only.  */
            if ((ed -> ux_synergy_ed_status & UX_SYNERGY_ED_STATIC) == 0)
            {
                /* Get the endpoint pointer from the physical ED.  */
                endpoint =  ed -> ux_synergy_ed_endpoint;

                /* Add to the bandwidth used the max packet size pointed by this ED.  */
                bandwidth_used +=  (ULONG) endpoint -> ux_endpoint_descriptor.wMaxPacketSize;
            }
            
            /* Move to next ED.  */           
            ed =  ed -> ux_synergy_ed_next_ed;
        }

        /* We have processed a list, check the bandwidth used by this list.
           If this bandwidth is the minimum, we memorize the ED.  */        
        if (bandwidth_used < min_bandwidth_used)
        {
            /* We have found a better list with a lower used bandwidth, memorize the bandwidth 
               for this list.  */
            min_bandwidth_used =  bandwidth_used;
            
            /* Memorize the begin ED for this list.  */
            min_bandwidth_ed =  begin_ed;
        }
    }
    
    /* Return the ED list with the lowest bandwidth.  */
    return (min_bandwidth_ed);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
