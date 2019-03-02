/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_glcdc_private.h
 * Version      : 1.00
 * Description  : Header file of GLCDC internal functions.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.10.2017 1.00      First Release
 ***********************************************************************************************************************/

#ifndef R_GLCDC_PRIVATE_H
#define R_GLCDC_PRIVATE_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include <machine.h>
#include <stddef.h>
#include <stdint.h>

#include "platform.h"

#include "r_glcdc_rx_if.h"
#include "r_glcdc_rx_config.h"

/* This checks that the module of the GLCDC is supported to the MCU that has been selected for sure. */
#if (defined(BSP_MCU_RX65N_2MB))
#else
    #error "This MCU is not supported by the current r_glcdc_rx module."
#endif

#if ((GLCDC_CFG_PARAM_CHECKING_ENABLE == 0) || (GLCDC_CFG_PARAM_CHECKING_ENABLE == 1))
#else
    #error "ERROR- GLCDC_CFG_PARAM_CHECKING_ENABLE - setting values is out of range defined in r_glcdc_rx_config.h."
#endif

#if ((GLCDC_CFG_INTERRUPT_PRIORITY_LEVEL >= 0) && (GLCDC_CFG_INTERRUPT_PRIORITY_LEVEL <= 15))
#else
    #error "ERROR- GLCDC_CFG_INTERRUPT_PRIORITY_LEVEL - setting values is out of range defined in r_glcdc_rx_config.h."
#endif

/**********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* To use for 64-byte alignment address checking, calculation */
#define GLCDC_ADDRESS_ALIGNMENT_64B (0x0000003FUL)

/* To use for 2 and 4 pixel alignment checking, calculation */
#define ALIGNMENT_4_MASK            (0x0003U)
#define ALIGNMENT_2_MASK            (0x0001U)

/* To adjust 64 pixel margin calculation */
#define OFFSET_MARGIN_MINUS_64PIX (64)

/* Color look up table entry size */
#define GLCDC_CLUT_ENTRY_SIZE (256)

/* Fixed margin by Hardware operation */
#define BG_PLANE_H_CYC_MARGIN_MIN      (2)      /* Hsync signal margin is 2 */
#define BG_PLANE_V_CYC_MARGIN_MIN      (1)      /* Vsync signal margin is 1 */

/* Panel timing, Maximum threshold */
#define BG_PLANE_H_CYC_MAX                (1024)        /* BG_PERI.FH (Max=1024) */
#define BG_PLANE_V_CYC_MAX                (1024)        /* BG_PERI.FV (Max=1024) */
#define BG_PLANE_H_CYC_ACTIVE_SIZE_MAX    (1016)        /* BG_HSIZE.HW (Max=1016) */
#define BG_PLANE_V_CYC_ACTIVE_SIZE_MAX    (1020)        /* BG_VSIZE.VW (Max=1020) */
#define BG_PLANE_H_ACTIVE_POS_MAX         (1006)        /* BG_HSIZE.HP (Max=1006) */
#define BG_PLANE_V_ACTIVE_POS_MAX         (1007)        /* BG_VSIZE.VP (Max=1007) */
#define GR_PLANE_LNOFF_POS_MAX            (32767)       /* GRn_FLM3_LNOFF(positive num max=32767) */
#define GR_PLANE_H_START_POS_MAX          (1005)        /* GRn_AB3_GRCHS (Max=1005) */
#define GR_PLANE_V_START_POS_MAX          (1006)        /* GRn_AB2_GRCVS (Max=1006) */
#define GR_PLANE_H_CYC_ACTIVE_SIZE_MAX    (1016)        /* GRn_AB3_GRCHW (Max=1016) */
#define GR_PLANE_V_CYC_ACTIVE_SIZE_MAX    (1020)        /* GRn_AB3_GRCVW (Max=1020) */
#define GR_PLANE_H_ACTIVE_POS_MAX         (1005)        /* GRn_AB2.GRCHS (Min=1005) */
#define GR_PLANE_V_ACTIVE_POS_MAX         (1006)        /* GRn_AB2.GRCVS (Min=1006) */
#define BG_PLANE_H_FRONT_PORCH_MAX        (17)          /* Horizontal front porch parameter (MAX=17)*/
#define BG_PLANE_V_FRONT_PORCH_MAX        (16)          /* Vertical front porch parameter (MAX=16)*/
#define GR_PLANE_DATANUM_POS_MAX          (65536)       /* GRn_FLM5_DATANUM (Max=65536) */
#define GR_BLEND_H_ACTIVE_POS_MAX         (1005)        /* GRn_AB5_GRCHS (Max=1005) */
#define GR_BLEND_V_ACTIVE_POS_MAX         (1006)        /* GRn_AB4_GRCVS (Max=1006) */
#define GR_BLEND_H_CYC_ACTIVE_SIZE_MAX    (1016)        /* GRn_AB5_GRCHW (Max=1016) */
#define GR_BLEND_V_CYC_ACTIVE_SIZE_MAX    (1020)        /* GRn_AB4_GRCVW (Max=1020) */

