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
#include "ux_utility.h"

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function adds a transfer descriptor to an Isochronous Endpoint Descriptor.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to an Endpoint control block
 *
 * @retval UX_SUCCESS            A transfer descriptor was added to an Isochronous Endpoint Descriptor successfully.
 * @retval Others                See @ref Common_Error_Codes for other possible return codes or causes.
 *                               This function calls : ux_hcd_synergy_buffer_write()
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_iso_td_add(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed)
{
    UX_SYNERGY_ISO_TD  * current_td;
    UINT                 status;
    
    /* Get transmit descriptors. */
    current_td = (UX_SYNERGY_ISO_TD *) ed->ux_synergy_ed_head_td;
    
    /* Set TD into response pending state. */
    current_td -> ux_synergy_iso_td_status |=  UX_SYNERGY_TD_ACK_PENDING;
    
    /* Set PIPEx FIFO in in status. */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)ed -> ux_synergy_pipe_index);

    /* Set PID to NAK. */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                (USHORT)UX_SYNERGY_HC_PIPECTR_PID_MASK);
        
    /* Check the direction of the transfer. */
    if (current_td -> ux_synergy_iso_td_direction == UX_SYNERGY_TD_IN)
    {
        /* Enable the BRDY interrupt.  */
        ux_hcd_synergy_buffer_ready_interrupt(hcd_synergy, ed, (ULONG)UX_SYNERGY_ENABLE);
           
        /* Enable the NRDY interrupt.  */
        ux_hcd_synergy_buffer_notready_interrupt(hcd_synergy, ed, (ULONG)UX_SYNERGY_ENABLE);
    
        /* Start transmission - set PID to NAK  then  set PID to BUF. */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                                        (USHORT)UX_SYNERGY_HC_PIPECTR_PIDBUF);
    
        /* Set the ED in the ed array.  */
        hcd_synergy -> ux_hcd_synergy_ed_ptr[ed -> ux_synergy_pipe_index] = ed;
    }       
    else 
    {
        /* Must be an OUT now.  */                              
        if ( current_td -> ux_synergy_iso_td_direction == UX_SYNERGY_TD_OUT)
        {
            /* Write the buffer to the pipe.  */
            status =  ux_hcd_synergy_buffer_write(hcd_synergy, ed);

            /* Check status.  */
            if (status != (UINT)UX_ERROR)
            {
                /* If no error, we can set the pipe PID_BUF flag.  */
                ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                                        (USHORT)UX_SYNERGY_HC_PIPECTR_PIDBUF);
            }
        }
    }        

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
