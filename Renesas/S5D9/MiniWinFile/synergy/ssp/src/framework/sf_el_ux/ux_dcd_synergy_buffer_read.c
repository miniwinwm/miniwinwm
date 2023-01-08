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
#include "ux_dcd_synergy.h"
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
/*    ux_dcd_synergy_buffer_read                          PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function reads from a specified pipe into a buffer.            */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    dcd_synergy                           Pointer to synergy controller */ 
/*    ed                                    Register to the ed            */ 
/*    transfer_request                      Transfer request              */ 
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
/*    SYNERGY Controller Driver                                           */
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
 * @brief  This function reads from a specified pipe into a buffer.
 *
 * @param[in]  dcd_synergy  Pointer to a DCD control block
 * @param[in]  ed           Pointer to a physical Endpoint(ED) control block
 *
 * @retval UX_SUCCESS     Read a data from buffer successfully.
 * @retval UX_ERROR       Unable to read a data from buffer.
 *
 * @return                See @ref Common_Error_Codes for other possible return codes or causes.
 *                        This function calls:
 *                        * ux_dcd_synergy_fifo_read()
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_buffer_read(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed)
{
    UINT    status;
    
    /* Read from the FIFO C or D0 or D1.  */
    status = ux_dcd_synergy_fifo_read(dcd_synergy, ed);

    /* Analyze return status.  */
    switch (status)
    {
        case UX_SYNERGY_DCD_FIFO_READING:
            /* Enable the Ready interrupt.  */
            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_ENABLE);
            
            /* Operation was OK.  */
            status = (UINT)UX_SUCCESS;
            
            break;      

        case UX_SYNERGY_DCD_FIFO_READ_END:
        case UX_SYNERGY_DCD_FIFO_READ_SHORT:
            /* Disable the Ready interrupt.  */
            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
            
            /* Operation was OK.  */
            status = (UINT)UX_SUCCESS;
            
            break;      
        
        case UX_SYNERGY_DCD_FIFO_READ_DMA:
            break;
            
        case UX_SYNERGY_DCD_FIFO_READ_ERROR:
        default:
            /* Disable the Ready interrupt.  */
            ux_dcd_synergy_buffer_ready_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
            
            /* Disable the Buffer empty interrupt.  */
            ux_dcd_synergy_buffer_empty_interrupt(dcd_synergy, ed, UX_DCD_SYNERGY_DISABLE);
            
            /* Operation was not OK.  */
            status = (UINT)UX_ERROR;
            
            break;
    }

    /* Return to caller. */
    return (status);
}
 /*******************************************************************************************************************//**
  * @} (end addtogroup sf_el_ux)
  **********************************************************************************************************************/

