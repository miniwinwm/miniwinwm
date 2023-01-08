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

static UINT ux_dcd_synergy_initialize_common (ULONG dcd_io);

static void ux_dcd_synergy_initialize_common_complete (void);

static void ux_dcd_dma_complete_tx (transfer_callback_args_t * p_args);

static void ux_dcd_dma_complete_rx (transfer_callback_args_t * p_args);

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
/*    This function initializes the USB slave controller of the Renesas   */
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
/*    ux_dcd_synergy_register_write         Read register                 */
/*    _ux_utility_memory_allocate           Allocate memory               */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    USBX Device Stack                                                   */ 
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
 * @brief  This function initializes the USB slave controller for Renesas Synergy MCUs.
 *
 * @param[in,out]  dcd_io Address of DCD
 *
 * @return           See @ref Common_Error_Codes for other possible return codes or causes.
 *
 *                   This function calls:
 *                   * ux_dcd_synergy_initialize_common()
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_initialize(ULONG dcd_io)
{
    UINT            status;

    status = ux_dcd_synergy_initialize_common (dcd_io);
    if (UX_SUCCESS == status)
    {
        ux_dcd_synergy_initialize_common_complete ();
    }

    return status;
}

/******************************************************************************************************************//**
 * @brief  The function initializes the USB slave controller of the Renesas Synergy MCUs with associated DMA transfer
 *         modules.

 * @param[in]  dcd_io                      Address of the USB controller.
 * @param[in]  p_transfer_instance         Pointer to Synergy Transfer module instances.

 * @retval     UX_SUCCESS                  Completed the USB controller initialization successfully.
 * @retval     UX_CONTROLLER_INIT_FAILED   Failed to initialize the USB controller.
 * @retval     UX_MEMORY_INSUFFICIENT      Memory was not allocated properly for the Synergy DCD instance.
 **********************************************************************************************************************/
