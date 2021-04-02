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
 * File Name    : r_glcdc_rx65n.c
 * Version      : 1.00
 * Description  : Internal function program using in GLCDC API functions.
 ************************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version   Description
 *         : 01.10.2017 1.00      First Release
***********************************************************************************************************************/
/***********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 ************************************************************************************************************************/
#include "r_glcdc_private.h"

/***********************************************************************************************************************
 Imported global variables and functions (from other files)
 ***********************************************************************************************************************/
extern glcdc_ctrl_t g_ctrl_blk;


/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/
/* Structure pointer for accessing iodefine witch related to graphic 1 and graphic 2 */
volatile st_glcdc_gr_t __evenaccess * gp_gr[GLCDC_FRAME_LAYER_NUM] =
{
    (st_glcdc_gr_t __evenaccess *)&GLCDC.GR1VEN,
    (st_glcdc_gr_t __evenaccess *)&GLCDC.GR2VEN
};

/* Structure pointer for accessing iodefine witch related to graphic 1 and graphic 2 color look up table */
volatile st_glcdc_gr_clut_t __evenaccess * gp_gr_clut[GLCDC_FRAME_LAYER_NUM][GLCDC_CLUT_PLANE_NUM] =
{
 {
    (st_glcdc_gr_clut_t __evenaccess *)&GLCDC.GR1CLUT0[0],
    (st_glcdc_gr_clut_t __evenaccess *)&GLCDC.GR1CLUT1[0]
 },
 {
    (st_glcdc_gr_clut_t __evenaccess *)&GLCDC.GR2CLUT0[0],
    (st_glcdc_gr_clut_t __evenaccess *)&GLCDC.GR2CLUT1[0]
 }
};

/* ---- private prototype functions ---- */
static uint16_t r_glcdc_get_bit_size(glcdc_in_format_t format);
static void r_glcdc_gr_plane_format_set(glcdc_in_format_t format, glcdc_frame_layer_t frame);
static void r_glcdc_hsync_set(glcdc_tcon_pin_t tcon, glcdc_timing_t const * const p_timing,
        glcdc_signal_polarity_t polarity);
static void r_glcdc_vsync_set(glcdc_tcon_pin_t tcon, glcdc_timing_t const * const p_timing,
        glcdc_signal_polarity_t polarity);
static void r_glcdc_data_enable_set(glcdc_tcon_pin_t tcon, glcdc_timing_t const * const p_vtiming,
        glcdc_timing_t const * const p_htiming, glcdc_signal_polarity_t polarity);


#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
/* ---- private prototype functions and variables for parameter checking ---- */
static glcdc_err_t r_glcdc_param_check_sync_signal (glcdc_cfg_t const * const p_cfg);

/*******************************************************************************
 * Outline      : Parameter check for synchronize signal
 * Function Name: r_glcdc_param_check_sync_signal
 * Description  : This function is parameter check of output signal.
 * Arguments    : p_cfg -
 *                  Pointer of setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_TIMING_SETTING -
 *                  Invalid panel timing parameter.
 * Note         : none
 *******************************************************************************/
static glcdc_err_t r_glcdc_param_check_sync_signal (glcdc_cfg_t const * const p_cfg)
{
    uint32_t hsync_total_cyc;
    uint32_t vsync_total_cyc;
    uint32_t hsync_active_pos_cyc;
    uint32_t vsync_active_pos_cyc;

    /* Calculation of total cycle */
    hsync_total_cyc = (((p_cfg->output.htiming.front_porch + p_cfg->output.htiming.sync_width)
            + p_cfg->output.htiming.display_cyc) + p_cfg->output.htiming.back_porch);
    vsync_total_cyc = (((p_cfg->output.vtiming.front_porch + p_cfg->output.vtiming.sync_width)
            + p_cfg->output.vtiming.display_cyc) + p_cfg->output.vtiming.back_porch);

    /* Calculation of active position cycle */
    hsync_active_pos_cyc = (((p_cfg->output.htiming.front_porch - BG_PLANE_H_CYC_MARGIN_MIN)
            + p_cfg->output.htiming.sync_width) + p_cfg->output.htiming.back_porch);
    vsync_active_pos_cyc = (((p_cfg->output.vtiming.front_porch - BG_PLANE_V_CYC_MARGIN_MIN)
            + p_cfg->output.vtiming.sync_width) + p_cfg->output.vtiming.back_porch);


    /* Total cycle */
    if ((BG_PLANE_H_CYC_MIN > hsync_total_cyc) || (BG_PLANE_H_CYC_MAX < hsync_total_cyc))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    if((BG_PLANE_V_CYC_MIN > vsync_total_cyc) || (BG_PLANE_V_CYC_MAX < vsync_total_cyc))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* Front porch */
    if ((BG_PLANE_H_FRONT_PORCH_MIN > p_cfg->output.htiming.front_porch)
            || (BG_PLANE_H_FRONT_PORCH_MAX < p_cfg->output.htiming.front_porch))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    if ((BG_PLANE_V_FRONT_PORCH_MIN > p_cfg->output.vtiming.front_porch)
            || (BG_PLANE_V_FRONT_PORCH_MAX < p_cfg->output.vtiming.front_porch))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* Display cycle */
    if ((BG_PLANE_H_CYC_ACTIVE_SIZE_MIN > p_cfg->output.htiming.display_cyc) || (BG_PLANE_H_CYC_ACTIVE_SIZE_MAX < p_cfg->output.htiming.display_cyc))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    if ((BG_PLANE_V_CYC_ACTIVE_SIZE_MIN > p_cfg->output.vtiming.display_cyc) || (BG_PLANE_V_CYC_ACTIVE_SIZE_MAX < p_cfg->output.vtiming.display_cyc))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    if ((true == p_cfg->output.dithering.dithering_on)
            && (GLCDC_DITHERING_MODE_2X2PATTERN == p_cfg->output.dithering.dithering_mode))
    {

        if (GLCDC_OUT_FORMAT_8BITS_SERIAL == p_cfg->output.format)
        {
            if (2 != (p_cfg->output.htiming.display_cyc & ALIGNMENT_4_MASK))
            {
                return GLCDC_ERR_INVALID_TIMING_SETTING;
            }
        }
        else
        {
            if (0 != (p_cfg->output.htiming.display_cyc & ALIGNMENT_4_MASK))
            {
                return GLCDC_ERR_INVALID_TIMING_SETTING;
            }
        }

        if (0 != (p_cfg->output.vtiming.display_cyc & ALIGNMENT_2_MASK))
        {
            return GLCDC_ERR_INVALID_TIMING_SETTING;
        }

    }


    /* Back Porch check for Hardware limitation */
    if (BG_PLANE_H_BACK_PORCH_MIN > p_cfg->output.htiming.back_porch)
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* sync width in HSYNC check for Hardware limitation */
    if (TCON_H_SYNC_WIDTH_MAX < p_cfg->output.htiming.sync_width)
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* Total of back porch and sync width in HSYNC check for Hardware limitation */
    if (TCON_H_SYNC_POS_MAX < (p_cfg->output.htiming.sync_width +  p_cfg->output.htiming.back_porch))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* Total of front porch, back porch and sync width in HSYNC check for Hardware limitation */
    if ((BG_PLANE_H_ACTIVE_POS_MIN > hsync_active_pos_cyc)
            || (BG_PLANE_H_ACTIVE_POS_MAX < hsync_active_pos_cyc))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* Back Porch check for Hardware limitation */
    if (BG_PLANE_V_BACK_PORCH_MIN > p_cfg->output.vtiming.back_porch)
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* sync width in VSYNC check for Hardware limitation */
    if (TCON_V_SYNC_WIDTH_MAX < p_cfg->output.vtiming.sync_width)
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* Total of back porch and sync width in VSYNC check for Hardware limitation */
    if (TCON_V_SYNC_POS_MAX < (p_cfg->output.vtiming.sync_width +  p_cfg->output.vtiming.back_porch))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    /* Total of front porch, back porch and sync width in VSYNC check for Hardware limitation */
    if ((BG_PLANE_V_ACTIVE_POS_MIN > vsync_active_pos_cyc)
            || (BG_PLANE_V_ACTIVE_POS_MAX < vsync_active_pos_cyc))
    {
        return GLCDC_ERR_INVALID_TIMING_SETTING;
    }

    return GLCDC_SUCCESS;
} /* End of function r_glcdc_param_check_sync_signal() */

/*******************************************************************************
 * Outline      : Parameter check for layer setting
 * Function Name: r_glcdc_param_check_layer
 * Description  : Parameter check of graphic 1, 2.
 * Arguments    : p_runtime -
 *                  Pointer of layer setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_LAYER_SETTING -
 *                  Invalid layer setting found.
 *                GLCDC_ERR_INVALID_ALIGNMENT -
 *                  Invalid memory alignment found.
 *                GLCDC_ERR_INVALID_BLEND_SETTING -
 *                  Invalid blend setting found.
 * Note         : none
 *******************************************************************************/
glcdc_err_t r_glcdc_param_check_layer(glcdc_runtime_cfg_t const * const p_runtime)
{
    uint32_t line_byte_num;
    uint32_t line_trans_num;
    
    /* Check graphics, blending, and chroma key invalid setting combination */
    if (true == p_runtime->blend.visible)
    {
        if (GLCDC_BLEND_CONTROL_NONE == p_runtime->blend.blend_control)
        {
            if (true == p_runtime->chromakey.enable)
            {
                return GLCDC_ERR_INVALID_ARG;
            }
        }
    }
    else
    {
        if ((GLCDC_BLEND_CONTROL_NONE != p_runtime->blend.blend_control) && (GLCDC_BLEND_CONTROL_PIXEL != p_runtime->blend.blend_control))
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (true == p_runtime->chromakey.enable)
        {
            return GLCDC_ERR_INVALID_ARG;
        }
    }


    /* Base address and memory stride have to be aligned to 64-byte boundary */
    if (0 != ((uint32_t) (p_runtime->input.p_base) & GLCDC_ADDRESS_ALIGNMENT_64B))
    {
        return GLCDC_ERR_INVALID_ALIGNMENT;
    }

    /* Graphics horizontal size x check for Hardware limitation */
    if ((GR_PLANE_H_CYC_ACTIVE_SIZE_MIN > p_runtime->input.hsize) || (GR_PLANE_H_CYC_ACTIVE_SIZE_MAX < p_runtime->input.hsize))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Convert to byte size of Single line data transfer, round up fractions below the decimal point */
    line_byte_num = ((r_glcdc_get_bit_size(p_runtime->input.format) * p_runtime->input.hsize) / 8);
    if (0 != ((r_glcdc_get_bit_size(p_runtime->input.format) * p_runtime->input.hsize) % 8))
    {
        line_byte_num += 1;
    }
    
    /* Convert to Single line data transfer count, round up fractions below the decimal point */
    line_trans_num = (line_byte_num >> 6);
    if (0 != (line_byte_num & GLCDC_ADDRESS_ALIGNMENT_64B))
    {
        line_trans_num += 1;
    }

    /* Single line data transfer count check for Hardware limitation */
    if (GR_PLANE_DATANUM_POS_MAX < line_trans_num)
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics horizontal size check for Software limitation */
    if (g_ctrl_blk.hsize < p_runtime->input.hsize)
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    if (0 != ((p_runtime->input.hsize) & ALIGNMENT_2_MASK))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics vertical size y check for Hardware limitation */
    if ((GR_PLANE_V_CYC_ACTIVE_SIZE_MIN > p_runtime->input.vsize) || (GR_PLANE_V_CYC_ACTIVE_SIZE_MAX < p_runtime->input.vsize))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics vertical size check for Software limitation  */
    if (g_ctrl_blk.vsize < p_runtime->input.vsize)
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Line stride have to be aligned to 64-byte boundary */
    if (0 != (p_runtime->input.offset & GLCDC_ADDRESS_ALIGNMENT_64B))
    {
        return GLCDC_ERR_INVALID_ALIGNMENT;
    }

    if ((GR_PLANE_LNOFF_POS_MIN > p_runtime->input.offset) || (GR_PLANE_LNOFF_POS_MAX < p_runtime->input.offset))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Check the layer offset coordinate setting */

    /* Graphics start position x check for Hardware limitation */
    if ((GR_PLANE_H_ACTIVE_POS_MIN > (p_runtime->input.coordinate.x + g_ctrl_blk.active_start_pos.x)) || (GR_PLANE_H_ACTIVE_POS_MAX < (p_runtime->input.coordinate.x + g_ctrl_blk.active_start_pos.x)))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics start position x check for software limitation */
    if ((0 > p_runtime->input.coordinate.x) || (g_ctrl_blk.hsize < p_runtime->input.coordinate.x))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics end position x check for software limitation */
    if ((0 > (p_runtime->input.coordinate.x + p_runtime->input.hsize)) || (g_ctrl_blk.hsize < (p_runtime->input.coordinate.x + p_runtime->input.hsize)))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics start position y check for Hardware limitation */
    if ((GR_PLANE_V_ACTIVE_POS_MIN > (p_runtime->input.coordinate.y + g_ctrl_blk.active_start_pos.y)) || (GR_PLANE_V_ACTIVE_POS_MAX < (p_runtime->input.coordinate.y + g_ctrl_blk.active_start_pos.y)))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics start position y check for software limitation */
    if ((0 > p_runtime->input.coordinate.y) || (g_ctrl_blk.vsize < p_runtime->input.coordinate.y))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* Graphics end position y check for software limitation */
    if ((0 > (p_runtime->input.coordinate.y + p_runtime->input.vsize)) || (g_ctrl_blk.vsize < (p_runtime->input.coordinate.y + p_runtime->input.vsize)))
    {
        return GLCDC_ERR_INVALID_LAYER_SETTING;
    }

    /* In case of fade in setting to fade fixed setting */
    if ((GLCDC_BLEND_CONTROL_FADEIN <= p_runtime->blend.blend_control)
            && (GLCDC_BLEND_CONTROL_FIXED >= p_runtime->blend.blend_control))
    {
        /* Blend start position x check for Hardware limitation */
        if ((GR_BLEND_H_ACTIVE_POS_MIN > (p_runtime->blend.start_coordinate.x + g_ctrl_blk.active_start_pos.x)) || (GR_BLEND_H_ACTIVE_POS_MAX < (p_runtime->blend.start_coordinate.x + g_ctrl_blk.active_start_pos.x)))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Blend end position x check for Hardware limitation */
        if ((GR_BLEND_H_CYC_ACTIVE_SIZE_MIN > (p_runtime->blend.end_coordinate.x - p_runtime->blend.start_coordinate.x)) || (GR_BLEND_H_CYC_ACTIVE_SIZE_MAX < (p_runtime->blend.end_coordinate.x - p_runtime->blend.start_coordinate.x)))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Blend start position x check for software limitation */
        if ((0 > p_runtime->blend.start_coordinate.x) || (g_ctrl_blk.hsize < p_runtime->blend.start_coordinate.x))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Blend end position x check for software limitation */
        if ((0 > p_runtime->blend.end_coordinate.x) || (g_ctrl_blk.hsize < p_runtime->blend.end_coordinate.x))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Combination of start position and end position x check */
        if (p_runtime->blend.start_coordinate.x >= p_runtime->blend.end_coordinate.x)
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Blend start position y check for Hardware limitation */
        if ((GR_BLEND_V_ACTIVE_POS_MIN > (p_runtime->blend.start_coordinate.y + g_ctrl_blk.active_start_pos.y)) || (GR_BLEND_V_ACTIVE_POS_MAX < (p_runtime->blend.start_coordinate.y + g_ctrl_blk.active_start_pos.y)))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Blend end position y check for Hardware limitation */
        if ((GR_BLEND_V_CYC_ACTIVE_SIZE_MIN > (p_runtime->blend.end_coordinate.y - p_runtime->blend.start_coordinate.y)) || (GR_BLEND_V_CYC_ACTIVE_SIZE_MAX < (p_runtime->blend.end_coordinate.y - p_runtime->blend.start_coordinate.y)))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Blend start position y check for software limitation */
        if ((0 > p_runtime->blend.start_coordinate.y) || (g_ctrl_blk.vsize < p_runtime->blend.start_coordinate.y))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Blend end position y check for software limitation */
        if ((0 > p_runtime->blend.end_coordinate.y) || (g_ctrl_blk.vsize < p_runtime->blend.end_coordinate.y))
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

        /* Combination of start position and end position y check */
        if (p_runtime->blend.start_coordinate.y >= p_runtime->blend.end_coordinate.y)
        {
            return GLCDC_ERR_INVALID_BLEND_SETTING;
        }

    }

    /* In case of chroma key is enabled */
    if (true == p_runtime->chromakey.enable)
    {
        if (GLCDC_CHROMAKEY_BEFORE_MAX <  p_runtime->chromakey.before.byte.r)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CHROMAKEY_BEFORE_MAX < p_runtime->chromakey.before.byte.g)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CHROMAKEY_BEFORE_MAX < p_runtime->chromakey.before.byte.b)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CHROMAKEY_AFTER_MAX <  p_runtime->chromakey.after.byte.r)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CHROMAKEY_AFTER_MAX < p_runtime->chromakey.after.byte.g)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CHROMAKEY_AFTER_MAX < p_runtime->chromakey.after.byte.b)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CHROMAKEY_AFTER_MAX < p_runtime->chromakey.after.byte.a)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

    }

    return GLCDC_SUCCESS;
} /* End of function r_glcdc_param_check_layer() */


