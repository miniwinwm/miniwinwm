/***********************************************************************************************************************
 * Copyright [2018-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
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
 * File Name    : sf_touch_panel_chip_sx8654.c
 * Description  : Touch panel framework chip specific implementation for the SX8654 touch panel chip.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "sf_touch_panel_chip_sx8654.h"
#include "sf_touch_panel_v2.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define extract_x(t) ((int16_t) (((t).x_msb << 8) | ((t).x_lsb)))
#define extract_y(t) ((int16_t) (((t).y_msb << 8) | ((t).y_lsb)))
#define I2C_TIMEOUT                (10U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Driver-specific touch point register mapping */
typedef struct st_SX8654_touch
{
    uint8_t  x_msb  : 4;
    uint8_t  x_chan : 3;
    uint8_t         : 1;
    uint8_t  x_lsb;

    uint8_t  y_msb  : 4;
    uint8_t  y_chan : 3;
    uint8_t         : 1;
    uint8_t  y_lsb  : 8;
} SX8654_touch_t;

/* Touch controller register addresses */
#define SX8654_REGTOUCH0    (0x00)
#define SX8654_REGCHANMSK   (0x04)
#define SX8654_REGPROX0     (0x0B)
#define SX8654_REGIRQMSK    (0x22)
#define SX8654_REGIRQSRC    (0x23)

/* Commands */
#define SX8654_CMD_PENTRG   (0xe0)
#define SX8654_CMD_READ_REG (0x40)

/* Bits for RegTouch0 (Address 0x00) */
#define SX8654_REG_TOUCH0_TOUCHRATE_200CPS  (0x7 << 4)
#define SX8654_REG_TOUCH0_POWDLY_8_9US      (0x4 << 0)

/* Pen detection circuit's pull-up resistor value */
#define SX8654_REG_TOUCH1_RPNDT_114KOHM     (0x0 << 2)
#define SX8654_REG_TOUCH1_RPNDT_228KOHM     (0x1 << 2)
#define SX8654_REG_TOUCH1_RPNDT_57KOHM      (0x2 << 2)
#define SX8654_REG_TOUCH1_RPNDT_28KOHM      (0x3 << 2)

/* Bits for RegTouch1 (Address 0x01) */
#define SX8654_REG_TOUCH1_RESERVED                   (0x1 << 5)
/* Change this configuration to one of the resistor value, based on the panel used*/
#define SX8654_REG_TOUCH1_RPDNT_RESISTOR_VALUE_CFG   (SX8654_REG_TOUCH1_RPNDT_228KOHM)
#define SX8654_REG_TOUCH1_FILT_NFILT3                (0x3 << 0)

/* Bits for RegTouch2 (Address 0x02) */
#define SX8654_REG_TOUCH2_SETDLY_8_9US      (0x4 << 0)

/* Bits for RegChanMsk (Address 0x4) */
#define SX8654_REGCHANMSK_XCONV             (0x1 << 7)
#define SX8654_REGCHANMSK_YCONV             (0x1 << 6)

/* Bits for RegProx0 (Address 0x0B) */
#define SX8654_REGPROX0_PROXSCANPERIOD_OFF  (0x0 << 0)

/* Bits for RegIrqMsk (Address 0x22) */
#define SX8654_REGIRQMSK_PENRELEASE         (0x1 << 2)
#define SX8654_REGIRQMSK_PENTOUCH_TOUCHCONVDONE (0x1 << 3)

/* Bits for RegIrqSrc (Address 0x23) */
#define SX8654_REGIRQSRC_PENRELEASEIRQ      (0x1 << 2)

/* ADC max output value (12-bit resolution) */
#define SX8654_MAX_ADC_OUTPUT_VALUE         (4095L)

/* I2C communication retry times */
#define SX8654_I2C_RETRY_TIMES              (10)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static ssp_err_t SX8654_open (sf_touch_panel_chip_ctrl_t * const p_ctrl,
                              sf_touch_panel_chip_cfg_t const * const p_cfg);

static ssp_err_t SX8654_payload_get (sf_touch_panel_chip_ctrl_t * const    p_ctrl,
                                     sf_touch_panel_v2_payload_t * const p_payload);

static ssp_err_t SX8654_reset (sf_touch_panel_chip_ctrl_t * const p_ctrl);

static ssp_err_t SX8654_i2c_read (sf_i2c_api_t const * const p_i2c_api, sf_i2c_ctrl_t * const p_i2c_ctrl,
                                  uint8_t * const p_dest, uint32_t const bytes);

