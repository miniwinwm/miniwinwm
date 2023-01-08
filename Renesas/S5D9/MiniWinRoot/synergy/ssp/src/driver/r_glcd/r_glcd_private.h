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
 * File Name    : r_glcd_private.h
 * Description  : GLCD HAL module private header file
 **********************************************************************************************************************/

#ifndef R_GLCD_PRIVATE_H
#define R_GLCD_PRIVATE_H

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define GLCD_CODE_VERSION_MAJOR (2U)
#define GLCD_CODE_VERSION_MINOR (0U)

/* Color look up table entry size */
#define GLCD_CLUT_ENTRY_SIZE (256U)

/* Panel timing, Maximum threshold */
#define BG_PLANE_H_CYC_MAX                (1024U)        ///< BG_PERI.FH (Max=1024)
#define BG_PLANE_V_CYC_MAX                (1024U)        ///< BG_PERI.FV (Max=1024)
#define BG_PLANE_HSYNC_POS_MAX            (15U)          ///< BG_SYNC.HP (Max=15)
#define BG_PLANE_VSYNC_POS_MAX            (15U)          ///< BG_SYNC.VP (Max=15)
#define BG_PLANE_H_CYC_ACTIVE_SIZE_MAX    (1016U)        ///< BG_HSIZE.HW (Max=1016)
#define BG_PLANE_V_CYC_ACTIVE_SIZE_MAX    (1020U)        ///< BG_VSIZE.VW (Max=1020)
#define BG_PLANE_H_CYC_ACTIVE_POS_MAX     (1006U)        ///< BG_HSIZE.HP (Max=1006, note that this value is 1cycle
                                                        // larger than GRn_AB3.GRCHS)
#define BG_PLANE_V_CYC_ACTIVE_POS_MAX     (1007U)        ///< BG_VSIZE.VP (Max=1007, note that this value is 1cycle
                                                        // larger than GRn_AB3.GRCVS)
#define GR_PLANE_TOTAL_TRANSFER_TIMES_MAX (65536U)       ///< GRn_FLM5.DATANUM (Max=65536)
#define GR_PLANE_TOTAL_LINE_NUMBER_MAX    (1020U)        ///< GRn_FLM5.LNNUM (Max=1020)
#define GR_PLANE_H_CYC_ACTIVE_SIZE_MAX    (1008U)        ///< GRn_AB3.GRCHW (Max=1016) ; Image Area, GRn_AB5.ARCHW (Max=1008)
                                                        // (Max=1016) ; Rectangular Area
#define GR_PLANE_V_CYC_ACTIVE_SIZE_MAX    (1020U)        ///< GRn_AB2.GRCVW (Max=1020) ; Image Area, GRn_AB4.ARCVW (Max=1020)
                                                        // (Max=1020) ; Rectangular Area
#define GR_PLANE_H_CYC_ACTIVE_POS_MAX     (1005U)        ///< GRn_AB3.GRCHS (Max=1005) ; Image Area, GRn_AB5.ARCHS (Max=1005)
                                                        // (Max=1005) ; Rectangular Area
#define GR_PLANE_V_CYC_ACTIVE_POS_MAX     (1006U)        ///< GRn_AB2.GRCVS (Max=1006) ; Image Area, GRn_AB4.ARCVS (Max=1006)
                                                        // (Max=1006) ; Rectangular Area
#define TCON_SYGNAL_ASSERT_WIDTH_MAX      (1023U)

/* Panel timing, Minimum threshold */
#define BG_PLANE_H_CYC_MIN             ((uint16_t) 24)   ///< BG_PERI.FH (Min=24)
#define BG_PLANE_V_CYC_MIN             ((uint16_t) 20)   ///< BG_PERI.FV (Min=20)
#define BG_PLANE_HSYNC_POS_MIN         ((uint16_t) 1)    ///< BG_HSYNC.HP (Min=1)
#define BG_PLANE_VSYNC_POS_MIN         ((uint16_t) 1)    ///< BG_HSYNC.VP (Min=1)
#define BG_PLANE_H_CYC_ACTIVE_SIZE_MIN ((uint16_t) 16)   ///< BG_HSIZE.HW (Min=16)
#define BG_PLANE_V_CYC_ACTIVE_SIZE_MIN ((uint16_t) 16)   ///< BG_VSIZE.VW (Min=16)
#define BG_PLANE_H_CYC_ACTIVE_POS_MIN  ((uint16_t) 6)    ///< BG_HSIZE.HP (Min= 6)
#define BG_PLANE_V_CYC_ACTIVE_POS_MIN  ((uint16_t) 3)    ///< BG_VSIZE.VP (Min= 3)
#define GR_PLANE_TOTAL_LINE_NUMBER_MIN (16U)             ///< GRn_FLM5.LNNUM (Min=16)
#define GR_PLANE_H_CYC_ACTIVE_SIZE_MIN (16U)             ///< GRn_AB3.GRCHW (Min=16) ; Image Area, GRn_AB5.ARCHW (Min= 1)
                                                         // ; Rectangular Area
#define GR_PLANE_V_CYC_ACTIVE_SIZE_MIN (16U)             ///< GRn_AB2.GRCVW (Min=16) ; Image Area, GRn_AB4.ARCVW (Min= 1)
                                                         // ; Rectangular Area

/* This driver sets same value to GRn_AB2.GRCVW and GRn_AB4.ARCVW, so the value of this macro
 * is defined as the number of GRn_AB2.GRCVW(larger value).
 */
#define GR_PLANE_H_CYC_ACTIVE_POS_MIN (5U)               ///< GRn_AB3.GRCHS (Min= 5) ; Image Area, GRn_AB5.ARCHS (Min= 5)
                                                        // ; Rectangular Area
#define GR_PLANE_V_CYC_ACTIVE_POS_MIN (2U)               ///< GRn_AB2.GRCVS (Min= 2) ; Image Area, GRn_AB4.ARCVS (Min= 2)
                                                        // ; Rectangular Area
#define TCON_SYGNAL_ASSERT_WIDTH_MIN  (0U)

/* Color correction setting threshold */
#define GLCD_BRIGHTNESS_DEFAULT  (512U)                  ///< OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Mid=512)
#define GLCD_BRIGHTNESS_MIN      (0U)                    ///< OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Min=0)
#define GLCD_BRIGHTNESS_MAX      (1023U)                 ///< OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Max=1023)
#define GLCD_CONTRAST_DEFAULT    (128U)                  ///< OUT_CONTRAST.CONTG and .CONTB and .CONTR (Mid=128)
#define GLCD_CONTRAST_MIN        (0U)                    ///< OUT_CONTRAST.CONTG and .CONTB and .CONTR (Min=0)
#define GLCD_CONTRAST_MAX        (255U)                  ///< OUT_CONTRAST.CONTG and .CONTB and .CONTR (Max=255)
#define GLCD_GAMMA_GAIN_MAX      (2047U)                 ///< GAMx_LUTn.GAIN15 - GAIN0 (Max=2047)
#define GLCD_GAMMA_THRESHOLD_MAX (1023U)                 ///< GAMx_AREAn.TH15  - TH0   (Max=1023)

#define GLCD_PANEL_CLKDIV_NUM    (13U)                   ///< The number of possible number of division ratio setting

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#endif /* R_GLCD_PRIVATE_H */
