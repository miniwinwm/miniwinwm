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
 * File Name    : r_glcdc_rx.c
 * Version      : 1.00
 * Description  : GLCDC API functions.
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
 Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/
/* GLCD control block */
glcdc_ctrl_t g_ctrl_blk =
{
   GLCDC_STATE_CLOSED,
   false,
   { 0U, 0U },
   0U,
   0U,
   { false, false },
   NULL,
   false,
   { false, false, false }
};

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Outline      : GLCDC Initialization Processing
 * Function Name: R_GLCDC_Open
 * Description  : Setting GLCDC initialization. It is necessary to set an argument *p_cfg
 *                and when this function is executed, GLCDC is ready to be used.
 * Arguments    : p_cfg -
 *                  GLCDC configuration parameters.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_LOCK_FUNC -
 *                  GLCDC resource is in use by another process.
 *                GLCDC_ERR_INVALID_PTR -
 *                  Pointer to the control block or the configuration structure is NULL.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid parameter in the argument.
 *                GLCDC_ERR_INVALID_MODE -
 *                  Incorrect mode
 *                GLCDC_ERR_INVALID_TIMING_SETTING -
 *                  Invalid panel timing parameter.
 *                GLCDC_ERR_INVALID_LAYER_SETTING -
 *                  Invalid layer setting found.
 *                GLCDC_ERR_INVALID_ALIGNMENT -
 *                  Invalid memory alignment found.
 *                GLCDC_ERR_INVALID_GAMMA_SETTING -
 *                  Invalid gamma correction setting found.
 *                GLCDC_ERR_INVALID_CLUT_ACCESS -
 *                  Invalid access to color palette entry.
 *                GLCDC_ERR_INVALID_BLEND_SETTING -
 *                  Invalid blend setting.
 * Note         : To use Graphics LCD Controller (GLCDC), PCLKA setting is required.
 *              : GLCDC pins must be set in IOPORT after calling this API.
 ***********************************************************************************************************************/
glcdc_err_t R_GLCDC_Open(glcdc_cfg_t const * const p_cfg)
{
    uint32_t frame;
    glcdc_interrupt_cfg_t initial_interrupt;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    glcdc_err_t err = GLCDC_SUCCESS;
#endif

    /* Status check */
    if (GLCDC_STATE_CLOSED != g_ctrl_blk.state)
    {
        return GLCDC_ERR_INVALID_MODE;
    }

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    /* Argument check */
    if (NULL == p_cfg)
    {
        return GLCDC_ERR_INVALID_PTR;
    }
#endif

    /* Store position information to the control block (it is necessary to set the layer and blending section later) */
    g_ctrl_blk.active_start_pos.x = (int16_t) (p_cfg->output.htiming.back_porch + p_cfg->output.htiming.sync_width);
    g_ctrl_blk.active_start_pos.y = (int16_t) (p_cfg->output.vtiming.back_porch + p_cfg->output.vtiming.sync_width);
    g_ctrl_blk.hsize = p_cfg->output.htiming.display_cyc;
    g_ctrl_blk.vsize = p_cfg->output.vtiming.display_cyc;

    /* Subscribe each interrupt function  */
    if (false == g_ctrl_blk.is_entry)
    {
        R_BSP_InterruptWrite (BSP_INT_SRC_AL1_GLCDC_VPOS, (bsp_int_cb_t) r_glcdc_line_detect_isr);
        R_BSP_InterruptWrite (BSP_INT_SRC_AL1_GLCDC_GR1UF, (bsp_int_cb_t) r_glcdc_underflow_1_isr);
        R_BSP_InterruptWrite (BSP_INT_SRC_AL1_GLCDC_GR2UF, (bsp_int_cb_t) r_glcdc_underflow_2_isr);

        g_ctrl_blk.is_entry = true;
    }

    /* Save status of frame buffer read enable */
    if(NULL == p_cfg->input[GLCDC_FRAME_LAYER_1].p_base)
    {
        g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_1] = false;
    }
    else
    {
        g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_1] = true;
    }

    if(NULL == p_cfg->input[GLCDC_FRAME_LAYER_2].p_base)
    {
        g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_2] = false;
    }
    else
    {
        g_ctrl_blk.graphics_read_enable[GLCDC_FRAME_LAYER_2] = true;
    }

    /* Save callback function */
    g_ctrl_blk.p_callback = p_cfg->p_callback;

    /* Save setting of interrupt */
    g_ctrl_blk.interrupt.vpos_enable = p_cfg->interrupt.vpos_enable;
    g_ctrl_blk.interrupt.gr1uf_enable = p_cfg->interrupt.gr1uf_enable;
    g_ctrl_blk.interrupt.gr2uf_enable = p_cfg->interrupt.gr2uf_enable;

    /* If one of the interrupt setting is enable, setting value is set after first vpos interrupt */
    if ((true == p_cfg->interrupt.vpos_enable) || (true == p_cfg->interrupt.gr1uf_enable) || (true == p_cfg->interrupt.gr2uf_enable))
    {
        g_ctrl_blk.first_vpos_interrupt_flag = false;
        initial_interrupt.vpos_enable = true;
        initial_interrupt.gr1uf_enable = false;
        initial_interrupt.gr2uf_enable = false;
    }
    else
    {
        g_ctrl_blk.first_vpos_interrupt_flag = true;
        initial_interrupt.vpos_enable = false;
        initial_interrupt.gr1uf_enable = false;
        initial_interrupt.gr2uf_enable = false;
    }

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    /* Check parameters */
    err = r_glcdc_open_param_check (p_cfg);
    if (GLCDC_SUCCESS != err)
    {
        return err;
    }
