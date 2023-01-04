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
/***********************************************************************************************************************
* File Name    : bsp_clocks.c
* Description  : Calls the CGC module to setup the system clocks. Settings for clocks are based on macros in
*                bsp_clock_cfg.h.
***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup BSP_MCU_S5D9
 * @defgroup BSP_MCU_CLOCKS_S5D9 Clock Initialization
 *
 * Functions in this file configure the system clocks based upon the macros in bsp_clock_cfg.h.
 *
 * @{
 **********************************************************************************************************************/



/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "bsp_api.h"

#if defined(BSP_MCU_GROUP_S5D9)

#include "r_cgc_api.h"
#include "r_cgc.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/** SRAM requires 1 wait state be inserted at ICLK > 60 MHz. SRAMHS is always no wait state */
#define CGC_SYS_CLOCK_FREQ_NO_RAM_WAITS   (60000000U)

/** FLASH requires 1 wait state be inserted when (40 MHz < ICLK <= 80 MHz) */
#define CGC_SYS_CLOCK_FREQ_ONE_ROM_WAITS  (40000000U)

/** FLASH requires 2 wait states be inserted when (80 MHz < ICLK <= 120 MHz) */
#define CGC_SYS_CLOCK_FREQ_TWO_ROM_WAITS  (80000000U)

#define CGC_SRAM_ZERO_WAIT_CYCLES (0U)              ///< Specify zero wait states for SRAM
#define CGC_SRAM_ONE_WAIT_CYCLES  (1U)              ///< Specify one wait states for SRAM

#define CGC_SRAM_PRCR_KEY                 (0x78U)
#define CGC_SRAM_UNLOCK                   (((CGC_SRAM_PRCR_KEY) << 1) | 0x1U)
#define CGC_SRAM_LOCK                     (((CGC_SRAM_PRCR_KEY) << 1) | 0x0U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
 
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/


/*******************************************************************************************************************//**
 * @brief      Sets up system clocks.
 **********************************************************************************************************************/
void bsp_clock_init (void)
{
    ssp_err_t err = SSP_SUCCESS;
    g_cgc_on_cgc.init();

    /** MOCO is default clock out of reset. Enable new clock if chosen. */
    cgc_clock_t clock;

    if (BSP_CFG_CLOCK_SOURCE != CGC_CLOCK_PLL)
    {
        clock = BSP_CFG_CLOCK_SOURCE;
        err = g_cgc_on_cgc.clockStart(clock, NULL);
    }
    else
    {
        /** Need to start PLL source clock and let it stabilize before starting PLL */
        clock = BSP_CFG_PLL_SOURCE;
        g_cgc_on_cgc.clockStart(clock, NULL);

        cgc_clock_cfg_t pll_cfg;

        /** Set PLL Divider. */
        pll_cfg.divider = BSP_CFG_PLL_DIV;

        /** Set PLL Multiplier. */
        /*LDRA_INSPECTED 90 s float used because float32_t is not part of the C99 standard integer definitions. */
        pll_cfg.multiplier = (float)BSP_CFG_PLL_MUL;

        /** Set PLL Source clock. */
        pll_cfg.source_clock = clock;

        while (SSP_ERR_STABILIZED != g_cgc_on_cgc.clockCheck(clock))
        {
            /** Wait for PLL clock source to stabilize */
        }

        err = g_cgc_on_cgc.clockStart(CGC_CLOCK_PLL, &pll_cfg);

        clock = CGC_CLOCK_PLL;
    }

    /** If the system clock has failed to start call the unrecoverable error handler. */
    if((SSP_SUCCESS != err) && (SSP_ERR_CLOCK_ACTIVE != err))
    {
        BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(0);
    }

    R_ROMC->ROMCE_b.ROMCEN = 1U;         /** Enable ROM cache */

    /** MOCO, LOCO, and subclock do not have stabilization flags that can be checked. */
    if ((CGC_CLOCK_MOCO != clock) && (CGC_CLOCK_LOCO != clock) && (CGC_CLOCK_SUBCLOCK != clock))
    {
        while (SSP_ERR_STABILIZED != g_cgc_on_cgc.clockCheck(clock))
        {
            /** Wait for clock source to stabilize */
        }
    }

    cgc_system_clock_cfg_t sys_cfg;

    sys_cfg.iclk_div  = BSP_CFG_ICK_DIV;
    sys_cfg.pclka_div = BSP_CFG_PCKA_DIV;
    sys_cfg.pclkb_div = BSP_CFG_PCKB_DIV;
    sys_cfg.pclkc_div = BSP_CFG_PCKC_DIV;
    sys_cfg.pclkd_div = BSP_CFG_PCKD_DIV;
    sys_cfg.fclk_div  = BSP_CFG_FCK_DIV;
    sys_cfg.bclk_div  = BSP_CFG_BCK_DIV;

    /** Set which clock to use for system clock and divisors for all system clocks. */
    err = g_cgc_on_cgc.systemClockSet(clock, &sys_cfg);

    /** If the system clock has failed to be configured properly call the unrecoverable error handler. */
    if(SSP_SUCCESS != err)
    {
        BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(0);
    }

    /** Set USB clock divisor. */
    g_cgc_on_cgc.usbClockCfg(BSP_CFG_UCK_DIV);

    /** Configure BCLK */
#if   BSP_CFG_BCLK_OUTPUT == 1
    g_cgc_on_cgc.busClockOutCfg(CGC_BCLOCKOUT_DIV_1);
    g_cgc_on_cgc.busClockOutEnable();
#elif BSP_CFG_BCLK_OUTPUT == 2
    g_cgc_on_cgc.busClockOutCfg(CGC_BCLOCKOUT_DIV_2);
    g_cgc_on_cgc.busClockOutEnable();
#else
    g_cgc_on_cgc.busClockOutDisable();
#endif

    /** Configure SDRAM Clock */
#if   BSP_CFG_SDCLK_OUTPUT == 0
    g_cgc_on_cgc.sdramClockOutDisable();
#else
    g_cgc_on_cgc.sdramClockOutEnable();
#endif
}

