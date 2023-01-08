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

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    ux_hcd_synergy_uninitialize                           PORTABLE C    */
/*                                                           5.7          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function un-initializes the Synergy HOST controller.           */
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
/*                                                                        */
/*    ux_hcd_synergy_register_clear         Write Synergy register write  */
/*    _ux_utility_delay_ms                   Inserts sleep delay          */
/*    _ux_utility_memory_free               De-allocate memory block                                                    */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application                                                         */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  10-10-2012     TCRG                     Initial Version 5.6           */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  This function disables the Synergy HOST controller.
 *
 * @param[in]      ux_hcd_io           :  HCD controller base address
 *
 * @retval UX_SUCCESS                     HCD controller disabled successfully.
 * @retval UX_SYNERGY_UNINIT_FAILED       HCD controller un-initialization failed.
 **********************************************************************************************************************/
UINT ux_hcd_synergy_disable(ULONG ux_hcd_io)
{
    UX_HCD                *hcd;
    UINT                  status = UX_ERROR;
    UX_HCD_SYNERGY        *hcd_synergy = UX_NULL;

    /* Store the first HCD controller entry.  */
    hcd =  _ux_system_host -> ux_system_host_hcd_array;

#if UX_MAX_HCD > 1
    /** If there is more than one hcd, We need to parse the controller driver table to find correct
     *  HCD controller entry.  */
    for(UINT hcd_index = 0U; hcd_index < (UINT)(_ux_system_host-> ux_system_host_max_hcd); hcd_index++)
    {
#endif
        if(((UINT)UX_UNUSED != (UINT)hcd -> ux_hcd_status) && (ux_hcd_io == hcd -> ux_hcd_io))
        {
            /* We found the correct synergy HCD .  */
            hcd_synergy =  (UX_HCD_SYNERGY *) hcd -> ux_hcd_controller_hardware;
            status = (UINT)UX_SUCCESS;
#if UX_MAX_HCD > 1
            break;
#endif
        }

        /* Try the next HCD structure */
        hcd++;
#if UX_MAX_HCD > 1
    }
#endif

    if (UX_SUCCESS != status)
    {
        /* Return failure status  */
        return (UINT)UX_SYNERGY_UNINIT_FAILED;
    }

    /* Disable the port.   */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DVSTCTR0, UX_SYNERGY_HC_DVSTCTR0_UACT);

    /* Delay.  */
    _ux_utility_delay_ms(10UL);

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;
}


/*******************************************************************************************************************//**
 * @brief  This function un-initializes the Synergy HOST controller.
 *
 * @param[in]      ux_hcd_io           :  HCD controller base address
 *
 * @retval UX_SUCCESS                     Completed the USB controller Un-initialization successfully.
 * @retval UX_SYNERGY_UNINIT_FAILED       HCD controller un-initialization failed.
 * @return                                See @ref Common_Error_Codes for other possible return codes or causes.
 *                                        This function calls:
 *                                        * ux_hcd_synergy_uninitialize_transfer_support()
 **********************************************************************************************************************/