/* Panel timing, Minimum threshold */
#define BG_PLANE_H_CYC_MIN             (24)             /* BG_PERI.FH (Min=24) */
#define BG_PLANE_V_CYC_MIN             (20)             /* BG_PERI.FV (Min=20) */
#define BG_PLANE_HSYNC_POS_MIN         (1)              /* BG_HSYNC.HP (Min=1) */
#define BG_PLANE_VSYNC_POS_MIN         (1)              /* BG_HSYNC.VP (Min=1) */
#define BG_PLANE_H_CYC_ACTIVE_SIZE_MIN (16)             /* BG_HSIZE.HW (Min=16) */
#define BG_PLANE_V_CYC_ACTIVE_SIZE_MIN (16)             /* BG_VSIZE.VW (Min=16) */
#define BG_PLANE_H_ACTIVE_POS_MIN      (6)              /* BG_HSIZE.HP (Min=6) */
#define BG_PLANE_V_ACTIVE_POS_MIN      (3)              /* BG_VSIZE.VP (Min=3) */
#define GR_PLANE_LNOFF_POS_MIN         (-32768)         /* GRn_FLM3_LNOFF(positive num min=-32768) */
#define GR_PLANE_H_CYC_ACTIVE_SIZE_MIN (16)             /* GRn_AB3.GRCHW (Min=16) */
#define GR_PLANE_V_CYC_ACTIVE_SIZE_MIN (16)             /* GRn_AB2.GRCVW (Min=16) */
#define GR_PLANE_H_ACTIVE_POS_MIN      (5)              /* GRn_AB2.GRCHS (Min=5) */
#define GR_PLANE_V_ACTIVE_POS_MIN      (2)              /* GRn_AB2.GRCVS (Min=2) */
#define BG_PLANE_H_FRONT_PORCH_MIN     (3)              /* Horizontal front porch parameter (MIN=3) */
#define BG_PLANE_V_FRONT_PORCH_MIN     (2)              /* Vertical front porch parameter (MIN=2) */
#define BG_PLANE_H_BACK_PORCH_MIN      (1)              /* Horizontal back porch parameter (MIN=1) */
#define BG_PLANE_V_BACK_PORCH_MIN      (1)              /* Vertical back porch parameter (MIN=1) */
#define BG_PLANE_H_SYNC_WIDTH_MIN      (4)              /* Horizontal sync signal width parameter (MIN=4) */
#define BG_PLANE_V_SYNC_WIDTH_MIN      (1)              /* Vertical sync signal width parameter (MIN=1) */
#define GR_BLEND_H_ACTIVE_POS_MIN      (5)              /* GRn_AB5_GRCHS (Min=5) */
#define GR_BLEND_V_ACTIVE_POS_MIN      (2)              /* GRn_AB4_GRCVS (Min=2) */
#define GR_BLEND_H_CYC_ACTIVE_SIZE_MIN (1)              /* GRn_AB5_GRCHW (Min=1) */
#define GR_BLEND_V_CYC_ACTIVE_SIZE_MIN (1)              /* GRn_AB4_GRCVW (Min=1) */

