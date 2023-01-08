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

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_asynch_queue_process_brdy            PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function process the BRDY event that occured on a specific ED  */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                    Pointer to Synergy controller        */
/*    ed                             Endpoint on which the event happened */
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
 * @brief  This function process the BRDY(Buffer Ready)interrupt that occurred on a specific ED.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to an Endpoint control block
 *********************************************************************************************************************/
VOID  ux_hcd_synergy_asynch_queue_process_brdy(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED  *ed)
{
    UX_SYNERGY_TD            *td;
    UX_SYNERGY_TD            *next_td;
    UX_TRANSFER         *transfer_request;
    ULONG               actual_length;
    ULONG               synergy_register;

    /* Clear the status flag.  */
    hcd_synergy -> ux_hcd_synergy_ed_irq[ed -> ux_synergy_pipe_index] =
            hcd_synergy -> ux_hcd_synergy_ed_irq[ed -> ux_synergy_pipe_index] &
            (~(UX_SYNERGY_HC_ED_BRDY | UX_SYNERGY_HC_ED_BEMP));

    /* Get the TD associated with this transfer. */
    td = ed -> ux_synergy_ed_head_td;
    
    /* Ensure the interrupt was valid.  */
    if ((td -> ux_synergy_td_status & UX_SYNERGY_TD_ACK_PENDING) == 0)
    {
        return;
    }

    /* Get the transfer request associated with the TD.  */                          
    transfer_request =  td -> ux_synergy_td_transfer_request;

    /* We have a special case for endpoint index 0.  */
    if(ed -> ux_synergy_endpoint_index == 0UL)
    {
        /* Set to NAK. The pipe stops sending tokens. */
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_PID_MASK);
    
        /* Check the phase.  If SETUP, simply remove the TD. */
        if (td -> ux_synergy_td_status & UX_SYNERGY_TD_SETUP_PHASE)
        {
            /* Take the TD out of the Endpoint.  */
            ed -> ux_synergy_ed_head_td =  td -> ux_synergy_td_next_td;
    
            /* We can now free the TD used in this PTD.  */
            td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
        }
        else
        {
            /* Check the phase.  If DATA phase, check direction. We may need to read the
               buffer into the request_transfer buffer. */
            if (td -> ux_synergy_td_status & UX_SYNERGY_TD_DATA_PHASE)
            {
                /* Look at the direction.  If out, take out the TD from the link. */
                if (td -> ux_synergy_td_direction ==  UX_SYNERGY_TD_OUT)
                {
                    /* Take the TD out of the Endpoint.  */
                    ed -> ux_synergy_ed_head_td =  td -> ux_synergy_td_next_td;
        
                    /* We can now free the TD used in this PTD.  */
                    td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
                    
                    /* Update the transmitted length.  */
                    transfer_request -> ux_transfer_request_actual_length +=  td -> ux_synergy_td_length;
                }                
                else
                {
                    /* This is an IN transfer.  We need to read the buffer into the
                       transfer_request memory buffer.  */
                    ux_hcd_synergy_buffer_read(hcd_synergy, ed);
    
                    /* We need to read the length received.  */
                    actual_length =  td -> ux_synergy_td_actual_length;
    
                    /* Update the received length.  */
                    transfer_request -> ux_transfer_request_actual_length +=  actual_length;
                    
                    /* Clear the FIFO buffer memory */
                     ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR, UX_SYNERGY_HC_FIFOCTR_BCLR );
                     
                    /* Take the TD out of the Endpoint.  */
                    ed -> ux_synergy_ed_head_td =  td -> ux_synergy_td_next_td;
        
                    /* We can now free the TD used in this PTD.  */
                    td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
                    
                    /* Point to next TD.  */
                    td =  td -> ux_synergy_td_next_td;                     
    
                    /* Check the received length and see if we have a short packet.  */
                    if (transfer_request -> ux_transfer_request_actual_length != transfer_request ->ux_transfer_request_requested_length)
                    {
                        /* The transfer is not complete yet, check for short packet.  */
                        if ((actual_length == 0UL) || ((actual_length % ed -> ux_synergy_ed_endpoint ->ux_endpoint_descriptor.wMaxPacketSize) != 0UL))
                        {
                            /* Remove all the TDs attached to a DATA phase.  */
                            while (td != ed -> ux_synergy_ed_tail_td)
                            {
                                /* Check the TD phase.  */
                                if (td -> ux_synergy_td_status & UX_SYNERGY_TD_DATA_PHASE)
                                {
                                    /* Memorize this TD.  */
                                    next_td =  td -> ux_synergy_td_next_td;                     
    
                                    /* This is a DATA phase, take it out of the chain.  */
                                    ed -> ux_synergy_ed_head_td =  next_td;                     
    
                                    /* We can now free the TD.  */
                                    td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
    
                                    /* Next TD.  */
                                    td =  next_td;
                                }
                                else
                                {
                                    /* Next TD.  */
                                    td =  td -> ux_synergy_td_next_td;
                                }
                            }
                        }
                    }
                }    
            }
            else
            {
                /* Check the phase.  If STATUS phase, wake up the pending thread.  */
                if (td -> ux_synergy_td_status & UX_SYNERGY_TD_STATUS_PHASE)
                {
                    /* Check the direction.  */
                    if (td -> ux_synergy_td_direction ==  UX_SYNERGY_TD_IN)
                    {
                        /* Clear the FIFO buffer memory. */
                        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR, UX_SYNERGY_HC_FIFOCTR_BCLR);
                    }

                    /* Take the TD out of the Endpoint.  */
                    ed -> ux_synergy_ed_head_td =  td -> ux_synergy_td_next_td;
            
                    /* We can now free the TD used in this PTD.  */
                    td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
        
                    /* Set the transfer code to completed.  */
                    transfer_request -> ux_transfer_request_completion_code = (UINT)UX_SUCCESS;
        
                    /* Check if there is a callback.  */
                    if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
                    {
                        /* Yes, so execute it.  */
                        transfer_request -> ux_transfer_request_completion_function(transfer_request);
                    }

                    /* Wake up the thread waiting for this event to complete.  */
                    _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);
                }
            }
        }
    }
    else
    {
        /* Select pipe.  */
        ux_hcd_synergy_register_write( hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)ed -> ux_synergy_pipe_index);
    
        /* The toggle bit expected for the next transfer has to be memorized if the toggle
           is derived from the ED value.  */
        if (td -> ux_synergy_td_toggle ==  UX_SYNERGY_TD_TOGGLE_FROM_ED)
        {
            /* Read the PIPCxCTR register.  */
            synergy_register =  ux_hcd_synergy_register_read(hcd_synergy,
                                                    UX_SYNERGY_HC_PIPE1CTR + ((ed -> ux_synergy_pipe_index - 1UL) * 2UL));
    
            /* Check the SQMON bit from the PIPExCTR register.  */
            if (synergy_register & UX_SYNERGY_HC_PIPECTR_SQMON)
            {
                /* Next phase is DATA1.  */
                ed -> ux_synergy_ed_toggle = 1UL;
            }
            else
            {
                /* Next phase is DATA0.  */
                ed -> ux_synergy_ed_toggle = 0UL;
            }
        }

        /* Set PIPEx to NAK. The pipe stops sending tokens. */
        ux_hcd_synergy_register_clear(hcd_synergy,  UX_SYNERGY_HC_PIPE1CTR +((ed -> ux_synergy_pipe_index - 1UL) * 2UL),
                                                    (USHORT)UX_SYNERGY_HC_DCPCTR_PID_MASK);
        
        /* We are dealing with a non 0 endpoint.  Check the direction.  */
        if (td -> ux_synergy_td_direction ==  UX_SYNERGY_TD_OUT)
        {
            /* Add the length transmitted to the total.  */
            transfer_request -> ux_transfer_request_actual_length +=  td -> ux_synergy_td_length;
                        
            /* Check the transmission is complete.  */
            if (transfer_request -> ux_transfer_request_actual_length == transfer_request -> ux_transfer_request_requested_length)
            {
                /* Set the transfer code to completed.  */
                transfer_request -> ux_transfer_request_completion_code = (UINT)UX_SUCCESS;

                /* Check if there is a callback.  */
                if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
                {
                    /* Yes, so execute it.  */
                    transfer_request -> ux_transfer_request_completion_function(transfer_request);
                }

                /* Wake up the thread waiting for this event to complete.  */
                _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);
            }       

            /* Take the TD out of the Endpoint.  */
            ed -> ux_synergy_ed_head_td =  td -> ux_synergy_td_next_td;
    
            /* We can now free the TD used in this PTD.  */
            td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
        
        }                                      
        else
        {
            /* This is an IN transfer.  We need to read the buffer into the
               transfer_request memory buffer.  */
            ux_hcd_synergy_buffer_read(hcd_synergy, ed);
            
            /* We need to read the length received.  */
            actual_length =  td -> ux_synergy_td_actual_length;

            /* Update the received length.  */
            transfer_request -> ux_transfer_request_actual_length +=  actual_length;

             /*Clear FIFOC buffer memory*/
             ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR, UX_SYNERGY_HC_FIFOCTR_BCLR );


            /* Check the received length and see if we have a short packet or if we are finished with this transfer.  */
             if ((transfer_request -> ux_transfer_request_actual_length == transfer_request -> ux_transfer_request_requested_length)
                || (actual_length == 0UL)
                || ((actual_length % ed -> ux_synergy_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize) != 0UL))
            {
                /* Remove all the TDs attached.  */
                while (td != ed -> ux_synergy_ed_tail_td)
                {
                    /* Memorize this TD.  */
                    next_td =  td -> ux_synergy_td_next_td;                     

                    /* Take it out of the chain.  */
                    ed -> ux_synergy_ed_head_td =  next_td;                     

                    /* We can now free the TD.  */
                    td -> ux_synergy_td_status = (ULONG)UX_UNUSED;

                    /* Next TD.  */
                    td =  next_td;
                }
                
                /* Set the transfer code to completed.  */
                transfer_request -> ux_transfer_request_completion_code = (UINT)UX_SUCCESS;

                /* Check if there is a callback.  */
                if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
                {
                    /* Yes, so execute it.  */
                    transfer_request -> ux_transfer_request_completion_function(transfer_request);
                }

                /* Wake up the thread waiting for this event to complete.  */
                _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);
            }
            else
            {
                /* Take the TD out of the Endpoint.  */
                ed -> ux_synergy_ed_head_td =  td -> ux_synergy_td_next_td;
    
                /* We can now free the TD used in this PTD.  */
                td -> ux_synergy_td_status = (ULONG)UX_UNUSED;
            }
        }
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