/*******************************************************************************
 * Outline      : Parameter check for color palette setting
 * Function Name: r_glcdc_param_check_clut
 * Description  : Parameter check of color palette setting.
 * Arguments    : p_clut -
 *                  Pointer of color palette setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_CLUT_ACCESS -
 *                  Invalid access to color palette entry.
 * Note         : none
 *******************************************************************************/
glcdc_err_t r_glcdc_param_check_clut(glcdc_clut_cfg_t const * const p_clut)
{
    if (true == p_clut->enable)
    {
        /* Check whether the base address is Null or not */
        if (NULL == p_clut->p_base)
        {
            return GLCDC_ERR_INVALID_CLUT_ACCESS;
        }

        /* Setting value is less than 256 */
        if (GLCDC_CLUT_ENTRY_SIZE <= p_clut->start)
        {
            return GLCDC_ERR_INVALID_CLUT_ACCESS;
        }

        /* Check whether the base address is 0 or not */
        if (0 == p_clut->size)
        {
            return GLCDC_ERR_INVALID_CLUT_ACCESS;
        }

        /* Total value of start index and pallete size is 256 or less */
        if (GLCDC_CLUT_ENTRY_SIZE < (p_clut->start + p_clut->size))
        {
            return GLCDC_ERR_INVALID_CLUT_ACCESS;
        }
    }

    return GLCDC_SUCCESS;
} /* End of function r_glcdc_param_check_clut() */


/*******************************************************************************
 * Outline      : Parameter check for brightness setting
 * Function Name: r_glcdc_param_check_brightness
 * Description  : Parameter check of brightness setting.
 * Arguments    : p_brightness -
 *                  Pointer of brightness setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid p_brightness setting found.
 * Note         : none
 *******************************************************************************/
glcdc_err_t r_glcdc_param_check_brightness(glcdc_brightness_t const * const p_brightness)
{
    if (true == p_brightness->enable)
    {
        if (GLCDC_BRIGHTNESS_MAX < p_brightness->r)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_BRIGHTNESS_MAX < p_brightness->g)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_BRIGHTNESS_MAX < p_brightness->b)
        {
            return GLCDC_ERR_INVALID_ARG;
        }
    }

    return GLCDC_SUCCESS;
} /* End of function r_glcdc_param_check_brightness() */

/*******************************************************************************
 * Outline      : Parameter check for contrast setting
 * Function Name: r_glcdc_param_check_contrast
 * Description  : Parameter check of contrast setting.
 * Arguments    : p_contrast -
 *                  Pointer of contrast setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid contrast setting found.
 * Note         : none
 *******************************************************************************/
glcdc_err_t r_glcdc_param_check_contrast(glcdc_contrast_t const * const p_contrast)
{
    if (true == p_contrast->enable)
    {
        if (GLCDC_CONTRAST_MAX < p_contrast->r)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CONTRAST_MAX < p_contrast->g)
        {
            return GLCDC_ERR_INVALID_ARG;
        }

        if (GLCDC_CONTRAST_MAX < p_contrast->b)
        {
            return GLCDC_ERR_INVALID_ARG;
        }
    }

    return GLCDC_SUCCESS;
} /* End of function r_glcdc_param_check_contrast() */

/*******************************************************************************
 * Outline      : Parameter check for gamma setting
 * Function Name: r_glcdc_param_check_gamma
 * Description  : Parameter check of gamma setting.
 * Arguments    : p_gamma -
 *                  Pointer of gamma setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_GAMMA_SETTING -
 *                  Invalid gamma correction setting found.
 * Note         : none
 *******************************************************************************/
glcdc_err_t r_glcdc_param_check_gamma(glcdc_gamma_correction_t const * const p_gamma)
{
    int32_t i;
    uint16_t previous_threshold;

    if (true == p_gamma->enable)
    {
        previous_threshold = 0;
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i++)
        {
            /* Each of the gamma correction threshold values must be less than GLCDC_GAMMA_THRESHOLD_MAX */
            if (GLCDC_GAMMA_THRESHOLD_MAX < p_gamma->p_b->threshold[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }

            /* The Gamma correction threshold[N] must be less than threshold[N+1] */
            if (previous_threshold > p_gamma->p_b->threshold[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }

            /* The Gamma correction threshold[N] is THn = THn + 1 may be used, only when THn = GLCDC_GAMMA_THRESHOLD_MAX. */
            if ((previous_threshold == p_gamma->p_b->threshold[i]) && (GLCDC_GAMMA_THRESHOLD_MAX != p_gamma->p_b->threshold[i]))
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }


            previous_threshold = p_gamma->p_b->threshold[i];
        }

        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i++)
        {
            /* Each of gamma correction gain values must be less than GLCDC_GAMMA_GAIN_MAX */
            if (GLCDC_GAMMA_GAIN_MAX < p_gamma->p_b->gain[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }
        }

        previous_threshold = 0;
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i++)
        {
            /* Each of gamma correction threshold value must be less than GLCDC_GAMMA_THRESHOLD_MAX */
            if (GLCDC_GAMMA_THRESHOLD_MAX < p_gamma->p_g->threshold[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }

            /* Gamma correction threshold[N] must be less than threshold[N+1] */
            if (previous_threshold > p_gamma->p_g->threshold[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }

            /* The Gamma correction threshold[N] is THn = THn + 1 may be used, only when THn = GLCDC_GAMMA_THRESHOLD_MAX. */
            if ((previous_threshold == p_gamma->p_g->threshold[i]) && (GLCDC_GAMMA_THRESHOLD_MAX != p_gamma->p_g->threshold[i]))
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }


            previous_threshold = p_gamma->p_g->threshold[i];
        }

        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i++)
        {
            /* Each of gamma correction gain value must be less than GLCDC_GAMMA_GAIN_MAX */
            if (GLCDC_GAMMA_GAIN_MAX < p_gamma->p_g->gain[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }
        }

        previous_threshold = 0;
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i++)
        {
            /* Each of gamma correction threshold value must be less than GLCDC_GAMMA_THRESHOLD_MAX */
            if (GLCDC_GAMMA_THRESHOLD_MAX < p_gamma->p_r->threshold[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }

            /* Gamma correction threshold[N] must be less than threshold[N+1] */
            if (previous_threshold > p_gamma->p_r->threshold[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }

            /* The Gamma correction threshold[N] is THn = THn + 1 may be used, only when THn = GLCDC_GAMMA_THRESHOLD_MAX. */
            if ((previous_threshold == p_gamma->p_r->threshold[i]) && (GLCDC_GAMMA_THRESHOLD_MAX != p_gamma->p_r->threshold[i]))
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }


            previous_threshold = p_gamma->p_r->threshold[i];
        }

        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i++)
        {
            /* Each of gamma correction gain value must be less than GLCDC_GAMMA_GAIN_MAX */
            if (GLCDC_GAMMA_GAIN_MAX < p_gamma->p_r->gain[i])
            {
                return GLCDC_ERR_INVALID_GAMMA_SETTING;
            }
        }
    }

    return GLCDC_SUCCESS;
} /* End of function r_glcdc_param_check_gamma() */


/*******************************************************************************
 * Outline      : Parameter check for all setting
 * Function Name: r_glcdc_open_param_check
 * Description  : Parameter check of R_GLCDC_Open function.
 * Arguments    : p_cfg -
 *                  Pointer of open setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_PTR -
 *                  Pointer to the control block or the configuration structure is NULL.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid parameter in the argument.
 *                GLCDC_ERR_INVALID_MODE -
 *                  Incorrect mode.
 *                GLCDC_ERR_INVALID_TIMING_SETTING -
 *                  Invalid panel timing parameter.
 *                GLCDC_ERR_INVALID_LAYER_SETTING -
 *                  Invalid layer setting found.
 *                GLCDC_ERR_INVALID_ALIGNMENT -
 *                  Invalid memory alignment found.
 *                GLCDC_ERR_INVALID_GAMMA_SETTING -
 *                  Invalid gamma correction setting found.
 *                GLCDC_ERR_INVALID_BLEND_SETTING -
 *                  Invalid blend setting found.
 * Note         : none
 *******************************************************************************/