/* TCON setting threshold */
#define TCON_V_SYNC_POS_MAX        (2047)           /* TCONSTVB1.VS (MAX=2047)*/
#define TCON_V_SYNC_POS_MIN        (0)              /* TCONSTVB1.VS (MIN=0) */
#define TCON_V_SYNC_WIDTH_MAX      (2047)           /* TCONSTVB1.VW (MAX=2047) */
#define TCON_V_SYNC_WIDTH_MIN      (0)              /* TCONSTVB1.VW (MIN=0) */
#define TCON_H_SYNC_POS_MAX        (1023)           /* TCONSTHB.HS (MAX=1023) */
#define TCON_H_SYNC_POS_MIN        (0)              /* TCONSTHB.HS (MIN=0) */
#define TCON_H_SYNC_WIDTH_MAX      (1023)           /* TCONSTHB.HW (MAX=1023) */
#define TCON_H_SYNC_WIDTH_MIN      (0)              /* TCONSTHB.HW (MIN=0) */

/* Chroma key setting threshold */
#define GLCDC_CHROMAKEY_BEFORE_MAX     (255)         /* GR_AB8.CKKR and .CKKB and .CKKG (Max=255) */
#define GLCDC_CHROMAKEY_AFTER_MAX      (255)         /* GR_AB9.CKA and .CKR and .CKB and .CKG (Max=255) */

/* Color correction setting threshold */
#define GLCDC_BRIGHTNESS_DEFAULT  (512)                /* OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Mid=512) */
#define GLCDC_BRIGHTNESS_MAX      (1023)               /* OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Max=1023) */
#define GLCDC_CONTRAST_DEFAULT    (128)                /* OUT_CONTRAST.CONTG and .CONTB and .CONTR (Mid=128) */
#define GLCDC_CONTRAST_MAX        (255)                /* OUT_CONTRAST.CONTG and .CONTB and .CONTR (Max=255) */
#define GLCDC_GAMMA_GAIN_MAX      (2047)               /* GAMx_LUTn.GAIN15 - GAIN0 (Max=2047) */
#define GLCDC_GAMMA_THRESHOLD_MAX (1023)               /* GAMx_AREAn.TH15  - TH0   (Max=1023) */

/* One line transfer byte */
#define GR_PLANE_DATANUM_TRANS_BYTE   (64)

/* Registers for Background Frame Control Block */
#define BG_PERI_FV_MASK  (0x000007FFUL)
#define BG_PERI_FH_MASK  (0x000007FFUL)
#define BG_SYNC_VP_MASK  (0x000FU)
#define BG_SYNC_HP_MASK  (0x000FU)
#define BG_VSIZE_VP_MASK (0x07FFU)
#define BG_VSIZE_VW_MASK (0x07FFU)
#define BG_HSIZE_HP_MASK (0x07FFU)
#define BG_HSIZE_HW_MASK (0x07FFU)

/* Register bit definition for Graphics Frame Control Block */
#define GRn_FLM3_LNOFF_MASK   (0x0000FFFFUL)
#define GRn_FLM5_LNNUM_MASK   (0x000007FFUL)
#define GRn_FLM5_DATANUM_MASK (0x0000FFFFUL)

#define GRn_AB1_DISPSEL_MASK  (0x00000003UL)
#define GRn_AB2_GRCVS_MASK    (0x000007FFUL)
#define GRn_AB2_GRCVW_MASK    (0x07FFU)
#define GRn_AB3_GRCHS_MASK    (0x000007FFUL)
#define GRn_AB3_GRCHW_MASK    (0x07FFU)
#define GRn_AB4_ARCVS_MASK    (0x000007FFUL)
#define GRn_AB4_ARCVW_MASK    (0x07FFU)
#define GRn_AB5_ARCHS_MASK    (0x000007FFUL)
#define GRn_AB5_ARCHW_MASK    (0x07FFU)
#define GRn_AB6_ARCCOEF_MASK  (0x000001FFUL)
#define GRn_AB7_ARCDEF_MASK   (0x000000FFUL)
#define GRn_CLUTINT_LINE_MASK (0x000007FFUL)


