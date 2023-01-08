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

/*************************************************************************//*******************************************
 * File Name    : sf_i2c.c
 * Description  : Source code for I2C framework API functions.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "tx_api.h"
#include "sf_i2c_api.h"
#include "sf_i2c.h"
#include "sf_i2c_private_api.h"

/*******************************************************************************************************************//**
 * @addtogroup SF_I2C
 * @brief SSP I2C framework driver API
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef SF_I2C_ERROR_RETURN
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define SF_I2C_ERROR_RETURN(expression, error) \
        SSP_ERROR_RETURN((expression), (error), &g_module_name[0], &g_sf_i2c_version)
#endif

/* Internal ThreadX mutex ID, used to know if a mutex is created. */
#define TX_MUTEX_ID                             ((ULONG) 0x4D555445)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
/* Callback functions for SSP framework */
static void sf_i2c_callback (i2c_callback_args_t * parg);

static ssp_err_t sf_i2c_common_start (sf_i2c_instance_ctrl_t * const p_ctrl, uint32_t const timeout);

static ssp_err_t sf_i2c_common_wait (sf_i2c_instance_ctrl_t * const p_ctrl, i2c_event_t event, uint32_t const timeout);

static ssp_err_t sf_i2c_common_finish (sf_i2c_instance_ctrl_t * const p_ctrl);

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
static bool sf_i2c_check_lower_lvl_driver_parameters (sf_i2c_cfg_t const * const p_cfg);

static bool sf_i2c_check_common_parameters (sf_i2c_ctrl_t * const p_ctrl, uint32_t const bytes);
#endif

static ssp_err_t sf_i2c_reconfigure_device (sf_i2c_instance_ctrl_t * const p_ctrl);

static ssp_err_t sf_i2c_lower_lvl_driver_open (sf_i2c_instance_ctrl_t * const p_ctrl, sf_i2c_cfg_t const * const p_cfg,
                                               i2c_cfg_t * tmp_cfg);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
#if defined(__GNUC__)
/* This structure is affected by warnings from the GCC compiler bug.
 * This pragma suppresses the warnings in this structure only, and will be removed when the SSP compiler is updated to
 * v5.3.*/
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
/** Version data structure used by error logger macro. */
static const ssp_version_t g_sf_i2c_version =
{
    .api_version_minor  = SF_I2C_API_VERSION_MINOR,
    .api_version_major  = SF_I2C_API_VERSION_MAJOR,
    .code_version_minor = SF_I2C_CODE_VERSION_MINOR,
    .code_version_major = SF_I2C_CODE_VERSION_MAJOR,
};
#if defined(__GNUC__)
/* Restore warning settings for 'missing-field-initializers' to as specified on command line. */
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic pop
#endif

#if BSP_CFG_ERROR_LOG != 0
static const char          g_module_name[] = "sf_i2c";
#endif

