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
/*    ux_hcd_synergy_asynch_schedule                      PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function schedules new transfers from the control/bulk lists.  */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                       Pointer to Synergy controller     */
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
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
 * @brief  This function schedules new transfers from the control or bulk lists.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 **********************************************************************************************************************/
VOID  ux_hcd_synergy_asynch_schedule(UX_HCD_SYNERGY *hcd_synergy)
{
    UX_SYNERGY_ED  * ed;
    UX_SYNERGY_ED  * first_ed;
    UINT             status;

    /* Get the pointer to the current ED in the asynchronous list.  */
    ed =  hcd_synergy -> ux_hcd_synergy_asynch_current_ed;

    /* Check if there is any EDs candidate in the asynchronous list.  */
    if (ed == UX_NULL)
    {
        /* Check if there is any ED in the asynchronous list. If none, nothing to do.  */
        if (hcd_synergy -> ux_hcd_synergy_asynch_head_ed == UX_NULL)
        {
            return;
        }
        else
        {
            /* We use the first ED of the asynchronous list.  */
            ed = hcd_synergy -> ux_hcd_synergy_asynch_head_ed;
        }
    }

    /* Remember this ED.  */
    first_ed =  ed;

    /* Parse the list of EDs in search for scheduling candidates. */
    do 
    {
        /* Check if this ED has a tail and head TD different, and no TD in progress */
        if (   (ed -> ux_synergy_ed_tail_td != ed -> ux_synergy_ed_head_td)
            && (0 == (ed -> ux_synergy_ed_head_td -> ux_synergy_td_status & UX_SYNERGY_TD_ACK_PENDING))
        ){
            /* Insert this transfer in the list of TDs if possible.  */
            status =  ux_hcd_synergy_td_add(hcd_synergy, ed);

            /* If the TD has been added to the list, we can memorize this ED has
               being served and make the next ED as the one to be first scanned
               at the next SOF.  */
            if (status == (UINT)UX_SUCCESS)
            {
                /* If this is the end of the list ?  */
                if (ed -> ux_synergy_ed_next_ed == UX_NULL)
                {
                    /* Restart from the beginning.  */
                    hcd_synergy -> ux_hcd_synergy_asynch_current_ed =  hcd_synergy -> ux_hcd_synergy_asynch_head_ed;
                }
                else
                {
                    /* This is not the end, so use the next ED as the next candidate.  */
                    hcd_synergy -> ux_hcd_synergy_asynch_current_ed =  ed -> ux_synergy_ed_next_ed;
                }
            }
        }

        /* Point to the next ED in the list. Check if at end of list.  */
        if (ed -> ux_synergy_ed_next_ed == UX_NULL)
        {
            /* We are at the end. restart from the beginning.  */
            ed =  hcd_synergy -> ux_hcd_synergy_asynch_head_ed;
        }
        else            
        {
            /* Proceed to the next ED.  */
            ed =  ed -> ux_synergy_ed_next_ed;
        }
    } while ((ed) && (ed != first_ed));
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

