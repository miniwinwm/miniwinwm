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

#include "bsp_api.h"
#include "r_cgc.h"
#include "sf_el_ux_hcd_hs_cfg.h"
#include "sf_el_ux_hcd_fs_cfg.h"

static UINT ux_hcd_synergy_initialize_common(UX_HCD *hcd);

static void ux_hcd_synergy_initialize_common_complete(UX_HCD *hcd);

static void ux_hcd_dma_complete_tx(transfer_callback_args_t * p_args);

static void ux_hcd_dma_complete_rx(transfer_callback_args_t * p_args);

typedef union local_buffer_u {
    ULONG   input;
    UCHAR   output[4];
} local_buffer_t;

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy_initialize                           PORTABLE C      */
/*                                                           5.7          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function initializes the Synergy controller.                   */
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    HCD                                   Pointer to HCD                */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    ux_hcd_synergy_register_read          Read Synergy register read    */
/*    ux_hcd_synergy_register_write         Write Synergy register write  */
/*    ux_hcd_synergy_periodic_tree_create   Create periodic tree          */
/*    ux_hcd_synergy_power_root_hubs        Power root HUBs               */
/*    _ux_utility_memory_allocate            Allocate memory block        */
/*    _ux_utility_set_interrupt_handler      Setup interrupt handler      */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Host Stack                                                          */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  10-10-2012     TCRG                     Initial Version 5.6           */ 
/*  06-01-2014     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.7    */ 
/*                                                                        */ 
/**************************************************************************/ 

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function initializes the Synergy controller.
 *
 * @param[in,out]  hcd : Pointer to USBX host controller structure.
 *
 * @return               See @ref Common_Error_Codes for other possible return codes or causes.
 *                       This function calls:
 *                       * ux_hcd_synergy_initialize_common()
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_initialize(UX_HCD *hcd)
{   
    UINT    status;

    /* Initialize USB peripheral except interrupts. */
    status = ux_hcd_synergy_initialize_common (hcd);
    if (UX_SUCCESS == status)
    {
        /* Enable USB interrupts to activate USB port. */
        ux_hcd_synergy_initialize_common_complete (hcd);
    }

    return status;
}


/*******************************************************************************************************************//**
 * @brief  This function Initialize USB peripheral.
 *
 * @param[in,out]  hcd : Pointer to USBX host controller structure.
 *
 * @retval     UX_SUCCESS                   Initialize hcd transfer support successfully.
 * @retval     UX_CONTROLLER_INIT_FAILED    Failed in Transfer module setup, or Unsupported USB controller was specified.
 * @retval     UX_MEMORY_INSUFFICIENT       Failed in allocation memory.
 *
 * @return               See @ref Common_Error_Codes for other possible return codes or causes.
 *                       This function calls:
 *                       * ux_hcd_synergy_periodic_tree_create()
 **********************************************************************************************************************/