/***********************************************************************************************************************
 * Implementation of Interface
 **********************************************************************************************************************/
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const sf_i2c_api_t g_sf_i2c_on_sf_i2c =
{
    .open     = SF_I2C_Open,
    .read     = SF_I2C_Read,
    .write    = SF_I2C_Write,
    .reset    = SF_I2C_Reset,
    .close    = SF_I2C_Close,
    .lock     = SF_I2C_Lock,
    .unlock   = SF_I2C_Unlock,
    .version  = SF_I2C_VersionGet,
    .lockWait = SF_I2C_LockWait
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * @brief  Initialize a I2C bus and open low level I2C driver.
 * @retval SSP_SUCCESS                  I2C device is successfully opened.
 * @retval SSP_ERR_ASSERTION            One of the following parameters is NULL:
 *                                      p_api_ctrl, p_cfg,
 *                                      Pointer to Open, Close, Read, Write, or reset API interfaces,p_cfg->p_bus.
 * @retval SSP_ERR_INTERNAL             Internal error occurred.
 * @retval SSP_ERR_ALREADY_OPEN         Same I2C framework device is already open.
 * @return See @ref Common_Error_Codes and lower level driver function for other possible return codes.
 *         This driver function is
 *         * i2c_api_master_t::open
 * @note This function is reentrant for any channel.
 * @note Control handle must be cleared by caller before calling this function.
 **********************************************************************************************************************/
ssp_err_t SF_I2C_Open (sf_i2c_ctrl_t * const p_api_ctrl, sf_i2c_cfg_t const * const p_cfg)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    /* Perform parameter checking */
    SSP_ASSERT(NULL != p_cfg);
    SSP_ASSERT(NULL != p_ctrl);
    /* Perform Lower level driver parameter checking */
    bool error_flag = true;
    error_flag = sf_i2c_check_lower_lvl_driver_parameters(p_cfg);
    SF_I2C_ERROR_RETURN((true == error_flag), SSP_ERR_ASSERTION);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    /** Check whether device is already opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED != p_ctrl->dev_state), SSP_ERR_ALREADY_OPEN);

    ssp_err_t err = SSP_SUCCESS;
    i2c_cfg_t tmp_cfg = {0U};
    UINT status = TX_MUTEX_ERROR;

    p_ctrl->p_bus  = p_cfg->p_bus;                                                /** Copy bus pointer to control */

    memcpy(&tmp_cfg, p_cfg->p_lower_lvl_cfg, sizeof(i2c_cfg_t));

    /** Set framework level callback function. */
    tmp_cfg.p_callback = sf_i2c_callback;

    /** Save context for use in ISRs. */
    tmp_cfg.p_context = (void *) p_ctrl;

    /* Use bus channel in device open. */
    tmp_cfg.channel = p_cfg->p_bus->channel;

    while (TX_SUCCESS != status)
    {
        /** Enter a critical section before checking the device count mutex status. */
        SSP_CRITICAL_SECTION_DEFINE;
        SSP_CRITICAL_SECTION_ENTER;

        /** Check if device count mutex is already created. If not then create the mutex. */
        if (TX_MUTEX_ID != p_ctrl->p_bus->device_count_mutex.tx_mutex_id)
        {
            /** Create device_count_mutex. This is used to protect shared variable device_count
             *  in bus control structure. */
            status = tx_mutex_create(&(p_ctrl->p_bus->device_count_mutex), (CHAR *)"SF_I2C device count mutex",
                                     TX_INHERIT);
            if (TX_SUCCESS != status)
            {
                /** If mutex create fails, return error. */
                SSP_ERROR_LOG(SSP_ERR_INTERNAL, &g_module_name[0], &g_sf_i2c_version);
                SSP_CRITICAL_SECTION_EXIT;
                return SSP_ERR_INTERNAL;
            }
        }
        /** Exit critical section */
        SSP_CRITICAL_SECTION_EXIT;

        /** Acquire the device count mutex before accessing the shared resource.
         *  Try again if the mutex was deleted in close. */
        status = tx_mutex_get(&(p_ctrl->p_bus->device_count_mutex), TX_WAIT_FOREVER);
    }

    /* Open only for the first device on the bus.*/
    err = sf_i2c_lower_lvl_driver_open(p_ctrl, p_cfg, &tmp_cfg);
    SF_I2C_ERROR_RETURN((SSP_SUCCESS == err), err);

    /** Increment device count.*/
    p_ctrl->p_bus->device_count++;

    /** Release the device count mutex */
    status = tx_mutex_put(&(p_ctrl->p_bus->device_count_mutex));
    SF_I2C_ERROR_RETURN(TX_SUCCESS == status, SSP_ERR_INTERNAL);

    /** Save device configuration for reconfiguration.*/
    memcpy(&p_ctrl->lower_lvl_cfg, &tmp_cfg, sizeof(tmp_cfg));

    /** Set device state as Opened.*/
    p_ctrl->dev_state = SF_I2C_DEV_STATE_OPENED;

    /** Initialize restarted flag to false.*/
    p_ctrl->restarted = false;

    return err;
} /* End of function SF_I2C_Open() */

/******************************************************************************************************************//**
 * @brief  Start the transfer process and receive data from I2C device.
 * @retval SSP_SUCCESS                  Data received successfully.
 * @retval SSP_ERR_NOT_OPEN             Device instance not opened.
 * @retval SSP_ERR_ASSERTION            One of the following parameters is NULL:
 *                                      p_api_ctrl, p_dest, bytes, timeout.
 * @return See @ref Common_Error_Codes and lower level driver function for other possible return codes.
 *         This driver function is:
 *         * i2c_api_master_t::read
 **********************************************************************************************************************/