glcdc_err_t r_glcdc_open_param_check(glcdc_cfg_t const * const p_cfg)
{
    glcdc_err_t err;
    glcdc_runtime_cfg_t runtime_cfg;

    /* Sync signal parameter check */
    err = r_glcdc_param_check_sync_signal (p_cfg);
    if (GLCDC_SUCCESS != err)
    {
        return err;
    }

    /* Layer setting parameter check */
    if (true == g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_1])
    {
        runtime_cfg.input = p_cfg->input[GLCDC_FRAME_LAYER_1];
        runtime_cfg.blend = p_cfg->blend[GLCDC_FRAME_LAYER_1];
        runtime_cfg.chromakey = p_cfg->chromakey[GLCDC_FRAME_LAYER_1];

        err = r_glcdc_param_check_layer (&runtime_cfg);
        if (GLCDC_SUCCESS != err)
        {
            return err;
        }

        err = r_glcdc_param_check_clut(&p_cfg->clut[GLCDC_FRAME_LAYER_1]);
        if (GLCDC_SUCCESS != err)
        {
            return err;
        }
    }

    if (true == g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_2])
    {
        runtime_cfg.input = p_cfg->input[GLCDC_FRAME_LAYER_2];
        runtime_cfg.blend = p_cfg->blend[GLCDC_FRAME_LAYER_2];
        runtime_cfg.chromakey = p_cfg->chromakey[GLCDC_FRAME_LAYER_2];

        err = r_glcdc_param_check_layer (&runtime_cfg);
        if (GLCDC_SUCCESS != err)
        {
            return err;
        }

        err = r_glcdc_param_check_clut(&p_cfg->clut[GLCDC_FRAME_LAYER_2]);
        if (GLCDC_SUCCESS != err)
        {
            return err;
        }
    }

    /* Color correction setting parameter check */
    err = r_glcdc_param_check_brightness (&p_cfg->output.brightness);
    if (GLCDC_SUCCESS != err)
    {
        return err;
    }

    err = r_glcdc_param_check_contrast (&p_cfg->output.contrast);
    if (GLCDC_SUCCESS != err)
    {
        return err;
    }

    err = r_glcdc_param_check_gamma (&p_cfg->output.gamma);
    if (GLCDC_SUCCESS != err)
    {
        return err;
    }

    return GLCDC_SUCCESS;
} /* End of function r_glcdc_open_param_check() */
#endif /* if (GLCDC_CFG_PARAM_CHECKING_ENABLE) */


/*******************************************************************************
 * Outline      : Panel clock setting
 * Function Name: r_glcdc_clock_set
 * Description  : Panel clock, pixel clock setting.
 * Arguments    : p_cfg -
 *                  Pointer of panel clock setting parameter.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_clock_set(glcdc_cfg_t const * const p_cfg)
{
    /* PANELCLK - Panel Clock Control Register
    b31:b25 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b24     Reserved - These bits are read as 1. Writing to this bit has no effect.
    b23:b21 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b20     Reserved - These bits are read as 1. Writing to this bit has no effect.
    b19:b16 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b15:b13 Reserved - These bits are read as 0. The write value should be 0.
    b12     PIXSEL   - Pixel Clock Select. - No frequency division (parallel RGB) or Divided-by-4 (serial RGB)
    b11:b9  Reserved - These bits are read as 0. The write value should be 0.
    b8      CLKSEL   - Clock Source Select. - Select LCD_EXTCLK (external clock) or Select PLL clock.
    b7      Reserved - This bit is read as 0. The write value should be 0.
    b6      CLKEN    - Panel Clock Output Enable. - Disable LCD_CLK output or Enable LCD_CLK output.
    b5      DCDR[5:0]- Clock Division Ratio Setting. - Divide-by-2 to Divide-by-32. */

    /* Selects input source for panel clock */
    GLCDC.PANELCLK.BIT.CLKSEL = (uint32_t)p_cfg->output.clksrc;

    /* Sets division ratio */
    GLCDC.PANELCLK.BIT.DCDR = (uint32_t)p_cfg->output.clock_div_ratio & SYSCNT_PANEL_CLK_DCDR_MASK;

    /* Selects pixel clock output */
    if (GLCDC_OUT_FORMAT_8BITS_SERIAL != p_cfg->output.format)
    {
        GLCDC.PANELCLK.BIT.PIXSEL = 0; /* ParallelRGBSelect */
    }
    else
    {
        GLCDC.PANELCLK.BIT.PIXSEL = 1; /* SerialRGBSelect */
    }

    GLCDC.PANELCLK.BIT.CLKEN = 1; /* Panel Clock(LCD_CLK) Output Enable */

    /* Waiting for supply of panel clock(LCD_CLK) and pixel clock(PXCLK)
     * The BGMON.SWRST bit is sampled with PXCLK. Therefore, if the CLKEN bit is set,
     * the BGEN.SWRST bit is reflected on the BGMON.SWRST bit. */
    while (0 == GLCDC.BGMON.BIT.SWRST)
    {
        nop();
    }

} /* End of function r_glcdc_clock_set() */


/*******************************************************************************
 * Outline      : Sync signal setting (TCON block setting)
 * Function Name: r_glcdc_sync_signal_set
 * Description  : Port output signal setting. (Hsync, Vsync, Data Enable)
 * Arguments    : p_cfg -
 *                  Pointer of sync signal setting parameter.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_sync_signal_set(glcdc_cfg_t const * const p_cfg)
{
    /* CLKPHASE - Output Phase Control Register
    b31:b13 Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b12     FRONTGAM  - Correction Sequence Control.
    b11:b9  Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b8      LCDEDG    - DATA Output Phase Control. - synchronized with rising or falling edges of LCD_CLK
    b7      Reserved  - This bit is read as 0. The write value should be 0.
    b6      TCON0EDGE - TCON0 Output Phase Control. - synchronized with rising or falling edges of LCD_CLK
    b5      TCON1EDGE - TCON1 Output Phase Control. - synchronized with rising or falling edges of LCD_CLK
    b4      TCON2EDGE - TCON2 Output Phase Control. - synchronized with rising or falling edges of LCD_CLK
    b3      TCON3EDGE - TCON3 Output Phase Control. - synchronized with rising or falling edges of LCD_CLK
    b2:b0   Reserved  - These bits are read as 0. Writing to these bits have no effect. */
    GLCDC.CLKPHASE.BIT.LCDEDG = (uint32_t)p_cfg->output.sync_edge;
    GLCDC.CLKPHASE.BIT.TCON0EDG = (uint32_t)p_cfg->output.sync_edge;
    GLCDC.CLKPHASE.BIT.TCON1EDG = (uint32_t)p_cfg->output.sync_edge;
    GLCDC.CLKPHASE.BIT.TCON2EDG = (uint32_t)p_cfg->output.sync_edge;
    GLCDC.CLKPHASE.BIT.TCON3EDG = (uint32_t)p_cfg->output.sync_edge;


    /* TCONTIM - Reference Timing Setting Register
    b31:b27  Reserved     - These bits are read as 0. Writing to these bits have no effect.
    b26:b16  HALF[10:0]   - Vertical synchronization signal change timing setting.
    b15:b11  Reserved     - These bits are read as 0. Writing to these bits have no effect.
    b10:b0   OFFSET[10:0] - Horizontal synchronization signal generation reference timing. */
    GLCDC.TCONTIM.BIT.OFFSET = 0; /* 1 pixel */
    GLCDC.TCONTIM.BIT.HALF = 0;   /* 1 pixel (No delay) */

    r_glcdc_hsync_set (p_cfg->output.tcon_hsync, &p_cfg->output.htiming, p_cfg->output.hsync_polarity);
    r_glcdc_vsync_set (p_cfg->output.tcon_vsync, &p_cfg->output.vtiming, p_cfg->output.vsync_polarity);
    r_glcdc_data_enable_set (p_cfg->output.tcon_de, &p_cfg->output.vtiming, &p_cfg->output.htiming, p_cfg->output.data_enable_polarity);

} /* End of function r_glcdc_sync_signal_set() */


/*******************************************************************************
 * Outline      : Horizontal signal setting
 * Function Name: r_glcdc_hsync_set
 * Description  : Horizontal synchronization signal (HS) output setting.
 * Arguments    : tcon -
 *                  Tcon pin select.
 *                p_timing -
 *                  Pointer of hsync signal timing parameter.
 *                polarity -
 *                  Polarity select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
static void r_glcdc_hsync_set(glcdc_tcon_pin_t tcon, glcdc_timing_t const * const p_timing, glcdc_signal_polarity_t polarity)
{
    switch (tcon)
    {
        case GLCDC_TCON_PIN_1:
            GLCDC.TCONSTVB2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS; /* Hsync(STHA) -> TCON1 */
        break;
        case GLCDC_TCON_PIN_2:
            GLCDC.TCONSTHA2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS; /* Hsync(STHA) -> TCON2 */
        break;
        case GLCDC_TCON_PIN_3:
            GLCDC.TCONSTHB2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS; /* Hsync(STHA) -> TCON3 */
        break;
        case GLCDC_TCON_PIN_0: /* Intentionally go though to the default case */
        default:
            GLCDC.TCONSTVA2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STHA_HS; /* Hsync(STHA) -> TCON0 */
        break;
    }

    /* Polarity of a signal select */
    /* TCONSTHA2 - Horizontal Timing Setting Register A2
    b31:b9 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b8     HSSEL    - STHy Signal Reference Timing Select. - Select HS signal or
                      the TCONTIM.OFFSET[10:0] bits as reference for signal generation.
    b7:b5  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b4     INV      - STHy Signal Polarity Inversion. - Do not invert the STHy signal or Invert the STHy signal.
    b3     Reserved - These bits are read as 0. Writing to these bits have no effect.
    b2:b0  SEL[2:0] - Output Signal Select. - Select as STVA, STVB, STHA, STHB or DE */
    GLCDC.TCONSTHA2.BIT.INV = (uint32_t)polarity; /* Hsync(STHA) -> Invert or Not Invert */

    /* Hsync beginning position */
    GLCDC.TCONSTHA1.BIT.HS = 0;    /* No delay */
    GLCDC.TCONSTHA2.BIT.HSSEL = 0; /* Select input Hsync as reference */

    /* HSync Width Setting */
    GLCDC.TCONSTHA1.BIT.HW = p_timing->sync_width & TCON_STHx1_HW_MASK;

} /* End of function r_glcdc_hsync_set () */


/*******************************************************************************
 * Outline      : Vertical signal setting
 * Function Name: r_glcdc_vsync_set
 * Description  : Vertical synchronization signal (VS) output setting
 * Arguments    : tcon -
 *                  Tcon pin select.
 *                p_timing -
 *                  Pointer of vsync signal timing parameter.
 *                polarity -
 *                  Polarity select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
static void r_glcdc_vsync_set(glcdc_tcon_pin_t tcon, glcdc_timing_t const * const p_timing, glcdc_signal_polarity_t polarity)
{

    switch (tcon)
    {
        case GLCDC_TCON_PIN_0:
            GLCDC.TCONSTVA2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS; /* Vsync(STVA) -> TCON0 */
        break;
        case GLCDC_TCON_PIN_2:
            GLCDC.TCONSTHA2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS; /* Vsync(STVA) -> TCON2 */
        break;
        case GLCDC_TCON_PIN_3:
            GLCDC.TCONSTHB2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS; /* Vsync(STVA) -> TCON3 */
        break;
        case GLCDC_TCON_PIN_1: /* Intentionally go though to the default case */
        default:
            GLCDC.TCONSTVB2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_STVA_VS; /* Vsync(STVA) -> TCON1 */
        break;
    }

    GLCDC.TCONSTVA2.BIT.INV = (uint32_t)polarity; /* Vsync(STVA) -> Invert or Vsync(STVA) -> Not Invert */

    /* Vsync beginning position */
    GLCDC.TCONSTVA1.BIT.VS = 0;      /* No delay. */

    /* VSync Width Setting */
    GLCDC.TCONSTVA1.BIT.VW = p_timing->sync_width & TCON_STVx1_VW_MASK;

} /* End of function r_glcdc_vsync_set () */


/*******************************************************************************
 * Outline      : Data enable(DE) signal setting
 * Function Name: r_glcdc_data_enable_set
 * Description  : Data enable signal (DE) output setting.
 * Arguments    : tcon -
 *                  Tcon pin select.
 *                p_vtiming -
 *                  Pointer of vsync signal timing parameter.
 *                p_htiming -
 *                  Pointer of hsync signal timing parameter.
 *                polarity -
 *                  Polarity select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
static void r_glcdc_data_enable_set(glcdc_tcon_pin_t tcon, glcdc_timing_t const * const p_vtiming,
                                    glcdc_timing_t const * const p_htiming, glcdc_signal_polarity_t polarity)
{

    switch (tcon)
    {
        case GLCDC_TCON_PIN_0:
            GLCDC.TCONSTVA2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE; /* DE -> TCON0 */
        break;
        case GLCDC_TCON_PIN_1:
            GLCDC.TCONSTVB2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE; /* DE -> TCON1 */
        break;
        case GLCDC_TCON_PIN_3:
            GLCDC.TCONSTHB2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE; /* DE -> TCON3 */
        break;
        case GLCDC_TCON_PIN_2: /* Intentionally go though to the default case */
        default:
            GLCDC.TCONSTHA2.BIT.SEL = (uint32_t)GLCDC_TCON_SIGNAL_SELECT_DE; /* DE -> TCON2 */
        break;
    }

    GLCDC.TCONDE.BIT.INV = (uint32_t)polarity; /* DE -> Invert or Not Invert */

    /* Set data enable timing */
    GLCDC.TCONSTHB1.BIT.HS = (p_htiming->back_porch + p_htiming->sync_width) & TCON_STHx1_HS_MASK;
    GLCDC.TCONSTHB1.BIT.HW = p_htiming->display_cyc & TCON_STHx1_HW_MASK;
    GLCDC.TCONSTHB2.BIT.HSSEL = 0; /* Select input Hsync as reference */
    GLCDC.TCONSTVB1.BIT.VS = (p_vtiming->back_porch + p_vtiming->sync_width) & TCON_STVx1_VS_MASK;
    GLCDC.TCONSTVB1.BIT.VW = p_vtiming->display_cyc & TCON_STVx1_VW_MASK;

} /* End of function r_glcdc_data_enable_set () */