UINT  ux_dcd_synergy_initialize_transfer_support (ULONG dcd_io, UX_DCD_SYNERGY_TRANSFER * p_transfer_instance)
{
    UINT                status;
    ssp_err_t           ssp_err;
    UX_SLAVE_DCD      * dcd = &_ux_system_slave -> ux_system_slave_dcd;
    UX_DCD_SYNERGY    * dcd_synergy;
    UINT                sem_create_status;

    status = ux_dcd_synergy_initialize_common (dcd_io);
    if (UX_SUCCESS == status)
    {
        /** Get the pointer to the Synergy DCD instance.  */
        dcd_synergy = (UX_DCD_SYNERGY *)dcd->ux_slave_dcd_controller_hardware;

        /** To begin, initialize D0 and D1 FIFO as free. */
        dcd_synergy -> ux_dcd_synergy_D0_fifo_state = UX_DCD_SYNERGY_FIFO_FOR_DMA_FREE;
        dcd_synergy -> ux_dcd_synergy_D1_fifo_state = UX_DCD_SYNERGY_FIFO_FOR_DMA_FREE;

        /** Initialize Transfer instances. */
        if (NULL != p_transfer_instance)
        {
            if (NULL != p_transfer_instance->ux_synergy_transfer_tx)
            {
                dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx =
                        (transfer_instance_t *) p_transfer_instance->ux_synergy_transfer_tx;

                /** Setup the Transfer module for transmission. */
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info   =
                        dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->p_info;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->mode           = TRANSFER_MODE_BLOCK;

                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_info->irq = TRANSFER_IRQ_END;
#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
                /** DTC is not supported in S1 series - so no need of activation source*/
#else
#if defined(R_USBHS_BASE)
                if (dcd_io == R_USBHS_BASE)
                {
                   dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.activation_source      = ELC_EVENT_USBHS_FIFO_0;
                }
                else
                {
                    dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.activation_source      = ELC_EVENT_USBFS_FIFO_0;
                }
#else
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.activation_source      = ELC_EVENT_USBFS_FIFO_0;
#endif
#endif
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.auto_enable            = false;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_callback             = ux_dcd_dma_complete_tx;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_context              = dcd_synergy;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.irq_ipl  =
                        dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->irq_ipl;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_tx.p_extend =
                        dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->p_extend;

                sem_create_status = _ux_utility_semaphore_create(&dcd_synergy->dma_tx_completion_semaphore,
                                                                 "dma_tx_completion_sem", 0);
                if(TX_SUCCESS != sem_create_status)
                {
                    return (UINT)UX_SEMAPHORE_ERROR;
                }
                /** Clear the DMA transfer end callback flag. */
                dcd_synergy->ux_dcd_synergy_dma_done_tx = 0;

                /** Open Transfer module for transmission. */
                ssp_err = dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_api->open(
                          dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl,
                          &dcd_synergy->ux_dcd_synergy_transfer_cfg_tx);
                if(ssp_err != SSP_SUCCESS)
                {
                    status = (UINT)UX_CONTROLLER_INIT_FAILED;
                }
            }
            if (NULL != p_transfer_instance->ux_synergy_transfer_rx)
            {
                dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx =
                        (transfer_instance_t *) p_transfer_instance->ux_synergy_transfer_rx;

                /** Setup the Transfer module for reception. */
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info   =
                        dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_cfg->p_info;
                /** Note address mode in rx is reverst of tx: 
                 * Destination (which is ram) is incremented and source (which is
                 * FIFO_1 buffer)
                 */
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->src_addr_mode  = TRANSFER_ADDR_MODE_FIXED;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->repeat_area    = TRANSFER_REPEAT_AREA_SOURCE;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->mode           = TRANSFER_MODE_BLOCK;
#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
                /** DTC is not supported in S1 series - so no need of activation source*/
#else
#if defined(R_USBHS_BASE)
                if (dcd_io == R_USBHS_BASE)
                {
                   dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.activation_source      = ELC_EVENT_USBHS_FIFO_1;
                }
                else
                {
                    dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.activation_source      = ELC_EVENT_USBFS_FIFO_1;
                }
#else
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.activation_source      = ELC_EVENT_USBFS_FIFO_1;
#endif
#endif
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.auto_enable            = false;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_callback             = ux_dcd_dma_complete_rx;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_context              = dcd_synergy;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.irq_ipl  =
                        dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_cfg->irq_ipl;
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_extend =
                        dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_cfg->p_extend;
                /* Wait till IRQ end */
                dcd_synergy->ux_dcd_synergy_transfer_cfg_rx.p_info->irq = TRANSFER_IRQ_END;

                sem_create_status = _ux_utility_semaphore_create(&dcd_synergy->dma_rx_completion_semaphore,
                                                                 "dma_rx_completion_sem", 0);
                if(TX_SUCCESS != sem_create_status)
                {
                    return (UINT)UX_SEMAPHORE_ERROR;
                }
                /** Clear the DMA transfer end callback flag. */
                dcd_synergy->ux_dcd_synergy_dma_done_rx = false;

                /** Open Transfer module for reception. */
                ssp_err = dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_api->open(
                          dcd_synergy->ux_dcd_synergy_transfer.ux_synergy_transfer_rx->p_ctrl,
                          &dcd_synergy->ux_dcd_synergy_transfer_cfg_rx);
                if(ssp_err != SSP_SUCCESS)
                {
                    status = (UINT)UX_CONTROLLER_INIT_FAILED;
                }
            }
        }

        ux_dcd_synergy_initialize_common_complete ();
    }

    /** Return successful completion.  */
    return status;
}

/******************************************************************************************************************//**
 * @brief  USBX DCD first half common part of the USB controller initialization.
 *
 * @param[in]  dcd_io                      Address of the USB controller.
 *
 * @retval     UX_SUCCESS                  Completed the USB controller initialization successfully.
 * @retval     UX_CONTROLLER_INIT_FAILED   Failed to initialize the USB controller.
 * @retval     UX_MEMORY_INSUFFICIENT      Memory was not allocated properly for the Synergy DCD instance.
 **********************************************************************************************************************/
