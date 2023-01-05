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
 * File Name    : r_glcd.h
 * Description  : GLCD HAL driver module public header file
 **********************************************************************************************************************/

#ifndef R_GLCD_H
#define R_GLCD_H

/*******************************************************************************************************************//**
 * @ingroup HAL_Library
 * @defgroup GLCD GLCDC
 * @brief Driver for the Graphics LCD Controller (GLCDC).
 *
 * @section GLCD_HAL_Library_SUMMARY Summary
 * Implements  @ref DISPLAY_API.
 * This module supports the Graphics LCD Controller (GLCDC). It implements the display interface and drives LCD panels
 * connected to the GLCDC pins.
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_display_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Display control block.  DO NOT INITIALIZE. */
typedef struct st_glcd_instance_ctrl
{
    display_state_t  state;                                         ///< Status of GLCD module

    /* Parameters to Event processing for display devices */
    void (* p_callback)(display_callback_args_t * p_args);          ///< Pointer to callback function
    void const   * p_context;                                       ///< Pointer to the higher level device context
    R_GLCDC_Type * p_reg;                                           ///< Base register address
} glcd_instance_ctrl_t;

/** Clock source select */
typedef enum e_glcd_clk_src
{
    GLCD_CLK_SRC_INTERNAL,	///< Internal
    GLCD_CLK_SRC_EXTERNAL,	///< External
} glcd_clk_src_t;

/** Clock frequency division ratio */
typedef enum e_glcd_panel_clk_div
{
    GLCD_PANEL_CLK_DIVISOR_1  = 1,                          ///< Division Ratio 1/1
    GLCD_PANEL_CLK_DIVISOR_2  = 2,                          ///< Division Ratio 1/2
    GLCD_PANEL_CLK_DIVISOR_3  = 3,                          ///< Division Ratio 1/3
    GLCD_PANEL_CLK_DIVISOR_4  = 4,                          ///< Division Ratio 1/4
    GLCD_PANEL_CLK_DIVISOR_5  = 5,                          ///< Division Ratio 1/5
    GLCD_PANEL_CLK_DIVISOR_6  = 6,                          ///< Division Ratio 1/6
    GLCD_PANEL_CLK_DIVISOR_7  = 7,                          ///< Division Ratio 1/7
    GLCD_PANEL_CLK_DIVISOR_8  = 8,                          ///< Division Ratio 1/8
    GLCD_PANEL_CLK_DIVISOR_9  = 9,                          ///< Division Ratio 1/9
    GLCD_PANEL_CLK_DIVISOR_12 = 12,                         ///< Division Ratio 1/12
    GLCD_PANEL_CLK_DIVISOR_16 = 16,                         ///< Division Ratio 1/16
    GLCD_PANEL_CLK_DIVISOR_24 = 24,                         ///< Division Ratio 1/24
    GLCD_PANEL_CLK_DIVISOR_32 = 32,                         ///< Division Ratio 1/32
} glcd_panel_clk_div_t;

/** LCD TCON output pin select */
typedef enum e_glcd_tcon_pin
{
    GLCD_TCON_PIN_NONE = -1,                                ///< No output
    GLCD_TCON_PIN_0,                                        ///< LCD_TCON0
    GLCD_TCON_PIN_1,                                        ///< LCD_TCON1
    GLCD_TCON_PIN_2,                                        ///< LCD_TCON2
    GLCD_TCON_PIN_3,                                        ///< LCD_TCON3
} glcd_tcon_pin_t;

/** Bus Arbitration setting */
typedef enum e_glcd_bus_arbitraion
{
    GLCD_BUS_ARBITRATION_ROUNDROBIN,                        ///< Round robin
    GLCD_BUS_ARBITRATION_FIX_PRIORITY                       ///< Fixed
} glcd_bus_arbitration_t;

/** Correction circuit sequence control */
typedef enum e_glcd_correction_proc_order
{
    GLCD_CORRECTION_PROC_ORDER_BRIGHTNESS_CONTRAST2GAMMA,   ///< Brightness -> contrast -> gamma correction
    GLCD_CORRECTION_PROC_ORDER_GAMMA2BRIGHTNESS_CONTRAST    ///< Gamma correction -> brightness -> contrast
} glcd_correction_proc_order_t;

/** Timing signals for driving the LCD panel */
typedef enum e_glcd_tcon_signal_select
{
    GLCD_TCON_SIGNAL_SELECT_STVA_VS = 0,                    ///< STVA/VS
    GLCD_TCON_SIGNAL_SELECT_STVB_VE = 1,                    ///< STVB/VE
    GLCD_TCON_SIGNAL_SELECT_STHA_HS = 2,                    ///< STH/SP/HS
    GLCD_TCON_SIGNAL_SELECT_STHB_HE = 3,                    ///< STB/LP/HE
    GLCD_TCON_SIGNAL_SELECT_DE      = 7                     ///< DE
} glcd_tcon_signal_select_t;

/** Clock phase adjustment for serial RGB output */
typedef enum e_glcd_clut_plane
{
    GLCD_CLUT_PLANE_0 = 0,                                  ///< GLCD CLUT plane 0
    GLCD_CLUT_PLANE_1 = 1,                                  ///< GLCD CLUT plane 1
} glcd_clut_plane_t;