/*******************************************************************************
 * Outline      : Background screen setting
 * Function Name: r_glcdc_background_screen_set
 * Description  : Background screen setting.
 * Arguments    : p_cfg -
 *                  Pointer of background setting parameter.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_background_screen_set(glcdc_cfg_t const * const p_cfg)
{
    uint32_t hsync_total_cyc;
    uint32_t vsync_total_cyc;

    hsync_total_cyc = (((p_cfg->output.htiming.front_porch + p_cfg->output.htiming.sync_width)
            + p_cfg->output.htiming.display_cyc) + p_cfg->output.htiming.back_porch);
    vsync_total_cyc = (((p_cfg->output.vtiming.front_porch + p_cfg->output.vtiming.sync_width)
            + p_cfg->output.vtiming.display_cyc) + p_cfg->output.vtiming.back_porch);


    /* ---- Set number of total cycle for a line including Sync & Back poach, Front poach ---- */
    /* BGPERI - Free-Running Period Register
    b31:b27  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b26:b16  FV[10:0] - Vertical Synchronization Signal Period Setting.
    b15:b11  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b10:b0   FH[10:0] - Horizontal Synchronization Signal Period Setting. */
    GLCDC.BGPERI.BIT.FH = (hsync_total_cyc - 1) & BG_PERI_FH_MASK;
    GLCDC.BGPERI.BIT.FV = (vsync_total_cyc - 1) & BG_PERI_FV_MASK;

    /* BGSYNC - Synchronization Position Register
    b31:b20 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b19:b16 VP[3:0]  - Vertical Synchronization Assertion Position Setting.
    b15:b4  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b3:b0   HP[3:0]  - Horizontal Synchronization Signal Assertion Position Setting. */
    GLCDC.BGSYNC.BIT.HP = (p_cfg->output.htiming.front_porch - BG_PLANE_H_CYC_MARGIN_MIN) & BG_SYNC_HP_MASK;
    GLCDC.BGSYNC.BIT.VP = (p_cfg->output.vtiming.front_porch - BG_PLANE_V_CYC_MARGIN_MIN) & BG_SYNC_VP_MASK;


    /* ---- Set the start position of Background screen ---- */
    /* BGHSIZE - Horizontal Size Register
    b31:b27  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b26:b16  HP[10:0] - Horizontal Active Pixel Start Position Setting.
    b15:b11  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b10:b0   HW[10:0] - Horizontal Active Pixel Width Setting. */
    GLCDC.BGHSIZE.BIT.HP = (uint16_t) ((p_cfg->output.htiming.front_porch - BG_PLANE_H_CYC_MARGIN_MIN)
            + p_cfg->output.htiming.sync_width + p_cfg->output.htiming.back_porch) & BG_HSIZE_HP_MASK;

    /* BGVSIZE - Vertical Size Register
    b31:b27  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b26:b16  VP[10:0] - Vertical Active Pixel Start Position Setting.
    b15:b11  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b10:b0   VW[10:0] - Vertical Active Pixel Width Setting. */
    GLCDC.BGVSIZE.BIT.VP = (uint16_t) ((p_cfg->output.vtiming.front_porch - BG_PLANE_V_CYC_MARGIN_MIN)
            + p_cfg->output.vtiming.sync_width + p_cfg->output.vtiming.back_porch) & BG_VSIZE_VP_MASK;

    /* ---- Set the width of Background screen ---- */
    /* BGHSIZE - Horizontal Size Register
    b10:b0   HW[10:0] - Horizontal Active Pixel Width Setting. */
    GLCDC.BGHSIZE.BIT.HW = p_cfg->output.htiming.display_cyc & BG_HSIZE_HW_MASK;

    /* BGVSIZE - Vertical Size Register
    b10:b0   VW[10:0] - Vertical Active Pixel Width Setting. */
    GLCDC.BGVSIZE.BIT.VW = p_cfg->output.vtiming.display_cyc & BG_VSIZE_VW_MASK;

    /* ---- Set the Background color ---- */
    /* BGCOLOR - Background Color Register
    b31:b24  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b23:b16  R[7:0] - Background Color R Value Setting.
    b15:b8   G[7:0] - Background Color G Value Setting.
    b7:b0    B[7:0] - Background Color B Value Setting. */
    GLCDC.BGCOLOR.BIT.R = p_cfg->output.bg_color.byte.r;
    GLCDC.BGCOLOR.BIT.G = p_cfg->output.bg_color.byte.g;
    GLCDC.BGCOLOR.BIT.B = p_cfg->output.bg_color.byte.b;

} /* End of function r_glcdc_background_screen_set () */

/*******************************************************************************
 * Outline      : GLCDC graphics planes blending setting
 * Function Name: r_glcdc_blend_condition_set
 * Description  : Blending setting.
 * Arguments    : p_blend -
 *                  Pointer of layer setting parameter.
 *                frame -
 *                  Graphic plane select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_blend_condition_set(glcdc_blend_t const * const p_blend, glcdc_frame_layer_t frame)
{

    /* if enable graphics data read from memory */
    if (false == g_ctrl_blk.graphics_read_enable[frame])
    {
        /* GRnAB1 - Graphic n Alpha Blending Control Register 1
        b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current graphics with lower-layer graphics */
        gp_gr[frame]->grxab1.bit.dispsel = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT & GRn_AB1_DISPSEL_MASK; /* Set layer transparent */

        return;
    }


    switch(p_blend->blend_control)
    {
        case GLCDC_BLEND_CONTROL_NONE:

            /* GRnAB1 - Graphic n Alpha Blending Control Register 1
            b31:b13 Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b12     ARCON     - Alpha Blending Control. - Per-pixel alpha blending.
            b11:b9  Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b8      ARCDISPON - Rectangular Alpha Blending Area Frame Display Control.
                              - Area Frame is displayed or not displayed.
            b7:b5   Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b4      GRCDISPON - Graphics Area Frame Display Control.
                              - Area Frame is displayed or not displayed.
            b3:b2   Reserved  - These bits are read as 0. Writing to these bits have no effect.
            b1:b0   DISPSEL[1:0] - Display Screen Control. - Displays the background, lower-layer,
                                   current graphics or blend graphics with lower-layer */
            gp_gr[frame]->grxab1.bit.arcon = 0;

            if (true == p_blend->visible)
            {
                /* GRnAB1 - Graphic n Alpha Blending Control Register 1
                 b1:b0   DISPSEL[1:0] - Display Screen Control. - Displays current graphics */
                gp_gr[frame]->grxab1.bit.dispsel = (uint32_t)GLCDC_PLANE_BLEND_NON_TRANSPARENT & GRn_AB1_DISPSEL_MASK;
            }
            else
            {
                /* GRnAB1 - Graphic n Alpha Blending Control Register 1
                 b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current graphics with lower-layer graphics */
                gp_gr[frame]->grxab1.bit.dispsel = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT & GRn_AB1_DISPSEL_MASK; /* Set layer transparent */
            }


        break;
        case GLCDC_BLEND_CONTROL_FADEIN:
        case GLCDC_BLEND_CONTROL_FADEOUT:
        case GLCDC_BLEND_CONTROL_FIXED:

            /* ---- Set the start position of the rectangle area in the graphics layers ---- */
            /* GRnAB5 - Graphic n Alpha Blending Control Register 5
            b31:b27  Reserved    - These bits are read as 0. Writing to these bits have no effect.
            b26:b16  ARCHS[10:0] - Rectangular Alpha Blending Area Horizontal Start Position Setting.
            b15:b11  Reserved    - These bits are read as 0. Writing to these bits have no effect.
            b10:b0   ARCHW[10:0] - Rectangular Alpha Blending Area Horizontal Width Setting. */
            gp_gr[frame]->grxab5.bit.archs = ((uint32_t) (g_ctrl_blk.active_start_pos.x
                    + p_blend->start_coordinate.x))& GRn_AB5_ARCHS_MASK;

            /* GRnAB4 - Graphic n Alpha Blending Control Register 4
            b31:b27  Reserved    - These bits are read as 0. Writing to these bits have no effect.
            b26:b16  ARCVS[10:0] - Rectangular Alpha Blending Area Vertical Start Position Setting.
            b15:b11  Reserved    - These bits are read as 0. Writing to these bits have no effect.
            b10:b0   ARCVW[10:0] - Rectangular Alpha Blending Area Vertical Width Setting. */
            gp_gr[frame]->grxab4.bit.arcvs = ((uint32_t) (g_ctrl_blk.active_start_pos.y
                    + p_blend->start_coordinate.y))& GRn_AB4_ARCVS_MASK;

            /* ---- Set the width of the graphics layers ---- */
            /* GRnAB5 - Graphic n Alpha Blending Control Register 5
            b10:b0   ARCHW[10:0] - Rectangular Alpha Blending Area Horizontal Width Setting. */
            gp_gr[frame]->grxab5.bit.archw = (p_blend->end_coordinate.x - p_blend->start_coordinate.x)
                    & GRn_AB5_ARCHW_MASK;

            /* GRnAB4 - Graphic n Alpha Blending Control Register 4
            b10:b0   ARCVW[10:0] - Rectangular Alpha Blending Area Vertical Width Setting. */
            gp_gr[frame]->grxab4.bit.arcvw = (p_blend->end_coordinate.y - p_blend->start_coordinate.y)
                    & GRn_AB4_ARCVW_MASK;

            /*---- Enable rectangular alpha blending ---- */
            /* GRnAB1 - Graphic n Alpha Blending Control Register 1
            b12     ARCON     - Alpha Blending Control. - Set rectangular alpha blending. */
            gp_gr[frame]->grxab1.bit.arcon = 1;

            /* GRnAB6 - Graphic n Alpha Blending Control Register 6
            b31:b25  Reserved    - These bits are read as 0. Writing to these bits have no effect.
            b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting.
            b15:b8   Reserved    - These bits are read as 0. Writing to these bits have no effect.
            b7:b0    ARCRATE[7:0]- Alpha Blending Updating Rate Setting. Set 1 frame. */
            gp_gr[frame]->grxab6.bit.arcrate = 0x00;

            if (GLCDC_BLEND_CONTROL_FADEIN == p_blend->blend_control)
            {
                /* GRnAB7 - Graphic n Alpha Blending Control Register 7
                b31:b24 Reserved    - These bits are read as 0. Writing to these bits have no effect.
                b23:b16 ARCDEF[7:0] - Initial Alpha Value Setting. - Set is 0.
                b15:b1  Reserved    - These bits are read as 0. Writing to these bits have no effect.
                b0      CKON        - Chroma Key Compositing Control. */
                gp_gr[frame]->grxab7.bit.arcdef = (uint32_t)GLCDC_FADING_CONTROL_INITIAL_ALPHA_MIN & GRn_AB7_ARCDEF_MASK;

                /* GRnAB6 - Graphic n Alpha Blending Control Register 6
                b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting. */
                gp_gr[frame]->grxab6.bit.arccoef = (uint32_t)p_blend->fade_speed & GRn_AB6_ARCCOEF_MASK;

            }
            else if (GLCDC_BLEND_CONTROL_FADEOUT == p_blend->blend_control)
            {
                /* GRnAB7 - Graphic n Alpha Blending Control Register 7
                b23:b16 ARCDEF[7:0] - Initial Alpha Value Setting. - Set is 0. */
                gp_gr[frame]->grxab7.bit.arcdef = (uint32_t)GLCDC_FADING_CONTROL_INITIAL_ALPHA_MAX & GRn_AB7_ARCDEF_MASK;

                /* GRnAB6 - Graphic n Alpha Blending Control Register 6
                b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting. */
                gp_gr[frame]->grxab6.bit.arccoef = ((uint32_t) p_blend->fade_speed | (1 << 8)) & GRn_AB6_ARCCOEF_MASK;

            }
            else
            /* ---- GLCDC_FADE_CONTROL_FIXED ---- */
            {
                /* GRnAB7 - Graphic n Alpha Blending Control Register 7
                b23:b16 ARCDEF[7:0] - Initial Alpha Value Setting. - Set is 0. */
                gp_gr[frame]->grxab7.bit.arcdef = (uint32_t)p_blend->fixed_blend_value & GRn_AB7_ARCDEF_MASK;

                /* GRnAB6 - Graphic n Alpha Blending Control Register 6
                b24:b16  ARCCOEF[8:0]- Alpha Coefficient Setting. - Set is 0 */
                gp_gr[frame]->grxab6.bit.arccoef = 0x000;
            }

            /* GRnAB1 - Graphic n Alpha Blending Control Register 1
            b8      ARCDISPON - Rectangular Alpha Blending Area Frame Display Control.
                              - Area Frame is displayed or not displayed. */
            if (true == p_blend->frame_edge)
            {
                /* Set the frame of the rectangular alpha blending area to displayed */
                gp_gr[frame]->grxab1.bit.arcdispon = 1;
            }
            else
            {
                /* Set the frame of the rectangular alpha blending area to not displayed */
                gp_gr[frame]->grxab1.bit.arcdispon = 0;
            }

            /* GRnAB1 - Graphic n Alpha Blending Control Register 1
             b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current graphics with lower-layer graphics */
            gp_gr[frame]->grxab1.bit.dispsel = (uint32_t)GLCDC_PLANE_BLEND_ON_LOWER_LAYER & GRn_AB1_DISPSEL_MASK;


        break;
        case GLCDC_BLEND_CONTROL_PIXEL:
        default:

            /* GRnAB1 - Graphic n Alpha Blending Control Register 1
            b12     ARCON     - Alpha Blending Control. - Per-pixel alpha blending. */
            gp_gr[frame]->grxab1.bit.arcon = 0;

            if (true == p_blend->visible)
            {
                /* GRnAB1 - Graphic n Alpha Blending Control Register 1
                 b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current graphics with lower-layer graphics */
                gp_gr[frame]->grxab1.bit.dispsel = (uint32_t)GLCDC_PLANE_BLEND_ON_LOWER_LAYER & GRn_AB1_DISPSEL_MASK;
            }
            else
            {
                /* GRnAB1 - Graphic n Alpha Blending Control Register 1
                 b1:b0   DISPSEL[1:0] - Display Screen Control. - Blended display of current graphics with lower-layer graphics */
                gp_gr[frame]->grxab1.bit.dispsel = (uint32_t)GLCDC_PLANE_BLEND_TRANSPARENT & GRn_AB1_DISPSEL_MASK; /* Set layer transparent */
            }

        break;
    }

} /* End of function r_glcdc_blend_condition_set() */


