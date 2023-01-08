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

#define UX_SOURCE_CODE


/* Include necessary system files.  */

#include "ux_api.h"
#include "ux_dcd_synergy.h"
#include "ux_device_stack.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "sf_el_ux_dcd_hs_cfg.h"
#include "sf_el_ux_dcd_fs_cfg.h"

#include "bsp_api.h"
#include "r_cgc.h"


/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    ux_dcd_synergy_initialize                             PORTABLE C    */
/*                                                             5.6        */
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function un-initializes the USB slave controller of the Renesas*/
/*    Synergy chipset.                                                    */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd                                   Address of DCD                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */ 
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_dcd_synergy_register_clear         Clear register                */
/*    _ux_utility_memory_free               Deallocate memory             */
/*                                                                        */ 
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


/******************************************************************************************************************//**
 * @brief  USBX DCD disconnect the USB controller communication from the host.
 **********************************************************************************************************************/
void ux_dcd_synergy_disconnect(void)
{
    UX_SLAVE_DCD        * dcd;
    UX_DCD_SYNERGY      * dcd_synergy;

    /* Get the pointer to the DCD.  */
    dcd =  &_ux_system_slave -> ux_system_slave_dcd;

    /* Get the pointer to the Synergy DCD.  */
    dcd_synergy = (UX_DCD_SYNERGY *)dcd -> ux_slave_dcd_controller_hardware;

    /* Detach USB.  */
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, (USHORT)UX_SYNERGY_DCD_SYSCFG_DPRPU);

    if (dcd_synergy -> ux_dcd_synergy_base == R_USBFS_BASE)
     {
         /* Release D- pull up */
         ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_DMRPU);
     }
     else
     {
         /* clear DRPD bit to 0 in Device mode. */
         ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_DRPD);
     }

    /* Delay.  */
    _ux_utility_delay_ms(20UL);
}

/******************************************************************************************************************//**
 * @brief  USBX DCD un-initialization the USB controller.
 *
 * @param[in]  dcd_io                        Address of the USB controller.
 *
 * @retval     UX_SUCCESS                    Completed the USB controller Un-initialization successfully.
 * @retval     UX_DCD_SYNERGY_UNINIT_FAILED  Failed to Un-initialize the USB controller.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_uninitialize (ULONG dcd_io)
{
    UX_DCD_SYNERGY      * dcd_synergy;
    UX_SLAVE_DCD        * dcd;

    ssp_signal_t          signal;
    ssp_feature_t         ssp_feature = {{(ssp_ip_t) 0U}};
    fmi_event_info_t      event_info  = {(IRQn_Type) 0U};
    UINT                  status = SSP_SUCCESS;

#if defined(R_USBHS_BASE)
    if ( (dcd_io != R_USBHS_BASE) && (dcd_io != R_USBFS_BASE) )
#else
    if  (dcd_io != R_USBFS_BASE)
#endif
    {
        /* Error trap. */
        _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_THREAD,
                                 (UINT)UX_SYSTEM_CONTEXT_DCD, (UINT)UX_DCD_SYNERGY_UNINIT_FAILED);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_DCD_SYNERGY_UNINIT_FAILED, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

        /* Return failure status  */
        return (UINT)UX_DCD_SYNERGY_UNINIT_FAILED;
    }

    /* Get the pointer to the DCD.  */
    dcd =  &_ux_system_slave -> ux_system_slave_dcd;

    /* Get the pointer to the Synergy DCD.  */
    dcd_synergy = (UX_DCD_SYNERGY *)dcd -> ux_slave_dcd_controller_hardware;

    /** Disable interrupt requests */
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_INTENB0,
                                (UX_SYNERGY_DCD_INTENB0_VBSE  |
                                 UX_SYNERGY_DCD_INTENB0_DVSE  |
                                 UX_SYNERGY_DCD_INTENB0_CTRE  |
                                 UX_SYNERGY_DCD_INTENB0_BEMPE |
                                 UX_SYNERGY_DCD_INTENB0_NRDYE |
                                 UX_SYNERGY_DCD_INTENB0_BRDYE));

    if( (NULL != dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx) || (NULL != dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx) )
    {
    	/** uninitialize and disable DMA support  */
        status = ux_dcd_synergy_uninitialize_transfer_support(dcd_io);
        /* return an error, if DMA uninitialization is failed  */
        if(status != SSP_SUCCESS)
        {
            return (UINT)status;
        }
    }

#if ( !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA) )
    for (UCHAR pipenum=1U; pipenum <= (UCHAR)UX_DCD_SYNERGY_MAX_PIPE; pipenum++)
    {
        /** Delete the semaphores*/
        _ux_utility_semaphore_delete(&(dcd_synergy->ux_dcd_synergy_ed[pipenum].ux_dcd_synergy_ep_slave_transfer_request_semaphore));
    }
#endif

#if defined(UX_DCD_FS_LDO_ENABLE)
    /* Set USB regulator OFF */
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_USBMC, (USHORT)UX_SYNERGY_DCD_USBMC_VDCEN);
#endif