/* Register bit definition for Output Control Block */
#define GAMX_LUTX_GAIN_MASK            (0x07FFU)
#define GAMX_AREAX_MASK                (0x03FFU)

#define OUT_SET_FRQSEL_NO_DIVISION     (0)
#define OUT_SET_FRQSEL_QUATER_DIVISION (1)

#define OUT_BRIGHT1_BRTG_MASK          (0x03FFU)
#define OUT_BRIGHT2_BRTB_MASK          (0x03FFU)
#define OUT_BRIGHT2_BRTR_MASK          (0x03FFU)

#define OUT_CONTRAST_CONTG_MASK        (0xFFU)
#define OUT_CONTRAST_CONTB_MASK        (0xFFU)
#define OUT_CONTRAST_CONTR_MASK        (0xFFU)

#define TCON_STHx1_HS_MASK             (0x07FFU)
#define TCON_STHx1_HW_MASK             (0x07FFU)
#define TCON_STVx1_VS_MASK             (0x07FFU)
#define TCON_STVx1_VW_MASK             (0x07FFU)

#define SYSCNT_PANEL_CLK_DCDR_MASK     (0x3FU)

/**********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/** GR1,GR2 register access definition */
#pragma bit_order left
#pragma unpack
typedef struct st_glcdc_gr_clut {
    union {
        uint32_t lsize;
        struct {
            uint32_t a:8;
            uint32_t r:8;
            uint32_t g:8;
            uint32_t b:8;
        } bit;
    } grxclut[256];
} st_glcdc_gr_clut_t;

typedef struct st_glcdc_gr {
    union {
        uint32_t lsize;
        struct {
            uint32_t :31;
            uint32_t ven:1;
        } bit;
    } grxven;
    union {
        uint32_t lsize;
        struct {
            uint32_t :31;
            uint32_t renb:1;
        } bit;
    } grxflmrd;
    char           wk0[4];
    uint32_t  grxflm2;
    union {
        uint32_t lsize;
        struct {
            uint32_t lnoff:16;
            uint32_t :16;
        } bit;
    } grxflm3;
    char           wk1[4];
    union {
        uint32_t lsize;
        struct {
            uint32_t :5;
            uint32_t lnnum:11;
            uint32_t datanum:16;
        } bit;
    } grxflm5;
    union {
        uint32_t lsize;
        struct {
            uint32_t :1;
            uint32_t format:3;
            uint32_t :28;
        } bit;
    } grxflm6;
    union {
        uint32_t lsize;
        struct {
            uint32_t :19;
            uint32_t arcon:1;
            uint32_t :3;
            uint32_t arcdispon:1;
            uint32_t :3;
            uint32_t grcdispon:1;
            uint32_t :2;
            uint32_t dispsel:2;
        } bit;
    } grxab1;
    union {
        uint32_t lsize;
        struct {
            uint32_t :5;
            uint32_t grcvs:11;
            uint32_t :5;
            uint32_t grcvw:11;
        } bit;
    } grxab2;
    union {
        uint32_t lsize;
        struct {
            uint32_t :5;
            uint32_t grchs:11;
            uint32_t :5;
            uint32_t grchw:11;
        } bit;
    } grxab3;
    union {
        uint32_t lsize;
        struct {
            uint32_t :5;
            uint32_t arcvs:11;
            uint32_t :5;
            uint32_t arcvw:11;
        } bit;
    } grxab4;
    union {
        uint32_t lsize;
        struct {
            uint32_t :5;
            uint32_t archs:11;
            uint32_t :5;
            uint32_t archw:11;
        } bit;
    } grxab5;
    union {
        uint32_t lsize;
        struct {
            uint32_t :7;
            uint32_t arccoef:9;
            uint32_t :8;
            uint32_t arcrate:8;
        } bit;
    } grxab6;
    union {
        uint32_t lsize;
        struct {
            uint32_t :8;
            uint32_t arcdef:8;
            uint32_t :15;
            uint32_t ckon:1;
        } bit;
    } grxab7;
    union {
        uint32_t lsize;
        struct {
            uint32_t :8;
            uint32_t ckkg:8;
            uint32_t ckkb:8;
            uint32_t ckkr:8;
        } bit;
    } grxab8;
    union {
        uint32_t lsize;
        struct {
            uint32_t cka:8;
            uint32_t ckg:8;
            uint32_t ckb:8;
            uint32_t ckr:8;
        } bit;
    } grxab9;
    char           wk2[8];
    union {
        uint32_t lsize;
        struct {
            uint32_t :8;
            uint32_t g:8;
            uint32_t b:8;
            uint32_t r:8;
        } bit;
    } grxbase;
    union {
        uint32_t lsize;
        struct {
            uint32_t :15;
            uint32_t sel:1;
            uint32_t :5;
            uint32_t line:11;
        } bit;
    } grxclutint;
    union {
        uint32_t lsize;
        struct {
            uint32_t :15;
            uint32_t ufst:1;
            uint32_t :15;
            uint32_t arcst:1;
        } bit;
    } grxmon;
} st_glcdc_gr_t;
#pragma bit_order
#pragma packoption