static UINT  ux_hcd_synergy_initialize_common(UX_HCD *hcd)
{
    UX_HCD_SYNERGY    * hcd_synergy;
    UINT                status;
    uint8_t             irq_ipl = 0xFF;
    ssp_signal_t        signal;
    ssp_feature_t       ssp_feature = {{(ssp_ip_t) 0U}};
    fmi_event_info_t    event_info  = {(IRQn_Type) 0U};

    ssp_feature.id = SSP_IP_USB;
    ssp_feature.channel = 0U;

#if defined(R_USBHS_BASE)
    if (hcd -> ux_hcd_io == R_USBHS_BASE)
    {
        ssp_feature.unit = (uint32_t) SSP_IP_UNIT_USBHS;
        signal = SSP_SIGNAL_USB_USB_INT_RESUME;
        irq_ipl = (uint8_t) SF_EL_UX_HCD_CFG_HS_IRQ_IPL;
    }
    else
    {
#endif
        if (hcd -> ux_hcd_io == R_USBFS_BASE)
        {
            ssp_feature.unit = (uint32_t) SSP_IP_UNIT_USBFS;
            signal = SSP_SIGNAL_USB_INT;
            irq_ipl = (uint8_t) SF_EL_UX_HCD_CFG_FS_IRQ_IPL;
        }
        else
        {
            /* Error trap. */
            _ux_system_error_handler((UINT)UX_SYSTEM_LEVEL_THREAD, (UINT)UX_SYSTEM_CONTEXT_HCD, (UINT)UX_CONTROLLER_INIT_FAILED);

            /* If trace is enabled, insert this event into the trace buffer.  */
            UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_CONTROLLER_INIT_FAILED, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

            return (UINT)UX_CONTROLLER_INIT_FAILED;
        }
#if defined (R_USBHS_BASE)
    }
#endif

    /* Start module (cancel module stop). */
    R_BSP_ModuleStart(&ssp_feature);

    /* Get IRQ information from FMI. */
    g_fmi_on_fmi.eventInfoGet(&ssp_feature, signal, &event_info);
    if (SSP_INVALID_VECTOR != event_info.irq)
    {
        NVIC_SetPriority(event_info.irq, irq_ipl);
        NVIC_EnableIRQ(event_info.irq);
    }
    else
    {
        return (UINT)UX_CONTROLLER_INIT_FAILED;
    }

    /* Allocate memory for this synergy HCD instance.  */
    hcd_synergy =  _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY, sizeof(UX_HCD_SYNERGY));
    if (hcd_synergy == UX_NULL)
    {
        return (UINT)UX_MEMORY_INSUFFICIENT;
    }

    /* Allocate the list of eds. All eds are allocated on 16 byte memory boundary.  */
    hcd_synergy -> ux_hcd_synergy_ed_list =  _ux_utility_memory_allocate((ULONG)UX_ALIGN_16, (ULONG)UX_REGULAR_MEMORY,
                                                 (ULONG)(sizeof(UX_SYNERGY_ED) *_ux_system_host -> ux_system_host_max_ed));
    if (hcd_synergy -> ux_hcd_synergy_ed_list == UX_NULL)
    {
        return (UINT)UX_MEMORY_INSUFFICIENT;
    }

    /* Allocate the list of tds. All tds are allocated on 32 byte memory boundary.  */
    hcd_synergy -> ux_hcd_synergy_td_list =  _ux_utility_memory_allocate((ULONG)UX_ALIGN_32, (ULONG)UX_REGULAR_MEMORY,
                                                 (ULONG)(sizeof(UX_SYNERGY_TD) *_ux_system_host -> ux_system_host_max_td));
    if (hcd_synergy -> ux_hcd_synergy_td_list == UX_NULL)
    {
        return (UINT)UX_MEMORY_INSUFFICIENT;
    }

    /* Allocate the list of isochronous tds. All tds are allocated on 32 byte memory boundary.  */
    hcd_synergy -> ux_hcd_synergy_iso_td_list =  _ux_utility_memory_allocate((ULONG)UX_ALIGN_32, (ULONG)UX_REGULAR_MEMORY,
                                                 (ULONG)(sizeof(UX_SYNERGY_ISO_TD) *_ux_system_host -> ux_system_host_max_iso_td));
    if (hcd_synergy -> ux_hcd_synergy_iso_td_list == UX_NULL)
    {
        return (UINT)UX_MEMORY_INSUFFICIENT;
    }

    /* Initialize the periodic tree.  */
    status =  ux_hcd_synergy_periodic_tree_create(hcd_synergy);
    if (status != (UINT)UX_SUCCESS)
    {
        return (status);
    }

    /* Set the state of the controller to HALTED first.  */
    hcd -> ux_hcd_status =  (UINT)UX_HCD_STATUS_HALTED;

    /* Set the pointer to the synergy HCD.  */
    hcd -> ux_hcd_controller_hardware =  (VOID *) hcd_synergy;

    /* Set HCD controller type. */
    hcd -> ux_hcd_controller_type =  (UINT)UX_SYNERGY_CONTROLLER;

    /* Initialize the max bandwidth for periodic endpoints. On synergy, the spec says
       no more than 90% to be allocated for periodic.  */
    hcd -> ux_hcd_available_bandwidth =  UX_SYNERGY_HC_AVAILABLE_BANDWIDTH;

    /* Initialize the function collector for this HCD.  */
    hcd -> ux_hcd_entry_function =  ux_hcd_synergy_entry;

    /* Get the number of ports on the controller. The number of ports needs to be reflected both
       for the generic HCD container and the local Synergy container.  */
    hcd -> ux_hcd_nb_root_hubs =  1U;
    hcd_synergy -> ux_hcd_synergy_nb_root_hubs =  1U;

    /* Set Host Controller IO base address. */
    hcd_synergy->ux_hcd_synergy_base = hcd->ux_hcd_io;

    /* Set the generic HCD owner for the synergy HCD.  */
    hcd_synergy -> ux_hcd_synergy_hcd_owner =  hcd;

    /*  Buffer number starts at 8 , till 127 */
    hcd_synergy -> ux_synergy_next_available_bufnum =  8UL;

    /* Disable Synergy Transfer module support. */
    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx = UX_NULL;
    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx = UX_NULL;

    /* So far no device is attached. */
    hcd_synergy -> ux_synergy_device_attached = (ULONG)UX_FALSE;