static ssp_err_t SX8654_i2c_write (sf_i2c_api_t const * const p_i2c_api, sf_i2c_ctrl_t * const p_i2c_ctrl,
                                   uint8_t * const p_src, uint32_t const bytes, bool const restart );

static ssp_err_t SX8654_i2c_write_followed_by_read (sf_i2c_api_t const * const p_i2c_api,
                                                    sf_i2c_ctrl_t * const p_i2c_ctrl,
                                                    uint8_t * const p_data, uint32_t const bytes);

static ssp_err_t SX8654_close (sf_touch_panel_chip_ctrl_t * const p_ctrl);

static ssp_err_t SX8654_versionGet (ssp_version_t * const p_version);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static const ssp_version_t g_version =
{
    .api_version_minor  = SF_TOUCH_PANEL_CHIP_API_VERSION_MINOR,
    .api_version_major  = SF_TOUCH_PANEL_CHIP_API_VERSION_MAJOR,
    .code_version_major = SF_TOUCH_PANEL_CHIP_SX8654_CODE_VERSION_MAJOR,
    .code_version_minor = SF_TOUCH_PANEL_CHIP_SX8654_CODE_VERSION_MINOR
};

const sf_touch_panel_chip_api_t g_sf_touch_panel_chip_sx8654 =
{
    .open       = SX8654_open,
    .payloadGet = SX8654_payload_get,
    .reset      = SX8654_reset,
    .close      = SX8654_close,
    .versionGet = SX8654_versionGet
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Reads data from the touch controller through the I2C-BUS interface.
 **********************************************************************************************************************/
static ssp_err_t SX8654_i2c_read (sf_i2c_api_t const * const p_i2c_api, sf_i2c_ctrl_t * const p_i2c_ctrl,
                                  uint8_t * const p_dest, uint32_t const bytes)
{
    ssp_err_t err = SSP_SUCCESS;

    /** Performs I2C read operation. Retry some time if failed in the communication. */
    for (int i = 0; i < SX8654_I2C_RETRY_TIMES; i++)
    {
        p_i2c_api->lock(p_i2c_ctrl);
        err = p_i2c_api->read(p_i2c_ctrl, p_dest, bytes, false, I2C_TIMEOUT);
        p_i2c_api->unlock(p_i2c_ctrl);
        if (SSP_SUCCESS == err)
        {
            break;
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief  Writes data to the touch controller through the I2C-BUS interface.
 **********************************************************************************************************************/
static ssp_err_t SX8654_i2c_write (sf_i2c_api_t const * const p_i2c_api, sf_i2c_ctrl_t * const p_i2c_ctrl,
                                   uint8_t * const p_src, uint32_t const bytes, bool const restart)
{
    ssp_err_t err = SSP_SUCCESS;

    /** Performs I2C write operation. Retry some time if failed in the communication. */
    for (int i = 0; i < SX8654_I2C_RETRY_TIMES; i++)
    {
        p_i2c_api->lock(p_i2c_ctrl);
        err = p_i2c_api->write(p_i2c_ctrl, p_src, bytes, restart, I2C_TIMEOUT);
        p_i2c_api->unlock(p_i2c_ctrl);
        if (SSP_SUCCESS == err)
        {
            break;
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief  Write data to and read data from the touch controller through the I2C-BUS interface.
 **********************************************************************************************************************/
static ssp_err_t SX8654_i2c_write_followed_by_read (sf_i2c_api_t const * const p_i2c_api,
                                                    sf_i2c_ctrl_t * const p_i2c_ctrl,
                                                    uint8_t * const p_data, uint32_t const bytes)
{
    ssp_err_t err = SSP_SUCCESS;

    /** Performs I2C write followed by read. Retry some time if failed in the communication. */
    for (int i = 0; i < SX8654_I2C_RETRY_TIMES; i++)
    {
        p_i2c_api->lock(p_i2c_ctrl);
        /** Performs I2C write operation with requesting restart condition. */
        err = p_i2c_api->write(p_i2c_ctrl, p_data, bytes, true, I2C_TIMEOUT);
        p_i2c_api->unlock(p_i2c_ctrl);
        if (SSP_SUCCESS == err)
        {
            p_i2c_api->lock(p_i2c_ctrl);
            /** Performs I2C read operation. This starts from the restart condition. */
            err = p_i2c_api->read(p_i2c_ctrl, p_data, bytes, false, I2C_TIMEOUT);
            p_i2c_api->unlock(p_i2c_ctrl);
            if (SSP_SUCCESS == err)
            {
                break;
            }
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief  Opens the lower level drivers. Implements sf_touch_panel_chip_api_t::open.
 *
 * @param[in,out]  p_api_ctrl   Pointer to control block from touch panel framework.
 * @param[in]      p_cfg    Pointer to configuration structure. All elements of the structure must be set by user.
 **********************************************************************************************************************/
static ssp_err_t SX8654_open (sf_touch_panel_chip_ctrl_t * const p_api_ctrl,
                              sf_touch_panel_chip_cfg_t const * const p_cfg)
{
    sf_touch_panel_chip_sx8654_instance_ctrl_t * p_ctrl = (sf_touch_panel_chip_sx8654_instance_ctrl_t *) p_api_ctrl;

    /** Initialize previous event. */
    p_ctrl->last_payload.event_type = SF_TOUCH_PANEL_V2_EVENT_INVALID;
    p_ctrl->last_payload.x          = -1;
    p_ctrl->last_payload.y          = -1;

    sf_touch_panel_chip_on_sx8654_cfg_t const * const p_cfg_extend = p_cfg->p_extend;
    p_ctrl->p_lower_lvl_framewrk     = p_cfg_extend->p_lower_lvl_framewrk;
    p_ctrl->p_lower_lvl_irq          = p_cfg_extend->p_lower_lvl_irq;
    p_ctrl->pin                      = p_cfg_extend->pin;
    p_ctrl->hsize_pixels             = p_cfg_extend->hsize_pixels;
    p_ctrl->vsize_pixels             = p_cfg_extend->vsize_pixels;
    ssp_err_t err                    = SSP_SUCCESS;

    /** Initialize the lower level I2C framework. */
    err = p_cfg_extend->p_lower_lvl_framewrk->p_api->open(p_cfg_extend->p_lower_lvl_framewrk->p_ctrl,
                                                          p_cfg_extend->p_lower_lvl_framewrk->p_cfg);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    /** Initialize the lower level external IRQ driver. */
    err = p_cfg_extend->p_lower_lvl_irq->p_api->open(p_cfg_extend->p_lower_lvl_irq->p_ctrl,
                                                     p_cfg_extend->p_lower_lvl_irq->p_cfg);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Reads the touch event data from the touch controller. Implements sf_touch_panel_chip_api_t::payloadGet.
 * @param[in,out] p_api_ctrl     Pointer to a structure allocated by user. This control structure is initialized in
 *                           this function.
 * @param[out]    p_payload  Pointer to the payload data structure. Touch data provided should be processed to
 *                           logical pixel values.
 **********************************************************************************************************************/
static ssp_err_t SX8654_payload_get (sf_touch_panel_chip_ctrl_t * const p_api_ctrl,
                                     sf_touch_panel_v2_payload_t * const p_payload)
{
    sf_touch_panel_chip_sx8654_instance_ctrl_t * p_ctrl = (sf_touch_panel_chip_sx8654_instance_ctrl_t *) p_api_ctrl;

    sf_i2c_ctrl_t                     * p_i2c_ctrl    = p_ctrl->p_lower_lvl_framewrk->p_ctrl;
    sf_external_irq_ctrl_t            * p_irq_ctrl    = p_ctrl->p_lower_lvl_irq->p_ctrl;
    sf_i2c_api_t             const    * p_i2c_api     = p_ctrl->p_lower_lvl_framewrk->p_api;
    sf_external_irq_api_t    const    * p_irq_api     = p_ctrl->p_lower_lvl_irq->p_api;
    ssp_err_t                         err             = SSP_SUCCESS;

    /** Wait pin interrupt from touch controller. */
    err = p_irq_api->wait(p_irq_ctrl, TX_WAIT_FOREVER);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    /** Gets interrupt from a touch panel, which means the touch panel is pressed. */
    SX8654_touch_t touch[1];
    uint8_t reg;

    /* Initializes all return parameters */
    p_payload->x          = 0;
    p_payload->y          = 0;
    p_payload->event_type = SF_TOUCH_PANEL_V2_EVENT_DOWN;

    /* Read RegIrqSrc to determine if Released or Touching */
    reg = SX8654_CMD_READ_REG | SX8654_REGIRQSRC;

    /** Gets the released/touching status */
    err = SX8654_i2c_write_followed_by_read(p_i2c_api, p_i2c_ctrl, &reg, sizeof(reg));
    if (SSP_SUCCESS != err)
    {
        return SSP_ERR_INTERNAL;
    }

    if (reg & SX8654_REGIRQSRC_PENRELEASEIRQ)
    {
        p_payload->event_type = SF_TOUCH_PANEL_V2_EVENT_UP;
    }

    /** Gets X/Y coordinate data */
    err = SX8654_i2c_read(p_i2c_api, p_i2c_ctrl, (uint8_t *) &touch[0], sizeof(touch));
    if (SSP_SUCCESS != err)
    {
        return SSP_ERR_INTERNAL;
    }

    /** Processes the raw data for the touch point(s) into useful data */
    p_payload->x = (int16_t) (((int32_t) p_ctrl->hsize_pixels * (int32_t) extract_x(touch[0]))
                   / SX8654_MAX_ADC_OUTPUT_VALUE);
    p_payload->y = (int16_t) (((int32_t) p_ctrl->vsize_pixels * (int32_t) extract_y(touch[0]))
                   / SX8654_MAX_ADC_OUTPUT_VALUE);

    if(SF_TOUCH_PANEL_V2_EVENT_HOLD == p_ctrl->last_payload.event_type ||
       SF_TOUCH_PANEL_V2_EVENT_MOVE == p_ctrl->last_payload.event_type)
    {
        p_ctrl->last_payload.event_type = SF_TOUCH_PANEL_V2_EVENT_DOWN;
    }

    if(SF_TOUCH_PANEL_V2_EVENT_DOWN == p_ctrl->last_payload.event_type &&
       SF_TOUCH_PANEL_V2_EVENT_DOWN == p_payload->event_type)
    {
        if ((p_ctrl->last_payload.x != p_payload->x) || (p_ctrl->last_payload.y != p_payload->y))
        {
            p_payload->event_type = SF_TOUCH_PANEL_V2_EVENT_MOVE;
        }
        else
        {
            p_payload->event_type = SF_TOUCH_PANEL_V2_EVENT_HOLD;
        }
    }

    p_ctrl->last_payload.event_type = p_payload->event_type;

    if(p_payload->event_type == SF_TOUCH_PANEL_V2_EVENT_UP)
    {
        p_payload->x = p_ctrl->last_payload.x; /* SX8654 returns coordinates with the max value if PEN UP event happens.*/
        p_payload->y = p_ctrl->last_payload.y; /* Use the coordinates obtained at last PEN DOWN and do not save the one got this time. */
    }
    else
    {
        p_ctrl->last_payload.x = p_payload->x;
        p_ctrl->last_payload.y = p_payload->y;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief  Resets the touch chip. Implements sf_touch_panel_chip_api_t::reset.
 *
 * @param[in]  p_api_ctrl   Pointer to control block from touch panel framework.
 **********************************************************************************************************************/
static ssp_err_t SX8654_reset (sf_touch_panel_chip_ctrl_t * const p_api_ctrl)
{
    sf_touch_panel_chip_sx8654_instance_ctrl_t * p_ctrl = (sf_touch_panel_chip_sx8654_instance_ctrl_t *) p_api_ctrl;
    /* Parameter checking done in touch panel framework. */

    sf_i2c_api_t    const     * const p_i2c_api       = p_ctrl->p_lower_lvl_framewrk->p_api;
    sf_i2c_ctrl_t * const             p_i2c_ctrl      = p_ctrl->p_lower_lvl_framewrk->p_ctrl;
    ssp_err_t                         err             = SSP_SUCCESS;
    uint8_t                           command[4];

    /** Resets touch chip by setting GPIO reset pin low. */
    g_ioport_on_ioport.pinWrite(p_ctrl->pin, IOPORT_LEVEL_LOW);

    /** Waits for a while (keep the reset signal low longer than 1ms) */
    tx_thread_sleep(2);

    /** Releases touch chip from reset */
    g_ioport_on_ioport.pinWrite(p_ctrl->pin, IOPORT_LEVEL_HIGH);

    /** Waits just for a while before accessing touch chip */
    tx_thread_sleep(2);

    /** Writes a complete configuration generated by the SX8654 evaluation software */
    command[0] = SX8654_REGTOUCH0;
    command[1] = SX8654_REG_TOUCH0_TOUCHRATE_200CPS|SX8654_REG_TOUCH0_POWDLY_8_9US;
    command[2] = SX8654_REG_TOUCH1_RESERVED|SX8654_REG_TOUCH1_RPDNT_RESISTOR_VALUE_CFG|SX8654_REG_TOUCH1_FILT_NFILT3;
    command[3] = SX8654_REG_TOUCH2_SETDLY_8_9US;
    err        = SX8654_i2c_write(p_i2c_api, p_i2c_ctrl, command, 4, false);
    if (SSP_SUCCESS != err)
    {
        return SSP_ERR_INTERNAL;
    }

    /** The generated configuration enables too many conversion channels, ensure only
     * channels X and Y are enabled
     */
    command[0] = SX8654_REGCHANMSK;
    command[1] = SX8654_REGCHANMSK_XCONV | SX8654_REGCHANMSK_YCONV;
    err        = SX8654_i2c_write(p_i2c_api, p_i2c_ctrl, command, 2, false);
    if (SSP_SUCCESS != err)
    {
        return SSP_ERR_INTERNAL;
    }

    /** Enables the PenTouch/TouchConvDone and PenRelease interrupts */
    command[0] = SX8654_REGIRQMSK;
    command[1] = SX8654_REGIRQMSK_PENTOUCH_TOUCHCONVDONE | SX8654_REGIRQMSK_PENRELEASE;
    err        = SX8654_i2c_write(p_i2c_api, p_i2c_ctrl, command, 2, false);
    if (SSP_SUCCESS != err)
    {
        return SSP_ERR_INTERNAL;
    }

    /** Defines the proximity scan period - Turn off proximity as we don't currently use it */
    command[0] = SX8654_REGPROX0;
    command[1] = SX8654_REGPROX0_PROXSCANPERIOD_OFF;
    err        = SX8654_i2c_write(p_i2c_api, p_i2c_ctrl, command, 2, false);
    if (SSP_SUCCESS != err)
    {
        return SSP_ERR_INTERNAL;
    }

    /** Enables pen trigger mode */
    command[0] = SX8654_CMD_PENTRG;
    err        = SX8654_i2c_write(p_i2c_api, p_i2c_ctrl, command, 1, false);
    if (SSP_SUCCESS != err)
    {
        return SSP_ERR_INTERNAL;
    }

    /** Initializes the last touch event info. */
    p_ctrl->last_payload.event_type = SF_TOUCH_PANEL_V2_EVENT_NONE;

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Closes the lower level drivers. Implements sf_touch_panel_chip_api_t::close.
 *
 * @param[in,out]  p_api_ctrl   Pointer to control block from touch panel framework.
 **********************************************************************************************************************/
static ssp_err_t SX8654_close (sf_touch_panel_chip_ctrl_t * const p_api_ctrl)
{

    sf_touch_panel_chip_sx8654_instance_ctrl_t * p_ctrl = (sf_touch_panel_chip_sx8654_instance_ctrl_t *) p_api_ctrl;
    sf_i2c_ctrl_t * const                         p_i2c_ctrl  = p_ctrl->p_lower_lvl_framewrk->p_ctrl;
    ssp_err_t                                     err         = SSP_SUCCESS;

    /** Close the lower level external IRQ driver. */
    err = p_ctrl->p_lower_lvl_irq->p_api->close(p_ctrl->p_lower_lvl_irq->p_ctrl);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    /** Resets touch chip by setting GPIO reset pin low. */
    g_ioport_on_ioport.pinWrite(p_ctrl->pin, IOPORT_LEVEL_LOW);
    /** Waits for a while (keep the reset signal low longer than 1ms) */
    tx_thread_sleep(2);

    /** Close the lower level I2C framework. */
    err = p_ctrl->p_lower_lvl_framewrk->p_api->close(p_i2c_ctrl);
    if (SSP_ERR_ABORTED == err)
    {
      /** If I2C Abort returned from previous close, one more try to close I2C driver. */
      err = p_ctrl->p_lower_lvl_framewrk->p_api->close(p_i2c_ctrl);
    }
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    return SSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @brief Implements sf_touch_panel_chip_api_t::versionGet.
 *
 * @param[out]  p_version  Code and API version used are stored here.
 *********************************************************************************************************************/
static ssp_err_t SX8654_versionGet (ssp_version_t * const p_version)
{
#if SF_TOUCH_PANEL_V2_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_version);
#endif

    *p_version = g_version;

    return SSP_SUCCESS;
}