/*******************************************************************************************************************//**
 * @brief      Returns frequency of CPU clock in Hz.
 *
 * @retval     Frequency of the CPU in Hertz
 **********************************************************************************************************************/
uint32_t bsp_cpu_clock_get (void)
{
    uint32_t freq = (uint32_t)0;

    g_cgc_on_cgc.systemClockFreqGet(CGC_SYSTEM_CLOCKS_ICLK, &freq);

    return freq;
}

/*******************************************************************************************************************//**
 * @brief      This function sets the value of the ROMWT register which is used to specify wait states required
 *             when accessing Flash ROM.
 * @param[in]  setting The number of wait states to be used.
 * @retval     none
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_clocks_rom_wait_set (uint8_t setting)
{
    R_ROMC->ROMWT_b.ROMWT = (uint8_t)(setting & 0x07);
}

/*******************************************************************************************************************//**
 * @brief      This function gets the value of the ROMWT register
 * @retval     MEMWAIT setting
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t bsp_clocks_rom_wait_get (void)
{
    return (R_ROMC->ROMWT_b.ROMWT);
}

/*******************************************************************************************************************//**
 * @brief      This function sets the RAM wait state settings for the SRAM0, SRAM0 ECC and SRAM1 RAM memory
 * @param[in]  setting The number of wait states to be used.
 * @retval     none
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_clocks_sram_wait_set (uint32_t setting)
{
    R_SRAM->RAMPRCR = CGC_SRAM_UNLOCK;
    R_SRAM->RAMWTSC_b.SRAM0WTEN = (uint8_t)(setting & 0x01);
    R_SRAM->RAMWTSC_b.SRAM1WTEN = (uint8_t)(setting & 0x01);
    R_SRAM->RAMWTSC_b.ECCRAMRDWTEN = (uint8_t)(setting & 0x01);
    R_SRAM->RAMPRCR = CGC_SRAM_LOCK;
}


ssp_err_t bsp_clock_set_callback(bsp_clock_set_callback_args_t * p_args)
{
    static uint8_t new_rom_wait_state = 0U;

    if (BSP_CLOCK_SET_EVENT_PRE_CHANGE == p_args->event)
    {
        uint32_t requested_frequency = p_args->requested_freq_hz;

        /** Wait states for low speed RAM (SRAM0 and SRAM1) */
        /** No wait: ICLK <= 60 MHz */
        /** 1 wait:  ICLK > 60 MHz */
        if (requested_frequency <= CGC_SYS_CLOCK_FREQ_NO_RAM_WAITS)
        {
            bsp_clocks_sram_wait_set(CGC_SRAM_ZERO_WAIT_CYCLES);
        }
        else
        {
            bsp_clocks_sram_wait_set(CGC_SRAM_ONE_WAIT_CYCLES);
        }

        /** Calculate the Wait states for ROM */
        if (requested_frequency <= CGC_SYS_CLOCK_FREQ_ONE_ROM_WAITS)
        {
            new_rom_wait_state = 0U;
        }
        else if (requested_frequency <= CGC_SYS_CLOCK_FREQ_TWO_ROM_WAITS)
        {
            new_rom_wait_state = 1U;
        }
        else
        {
            new_rom_wait_state = 2U;
        }

        if (new_rom_wait_state > bsp_clocks_rom_wait_get())
        {
            /** Set the wait state BEFORE we change iclk */
            bsp_clocks_rom_wait_set(new_rom_wait_state);
        }
    }
    if (BSP_CLOCK_SET_EVENT_POST_CHANGE == p_args->event)
    {
        if (new_rom_wait_state != bsp_clocks_rom_wait_get())
        {
            /** In this case we need to set the wait state AFTER we change iclk */
            bsp_clocks_rom_wait_set(new_rom_wait_state);
        }
    }
    return SSP_SUCCESS;
}

#endif



/** @} (end defgroup BSP_MCU_CLOCKS_S5D9) */