ssp_err_t SF_I2C_Read (sf_i2c_ctrl_t           * const p_api_ctrl,
                       uint8_t                 * const p_dest,
                       uint32_t const                  bytes,
                       bool const                      restart,
                       uint32_t const                  timeout)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    /* Perform parameter checking. */
    bool error_flag = true;
    error_flag = sf_i2c_check_common_parameters(p_ctrl, bytes);
    SF_I2C_ERROR_RETURN((true == error_flag), SSP_ERR_ASSERTION);
    SSP_ASSERT(NULL != p_dest);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    ssp_err_t err = SSP_SUCCESS;

    /** Check whether device is opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED == p_ctrl->dev_state), SSP_ERR_NOT_OPEN);

    /** Start transfer process - check reconfiguration, get Mutex. */
    err = sf_i2c_common_start(p_ctrl, timeout);
    SF_I2C_ERROR_RETURN((SSP_SUCCESS == err), err);

    sf_i2c_instance_ctrl_t * p_temp;
    p_temp = (sf_i2c_instance_ctrl_t *) (*p_ctrl->p_bus->pp_curr_bus_ctrl);    /** Get the low level control in use.*/

    /** Perform read. */
    err = p_ctrl->p_bus->p_lower_lvl_api->read(p_temp->p_lower_lvl_ctrl, p_dest, bytes, restart);
    if (SSP_SUCCESS == err)
    {
        /* Update restarted flag */
        p_ctrl->restarted = (restart == true) ? true : false;

        /** Wait for callback to set event flag. */
        err = sf_i2c_common_wait(p_ctrl, I2C_EVENT_RX_COMPLETE, timeout);
        if (SSP_SUCCESS != err)
        {
            SSP_ERROR_LOG(err, &g_module_name[0], &g_sf_i2c_version);

            /* Finish transfer.*/
            sf_i2c_common_finish(p_ctrl);
            return err;
        }
    }
    else
    {
        SSP_ERROR_LOG(err, &g_module_name[0], &g_sf_i2c_version);

        /* Finish transfer. */
        sf_i2c_common_finish(p_ctrl);
        return err;
    }

    /** Finish transfer. */
    err = sf_i2c_common_finish(p_ctrl);

    return err;
} /* End of function SF_I2C_Read() */

/******************************************************************************************************************//**
 * @brief  Start the transfer process and send data on I2C bus.
 * @retval SSP_SUCCESS                  Data written successfully.
 * @retval SSP_ERR_NOT_OPEN             Device instance not opened.
 * @retval SSP_ERR_ASSERTION            One of the following parameters is NULL:
 *                                      p_api_ctrl, p_src, bytes.
 * @return See @ref Common_Error_Codes and lower level driver function for other possible return codes.
 *         This driver function is:
 *         * i2c_api_master_t::write
 **********************************************************************************************************************/
ssp_err_t SF_I2C_Write (sf_i2c_ctrl_t          * const p_api_ctrl,
                        uint8_t                * const p_src,
                        uint32_t const                 bytes,
                        bool const                     restart,
                        uint32_t const                 timeout)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    /* Perform parameter checking. */
    bool error_flag = true;
    error_flag = sf_i2c_check_common_parameters(p_ctrl, bytes);
    SF_I2C_ERROR_RETURN((true == error_flag), SSP_ERR_ASSERTION);
    SSP_ASSERT(NULL != p_src);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    ssp_err_t err = SSP_SUCCESS;

    /** Check whether device is opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED == p_ctrl->dev_state), SSP_ERR_NOT_OPEN);

    /** Start transfer process - check reconfiguration, get Mutex. */
    err = sf_i2c_common_start(p_ctrl, timeout);
    SF_I2C_ERROR_RETURN((SSP_SUCCESS == err), err);

    sf_i2c_instance_ctrl_t * p_temp;
    p_temp = (sf_i2c_instance_ctrl_t *) (*p_ctrl->p_bus->pp_curr_bus_ctrl);    /** Get the low level control in use.*/

    /** Perform write. */
    err = p_ctrl->p_bus->p_lower_lvl_api->write(p_temp->p_lower_lvl_ctrl, p_src, bytes, restart);
    if (SSP_SUCCESS == err)
    {
        /* Update restarted flag */
        p_ctrl->restarted = (restart == true) ? true : false;

        /** Wait for callback to set event flag. */
        err = sf_i2c_common_wait(p_ctrl, I2C_EVENT_TX_COMPLETE, timeout);
        if (SSP_SUCCESS != err)
        {
            SSP_ERROR_LOG(err, &g_module_name[0], &g_sf_i2c_version);

            /* Finish transfer. */
            sf_i2c_common_finish(p_ctrl);
            return err;
        }
    }
    else
    {
        SSP_ERROR_LOG(err, &g_module_name[0], &g_sf_i2c_version);

        /* Finish transfer. */
        sf_i2c_common_finish(p_ctrl);
        return err;
    }

    /** Finish transfer. */
    err = sf_i2c_common_finish(p_ctrl);

    return err;
} /* End of function SF_I2C_Write() */

/******************************************************************************************************************//**
 * @brief  Abort any in-progress transfer.
 * @retval SSP_SUCCESS                  Channel was reseted without issue.
 * @retval SSP_ERR_NOT_OPEN             Device was not even opened.
 * @retval SSP_ERR_IN_USE               In-use error.
 * @retval SSP_ERR_INTERNAL             Internal error occurred.
 * @retval SSP_ERR_ASSERTION            Following parameters is NULL:
 *                                      p_api_ctrl.
 * @return See @ref Common_Error_Codes and lower level driver function for other possible return codes.
 *         This driver function is:
 *         * i2c_api_master_t::reset
 *********************************************************************************************************************/