UINT  ux_hcd_synergy_uninitialize(ULONG ux_hcd_io)
{

    UX_HCD                *hcd;
    UINT                  status = UX_ERROR;
    UX_HCD_SYNERGY        *hcd_synergy = UX_NULL;
    ssp_signal_t          signal;
    ssp_feature_t         ssp_feature = {{(ssp_ip_t) 0U}};
    fmi_event_info_t      event_info  = {(IRQn_Type) 0U};

    /* Store the first HCD controller entry.  */
    hcd =  _ux_system_host -> ux_system_host_hcd_array;

#if UX_MAX_HCD > 1
    /** If there is more than one hcd, we need to parse the controller driver table to find correct
     *  HCD controller entry.  */
    for(UINT hcd_index = 0U; hcd_index < (UINT)(_ux_system_host-> ux_system_host_max_hcd); hcd_index++)
    {
#endif
        if(((UINT)UX_UNUSED != (UINT)hcd -> ux_hcd_status) && (ux_hcd_io == hcd -> ux_hcd_io))
        {
            /* We found the correct synergy HCD .  */
            hcd_synergy =  (UX_HCD_SYNERGY *) hcd -> ux_hcd_controller_hardware;
            status = (UINT)UX_SUCCESS;
#if UX_MAX_HCD > 1
            break;
#endif
        }

        /* Try the next HCD structure */
        hcd++;
#if UX_MAX_HCD > 1
    }
#endif

    if (UX_SUCCESS != status)
    {
        /* Return failure status  */
        return (UINT)UX_SYNERGY_UNINIT_FAILED;
    }

    /** Reset the BEMPE, NRDYE, BRDYE, SOFE bits.  */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_INTENB0,
            (USHORT)(UX_SYNERGY_HC_INTENB0_BRDYE | UX_SYNERGY_HC_INTENB0_NRDYE | UX_SYNERGY_HC_INTENB0_BEMPE
                    | UX_SYNERGY_HC_INTENB0_SOFE ));

    /** Clear the INTENB1 bits.  */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_INTENB1,  UX_SYNERGY_HC_INTENB1_OVRCRE
            | UX_SYNERGY_HC_INTENB1_ATTCHE
            | UX_SYNERGY_HC_INTENB1_DTCHE
            | UX_SYNERGY_HC_INTENB1_EOFERRE
            | UX_SYNERGY_HC_INTENB1_SACKE);

    /** Reset the BRDY, NRDY, BEMPE for all pipes.  */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_BRDYENB, UX_SYNERGY_HC_PIPE_ALL);
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_NRDYENB, UX_SYNERGY_HC_PIPE_ALL);
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_BEMPENB, UX_SYNERGY_HC_PIPE_ALL);

    /** Clear USB interrupt status0 register. */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_INTSTS0, UX_SYNERGY_HC_INTSTS0_VBINT
            |UX_SYNERGY_HC_INTSTS0_RESM|UX_SYNERGY_HC_INTSTS0_SOFR
            |UX_SYNERGY_HC_INTSTS0_DVST|UX_SYNERGY_HC_INTSTS0_CTRT);

    /** Clear USB interrupt status1 register. */
    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_INTSTS1, UX_SYNERGY_HC_INTSTS1_ALL_CLEAR);

    /* Reset the BRDY, NRDY, BEMPE status for all pipes.  */
    ux_hcd_synergy_register_status_clear(hcd_synergy, UX_SYNERGY_HC_BRDYSTS, UX_SYNERGY_HC_PIPE_ALL);
    ux_hcd_synergy_register_status_clear(hcd_synergy, UX_SYNERGY_HC_NRDYSTS, UX_SYNERGY_HC_PIPE_ALL);
    ux_hcd_synergy_register_status_clear(hcd_synergy, UX_SYNERGY_HC_BEMPSTS, UX_SYNERGY_HC_PIPE_ALL);

    /** Clear all the physical endpoint.  */
    UINT pipe_count = UX_SYNERGY_HC_PIPE0;
    while(pipe_count <= (UX_SYNERGY_HC_PIPE3 + UX_SYNERGY_HC_PIPE0))
    {
        /* Select pipe.  */
        ux_hcd_synergy_register_write( hcd_synergy, UX_SYNERGY_HC_PIPESEL, (USHORT)pipe_count);

        /* Disable endpoint in the CFG register.  */
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_PIPECFG, UX_SYNERGY_HC_PIPECFG_TYPE_MASK);
        pipe_count++;

    }

    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_DCFM);

    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_DCPCFG, (USHORT)UX_SYNERGY_HC_DCPCFG_DIR
            | (USHORT)UX_SYNERGY_HC_PIPECFG_SHTNAK | (USHORT) UX_SYNERGY_HC_PIPECFG_CNTMD );

    ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_DCPMAXP, UX_SYNERGY_HC_PIPE6);

    /** Disable pull-up/pull-down of the D+/D- line. */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_DPRPU);
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_DRPD);

#if defined(UX_HCD_FS_LDO_ENABLE)
    /* Set USB regulator OFF */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_USBMC, (USHORT)UX_SYNERGY_HC_USBMC_VDCEN);
#endif

    /** Disable USB clock operation.  */
    ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_SYSCFG, UX_SYNERGY_HC_SYSCFG_USBE);

    if (R_USBFS_BASE == hcd_synergy->ux_hcd_synergy_base)
    {
        /* Stop clock source to the USB controller. This is only required for Synergy USBFS controllers. */
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_SYSCFG, (USHORT)UX_SYNERGY_HC_SYSCFG_SCKE);
    }
    ssp_feature.id      = SSP_IP_USB;
    ssp_feature.channel = 0U;