/*******************************************************************************
 * Outline      : Graphics layer register settings
 * Function Name: r_glcdc_graphics_layer_set
 * Description  : Graphic 1, graphic 2 setting.
 * Arguments    : p_input -
 *                  Pointer of input setting parameter.
 *                frame -
 *                  Graphic plane select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_graphics_layer_set(glcdc_input_cfg_t const * const p_input, glcdc_frame_layer_t frame)
{
    uint32_t line_byte_num;
    uint32_t line_trans_num;
    uint32_t bit_size = r_glcdc_get_bit_size (p_input->format);

    /* If enable graphics data read from memory */
    if (false == g_ctrl_blk.graphics_read_enable[frame])
    {
        return;
    }

    r_glcdc_gr_plane_format_set (p_input->format, frame);

    /* ---- Set the base address of graphics plane ---- */
    /* GRnFLM2 - Graphic n Frame Buffer Control Register 2 */
    gp_gr[frame]->grxflm2 = (uint32_t) p_input->p_base;

    /* ---- Set the background color on graphics plane ---- */
    /* GRnBASE - Graphic n Background Color Control Register
    b31:b24  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b23:b16  G[7:0] - Background Color G Value Setting.
    b15:b8   B[7:0] - Background Color B Value Setting.
    b7:b0    R[7:0] - Background Color R Value Setting. */
    gp_gr[frame]->grxbase.bit.r = p_input->bg_color.byte.r;
    gp_gr[frame]->grxbase.bit.g = p_input->bg_color.byte.g;
    gp_gr[frame]->grxbase.bit.b = p_input->bg_color.byte.b;

    /* ---- Set the number of data transfer times per line, 64 bytes are transferred in each transfer ---- */
    /* GRnFLM5 - Graphic n Frame Buffer Control Register 5
    b31:b27 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b26:b16 LNNUM[10:0] - Single Frame Line Count Setting.
    b15:b0  DATANUM[15:0] - Single Line Data Transfer Count Setting */
    
    /* Convert to byte size of Single line data transfer, round up fractions below the decimal point */
    line_byte_num = ((bit_size * p_input->hsize) / 8);
    if (0 != ((bit_size * p_input->hsize) % 8))
    {
        line_byte_num += 1;
    }
    
    /* Convert to Single line data transfer count, round up fractions below the decimal point */
    line_trans_num = (line_byte_num >> 6);
    if (0 != (line_byte_num & GLCDC_ADDRESS_ALIGNMENT_64B))
    {
        line_trans_num += 1;
    }
    
    gp_gr[frame]->grxflm5.bit.datanum = (line_trans_num - 1) & GRn_FLM5_DATANUM_MASK;

    /* ---- Set the line offset address for accessing the graphics data ---- */
    /* GRnFLM5 - Graphic n Frame Buffer Control Register 5
    b26:b16 LNNUM[10:0] - Single Frame Line Count Setting. */
    gp_gr[frame]->grxflm5.bit.lnnum = ((uint32_t) (p_input->vsize - 1)) & GRn_FLM5_LNNUM_MASK;

    /* ---- Set the line offset address for accessing the graphics data on graphics plane ---- */
    /* GRnFLM3 - Graphic n Frame Buffer Control Register 3
    b31:b16 LNOFF[15:0] - Macro Line Offset Setting. - Set the offset value from the end address of the line
                              on the frame buffer (macro line) to the start address of the next macro line. */
    gp_gr[frame]->grxflm3.bit.lnoff = (uint32_t) p_input->offset & GRn_FLM3_LNOFF_MASK;

    /* GRnAB2 - Graphic n Alpha Blending Control Register 2
    b10:b0  GRCVW[10:0] - Graphics Area Vertical Width Setting. */
    gp_gr[frame]->grxab2.bit.grcvw = p_input->vsize & GRn_AB2_GRCVW_MASK;

    /* GRnAB2 - Graphic n Alpha Blending Control Register 2
    b26:b16 GRCVS[10:0] - Graphics Area Vertical Start Position Setting. */
    gp_gr[frame]->grxab2.bit.grcvs = ((uint32_t) (g_ctrl_blk.active_start_pos.y
            + p_input->coordinate.y)) & GRn_AB2_GRCVS_MASK;

    /* ---- Set the width of the graphics layers ---- */
    /* GRnAB3 - Graphic n Alpha Blending Control Register 3
    b10:b0  GRCHW[10:0] - Graphics Area Horizontal Width Setting. */
    gp_gr[frame]->grxab3.bit.grchw = p_input->hsize & GRn_AB3_GRCHW_MASK;

    /* ---- Set the start position of the graphics layers ---- */
    /* GRnAB3 - Graphic n Alpha Blending Control Register 3
    b31:b27 Reserved    - These bits are read as 0. Writing to these bits have no effect.
    b26:b16 GRCHS[10:0] - Graphics Area Horizontal Start Position Setting.
    b15:b11 Reserved    - These bits are read as 0. Writing to these bits have no effect.
    b10:b0  GRCHW[10:0] - Graphics Area Horizontal Width Setting. */
    gp_gr[frame]->grxab3.bit.grchs = ((uint32_t) (g_ctrl_blk.active_start_pos.x
            + p_input->coordinate.x)) & GRn_AB3_GRCHS_MASK;

    /* GRnAB1 - Graphic n Alpha Blending Control Register 1
    b4      GRCDISPON - Graphics Area Frame Display Control.
                                  - Area Frame is displayed or not displayed. */
    if (true == p_input->frame_edge)
    {
        /* Set the frame of the graphics area to displayed */
        gp_gr[frame]->grxab1.bit.grcdispon = 1;
    }
    else
    {
        /* Set the frame of the graphics area to not displayed */
        gp_gr[frame]->grxab1.bit.grcdispon = 0;
    }

} /* End of function r_glcdc_graphics_layer_set() */


/*******************************************************************************
 * Outline      : Chroma key setting
 * Function Name: r_glcdc_graphics_chromakey_set
 * Description  : Chroma key setting.
 * Arguments    : p_chromakey -
 *                  Pointer of chroma key setting parameter.
 *                frame -
 *                  Graphic plane select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_graphics_chromakey_set(glcdc_chromakey_t const * const p_chromakey, glcdc_frame_layer_t frame)
{

    /* if enable graphics data read from memory */
    if (false == g_ctrl_blk.graphics_read_enable[frame])
    {
        return;
    }

    if (true == p_chromakey->enable)
    {
        /* ---- Chroma key enable ---- */
        /* GRnAB7 - Graphic n Alpha Blending Control Register 7
         b0 CKON - Chroma Key Compositing Control. - Enable RGB reference chroma key compositing. */
        gp_gr[frame]->grxab7.bit.ckon = 1;

        /* ---- Before ---- */
        /* GRnAB8 - Graphic n Alpha Blending Control Register 8
        b31:b24  Reserved - These bits are read as 0. Writing to these bits have no effect.
        b23:b16  CKKG[7:0] - Chroma Key Compositing Target G Value Setting.
        b15:b8   CKKB[7:0] - Chroma Key Compositing Target B Value Setting.
        b7:b0    CKKR[7:0] - Chroma Key Compositing Target R Value Setting. */
        gp_gr[frame]->grxab8.bit.ckkr = p_chromakey->before.byte.r;
        gp_gr[frame]->grxab8.bit.ckkg = p_chromakey->before.byte.g;
        gp_gr[frame]->grxab8.bit.ckkb = p_chromakey->before.byte.b;

        /* ---- After ---- */
        /* GRnAB9 - Graphic n Alpha Blending Control Register 9
        b31:b24  CKA[7:0] - Chroma Key Compositing Replacing A Value Setting.
        b23:b16  CKG[7:0] - Chroma Key Compositing Replacing G Value Setting.
        b15:b8   CKB[7:0] - Chroma Key Compositing Replacing B Value Setting.
        b7:b0    CKR[7:0] - Chroma Key Compositing Replacing R Value Setting. */
        gp_gr[frame]->grxab9.bit.cka = p_chromakey->after.byte.a;
        gp_gr[frame]->grxab9.bit.ckr = p_chromakey->after.byte.r;
        gp_gr[frame]->grxab9.bit.ckg = p_chromakey->after.byte.g;
        gp_gr[frame]->grxab9.bit.ckb = p_chromakey->after.byte.b;

    }
    else
    {
        /* ---- Chroma key disable ---- */
        /* GRnAB7 - Graphic n Alpha Blending Control Register 7
        b0 CKON - Chroma Key Compositing Control. - Disable RGB reference chroma key compositing. */
        gp_gr[frame]->grxab7.bit.ckon = 0;

    }

} /* End of function r_glcdc_graphics_chromakey_set() */


/*******************************************************************************
 * Outline      : Output control block register settings
 * Function Name: r_glcdc_output_block_set
 * Description  : Panel output setting
 * Arguments    : p_cfg -
 *                  Pointer of output format setting parameter.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_output_block_set(glcdc_cfg_t const * const p_cfg)
{
    /* OUTSET - Output Interface Register
    b31:b29 Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b28     ENDIANON   - Bit Endian Control. - Little endian or big endian.
    b27:b25 Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b24     SWAPON     - Pixel Order Control. - R-G-B order or B-G-R order.
    b23:b14 Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b13:b12 FORMAT[1:0]- Output Data Format Select. - RGB(888), RGB(666), RGB(565) or Serial RGB.
    b11:b10 Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b9      FRQSEL[1:0]- Pixel Clock Division Control. - No division (parallel RGB) or Divide-by-4 (serial RGB).
    b8      Reserved   - This bit is read as 0. The write value should be 0.
    b7:b5   Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b4      DIRSEL     - Serial RGB Scan Direction Select. - Forward scan or Reverse scan.
    b3:b2   Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b1:b0   PHASE[1:0] - Serial RGB Data Output Delay Control. - 0 to 3 cycles */

    /* Selects big or little endian for output data */
    GLCDC.OUTSET.BIT.ENDIANON = (uint32_t)p_cfg->output.endian;

    /* Selects the output byte order swapping */
    GLCDC.OUTSET.BIT.SWAPON = (uint32_t)p_cfg->output.color_order;


    /* Selects the output format */
    switch (p_cfg->output.format)
    {
        case GLCDC_OUT_FORMAT_8BITS_SERIAL: /* In case of serial RGB, set as RGB888 format */
            GLCDC.OUTSET.BIT.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_8BITS_SERIAL;
            GLCDC.OUTSET.BIT.PHASE = (uint32_t)p_cfg->output.serial_output_delay;
            GLCDC.OUTSET.BIT.DIRSEL = (uint32_t)p_cfg->output.serial_scan_direction;
            GLCDC.PANELDTHA.BIT.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB888;
        break;
        case GLCDC_OUT_FORMAT_16BITS_RGB565:
            GLCDC.OUTSET.BIT.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_16BITS_RGB565;
            GLCDC.PANELDTHA.BIT.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB565;
        break;
        case GLCDC_OUT_FORMAT_18BITS_RGB666:
            GLCDC.OUTSET.BIT.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_18BITS_RGB666;
            GLCDC.PANELDTHA.BIT.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB666;
        break;
        case GLCDC_OUT_FORMAT_24BITS_RGB888:
        default:
            GLCDC.OUTSET.BIT.FORMAT = (uint32_t)GLCDC_OUT_FORMAT_24BITS_RGB888;
            GLCDC.PANELDTHA.BIT.FORM = (uint32_t)GLCDC_DITHERING_OUTPUT_FORMAT_RGB888;
        break;
    }

    /* Sets the pixel clock (the GLCD internal signal) frequency in case that the output format is 8-bit serial RGB */
    if (GLCDC_OUT_FORMAT_8BITS_SERIAL == p_cfg->output.format)
    {
        GLCDC.OUTSET.BIT.FRQSEL = OUT_SET_FRQSEL_QUATER_DIVISION;
    }
    else
    {
        GLCDC.OUTSET.BIT.FRQSEL = OUT_SET_FRQSEL_NO_DIVISION;
    }

    /* Sets the Brightness/contrast and Gamma Correction processing order */
    /* CLKPHASE - Output Phase Control Register
    b12     FRONTGAM  - Correction Sequence Control. */
    GLCDC.CLKPHASE.BIT.FRONTGAM = (uint32_t)p_cfg->output.correction_proc_order;


    /* PANELDTHA - Panel Dither Control Register
    b31:b22 Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b21:b20 SEL[1:0]  - Rounding Mode Setting. - Truncate, Round-off, 2*2 pattern dither.
    b19:b18 Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b17:b16 FORM[1:0] - Output Format Select. - RGB(888), RGB(666), RGB(565).
    b15:b14 Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b13:b12 PA[1:0]   - Dither Pattern Value A Setting.
    b11:b10 Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b9:b8   PB[1:0]   - Dither Pattern Value B Setting.
    b7:b6   Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b5:b4   PC[1:0]   - Dither Pattern Value C Setting.
    b3:b2   Reserved  - These bits are read as 0. Writing to these bits have no effect.
    b1:b0   PD[1:0]   - Dither Pattern Value D Setting. */

    /* ---- Set the dithering mode ---- */
    if (true == p_cfg->output.dithering.dithering_on)
    {
        if (GLCDC_DITHERING_MODE_2X2PATTERN == p_cfg->output.dithering.dithering_mode)
        {
            GLCDC.PANELDTHA.BIT.PA = (uint32_t)p_cfg->output.dithering.dithering_pattern_a;
            GLCDC.PANELDTHA.BIT.PB = (uint32_t)p_cfg->output.dithering.dithering_pattern_b;
            GLCDC.PANELDTHA.BIT.PC = (uint32_t)p_cfg->output.dithering.dithering_pattern_c;
            GLCDC.PANELDTHA.BIT.PD = (uint32_t)p_cfg->output.dithering.dithering_pattern_d;
        }

        GLCDC.PANELDTHA.BIT.SEL = (uint32_t)p_cfg->output.dithering.dithering_mode;

    }
    else
    {
        GLCDC.PANELDTHA.BIT.SEL = (uint32_t)GLCDC_DITHERING_MODE_TRUNCATE;
    }

} /* End of function r_glcdc_output_block_set() */


