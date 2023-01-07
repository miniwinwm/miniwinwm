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
 * File Name    : r_external_irq_api.h
 * Description  : API for external interrupt applications. Allows for external interrupt use.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup Interface_Library
 * @defgroup EXTERNAL_IRQ_API External IRQ Interface
 * @brief Interface for detecting external interrupts.
 *
 * @section EXTERNAL_IRQ_API_SUMMARY Summary
 * The external IRQ interface supports external inputs, for example input from pins or capacitive touch buttons.  When
 * an input trigger is detected, a user provided callback function will be called.
 *
 * Implemented by:
 * @ref ICU
 *
 * Related interfaces:
 * @ref KEYMATRIX_API
 *
 * Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * External IRQ Interface description: @ref HALEXTERNAL_IRQInterface
 * @{
 **********************************************************************************************************************/

#ifndef DRV_EXTERNAL_IRQ_API_H
#define DRV_EXTERNAL_IRQ_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#define EXTERNAL_IRQ_API_VERSION_MAJOR (2U)     ///< EXTERNAL IRQ API version number (Major)
#define EXTERNAL_IRQ_API_VERSION_MINOR (0U)     ///< EXTERNAL IRQ API version number (Minor)

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/
/** Callback function parameter data */
typedef struct st_external_irq_callback_args
{
    /** Placeholder for user data. Set in external_irq_api_t::open function in ::external_irq_cfg_t. */
    void const *        p_context;
    uint32_t            channel;  ///< The physical hardware channel that caused the interrupt.
} external_irq_callback_args_t;

/** External IRQ control block.  Allocate an instance specific control block to pass into the external IRQ API calls.
 * @par Implemented as
 * - icu_instance_ctrl_t
 */
typedef void external_irq_ctrl_t;

/** Trigger type: rising edge, falling edge, both edges, low level. */
typedef enum e_external_irq_trigger
{
    EXTERNAL_IRQ_TRIG_FALLING    = 0,  ///< Falling edge trigger
    EXTERNAL_IRQ_TRIG_RISING     = 1,  ///< Rising edge trigger
    EXTERNAL_IRQ_TRIG_BOTH_EDGE  = 2,  ///< Both edges trigger
    EXTERNAL_IRQ_TRIG_LEVEL_LOW  = 3,  ///< Low level trigger
} external_irq_trigger_t;

/** External IRQ input pin digital filtering sample clock divisor settings. */
typedef enum e_external_irq_pclk_div
{
    EXTERNAL_IRQ_PCLK_DIV_BY_1  = 0,   ///< Filter using PCLK divided by 1
    EXTERNAL_IRQ_PCLK_DIV_BY_8  = 1,   ///< Filter using PCLK divided by 8
    EXTERNAL_IRQ_PCLK_DIV_BY_32 = 2,   ///< Filter using PCLK divided by 32
    EXTERNAL_IRQ_PCLK_DIV_BY_64 = 3,   ///< Filter using PCLK divided by 64
} external_irq_pclk_div_t;

/** User configuration structure, used in open function */
typedef struct st_external_irq_cfg
{
    uint8_t                   channel;            ///< Hardware channel used.
    uint8_t                   irq_ipl;            ///< Interrupt priority
    external_irq_trigger_t    trigger;            ///< Trigger setting.
    external_irq_pclk_div_t   pclk_div;           ///< Digital filter clock divisor setting.
    bool                      autostart;          ///< Start operation and enable interrupts during open().
    bool                      filter_enable;      ///< Digital filter enable/disable setting.

    /** Callback provided external input trigger occurs. */
    void                   (* p_callback)(external_irq_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in ::external_irq_callback_args_t. */
    void const *              p_context;
    void const *              p_extend;           ///< External IRQ hardware dependent configuration.
} external_irq_cfg_t;

/** External interrupt driver structure. External interrupt functions implemented at the HAL layer will follow this API. */
typedef struct st_external_irq_api
{
    /** Initial configuration.
     * @par Implemented as
     * - R_ICU_ExternalIrqOpen()
     *
     * @param[out]  p_ctrl  Pointer to control block. Must be declared by user. Value set here.
     * @param[in]   p_cfg   Pointer to configuration structure. All elements of the structure must be set by user.
     */
    ssp_err_t (* open)(external_irq_ctrl_t           * const p_ctrl,
                       external_irq_cfg_t const      * const p_cfg);

    /** Enable callback when external IRQ occurs.
     * @par Implemented as
     * - R_ICU_ExternalIrqEnable()
     *
     * @param[in]  p_ctrl      Control block set in Open call for this external interrupt.
     */
    ssp_err_t (* enable)(external_irq_ctrl_t         * const p_ctrl);

    /** Disable callback when external IRQ occurs.
     * @par Implemented as
     * - R_ICU_ExternalIrqDisable()
     *
     * @param[in]  p_ctrl      Control block set in Open call for this external interrupt.
     */
    ssp_err_t (* disable)(external_irq_ctrl_t        * const p_ctrl);

    /** Set trigger.
     * @par Implemented as
     * - R_ICU_ExternalIrqTriggerSet()
     *
     * @param[in]  p_ctrl      Control block set in Open call for this external interrupt.
     * @param[in] trigger      Trigger type
     */
    ssp_err_t (* triggerSet)(external_irq_ctrl_t     * const p_ctrl,
                             external_irq_trigger_t    const trigger);

    /** Enables noise filter.
     * @par Implemented as
     * - R_ICU_ExternalIrqFilterEnable()
     *
     * @param[in]  p_ctrl      Control block set in Open call for this external interrupt.
     */
    ssp_err_t (* filterEnable)(external_irq_ctrl_t   * const p_ctrl);

    /** Disable noise filter.
     * @par Implemented as
     * - R_ICU_ExternalIrqFilterDisable()
     *
     * @param[in]  p_ctrl      Control block set in Open call for this external interrupt.
     */
    ssp_err_t (* filterDisable)(external_irq_ctrl_t  * const p_ctrl);

    /** Allow driver to be reconfigured. May reduce power consumption.
     * @par Implemented as
     * - R_ICU_ExternalIrqClose()
     *
     * @param[in]  p_ctrl      Control block set in Open call for this external interrupt.
     */
    ssp_err_t (* close)(external_irq_ctrl_t          * const p_ctrl);

    /** Get version and store it in provided pointer p_version.
     * @par Implemented as
     * - R_ICU_ExternalIrqVersionGet()
     *
     * @param[out]  p_version  Code and API version used.     */
    ssp_err_t (* versionGet)(ssp_version_t           * const p_version);

} external_irq_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_external_irq_instance
{
    external_irq_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    external_irq_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    external_irq_api_t const * p_api;     ///< Pointer to the API structure for this instance
} external_irq_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup EXTERNAL_IRQ_API)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* DRV_EXTERNAL_IRQ_API_H */