#if defined(UX_HCD_FS_LDO_ENABLE)
    /* Set USB regulator ON */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_USBMC, (USHORT)UX_SYNERGY_HC_USBMC_VDCEN);
#endif

    /* Disable pull-up the D+ line. */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_DPRPU);

    /* Disable pull-down of D+ and D- lines. */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_DRPD);

    /* Select Host Controller. */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_DCFM);

    if (R_USBFS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        /* Supply clock source to the USB controller. This is only required for Synergy USBFS controllers. */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_SCKE);

        /* Wait until SCKE bit is changed to zero. */
        while (1)
        {
            ULONG reg = 0;
            reg = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_SYSCFG);
            if (UX_SYNERGY_HC_SYSCFG_SCKE & reg)
            {
                break;
            }
        }

#if defined(BSP_MCU_GROUP_S7G2) || defined(BSP_MCU_GROUP_S5D9)
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PHYSLEW,
                (USHORT)(  UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWF01 | UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWF00
                         | UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWR01 | UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWR00));

        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PHYSLEW,
                (USHORT)(UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWF00 | UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWR00));
#endif
    }
    else
    {
#ifndef UX_HOST_DISABLE_HS
        /* Enable High-Speed Operation. */
       ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_SYSCFG, UX_SYNERGY_HC_SYSCFG_HSE);
#endif

#if defined(BSP_MCU_GROUP_S7G2) || defined(BSP_MCU_GROUP_S5D9)
        ULONG reg;
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

        /* PHY clock settings.  */
#ifndef UX_HOST_DISABLE_HS
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_HSEB);

#else
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_HSEB);
#endif
       switch(cgc_feature->main_osc_freq_hz)
       {

       case UX_SYNERGY_HC_MAIN_OSC_24MHz:
           ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_CLKSEL_0);
           ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_CLKSEL_1);
           break;

       case UX_SYNERGY_HC_MAIN_OSC_20MHz:
           ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_CLKSEL_0);
           ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_CLKSEL_1);
           break;

#if defined(BSP_MCU_GROUP_S5D9)
       case UX_SYNERGY_HC_MAIN_OSC_12MHz:
           ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_CLKSEL_0);
           ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_CLKSEL_1);
           break;
#endif

       default:
           status = (UINT)UX_CONTROLLER_INIT_FAILED;

       }

       if (status != (UINT)UX_SUCCESS)
       {
           return (status);
       }

        /* Wait at least 1us by software delay. Assuming the peripheral clock is set to 120MHz. */
        volatile uint32_t i = 120U;
        while (i)
        {
            ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_PHYSET);
            --i;
        }

        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_DIRPD);

        /* Wait at least 1ms by software delay. Assuming the peripheral clock is set to 120MHz. */
        i = 120000U;
        while (i)
        {
            ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_PHYSET);
            --i;
        }

        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PHYSET,  UX_SYNERGY_HC_PHYSET_PLLRESET);
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_LPSTS,  UX_SYNERGY_HC_LPSTS_SUSPENDM);

        do {
            /* Check if PLL is locked. */
            reg = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_PLLSTA);
        } while (0UL == (reg & (ULONG)UX_SYNERGY_HC_PLLSTA_PLLLOCK));
