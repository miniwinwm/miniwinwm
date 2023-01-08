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
/*    ux_hcd_synergy_frame_number_get                     PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function will return the frame number currently used by the    */
/*    controller. This function is mostly used for isochronous purposes   */ 
/*    and for timing.                                                     */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*    frame_number                          Frame number to set           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_hcd_synergy_register_read            Read Synergy register       */
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
 * @brief  This function will return the frame number currently used by the
 *         controller. This function is mostly used for isochronous purposes
 *         and for timing.
 *
 * @param[in,out]  hcd_synergy  : Pointer to a HCD control block
 * @param[in,out]  frame_number : Frame number to set
 *
 * @retval UX_SUCCESS       Frame number returned successfully.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_frame_number_get(UX_HCD_SYNERGY *hcd_synergy, ULONG *frame_number)
{
    ULONG               synergy_register_port_status;
    volatile ULONG      index_loop;
    volatile ULONG      dummy_access = 0;
    
    /* Read the true port status.  */            
    synergy_register_port_status =  ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_DVSTCTR0);
                                
    /* Check if port is transmitting SOFs. 
       There is a catch with the SH2 processor USB cell. If the downstream port is not sending SOFs
       the frame number is not incremented. So we use a local loop.  */
    if ((synergy_register_port_status & UX_SYNERGY_HC_DVSTCTR0_UACT) == 0)
    {
        /* There s no SOF generated. Do 1 ms loop locally.  */
        for (index_loop = 0UL; index_loop < 200000UL; index_loop++)
        {
            dummy_access++;
        }

        /* Now increment the frame number in the HCD structure.  */
        hcd_synergy -> ux_hcd_synergy_frame_number++;
    }
    else
    {
        /* Pickup the frame number.  */
        hcd_synergy -> ux_hcd_synergy_frame_number =
                ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_FRMNUM) & UX_SYNERGY_HC_FRMNUM_FRNM_MASK;
    }

    /* Store the frame # in the caller's parameters.  */
    *frame_number = hcd_synergy -> ux_hcd_synergy_frame_number;

    return (UX_SUCCESS);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