/*******************************************************************************
 * Outline      : Brightness register settings
 * Function Name: r_glcdc_brightness_correction
 * Description  : Brightness setting.
 * Arguments    : p_brightness -
 *                  Pointer of brightness setting parameter.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_brightness_correction(glcdc_brightness_t const * const p_brightness)
{

    if (true == p_brightness->enable)
    {
        /* ---- Sets brightness correction register for each color in a pixel. ---- */
        /* BRIGHT1 - Brightness Adjustment Register 1
        b31:b10 Reserved  - These bits are read as 0. Writing to these bits have no effect.
        b9:b0   BRTG[9:0] - G Channel Brightness Adjustment Value Setting */
        GLCDC.BRIGHT1.BIT.BRTG = p_brightness->g & OUT_BRIGHT1_BRTG_MASK;

        /* BRIGHT2 - Brightness Adjustment Register 2
        b31:b26 Reserved  - These bits are read as 0. Writing to these bits have no effect.
        b25:b16 BRTB[9:0] - B Channel Brightness Adjustment Value Setting.
        b15:b10 Reserved  - These bits are read as 0. Writing to these bits have no effect.
        b9:b0   BRTR[9:0] - R Channel Brightness Adjustment Value Setting */
        GLCDC.BRIGHT2.BIT.BRTB = p_brightness->b & OUT_BRIGHT2_BRTB_MASK;
        GLCDC.BRIGHT2.BIT.BRTR = p_brightness->r & OUT_BRIGHT2_BRTR_MASK;
    }
    else
    {
        /* ---- If brightness setting in configuration is 'off', apply default value ---- */
        /* BRIGHT1 - Brightness Adjustment Register 1
        b9:b0   BRTG[9:0] - G Channel Brightness Adjustment Value Setting */
        GLCDC.BRIGHT1.BIT.BRTG = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT1_BRTG_MASK;

        /* BRIGHT2 - Brightness Adjustment Register 2
        b25:b16 BRTB[9:0] - B Channel Brightness Adjustment Value Setting.
        b9:b0   BRTR[9:0] - R Channel Brightness Adjustment Value Setting */
        GLCDC.BRIGHT2.BIT.BRTB = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT2_BRTB_MASK;
        GLCDC.BRIGHT2.BIT.BRTR = GLCDC_BRIGHTNESS_DEFAULT & OUT_BRIGHT2_BRTR_MASK;
    }

} /* End of function r_glcdc_brightness_correction() */


/*******************************************************************************
 * Outline      : Contrast register settings
 * Function Name: r_glcdc_contrast_correction
 * Description  : Contrast settings.
 * Arguments    : p_contrast -
 *                  Pointer of contrast setting parameter.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_contrast_correction(glcdc_contrast_t const * const p_contrast)
{

    if (true == p_contrast->enable)
    {
        /* ---- Sets the contrast correction register for each color in a pixel. ---- */
        /* CONTRAST - Contrast Adjustment Register
        b31:b24 Reserved  - These bits are read as 0. Writing to these bits have no effect.
        b23:b16 CONTG[7:0]- G Channel Contrast Adjustment Value Setting.
        b15:b8  CONTB[7:0]- B Channel Contrast Adjustment Value Setting.
        b7:b0   CONTR[7:0]- R Channel Contrast Adjustment Value Setting. */
        GLCDC.CONTRAST.BIT.CONTG = p_contrast->g & OUT_CONTRAST_CONTG_MASK;
        GLCDC.CONTRAST.BIT.CONTB = p_contrast->b & OUT_CONTRAST_CONTB_MASK;
        GLCDC.CONTRAST.BIT.CONTR = p_contrast->r & OUT_CONTRAST_CONTR_MASK;
    }
    else
    {
        /* ---- If the contrast setting in the configuration is set to 'off', apply default value ---- */
        /* CONTRAST - Contrast Adjustment Register
        b23:b16 CONTG[7:0]- G Channel Contrast Adjustment Value Setting.
        b15:b8  CONTB[7:0]- B Channel Contrast Adjustment Value Setting.
        b7:b0   CONTR[7:0]- R Channel Contrast Adjustment Value Setting. */
        GLCDC.CONTRAST.BIT.CONTG = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTG_MASK;
        GLCDC.CONTRAST.BIT.CONTB = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTB_MASK;
        GLCDC.CONTRAST.BIT.CONTR = GLCDC_CONTRAST_DEFAULT & OUT_CONTRAST_CONTR_MASK;
    }

} /* End of function r_glcdc_contrast_correction() */


/*******************************************************************************
 * Outline      : Gamma register settings
 * Function Name: r_glcdc_gamma_correction
 * Description  : Gamma value setting.
 * Arguments    : p_gamma -
 *                  Pointer of gamma setting parameter.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_gamma_correction(glcdc_gamma_correction_t const * const p_gamma)
{
    volatile uint8_t i;
    uint32_t *p_lut_table;

    if (true == p_gamma->enable)
    {
        /* ---- Gamma correction enable and set gamma setting ---- */
        /* GAMSW - Gamma Correction Block Function Switch Register
        b31:b1 Reserved - These bits are read as 0. Writing to these bits have no effect.
        b0     GAMON    - Gamma Correction Enable. - Enables gamma correction. */
        GLCDC.GAMSW.BIT.GAMON = 1;

        /* Green */
        p_lut_table = (uint32_t *) (&GLCDC.GAMGLUT1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2)
        {
            /* GAMGLUTx - Gamma Correction G Table Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_g->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
                    | ((uint32_t)p_gamma->p_g->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
            p_lut_table++;
        }

        p_lut_table = (uint32_t *) (&GLCDC.GAMGAREA1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3)
        {
            /* GAMGAREAx - Gamma Correction G Area Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_g->threshold[i] & GAMX_AREAX_MASK) << 20)
                    | (((uint32_t)p_gamma->p_g->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
                    | ((uint32_t)p_gamma->p_g->threshold[i + 2] & GAMX_AREAX_MASK));
            p_lut_table++;
        }


        /* Blue */
        p_lut_table = (uint32_t *)(&GLCDC.GAMBLUT1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2)
        {
            /* GAMBLUTx - Gamma Correction B Table Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_b->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
                    | ((uint32_t)p_gamma->p_b->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
            p_lut_table++;
        }

        p_lut_table = (uint32_t *) (&GLCDC.GAMBAREA1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3)
        {
            /* GAMBAREAx - Gamma Correction B Area Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_b->threshold[i] & GAMX_AREAX_MASK) << 20)
                    | (((uint32_t)p_gamma->p_b->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
                    | ((uint32_t)p_gamma->p_b->threshold[i + 2] & GAMX_AREAX_MASK));
            p_lut_table++;
        }


        /* Red */
        p_lut_table = (uint32_t *) (&GLCDC.GAMRLUT1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_GAIN_ELEMENT_NUM; i += 2)
        {
            /* GAMRLUTx - Gamma Correction R Table Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_r->gain[i] & GAMX_LUTX_GAIN_MASK) << 16)
                    | ((uint32_t)p_gamma->p_r->gain[i + 1] & GAMX_LUTX_GAIN_MASK));
            p_lut_table++;
        }

        p_lut_table = (uint32_t *) (&GLCDC.GAMRAREA1);
        for (i = 0; i < GLCDC_GAMMA_CURVE_THRESHOLD_ELEMENT_NUM; i += 3)
        {
            /* GAMRAREAx - Gamma Correction R Area Setting Register x */
            *p_lut_table = ((((uint32_t)p_gamma->p_r->threshold[i] & GAMX_AREAX_MASK) << 20)
                    | (((uint32_t)p_gamma->p_r->threshold[i + 1] & GAMX_AREAX_MASK) << 10)
                    | ((uint32_t)p_gamma->p_r->threshold[i + 2] & GAMX_AREAX_MASK));
            p_lut_table++;
        }

    }
    else
    {
        /* ---- Gamma Correction Disable ---- */
        /* GAMSW - Gamma Correction Block Function Switch Register
        b0     GAMON    - Gamma Correction Enable. - Disables gamma correction. */
        GLCDC.GAMSW.BIT.GAMON = 0;
    }

} /* End of function r_glcdc_gamma_correction() */


/*******************************************************************************
 * Outline      : Get the bit size of the specified format
 * Function Name: r_glcdc_get_bit_size
 * Description  : Collecting bit size of graphic data.
 * Arguments    : format -
 *                  Color format (specify glcdc_in_format_t type enumeration value)
 * Return Value : bit_size -
 *                  bit size of color format (1, 4, 8, 16 or 32 bit)
 * Note         : none
 *******************************************************************************/
static uint16_t r_glcdc_get_bit_size(glcdc_in_format_t format)
{
    uint16_t bit_size = 0;

    /* ---- Get bit size and set color format ---- */
    switch (format)
    {
        case GLCDC_IN_FORMAT_32BITS_ARGB8888:         ///< ARGB8888, 32bits
        case GLCDC_IN_FORMAT_32BITS_RGB888:           ///< RGB888,   32bits
            bit_size = 32;
        break;
        case GLCDC_IN_FORMAT_16BITS_RGB565:           ///< RGB565,   16bits
        case GLCDC_IN_FORMAT_16BITS_ARGB1555:         ///< ARGB1555, 16bits
        case GLCDC_IN_FORMAT_16BITS_ARGB4444:         ///< ARGB4444, 16bits
            bit_size = 16;
        break;
        case GLCDC_IN_FORMAT_CLUT8:                   ///< CLUT8
            bit_size = 8;
        break;
        case GLCDC_IN_FORMAT_CLUT4:                   ///< CLUT4
            bit_size = 4;
        break;
        case GLCDC_IN_FORMAT_CLUT1:                   ///< CLUT1
        default:
            bit_size = 1;
        break;
    }

    return bit_size;

} /* End of function r_glcdc_get_bit_size () */


/*******************************************************************************
 * Outline      : Set the color format of graphics plane to the GLCD register.
 * Function Name: r_glcdc_gr_plane_format_set
 * Description  : Input format setting of graphic data
 * Arguments    : format -
 *                  Color format (specify glcdc_in_format_t type enumeration value)
 *                frame -
 *                  Graphic plane select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
static void r_glcdc_gr_plane_format_set(glcdc_in_format_t format, glcdc_frame_layer_t frame)
{
    /* GRnFLM6 - Graphic n Frame Buffer Control Register 6
    b31     Reserved    - This bit is read as 0. The write value should be 0.
    b30:b28 FORMAT[2:0] - Frame Buffer Color Format Setting.
    b27:b0  Reserved    - These bits are read as 0. Writing to these bits have no effect. */
    gp_gr[frame]->grxflm6.bit.format = (uint32_t)format;

} /* End of function r_glcdc_gr_plane_format_set () */


/*******************************************************************************
 * Outline      : Graphic 1 underflow, Graphic 2 underflow, Graphic 2 line detection setting.
 * Function Name: r_glcdc_detect_setting
 * Description  : Graphic 1 underflow, Graphic 2 underflow, Graphic 2 line detection setting.
 * Arguments    : p_detection -
 *                  Pointer to each detection enable/disable select.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_detect_setting(glcdc_detect_cfg_t const * const p_detection)
{
    if (true == p_detection->vpos_detect)
    {
        /* Set Graphic 2 Specified Line Notification Detection to enable */
        GLCDC.DTCTEN.BIT.VPOSDTC = 1;
    }
    else
    {
        /* Set Graphic 2 Specified Line Notification Detection to disable */
        GLCDC.DTCTEN.BIT.VPOSDTC = 0;
    }

    if (true == p_detection->gr1uf_detect)
    {
        /* Set Graphic 1 Underflow Detection to enable */
        GLCDC.DTCTEN.BIT.GR1UFDTC = 1;
    }
    else
    {
        /* Set Graphic 1 Underflow Detection to disable */
        GLCDC.DTCTEN.BIT.GR1UFDTC = 0;
    }

    if (true == p_detection->gr2uf_detect)
    {
        /* Set Graphic 2 Underflow Detection to enable */
        GLCDC.DTCTEN.BIT.GR2UFDTC = 1;
    }
    else
    {
        /* Set Graphic 2 Underflow Detection to disable */
        GLCDC.DTCTEN.BIT.GR2UFDTC = 0;
    }

} /* End of function r_glcdc_detect_setting () */