static UINT  ux_dcd_synergy_initialize_common (ULONG dcd_io)
{
    UX_DCD_SYNERGY      * dcd_synergy;
    UX_SLAVE_DCD        * dcd;

    ssp_signal_t          signal;
    ssp_feature_t         ssp_feature = {{(ssp_ip_t) 0U}};
    fmi_event_info_t      event_info  = {(IRQn_Type) 0U};

    ssp_feature.id      = SSP_IP_USB;
    ssp_feature.channel = 0U;
    uint8_t irq_ipl     = (uint8_t)0xFF;
    ULONG                 synergy_register1;
    ULONG                 synergy_register2;
    ULONG                 synergy_register3;
#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
    UINT                  semaphore_create_status;
    CHAR                  transfer_status_semaphore[] = "semaphore_pipex";
#endif

     /** Perform Synergy specific FS component initialization */
#if defined(R_USBHS_BASE)
    if (dcd_io == R_USBHS_BASE)
    {
        ssp_feature.unit = (uint32_t) SSP_IP_UNIT_USBHS;
        signal  = SSP_SIGNAL_USB_USB_INT_RESUME;
        irq_ipl = (uint8_t)SF_EL_UX_DCD_CFG_HS_IRQ_IPL;
    }
    else
    {
#endif
        if (dcd_io == R_USBFS_BASE)
        {
            ssp_feature.unit = (uint32_t) SSP_IP_UNIT_USBFS;
            signal  = SSP_SIGNAL_USB_INT;
            irq_ipl = (uint8_t)SF_EL_UX_DCD_CFG_FS_IRQ_IPL;
        }
        else
        {
            /* Error trap. */
            _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_THREAD,
                                     (UINT)UX_SYSTEM_CONTEXT_DCD, (UINT)UX_CONTROLLER_INIT_FAILED);

            /* If trace is enabled, insert this event into the trace buffer.  */
            UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_CONTROLLER_INIT_FAILED, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

            return (UINT)UX_CONTROLLER_INIT_FAILED;
        }
#if defined(R_USBHS_BASE)
    }
#endif

    R_BSP_ModuleStart(&ssp_feature);

    g_fmi_on_fmi.eventInfoGet(&ssp_feature, signal, &event_info);
    if (SSP_INVALID_VECTOR != event_info.irq)
    {
        NVIC_SetPriority(event_info.irq, irq_ipl);
        NVIC_EnableIRQ(event_info.irq);
    }

    /** Get the pointer to the DCD.  */
    dcd =  &_ux_system_slave -> ux_system_slave_dcd;

    /* The controller initialized here is of synergy type.  */
    dcd -> ux_slave_dcd_controller_type =  UX_DCD_SYNERGY_SLAVE_CONTROLLER;
    
    /** Allocate memory for the Synergy DCD instance.  */
    dcd_synergy =  _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY, sizeof(UX_DCD_SYNERGY));

    /* Check if memory was properly allocated.  */
    if(dcd_synergy == UX_NULL)
    {
        return (UINT)UX_MEMORY_INSUFFICIENT;
    }

    /** Set the pointer to the synergy DCD.  */
    dcd -> ux_slave_dcd_controller_hardware =  (VOID *) dcd_synergy;

    /** Save the base address of the controller.  */
    dcd -> ux_slave_dcd_io =  dcd_io;
    dcd_synergy -> ux_dcd_synergy_base =  dcd_io;

    /** Set the generic DCD owner for the synergy DCD.  */
    dcd_synergy -> ux_dcd_synergy_dcd_owner =  dcd;

    /* Initialize the function collector for this DCD.  */
    dcd -> ux_slave_dcd_function =  ux_dcd_synergy_function;

