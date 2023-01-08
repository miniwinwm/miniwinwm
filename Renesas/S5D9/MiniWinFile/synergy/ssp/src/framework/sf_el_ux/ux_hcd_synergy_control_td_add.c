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
/*    ux_hcd_synergy_control_td_add                       PORTABLE C      */
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*     This function adds a transfer descriptor to an ED                  */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_synergy                           Pointer to Synergy controller */
/*    ed                                    Pointer to ED                 */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_utility_memory_copy               Copy memory block             */ 
/*    _ux_utility_memory_set                Set memory block              */ 
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
 * @brief  This function adds a transfer descriptor to an ED.
 *
 * @param[in,out]  hcd_synergy : Pointer to a HCD control block
 * @param[in,out]  ed          : Pointer to Synergy  ED structure
 *
 * @retval UX_SUCCESS            Transfer descriptor added to an ED successfully.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_control_td_add(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed)
{
    UX_SYNERGY_TD        *current_td;
    USHORT          register_value;
    ULONG           device_address;
    UINT            status;
    ULONG           current_status;
    ULONG           hubport_status;

    /** Get transmit descriptors. */
    current_td =  ed->ux_synergy_ed_head_td;

    /** Set TD into response pending state. */
    current_td -> ux_synergy_td_status |=  UX_SYNERGY_TD_ACK_PENDING;

    /** Check data, status for setup phase. */
    if (current_td -> ux_synergy_td_status &  UX_SYNERGY_TD_SETUP_PHASE)
    {
        /** We are processing a SETUP phase.  
           Set the device address register if different. */
        device_address = ed -> ux_synergy_ed_endpoint -> ux_endpoint_device -> ux_device_address;

        /** And store it.  Note that the device address is not an index.  */
        ux_hcd_synergy_register_write(hcd_synergy, ((ULONG)UX_SYNERGY_HC_DEVADD0 + (2UL * device_address)),
                                                                        ed->ux_synergy_devaddm_val);

        /** DEVADDm.USBSPD[1:0] is set by the Software after the speed of the device is obtained and reset after
         * connecting/disconnecting the device every time. To set the TRNENSEL bit, when LS device is connected to
         * FS Hub, we are indirectly examining the speed of the device by examining DEVADDm.USBSPD[1:0].
         */

        /* Read the USBSPD[1:0] bits of DEVADD1 register */
        current_status = ((ux_hcd_synergy_register_read(hcd_synergy, ((ULONG)UX_SYNERGY_HC_DEVADD1))) & UX_SYNERGY_HC_DEVADD_SPEED_HIGH);

        /** Check if the speed of the connected HUB is FS  */
        if ((UX_SYNERGY_HC_DEVADD_SPEED_FULL == current_status))
        {
            /* Read the HUBPORT[2:0] bits of DEVADDm register */
            hubport_status = ((ux_hcd_synergy_register_read(hcd_synergy, ((ULONG)UX_SYNERGY_HC_DEVADD0 + (2UL * device_address)))) & UX_SYNERGY_HC_DEVADD_HUBPORT_BIT_SHIFT);
            /*Read the USBSPD[1:0] bits of DEVADDm register */
            current_status = ((ux_hcd_synergy_register_read(hcd_synergy, ((ULONG)UX_SYNERGY_HC_DEVADD0 + (2UL * device_address)))) & UX_SYNERGY_HC_DEVADD_SPEED_HIGH);

            /* Check if the hub is connected and the device connected to the FS hub is LS */
            if ((UX_SYNERGY_HC_DEVADD_SPEED_LOW == current_status) && (0UL != hubport_status))
            {
                /* Switch the timing of token issue matching to low-speed mode. */
                ux_hcd_synergy_register_set(hcd_synergy,
                                            UX_SYNERGY_HC_SOFCFG, (USHORT)UX_SYNERGY_HC_SOFCFG_TRNENSEL);
            }
        }

        /** Clear the address field first.  */
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DCPMAXP, UX_SYNERGY_HC_DCPMAXP_DEVADDR_MASK);

        /** Store the new address but leave the MPS field intact.  */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPMAXP,
                                                    (USHORT)((device_address << UX_SYNERGY_HC_DCPMAXP_DEVADDR_SHIFT)));

        /** Set the buffer address to be accessed.  */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_DATA0);

        /** Copy the payload of the control transfer into each register : Request.  */
        register_value = (USHORT) _ux_utility_short_get( (current_td -> ux_synergy_td_buffer));
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_USBREQ, register_value);

        /** Copy the payload of the control transfer into each register : Value.  */
        register_value = (USHORT) _ux_utility_short_get( (current_td -> ux_synergy_td_buffer) + 2 );
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_USBVAL, register_value);

        /** Copy the payload of the control transfer into each register : Index.  */
        register_value = (USHORT) _ux_utility_short_get( (current_td -> ux_synergy_td_buffer) + 4 );
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_USBINDX, register_value);

        /** Copy the payload of the control transfer into each register : Length.  */
        register_value = (USHORT) _ux_utility_short_get( (current_td -> ux_synergy_td_buffer) + 6 );
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_USBLENG, register_value);

        /* DCP -  PIPE0 */
        hcd_synergy -> ux_hcd_synergy_ed_ptr[0] = ed;

        /* Set Toggle to DATA1.  */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_DATA1);

        /** Start transmission. */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_SUREQ);

    }
    else     
    {
         /** We are processing data/status stage of control transfer.  Check direction now.  */
        if (current_td -> ux_synergy_td_direction == UX_SYNERGY_TD_IN)
        {
            /** This is an IN. Reset the PID mask register.  */
            ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_PID_MASK);

            /** Set PIPE0 FIFO in in status. */
            ux_hcd_synergy_current_endpoint_change(hcd_synergy, ed, 0);

            /** Set DATA0-DATA1 toggle. */
            if (current_td -> ux_synergy_td_toggle == 0UL)
            {
                /* Set Toggle to DATA0.  */
                 ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_DATA0);
            }
            else
            {
                /* Set Toggle to DATA1.  */
                 ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_DATA1);
            }

            /** We are doing a read. Reset the Direction bit in the DCPCFG register.  */
            ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DCPCFG, (USHORT)UX_SYNERGY_HC_DCPCFG_DIR);
                    
            /** Clear the FIFO buffer memory. */
            ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR, (USHORT)UX_SYNERGY_HC_FIFOCTR_BCLR);

            /** Enable the Buffer empty interrupt.  */
            ux_hcd_synergy_buffer_empty_interrupt(hcd_synergy, ed, UX_SYNERGY_ENABLE);

            /** Enable the Ready interrupt.  */
            ux_hcd_synergy_buffer_ready_interrupt(hcd_synergy, ed, UX_SYNERGY_ENABLE);
            
            /** Start transmission - set PID to NAK  then  set PID to BUF. */
            ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_PIDBUF);
        }
        else 
        {
            /** Must be an OUT now.  */                              
            if ( current_td -> ux_synergy_td_direction == UX_SYNERGY_TD_OUT )
            {
                /** Clear the FIFO buffer memory. */
                ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_CFIFOCTR, (USHORT)UX_SYNERGY_HC_FIFOCTR_BCLR);
                
                /** Set PID to NAK.  */
                ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_PID_MASK);

                /** Set DATA0-DATA1 toggle. */
                if (current_td -> ux_synergy_td_toggle == 0UL)
                {
                    /* Set Toggle to DATA0.  */
                     ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_DATA0);
                }
                else
                {
                    /* Set Toggle to DATA1.  */
                     ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_DATA1);
                }

                /** Write the buffer to the pipe.  */
                status =  ux_hcd_synergy_buffer_write(hcd_synergy, ed);

                /** Check status.  */
                if (status != (UINT)UX_ERROR)
                {
                    /* If no error, we can set the pipe PID_BUF flag.  */
                    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DCPCTR, (USHORT)UX_SYNERGY_HC_DCPCTR_PIDBUF);
                }
            }
        }
    }       

    /** Return successful completion.  */
    return (UINT)UX_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