ssp_err_t SF_I2C_Reset (sf_i2c_ctrl_t  * const p_api_ctrl, uint32_t const timeout)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    ssp_err_t err = SSP_SUCCESS;
    UINT  status  = TX_SUCCESS;

    /** Check whether device is opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED == p_ctrl->dev_state), SSP_ERR_NOT_OPEN);

    sf_i2c_instance_ctrl_t * p_temp;
    p_temp = (sf_i2c_instance_ctrl_t *) (*p_ctrl->p_bus->pp_curr_bus_ctrl);    /** Get the low level control in use.*/

    /** Get mutex since this will access hardware registers. */
    status = tx_mutex_get(p_ctrl->p_bus->p_lock_mutex, timeout);
    SF_I2C_ERROR_RETURN(TX_SUCCESS == status, SSP_ERR_IN_USE);

    /* Perform lower level reset. */
    err = p_ctrl->p_bus->p_lower_lvl_api->reset(p_temp->p_lower_lvl_ctrl);

    /* Release mutex taken for any restarted transfer. */
    if (true == p_ctrl->restarted)
    {
        /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
         * current thread. The mutex is owned by the current thread because this call follows a successful call to
         * mutex get */
        tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);
        p_ctrl->restarted = false;
    }

    /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
     * current thread. The mutex is owned by the current thread because this call follows a successful call to
     * mutex get */
    tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);

    return err;
} /* End of function SF_I2C_Reset() */

/******************************************************************************************************************//**
 * @brief  Close the I2C device designated by the control handle and close the RTOS services used by the bus
           if last device is connected to the bus calls this API, else decrement the device count.
 * @retval SSP_SUCCESS                  Device is successfully closed.
 * @retval SSP_ERR_NOT_OPEN             Device was not even opened.
 * @retval SSP_ERR_ASSERTION            Following parameters is NULL:
 *                                      p_api_ctrl.
 * @return See @ref Common_Error_Codes and lower level driver function for other possible return codes.
 *         This driver function is:
 *         * i2c_api_master_t::close
 * @note This function is reentrant for any device.
 **********************************************************************************************************************/
ssp_err_t SF_I2C_Close (sf_i2c_ctrl_t * const p_api_ctrl)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    /* Perform parameter checking. */
    SSP_ASSERT(NULL != p_ctrl);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    ssp_err_t err = SSP_SUCCESS;

    /** Check whether device is opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED == p_ctrl->dev_state), SSP_ERR_NOT_OPEN);

    /** Acquire the device count mutex before accessing the shared resource in close. */
    /* The return codes are not checked here because Close API should not return an error except for
     * parameter checking */
    tx_mutex_get(&(p_ctrl->p_bus->device_count_mutex), TX_WAIT_FOREVER);

    /** Check the count of opened devices on the bus. If there are no devices opened or all other devices on the bus
     *  are closed then close the low level I2C driver and release the RTOS services used by the bus. */
    if (1U == p_ctrl->p_bus->device_count)
    {
        /** Get the low level control in use.*/
        sf_i2c_instance_ctrl_t * p_temp;
        p_temp = (sf_i2c_instance_ctrl_t *) (*p_ctrl->p_bus->pp_curr_bus_ctrl);

        /** Close low level driver.*/
        p_ctrl->p_bus->p_lower_lvl_api->close(p_temp->p_lower_lvl_ctrl);

        /** Delete RTOS services used by the bus.*/
        /* The return codes are not checked here because mutex and event_flag delete call cannot fail when called
         * with created RTOS objects. This object was successfully created in open function. */
        tx_mutex_delete(p_ctrl->p_bus->p_lock_mutex);
        tx_event_flags_delete(p_ctrl->p_bus->p_sync_eventflag);

        /** Decrement device count.*/
        p_ctrl->p_bus->device_count--;

        /** Delete the device count mutex */
        /* The return codes are not checked here because mutex delete call cannot fail when called
         * with created RTOS objects. This object was successfully created in open function. */
        tx_mutex_delete(&(p_ctrl->p_bus->device_count_mutex));
    }
    else
    {
        /** Decrement device count.*/
        p_ctrl->p_bus->device_count--;

        /** Release the device count mutex */
        /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
         * current thread. The mutex is owned by the current thread because this call follows a successful call to
         * mutex get */
        tx_mutex_put(&(p_ctrl->p_bus->device_count_mutex));
    }

    /** Set device to closed state and restarted flag to false.*/
    p_ctrl->dev_state = SF_I2C_DEV_STATE_CLOSED;

    p_ctrl->restarted = false;

    return err;
}  /* End of function SF_I2C_Close() */

