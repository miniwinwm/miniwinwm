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
 * File Name    : r_display_api.h
 * Description  : Interface definition for graphics display driver module
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup Interface_Library
 * @defgroup DISPLAY_API Display Interface
 * @brief Interface for LCD panel displays.
 *
 * @section DISPLAY_API_SUMMARY Summary
 * The display interface provides standard display functionality:
 * - Signal timing configuration for LCD panels with RGB interface.
 * - Dot clock source selection (internal or external) and frequency divider.
 * - Blending of multiple graphics layers  on the background screen.
 * - Color correction (brightness/configuration/gamma correction).
 * - Interrupts and callback function.
 *
 * Implemented by:
 * @ref GLCD
 *
 * Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * Display Interface description: @ref HALDisplayInterface
 *
 * @{
 **********************************************************************************************************************/

#ifndef DRV_DISPLAY_API_H
#define DRV_DISPLAY_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DISPLAY_API_VERSION_MAJOR       (2U)
#define DISPLAY_API_VERSION_MINOR       (0U)

#define DISPLAY_GAMMA_CURVE_ELEMENT_NUM (16)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Display frame number */
typedef enum e_display_frame_layer
{
    DISPLAY_FRAME_LAYER_1 = 0,	///< Frame layer 1
    DISPLAY_FRAME_LAYER_2 = 1	///< Frame layer 2
} display_frame_layer_t;

/** Display interface operation state */
typedef enum e_display_state
{
    DISPLAY_STATE_CLOSED     = 0,	///< Display closed
    DISPLAY_STATE_OPENED     = 1,	///< Display opened
    DISPLAY_STATE_DISPLAYING = 2	///< Displaying
} display_state_t;

/** Display event codes */
typedef enum e_display_event
{
    DISPLAY_EVENT_GR1_UNDERFLOW  = 1,       ///< Graphics frame1 underflow occurs
    DISPLAY_EVENT_GR2_UNDERFLOW  = 2,       ///< Graphics frame2 underflow occurs
    DISPLAY_EVENT_LINE_DETECTION = 3,       ///< Designated line is processed
} display_event_t;

/** Input format setting */
typedef enum e_display_in_format
{
    DISPLAY_IN_FORMAT_32BITS_ARGB8888 = 0,          ///< ARGB8888, 32 bits
    DISPLAY_IN_FORMAT_32BITS_RGB888   = 1,          ///< RGB888,   32 bits
    DISPLAY_IN_FORMAT_16BITS_RGB565   = 2,          ///< RGB565,   16 bits
    DISPLAY_IN_FORMAT_16BITS_ARGB1555 = 3,          ///< ARGB1555, 16 bits
    DISPLAY_IN_FORMAT_16BITS_ARGB4444 = 4,          ///< ARGB4444, 16 bits
    DISPLAY_IN_FORMAT_CLUT8           = 5,          ///< CLUT8
    DISPLAY_IN_FORMAT_CLUT4           = 6,          ///< CLUT4
    DISPLAY_IN_FORMAT_CLUT1           = 7,          ///< CLUT1
} display_in_format_t;

/** Output format setting */
typedef enum e_display_out_format
{
    DISPLAY_OUT_FORMAT_24BITS_RGB888,	///< RGB888, 24 bits
    DISPLAY_OUT_FORMAT_18BITS_RGB666,	///< RGB666, 18 bits
    DISPLAY_OUT_FORMAT_16BITS_RGB565,	///< RGB565, 16 bits
    DISPLAY_OUT_FORMAT_8BITS_SERIAL,	///< SERIAL, 8 bits
} display_out_format_t;

/** Data endian select */
typedef enum e_display_endian
{
    DISPLAY_ENDIAN_LITTLE,	///< Little-endian
    DISPLAY_ENDIAN_BIG,		///< Big-endian
} display_endian_t;

/** RGB color order select */
typedef enum e_display_color_order
{
    DISPLAY_COLOR_ORDER_RGB,	///< Color order RGB
    DISPLAY_COLOR_ORDER_BGR		///< Color order BGR
} display_color_order_t;

/** Polarity of a signal select */
typedef enum st_display_signal_polarity
{
    DISPLAY_SIGNAL_POLARITY_LOACTIVE,       ///< Low active signal
    DISPLAY_SIGNAL_POLARITY_HIACTIVE,       ///< High active signal
} display_signal_polarity_t;

/** Signal synchronization edge select */
typedef enum e_display_sync_edge
{
    DISPLAY_SIGNAL_SYNC_EDGE_RISING,        ///< Signal is synchronized to rising edge
    DISPLAY_SIGNAL_SYNC_EDGE_FALLING,       ///< Signal is synchronized to falling edge
} display_sync_edge_t;

/** Fading control */
typedef enum e_display_fade_control
{
    DISPLAY_FADE_CONTROL_NONE,              ///< Applying no fading control
    DISPLAY_FADE_CONTROL_FADEIN,            ///< Applying fade-in control
    DISPLAY_FADE_CONTROL_FADEOUT,           ///< Applying fade-out control
} display_fade_control_t;

/** Fading status */
typedef enum e_display_fade_status
{
    DISPLAY_FADE_STATUS_NOT_UNDERWAY,       ///< Fade-in/fade-out is not in progress
    DISPLAY_FADE_STATUS_FADING_UNDERWAY,    ///< Fade-in or fade-out is in progress
    DISPLAY_FADE_STATUS_UNCERTAIN           ///< Fade-in/fade-out status is uncertain just before hardware working
} display_fade_status_t;

/** Display signal timing setting */
typedef struct st_display_timing
{
    uint16_t                   total_cyc;     ///< Total cycles in one line or total lines in one frame
    uint16_t                   display_cyc;   ///< Active video cycles or lines
    uint16_t                   back_porch;    ///< Back poach cycles or lines
    uint16_t                   sync_width;    ///< Sync signal asserting width
    display_signal_polarity_t  sync_polarity; ///< Sync signal polarity
} display_timing_t;

/** RGB Color setting */
typedef struct st_display_color
{
    union
    {
        uint32_t  argb;
        struct
        {
            uint8_t  b;     ///< blue
            uint8_t  g;     ///< green
            uint8_t  r;     ///< red
            uint8_t  a;     ///< a
        }  byte;
    };
} display_color_t;

/** Contrast (gain) correction setting */
typedef struct st_display_coordinate
{
    int16_t  x;                             ///< Coordinate X, this allows to set signed value.
    int16_t  y;                             ///< Coordinate Y, this allows to set signed value.
} display_coordinate_t;

/** Brightness (DC) correction setting */
typedef struct st_display_brightness
{
    bool      enable;                       ///< Brightness Correction On/Off
    uint16_t  r;                            ///< Brightness (DC) adjustment for R channel
    uint16_t  g;                            ///< Brightness (DC) adjustment for G channel
    uint16_t  b;                            ///< Brightness (DC) adjustment for B channel
} display_brightness_t;

/** Contrast (gain) correction setting */
typedef struct st_display_contrast
{
    bool     enable;                        ///< Contrast Correction On/Off
    uint8_t  r;                             ///< Contrast (gain) adjustment for R channel
    uint8_t  g;                             ///< Contrast (gain) adjustment for G channel
    uint8_t  b;                             ///< Contrast (gain) adjustment for B channel
} display_contrast_t;

/** Color correction setting */
typedef struct st_display_correction
{
    display_brightness_t  brightness;	///< Brightness
    display_contrast_t    contrast;		///< Contrast
} display_correction_t;

/** Gamma correction setting for each color */
typedef struct st_gamma_correction
{
    bool      enable;                                              ///< Gamma Correction On/Off
    uint16_t  gain[DISPLAY_GAMMA_CURVE_ELEMENT_NUM];               ///< Gain adjustment
    uint16_t  threshold[DISPLAY_GAMMA_CURVE_ELEMENT_NUM];          ///< Start threshold
} gamma_correction_t;

/** Gamma correction setting */
typedef struct st_display_gamma_correction
{
    gamma_correction_t  r;	///< Gamma correction for R channel
    gamma_correction_t  g;	///< Gamma correction for G channel
    gamma_correction_t  b;	///< Gamma correction for B channel
} display_gamma_correction_t;

/** CLUT setting */
typedef struct st_display_clut
{
    uint32_t        color_num;              ///< The number of colors in CLUT
    const uint32_t  * p_clut;               ///< Address of the area storing the CLUT data (in ARGB8888 format)
} display_clut_t;

/** Graphics plane input configuration structure */
typedef struct st_display_input_cfg
{
    uint32_t             * p_base;                    ///< Base address to the frame buffer
    uint16_t             hsize;                       ///< Horizontal pixel size in a line
    uint16_t             vsize;                       ///< Vertical pixel size in a frame
    uint32_t             hstride;                     ///< Memory stride (bytes) in a line
    display_in_format_t  format;                      ///< Input format setting
    bool                 line_descending_enable;      ///< Line descending enable
    bool                 lines_repeat_enable;         ///< Line repeat enable
    uint16_t             lines_repeat_times;          ///< Expected number of line repeating
} display_input_cfg_t;

/** Display output configuration structure */
typedef struct st_display_output_cfg
{
    display_timing_t            htiming;              ///< Horizontal display cycle setting
    display_timing_t            vtiming;              ///< Vertical display cycle setting
    display_out_format_t        format;               ///< Output format setting
    display_endian_t            endian;               ///< Bit order of output data
    display_color_order_t       color_order;          ///< Color order in pixel
    display_signal_polarity_t   data_enable_polarity; ///< Data Enable signal polarity
    display_sync_edge_t         sync_edge;            ///< Signal sync edge selection
    display_color_t             bg_color;             ///< Background color
    display_brightness_t        brightness;           ///< Brightness setting
    display_contrast_t          contrast;             ///< Contrast setting
    display_gamma_correction_t  * p_gamma_correction; ///< Pointer to gamma correction setting
    bool                        dithering_on;         ///< Dithering on/off
} display_output_cfg_t;

/** Graphics layer blend setup parameter structure */
typedef struct st_display_layer
{
    display_coordinate_t    coordinate;               ///< Blending location (starting point of image)
    display_color_t         bg_color;                 ///< Color outside region
    display_fade_control_t  fade_control;             ///< Layer fade-in/out control on/off
    uint8_t                 fade_speed;               ///< Layer fade-in/out frame rate
} display_layer_t;

/** Display callback parameter definition */
typedef struct st_display_callback_args
{
    display_event_t  event;                           ///< Event code
    void const     * p_context;                     ///< Context provided to user during callback
} display_callback_args_t;

/** Display main configuration structure */
typedef struct st_display_cfg
{
    /** Generic configuration for display devices */
    display_input_cfg_t   input[DISPLAY_FRAME_LAYER_2 + 1];         ///< Graphics input frame setting
    display_output_cfg_t  output;                                   ///< Graphics output frame setting
    display_layer_t       layer[DISPLAY_FRAME_LAYER_2 + 1];         ///< Graphics layer blend setting
    uint8_t               line_detect_ipl;                          ///< Line detect interrupt priority
    uint8_t               underflow_1_ipl;                          ///< Underflow 1 interrupt priority
    uint8_t               underflow_2_ipl;                          ///< Underflow 1 interrupt priority

    /** Configuration for display event processing */
    void (* p_callback)(display_callback_args_t * p_args);   ///< Pointer to callback function
    void const * p_context;                                  ///< User defined context passed into callback function

    /** Pointer to display peripheral specific configuration */
    void const * p_extend;                                          ///< Display hardware dependent configuration
} display_cfg_t;

/** Display main configuration structure */
typedef struct st_display_runtime_cfg
{
    /** Generic configuration for display devices */
    display_input_cfg_t  input;                                     ///< Graphics input frame setting
    display_layer_t      layer;                                     ///< Graphics layer alpha blending setting
} display_runtime_cfg_t;

/** Display CLUT configuration structure */
typedef struct st_display_clut_cfg
{
    uint32_t  * p_base;                                             ///< Pointer to CLUT source data
    uint16_t  start;                                                ///< Beginning of CLUT entry to be updated
    uint16_t  size;                                                 ///< Size of CLUT entry to be updated
} display_clut_cfg_t;

/** Display control block.  Allocate an instance specific control block to pass into the display API calls.
 * @par Implemented as
 * - glcd_instance_ctrl_t
 */
/** Display control block */
typedef void display_ctrl_t;

/** Display Status */
typedef struct st_display_status
{
    display_state_t        state;                                   ///< Status of GLCD module
    display_fade_status_t  fade_status[DISPLAY_FRAME_LAYER_2 + 1];  ///< Status of fade-in/fade-out status
} display_status_t;

/** Shared Interface definition for display peripheral */
typedef struct st_display_api
{
    /** Open display device.
     * @par Implemented as
     * - R_GLCD_Open()
     * @param[in,out]  p_ctrl        Pointer to display interface control block. Must be declared by user. Value set
     *                               here.
     * @param[in]      p_cfg         Pointer to display configuration structure. All elements of this structure must be
     *                               set by user.
     */
	ssp_err_t (* open)(display_ctrl_t * const p_ctrl, display_cfg_t const * const p_cfg);

    /** Close display device.
     * @par Implemented as
     * - R_GLCD_Close()
     * @param[in]     p_ctrl   Pointer to display interface control block.
     */
    ssp_err_t (* close)(display_ctrl_t * const p_ctrl);

    /** Display start.
     * @par Implemented as
     * - R_GLCD_Start()
     * @param[in]     p_ctrl   Pointer to display interface control block.
     */
    ssp_err_t (* start)(display_ctrl_t * const p_ctrl);

    /** Display stop.
     * @par Implemented as
     * - R_GLCD_Stop()
     * @param[in]     p_ctrl   Pointer to display interface control block.
     */
    ssp_err_t (* stop)(display_ctrl_t * const p_ctrl);

    /** Change layer parameters at runtime.
     * @par Implemented as
     * - R_GLCD_LayerChange()
     * @param[in]   p_ctrl     Pointer to display interface control block.
     * @param[in]   p_cfg      Pointer to run-time layer configuration structure.
     * @param[in]   frame      Number of graphic frames.
     */
    ssp_err_t (* layerChange)(display_ctrl_t const * const        p_ctrl,
                              display_runtime_cfg_t const * const p_cfg,
                              display_frame_layer_t               frame);

    /** Color correction.
     * @par Implemented as
     * - R_GLCD_ColorCorrection()
     * @param[in]   p_ctrl     Pointer to display interface control block.
     * @param[in]   param      Pointer to color correction configuration structure.
     */
    ssp_err_t (* correction)(display_ctrl_t const * const p_ctrl, display_correction_t const * const p_param);

    /** Set CLUT for display device.
     * @par Implemented as
     * - R_GLCD_ClutUpdate()
     * @param[in]   p_ctrl     Pointer to display interface control block.
     * @param[in]   p_clut_cfg Pointer to CLUT configuration structure.
     * @param[in]   frame      Number of frame buffer corresponding to the CLUT.
     */
    ssp_err_t (* clut)(display_ctrl_t const * const     p_ctrl,
                       display_clut_cfg_t const * const p_clut_cfg,
                       display_frame_layer_t            frame);

    /** Get status for display device.
     * @par Implemented as
     * - R_GLCD_StatusGet()
     * @param[in]   p_ctrl     Pointer to display interface control block.
     * @param[in]   status     Pointer to display interface status structure.
     */
    ssp_err_t (* statusGet)(display_ctrl_t const * const p_ctrl, display_status_t * const p_status);

    /** Get version.
     * @par Implemented as
     * - R_GLCD_VersionGet()
     * @param[in]   p_version  Pointer to the memory to store the version information.
     */
    ssp_err_t (* versionGet)(ssp_version_t * p_version);
} display_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_display_instance
{
    display_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    display_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    display_api_t const * p_api;     ///< Pointer to the API structure for this instance
} display_instance_t;

/**********************************************************************************************************************
 * Public Functions
 **********************************************************************************************************************/

/** @} (end defgroup DISPLAY_API) */

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* DRV_DISPLAY_API_H */