/** Dithering mode */
typedef enum e_glcd_dithering_mode
{
    GLCD_DITHERING_MODE_TRUNCATE   = 0,                     ///< No dithering (truncate)
    GLCD_DITHERING_MODE_ROUND_OFF  = 1,                     ///< Dithering with round off
    GLCD_DITHERING_MODE_2X2PATTERN = 2,                     ///< Dithering with 2x2 pattern
    GLCD_DITHERING_MODE_SETTING_MAX                         ///< Setting prohibited
} glcd_dithering_mode_t;

/** Dithering mode */
typedef enum e_glcd_dithering_pattern
{
    GLCD_DITHERING_PATTERN_00 = 0,                          ///< 2x2 pattern '00'
    GLCD_DITHERING_PATTERN_01 = 1,                          ///< 2x2 pattern '01'
    GLCD_DITHERING_PATTERN_10 = 2,                          ///< 2x2 pattern '10'
    GLCD_DITHERING_PATTERN_11 = 3,                          ///< 2x2 pattern '11'
} glcd_dithering_pattern_t;

/** Output interface format */
typedef enum e_glcd_input_interface_format
{
    GLCD_INPUT_INTERFACE_FORMAT_RGB565   = 0,               ///< Input interface format RGB565
    GLCD_INPUT_INTERFACE_FORMAT_RGB888   = 1,               ///< Input interface format RGB888
    GLCD_INPUT_INTERFACE_FORMAT_ARGB1555 = 2,               ///< Input interface format ARGB1555
    GLCD_INPUT_INTERFACE_FORMAT_ARGB4444 = 3,               ///< Input interface format ARGB4444
    GLCD_INPUT_INTERFACE_FORMAT_ARGB8888 = 4,               ///< Input interface format ARGB8888
    GLCD_INPUT_INTERFACE_FORMAT_CLUT8    = 5,               ///< Input interface format CLUT8
    GLCD_INPUT_INTERFACE_FORMAT_CLUT4    = 6,               ///< Input interface format CLUT4
    GLCD_INPUT_INTERFACE_FORMAT_CLUT1    = 7,               ///< Input interface format CLUT1
} glcd_input_interface_format_t;

/** Output interface format */
typedef enum e_glcd_output_interface_format
{
    GLCD_OUTPUT_INTERFACE_FORMAT_RGB888     = 0,            ///< Output interface format RGB888
    GLCD_OUTPUT_INTERFACE_FORMAT_RGB666     = 1,            ///< Output interface format RGB666
    GLCD_OUTPUT_INTERFACE_FORMAT_RGB565     = 2,            ///< Output interface format RGB565
    GLCD_OUTPUT_INTERFACE_FORMAT_SERIAL_RGB = 3,            ///< Output interface format Serial RGB
} glcd_output_interface_format_t;

/** Dithering output format */
typedef enum e_glcd_dithering_output_format
{
    GLCD_DITHERING_OUTPUT_FORMAT_RGB888 = 0,                ///< Dithering output format RGB888
    GLCD_DITHERING_OUTPUT_FORMAT_RGB666 = 1,                ///< Dithering output format RGB666
    GLCD_DITHERING_OUTPUT_FORMAT_RGB565 = 2,                ///< Dithering output format RGB565
} glcd_dithering_output_format_t;

/** GLCD hardware specific configuration */
typedef struct st_glcd_cfg
{
    glcd_tcon_pin_t               tcon_hsync;               ///< GLCD TCON output pin select
    glcd_tcon_pin_t               tcon_vsync;               ///< GLCD TCON output pin select
    glcd_tcon_pin_t               tcon_de;                  ///< GLCD TCON output pin select
    glcd_correction_proc_order_t  correction_proc_order;    ///< Correction control route select
    glcd_clk_src_t                clksrc;                   ///< Clock Source selection
    glcd_panel_clk_div_t          clock_div_ratio;          ///< Clock divide ratio for dot clock
    glcd_dithering_mode_t         dithering_mode;           ///< Dithering mode
    glcd_dithering_pattern_t      dithering_pattern_A;      ///< Dithering pattern A
    glcd_dithering_pattern_t      dithering_pattern_B;      ///< Dithering pattern B
    glcd_dithering_pattern_t      dithering_pattern_C;      ///< Dithering pattern C
    glcd_dithering_pattern_t      dithering_pattern_D;      ///< Dithering pattern D
} glcd_cfg_t;

/** GLCD hardware specific control block */
typedef struct st_glcd_ctrl
{
    display_coordinate_t  back_porch;                       ///< Zero coordinate for graphics plane(Bach porch End)
    uint16_t              hsize;                            ///< Horizontal pixel size in a line
    uint16_t              vsize;                            ///< Vertical pixel size in a frame
    bsp_lock_t            resource_lock;                    ///< Resource lock
    void                  * p_context;                      ///< Pointer to the function level device context
                                                            ///   (e.g. display_ctrl_t type data)
} glcd_ctrl_t;

/**********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const display_api_t g_display_on_glcd;
/** @endcond */

/*******************************************************************************************************************//**
 * @} (end defgroup GLCD)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* R_GLCD_H */