#if defined(R_USBHS_BASE)
    if (hcd_synergy->ux_hcd_synergy_base == R_USBHS_BASE)
    {
        /* Clear UTMI normal mode */
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_LPSTS, (USHORT)UX_SYNERGY_HC_LPSTS_SUSPENDM);

        /* Disable the High-speed mode */
        ux_hcd_synergy_register_clear(hcd_synergy, UX_SYNERGY_HC_SYSCFG, UX_SYNERGY_HC_SYSCFG_HSE);

        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PHYSET, (USHORT)UX_SYNERGY_HC_PHYSET_CLKSEL_0);
        ux_hcd_synergy_register_set(hcd_synergy, UX_SYNERGY_HC_PHYSET, (USHORT)UX_SYNERGY_HC_PHYSET_CLKSEL_1);

        /* Set the Bus wait cycles to default */
        ux_hcd_synergy_register_write(hcd_synergy, UX_SYNERGY_HC_BUSWAIT,  UX_SYNERGY_HC_BUSWAIT_MASK);

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

    /** uninitialize and disable DMA support  */
    status = ux_hcd_synergy_uninitialize_transfer_support(hcd_synergy);
    if (UX_SUCCESS != status)
    {
        /* Return failure status  */
        return (UINT)UX_SYNERGY_UNINIT_FAILED;
    }

    g_fmi_on_fmi.eventInfoGet(&ssp_feature, signal, &event_info);
    if (SSP_INVALID_VECTOR != event_info.irq)
    {
        /* Clear the Pending IRQ in NVIC */
        NVIC_ClearPendingIRQ(event_info.irq);
        /* Disable the IRQ in NVIC */
        NVIC_DisableIRQ(event_info.irq);
    }

    /** Stop the module usage */
    R_BSP_ModuleStop(&ssp_feature);

    /* Set the state of the controller to unused.  */
    hcd -> ux_hcd_status = (UINT)UX_UNUSED;

    /* Set the hcd controller hardware to unknown.  */
    hcd -> ux_hcd_controller_hardware = UX_NULL;

    /* Reset HCD controller type. */
    hcd -> ux_hcd_controller_type = 0U;

    /* Initialize the max bandwidth for periodic endpoints to zero. */
    hcd -> ux_hcd_available_bandwidth = 0UL;

    /* Set the number of ports on the controller to zero.  */
    hcd -> ux_hcd_nb_root_hubs =  0U;

    /* Clear the irq flag. */
    hcd->ux_hcd_irq = 0U;

    /* Clear Host Controller IO base address. */
    hcd->ux_hcd_io = 0UL;

    /* Free up HCD resource.  */
    _ux_utility_memory_free(hcd_synergy -> ux_hcd_synergy_ed_list);
    _ux_utility_memory_free(hcd_synergy -> ux_hcd_synergy_td_list);
    _ux_utility_memory_free(hcd_synergy -> ux_hcd_synergy_iso_td_list);
    _ux_utility_memory_free(hcd_synergy);

    /* Return successful completion.  */
    return (UINT)UX_SUCCESS;

}

/******************************************************************************************************************//**
 * @brief  This function un-initializes the transfer module associated with the USBX HOST controller.
 *

 * @param[in]  hcd_synergy                 : HCD synergy controller instance.

 * @retval     UX_SUCCESS                    Completed the transfer Un-initialization successfully.
 * @retval     UX_SYNERGY_UNINIT_FAILED      Failed to Un-initialize the USB controller.
 **********************************************************************************************************************/
UINT  ux_hcd_synergy_uninitialize_transfer_support (UX_HCD_SYNERGY  *hcd_synergy)
{
    UINT                status = SSP_SUCCESS;
    ssp_err_t           ssp_err;

    if (NULL != hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx)
    {
        /* Delete semaphore used for transfer transmit synchronization. */
        _ux_utility_semaphore_delete(&hcd_synergy->ux_hcd_synergy_semaphore_tx);

        /* Close Transfer module for transmission. */
        ssp_err = hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_api->close(
                hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_tx->p_ctrl);
        if(SSP_SUCCESS != ssp_err)
        {
            status = (UINT)UX_SYNERGY_UNINIT_FAILED;
        }

    }

    if (NULL != hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx)
    {
        /* Delete semaphore used for transfer receive synchronization. */
        _ux_utility_semaphore_delete(&hcd_synergy->ux_hcd_synergy_semaphore_rx);

        /* Close Transfer module for reception. */
        ssp_err = hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_api->close(
                hcd_synergy->ux_hcd_synergy_transfer.ux_synergy_transfer_rx->p_ctrl);
        if(SSP_SUCCESS != ssp_err)
        {
            status = (UINT)UX_SYNERGY_UNINIT_FAILED;
        }

    }

    /* Return successful completion.  */
    return status;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup sf_el_ux)
 **********************************************************************************************************************/