#endif

        /* Enable single-ended receiver operation. Set CNEN to 1 after the PHY clock is supplied. */
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_SYSCFG, UX_SYNERGY_HC_SYSCFG_CNEN);
    }

    /* Enable pull-down of D+ and D- lines. */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_SYSCFG, UX_SYNERGY_HC_SYSCFG_DRPD);

    /* Enable VBUS. */
    if (hcd->ux_hcd_io == R_USBFS_BASE)
    {
#ifndef UX_HOST_FS_VBUS_ENABLE_LOW
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DVSTCTR0, UX_SYNERGY_HC_DVSTCTR0_VBUSEN);
#else
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DVSTCTR0, UX_SYNERGY_HC_DVSTCTR0_VBUSEN);
#endif
    }
    else
    {
#ifndef UX_HOST_HS_VBUS_ENABLE_LOW
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_DVSTCTR0, UX_SYNERGY_HC_DVSTCTR0_VBUSEN);
#else
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DVSTCTR0, UX_SYNERGY_HC_DVSTCTR0_VBUSEN);
#endif
    }
    /* USB clock operation enabled.  */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_SYSCFG, UX_SYNERGY_HC_SYSCFG_USBE);

    /* xFIFOSEL initialization.  */
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_CFIFOSEL, UX_SYNERGY_HC_CFIFOSEL_RCNT | UX_SYNERGY_HC_CFIFOSEL_MBW_8);
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_D0FIFOSEL,UX_SYNERGY_HC_DFIFOSEL_MBW_8);
    ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_D1FIFOSEL,UX_SYNERGY_HC_DFIFOSEL_MBW_8);

#if defined(BSP_MCU_GROUP_S7G2) || defined(BSP_MCU_GROUP_S5D9)
    if (R_USBHS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        uint32_t freq_hz = 0;
        uint32_t buswaitx10;
        uint32_t buswait;

        /* Adjust Bus wait cycles */
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_BUSWAIT, UX_SYNERGY_HC_BUSWAIT_MASK);

        g_cgc_on_cgc.systemClockFreqGet(CGC_SYSTEM_CLOCKS_PCLKA, &freq_hz);
        buswaitx10 = freq_hz / UX_SYNERGY_HC_BUSWAIT_CALC_FREQ_PCLK_CYCX10;
        buswait    = freq_hz / UX_SYNERGY_HC_BUSWAIT_CALC_FREQ_PCLK_CYC;

        /* Resolve the round up error. */
        if (buswaitx10 > (buswait * 10U))
        {
            buswait = buswait + 1U;   /* Round up the value */
        }
        if (buswait > 2U)
        {
            buswait = buswait - 2U;   /* Access to a USBHS register always need 2x PCLKA cycles. */
        }
        else
        {
            buswait = 0U;
        }
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_BUSWAIT, (uint16_t)buswait);
    }