#if    !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
    /** Create the semaphore (as this cannot be done in endpoint_create.c as it is called from 
       interrupt context) */
    for (ULONG pipenum= UX_DCD_SYNERGY_MIN_PIPE; pipenum <= UX_DCD_SYNERGY_MAX_PIPE; pipenum++)
    {
        /* Convert the pipe number to human readable ASCII format */
        transfer_status_semaphore[UX_DCD_SYNERGY_TX_SEMAPHORE_NAME_LENGTH] = (CHAR)(pipenum + (ULONG)'0');

        /* ux_dcd_synergy_ep_slave_transfer_request_semaphore is used for flagging the completion of the transfer */
        semaphore_create_status =  _ux_utility_semaphore_create
                                    (&(dcd_synergy->ux_dcd_synergy_ed[(UINT)pipenum].ux_dcd_synergy_ep_slave_transfer_request_semaphore),
                                     transfer_status_semaphore, 0);
        if (semaphore_create_status != (UINT)UX_SUCCESS)
        {
        	/* Delete the successfully created semaphores, as they are not useful anymore */
        	for (ULONG failed_pipenum= UX_DCD_SYNERGY_MIN_PIPE; failed_pipenum < pipenum; failed_pipenum++)
        	{
        		_ux_utility_semaphore_delete(&(dcd_synergy->ux_dcd_synergy_ed[(UINT)failed_pipenum].ux_dcd_synergy_ep_slave_transfer_request_semaphore));
        	}
            return semaphore_create_status;
        }
    }

#endif

#if defined(UX_DCD_FS_LDO_ENABLE)
    /** Set USB regulator ON */
    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_USBMC, (USHORT)UX_SYNERGY_DCD_USBMC_VDCEN);
#endif

#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_UCKSEL, (USHORT)UX_SYNERGY_DCD_UCKSEL_UCKSELC);
#endif

    if (dcd_io == R_USBFS_BASE)
    {
        /* Supply the clock to the USB module. The SCKE setting is required for USBFS controller but not for USBHS */
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_SCKE);

        while ((ULONG)UX_SYNERGY_DCD_SYSCFG_SCKE !=
                (ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_SYSCFG) & (ULONG)UX_SYNERGY_DCD_SYSCFG_SCKE))
        {
            /* Spin here until SCKE bit is set */
        }
    }

    /* Reset USB Module.  */
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, (USHORT)UX_SYNERGY_DCD_SYSCFG_USBE);
    
    /* Make sure we are in Device mode.  */
#if !defined(BSP_MCU_GROUP_S124) && !defined(BSP_MCU_GROUP_S128) && !defined(BSP_MCU_GROUP_S1JA)
    ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, (USHORT)UX_SYNERGY_DCD_SYSCFG_DCFM);
#endif

#if defined(R_USBHS_BASE)
    if (dcd_io == R_USBHS_BASE)
    {
        ULONG reg;
        UINT  status = (UINT)UX_SUCCESS;
        /*LDRA_NOANALYSIS LDRA_INSPECTED below not working. */
        /* This is initialized in cgc_api_t::init, which is called before the C runtime environment is initialized. */
        /*LDRA_INSPECTED 53 D */
        bsp_feature_cgc_t  const * cgc_feature;
        /*LDRA_ANALYSIS */

        /*LDRA_NOANALYSIS LDRA_INSPECTED below not working. */
        /* This is initialized in cgc_api_t::init, which is called before the C runtime environment is initialized. */
        /*LDRA_INSPECTED 53 D */
        R_BSP_FeatureCgcGet(&cgc_feature);
        /*LDRA_ANALYSIS */

        /** Initialize Bus wait cycles */
        ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_BUSWAIT, (USHORT)UX_SYNERGY_DCD_BUSWAIT_DEFAULT_VAL);

        /** USBHS controller needs USB-PHY clock initialization.  */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_HSEB);

        switch(cgc_feature->main_osc_freq_hz)
        {

        case UX_SYNERGY_DCD_MAIN_OSC_24MHz:
            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_0);
            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_1);
            break;

        case UX_SYNERGY_DCD_MAIN_OSC_20MHz:
            ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_0);
            ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_1);
            break;