/******************************************************************************************************************//**
 * @brief  Lock the bus for a device. Once bus is locked by a device it can not be used by other devices.
 * @retval SSP_SUCCESS                  I2C channel is successfully locked.
 * @retval SSP_ERR_NOT_OPEN             Device not opened.
 * @retval SSP_ERR_IN_USE               In-use error.
 * @retval SSP_ERR_ASSERTION            Following parameters is NULL:
 *                                      p_api_ctrl.
 * @note This function is reentrant for any device.
 **********************************************************************************************************************/
ssp_err_t SF_I2C_Lock (sf_i2c_ctrl_t * const p_api_ctrl)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    /* Perform parameter checking */
    SSP_ASSERT(NULL != p_ctrl);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    ssp_err_t err = SSP_SUCCESS;
    UINT  status  = TX_SUCCESS;

    /** Check whether device is opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED == p_ctrl->dev_state), SSP_ERR_NOT_OPEN);

    /** Get mutex since this will access hardware registers. */
    status = tx_mutex_get(p_ctrl->p_bus->p_lock_mutex, TX_NO_WAIT);
    SF_I2C_ERROR_RETURN(TX_SUCCESS == status, SSP_ERR_IN_USE);

    /** Reconfigure the device address, if necessary */
    err = sf_i2c_reconfigure_device (p_ctrl);
    if (SSP_SUCCESS != err)
    {
        /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
         * current thread. The mutex is owned by the current thread because this call follows a successful call to
         * mutex get */
        tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);
        SSP_ERROR_LOG(err, &g_module_name[0], &g_sf_i2c_version);
        return err;
    }

    return err;
}  /* End of function SF_I2C_Lock() */

/******************************************************************************************************************//**
 * @brief  Unlock the locked bus and make the bus usable for other devices.
 * @retval SSP_SUCCESS                  I2C bus is successfully unlocked.
 * @retval SSP_ERR_NOT_OPEN             Device not opened.
 * @retval SSP_ERR_IN_USE               In-use error.
 * @retval SSP_ERR_ASSERTION            Following parameters is NULL:
 *                                      p_api_ctrl.
 * @note This function is reentrant for any device.
 **********************************************************************************************************************/
ssp_err_t SF_I2C_Unlock (sf_i2c_ctrl_t * const p_api_ctrl)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    /* Perform parameter checking */
    SSP_ASSERT(NULL != p_ctrl);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    ssp_err_t err = SSP_SUCCESS;
    UINT  status  = TX_SUCCESS;

    /** Check whether device is opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED == p_ctrl->dev_state), SSP_ERR_NOT_OPEN);

    /** Release the mutex so that others can use the bus. */
    status = tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);
    SF_I2C_ERROR_RETURN(TX_SUCCESS == status, SSP_ERR_IN_USE);

    return err;
}  /* End of function SF_I2C_Unlock() */

/******************************************************************************************************************//**
  * @brief  Get the version information of the framework.
 * @retval SSP_SUCCESS                  Got version number successfully.
 * @retval SSP_ERR_ASSERTION            Following parameters is NULL:
 *                                      p_version.
 **********************************************************************************************************************/
ssp_err_t SF_I2C_VersionGet (ssp_version_t   * const p_version)
{
    /** Checks error. Further parameter checking can be done at the driver layer. */
#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
	SSP_ASSERT(p_version != NULL);
#endif

    p_version->version_id = g_sf_i2c_version.version_id;

    return SSP_SUCCESS;
}  /* End of function SF_I2C_VersionGet() */

/******************************************************************************************************************//**
 * @brief  Lock the I2C Bus resource. Once bus is locked by a device it can not be used by other devices.
 * @retval SSP_SUCCESS          I2C channel is successfully locked within the specified timeout.
 * @retval SSP_ERR_ASSERTION    Pointer to I2C control block is NULL.
 * @retval SSP_ERR_NOT_OPEN     Device not opened.
 * @retval SSP_ERR_TIMEOUT      Mutex not available in timeout.
 * @note   This function is reentrant for any device.
 **********************************************************************************************************************/
