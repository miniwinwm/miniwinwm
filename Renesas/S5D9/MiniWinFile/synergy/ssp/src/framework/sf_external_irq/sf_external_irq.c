/***********************************************************************************************************************
 * Copyright [2015-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
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

/**********************************************************************************************************************
 * File Name    : sf_external_irq.c
 * Description  : ThreadX aware general external interrupt driver functions.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "sf_external_irq.h"
#include "sf_external_irq_cfg.h"
#include "sf_external_irq_private_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/* Macro to identify valid control block */
#define OPEN (0x4F50454EU)

/** Macro for error logger. */
#ifndef SF_EXTERNAL_IRQ_ERROR_RETURN
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define SF_EXTERNAL_IRQ_ERROR_RETURN(a, err) SSP_ERROR_RETURN((a), (err), &g_module_name[0], &g_version)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
/* Callback functions for SSP framework */
static void sf_external_irq_callback (external_irq_callback_args_t * cb_data);

#if (SF_EXTERNAL_IRQ_CFG_PARAM_CHECKING_ENABLE)
static ssp_err_t sf_external_irq_param_check (sf_external_irq_instance_ctrl_t * p_ctrl,
                                              sf_external_irq_cfg_t const * const   p_cfg);
#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "sf_external_irq";
#endif

#if defined(__GNUC__)
/* This structure is affected by warnings from a GCC compiler bug. This pragma suppresses the warnings in this
 * structure only.*/
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
/** Version data structure used by error logger macro. */
static const ssp_version_t g_version =
{
    .code_version_minor = SF_EXTERNAL_IRQ_CODE_VERSION_MINOR,
	.api_version_major  = SF_EXTERNAL_IRQ_API_VERSION_MAJOR,
	.code_version_major = SF_EXTERNAL_IRQ_CODE_VERSION_MAJOR,
    .api_version_minor  = SF_EXTERNAL_IRQ_API_VERSION_MINOR,
};
#if defined(__GNUC__)
/* Restore warning settings for 'missing-field-initializers' to as specified on command line. */
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic pop
#endif