/*******************************************************************************
 * Outline      : Enables read graphics data.
 * Function Name: r_glcdc_graphics_read_enable
 * Description  : Enables or disables reading of the graphics data.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_graphics_read_enable(void)
{
    if (true == g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_1])
    {
        /* GR1FLMRD - Graphic 1 Frame Buffer Read Control Register
        b31:b1 Reserved   - These bits are read as 0. Writing to these bits have no effect.
        b0     RENB - Frame Buffer Read Enable. - Enable reading of the frame buffer. */
        GLCDC.GR1FLMRD.BIT.RENB = 1;    /* Enable reading. */
    }
    else
    {
        /* GR1FLMRD - Graphic 1 Frame Buffer Read Control Register
        b0     RENB - Frame Buffer Read Enable. - Disable reading of the frame buffer. */
        GLCDC.GR1FLMRD.BIT.RENB = 0;    /* Disable reading. */
    }

    if (true == g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_2])
    {
        /* GR2FLMRD - Graphic 2 Frame Buffer Read Control Register
        b0     RENB - Frame Buffer Read Enable. - Enable reading of the frame buffer. */
        GLCDC.GR2FLMRD.BIT.RENB = 1;    /* Enable reading. */
    }
    else
    {
        /* GR2FLMRD - Graphic 2 Frame Buffer Read Control Register
        b0     RENB - Frame Buffer Read Enable. - Enable reading of the frame buffer. */
        GLCDC.GR2FLMRD.BIT.RENB = 0;    /* Disable reading. */
    }

} /* End of function r_glcdc_graphics_read_enable() */


/*******************************************************************************
 * Outline      : Provides power to the GLCD module.
 * Function Name: r_glcdc_power_on
 * Description  : Module stop cancel of GLCDC.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_power_on(void)
{
    /* ---- Enable protection using PRCR register. ---- */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

    /* Release Module Stop of GLCDC */
    MSTP(GLCDC) = 0;

    /* ---- Disable protection using PRCR register. ---- */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

} /* End of function r_glcdc_power_on() */


/*******************************************************************************
 * Outline      : Removes power from the GLCD module.
 * Function Name: r_glcdc_power_off
 * Description  : Module stop transition of GLCDC.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_power_off(void)
{
    /* ---- Enable protection using PRCR register. ---- */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

    /* Set Module Stop of GLCDC */
    MSTP(GLCDC) = 1;

    /* ---- Disable protection using PRCR register. ---- */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

} /* End of function r_glcdc_power_off() */


/*******************************************************************************
 * Outline      : Negates reset signal to GLCDC hardware.
 * Function Name: r_glcdc_release_software_reset
 * Description  : Software reset release of GLCDC.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_release_software_reset(void)
{
    /* ---- Releases software reset. ---- */
    /* BGEN - Background Generating Block Operation Control Register
    b31:b17 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b16     SWRST    - GLCDC Software Reset Release. - Release GLCDC software reset.
    b15:b9  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b8      VEN      - Register Value Reflection Enable.
    b7:b1   Reserved - These bits are read as 0. Writing to these bits have no effect.
    b0      EN       - Background Generating Block Operation Enable. */
    GLCDC.BGEN.BIT.SWRST = 1;

} /* End of function r_glcdc_release_software_reset() */


/*******************************************************************************
 * Outline      : Asserts reset signal to GLCDC hardware.
 * Function Name: r_glcdc_software_reset
 * Description  : Software reset of GLCDC.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_software_reset(void)
{
    /* ---- Applies software reset. ---- */
    /* BGEN - Background Generating Block Operation Control Register
    b16     SWRST    - GLCDC Software Reset Release. - Release GLCDC software reset. */
    GLCDC.BGEN.BIT.SWRST = 0;

} /* End of function r_glcdc_software_reset() */


/*******************************************************************************
 * Outline      : Update color pallete
 * Function Name: r_glcdc_clut_update
 * Description  : Update color palette and switch an using pallete.
 * Arguments    : p_clut -
 *                   Pointer of setting parameter.
 *                frame -
 *                   Graphic plane select.
 * Return Value : none
 *******************************************************************************/
void r_glcdc_clut_update(glcdc_clut_cfg_t const * const p_clut, glcdc_frame_layer_t frame)
{
    uint32_t * p_base = p_clut->p_base;
    glcdc_clut_plane_t set_clutplane;
    volatile uint32_t i;

    /* If enable graphics data read from memory */
    if (false == g_ctrl_blk.graphics_read_enable[frame])
    {
        return;
    }

    if (true == p_clut->enable)
    {
        if (GLCDC_CLUT_PLANE_1 == r_glcdc_is_clutplane_selected (frame))
        {
            set_clutplane = GLCDC_CLUT_PLANE_0;
        }
        else
        {
            set_clutplane = GLCDC_CLUT_PLANE_1;
        }

        /* Copy the new CLUT data on the source memory to the CLUT SRAM in the GLCD module */
        for (i = p_clut->start; i < (p_clut->start + p_clut->size); i++)
        {
            r_glcdc_clut_set (frame, set_clutplane, i, *p_base++);
        }

        /* Make the GLCD module read the new CLUT table data from the next frame */
        r_glcdc_clutplane_select (frame, set_clutplane);
    }

} /* End of function r_glcdc_clut_update() */


/*******************************************************************************
 * Outline      : Updates data in the entry of CLUT0 or CLUT1.
 * Function Name: r_glcdc_clut_set
 * Description  : Color palette setting.
 * Arguments    : frame -
 *                  Graphic plane select.
 *                clut_plane -
 *                  Color table plane select.
 *                entry -
 *                  Number of CLUT entry
 *                data -
 *                  Data to be updated
 * Return Value : none
 *******************************************************************************/
void r_glcdc_clut_set(glcdc_frame_layer_t frame, glcdc_clut_plane_t clut_plane, uint32_t entry, uint32_t data)
{
    /* GRnCLUTm[k] - Color Look-up Table
    b31:b24 A[7:0] - Color Look-up Table A Value Setting.
    b23:b16 R[7:0] - Color Look-up Table R Value Setting.
    b15:b8  G[7:0] - Color Look-up Table G Value Setting.
    b7:b0   B[7:0] - Color Look-up Table B Value Setting. */
    gp_gr_clut[frame][clut_plane]->grxclut[entry].lsize = data;

} /* End of function r_glcdc_clut_set() */

/*******************************************************************************
 * Outline      : Enables the background screen generation block.
 * Function Name: r_glcdc_bg_operation_enable
 * Description  : Start operation.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_bg_operation_enable(void)
{
    /* ---- Enables background plane operation and internal register value reflection. ---- */
    /* BGEN - Background Generating Block Operation Control Register
    b16     SWRST    - GLCDC Software Reset Release. - Release GLCDC software reset.
    b8      VEN      - Register Value Reflection Enable. - Enable the reflection of the register values.
    b0      EN       - Background Generating Block Operation Enable. - Enable background generating block operation */
    GLCDC.BGEN.LONG = 0x00010101;

} /* End of function r_glcdc_bg_operation_enable() */


/*******************************************************************************
 * Outline      : Disables the background screen generation block.
 * Function Name: r_glcdc_bg_operation_disable
 * Description  : Stop operation.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_bg_operation_disable(void)
{
    /* Disables background plane operation */
    /* BGEN - Background Generating Block Operation Control Register
    b0 EN - Background Generating Block Operation Enable. - Disable background generating block operation */
    GLCDC.BGEN.BIT.EN = 0;

    /* Confirm that operation of the background plane stops. */
    while (1 == GLCDC.BGMON.BIT.EN)
    {
        nop();
    }

} /* End of function r_glcdc_bg_operation_disable() */


/*******************************************************************************
 * Outline      : Checks the register update status for all the control blocks in GLCDC.
 * Function Name: r_glcdc_is_register_reflecting
 * Description  : Checks the register update status for all the control blocks in GLCDC.
 * Arguments    : none
 * Return Value : true -
 *                   Register update for all the control block is underway
 *                false -
 *                   Register update is not underway
 *******************************************************************************/
bool r_glcdc_is_register_reflecting(void)
{
    /* BGEN - Background Generating Block Operation Control Register
    b8      VEN      - Register Value Reflection Enable. */
    return GLCDC.BGEN.BIT.VEN; /* checks status of internal register value reflection. */

} /* End of function r_glcdc_is_register_reflecting() */


/*******************************************************************************
 * Outline      : Enables output control block register update.
 * Function Name: r_glcdc_output_ctrl_update
 * Description  : Enables output control block register update.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_output_ctrl_update(void)
{
    /* OUTVEN - Output Control Block Register Update Control Register
    b8      VEN      - Register Value Reflection Enable. - Enable the reflection of the register values */
    GLCDC.OUTVEN.BIT.VEN = 1;

} /* End of function r_glcdc_output_ctrl_update() */


/*******************************************************************************
 * Outline      : Checks whether output control block register updating is underway or not.
 * Function Name: r_glcdc_is_output_ctrl_updating
 * Description  : Checks whether output control block register updating is underway or not.
 * Arguments    : none
 * Return Value : true -
 *                   Register update for output control block is underway
 *                false -
 *                   Register update is not underway
 *******************************************************************************/
bool r_glcdc_is_output_ctrl_updating(void)
{
    /* OUTVEN - Output Control Block Register Update Control Register
    b0  VEN - Output Control Block Register Value Reflection Enable. */
    return GLCDC.OUTVEN.BIT.VEN; /* checks status of internal register value reflection. */

} /* End of function r_glcdc_is_output_ctrl_updating() */


/*******************************************************************************
 * Outline      : Sets the number for line detection.
 * Function Name: r_glcdc_line_detect_number_set
 * Description  : Sets the number for line detection.
 * Arguments    : line -
 *                  Number for line detection.
 * Return Value : none
 *******************************************************************************/
void r_glcdc_line_detect_number_set(uint32_t line)
{
    /* GR2CLUTINT - Graphic 2 CLUT/Interrupt Control Register
    b31:b17 Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b16     SEL        - CLUT Control. - Select Color Look-up Table.
    b15:b11 Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b10:b0  LINE[10:0] - Detecting Scan line Setting. */
    GLCDC.GR2CLUTINT.BIT.LINE = line & GRn_CLUTINT_LINE_MASK;

} /* End of function r_glcdc_line_detect_number_set() */


/*******************************************************************************
 * Outline      : Checks whether fade in/out progress is underway or not.
 * Function Name: r_glcdc_is_fading
 * Description  : Checks whether fade in progress is underway or not.
 * Arguments    : frame -
 *                  Graphic plane select.
 * Return Value : true -
 *                   fade in progress is underway
 *                false -
 *                   fade in progress is not underway
 *******************************************************************************/
bool r_glcdc_is_fading(glcdc_frame_layer_t frame)
{
    /* GRnMON - Graphic n Status Monitor Register
    b31:b17 Reserved - These bits are read as 0.
    b16     UFST     - Underflow Status Flag.
    b15:b1  Reserved - These bits are read as 0.
    b0      ARCST    - Alpha Blending Status Flag. - Fade-in/fade-out in progress status */
    return gp_gr[frame]->grxmon.bit.arcst;

} /* End of function r_glcdc_is_fading() */


/*******************************************************************************
 * Outline      : Checks whether CLUT plane1 is currently selected or not.
 * Function Name: r_glcdc_is_clutplane_selected
 * Description  : Checks whether CLUT plane1 is currently selected or not.
 * Arguments    : frame -
 *                  Graphic plane select.
 * Return Value : GLCDC_CLUT_PLANE_0 -
 *                   CLUT plane0 is selected.
 *                GLCDC_CLUT_PLANE_1 -
 *                   CLUT plane1 is selected.
 *******************************************************************************/
glcdc_clut_plane_t r_glcdc_is_clutplane_selected(glcdc_frame_layer_t frame)
{
    /* GRnCLUTINT - Graphic n CLUT/Interrupt Control Register
    b16 SEL - CLUT Control. - Select Color Look-up Table. */
    return (glcdc_clut_plane_t)gp_gr[frame]->grxclutint.bit.sel;

} /* End of function r_glcdc_is_clutplane_selected() */


/*******************************************************************************
 * Outline      : Selects CLUT plane0 or plane1 as current plane for the specified graphics layer.
 * Function Name: r_glcdc_clutplane_select
 * Description  : Selects CLUT plane0 or plane1 as current plane for the specified graphics layer.
 * Arguments    : frame -
 *                  Graphic plane select.
 *                clut_plane -
 *                  Color table plane select.
 * Return Value : none
 *******************************************************************************/