ssp_err_t SF_I2C_LockWait (sf_i2c_ctrl_t * const p_api_ctrl, uint32_t const timeout)
{
    sf_i2c_instance_ctrl_t * p_ctrl = (sf_i2c_instance_ctrl_t *) p_api_ctrl;

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
    /* Perform parameter checking */
    SSP_ASSERT(p_ctrl);
#endif /* if SF_I2C_CFG_PARAM_CHECKING_ENABLE */

    ssp_err_t err = SSP_SUCCESS;
    UINT  status  = TX_SUCCESS;

    /** Check whether device is opened or not. */
    SF_I2C_ERROR_RETURN((SF_I2C_DEV_STATE_OPENED == p_ctrl->dev_state), SSP_ERR_NOT_OPEN);

    /** Get the mutex for this device. */
    status = tx_mutex_get(p_ctrl->p_bus->p_lock_mutex, timeout);
    SF_I2C_ERROR_RETURN(TX_SUCCESS == status, SSP_ERR_TIMEOUT);

    /** Reconfigure the device address, if necessary */
    err = sf_i2c_reconfigure_device (p_ctrl);
    if (SSP_SUCCESS != err)
    {
        /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
         * current thread. The mutex is owned by the current thread because this call follows a successful call to
         * mutex get */
        tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);
        SSP_ERROR_LOG(err, &g_module_name[0], &g_sf_i2c_version);
        return err;
    }

    return err;
}  /* End of function SF_I2C_LockWait() */

/*******************************************************************************************************************//**
 * @} (end addtogroup SF_I2C)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * @brief  Common I2C transfer start function. Used in all framework read write calls.
 *         This function checks is there any need for reconfiguration and gets the mutex and reconfigures if required.
 * @param[in]  p_ctrl                   Control handle for I2C framework driver context for a device.
 * @param[in]  timeout                  ThreadX timeout.
 * @retval SSP_SUCCESS                  Transfer started successfully.
 * @retval SSP_ERR_INTERNAL             Internal error occurred.
 * @note This function is reentrant for any device.
 **********************************************************************************************************************/
static ssp_err_t sf_i2c_common_start (sf_i2c_instance_ctrl_t * const p_ctrl,
                                      uint32_t const        timeout)
{
    ssp_err_t err    = SSP_SUCCESS;
    UINT      status = TX_SUCCESS;

    /* Clear event flag to get new events */
    tx_event_flags_set(p_ctrl->p_bus->p_sync_eventflag, TX_CLEAR_ID, TX_AND);

    /** Get the mutex for this device. */
    status = tx_mutex_get(p_ctrl->p_bus->p_lock_mutex, timeout);
    if (status == TX_SUCCESS)
    {
        /** Reconfigure the device address, if necessary */
        /* If reconfigure device fails, tx_mutex_put() is called to release the mutex. */
        err = sf_i2c_reconfigure_device (p_ctrl);
        if (SSP_SUCCESS != err)
        {
            /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
             * current thread. The mutex is owned by the current thread because this call follows a successful call to
             * mutex get */
            tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);
            return err;
        }

        /* If restarted flag is true, tx_mutex_put() is called. This just decrement the mutex count which was acquires
         * from previous operation, it does not actually releases the mutex. */
        if (true == p_ctrl->restarted)
        {
            /* The return code is not checked here because mutex put cannot fail when called with a mutex owned by the
             * current thread. The mutex is owned by the current thread because this call follows a successful call to
             * mutex get */
            tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);
        }
    }
    else
    {
        err = SSP_ERR_INTERNAL;
    }

    return err;
}

/******************************************************************************************************************//**
 * @brief  Common I2C wait. Waits for an operation to finish.
 * @param[in]  p_ctrl                   Control handle for I2C framework driver context for a device
 * @param[in]  event                    Event
 * @param[in]  timeout                  ThreadX timeout
 * @retval SSP_SUCCESS                  Data transmitted successfully.
 * @retval SSP_ERR_TRANSFER_ABORTED     Transfer aborted.
 * @retval SSP_ERR_INTERNAL             Internal error occurred.
 * @retval SSP_ERR_TIMEOUT              Transfer could not complete in the given time period.
 * @note This function is reentrant for any device.
 **********************************************************************************************************************/
static ssp_err_t sf_i2c_common_wait (sf_i2c_instance_ctrl_t * const p_ctrl,
                                     i2c_event_t           event,
                                     uint32_t const        timeout)
{
    ssp_err_t err    = SSP_SUCCESS;
    UINT      status = TX_SUCCESS;
    ULONG     actual_flags = 0U;
    sf_i2c_instance_ctrl_t * p_temp;
    p_temp = (sf_i2c_instance_ctrl_t *) (*p_ctrl->p_bus->pp_curr_bus_ctrl);

    /* Wait for operation to finish */
    status = tx_event_flags_get(p_ctrl->p_bus->p_sync_eventflag,
                                (1U << (ULONG) event) | (1U << I2C_EVENT_ABORTED),
                                TX_OR_CLEAR,
                                &actual_flags,
                                timeout);

    if (TX_SUCCESS == status)
    {
        if ((actual_flags & (ULONG) (1U << I2C_EVENT_ABORTED)) != 0)
        {
           err = SSP_ERR_TRANSFER_ABORTED;
        }
    }
    else if (TX_NO_EVENTS == status)
    {
        /* Aborts any in-progress transfer and reset the IIC peripheral because timeout error occurred */
        p_ctrl->restarted = false;
        err = p_ctrl->p_bus->p_lower_lvl_api->reset(p_temp->p_lower_lvl_ctrl);
        if ((SSP_SUCCESS == err) || (SSP_ERR_ABORTED == err))
        {
            err = SSP_ERR_TIMEOUT;
        }
    }
    else
    {
        err = SSP_ERR_INTERNAL;
    }
    return err;
}