#endif

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief  USBX HCD Transfer Support with DMA support.
 *
 * @param[in, out]  hcd                  Pointer to the USBX HCD control block.
 * @param[in]       p_transfer_instance  Pointer to Transfer module instances.
 *
 * @retval     UX_SUCCESS                   Initialize hcd transfer support successfully.
 * @retval     UX_CONTROLLER_INIT_FAILED    Failed in Transfer module setup, or Unsupported USB controller was specified.
 * @retval     UX_SEMAPHORE_ERROR           Failed in creating a semaphore used for DMA transfer.
 * @retval     UX_MEMORY_INSUFFICIENT       Failed in allocation memory.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_initialize_transfer_support(UX_HCD *hcd, const UX_HCD_SYNERGY_TRANSFER *p_transfer_instance)
{
    ssp_err_t           ssp_err;
    UINT                status;
    UX_HCD_SYNERGY    * hcd_synergy;

    /* Initialize USB peripheral except interrupts. */
    status = ux_hcd_synergy_initialize_common(hcd);
    if (UX_SUCCESS == status)
    {
        hcd_synergy = hcd -> ux_hcd_controller_hardware;

        /* Save the DMA transfer driver instances. */
        hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx =
                (transfer_instance_t *)p_transfer_instance->ux_synergy_transfer_tx;
        hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx =
                (transfer_instance_t *)p_transfer_instance->ux_synergy_transfer_rx;

        /* Create semaphores used for DMA transfer end synchronization. */
        status = _ux_utility_semaphore_create(&hcd_synergy->ux_hcd_synergy_semaphore_tx,"ux_hcd_semaphore_tx", 0U);
        if(TX_SUCCESS != status)
        {
            return (UINT)UX_SEMAPHORE_ERROR;
        }

        status = _ux_utility_semaphore_create(&hcd_synergy->ux_hcd_synergy_semaphore_rx,"ux_hcd_semaphore_rx", 1U);
        if(TX_SUCCESS != status)
        {
            return (UINT)UX_SEMAPHORE_ERROR;
        }

        /* DMA interrupt priority should be higher than or equal USB Controller peripheral's. */
        if (hcd -> ux_hcd_io == R_USBFS_BASE)
        {
            if (hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->irq_ipl >= (uint8_t) SF_EL_UX_HCD_CFG_FS_IRQ_IPL)
            {
                return (UINT)UX_CONTROLLER_INIT_FAILED;
            }
        }
        else
        {
            if (hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->irq_ipl >= (uint8_t) SF_EL_UX_HCD_CFG_HS_IRQ_IPL)
            {
                return (UINT)UX_CONTROLLER_INIT_FAILED;
            }
        }

        /* Configure DMA transfer configurations. */
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info   =
                                    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->p_info;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info   =
                                    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_cfg->p_info;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.irq_ipl  =
                                    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->irq_ipl;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.irq_ipl  =
                                    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_cfg->irq_ipl;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_extend =
                                    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_cfg->p_extend;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_extend =
                                    hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_cfg->p_extend;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_callback = ux_hcd_dma_complete_tx;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_callback = ux_hcd_dma_complete_rx;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_context  = hcd_synergy;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_context  = hcd_synergy;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->mode = TRANSFER_MODE_BLOCK;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->mode = TRANSFER_MODE_BLOCK;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.activation_source = ELC_EVENT_ELC_SOFTWARE_EVENT_0;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.activation_source = ELC_EVENT_ELC_SOFTWARE_EVENT_1;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.auto_enable = false;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.auto_enable = false;

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx.p_info->irq            = TRANSFER_IRQ_END;

        ssp_err = hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_api->open(
                      hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl,
                      &hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_tx);
        if(SSP_SUCCESS != ssp_err)
        {
            return (UINT)UX_CONTROLLER_INIT_FAILED;
        }

        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->src_addr_mode  = TRANSFER_ADDR_MODE_FIXED;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->repeat_area    = TRANSFER_REPEAT_AREA_SOURCE;
        hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->irq            = TRANSFER_IRQ_END;

        ssp_err = hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_api->open(
                      hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_ctrl,
                                   &hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx);
        if(SSP_SUCCESS != ssp_err)
        {
            return (UINT)UX_CONTROLLER_INIT_FAILED;
        }

        /* Enable USB interrupts to activate USB port. */
        ux_hcd_synergy_initialize_common_complete(hcd);
    }

    return status;
}

/******************************************************************************************************************//**
 * @brief   USBX HCD final procedure for the initialization.
 *
 * @param[in]  hcd       Pointer to the USBX HCD control block.
 **********************************************************************************************************************/
static void  ux_hcd_synergy_initialize_common_complete(UX_HCD *hcd)
{
    UX_HCD_SYNERGY    * hcd_synergy = hcd -> ux_hcd_controller_hardware;

    /* Set the controller to operational mode.  */
    hcd -> ux_hcd_status = (UINT)UX_HCD_STATUS_OPERATIONAL;

    /* Clear USB interrupt status0. */
    ULONG reg = 0U;
    reg = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_INTSTS0);
    reg = reg & (ULONG)(~(UX_SYNERGY_HC_INTSTS0_VBINT|UX_SYNERGY_HC_INTSTS0_RESM|UX_SYNERGY_HC_INTSTS0_SOFR
                         |UX_SYNERGY_HC_INTSTS0_DVST|UX_SYNERGY_HC_INTSTS0_CTRT));
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_INTSTS0, (USHORT)reg);

    /* Clear USB interrupt status1. Attach and Detach statuses are intentionally not cleared. */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_INTSTS1,
                                                (USHORT)(UX_SYNERGY_HC_INTSTS1_ATTCH|UX_SYNERGY_HC_INTSTS1_DTCH));

    /* Enable USB interrupts. */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_BRDYENB, UX_SYNERGY_HC_PIPE_ALL);
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_NRDYENB, UX_SYNERGY_HC_PIPE_ALL);
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_BEMPENB, UX_SYNERGY_HC_PIPE_ALL);
    
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_INTENB0,  UX_SYNERGY_HC_INTENB0_SOFE
                                                                     | UX_SYNERGY_HC_INTENB0_BRDYE
                                                                     | UX_SYNERGY_HC_INTENB0_NRDYE
                                                                     | UX_SYNERGY_HC_INTENB0_BEMPE);

    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_INTENB1,  UX_SYNERGY_HC_INTENB1_OVRCRE
                                                                     | UX_SYNERGY_HC_INTENB1_ATTCHE
                                                                     | UX_SYNERGY_HC_INTENB1_EOFERRE
                                                                     | UX_SYNERGY_HC_INTENB1_SACKE);

    /* All ports must now be powered to pick up device insertion.  */
    ux_hcd_synergy_power_root_hubs(hcd_synergy);
}