#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
    /* Set OFF the USB clock(HOCO) for S1 MCUs */
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_UCKSEL, (USHORT)UX_SYNERGY_DCD_UCKSEL_UCKSELC);
#endif

    if (dcd_io == R_USBFS_BASE)
    {
        /** Stop the clock to the USB module. The SCKE clearing is required for USBFS controller but not for USBHS */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_SCKE);
    }

    /** Reset USB Module.  */
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, (USHORT)UX_SYNERGY_DCD_SYSCFG_USBE);


    ssp_feature.id      = SSP_IP_USB;
    ssp_feature.channel = 0U;

#if defined(R_USBHS_BASE)
    if (dcd_io == R_USBHS_BASE)
    {
        /* Clear UTMI normal mode */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_LPSTS, (USHORT)UX_SYNERGY_DCD_LPSTS_SUSPENDM);

        /* Disable the High-speed mode */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_HSE);

        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_0);
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_1);

        /* Set the Bus wait cycles to default */
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_BUSWAIT,  UX_SYNERGY_DCD_BUSWAIT_DEFAULT_VAL);

        ssp_feature.unit = (uint32_t) SSP_IP_UNIT_USBHS;
        signal  = SSP_SIGNAL_USB_USB_INT_RESUME;
    }
    else
    {
#endif
        ssp_feature.unit = (uint32_t) SSP_IP_UNIT_USBFS;
        signal  = SSP_SIGNAL_USB_INT;
#if defined(R_USBHS_BASE)
    }
#endif

    g_fmi_on_fmi.eventInfoGet(&ssp_feature, signal, &event_info);
    if (SSP_INVALID_VECTOR != event_info.irq)
    {
        /** Clear the Pending IRQ in NVIC */
        NVIC_ClearPendingIRQ(event_info.irq);
        /** Disable the IRQ in NVIC */
        NVIC_DisableIRQ(event_info.irq);
    }
    
    /** Stop the module usage */
    R_BSP_ModuleStop(&ssp_feature);

    /** Free up resource.  */
     _ux_utility_memory_free(dcd_synergy);

     /* Reset DCD fields.  */
      dcd -> ux_slave_dcd_status = (UINT) UX_UNUSED;
      dcd -> ux_slave_dcd_controller_type =  0U;
      dcd -> ux_slave_dcd_controller_hardware = UX_NULL;
      dcd -> ux_slave_dcd_io = 0U;
      dcd -> ux_slave_dcd_function = UX_NULL;

    /* Return status  */
    return (UINT)status;
}

/******************************************************************************************************************//**
 * @brief  The function un-initializes the USB slave controller of the Renesas Synergy MCUs with associated DMA transfer
 *         modules.

 * @param[in]  dcd_io                        Address of the USB controller.

 * @retval     UX_SUCCESS                    Completed the USB controller Un-initialization successfully.
 * @retval     UX_DCD_SYNERGY_UNINIT_FAILED  Failed to Un-initialize the USB controller.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_uninitialize_transfer_support (ULONG dcd_io)
{
    UINT                status = SSP_SUCCESS;
    ssp_err_t           ssp_err;
    UX_SLAVE_DCD      * dcd = &_ux_system_slave -> ux_system_slave_dcd;
    UX_DCD_SYNERGY    * dcd_synergy;

    SSP_PARAMETER_NOT_USED(dcd_io);

    /* Get the pointer to the Synergy DCD instance.  */
    dcd_synergy = (UX_DCD_SYNERGY *)dcd->ux_slave_dcd_controller_hardware;

    if (NULL != dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx)
    {
        _ux_utility_semaphore_delete(&dcd_synergy->dma_tx_completion_semaphore);

        /* Close Transfer module for transmission. */
        ssp_err = dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_api->close(
                dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl);
        if(ssp_err != SSP_SUCCESS)
        {
            status = (UINT)UX_DCD_SYNERGY_UNINIT_FAILED;
        }

        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->dest_addr_mode = (transfer_addr_mode_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->src_addr_mode  = (transfer_addr_mode_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->repeat_area    = (transfer_repeat_area_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->mode           = (transfer_mode_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->irq            = (transfer_irq_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.activation_source      = (elc_event_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.auto_enable            = (bool) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_callback             = UX_NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_context              = (void *) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.irq_ipl                = 0U;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_extend               = (void *) NULL;
    }

    if (NULL != dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx)
    {
        _ux_utility_semaphore_delete(&dcd_synergy->dma_rx_completion_semaphore);

        ssp_err = dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_api->close(
                dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_ctrl);
        if(ssp_err != SSP_SUCCESS)
        {
            status = (UINT)UX_DCD_SYNERGY_UNINIT_FAILED;
        }

        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->dest_addr_mode = (transfer_addr_mode_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->src_addr_mode  = (transfer_addr_mode_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->repeat_area    = (transfer_repeat_area_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->mode           = (transfer_mode_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.activation_source      = (elc_event_t) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.auto_enable            = (bool) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_callback             = UX_NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_context              = (void *) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.irq_ipl                = 0U;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_extend               = (void *) NULL;
        dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->irq            = (transfer_irq_t) NULL;
    }

    /* Return successful completion.  */
    return status;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