#if defined(BSP_MCU_GROUP_S5D9)
        case UX_SYNERGY_DCD_MAIN_OSC_12MHz:
            ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_0);
            ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_CLKSEL_1);
            break;
#endif

        default:
            status = (UINT)UX_CONTROLLER_INIT_FAILED;

        }

        if ((UINT)UX_SUCCESS != status)
        {
            return (status);
        }

        /* Need to wait at least 1us. (Reference: S7G2 Hardware manual Figure33.2 PHY clock settings)
         * Do the USBHS register access to earn the delay time here.
         * The bus access cycles taken for a USBHS register read should be 4cycles in ICLK + (BWAIT+1)cycles in PCLKA.
         * The number of instructions for the software loop below is more than 5 at least so the estimated delay
         * time would be at least 9 ICLK + 17 PCLKA = 0.03749us + 0.17909us = 0.17909us.
         * So 6times USBHS register read accesses should be longer than 1us.
         */
        for (uint32_t i = 0U; i < 6U; i++)
        {
            ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_SYSSTS);
        }

        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_DIRPD);

        /* Wait at least 1ms */
        for (uint32_t i = 0U; i < 6000U; i++)
        {
            ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_SYSSTS);
        }

        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_PHYSET, (USHORT)UX_SYNERGY_DCD_PHYSET_PLLRESET);
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_LPSTS, (USHORT)UX_SYNERGY_DCD_LPSTS_SUSPENDM);

        do {
            reg = ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_PLLSTA);
            reg = reg & 0x1;
        } while(!reg);

        /* Set the speed mode to be High-speed */
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_HSE);
    }
#endif
    
    /** Check the state of VBUS. Attached or Detached.  */
    do {
    	/* Read 3 times the current status and wait for all read to be equal to avoid jitter.  */
    	synergy_register1 = ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0) & UX_SYNERGY_DCD_INTSTS0_VBSTS;
    	synergy_register2 = ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0) & UX_SYNERGY_DCD_INTSTS0_VBSTS;
    	synergy_register3 = ux_dcd_synergy_register_read(dcd_synergy, UX_SYNERGY_DCD_INTSTS0) & UX_SYNERGY_DCD_INTSTS0_VBSTS;

    } while( ( synergy_register1 != synergy_register2 ) || ( synergy_register1 != synergy_register3 ) );

    /** VBUS is stable. Check if on/off.  */
    if (synergy_register1 & UX_SYNERGY_DCD_INTSTS0_VBSTS)
    {
    	/* Enable D+ pull up */
    	ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_DPRPU);
    }

    if (dcd_io == R_USBFS_BASE)
    {
        /* Release D- pull up */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_DMRPU);
    }
    else
    {
        /* Set DRPD bit to 0 in Device mode. */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, UX_SYNERGY_DCD_SYSCFG_DRPD);
    }

#if defined(R_USBHS_BASE)
    if (dcd_io == R_USBHS_BASE)
    {
        uint32_t freq_hz = 0U;
        uint32_t buswaitx10;
        uint32_t buswait;

        /* Adjust Bus wait cycles */
        ux_dcd_synergy_register_clear(dcd_synergy, UX_SYNERGY_DCD_BUSWAIT,  UX_SYNERGY_DCD_BUSWAIT_MASK);

        g_cgc_on_cgc.systemClockFreqGet(CGC_SYSTEM_CLOCKS_PCLKA, &freq_hz);
        buswaitx10 = freq_hz / UX_SYNERGY_DCD_BUSWAIT_CALC_FREQ_PCLK_CYCx10;
        buswait    = freq_hz / UX_SYNERGY_DCD_BUSWAIT_CALC_FREQ_PCLK_CYC;

        /* Resolve the round up error. */
        if (buswaitx10 > (buswait * 10U))
        {
            buswait = buswait + 1U;   /* Round up the value. */
        }
        if (buswait > 2U)
        {
            buswait = buswait - 2U;   /* Access to a USBHS register always need 2x PCLKA cycles. */
        }
        else
        {
            buswait = 0U;
        }
        ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_BUSWAIT, (USHORT)buswait);
    }