#endif

    /* Check GLCDC resource is locked by another process */
    if (false == R_BSP_HardwareLock ((mcu_lock_t) BSP_LOCK_GLCDC))
    {
        return GLCDC_ERR_LOCK_FUNC;
    }

    /* Supply the peripheral clock to the GLCD module */
    r_glcdc_power_on ();

    /* Release GLCD from a SW reset status. */
    r_glcdc_release_software_reset ();

    /* Set the dot clock frequency */
    r_glcdc_clock_set (p_cfg);

    /* Set the panel signal timing */
    r_glcdc_sync_signal_set (p_cfg);

    /* Configure the background screen */
    r_glcdc_background_screen_set (p_cfg);

    /* Configure the graphics plane layers */
    for (frame = 0; frame <= GLCDC_FRAME_LAYER_2; frame++)
    {
        r_glcdc_graphics_layer_set (&p_cfg->input[frame], (glcdc_frame_layer_t) frame);
        r_glcdc_blend_condition_set (&p_cfg->blend[frame], (glcdc_frame_layer_t) frame);
        r_glcdc_graphics_chromakey_set (&p_cfg->chromakey[frame], (glcdc_frame_layer_t) frame);
        r_glcdc_clut_update(&p_cfg->clut[frame], (glcdc_frame_layer_t) frame);
    }

    /* Configure the output control block */
    r_glcdc_output_block_set (p_cfg);

    /* Configure the color correction setting (brightness, brightness and gamma correction) */
    r_glcdc_brightness_correction (&p_cfg->output.brightness);
    r_glcdc_contrast_correction (&p_cfg->output.contrast);
    r_glcdc_gamma_correction (&p_cfg->output.gamma);

    /* Set the line number which is suppose to happen the line detect interrupt */
    r_glcdc_line_detect_number_set (
            (uint16_t) (((p_cfg->output.vtiming.sync_width + p_cfg->output.vtiming.back_porch)
                    + p_cfg->output.vtiming.display_cyc) + BG_PLANE_HSYNC_POS_MIN));

    /* Enable the GLCD detections and interrupts */
    r_glcdc_detect_setting (&p_cfg->detection);
    r_glcdc_interrupt_setting (&initial_interrupt);

    /* Allow reading of graphics data */
    r_glcdc_graphics_read_enable();

    /* Change GLCDC driver state */
    g_ctrl_blk.state = GLCDC_STATE_NOT_DISPLAYING;

    return GLCDC_SUCCESS;
} /* End of function R_GLCDC_Open() */


