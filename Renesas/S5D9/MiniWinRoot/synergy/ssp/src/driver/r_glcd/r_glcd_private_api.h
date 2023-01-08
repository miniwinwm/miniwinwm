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

#ifndef R_GLCD_PRIVATE_API_H
#define R_GLCD_PRIVATE_API_H

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
 * Private Instance API Functions. DO NOT USE! Use functions through Interface API structure instead.
 **********************************************************************************************************************/
ssp_err_t R_GLCD_Open       (display_ctrl_t * const p_ctrl, display_cfg_t const * const p_cfg);
ssp_err_t R_GLCD_Close      (display_ctrl_t * const p_ctrl);
ssp_err_t R_GLCD_Start      (display_ctrl_t * const p_ctrl);
ssp_err_t R_GLCD_Stop       (display_ctrl_t * const p_ctrl);
ssp_err_t R_GLCD_LayerChange (display_ctrl_t const * const        p_ctrl,
                              display_runtime_cfg_t const * const p_cfg,
                              display_frame_layer_t               frame);
ssp_err_t R_GLCD_ColorCorrection (display_ctrl_t const * const       p_ctrl,
                                  display_correction_t const * const p_correction);
ssp_err_t R_GLCD_ClutUpdate (display_ctrl_t const * const     p_ctrl,
                             display_clut_cfg_t const * const p_clut_cfg,
                             display_frame_layer_t            frame);
ssp_err_t R_GLCD_StatusGet  (display_ctrl_t const * const p_ctrl, display_status_t * const status);
ssp_err_t R_GLCD_VersionGet (ssp_version_t * p_version);

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* R_GLCD_PRIVATE_API_H */
