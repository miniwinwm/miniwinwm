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

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_periodic_tree_create                 PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function creates the periodic static tree for the interrupt   */ 
/*     and isochronous eds.                                               */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_hcd_synergy_ed_obtain              Obtain Synergy ED             */
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
 * @brief  This function creates the periodic static tree for the interrupt
 *         and isochronous eds.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 *
 * @retval UX_SUCCESS            Periodic tree created successfully.
 * @retval UX_NO_ED_AVAILABLE    Failed to obtain an ED.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_periodic_tree_create(UX_HCD_SYNERGY *hcd_synergy)
{
    UX_SYNERGY_ED     * ed;
    UINT                list_index;
    UINT                list_entries;
    UINT                current_list_entry;
    UX_SYNERGY_ED     * ed_list[32];
    UX_SYNERGY_ED     * ed_start_list[32] = {NULL};
    
    /* Start with the 1st list - it has 32 entries.  */
    list_entries =  32U;

    /* Create each list one by one starting from the 32ms list.  */
    for (list_index = 0U; list_index < 6U; list_index++)
    {
        for (current_list_entry = 0U; current_list_entry < list_entries; current_list_entry++)
        {
            /* In each list, insert an static ED as the anchor. There should not
               be any errors when obtaining a new ED, still we do a sanity check.  */
            ed =  ux_hcd_synergy_ed_obtain(hcd_synergy);
            if (ed == UX_NULL)
            {
                return (UINT)UX_NO_ED_AVAILABLE;
            }

            /* Mark this anchor ED as static by putting it as SKIPPED, the synergy  controller will 
               not look into its tail and head list and will simply jump to the next ED.  */
            ed -> ux_synergy_ed_status = (ULONG)UX_SYNERGY_ED_STATIC;

            /* Either we hook this new ED to the start list for further processing
               or we hook it to the 2 successive entries in the previous list.  */
            if (list_index == 0U)
            {
                ed_start_list[current_list_entry] =  ed;
            }
            else
            {
                ed_list[current_list_entry * 2U] -> ux_synergy_ed_next_ed =  ed;
                ed_list[(current_list_entry * 2U) + 1U] -> ux_synergy_ed_next_ed =  ed;
            }

            /* Memorize this ED in the local list. We do this operation now, otherwise
               we would erase the previous list eds.  */
            ed_list[current_list_entry] =  ed;
        }

        /*  Shift the number of entries in the next list by 1 (i.e. divide by 2).  */
        list_entries =  list_entries >> 1;
    }

    /* The tree has been completed but the entries in the interrupt list are in the wrong order.
       We need to swap each entry according to the synergy specified entry order list 
       so that we have a fair interval frequency for each periodic ED. The primary eds are 
       fetched from the start list, and stored in the interrupt list.  */
    for (current_list_entry = 0U; current_list_entry < 32U; current_list_entry++)
    {
        ed =  ed_start_list[_ux_system_host_hcd_periodic_tree_entries[current_list_entry]];
        hcd_synergy -> ux_hcd_synergy_interrupt_ed_list[current_list_entry] =  ed;
    }

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