/***********************************************************************************************************************
 * Outline      : GLCDC Closing Processing
 * Function Name: R_GLCDC_Close
 * Description  : Perform GLCDC closing process. When this function is executed,
 *                GLCDC is reset and transitioned to module stop state.
 * Arguments    : none
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_NOT_OPEN -
 *                  Open function is not called yet.
 *                GLCDC_ERR_INVALID_MODE -
 *                  Incorrect mode.
 * Note         : Stop displaying with GLCDC_CMD_STOP_DISPLAY command of
 *                R_GLCDC_Control function before call this function.
 ***********************************************************************************************************************/
glcdc_err_t R_GLCDC_Close(void)
{
    glcdc_interrupt_cfg_t interrupt;
    glcdc_detect_cfg_t detection;

    /* Status check */
    if (GLCDC_STATE_CLOSED == g_ctrl_blk.state)
    {
        return GLCDC_ERR_NOT_OPEN;
    }
    if (GLCDC_STATE_DISPLAYING == g_ctrl_blk.state)
    {
        return GLCDC_ERR_INVALID_MODE;
    }

    /* Disable the GLCD detects */
    detection.vpos_detect = false;
    detection.gr1uf_detect = false;
    detection.gr2uf_detect = false;
    r_glcdc_detect_setting(&detection);

    /* interrupt disable */
    interrupt.vpos_enable = false;
    interrupt.gr1uf_enable = false;
    interrupt.gr2uf_enable = false;

    r_glcdc_interrupt_setting(&interrupt);

    /* Reset the GLCD hardware */
    r_glcdc_software_reset ();

    /* Halt the peripheral clock to the GLCD module */
    r_glcdc_power_off ();

    /* Release GLCDC resource */
    R_BSP_HardwareUnlock ((mcu_lock_t) BSP_LOCK_GLCDC);

    /* Change GLCDC driver state */
    g_ctrl_blk.state = GLCDC_STATE_CLOSED;

    return GLCDC_SUCCESS;
} /* End of function R_GLCDC_Close() */


/***********************************************************************************************************************
 * Outline      : GLCDC Control Processing
 * Function Name: R_GLCDC_Control
 * Description  : Perform GLCDC Control Process.
 *                Corresponding to argument cmd, GLCDC Operation Start, Operation Stop,
 *                Interrupt Setting, Detection Status Clear processing is performed.
 * Arguments    : cmd -
 *                  Control function command.
 *                p_args -
 *                  Pointer of setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_PTR -
 *                  Pointer to the control block or the configuration structure is NULL.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid parameter in the argument.
 *                GLCDC_ERR_INVALID_MODE -
 *                  Incorrect mode
 *                GLCDC_ERR_NOT_OPEN -
 *                  Open function is not called yet.
 *                GLCDC_ERR_INVALID_UPDATE_TIMING -
 *                  Invalid timing for register update.
 * Note         : none
 ***********************************************************************************************************************/