void r_glcdc_clutplane_select(glcdc_frame_layer_t frame, glcdc_clut_plane_t clut_plane)
{
    /* GRnCLUTINT - Graphic n CLUT/Interrupt Control Register
    b16 SEL - CLUT Control. - Select Color Look-up Table. */
    gp_gr[frame]->grxclutint.bit.sel = (uint32_t)clut_plane;

} /* End of function r_glcdc_clutplane_select() */


/*******************************************************************************
 * Outline      : Enables specified graphics layer register update at the next Vsync timing.
 * Function Name: r_glcdc_gr_plane_update
 * Description  : Enables specified graphics layer register update at the next Vsync timing.
 * Arguments    : frame -
 *                  Graphic plane select.
 * Return Value : none
 *******************************************************************************/
void r_glcdc_gr_plane_update(glcdc_frame_layer_t frame)
{
    /* GRnVEN - Graphic n Register Update Control Register
    b31:b1 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b0     VEN      - Graphic n Register Value Reflection Enable */
    gp_gr[frame]->grxven.bit.ven = 1;

} /* End of function r_glcdc_gr_plane_update() */


/*******************************************************************************
 * Outline      : Checks whether specified graphics layer register update is underway or not.
 * Function Name: r_glcdc_is_gr_plane_updating
 * Description  : Checks whether specified graphics layer register update is underway or not.
 * Arguments    : frame -
 *                  Graphic plane select.
 * Return Value : true -
 *                   Register update for the graphics plane block is underway.
 *                false -
 *                   Register update is not underway.
 *******************************************************************************/
bool r_glcdc_is_gr_plane_updating(glcdc_frame_layer_t frame)
{
    /* GRnVEN - Graphic n Register Update Control Register
    b0     VEN      - Graphic n Register Value Reflection Enable */
    return gp_gr[frame]->grxven.bit.ven;

} /* End of function r_glcdc_is_gr_plane_updating() */


/*******************************************************************************
 * Outline      : Enables specified gamma register update at the next Vsync timing.
 * Function Name: r_glcdc_gamma_update
 * Description  : Enables specified gamma register update at the next Vsync timing.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_gamma_update(void)
{
    /* ---- Reflect the value of registers ---- */
    /* GAMxVEN - Gamma Correction x Block Register Update Control Register
    b31:b1 Reserved - These bits are read as 0. Writing to these bits have no effect.
    b0     VEN      - Gamma Correction x Block Register Value Reflection Enable.
                    - Enable the reflection of the register values */
    GLCDC.GAMGVEN.BIT.VEN = 1;
    GLCDC.GAMBVEN.BIT.VEN = 1;
    GLCDC.GAMRVEN.BIT.VEN = 1;

} /* End of function r_glcdc_gamma_update() */


/*******************************************************************************
 * Outline      : Checks whether specified gamma correction register update is underway or not.
 * Function Name: r_glcdc_is_gamma_updating
 * Description  : Checks whether specified gamma correction register update is underway or not.
 * Arguments    : none
 * Return Value : true -
 *                   Register update for the gamma correction is underway.
 *                false -
 *                   Register update is not underway.
 *******************************************************************************/
bool r_glcdc_is_gamma_updating(void)
{
    /* GAMxVEN - Gamma Correction x Block Register Update Control Register
    b0     VEN      - Gamma Correction x Block Register Value Reflection Enable.
                    - Enable the reflection of the register values */
    return (GLCDC.GAMGVEN.BIT.VEN | GLCDC.GAMBVEN.BIT.VEN | GLCDC.GAMRVEN.BIT.VEN);

} /* End of function r_glcdc_is_gamma_updating() */


/*******************************************************************************
 * Outline      : Checks whether graphic 2 line detection is detected or not.
 * Function Name: r_glcdc_vpos_int_status_check
 * Description  : Checks whether graphic 2 line detection is detected or not.
 * Arguments    : none
 * Return Value : true -
 *                   graphic 2 line detection is detected.
 *                false -
 *                   graphic 2 line detection is not detected.
 *******************************************************************************/
bool r_glcdc_vpos_int_status_check(void)
{
    /* STMON - Detected Status Monitor Register
    b31:b3 Reserved   - These bits are read as 0.
    b2     GR2UF - Graphic 2 Underflow Detection Flag.
    b1     GR1UF - Graphic 1 Underflow Detection Flag.
    b0     VPOS  - Graphic 2 Specified Line Notification Detection Flag. */
    return GLCDC.STMON.BIT.VPOS;

} /* End of function r_glcdc_vpos_int_status_check() */


/*******************************************************************************
 * Outline      : Checks whether graphic 1 underflow detection is detected or not.
 * Function Name: r_glcdc_gr1uf_int_status_check
 * Description  : Checks whether graphic 1 underflow detection is detected or not.
 * Arguments    : none
 * Return Value : true -
 *                   graphic 1 underflow detection is detected.
 *                false -
 *                   graphic 1 underflow detection is not detected.
 *******************************************************************************/
bool r_glcdc_gr1uf_int_status_check(void)
{
    /* STMON - Detected Status Monitor Register
    b1     GR1UF - Graphic 1 Underflow Detection Flag. */
    return GLCDC.STMON.BIT.GR1UF;

} /* End of function r_glcdc_gr1uf_int_status_check() */


/*******************************************************************************
 * Outline      : Checks whether graphic 2 underflow detection is detected or not.
 * Function Name: r_glcdc_gr2uf_int_status_check
 * Description  : Checks whether graphic 2 underflow detection is detected or not.
 * Arguments    : none
 * Return Value : true -
 *                   graphic 2 underflow detection is detected.
 *                false -
 *                   graphic 2 underflow detection is not detected.
 *******************************************************************************/
bool r_glcdc_gr2uf_int_status_check(void)
{
    /* STMON - Detected Status Monitor Register
    b2     GR2UF - Graphic 2 Underflow Detection Flag. */
    return GLCDC.STMON.BIT.GR2UF;

} /* End of function r_glcdc_gr2uf_int_status_check() */


/*******************************************************************************
 * Outline      : Clear the graphic 2 line detection status.
 * Function Name: r_glcdc_vpos_int_status_clear
 * Description  : Clear the graphic 2 line detection status.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_vpos_int_status_clear(void)
{
    /* STCLR - Detected Status Clear Register
    b31:b3 Reserved   - These bits are read as 0. Writing to these bits have no effect.
    b2     GR2UFCLR - GR2UF Flag Clear.
    b1     GR1UFCLR - GR1UF Flag Clear.
    b0     VPOSCLR  - VPOS Flag Clear. - Writing 1 to this bit clears the STMON.VPOS flag. */
    GLCDC.STCLR.BIT.VPOSCLR = 1;

} /* End of function r_glcdc_vpos_int_status_clear() */


/*******************************************************************************
 * Outline      : Clear the graphic 1 underflow detection status.
 * Function Name: r_glcdc_gr1uf_int_status_clear
 * Description  : Clear the graphic 1 underflow detection status.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_gr1uf_int_status_clear(void)
{
    /* STCLR - Detected Status Clear Register
    b1     GR1UFCLR - GR1UF Flag Clear. - Writing 1 to this bit clears the STMON.GR1UF flag. */
    GLCDC.STCLR.BIT.GR1UFCLR = 1;

} /* End of function r_glcdc_gr1uf_int_status_clear() */


/*******************************************************************************
 * Outline      : Clear the graphic 2 underflow detection status.
 * Function Name: r_glcdc_gr2uf_int_status_clear
 * Description  : Clear the graphic 2 underflow detection status.
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void r_glcdc_gr2uf_int_status_clear(void)
{
    /* STCLR - Detected Status Clear Register
    b2     GR2UFCLR - GR2UF Flag Clear. - Writing 1 to this bit clears the STMON.GR2UF flag. */
    GLCDC.STCLR.BIT.GR2UFCLR = 1;

} /* End of function r_glcdc_gr2uf_int_status_clear() */


/*******************************************************************************
 * Outline      : Graphic 2 line detection interrupt service routine.
 * Function Name: r_glcdc_line_detect_isr
 * Description  : This ISR is called when the number of the display line reaches
 *                the designated number of lines.
 *                If a callback function is registered in R_GLCDC_Open(),
 *                it is called from this ISR and the GLCDC_EVENT_LINE_DETECTION event code
 *                is set as its argument.
 * Arguments    : none
 * Return Value : none
 * Note         : This function must be called from group AL1 interrupt function.
 *                In this application note, it is set to be called from the group AL1 interrupt function
 *                by the function implemented in the board support package module.
 *                When using this driver on the user system, please implement this function
 *                so that it can be called from the group AL1 interrupt in accordance with the user's manual.
 *******************************************************************************/
void r_glcdc_line_detect_isr(void)
{
    glcdc_callback_args_t args;

    /* Call back callback function if it is registered */
    if ((NULL != g_ctrl_blk.p_callback) && ((uint32_t)FIT_NO_FUNC != (uint32_t)g_ctrl_blk.p_callback))
    {
        args.event = GLCDC_EVENT_LINE_DETECTION;
        g_ctrl_blk.p_callback ((void *)&args);
    }

    /* Clear interrupt flag in the register of the GLCD module */
    r_glcdc_vpos_int_status_clear ();

    if(false == g_ctrl_blk.first_vpos_interrupt_flag)
    {
        /* Clear interrupt flag in the register of the GLCD module */
        r_glcdc_gr1uf_int_status_clear ();
        r_glcdc_gr2uf_int_status_clear ();

        /* Set the GLCD interrupts */
        r_glcdc_interrupt_setting (&g_ctrl_blk.interrupt);

        /* Set the first VPOS interrupt flag */
        g_ctrl_blk.first_vpos_interrupt_flag = true;
    }

} /* End of function r_glcdc_line_detect_isr() */


/*******************************************************************************
 * Outline      : Graphic 1 underflow detection interrupt service routine.
 * Function Name: r_glcdc_underflow_1_isr
 * Description  : This ISR is called when the underflow occurs in the graphics plane 1 control block.
 *                If a callback function is registered in R_GLCDC_Open(),
 *                it is called from this ISR and the GLCDC_EVENT_GR1_UNDERFLOW event code
 *                is set as its argument.
 * Arguments    : none
 * Return Value : none
 * Note         : This function must be called from group AL1 interrupt function.
 *                In this application note, it is set to be called from the group AL1 interrupt function
 *                by the function implemented in the board support package module.
 *                When using this driver on the user system, please implement this function
 *                so that it can be called from the group AL1 interrupt in accordance with the user's manual.
 *******************************************************************************/
void r_glcdc_underflow_1_isr(void)
{
    glcdc_callback_args_t args;

    /* Call back callback function if it is registered */
    if ((NULL != g_ctrl_blk.p_callback) && ((uint32_t)FIT_NO_FUNC != (uint32_t)g_ctrl_blk.p_callback))
    {
        args.event = GLCDC_EVENT_GR1_UNDERFLOW;
        g_ctrl_blk.p_callback ((void *)&args);
    }

    /* Clear interrupt flag in the register of the GLCD module */
    r_glcdc_gr1uf_int_status_clear ();

} /* End of function r_glcdc_underflow_1_isr() */


/*******************************************************************************
 * Outline      : Graphic 2 underflow detection interrupt service routine.
 * Function Name: r_glcdc_underflow_2_isr
 * Description  : This ISR is called when the underflow occurs in the graphics plane 2 control block.
 *                If a callback function is registered in R_GLCDC_Open(),
 *                it is called from this ISR and the GLCDC_EVENT_GR2_UNDERFLOW event code
 *                is set as its argument.
 * Arguments    : none
 * Return Value : none
 * Note         : This function must be called from group AL1 interrupt function.
 *                In this application note, it is set to be called from the group AL1 interrupt function
 *                by the function implemented in the board support package module.
 *                When using this driver on the user system, please implement this function
 *                so that it can be called from the group AL1 interrupt in accordance with the user's manual.
 *******************************************************************************/
void r_glcdc_underflow_2_isr(void)
{
    glcdc_callback_args_t args;

    /* Call the callback function if it is registered */
    if ((NULL != g_ctrl_blk.p_callback) && ((uint32_t)FIT_NO_FUNC != (uint32_t)g_ctrl_blk.p_callback))
    {
        args.event = GLCDC_EVENT_GR2_UNDERFLOW;
        g_ctrl_blk.p_callback ((void *)&args);
    }

    /* Clear interrupt flag in the register of the GLCD module */
    r_glcdc_gr2uf_int_status_clear ();

} /* End of function r_glcdc_underflow_2_isr() */


/*******************************************************************************
 * Outline      : Background color setting in Background screen.
 * Function Name: r_glcdc_bg_color_setting
 * Description  : Background color sets.
 * Arguments    : none
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_bg_color_setting (glcdc_color_t const * const p_color)
{
    /* ---- Set the Background color ---- */
    /* BGCOLOR - Background Color Register
    b31:b24  Reserved - These bits are read as 0. Writing to these bits have no effect.
    b23:b16  R[7:0] - Background Color R Value Setting.
    b15:b8   G[7:0] - Background Color G Value Setting.
    b7:b0    B[7:0] - Background Color B Value Setting. */
    GLCDC.BGCOLOR.BIT.R = p_color->byte.r;
    GLCDC.BGCOLOR.BIT.G = p_color->byte.g;
    GLCDC.BGCOLOR.BIT.B = p_color->byte.b;

} /* End of function r_glcdc_bg_color_setting() */

/* End of File */