#endif

    /** Return successful completion.  */
    return (UINT)UX_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief  USBX DCD bottom-half common part of the USB controller initialization.
 *
 **********************************************************************************************************************/
static void ux_dcd_synergy_initialize_common_complete (void)
{
    UX_DCD_SYNERGY    * dcd_synergy;
    UX_SLAVE_DCD      * dcd = &_ux_system_slave -> ux_system_slave_dcd;

    /** Get the pointer to the Synergy DCD instance.  */
    dcd_synergy = (UX_DCD_SYNERGY *)dcd -> ux_slave_dcd_controller_hardware;

    /** Enable USB Module Operation.  */
    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_SYSCFG, (USHORT)UX_SYNERGY_DCD_SYSCFG_USBE);

    /** Enable: SOF, ATTCH/BCHG. */
    ux_dcd_synergy_register_set(dcd_synergy, UX_SYNERGY_DCD_INTENB0,
                                (UX_SYNERGY_DCD_INTENB0_VBSE  |
                                 UX_SYNERGY_DCD_INTENB0_RSME  |
                                 UX_SYNERGY_DCD_INTENB0_DVSE  |
                                 UX_SYNERGY_DCD_INTENB0_CTRE  |
                                 UX_SYNERGY_DCD_INTENB0_BEMPE |
                                 UX_SYNERGY_DCD_INTENB0_NRDYE |
                                 UX_SYNERGY_DCD_INTENB0_BRDYE));

    /** Set the state of the controller to OPERATIONAL now.  */
    dcd -> ux_slave_dcd_status =  (UINT)UX_DCD_STATUS_OPERATIONAL;
}

/******************************************************************************************************************//**
 * @brief  USBX DCD DMA write callback function
 *
 * @param[in]  p_args       Pointer to the argument of a Transfer module callback function.
 **********************************************************************************************************************/
static void ux_dcd_dma_complete_tx (transfer_callback_args_t * p_args)
{
    UX_DCD_SYNERGY * dcd_synergy = (UX_DCD_SYNERGY *) p_args->p_context;

    /** Disable DMA transfer.  */
    ux_dcd_synergy_register_clear (dcd_synergy, UX_SYNERGY_DCD_D0FIFOSEL, (USHORT) UX_SYNERGY_DCD_PIPESEL_NO_PIPE_USHORT);
    ux_dcd_synergy_register_clear (dcd_synergy, UX_SYNERGY_DCD_D0FIFOSEL, (USHORT)UX_SYNERGY_DCD_DFIFOSEL_DREQE);
    _ux_utility_semaphore_put(&dcd_synergy->dma_tx_completion_semaphore);
}

/******************************************************************************************************************//**
 * @brief  USBX DCD DMA read callback function
 *
 * @param[in]  p_args       Pointer to the argument of a Transfer module callback function.
 **********************************************************************************************************************/
static void ux_dcd_dma_complete_rx (transfer_callback_args_t * p_args)
{
    UX_DCD_SYNERGY * dcd_synergy = (UX_DCD_SYNERGY *) p_args->p_context;

    /** Set PID to NAK for non Control End-points.  */
    ux_dcd_synergy_register_clear(dcd_synergy,
            UX_SYNERGY_DCD_PIPE1CTR  + ((dcd_synergy->read_pipe_number - 1UL) * 2UL),
            UX_SYNERGY_DCD_PIPECTR_PID_MASK);
    ux_dcd_synergy_register_write(dcd_synergy, UX_SYNERGY_DCD_D1FIFOCTR, UX_SYNERGY_DCD_FIFOCTR_BCLR);
    /** Semaphore will be released in transfer callback*/
    _ux_utility_semaphore_put(&dcd_synergy->dma_rx_completion_semaphore);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/