glcdc_err_t R_GLCDC_Control(glcdc_control_cmd_t cmd, void const * const p_args)
{
    glcdc_detect_cfg_t * p_detection;

    if (GLCDC_STATE_CLOSED == g_ctrl_blk.state)
    {
        return GLCDC_ERR_NOT_OPEN;
    }

    switch (cmd)
    {
        case GLCDC_CMD_START_DISPLAY:

            if (GLCDC_STATE_DISPLAYING == g_ctrl_blk.state)
            {
                return GLCDC_ERR_INVALID_MODE;
            }

            /* Change GLCDC driver state */
            g_ctrl_blk.state = GLCDC_STATE_DISPLAYING;

            /* Start to output the vertical and horizontal synchronization signals and screen data. */
            r_glcdc_bg_operation_enable ();

        break;

        case GLCDC_CMD_STOP_DISPLAY:

            if (GLCDC_STATE_NOT_DISPLAYING == g_ctrl_blk.state)
            {
                return GLCDC_ERR_INVALID_MODE;
            }

            /* Return immediately if the register is being updated */
            if (true == r_glcdc_is_gr_plane_updating (GLCDC_FRAME_LAYER_1))
            {
                return GLCDC_ERR_INVALID_UPDATE_TIMING;
            }
            if (true == r_glcdc_is_gr_plane_updating (GLCDC_FRAME_LAYER_2))
            {
                return GLCDC_ERR_INVALID_UPDATE_TIMING;
            }
            if (true == r_glcdc_is_output_ctrl_updating ())
            {
                return GLCDC_ERR_INVALID_UPDATE_TIMING;
            }
            if (true == r_glcdc_is_gamma_updating ())
            {
                return GLCDC_ERR_INVALID_UPDATE_TIMING;
            }
            if (true == r_glcdc_is_register_reflecting ())
            {
                return GLCDC_ERR_INVALID_UPDATE_TIMING;
            }

            /* Stop outputting the vertical and horizontal synchronization signals and screen data. */
            r_glcdc_bg_operation_disable ();

            /* status update */
            g_ctrl_blk.state = GLCDC_STATE_NOT_DISPLAYING;

        break;

        case GLCDC_CMD_SET_INTERRUPT:

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
            if (NULL == p_args)
            {
                return GLCDC_ERR_INVALID_PTR;
            }
#endif

            if (false == g_ctrl_blk.first_vpos_interrupt_flag)
            {
                return GLCDC_ERR_INVALID_UPDATE_TIMING;
            }

            /* interrupt setting */
            r_glcdc_interrupt_setting ((glcdc_interrupt_cfg_t *) p_args);

        break;

        case GLCDC_CMD_CLR_DETECTED_STATUS:

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
            if (NULL == p_args)
            {
                return GLCDC_ERR_INVALID_PTR;
            }
#endif
            p_detection = (glcdc_detect_cfg_t *) p_args;

            if (true == p_detection->vpos_detect)
            {
                r_glcdc_vpos_int_status_clear ();
            }
            if (true == p_detection->gr1uf_detect)
            {
                r_glcdc_gr1uf_int_status_clear ();
            }
            if (true == p_detection->gr2uf_detect)
            {
                r_glcdc_gr2uf_int_status_clear ();
            }

        break;

        case GLCDC_CMD_CHANGE_BG_COLOR:

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
            if (NULL == p_args)
            {
                return GLCDC_ERR_INVALID_PTR;
            }
#endif

            r_glcdc_bg_color_setting ((glcdc_color_t *) p_args);

        break;

        default:
            return GLCDC_ERR_INVALID_ARG;
    }

    return GLCDC_SUCCESS;
} /* End of function R_GLCDC_Control() */


/***********************************************************************************************************************
 * Outline      : Change processing of Graphic 1 and Graphic 2 of GLCDC
 * Function Name: R_GLCDC_LayerChange
 * Description  : Perform change processing of Graphic 1 and Graphic 2 of GLCDC.
 *                Corresponding to argument cmd, the basic setting, chroma key
 *                and blending setting of Graphic 1 and Graphic 2 are performed.
 * Arguments    : frame -
 *                   Graphic plane select.
 *                p_args -
 *                   Pointer of setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_PTR -
 *                  Pointer to the control block or the configuration structure is NULL.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid parameter in the argument.
 *                GLCDC_ERR_INVALID_MODE -
 *                  Incorrect mode.
 *                GLCDC_ERR_NOT_OPEN -
 *                  Open function is not called yet.
 *                GLCDC_ERR_INVALID_UPDATE_TIMING -
 *                  Invalid timing for register update.
 *                GLCDC_ERR_INVALID_LAYER_SETTING -
 *                  Invalid layer setting found.
 *                GLCDC_ERR_INVALID_ALIGNMENT -
 *                  Invalid memory alignment found.
 *                GLCDC_ERR_INVALID_BLEND_SETTING -
 *                  Invalid blend setting.
 * Note         : none
 ***********************************************************************************************************************/