/******************************************************************************************************************//**
 * @brief  USBX HCD DMA write callback function
 *
 * @param[in]  p_args       Pointer to the argument of a Transfer module callback function.
 **********************************************************************************************************************/
/* USBX HCD DMA write callback function */
static void ux_hcd_dma_complete_tx(transfer_callback_args_t * p_args)
{
    UX_HCD_SYNERGY * hcd_synergy = (UX_HCD_SYNERGY *)p_args->p_context;
    _ux_utility_semaphore_put(&hcd_synergy->ux_hcd_synergy_semaphore_tx);
}

/*******************************************************************************************************************//**
 * @brief  USBX HCD DMA read callback function
 *
 * @param[in]  p_args       Pointer to the argument of a Transfer module callback function.
 **********************************************************************************************************************/
static void ux_hcd_dma_complete_rx(transfer_callback_args_t * p_args)
{
    local_buffer_t  local_buffer;
    volatile ULONG   byte_count = 0;

    UX_HCD_SYNERGY * hcd_synergy = (UX_HCD_SYNERGY *)p_args->p_context;

    local_buffer.output[0] = 0U;

    /* Read data by software copy if we have remaining data in the FIFO. */
    if(hcd_synergy->remaining_payload_bytes != 0U)
    {
        /* Read data at once from FIFO. */
        if (TRANSFER_SIZE_4_BYTE == hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->size)
        {
            local_buffer.input = *((volatile ULONG *) (hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_D1FIFO));
        }
        else if (TRANSFER_SIZE_2_BYTE == hcd_synergy->ux_hcd_synergy_transfer_cfg_instance_rx.p_info->size)
        {
            local_buffer.input = *((volatile USHORT *) (hcd_synergy->ux_hcd_synergy_base + UX_SYNERGY_HC_D1FIFO));
        }

        /* Read the remaining payload data from FIFO without changing MBW */
        while (hcd_synergy->remaining_payload_bytes != 0U)
        {
            /* Read the 8 bit value.  */
            *hcd_synergy->payload_buffer = local_buffer.output[byte_count];

            /* Increase the payload buffer pointer */
            hcd_synergy->payload_buffer += sizeof(UCHAR);

            /* Decrease the remaining bytes */
            --hcd_synergy->remaining_payload_bytes;

            /* Increase the offset of remaining bytes array */
            ++byte_count;
        }
    }

    /* Need manual FIFO clear operation for PIPEs used for Interrupt endpoints. For Bulk endpoints, FIFO clear
     * operation is automatically done. This procedure might be changed in the future version.
     */
    ULONG reg = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_D1FIFOSEL);
    if ((ULONG)((ULONG)UX_SYNERGY_HC_DFIFOSEL_CURPIPE_MASK & reg) >= 6UL)
    {
        /* Clear FIFO if FRDY bit is set. FIFO must be cleared to be ready for next transfer. */
        reg = ux_hcd_synergy_register_read(hcd_synergy, UX_SYNERGY_HC_D1FIFOCTR);
        if ((ULONG)UX_SYNERGY_HC_FIFOCTR_FRDY & reg)
        {
            ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_D1FIFOCTR, UX_SYNERGY_HC_FIFOCTR_BCLR);
        }
    }

    /* Release the semaphore for next read */
    _ux_utility_semaphore_put(&hcd_synergy->ux_hcd_synergy_semaphore_rx);
}
/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