/***********************************************************************************************************************
 * Implementation of Interface
 **********************************************************************************************************************/
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const sf_external_irq_api_t g_sf_external_irq_on_sf_external_irq =
{
    .open       = SF_EXTERNAL_IRQ_Open,
    .close      = SF_EXTERNAL_IRQ_Close,
    .wait       = SF_EXTERNAL_IRQ_Wait,
    .versionGet = SF_EXTERNAL_IRQ_VersionGet,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup SF_EXTERNAL_IRQ
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Configure external IRQ and optionally enable external IRQ callbacks. Implements sf_external_irq_api_t::open.
 *
 * The SF_EXTERNAL_IRQ_Open() function creates semaphore for the external IRQ channel used, then calls the HAL driver
 * open function. After successful initialization, the external IRQ is ready for use.
 *
 * @retval SSP_SUCCESS         Initialization was successful and external interrupt has started.
 * @retval SSP_ERR_ASSERTION   One of the following parameters may be NULL: p_ctrl, p_api, or p_cfg, p_api, or
 *                             p_api->open. See HAL driver for other possible causes.
 * @retval SSP_ERR_IN_USE      This channel is already open.
 * @retval SSP_ERR_INTERNAL    An internal ThreadX error has occurred.
 * @return                     See @ref Common_Error_Codes or HAL driver for other possible return codes or causes.
 *                             This function calls:
 *                                 * external_irq_api_t::open
 *
 * @note This function is reentrant for any channel.
 *
 **********************************************************************************************************************/
ssp_err_t SF_EXTERNAL_IRQ_Open (sf_external_irq_ctrl_t        * const p_api_ctrl,
                                sf_external_irq_cfg_t const * const   p_cfg)
{
    UINT tx_err = TX_SUCCESS;
    ssp_err_t err = SSP_SUCCESS;
    sf_external_irq_instance_ctrl_t * p_ctrl = (sf_external_irq_instance_ctrl_t *) p_api_ctrl;

#if SF_EXTERNAL_IRQ_CFG_PARAM_CHECKING_ENABLE
    err = sf_external_irq_param_check (p_ctrl, p_cfg);
    SF_EXTERNAL_IRQ_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif

    /** Save driver structure for use in other framework layer functions */
    p_ctrl->p_lower_lvl_irq = p_cfg->p_lower_lvl_irq;

    /** Create semaphore for use with wait function */
    tx_err = tx_semaphore_create(&p_ctrl->semaphore, NULL, 0);
    SF_EXTERNAL_IRQ_ERROR_RETURN(TX_SUCCESS == tx_err, SSP_ERR_INTERNAL);

    /** Prepare configuration for lower layer */
    external_irq_cfg_t hal_cfg;
    memcpy(&hal_cfg, p_cfg->p_lower_lvl_irq->p_cfg, sizeof(hal_cfg));
    if (SF_EXTERNAL_IRQ_EVENT_NONE == p_cfg->event)
    {
        hal_cfg.p_callback    = NULL;
        hal_cfg.p_context     = 0;
        p_ctrl->callback_used = false;
    }
    else
    {
        hal_cfg.p_callback    = sf_external_irq_callback;
        hal_cfg.p_context     = (void *) p_ctrl;
        p_ctrl->callback_used = true;
    }

    /** Open lower layer */
    err = p_cfg->p_lower_lvl_irq->p_api->open(p_ctrl->p_lower_lvl_irq->p_ctrl, &hal_cfg);

    /** If low level initialization failed, delete the semaphore and exit the function with the error code */
    if (SSP_SUCCESS != err)
    {
    	/** Delete the semaphore. */
        tx_semaphore_delete(&p_ctrl->semaphore);
        /** log the error and return the error */
        SSP_ERROR_LOG(err, "sf_external_irq", g_version);
        return err;
    }

    /** Mark control block open so other tasks know it is valid */
    p_ctrl->open = OPEN;

    return SSP_SUCCESS;
} /* End of function SF_EXTERNAL_IRQ_Open() */

/******************************************************************************************************************//**
 * @brief Get semaphore with specified timeout for external interrupt to expire.
 * Implements sf_external_irq_api_t::wait.
 *
 * @retval  SSP_SUCCESS          External interrupt stopped successfully.
 * @retval  SSP_ERR_NOT_OPEN     Driver control block not valid.  Call ::SF_EXTERNAL_IRQ_Open to configure.
 * @retval  SSP_ERR_TIMEOUT      Time out happens while waiting a semaphore.
 * @retval  SSP_ERR_WAIT_ABORTED Suspension was aborted by another thread.
 * @return                       See @ref Common_Error_Codes or HAL driver for other possible return codes or causes.
 *********************************************************************************************************************/
ssp_err_t SF_EXTERNAL_IRQ_Wait       (sf_external_irq_ctrl_t      * const p_api_ctrl,
                                      ULONG const                         timeout)
{
    sf_external_irq_instance_ctrl_t * p_ctrl = (sf_external_irq_instance_ctrl_t *) p_api_ctrl;

#if SF_EXTERNAL_IRQ_CFG_PARAM_CHECKING_ENABLE
    /** Verify control block is valid */
    SSP_ASSERT(NULL != p_ctrl);
    SF_EXTERNAL_IRQ_ERROR_RETURN(OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    /** Wait for semaphore post from ISR */
    UINT tx_err;
    tx_err = tx_semaphore_get(&p_ctrl->semaphore, timeout);
    SF_EXTERNAL_IRQ_ERROR_RETURN(TX_NO_INSTANCE != tx_err, SSP_ERR_TIMEOUT);
    SF_EXTERNAL_IRQ_ERROR_RETURN(TX_SUCCESS == tx_err, SSP_ERR_WAIT_ABORTED);

    return SSP_SUCCESS;
} /* End of function SF_EXTERNAL_IRQ_Wait() */

/******************************************************************************************************************//**
 * @brief Get version and store it in provided pointer p_version. Implements sf_external_irq_api_t::versionGet.
 *
 * @retval SSP_SUCCESS           Version returned successfully.
 * @retval SSP_ERR_ASSERTION     Parameter p_version was null.
 *********************************************************************************************************************/
ssp_err_t SF_EXTERNAL_IRQ_VersionGet (ssp_version_t     * const p_version)
{
#if SF_EXTERNAL_IRQ_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_version.version_id;

    return SSP_SUCCESS;
} /* End of function SF_EXTERNAL_IRQ_VersionGet() */

/*******************************************************************************************************************//**
 * @brief   Close channel at HAL layer and delete the semaphore . Implements sf_external_irq_api_t::close.
 * @retval  SSP_SUCCESS          Successful close.
 * @retval  SSP_ERR_ASSERTION    The parameter ctrl is NULL.
 * @retval  SSP_ERR_NOT_OPEN     The channel is not opened.
 * @retval  SSP_ERR_UNSUPPORTED  Unsupported operation.
 * @return                       See @ref Common_Error_Codes or HAL driver for other possible return codes or causes.
 *                               This function calls:
 *                                   * external_irq_api_t::close
 **********************************************************************************************************************/
ssp_err_t SF_EXTERNAL_IRQ_Close (sf_external_irq_ctrl_t      * const p_api_ctrl)
{
    sf_external_irq_instance_ctrl_t * p_ctrl = (sf_external_irq_instance_ctrl_t *) p_api_ctrl;

#if SF_EXTERNAL_IRQ_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_lower_lvl_irq);
    SSP_ASSERT(NULL != p_ctrl->p_lower_lvl_irq->p_api);

    /** Verify control block is valid */
    SF_EXTERNAL_IRQ_ERROR_RETURN(OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
    SF_EXTERNAL_IRQ_ERROR_RETURN(NULL != p_ctrl->p_lower_lvl_irq->p_api->close, SSP_ERR_UNSUPPORTED);
#endif

    /* Error code of APIs called during close are not checked because returning error codes without completing the
       close process leaves the module in an undefined and unrecoverable state. */
    /** Close low level driver */
    p_ctrl->p_lower_lvl_irq->p_api->close(p_ctrl->p_lower_lvl_irq->p_ctrl);

    /** Clear information from control block so other functions know this instance is closed */
    p_ctrl->open = 0u;

    /** Delete the semaphore used */
    tx_semaphore_delete(&p_ctrl->semaphore);

    return SSP_SUCCESS;
} /* End of function SF_EXTERNAL_IRQ_Close() */

/*******************************************************************************************************************//**
 * @} (end defgroup SF_EXTERNAL_IRQ)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (SF_EXTERNAL_IRQ_CFG_PARAM_CHECKING_ENABLE)
/*******************************************************************************************************************//**
 * @brief        This is the parameter checking subroutine for the SF_EXTERNAL_IRQ_Open API.
 * @param[in]    p_ctrl              Control structure
 * @param[in]    p_cfg               Configuration structure
 * @retval       SSP_SUCCESS         The parameters are valid and the module is not in use.
 * @retval       SSP_ERR_ASSERTION   One of the following parameters may be NULL: p_ctrl, p_api, or p_cfg, or
 *                                   p_api->open. See HAL driver for other possible causes.
 * @retval       SSP_ERR_IN_USE      This channel is already open.
 **********************************************************************************************************************/
static ssp_err_t sf_external_irq_param_check (sf_external_irq_instance_ctrl_t * p_ctrl,
                                              sf_external_irq_cfg_t const * const   p_cfg)
{
    SSP_ASSERT(NULL != p_ctrl);
    SSP_ASSERT(NULL != p_cfg);
    SSP_ASSERT(NULL != p_cfg->p_lower_lvl_irq->p_api);
    SSP_ASSERT(NULL != p_cfg->p_lower_lvl_irq->p_api->open)
    SSP_ASSERT(NULL != p_cfg->p_lower_lvl_irq->p_cfg);
    SF_EXTERNAL_IRQ_ERROR_RETURN(OPEN != p_ctrl->open, SSP_ERR_IN_USE);

    return SSP_SUCCESS;
}/* End of function sf_external_irq_param_check() */
#endif /* SF_EXTERNAL_IRQ_CFG_PARAM_CHECKING_ENABLE*/

/******************************************************************************************************************//**
 * @brief  External IRQ SSP framework level callback
 * @param[in]  p_args                   Pointer to callback parameters
 **********************************************************************************************************************/
static void sf_external_irq_callback (external_irq_callback_args_t * p_args)
{
    if (p_args)
    {
        if (p_args->p_context)
        {
            /** Recover context from ISR */
            sf_external_irq_instance_ctrl_t * p_ctrl = (sf_external_irq_instance_ctrl_t *) (p_args->p_context);

            /** Verify control block is valid */
            if (OPEN != p_ctrl->open)
            {
                return;
            }

            /** Set semaphore */
            /* The return code is not checked here because tx_semaphore_ceiling_put cannot fail
               when called with valid input arguments. */
            tx_semaphore_ceiling_put(&p_ctrl->semaphore, (ULONG)1);
        }
    }
}