glcdc_err_t R_GLCDC_LayerChange(glcdc_frame_layer_t frame, glcdc_runtime_cfg_t const * const p_args)
{

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    glcdc_err_t err = GLCDC_SUCCESS;
#endif

    if (GLCDC_STATE_CLOSED == g_ctrl_blk.state)
    {
        return GLCDC_ERR_NOT_OPEN;
    }
    if (GLCDC_STATE_NOT_DISPLAYING == g_ctrl_blk.state)
    {
        return GLCDC_ERR_INVALID_MODE;
    }

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    if (NULL == p_args)
    {
        return GLCDC_ERR_INVALID_PTR;
    }
    if ((GLCDC_FRAME_LAYER_1 != frame) && (GLCDC_FRAME_LAYER_2 != frame))
    {
        return GLCDC_ERR_INVALID_ARG;
    }
#endif

    if(false == g_ctrl_blk.graphics_read_enable[frame])
    {
        return GLCDC_ERR_INVALID_ARG;
    }

    /* Return immediately if the register updating is in progress. */
    if (true == r_glcdc_is_gr_plane_updating (frame))
    {
        return GLCDC_ERR_INVALID_UPDATE_TIMING;
    }
    if (true == r_glcdc_is_register_reflecting ())
    {
        return GLCDC_ERR_INVALID_UPDATE_TIMING;
    }


#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)

    err = r_glcdc_param_check_layer (p_args);

    if (GLCDC_SUCCESS != err)
    {
        return err;
    }

#endif

    /* Configure the graphics plane layers */
    r_glcdc_graphics_layer_set (&p_args->input, frame);

    /* Configure the alpha blending condition */
    r_glcdc_blend_condition_set (&p_args->blend, frame);

    /* Configure the chroma key */
    r_glcdc_graphics_chromakey_set (&p_args->chromakey, frame);

    /* Reflect the graphics module register value to the GLCD internal operations
     *  (at the timing of the next Vsync assertion) */
    r_glcdc_gr_plane_update (frame);

    return GLCDC_SUCCESS;
} /* End of function R_GLCDC_LayerChange() */


/***********************************************************************************************************************
 * Outline      : GLCDC brightness, contrast, gamma change processing
 * Function Name: R_GLCDC_ColorCorrection
 * Description  : Perform GLCDC brightness, contrast, gamma change processing.
 *                Corresponding to argument cmd, GLCDC brightness, contrast,
 *                gamma change processing is performed.
 * Arguments    : cmd -
 *                   Control function command.
 *                p_args -
 *                   Pointer of setting parameter.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_PTR -
 *                  Pointer to the control block or the configuration structure is NULL.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid parameter in the argument.
 *                GLCDC_ERR_INVALID_MODE -
 *                  incorrect mode
 *                GLCDC_ERR_NOT_OPEN -
 *                  Open function is not called yet.
 *                GLCDC_ERR_INVALID_UPDATE_TIMING -
 *                  Invalid timing for register update.
 *                GLCDC_ERR_INVALID_GAMMA_SETTING -
 *                  Invalid gamma correction setting found.
 * Note         : none
 ***********************************************************************************************************************/
glcdc_err_t R_GLCDC_ColorCorrection(glcdc_correction_cmd_t cmd, void const * const p_args)
{
    glcdc_correction_t * p_correction;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    glcdc_err_t err = GLCDC_SUCCESS;
#endif

    if (GLCDC_STATE_CLOSED == g_ctrl_blk.state)
    {
        return GLCDC_ERR_NOT_OPEN;
    }
    if (GLCDC_STATE_NOT_DISPLAYING == g_ctrl_blk.state)
    {
        return GLCDC_ERR_INVALID_MODE;
    }

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    if (NULL == p_args)
    {
        return GLCDC_ERR_INVALID_PTR;
    }
#endif

    /* Return immediately if the register updating are performed */
    if (true == r_glcdc_is_output_ctrl_updating ())
    {
        return GLCDC_ERR_INVALID_UPDATE_TIMING;
    }
    if (true == r_glcdc_is_gamma_updating ())
    {
        return GLCDC_ERR_INVALID_UPDATE_TIMING;
    }
    if (true == r_glcdc_is_register_reflecting ())
    {
        return GLCDC_ERR_INVALID_UPDATE_TIMING;
    }

    switch (cmd)
    {
        case GLCDC_CORRECTION_CMD_SET_ALL:

            p_correction = (glcdc_correction_t *) p_args;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
            err = r_glcdc_param_check_brightness (&p_correction->brightness);
            if (GLCDC_SUCCESS != err)
            {
                return err;
            }

            err = r_glcdc_param_check_contrast (&p_correction->contrast);
            if (GLCDC_SUCCESS != err)
            {
                return err;
            }

            err = r_glcdc_param_check_gamma (&p_correction->gamma);
            if (GLCDC_SUCCESS != err)
            {
                return err;
            }
#endif

            /* Configure the brightness and contrast and gamma correction register setting. */
            r_glcdc_brightness_correction (&p_correction->brightness);
            r_glcdc_contrast_correction (&p_correction->contrast);
            r_glcdc_gamma_correction (&p_correction->gamma);

            /* Reflect the output block section and gamma register setting. */
            r_glcdc_output_ctrl_update ();
            r_glcdc_gamma_update ();

        break;

        case GLCDC_CORRECTION_CMD_BRIGHTNESS:

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
            err = r_glcdc_param_check_brightness ((glcdc_brightness_t *) p_args);
            if (GLCDC_SUCCESS != err)
            {
                return err;
            }
#endif
            /* Configure the brightness correction register setting. */
            r_glcdc_brightness_correction ((glcdc_brightness_t *) p_args);

            /* Reflect the output block section register setting. */
            r_glcdc_output_ctrl_update ();

        break;

        case GLCDC_CORRECTION_CMD_CONTRAST:

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
            err = r_glcdc_param_check_contrast ((glcdc_contrast_t *) p_args);
            if (GLCDC_SUCCESS != err)
            {
                return err;
            }
#endif
            /* Configure the contrast correction register setting. */
            r_glcdc_contrast_correction ((glcdc_contrast_t *) p_args);

            /* Reflect the output block section register setting. */
            r_glcdc_output_ctrl_update ();

        break;

        case GLCDC_CORRECTION_CMD_GAMMA:

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
            err = r_glcdc_param_check_gamma ((glcdc_gamma_correction_t *) p_args);
            if (GLCDC_SUCCESS != err)
            {
                return err;
            }
#endif
            /* Configure the gamma correction register setting. */
            r_glcdc_gamma_correction ((glcdc_gamma_correction_t *) p_args);

            /* Reflect the gamma register setting. */
            r_glcdc_gamma_update ();

        break;

        default:
            return GLCDC_ERR_INVALID_ARG;
    }


    return GLCDC_SUCCESS;
} /* End of function R_GLCDC_ColorCorrection() */