/******************************************************************************************************************//**
 * @brief  Common I2C finish. Release mutex.
 * @param[in]  p_ctrl                   Control handle for I2C framework driver context for a device
 * @retval SSP_SUCCESS                  Transfer finished successfully.
 * @note This function is reentrant for any device.
 **********************************************************************************************************************/
static ssp_err_t sf_i2c_common_finish (sf_i2c_instance_ctrl_t * const p_ctrl)
{
    /** Release mutex only if the restart condition is not issued to the bus. */
    if (false == p_ctrl->restarted)
    {
        /* Release mutex. The return code is not checked here because mutex put cannot fail when called with a mutex
         * owned by the current thread. The mutex is owned by the current thread because this call follows a successful
         * call to mutex get from common start function. */
        tx_mutex_put(p_ctrl->p_bus->p_lock_mutex);
    }
    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief  I2C SSP framework level callback
 * @param[in]  p_args                   Pointer to callback parameters
 * @retval void
 **********************************************************************************************************************/
static void sf_i2c_callback (i2c_callback_args_t * p_args)
{
    sf_i2c_instance_ctrl_t * p_ctrl  = (sf_i2c_instance_ctrl_t *) p_args->p_context;
    TX_EVENT_FLAGS_GROUP * pevtflg = p_ctrl->p_bus->p_sync_eventflag;

    /* Set flag to trigger waiting thread. The return code is not checked here because flag set cannot fail when
     * called with created RTOS objects. These objects were successfully created in this function */
    tx_event_flags_set(pevtflg, (ULONG) (1U << (p_args->event)), TX_OR);
}

#if SF_I2C_CFG_PARAM_CHECKING_ENABLE
/******************************************************************************************************************//**
 * @brief  Checks whether lower level I2C module and bus are configured.
 * @param[in]  p_cfg                    Pointer to I2C framework Configuration Structure
 * @retval true                         Lower level I2C driver, and I2C bus are configured.
 * @retval false                        Lower level I2C driver, and I2C bus are not configured.
 **********************************************************************************************************************/
static bool sf_i2c_check_lower_lvl_driver_parameters(sf_i2c_cfg_t const * const p_cfg)
{
    bool ret = true;

    /* Perform parameter checking. */
    if (((((NULL == p_cfg->p_bus->p_lower_lvl_api->open)
            || (NULL == p_cfg->p_bus->p_lower_lvl_api->close))
            || (NULL == p_cfg->p_bus->p_lower_lvl_api->read)))
            || (NULL == p_cfg->p_bus->p_lower_lvl_api->write)
            || (NULL == p_cfg->p_bus->p_lower_lvl_api->reset)
            || (NULL == p_cfg->p_bus)
            || (NULL == p_cfg->p_lower_lvl_cfg))
    {
        ret = false;
    }

    return ret;
}

/******************************************************************************************************************//**
 * @brief  Check if I2C framework control block address and number of bytes are not NULL.
 * @param[in]  p_ctrl                   Pointer to I2C framework control block
 * @param[in]  bytes                    Number of bytes of data to be transferred
 * @retval true                         I2C framework control block address, number of bytes are not NULL.
 * @retval false                        I2C framework control block address, number of bytes are NULL.
 **********************************************************************************************************************/
static bool sf_i2c_check_common_parameters(sf_i2c_ctrl_t * const p_ctrl, uint32_t const bytes)
{
    bool ret = true;

    if ((NULL == p_ctrl) || (0 == bytes))
    {
        ret = false;
    }
    return ret;
}
#endif

/******************************************************************************************************************//**
 * @brief  Assign a slave address of new device to current device on the bus.
 * @param[in]  p_ctrl                   Control handle for I2C framework context for a device
 * @retval SSP_SUCCESS                  New device slave address assigned to current device
 * @return See @ref Common_Error_Codes and lower level drivers for other possible return codes.
 *         These driver functions are:
 *         * i2c_api_master_t::slaveAddressSet
 **********************************************************************************************************************/
static ssp_err_t sf_i2c_reconfigure_device (sf_i2c_instance_ctrl_t * const p_ctrl)
{
    ssp_err_t err = SSP_SUCCESS;

    if (*p_ctrl->p_bus->pp_curr_ctrl != (sf_i2c_instance_ctrl_t *) p_ctrl)
    {
        /** Reconfigure the device by changing the slave address. */
        sf_i2c_instance_ctrl_t * p_temp;

        /* Get the low level control in use. */
        p_temp = (sf_i2c_instance_ctrl_t *) (*p_ctrl->p_bus->pp_curr_bus_ctrl);

        /** Change the slave address and addressing mode. */
        err = p_ctrl->p_bus->p_lower_lvl_api->slaveAddressSet(p_temp->p_lower_lvl_ctrl,
                                                              p_ctrl->lower_lvl_cfg.slave,
                                                              p_ctrl->lower_lvl_cfg.addr_mode);
        if (SSP_SUCCESS == err)
        {
            /** Assign this device to current. */
            *p_ctrl->p_bus->pp_curr_ctrl = (sf_i2c_instance_ctrl_t *) p_ctrl;
        }
    }
    return err;
}

/******************************************************************************************************************//**
 * @brief  Opens lover level driver on the bus.
 * @param[in,out]  p_ctrl                   Control handle for I2C framework context for a device.
 * @param[in]      p_cfg                    Pointer to I2C framework Configuration Structure.
 * @param[in]      tmp_cfg                  Low level configuration used to configure the low level driver.
 * @retval SSP_SUCCESS                      New device slave address assigned to current device
 * @retval SSP_ERR_INTERNAL                 Internal error occurred.
 * @return See @ref Common_Error_Codes and lower level drivers for other possible return codes.
 *         These driver functions are:
 *         * i2c_api_master_t::open
 **********************************************************************************************************************/
static ssp_err_t sf_i2c_lower_lvl_driver_open (sf_i2c_instance_ctrl_t * const p_ctrl, sf_i2c_cfg_t const * const p_cfg,
                                               i2c_cfg_t * tmp_cfg)
{
    ssp_err_t err = SSP_SUCCESS;
    /* Open only for the first device on the bus.
     * If the device requires a bus reconfiguration then that will happen when a later read/write occurs. */
    if (0U == p_ctrl->p_bus->device_count)
    {
        UINT status = TX_SUCCESS;

        /** Create mutex for this bus. */
        status = tx_mutex_create(p_ctrl->p_bus->p_lock_mutex, (CHAR *) (p_ctrl->p_bus->p_bus_name), TX_INHERIT);
        if (TX_SUCCESS != status)
        {
            /* Return codes are not checked in error condition processing because these objects were created
             * during this function. */
            tx_mutex_delete(&(p_ctrl->p_bus->device_count_mutex));
            SSP_ERROR_LOG(SSP_ERR_INTERNAL, &g_module_name[0], &g_sf_i2c_version);
            return SSP_ERR_INTERNAL;
        }

        /** Create Event flag for this bus. */
        status = tx_event_flags_create(p_ctrl->p_bus->p_sync_eventflag, (CHAR *) (p_ctrl->p_bus->p_bus_name));
        if (TX_SUCCESS != status)
        {
            /* Return codes are not checked in error condition processing because these objects were created
             * during this function. */
            tx_mutex_delete(p_ctrl->p_bus->p_lock_mutex);
            tx_mutex_delete(&(p_ctrl->p_bus->device_count_mutex));
            SSP_ERROR_LOG(SSP_ERR_INTERNAL, &g_module_name[0], &g_sf_i2c_version);
            return SSP_ERR_INTERNAL;
        }

        /** Open low level. */
        err = p_cfg->p_bus->p_lower_lvl_api->open(p_ctrl->p_lower_lvl_ctrl, tmp_cfg);
        if (SSP_SUCCESS != err)
        {
            /* Return codes are not checked in error condition processing because these objects were created
             * during this function. */
            tx_mutex_delete(p_ctrl->p_bus->p_lock_mutex);
            tx_mutex_delete(&(p_ctrl->p_bus->device_count_mutex));
            tx_event_flags_delete(p_ctrl->p_bus->p_sync_eventflag);
            SSP_ERROR_LOG(err, &g_module_name[0], &g_sf_i2c_version);
            return err;
        }

        /* Assign the device which is holding the low level bus,
         * same bus configuration can be used by other devices just by switching the slave address. */
        *p_ctrl->p_bus->pp_curr_bus_ctrl = (sf_i2c_instance_ctrl_t *) p_ctrl;

        /* Use this to check which device is currently communicating,
         * this will be updated after switching the address in the sf_i2c_common_start function */
        *p_ctrl->p_bus->pp_curr_ctrl = (sf_i2c_instance_ctrl_t *) p_ctrl;
    }
    return err;
}
/* End of file */