/** Timing signals for driving the LCD panel */
typedef enum e_glcdc_tcon_signal_select
{
    GLCDC_TCON_SIGNAL_SELECT_STVA_VS = 0,  // STVA/VS
    GLCDC_TCON_SIGNAL_SELECT_STVB_VE = 1,  // STVB/VE
    GLCDC_TCON_SIGNAL_SELECT_STHA_HS = 2,  // STH/SP/HS
    GLCDC_TCON_SIGNAL_SELECT_STHB_HE = 3,  // STB/LP/HE
    GLCDC_TCON_SIGNAL_SELECT_DE      = 7   // DE
} glcdc_tcon_signal_select_t;

/** Fade control initial value set */
typedef enum e_glcd_fading_ctrl_initial_alpha
{
    GLCDC_FADING_CONTROL_INITIAL_ALPHA_MIN = 0,    // Initial alpha value setting for a graphics plane is zero.
    GLCDC_FADING_CONTROL_INITIAL_ALPHA_MAX = 0xff  // Initial alpha value setting for a graphics plane is maximum.
} glcdc_fade_ctrl_initial_alpha_t;


/** Blend plane select */
typedef enum e_glcdc_plane_blend
{
    GLCDC_PLANE_BLEND_TRANSPARENT = 1,     // Current graphics layer is transparent and the lower layer is displayed.
    GLCDC_PLANE_BLEND_NON_TRANSPARENT = 2, // Current graphics layer is displayed.
    GLCDC_PLANE_BLEND_ON_LOWER_LAYER = 3   // Current graphics layer is blended with the lower layer.
} glcdc_plane_blend_t;

/** Clut plane select */
typedef enum e_glcdc_clut_plane
{
    GLCDC_CLUT_PLANE_0 = 0,                // GLCD CLUT plane 0.
    GLCDC_CLUT_PLANE_1 = 1                 // GLCD CLUT plane 1.
} glcdc_clut_plane_t;

/** Dithering output format */
typedef enum e_glcdc_dithering_output_format
{
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB888 = 0,  // Dithering output format RGB888.
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB666 = 1,  // Dithering output format RGB666.
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB565 = 2   // Dithering output format RGB565.
} glcdc_dithering_output_format_t;

/** GLCD hardware specific control block */
typedef struct st_glcdc_ctrl
{
    glcdc_operating_status_t state;                                      // Status of GLCD module.
    bool is_entry;                                                       // Flag of subcribed GLCDC interrupt function.
    glcdc_coordinate_t active_start_pos;                                 // Zero coordinate for graphics plane.
    uint16_t hsize;                                                      // Horizontal pixel size in a line.
    uint16_t vsize;                                                      // Vertical pixel size in a frame.
    bool graphics_read_enable[GLCDC_FRAME_LAYER_NUM];                    // Graphics data read enable.
    void (*p_callback)(void *);                                          // Pointer to callback function.
    bool first_vpos_interrupt_flag;                                      // First vpos interrupt after release software reset.
    glcdc_interrupt_cfg_t interrupt;                                     // Interrupt setting values.
} glcdc_ctrl_t;