/***********************************************************************************************************************
 * Outline      : GLCDC color palette update processing
 * Function Name: R_GLCDC_ClutUpdate
 * Description  : Perform GLCDC color palette update processing.
 * Arguments    : p_clut_cfg -
 *                   Control function command.
 *                frame -
 *                   Graphic plane select.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_PTR -
 *                  Pointer to the control block or the configuration structure is NULL.
 *                GLCDC_ERR_INVALID_ARG -
 *                  Invalid parameter in the argument.
 *                GLCDC_ERR_INVALID_MODE -
 *                  incorrect mode
 *                GLCDC_ERR_NOT_OPEN -
 *                  Open function is not called yet.
 *                GLCDC_ERR_INVALID_UPDATE_TIMING -
 *                  Invalid timing for register update.
 *                GLCDC_ERR_INVALID_CLUT_ACCESS -
 *                  Invalid access to color palette entry.
 * Note         : none
 ***********************************************************************************************************************/
glcdc_err_t R_GLCDC_ClutUpdate(glcdc_frame_layer_t frame, glcdc_clut_cfg_t const * const p_clut_cfg)
{

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    glcdc_err_t err = GLCDC_SUCCESS;
#endif
    
    /* Status check */
    if (GLCDC_STATE_CLOSED == g_ctrl_blk.state)
    {
        return GLCDC_ERR_NOT_OPEN;
    }
    if (GLCDC_STATE_NOT_DISPLAYING == g_ctrl_blk.state)
    {
        return GLCDC_ERR_INVALID_MODE;
    }

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    if (NULL == p_clut_cfg)
    {
        return GLCDC_ERR_INVALID_PTR;
    }
    if ((GLCDC_FRAME_LAYER_1 != frame) && (GLCDC_FRAME_LAYER_2 != frame))
    {
        return GLCDC_ERR_INVALID_ARG;
    }
#endif
    
    if(false == g_ctrl_blk.graphics_read_enable[frame])
    {
        return GLCDC_ERR_INVALID_ARG;
    }

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    err = r_glcdc_param_check_clut(p_clut_cfg);
    if (GLCDC_SUCCESS != err)
    {
        return err;
    }

#endif

    /* Return immediately if the register updating is in progress. */
    if (true == r_glcdc_is_gr_plane_updating (frame))
    {
        return GLCDC_ERR_INVALID_UPDATE_TIMING;
    }
    if (true == r_glcdc_is_register_reflecting ())
    {
        return GLCDC_ERR_INVALID_UPDATE_TIMING;
    }

    /* Update a color palette */
    r_glcdc_clut_update(p_clut_cfg, frame);

    /* Reflect the graphics module register value */
    r_glcdc_gr_plane_update (frame);

    return GLCDC_SUCCESS;
} /* End of function R_GLCDC_ClutUpdate() */


