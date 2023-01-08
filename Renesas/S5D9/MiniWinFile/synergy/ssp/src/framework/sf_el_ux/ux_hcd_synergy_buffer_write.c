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
/*    ux_hcd_synergy_buffer_write                         PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function writes a buffer to the specified PIPE                 */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*    ed                                    Register to the ed            */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                                              */ 
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
 * @brief  This function writes data to the selected FIFO of the endpoint.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in]      ed          : Pointer to a physical Endpoint(ED) control block
 *
 * @retval UX_SUCCESS     Buffer written to the specified PIPE successfully.
 *
 * @return                See @ref Common_Error_Codes for other possible return codes or causes.
 *                        This function calls:
 *                        * ux_hcd_synergy_fifod_write()
 *                        * ux_hcd_synergy_fifoc_write()
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_buffer_write(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed)
{
    UINT    status =  UX_SUCCESS;

    /* We are doing a write. Set the Direction bit in the DCPCFG register.  */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCFG, (USHORT)UX_SYNERGY_HC_DCPCFG_DIR);

    /* Select the fifo.  */
    switch (ed -> ux_synergy_fifo_index)
    {
        case UX_SYNERGY_HC_FIFO_D0 :
        case UX_SYNERGY_HC_FIFO_D1 :
        
            /* Write to the FIFO D0 or D1.  */
            status = ux_hcd_synergy_fifod_write(hcd_synergy, ed);
            break;

        case UX_SYNERGY_HC_FIFO_C :
        
            /* Write to the FIFO C1.  */
            status = ux_hcd_synergy_fifoc_write(hcd_synergy, ed);
            break;

        default :
            break;
    }

    /* Analyze return status.  */
    switch (status)
    {
        case UX_SYNERGY_HC_FIFO_WRITING :

            /* Enable the Ready interrupt.  */
            ux_hcd_synergy_buffer_ready_interrupt(hcd_synergy, ed, (ULONG)UX_SYNERGY_ENABLE);
            break;      

        case UX_SYNERGY_HC_FIFO_WRITE_END :
        case UX_SYNERGY_HC_FIFO_WRITE_SHORT :

            /* Disable the Ready interrupt.  */
            ux_hcd_synergy_buffer_ready_interrupt(hcd_synergy, ed, (ULONG)UX_SYNERGY_DISABLE);

            /* Enable the Buffer empty interrupt.  */
            ux_hcd_synergy_buffer_empty_interrupt(hcd_synergy, ed, (ULONG)UX_SYNERGY_ENABLE);

            break;      

        case UX_SYNERGY_HC_FIFO_WRITE_DMA :
            break;

        case UX_SYNERGY_HC_FIFO_WRITE_ERROR :
        default :

            /* Disable the Ready interrupt.  */
            ux_hcd_synergy_buffer_ready_interrupt(hcd_synergy, ed, (ULONG)UX_SYNERGY_DISABLE);

            /* Disable the Buffer empty interrupt.  */
            ux_hcd_synergy_buffer_empty_interrupt(hcd_synergy, ed, (ULONG)UX_SYNERGY_DISABLE);

            break;      
    }

    /* Return to caller. */
    return (status);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