/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
glcdc_err_t r_glcdc_open_param_check(glcdc_cfg_t const * const p_cfg);
glcdc_err_t r_glcdc_param_check_layer(glcdc_runtime_cfg_t const * const p_runtime);
glcdc_err_t r_glcdc_param_check_clut(glcdc_clut_cfg_t const * const p_clut);
glcdc_err_t r_glcdc_param_check_brightness(glcdc_brightness_t const * const p_brightness);
glcdc_err_t r_glcdc_param_check_contrast(glcdc_contrast_t const * const p_contrast);
glcdc_err_t r_glcdc_param_check_gamma(glcdc_gamma_correction_t const * const p_gamma);
#endif

void r_glcdc_clock_set(glcdc_cfg_t const * const p_cfg);
void r_glcdc_sync_signal_set(glcdc_cfg_t const * const p_cfg);
void r_glcdc_background_screen_set(glcdc_cfg_t const * const p_cfg);
void r_glcdc_blend_condition_set(glcdc_blend_t const * const p_blend, glcdc_frame_layer_t frame);

void r_glcdc_graphics_layer_set(glcdc_input_cfg_t const * const p_input, glcdc_frame_layer_t frame);
void r_glcdc_graphics_chromakey_set(glcdc_chromakey_t const * const p_chromakey, glcdc_frame_layer_t frame);
void r_glcdc_output_block_set(glcdc_cfg_t const * const p_cfg);
void r_glcdc_brightness_correction(glcdc_brightness_t const * const p_brightness);
void r_glcdc_contrast_correction(glcdc_contrast_t const * const p_contrast);
void r_glcdc_gamma_correction(glcdc_gamma_correction_t const * const p_gamma);

void r_glcdc_detect_setting(glcdc_detect_cfg_t const * const p_detection);
void r_glcdc_interrupt_setting(glcdc_interrupt_cfg_t const * const p_interrupt);

void r_glcdc_graphics_read_enable(void);
void r_glcdc_bg_color_setting(glcdc_color_t const * const p_color);

void r_glcdc_power_on(void);
void r_glcdc_power_off(void);
void r_glcdc_release_software_reset(void);
void r_glcdc_software_reset(void);
void r_glcdc_clut_update(glcdc_clut_cfg_t const * const p_clut, glcdc_frame_layer_t frame);
void r_glcdc_clut_set(glcdc_frame_layer_t frame, glcdc_clut_plane_t clut_plane, uint32_t entry, uint32_t data);
void r_glcdc_bg_operation_enable(void);
void r_glcdc_bg_operation_disable(void);
bool r_glcdc_is_register_reflecting(void);
void r_glcdc_output_ctrl_update(void);
bool r_glcdc_is_output_ctrl_updating(void);
void r_glcdc_line_detect_number_set(uint32_t line);
bool r_glcdc_is_fading(glcdc_frame_layer_t frame);
glcdc_clut_plane_t r_glcdc_is_clutplane_selected(glcdc_frame_layer_t frame);

void r_glcdc_clutplane_select(glcdc_frame_layer_t frame, glcdc_clut_plane_t clut_plane);
void r_glcdc_gr_plane_update(glcdc_frame_layer_t frame);
bool r_glcdc_is_gr_plane_updating(glcdc_frame_layer_t frame);
void r_glcdc_gamma_update(void);
bool r_glcdc_is_gamma_updating(void);
bool r_glcdc_vpos_int_status_check(void);
bool r_glcdc_gr1uf_int_status_check(void);
bool r_glcdc_gr2uf_int_status_check(void);
void r_glcdc_vpos_int_status_clear(void);
void r_glcdc_gr1uf_int_status_clear(void);
void r_glcdc_gr2uf_int_status_clear(void);

void r_glcdc_line_detect_isr(void);
void r_glcdc_underflow_1_isr(void);
void r_glcdc_underflow_2_isr(void);

#endif /* R_GLCDC_PRIVATE_H */