/*******************************************************************************
 * Outline      : GLCDC status acquisition processing
 * Function Name: R_GLCDC_GetStatus
 * Description  : Perform GLCDC status acquisition processing
 *                The following status is stored in the argument pointer.
 *                 - Graphic 2 Line Detection Status
 *                 - Graphic 1 Underflow Detection Status
 *                 - Graphic 2 Underflow Detection Status
 *                 - Fade in/out Status
 *                 - Internal Status
 * Arguments    : p_status -
 *                  Control function command.
 * Return Value : GLCDC_SUCCESS -
 *                  Device was opened successfully.
 *                GLCDC_ERR_INVALID_PTR -
 *                  Pointer to the control block or the configuration structure is NULL.
 *                GLCDC_ERR_NOT_OPEN -
 *                  Open function is not called yet.
 * Note         : none
 *******************************************************************************/
glcdc_err_t R_GLCDC_GetStatus(glcdc_status_t * const p_status)
{
    uint8_t frame;

    if (GLCDC_STATE_CLOSED == g_ctrl_blk.state)
    {
        return GLCDC_ERR_NOT_OPEN;
    }

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    if (NULL == p_status)
    {
        return GLCDC_ERR_INVALID_PTR;
    }
#endif

    /* Return the GLCD driver state */
    p_status->state = g_ctrl_blk.state;

    /* Return the fading status for the layers */
    for (frame = 0; frame < GLCDC_FRAME_LAYER_NUM; frame++)
    {
        if (true == r_glcdc_is_gr_plane_updating ((glcdc_frame_layer_t) frame))
        {
            /* Fading status is uncertain (the reason is described above). */
            p_status->fade_status[frame] = GLCDC_FADE_STATUS_UNCERTAIN;
        }
        else
        {
            if (true == r_glcdc_is_fading ((glcdc_frame_layer_t) frame))
            {
                p_status->fade_status[frame] = GLCDC_FADE_STATUS_FADING_UNDERWAY;
            }
            else
            {
                p_status->fade_status[frame] = GLCDC_FADE_STATUS_NOT_UNDERWAY;
            }
        }
    }

    /* Return the detected status for the vpos, gr1uf, gr2uf */
    if (true == r_glcdc_vpos_int_status_check ())
    {
        p_status->state_vpos = GLCDC_DETECTED;
    }
    else
    {
        p_status->state_vpos = GLCDC_NOT_DETECTED;
    }
    if (true == r_glcdc_gr1uf_int_status_check ())
    {
        p_status->state_gr1uf = GLCDC_DETECTED;
    }
    else
    {
        p_status->state_gr1uf = GLCDC_NOT_DETECTED;
    }
    if (true == r_glcdc_gr2uf_int_status_check ())
    {
        p_status->state_gr2uf = GLCDC_DETECTED;
    }
    else
    {
        p_status->state_gr2uf = GLCDC_NOT_DETECTED;
    }

    return GLCDC_SUCCESS;
} /* End of function R_GLCDC_GetStatus() */


/***********************************************************************************************************************
 * Function Name: R_GLCDC_GetVersion
 * Description  : Returns this module's version information.
 *                The version number is encoded where the top 2 bytes are the major version number and the bottom 2 bytes
 *                are the minor version number. For example, Version 4.25 would be returned as 0x00040019.
 * Arguments    : none
 * Return Value : Version number
 ***********************************************************************************************************************/
#pragma inline(R_GLCDC_GetVersion)
uint32_t R_GLCDC_GetVersion (void)
{
    return ((((uint32_t) GLCDC_RX_VERSION_MAJOR) << 16) | ((uint32_t) GLCDC_RX_VERSION_MINOR));
} /* End of function R_GLCDC_GetVersion() */

/* End of File */
