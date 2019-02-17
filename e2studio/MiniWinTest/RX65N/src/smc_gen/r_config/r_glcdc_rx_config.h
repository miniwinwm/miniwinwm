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
 * File Name    : r_glcdc_rx_config.h
 * Version      : 1.00
 * Description  : GLCDC configuration header file
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.10.2017 1.00     First Release
 ***********************************************************************************************************************/

#ifndef R_GLCDC_RX_CONFIG_H
#define R_GLCDC_RX_CONFIG_H

/**********************************************************************************************************************
 * Configuration Options
 **********************************************************************************************************************/

/* Select whether to perform parameter check processing or not.
 * 1: Enable parameter check
 *    Include parameter checking process when building code
 * 0: Disable parameter check
 *    Exclude parameter checking process when building code
 */
#define GLCDC_CFG_PARAM_CHECKING_ENABLE (1)

/* Interrupt priority level of GLCDC interrupt (group AL1 interrupt)
 *  Setting range: 0 to 15
 */
#define GLCDC_CFG_INTERRUPT_PRIORITY_LEVEL (5)

#endif /* R_GLCDC_RX_CONFIG_H */

/* End of File */
