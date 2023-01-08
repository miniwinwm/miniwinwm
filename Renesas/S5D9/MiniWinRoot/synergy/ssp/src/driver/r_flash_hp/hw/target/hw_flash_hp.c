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
 * File Name    : hw_flash_hp.c
 * Description  : LLD Interface for the FLASH peripheral using RV40F Flash technology on SC32 MCUs.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_flash_hp.h"
#include "hw_flash_hp_private.h"
#include "r_flash_cfg.h"
#include "r_cgc_api.h"
#include "r_cgc.h"

/* Force the optimization to O0 for hardware functions for gcc build to avoid errors caused due to optimization */
#if defined(__GNUC__)
#pragma GCC push_options
#pragma GCC optimize ("O0")
#endif
/*******************************************************************************************************************//**
 * @addtogroup FLASH_HP
 * @{
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @} (end FLASH_HP)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** These typedefs are used for guaranteeing correct accesses to memory. When
 * working with the FCU sometimes byte or word accesses are required. */
typedef  volatile uint8_t *  FCU_BYTE_PTR;
typedef  volatile uint16_t * FCU_WORD_PTR;

typedef volatile struct
{
    uint8_t  FLWE : 2;
    uint8_t       : 6;
} SC32_FWEPROR_BIT_TypeDef;

typedef volatile union
{
    uint8_t  BYTE;
    SC32_FWEPROR_BIT_TypeDef FWEP_BITS;
} SC32_FWEPROR_UNION_TypeDef;


typedef volatile struct
{
  SC32_FWEPROR_UNION_TypeDef  FWEPROR;
} SC32_FWEPROR_TypeDef;

#define                SC32_FWEPROR_BASE (0x4001E416UL)                 /* ( FWEPROR   ) Base Address */
#define                SC32_FWEPROR      (*(SC32_FWEPROR_TypeDef         *) (SC32_FWEPROR_BASE))

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef R_FLASH_HP_SIZEOF_CONFIGURATION_SET
#define R_FLASH_HP_SIZEOF_CONFIGURATION_SET (600U) // Define the maximum compiled size of HW_FLASH_HP_configurationSet.
                                                   // This is used to validate that the function is not in prohibited
                                                   //   regions of memory. 
                                                   // Refer to technical update number TN-SY*-A033A/E for information
                                                   //   regarding prohibited regions of memory.
#endif

#if defined(FLASH_HP_VERSION_PHASE_2)
#ifndef R_FLASH_HP_CHECK_MODULE_STOP_BITS
#define R_FLASH_HP_CHECK_MODULE_STOP_BITS (1U)
#endif
#endif

#define FCU_COMMAND_AREA (0x407E0000UL)
static FCU_BYTE_PTR g_pfcu_cmd_area = (FCU_BYTE_PTR) FCU_COMMAND_AREA;

/** R_FACI Commands */
#define FLASH_FACI_CMD_PROGRAM       0xE8U
#define FLASH_FACI_CMD_PROGRAM_CF    0x80U
#define FLASH_FACI_CMD_PROGRAM_DF    0x02U
#define FLASH_FACI_CMD_BLOCK_ERASE   0x20U
#define FLASH_FACI_CMD_PE_SUSPEND    0xB0U
#define FLASH_FACI_CMD_PE_RESUME     0xD0U
#define FLASH_FACI_CMD_STATUS_CLEAR  0x50U
#define FLASH_FACI_CMD_FORCED_STOP   0xB3U
#define FLASH_FACI_CMD_BLANK_CHECK   0x71U
#define FLASH_FACI_CMD_CONFIG_SET_1  0x40U
#define FLASH_FACI_CMD_CONFIG_SET_2  0x08U
#define FLASH_FACI_CMD_LOCK_BIT_PGM  0x77U
#define FLASH_FACI_CMD_LOCK_BIT_READ 0x71U
#define FLASH_FACI_CMD_FINAL         0xD0U

/**  Configuration set Command offset*/
#if defined(BSP_MCU_GROUP_S7G2)
#define FCU_CONFIG_SET_ID_BYTE              (0x00000050U)
#define FCU_CONFIG_SET_ACCESS_STARTUP       (0x00000060U)
/* Zero based offset into configurationSetArea[] for FSPR (WD1) */
#define FCU_CONFIG_SET_FSPR_OFFSET          1U
#endif

#if defined(FLASH_HP_VERSION_PHASE_2)
#define FCU_CONFIG_SET_ID_BYTE              (0x0000A150U)
#define FCU_CONFIG_SET_ACCESS_STARTUP       (0x0000A160U)
#endif

/* Zero based offset into configurationSetArea[] for FAWS */
#define FCU_CONFIG_SET_FAWS_OFFSET          2U

/* Zero based offset into configurationSetArea[] for FAWE and BTFLG */
#define FCU_CONFIG_SET_FAWE_BTFLG_OFFSET    3U

/* These bits must always be set when writing to the configuration area. */
#define FCU_CONFIG_FAWE_BTFLG_UNUSED_BITS   (0x7800U)
#define FCU_CONFIG_FAWS_UNUSED_BITS         (0xF800U)

#define CONFIG_SET_ACCESS_WORD_CNT          8U             // 8 words need to be written

#define SAS_DEFAULT_AREA                    0x6602U        // Bit value for FSUAC register specifying DEFAULT area
#define SAS_ALTERNATE_AREA                  0x6603U        // Bit value for FSUAC register specifying ALTERNATE area
#define SAS_PER_BTFLG_AREA                  0x6600U        // Bit value for FSUAC register specifying use BTFLG area

/** Register masks */
#define FPESTAT_NON_LOCK_BIT_PGM_ERROR      0x0002U        // Bits indicating Non Lock Bit related Programming error.
#define FPESTAT_NON_LOCK_BIT_ERASE_ERROR    0x0012U        // Bits indicating Non Lock Bit related Erasure error.
#define FENTRYR_DF_PE_MODE                  0x0080U        // Bits indicating that Data Flash is in P/E mode.
#define FENTRYR_CF_PE_MODE                  0x0001U        // Bits indicating that CodeFlash is in P/E mode.
#define FENTRYR_TRANSITION_TO_CF_PE         0xAA01U        // Key Code to transition to CF P/E mode.
#define FENTRYR_TRANSITION_TO_DF_PE         0xAA80U        // Key Code to transition to DF P/E mode.

#define FLASH_FREQUENCY_IN_HZ               (1000000U)

/* The number of CPU cycles per each timeout loop. */
#ifndef R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP
#if defined(__GNUC__)
#define R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP (6U)
#elif defined(__ICCARM__)
#define R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP (6U)
#endif
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static flash_block_info_t     g_hw_block_info = {0};          /// Structure holding block info about an address.
static current_parameters_t * gp_flash_parameters = {0};      /// passed in via flash_init()

static uint16_t configurationSetArea[CONFIG_SET_ACCESS_WORD_CNT] = {0xFFFFU};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
void fcu_fiferr_isr (void);
void fcu_frdyi_isr (void);

/*LDRA_INSPECTED 293 S - This is an allowed exception to LDRA standard 293 S "Non ANSI/ISO construct used." */
/*LDRA_INSPECTED 219 s - This is an allowed exception to LDRA standard 219 S "User name starts with underscore."*/
static ssp_err_t HW_FLASH_HP_configurationSet (R_FACI_Type * p_faci_reg, uint32_t fsaddr) PLACE_IN_RAM_SECTION __attribute__((__noinline__));

/*LDRA_INSPECTED 219 s - This is an allowed exception to LDRA standard 219 S "User name starts with underscore."*/
static ssp_err_t HW_FLASH_HP_operation_status_check (R_FACI_Type * p_faci_reg) PLACE_IN_RAM_SECTION;

/*LDRA_INSPECTED 219 s - This is an allowed exception to LDRA standard 219 S "User name starts with underscore."*/
static ssp_err_t HW_FLASH_HP_erase_next_block (R_FACI_Type * p_faci_reg) PLACE_IN_RAM_SECTION;

/*LDRA_INSPECTED 219 s - This is an allowed exception to LDRA standard 219 S "User name starts with underscore."*/
static void HW_FLASH_HP_configurationSetArea_AccessStartup (uint32_t swap, 
                                                            uint32_t start_addr, 
                                                            uint32_t end_addr) PLACE_IN_RAM_SECTION;

static inline bool HW_FLASH_HP_frdyi_df_bgo_write (flash_hp_instance_ctrl_t *p_ctrl, flash_callback_args_t *p_cb_data);
static inline bool HW_FLASH_HP_frdyi_df_bgo_erase (flash_hp_instance_ctrl_t *p_ctrl, flash_callback_args_t *p_cb_data);

/*LDRA_INSPECTED 219 s - This is an allowed exception to LDRA standard 219 S "User name starts with underscore."*/
static ssp_err_t enter_pe_df_mode(flash_hp_instance_ctrl_t * const p_ctrl) PLACE_IN_RAM_SECTION;

#if (FLASH_CFG_PARAM_CODE_FLASH_PROGRAMMING_ENABLE == 1)
/*LDRA_INSPECTED 219 s - This is an allowed exception to LDRA standard 219 S "User name starts with underscore."*/
static ssp_err_t enter_pe_cf_mode(flash_hp_instance_ctrl_t * const p_ctrl) PLACE_IN_RAM_SECTION;
#endif

static ssp_err_t HW_FLASH_HP_address_checker(uint32_t address);

/*******************************************************************************************************************//**
 * @brief      Checks if address is in a region of prohibited memory. Refer to the S5 series flash technical update.
 *             Technical Update number TN-SY*-A033A/E
 * @param[in]  address         The address to verify
 * @retval     SSP_ERR_INVALID_LINKED_ADDRESS  The address is in a region of memory prone to issues.
 * @retval     SSP_SUCCESS                     The address is safe to use when interacting with the flash configuration registers.
 **********************************************************************************************************************/
static ssp_err_t HW_FLASH_HP_address_checker(uint32_t address)
{
    uint32_t msb = (address >> 24U) & 0xF8U;

    /** If the address being validated is in the prohibited regions of memory return error. */
    if((msb == 0x18U) || (msb == 0x60U) || (msb == 0x80U) || (msb == 0x90U))
    {
        if (((address & 0x0101F800U) == 0x01010000U) || ((address & 0x0101FC00U) == 0x01012000U))
        {
            return SSP_ERR_INVALID_LINKED_ADDRESS;
        }
    }

    /** If the address being validated is in code flash return error. */
    if(address < 0x0400000U)
    {
        return SSP_ERR_INVALID_LINKED_ADDRESS;
    }
    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief      Verifies the addresses required for setting the flash configuration area are valid.
 * @retval     SSP_SUCCESS      Code and data required for setting the configuration area is in valid regions of memory.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_linked_address_check()
{
    ssp_err_t err;

    uint32_t addresses[] = 
    {
        (uint32_t)HW_FLASH_HP_configurationSet, 
        (uint32_t)(((uint32_t)(HW_FLASH_HP_configurationSet)) + R_FLASH_HP_SIZEOF_CONFIGURATION_SET)
    };

    /** Validate the address of the configuration set code and data. */
    for (uint32_t i = 0U; i < (sizeof(addresses) / sizeof(addresses[0U])); i++)
    {
        err = HW_FLASH_HP_address_checker(addresses[i]);
        if(SSP_SUCCESS != err)
        {
            return err;
        }
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief   This function enables or disables the Flash interrupt. The flash interrupt, if enabled, is called when a
 *          Flash operation completes, or when an Error condition is detected. If the caller has provided a callback
 *          function as part of the provided p_cfg pointer, then that function will be called as a result of the
 *          interrupt.
 *          
 * @param[in]  p_faci_reg   Base address of flash registers.
 * @param[in]  p_ctrl       Pointer to the Flash control block
 * @param[in]  state        True ==> interrupts are enabled
 * @param[in]  p_cfg        Pointer to the FLASH configuration structure.
 * @retval SSP_SUCCESS              Successful.
 * @retval SSP_ERR_IRQ_BSP_DISABLED Caller is requesting BGO but the Flash interrupts are not enabled.
 *
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_irq_cfg (R_FACI_Type * p_faci_reg, flash_hp_instance_ctrl_t * p_ctrl, bool state, flash_cfg_t const * const p_cfg)
{
    /* If BGO is being used then we require both interrupts to be enabled (RDY and ERR). If either one
     *  is not enabled then we are not going to be doing BGO and the user will get don't generate any ISR routines */
    /** If both ready and error interrupts are enabled then enable or disable the interrupts based on the state. */
    if ((SSP_INVALID_VECTOR != p_ctrl->irq) && (SSP_INVALID_VECTOR != p_ctrl->err_irq))
    {
        /*Enable the Interrupts*/
        if (true == state)
        {
            /* Enable FCU interrupts if callback is not null, clear the Interrupt Request bit */
            p_faci_reg->FRDYIE = 0x01U;
            R_BSP_IrqStatusClear(p_ctrl->irq);
            NVIC_ClearPendingIRQ(p_ctrl->irq);
            NVIC_EnableIRQ(p_ctrl->irq);

            p_faci_reg->FAEINT = 0x99U;
            R_BSP_IrqStatusClear(p_ctrl->err_irq);
            NVIC_ClearPendingIRQ(p_ctrl->err_irq);
            NVIC_EnableIRQ(p_ctrl->err_irq);
        }
        /* Disable the Interrupts */
        else
        {
            /* Disable interrupt in ICU */
            NVIC_DisableIRQ(p_ctrl->irq);

            /* Disable Flash Rdy interrupt in the FLASH peripheral */
            p_faci_reg->FRDYIE = 0x00U;

            /* Clear the Interrupt Request bit */
            R_BSP_IrqStatusClear(p_ctrl->irq);

            /* Disable interrupt in ICU */
            NVIC_DisableIRQ(p_ctrl->err_irq);

            /* Disable Flash Error interrupt in the FLASH peripheral */
            p_faci_reg->FAEINT = 0x00U;

            /* Clear the Interrupt Request bit */
            R_BSP_IrqStatusClear(p_ctrl->err_irq);
        }
        return SSP_SUCCESS;
    }
    else
    {
        /** The Flash Interrupts have not been enabled. If the caller is requesting BGO then we'll flag this as an error. */
        if (p_cfg->data_flash_bgo == true)
        {
            return SSP_ERR_IRQ_BSP_DISABLED;
        }
        else
        {
            return SSP_SUCCESS;
        }
    }
}

/*******************************************************************************************************************//**
 * @brief   This function will initialize the FCU and set the FCU Clock based on the current FCLK frequency.
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @param[in, out]  p_current_parameters        Pointer to the g_current_parameters structure created by the HLD layer.
 * @retval SSP_SUCCESS        Successful.
 * @retval SSP_ERR_TIMEOUT  Timed out while attempting to switch to P/E mode or
 *                            while trying to issue a STOP or an ongoing flash operation timed out.
 * @retval FLASH_ERR_LOCKED   Switch to Read mode timed out and STOP was attempted to recover. Stop operation failed.
 *                            Flash Peripheral in locked state.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_init (R_FACI_Type * p_faci_reg, current_parameters_t * p_current_parameters)
{
    gp_flash_parameters = p_current_parameters; // our copy from now on

    gp_flash_parameters->current_operation = FLASH_OPERATION_FCU_INIT;

    /*Allow Access to the Flash registers*/
    SC32_FWEPROR.FWEPROR.BYTE = 0x01U;       // Not currently available in the register set.

    /* Round up the frequency to a whole number */
    uint32_t flash_clock_freq_mhz = (gp_flash_parameters->flash_clock_freq + (FLASH_FREQUENCY_IN_HZ - 1)) / FLASH_FREQUENCY_IN_HZ;

    /* Round up the frequency to a whole number */
    uint32_t system_clock_freq_mhz = (gp_flash_parameters->system_clock_freq + (FLASH_FREQUENCY_IN_HZ - 1)) / FLASH_FREQUENCY_IN_HZ;

    /* Set the Clock */
    p_faci_reg->FPCKAR = (uint16_t)((0x1E00UL) + flash_clock_freq_mhz);

    gp_flash_parameters->flash_clock_freq  = gp_flash_parameters->flash_clock_freq / FLASH_FREQUENCY_IN_HZ;  // Scale it down
    gp_flash_parameters->system_clock_freq = gp_flash_parameters->system_clock_freq / FLASH_FREQUENCY_IN_HZ; // Scale it down

    /*  According to HW Manual the Max Programming Time for 256 bytes (ROM)
     *  is 15.8ms.  This is with a FCLK of 4MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    gp_flash_parameters->wait_max_write_cf = (uint32_t) (15800 * system_clock_freq_mhz)/R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Programming Time for 4 bytes
     *  (Data Flash) is 3.8ms.  This is with a FCLK of 4MHz. The calculation
     *  below calculates the number of ICLK ticks needed for the timeout delay.
     */
    gp_flash_parameters->wait_max_write_df = (uint32_t) (3800 * system_clock_freq_mhz)/R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Blank Check time for 4 bytes
     *  (Data Flash) is 84 usec.  This is with a FCLK of 4MHz. The calculation
     *  below calculates the number of ICLK ticks needed for the timeout delay.
     */
    gp_flash_parameters->wait_max_blank_check = (uint32_t) (84 * system_clock_freq_mhz)/R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the max timeout value when using the configuration set
     *  command is 307 ms. This is with a FCLK of 4MHz. The
     *  calculation below calculates the number of ICLK ticks needed for the
     *  timeout delay.
     */
    gp_flash_parameters->wait_max_configuration_set = (uint32_t) (307000 * system_clock_freq_mhz)/R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Erasure Time for a 32KB block is
     *  around 1040ms.  This is with a FCLK of 4MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    gp_flash_parameters->wait_max_erase_cf_large_block = (uint32_t)(1040000 * system_clock_freq_mhz)/R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Erasure Time for a 64 byte Data Flash block is
     *  around 18ms.  This is with a FCLK of 4MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    gp_flash_parameters->wait_max_erase_df_block = (uint32_t) (18000 * system_clock_freq_mhz)/R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    /*  According to HW Manual the Max Erasure Time for a 8KB block is
     *  around 260ms.  This is with a FCLK of 4MHz. The calculation below
     *  calculates the number of ICLK ticks needed for the timeout delay.
     */
    gp_flash_parameters->wait_max_erase_cf_small_block = (uint32_t) (260000 * system_clock_freq_mhz)/R_FLASH_HP_CYCLES_MINIMUM_PER_TIMEOUT_LOOP;

    return SSP_SUCCESS;
}
/*******************************************************************************************************************//**
 * @brief   This function erases a specified number of Code or Data Flash blocks
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @param[in]   block_address   The starting address of the first block to erase.
 * @param[in]   num_blocks      The number of blocks to erase.
 * @retval SSP_SUCCESS            Successfully erased (non-BGO) mode or operation successfully started (BGO).
 * @retval SSP_ERR_ERASE_FAILED   Status is indicating a Erase error.
 * @retval SSP_ERR_CMD_LOCKED     FCU is in locked state, typically as a result of attempting to Write or Erase
 *                                an area that is protected by an Access Window.
 * @retval SSP_ERR_TIMEOUT        Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_erase (R_FACI_Type * p_faci_reg, uint32_t block_address, uint32_t num_blocks)
{
    ssp_err_t err = SSP_SUCCESS;

    /** Set current operation parameters */
    gp_flash_parameters->dest_addr   = block_address;
    gp_flash_parameters->total_count = num_blocks;
    gp_flash_parameters->wait_cnt    = gp_flash_parameters->wait_max_erase_cf_large_block;

    /** Set Erasure Priority Mode*/
    p_faci_reg->FCPSR = (uint16_t)0x0001;

    for (gp_flash_parameters->current_count = 0U;
         gp_flash_parameters->current_count    < gp_flash_parameters->total_count;
         gp_flash_parameters->current_count++)
    {
        /** Set block start address*/
        p_faci_reg->FSADDR = gp_flash_parameters->dest_addr;

        /** Issue two part Block Erase commands */
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_BLOCK_ERASE;
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

        /** If in BGO mode, exit here; remaining processing if any will be done in ISR */
        if (gp_flash_parameters->current_operation == FLASH_OPERATION_DF_BGO_ERASE)
        {
            return err;
        }

        /** Wait until the operation has completed or timeout. If timeout stop the flash and return error. */
        /* Read FRDY bit until it has been set to 1 indicating that the current
         * operation is complete.*/
        while (1U != p_faci_reg->FSTATR_b.FRDY)
        {
            /* Wait until FRDY is 1 unless timeout occurs. */
            if (gp_flash_parameters->wait_cnt == 0U)
            {
                /* if FRDY is not set to 1 after max timeout, issue the stop command */
                HW_FLASH_HP_stop(p_faci_reg);
                return SSP_ERR_TIMEOUT; // Need to indicate an error occured
            }
            gp_flash_parameters->wait_cnt--;
        }

        /** Check the status of the erase operation. If failure return error. */
        err = HW_FLASH_HP_operation_status_check(p_faci_reg);
        if (SSP_SUCCESS != err)
        {
            break;
        }

        /** Configure parameters for next erase command. */
        err = HW_FLASH_HP_erase_next_block(p_faci_reg);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief   This function writes a specified number of bytes to Code or Data Flash.
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @param[in]   src_start_address   The starting address of the first byte (source) to write.
 * @param[in]   dest_start_address  The starting address of the Flash (destination) to write.
 * @param[in]   num_bytes           The number of bytes to write.
 * @retval SSP_SUCCESS            Data successfully written (non-BGO) mode or operation successfully started (BGO).
 * @retval SSP_ERR_ERASE_FAILED   Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED     FCU is in locked state, typically as a result of attempting to Write or Erase
 *                                an area that is protected by an Access Window.
 * @retval SSP_ERR_WRITE_FAILED   Status is indicating a Programming error for the requested operation. This
 *                                may be returned if the requested Flash area is not blank.
 * @retval SSP_ERR_TIMEOUT Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_write (R_FACI_Type * p_faci_reg, uint32_t const * src_start_address, uint32_t * dest_start_address, uint32_t num_bytes)
{
    ssp_err_t err                      = SSP_SUCCESS;

    gp_flash_parameters->total_count   = (num_bytes) >> 1; //Since two bytes will be written at a time
    gp_flash_parameters->dest_addr     = *dest_start_address;
    gp_flash_parameters->src_addr      = *src_start_address;
    gp_flash_parameters->current_count = (uint32_t)0;

    /** Iterate through the number of data bytes */
    while ((gp_flash_parameters->total_count > (uint32_t)0) && (err == SSP_SUCCESS))
    {
        /** Set block start address */
        p_faci_reg->FSADDR = gp_flash_parameters->dest_addr;

        /** Issue two part Write commands */
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_PROGRAM;
        *g_pfcu_cmd_area = (uint8_t) gp_flash_parameters->min_pgm_size;

        /* Write one line (FLASH_MIN_PGM_SIZE_DF bytes for DF, FLASH_MIN_PGM_SIZE_CF bytes for CF) */
        /** Write one line. If timeout Stop the flash and return error. */
        while (gp_flash_parameters->current_count < gp_flash_parameters->min_pgm_size)
        {
            gp_flash_parameters->current_count++;
            /* Copy data from source address to destination area */
            *(FCU_WORD_PTR) g_pfcu_cmd_area = *(uint16_t *) gp_flash_parameters->src_addr;

            while (p_faci_reg->FSTATR_b.DBFULL == (uint32_t)1)
            {
                /* Wait until DBFULL is 0 unless timeout occurs. */
                if (gp_flash_parameters->wait_cnt <= (uint32_t)0)
                {

                    /* if DBFULL is not set to 0 after max timeout, issue the stop command*/
                    HW_FLASH_HP_stop(p_faci_reg);
                    return SSP_ERR_TIMEOUT; // Need to indicate an error occured
                }
                gp_flash_parameters->wait_cnt--;
           }

            gp_flash_parameters->src_addr  += 2U;
            gp_flash_parameters->dest_addr += 2U;
            gp_flash_parameters->total_count--;
        }

        /** Reset current write count. */
        gp_flash_parameters->current_count = (uint32_t)0;

        /** Issue write end command */
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

        /** If in BGO mode, exit here; remaining processing if any will be done in ISR */
        if (gp_flash_parameters->current_operation == FLASH_OPERATION_DF_BGO_WRITE)
        {
            return err;
        }

        /** Set the timeout based on code flash or data flash operation. */
        if (FLASH_OPERATION_CF_WRITE == gp_flash_parameters->current_operation)
        {
            gp_flash_parameters->wait_cnt = gp_flash_parameters->wait_max_write_cf;
        }
        else
        {
            gp_flash_parameters->wait_cnt = gp_flash_parameters->wait_max_write_df;
        }

        /* Read FRDY bit until it has been set to 1 indicating that the current operation is complete.*/
        /** Wait until operation has completed or timeout occurs. If timeout stop the module and return error. */
        while (1U != p_faci_reg->FSTATR_b.FRDY)
        {
            /* Wait until FRDY is 1 unless timeout occurs. */
            if (gp_flash_parameters->wait_cnt <= (uint32_t)0)
            {
                /* if FRDY is not set to 1 after max timeout, issue the stop command */
                HW_FLASH_HP_stop(p_faci_reg);
                return SSP_ERR_TIMEOUT; // Need to indicate an error occured
            }
            gp_flash_parameters->wait_cnt--;
        }

        /** Check the status of the Write operation. If failure return error. */
        err = HW_FLASH_HP_operation_status_check(p_faci_reg);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief   This function checks if the specified Data Flash address range is blank.
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @param[in]   start_address      The starting address of the Flash area to blank check.
 * @param[in]   num_bytes          Specifies the number of bytes that need to be checked.
 * @param[out]  result             Pointer that will be populated by the API with the results of the blank check
 *                                 operation in non-BGO (blocking) mode. In this case the blank check operation
 *                                 completes here and the result is returned. In Data Flash BGO mode the blank check
 *                                 operation is only started here and the result obtained later when the
 *                                 supplied callback routine is called.
 * @retval SSP_SUCCESS             Blankcheck operation completed with result in result,
 *                                 or blankcheck started and in-progess (BGO mode).
 * @retval SSP_ERR_ERASE_FAILED     Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED   FCU is in locked state, typically as a result of having received an illegal
 * command.
 * @retval SSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval SSP_ERR_TIMEOUT Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_blankcheck (R_FACI_Type * p_faci_reg, uint32_t start_address, uint32_t num_bytes, flash_result_t * result)
{
    ssp_err_t err = SSP_SUCCESS;

    /** Set the mode to incremental*/
    p_faci_reg->FBCCNT = 0x00U;

    /** Set the start address for blank checking*/
    p_faci_reg->FSADDR = start_address;

    /** Set the end address for blank checking*/
    p_faci_reg->FEADDR = (start_address + num_bytes) - 1U;

    /** Issue two part Blank Check command*/
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_BLANK_CHECK;
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

    /** If in DF BGO mode, exit here; remaining processing if any will be done in ISR */
    if (gp_flash_parameters->bgo_enabled_df == true)
    {
        *result = FLASH_RESULT_BGO_ACTIVE;
        return err;
    }

    /** Wait for the operation to complete or timeout. If timeout stop the module and return error. */
    /* Read FRDY bit until it has been set to 1 indicating that the current
     * operation is complete. */
    while (1U != p_faci_reg->FSTATR_b.FRDY)
    {
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (gp_flash_parameters->wait_cnt <= (uint32_t)0)
        {
            /* if FRDY is not set to 1 after max timeout, issue the stop command */
            HW_FLASH_HP_stop(p_faci_reg);
            return SSP_ERR_TIMEOUT; // Need to indicate an error occured
        }
        gp_flash_parameters->wait_cnt--;
    }

    /** Check the status of the Blank Check operation. */
    err = HW_FLASH_HP_operation_status_check(p_faci_reg);

    /** Set the result to blank or not blank. */
    if (p_faci_reg->FBCSTAT == 0x01UL)
    {
        *result = FLASH_RESULT_NOT_BLANK;
    }
    else
    {
        *result = FLASH_RESULT_BLANK;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief   This function switches the peripheral to P/E mode for Code Flash or Data Flash.
 * @param[in]   p_ctrl : Pointer to the Flash control block.
 * @param[in]   flash_type : Specifies Code or Data Flash.
 *                           Valid selections are: FLASH_TYPE_CODE_FLASH or FLASH_TYPE_DATA_FLASH
 * @retval SSP_SUCCESS                 Successfully entered P/E mode.
 * @retval SSP_ERR_PE_FAILURE    Failed to enter P/E mode
 *
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_pe_mode_enter (flash_hp_instance_ctrl_t * const p_ctrl, flash_type_t flash_type)
{
    ssp_err_t err = SSP_SUCCESS;

    /** If flash type is data flash enter PE mode for data flash. Otherwise enter PE mode for code flash if enabled. */
    if (flash_type == FLASH_TYPE_DATA_FLASH)
    {
        err = enter_pe_df_mode(p_ctrl);
    }
    else
    {
#if (FLASH_CFG_PARAM_CODE_FLASH_PROGRAMMING_ENABLE == 1)
        err = enter_pe_cf_mode(p_ctrl);
#endif /* if (FLASH_CFG_PARAM_CODE_FLASH_PROGRAMMING_ENABLE == 1) */
    }

    return err;
}


/*******************************************************************************************************************//**
 * @brief   This function switches the peripheral from P/E mode for Code Flash or Data Flash to Read mode.
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @retval SSP_SUCCESS                 Successfully entered P/E mode.
 * @retval SSP_ERR_PE_FAILURE          Failed to exited P/E mode
 * @retval SSP_FLASH_ERR_PARAMETERS    Supplied flash_type was something other than FLASH_TYPE_CODE_FLASH or
 *                                     FLASH_TYPE_DATA_FLASH.
 *
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_pe_mode_exit (flash_hp_instance_ctrl_t * const p_ctrl)
{
    R_FACI_Type * p_faci_reg = p_ctrl->p_reg;
    ssp_err_t         err      = SSP_SUCCESS;
    ssp_err_t         temp_err = SSP_SUCCESS;
    uint32_t pe_mode = p_faci_reg->FENTRYR;

    /* Timeout counter. */
    volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

    /** Wait for current operation to complete or timeout. If timeout return error. */
    /* Read FRDY bit until it has been set to 1 indicating that the current
     * operation is complete.*/
    while (1U != p_faci_reg->FSTATR_b.FRDY)
    {
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (wait_cnt <= (uint32_t)0)
        {
            /* if FRDY is not set to 1 after max timeout, return timeout status*/
            return SSP_ERR_TIMEOUT;
        }
        wait_cnt--;
    }

    /** Check if Command Lock bit is set. */
    if (0U != p_faci_reg->FASTAT_b.CMDLK)
    {
        /*Issue a Status Clear to clear Command Locked state*/
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_STATUS_CLEAR;
        temp_err         = SSP_ERR_CMD_LOCKED;
    }

    wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

    /** Transition to Read mode */
    p_faci_reg->FENTRYR = 0xAA00;

    /** Wait until the flash is in read mode or timeout. If timeout return error. */
    /* Read FENTRYR until it has been set to 0x0000 indicating that we have successfully exited P/E mode.*/
    while (0x0000UL != p_faci_reg->FENTRYR)
    {
        /* Wait until FENTRYR is 0x0000 unless timeout occurs. */
        if (wait_cnt <= (uint32_t)0)
        {
            /* if FENTRYR is not set after max timeout, SSP_ERR_PE_FAILURE*/
            err = SSP_ERR_PE_FAILURE;
        }
        wait_cnt--;
    }

    /** If the device is coming out of code flash p/e mode restore the flash cache state. */
    if(FENTRYR_CF_PE_MODE == pe_mode)
    {
        R_BSP_CacheSet(p_ctrl->cache_state);
    }

    /** If a command locked state was detected earlier, then return that error. */
    if (SSP_ERR_CMD_LOCKED == temp_err)
    {
        return temp_err;
    }
    else
    {
        return err;
    }
}

/*******************************************************************************************************************//**
 * @brief   This function resets the Flash peripheral.
 * @param[in]   p_ctrl -  Pointer to the Flash HP instance control block.
 *
 **********************************************************************************************************************/
void HW_FLASH_HP_reset (flash_hp_instance_ctrl_t *p_ctrl)
{
    /** Disable the FACI interrupts, we don't want the reset itself to generate an interrupt */
    NVIC_DisableIRQ(p_ctrl->irq);
    NVIC_DisableIRQ(p_ctrl->err_irq);

    /** Clear the Interrupt Request */
    R_BSP_IrqStatusClear(p_ctrl->irq);

    /** Clear any pending Rdy interrupt */
    NVIC_ClearPendingIRQ(p_ctrl->irq);

    /** Clear the Interrupt Request */
    R_BSP_IrqStatusClear(p_ctrl->err_irq);

    /** Clear any pending Err interrupt */
    NVIC_ClearPendingIRQ(p_ctrl->err_irq);

    /* If not in PE mode enter PE mode. */
    if (p_ctrl->p_reg->FENTRYR == 0x0000UL)
    {
        /* Enter P/E mode so that we can execute some FACI commands. Either Code or Data Flash P/E mode would work
         * but Code Flash P/E mode requires FLASH_CFG_PARAM_CODE_FLASH_PROGRAMMING_ENABLE ==1, which may not be true */
        HW_FLASH_HP_pe_mode_enter(p_ctrl, FLASH_TYPE_DATA_FLASH);
    }

    /** Issue a Flash Stop to stop any ongoing operation*/
    HW_FLASH_HP_stop(p_ctrl->p_reg);

    /** Issue a status clear to clear the locked-command state*/
    HW_FLASH_HP_status_clear(p_ctrl->p_reg);

    /** Issue a Flash Stop again for a complete RESET*/
    HW_FLASH_HP_stop(p_ctrl->p_reg);

    /** Transition back to Read mode*/
    HW_FLASH_HP_pe_mode_exit(p_ctrl);


    /** If the operation in progress was something that would generate a Data Flash BGO interrupt
     * then reenable interrupts so we'll give a callback for the Reset */
    if ((gp_flash_parameters->bgo_enabled_df == true) &&
        ((gp_flash_parameters->current_operation == FLASH_OPERATION_DF_BGO_ERASE) ||
         (gp_flash_parameters->current_operation == FLASH_OPERATION_DF_BGO_WRITE) ||
         (gp_flash_parameters->current_operation == FLASH_OPERATION_DF_BGO_BLANKCHECK)))
    {
        /* Indicate that we just reset the FCU */
        gp_flash_parameters->current_operation = FLASH_OPERATION_FCU_RESET;

        if (SSP_INVALID_VECTOR != p_ctrl->irq)
        {
            NVIC_EnableIRQ(p_ctrl->irq);           // We are supporting Flash Rdy interrupts for Data Flash operations
        }
        if (SSP_INVALID_VECTOR != p_ctrl->err_irq)
        {
            NVIC_EnableIRQ(p_ctrl->err_irq);       // We are supporting Flash Err interrupts for Data Flash operations
        }
    }

}

/*******************************************************************************************************************//**
 * @brief   This function issues the STOP command and checks the state of the Command Lock bit..
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @retval SSP_SUCCESS           Successful stop.
 * @retval SSP_ERR_TIMEOUT       Timeout executing flash_stop.Failed to exited P/E mode
 * @retval SSP_ERR_CMD_LOCKED    Peripheral in command locked state
 *
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_stop (R_FACI_Type * p_faci_reg)
{
    /* Timeout counter. */
    volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

    /** Issue stop command to flash command area*/
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FORCED_STOP;

    /** Wait until the command has completed or timeout. If timeout return error. */
    /* Read FRDY bit until it has been set to 1 indicating that the current
     * operation is complete.*/
    while (1U != p_faci_reg->FSTATR_b.FRDY)
    {
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (wait_cnt <= (uint32_t)0)
        {
            /* This should not happen normally.
             * FRDY should get set in 15-20 ICLK cycles on STOP command*/
            return SSP_ERR_TIMEOUT;
        }
        wait_cnt--;
   }

    /** Check that Command Lock bit is cleared. If locked return error. */
    if (0U != p_faci_reg->FASTAT_b.CMDLK)
    {
        return SSP_ERR_CMD_LOCKED;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief   This function is used to clear the command-locked state .
 * @param[in]   p_faci_reg       Pointer to the FACI base address register.
 * @retval SSP_SUCCESS           Successful stop.
 * @retval SSP_ERR_TIMEOUT       Timeout executing flash_stop.Failed to exited P/E mode
 * @retval SSP_ERR_CMD_LOCKED    Peripheral in command locked state
 *
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_status_clear (R_FACI_Type * p_faci_reg)
{
    /* Timeout counter. */
    volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

    /*Issue stop command to flash command area*/
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_STATUS_CLEAR;

    /* Read FRDY bit until it has been set to 1 indicating that the current
     * operation is complete.*/
    while (1U != p_faci_reg->FSTATR_b.FRDY)
    {
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (wait_cnt <= (uint32_t)0)
        {
            /* This should not happen normally.
             * FRDY should get set in 15-20 ICLK cycles on STOP command*/
            return SSP_ERR_TIMEOUT;
        }
        wait_cnt--;
   }

    /*Check that Command Lock bit is cleared*/
    if (0U != p_faci_reg->FASTAT_b.CMDLK)
    {
        return SSP_ERR_CMD_LOCKED;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Configure an access window for the Code Flash memory using the provided start and end address. An access
 *         window defines a contiguous area in Code Flash for which programming/erase is enabled. This area is
 *         on block boundaries.
 *         The block containing start_addr is the first block. The block containing end_addr is the last block.
 *         The access window then becomes first block - last block inclusive. Anything outside this range
 *         of Code Flash is then write protected.
 *         This command DOES modify the configuration via The Configuration Set command to update the FAWS and FAWE.
 *
 * @param[in]  p_faci_reg Pointer to the FACI base address register.
 * @param[in]  start_addr Determines the Starting block for the Code Flash access window.
 * @param[in]  end_addr   Determines the Ending block for the Code Flash access window.
 *
 * @retval SSP_SUCCESS                Access window successfully configured.
 * @retval SSP_ERR_ERASE_FAILED        Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED   FCU is in locked state, typically as a result of having received an illegal
 * command.
 * @retval SSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval SSP_ERR_TIMEOUT Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_access_window_set (R_FACI_Type * p_faci_reg, uint32_t const start_addr, uint32_t const end_addr)
{
    uint32_t btflg = p_faci_reg->FAWMON_b.BTFLG;

    /* Configure the configuration area to be written. */
    HW_FLASH_HP_configurationSetArea_AccessStartup (btflg, start_addr >> 13U, end_addr >> 13U);

    /* Write the configuration area to the access/startup region. */
    return HW_FLASH_HP_configurationSet(p_faci_reg, FCU_CONFIG_SET_ACCESS_STARTUP);
}

/*******************************************************************************************************************//**
 * @brief  Remove any access window that is currently configured in the Code Flash.
 *         This command DOES modify the configuration via The Configuration Set command to update the FAWS and FAWE.
 *         Subsequent to this call all Code Flash is writable.
 *
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 *
 * @retval SSP_SUCCESS              Access window successfully removed.
 * @retval SSP_ERR_ERASE_FAILED     Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED   FCU is in locked state, typically as a result of having received an illegal
 * command.
 * @retval SSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval SSP_ERR_TIMEOUT      Timed out waiting for the FCU to become ready.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_access_window_clear (R_FACI_Type * p_faci_reg)
{
    uint32_t btflg = p_faci_reg->FAWMON_b.BTFLG;

    /* Configure the configuration area to be written. */
    HW_FLASH_HP_configurationSetArea_AccessStartup (btflg, 0U, 0U);

    /* Write the configuration area to the access/startup region. */
    return HW_FLASH_HP_configurationSet(p_faci_reg, FCU_CONFIG_SET_ACCESS_STARTUP);
}

/*******************************************************************************************************************//**
 * @brief      Set up the configurationSetArea for writing to the access/startup region of option setting memory.
 *
 * @param[in]  swap            The swap flag
 * @param[in]  start_addr      The access window start address
 * @param[in]  end_addr        The access window end address
 *
 **********************************************************************************************************************/
static void HW_FLASH_HP_configurationSetArea_AccessStartup (uint32_t swap, uint32_t start_addr, uint32_t end_addr)
{
    /* Unused bits should be written as 1. */
    configurationSetArea[0] = 0xFFFFU;
    configurationSetArea[1] = 0xFFFFU;

    /** Prepare the configuration data. */

    /* Bit 15 is BTFLG(Startup Area Select Flag) */
    /* Bits 10:0 are FAWE(Flash Access Window End Block). */
    /* Unused bits should be written as 1. */
    configurationSetArea[FCU_CONFIG_SET_FAWE_BTFLG_OFFSET] = (uint16_t)(FCU_CONFIG_FAWE_BTFLG_UNUSED_BITS | end_addr | (swap << 15U));

    /* Bits 10:0 are FAWS(Flash Access Window Start Block). */
    /* Unused bits should be written as 1. */
    configurationSetArea[FCU_CONFIG_SET_FAWS_OFFSET] = (uint16_t)(FCU_CONFIG_FAWS_UNUSED_BITS | start_addr);

    configurationSetArea[4] = 0xFFFFU;
    configurationSetArea[5] = 0xFFFFU;
    configurationSetArea[6] = 0xFFFFU;
    configurationSetArea[7] = 0xFFFFU;
}

/*******************************************************************************************************************//**
 * @brief      Set the ID code.
 *
 * @param      p_faci_reg                    The p faci register
 * @param      p_id_code                     The identifier code
 *
 * @retval     SSP_SUCCESS                   Set Configuration successful
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_set_id_code (R_FACI_Type * p_faci_reg, uint8_t const * const p_id_code, flash_id_code_mode_t mode)
{
    uint32_t * temp = (uint32_t *)p_id_code;
    uint32_t * temp_area = (uint32_t *)configurationSetArea;

    /** Configure the configuration area to be written. If the mode is unlocked write all 0xFF. */
    for (uint32_t index = 0U; index < 4U; index++)
    {
        if(FLASH_ID_CODE_MODE_UNLOCKED == mode)
        {
            temp_area[index] = 0xFFFFFFFFU;
        }
        else
        {
            temp_area[index] = temp[index];
        }
    }

    /** If the mode is locked with all erase support make sure bits 126 and 127 are set. */
    if(FLASH_ID_CODE_MODE_LOCKED_WITH_ALL_ERASE_SUPPORT == mode)
    {
        configurationSetArea[CONFIG_SET_ACCESS_WORD_CNT - 1U] |= 0xC000U;
    }

    /** If the mode is locked with all erase support make sure bit 127 is set. */
    if(FLASH_ID_CODE_MODE_LOCKED == mode)
    {
        configurationSetArea[CONFIG_SET_ACCESS_WORD_CNT - 1U] |= 0x8000U;
    }

    /** Write the configuration area to the access/startup region. */
    return HW_FLASH_HP_configurationSet(p_faci_reg, FCU_CONFIG_SET_ID_BYTE);
}

/*LDRA_INSPECTED 302 s - Comment contains linker script code to resolve error.*/
/*LDRA_INSPECTED 302 s - Comment contains linker script code to resolve error.*/
/*LDRA_INSPECTED 302 s - Comment contains linker script code to resolve error.*/
/*LDRA_INSPECTED 302 s - Comment contains linker script code to resolve error.*/
/*******************************************************************************************************************//**
 * @brief  Execute the Set Configuration sequence using the configurationSetArea structure set up the caller.
 *
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @param[in]   fsaddr             Flash address to be written to.
 *
 * @retval SSP_SUCCESS                Set Configuration successful
 * @retval SSP_ERR_ERASE_FAILED        Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED   FCU is in locked state, typically as a result of having received an illegal
 * command.
 * @retval SSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval SSP_ERR_TIMEOUT Timed out waiting for the FCU to become ready.
 * @retval SSP_ERR_INVALID_HW_CONDITION The configuration area cannot be written while DTC/DMAC, EDMAC, LCDC/2DG/JPEG
 *                                          are enabled. This is to prevent prohibited memory accesses while the
 *                                          flash sequencer is running. Refer to the technical update  number 
 *                                          TN-SY*-A033A/E. This check can be disabled by defining 
 *                                          R_FLASH_HP_CHECK_MODULE_STOP_BITS to 0.
 *                                          To disable DMAC/DTC, close all modules using DMAC/DTC and do the following:
 *                                              ssp_err_t err;
 *                                              ssp_feature_t ssp_feature = {{(ssp_ip_t) 0U}};
 *                                              ssp_feature.id = SSP_IP_DTC;
 *                                              err = R_BSP_ModuleStopAlways(&ssp_feature);
 *
 **********************************************************************************************************************/
static ssp_err_t HW_FLASH_HP_configurationSet (R_FACI_Type * p_faci_reg, uint32_t fsaddr)
{
    uint32_t old_mask_level = 0U;
    ssp_err_t err = SSP_SUCCESS;

    /* Interrupts must be disabled while writing to the configuration area. This code is used in place of the critical
     * section macro to ensure all interrupts are disabled. If high priority interrupts are allowed and they access
     * prohibited memory regions, the MCU could write to unexpected memory locations. */
    old_mask_level = __get_PRIMASK();
    __set_PRIMASK(1U);

#if R_FLASH_HP_CHECK_MODULE_STOP_BITS
    /* Check the DMAC/DTC Module Stop Bit. */
    uint32_t module_stop = R_SYSTEM->MSTPCRA_b.MSTPA22;
    /* Check the ETHERC0 EDMAC0 Module Stop Bit. */
    module_stop &= R_MSTP->MSTPCRB_b.MSTPB15;
    /* Check the LCDC Module Stop Bit. */
    module_stop &= R_MSTP->MSTPCRC_b.MSTPC4;
    /* Check the JPEG Codec Engine Module Stop Bit. */
    module_stop &= R_MSTP->MSTPCRC_b.MSTPC5;
    /* Check the 2D Drawing Engine Module Stop Bit. */
    module_stop &= R_MSTP->MSTPCRC_b.MSTPC6;

    /* If any modules with direct access to memory are enabled return error. */
    if (0U == module_stop)
    {
        /* Restore interrupts to their previous state. */
        __set_PRIMASK(old_mask_level);

        return SSP_ERR_INVALID_HW_CONDITION;
    }
#endif

    p_faci_reg->FSADDR = fsaddr;
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_CONFIG_SET_1;
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_CONFIG_SET_2;

    /** Write the configuration data. */
    for (uint32_t index = 0U; index < CONFIG_SET_ACCESS_WORD_CNT; index++)
    {
        /* There are 8 16 bit words that must be written to accomplish a configuration set */
        *(FCU_WORD_PTR) g_pfcu_cmd_area = configurationSetArea[index];
    }

    /* While the sequencer is running the bus arbitration method must be set to fixed order. Round robin arbitration
       could result in interacting with prohibited regions of memory. */
#if defined(FLASH_HP_VERSION_PHASE_2)
    uint32_t bus_arbitration_method = R_BUS->BUSSCNTFLI_b.ARBMET;
    R_BUS->BUSSCNTFLI_b.ARBMET = 0U;
#endif

    __asm volatile (
        /* This function is assembly to ensure the CPU does not access prohibited areas during the process of setting
         * the configuration data. */

        /* An exception is granted in this case to allow commented out code.  Commented out equivalent C code is
         * included before each section of assembly code that has a C equivalent.  This is done to improve readability
         * and maintainability.  Commented out equivalent C code is in single line comments with no code on the
         * same line. */
#if defined(__GNUC__)
        ".syntax unified                    \n"
#endif

        /** Issue end command */
        // *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;
        "MOVS  r12, %[cmd_final]            \n"
        "STRB  r12, [%[fcu_cmd_area]]       \n"

        /** Wait for the write to complete or timeout. */
        // while (1U != p_faci_reg->FSTATR_b.FRDY)
        // {
        "LOCAL_CHECK_FRDY:                  \n"
        "LDR   r12, [%[fstatr], #0]         \n"
        /* Get FRDY which is bit 15 */
        "UBFX  r12, R12, #+15, #+1          \n"
        "CMP   r12, #+0                     \n"

        /* If FRDY is 1, then operation has completed. */
        "BNE   LOCAL_SUCCESS                \n"

        /* Check timeout counter. */
        // if (timeout <= (uint32_t)0)
        // {        
        "CMP   %[waitcnt], #+0              \n"

        /* If timeout occurs, set err and exit inline assembly */
        "BEQ   LOCAL_TIMEOUT                \n"

        /* Decrement timeout counter. */
        // timeout--;
        "SUBS  %[waitcnt], %[waitcnt], #+1  \n"
        "B     LOCAL_CHECK_FRDY             \n"

        "LOCAL_TIMEOUT:                     \n"

        /* If FRDY is not 1 after max timeout, set error code so it can be handled. */
        // err = SSP_ERR_TIMEOUT; 
        "MOV   %[retcode], %[errtimeout]    \n"                

        "B     LOCAL_FLASH_EXIT             \n"

        "LOCAL_SUCCESS:                     \n"

        // err = SSP_SUCCESS
        "MOV   %[retcode], %[errsuccess]    \n"                

        "LOCAL_FLASH_EXIT:                  \n"

        /* This is extended assembly syntax.  Refer to the Inline Assembler chapter of the EWARM Development Guide
         * or the Extended Asm chapter of the GCC documentation for syntax references. */
        : /* Output error code. */
          [retcode]      "=r" (err)
        : /* Inputs passed in registers. */
          [fcu_cmd_area] "r" (FCU_COMMAND_AREA),
          [fstatr]       "r" (&p_faci_reg->FSTATR),
          [waitcnt]      "r" (gp_flash_parameters->wait_max_configuration_set), //Prepare our worst case timeout

          /* Immediate constants. */
          [cmd_final]    "I" (FLASH_FACI_CMD_FINAL),
          [errtimeout]   "I" (SSP_ERR_TIMEOUT),
          [errsuccess]   "I" (SSP_SUCCESS)
        : /* Clobbers.  r12 is used as a scratch register and condition codes will be modified. */
          "r12", "cc"
    );

#if defined(FLASH_HP_VERSION_PHASE_2)
    R_BUS->BUSSCNTFLI_b.ARBMET = (0x3U & bus_arbitration_method);
#endif

    /* Restore interrupts to their previous state. */
    __set_PRIMASK(old_mask_level);

    if (SSP_SUCCESS == err)
    {
        /** If no timeout occurred return the status of the configuration set operation. */
        err = HW_FLASH_HP_operation_status_check(p_faci_reg);
    }
    else
    {
        /** If timeout occurred then issue the stop command and return error. */
        HW_FLASH_HP_stop(p_faci_reg);
    }
    return err;
}


/*******************************************************************************************************************//**
 * @brief  Check the status of the current operation.
 *
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 *
 * @retval SSP_SUCCESS             Set Configuration successful
 * @retval SSP_ERR_ERASE_FAILED    Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED      FCU is in locked state, typically as a result of attempting to Write or Erase
 *                                 an area that is protected by an Access Window.
 * @retval SSP_ERR_WRITE_FAILED   Status is indicating a Programming error for the requested operation.
 * @retval SSP_ERR_TIMEOUT        Timed out waiting for the FCU to become ready.
 *
 **********************************************************************************************************************/
static ssp_err_t HW_FLASH_HP_operation_status_check (R_FACI_Type * p_faci_reg)
{
    ssp_err_t err   = SSP_SUCCESS;

    /** If the flash sequencer is not in the command locked state return success. */
    if (0U != p_faci_reg->FASTAT_b.CMDLK)
    {
        /* S5D9 Flash Sequencer does not reference the FPESTAT register */
#if defined(FLASH_HP_VERSION_PHASE_2)
        /* Check if status is indicating a Programming error */
        /** If a programming error occurred return error. */
        if (p_faci_reg->FSTATR_b.PRGERR)
        {
            err = SSP_ERR_WRITE_FAILED;
        }
        /* Check if status is indicating a Erase error */
        /** If an erase error occurred return error. */
        else if (p_faci_reg->FSTATR_b.ERSERR)
        {
            err = SSP_ERR_ERASE_FAILED;
        }
        /** Otherwise return locked error. */
        else
        {
            err = SSP_ERR_CMD_LOCKED;
        }
#else
        /* Check if status is indicating a Programming error */
        /** If a programming error occurred return error. */
        if ((FPESTAT_NON_LOCK_BIT_PGM_ERROR & p_faci_reg->FPESTAT) &&
            ((p_faci_reg->FSTATR_b.PRGERR) || (p_faci_reg->FSTATR_b.ERSERR)))
        {
            err = SSP_ERR_WRITE_FAILED;
        }
        /* Check if status is indicating a Erase error */
        /** If an erase error occurred return error. */
        else if ((FPESTAT_NON_LOCK_BIT_ERASE_ERROR & p_faci_reg->FPESTAT) &&
                ((p_faci_reg->FSTATR_b.PRGERR) || (p_faci_reg->FSTATR_b.ERSERR)))
        {
            err = SSP_ERR_ERASE_FAILED;
        }
        /** Otherwise return locked error. */
        else
        {
            err = SSP_ERR_CMD_LOCKED;
        }
#endif
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief  Increment to the next erase block starting address by adding the appropriate block size.
 *
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 *
 * @retval SSP_SUCCESS                Set Configuration successful
 * @retval SSP_ERR_ERASE_FAILED        Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED   FCU is in locked state, typically as a result of having received an illegal
 * command.
 * @retval SSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval SSP_ERR_TIMEOUT Timed out waiting for the FCU to become ready.
 *
 **********************************************************************************************************************/
static ssp_err_t HW_FLASH_HP_erase_next_block (R_FACI_Type * p_faci_reg)
{
    /** Get the block information about this address. If failure return error. */
    if ((flash_get_block_info(gp_flash_parameters->dest_addr, &g_hw_block_info)) != true)
    {
        return SSP_ERR_INVALID_ADDRESS;
    }

    /** Increment to the next block starting address by adding the appropriate block size. */
    /** Configure timeout based on flash type. */
    gp_flash_parameters->dest_addr += g_hw_block_info.block_size;
    if (p_faci_reg->FENTRYR == FENTRYR_DF_PE_MODE)
    {
        gp_flash_parameters->wait_cnt = gp_flash_parameters->wait_max_erase_df_block;
    }
    else if (p_faci_reg->FENTRYR == FENTRYR_CF_PE_MODE)
    {
        if (g_hw_block_info.block_size > FLASH_CODE_SMALL_BLOCK_SZ)
        {
            gp_flash_parameters->wait_cnt = gp_flash_parameters->wait_max_erase_cf_large_block;
        }
        else
        {
            gp_flash_parameters->wait_cnt = gp_flash_parameters->wait_max_erase_cf_small_block;
        }
    }
    else
    {
        return SSP_ERR_ERASE_FAILED; // should never get here
    }
    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Temporarily sets the startup area to use the DEFAULT or ALTERNATE area as requested.
 * On the next subsequent reset, the startup area will be determined by the state of the BTFLG.
 * This command does NOT modify the configuration via The Configuration Set command, hence these changes are
 * only in effect until the next reset.
 *
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @param[in]   swap_type          The swap type Alternate or Default.
 * @retval SSP_SUCCESS             StartUp area temporarily modified.
 * @note FSUACR register must be set using the full word. Setting the KEY bitfield and SAS bitfields separately will
 * not work.
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_set_startup_area_temporary (R_FACI_Type * p_faci_reg, flash_startup_area_swap_t swap_type)
{
    ssp_err_t err = SSP_SUCCESS;

    /** Set the SAS bit as requested */
    if (FLASH_STARTUP_AREA_BLOCK0 == swap_type)
    {
        p_faci_reg->FSUACR = SAS_DEFAULT_AREA;
    }
    else if (FLASH_STARTUP_AREA_BLOCK1 == swap_type)
    {
        p_faci_reg->FSUACR = SAS_ALTERNATE_AREA;
    }
    else
    {
        p_faci_reg->FSUACR = SAS_PER_BTFLG_AREA;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Modifies the start-up program swap flag (BTFLG) based on the supplied parameters. These changes will
 *        take effect on the next reset. This command DOES modify the configuration via The Configuration
 *        Set command to update the BTFLG.
 *
 * @param[in]   p_faci_reg         Pointer to the FACI base address register.
 * @param[in]   swap_type          The swap type Alternate or Default.
 * @retval SSP_SUCCESS                Access window successfully removed.
 * @retval SSP_ERR_ERASE_FAILED        Status is indicating an erase error. Possibly from a prior operation.
 * @retval SSP_ERR_CMD_LOCKED   FCU is in locked state, typically as a result of having received an illegal
 * command.
 * @retval SSP_ERR_WRITE_FAILED  Status is indicating a Programming error for the requested operation.
 * @retval SSP_ERR_TIMEOUT Timed out waiting for the FCU to become ready.
 *
 **********************************************************************************************************************/
ssp_err_t HW_FLASH_HP_set_startup_area_boot (R_FACI_Type * p_faci_reg, flash_startup_area_swap_t swap_type)
{
    /* Do not call functions with multiple volatile parameters. */
    uint32_t faws = p_faci_reg->FAWMON_b.FAWS;
    uint32_t fawe = p_faci_reg->FAWMON_b.FAWE;

    /* Configure the configuration area to be written. */
    HW_FLASH_HP_configurationSetArea_AccessStartup ((uint8_t)swap_type, faws, fawe);

    /* Write the configuration area to the access/startup region. */
    return HW_FLASH_HP_configurationSet(p_faci_reg, FCU_CONFIG_SET_ACCESS_STARTUP);
}

/*******************************************************************************************************************//**
 * @brief  Handle the FACI frdyi interrupt when the operation is Data Flash BGO write.
 * @param[in]   p_ctrl -  Pointer to the Flash HP instance control block.
 * @param[in]   p_cb_data - Pointer to the Callback function parameter data
 * @retval true, when operation is completed or error has occurred.
 *
 **********************************************************************************************************************/
static inline bool HW_FLASH_HP_frdyi_df_bgo_write (flash_hp_instance_ctrl_t *p_ctrl, flash_callback_args_t *p_cb_data)
{
    uint32_t wait_cnt = FLASH_DBFULL_TIMEOUT;
    bool operation_complete = false;

    /* If there are still bytes to write*/
    if (gp_flash_parameters->total_count > (uint32_t)0)
    {
        /*Set block start address*/
        p_ctrl->p_reg->FSADDR   = gp_flash_parameters->dest_addr;

        /*Issue two part Write commands*/
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_PROGRAM;
        *g_pfcu_cmd_area = (uint8_t) gp_flash_parameters->min_pgm_size;

        /* Write one line (256 for CF, 4 for DF) */
        while (gp_flash_parameters->current_count < gp_flash_parameters->min_pgm_size)
        {
            gp_flash_parameters->current_count++;

            /* Copy data from source address to destination area */
            *(FCU_WORD_PTR) g_pfcu_cmd_area =   *(uint16_t *) gp_flash_parameters->src_addr;
            while (p_ctrl->p_reg->FSTATR_b.DBFULL == 1UL)
            {
                /* Wait until DBFULL is 0 unless timeout occurs. */
                if (wait_cnt <= 0U)
                {
                    /* if DBFULL is not set to 0 after max timeout, reset thr FCU*/
                    HW_FLASH_HP_reset(p_ctrl);
                    p_cb_data->event = FLASH_EVENT_ERR_FAILURE;
                    return(operation_complete);
                }
                wait_cnt--;
           }

            gp_flash_parameters->src_addr  += 2U;
            gp_flash_parameters->dest_addr += 2U;
            gp_flash_parameters->total_count--;
        }

        /*Reset line count*/
        gp_flash_parameters->current_count = 0U;
        /*Issue write end command*/
        *g_pfcu_cmd_area                   = FLASH_FACI_CMD_FINAL;
    }
    /*Done writing all bytes*/
    else
    {
        p_cb_data->event = FLASH_EVENT_WRITE_COMPLETE;
        operation_complete = true;
    }
    return(operation_complete);
}

/*******************************************************************************************************************//**
 * @brief  Handle the FACI frdyi interrupt when the operation is Data Flash BGO erase.
 * @param[in]   p_ctrl -  Pointer to the Flash HP instance control block.
 * @param[in]   p_cb_data - Pointer to the Callback function parameter data
 * @retval true, when operation is completed or error has occurred.
 *
 **********************************************************************************************************************/
static inline bool HW_FLASH_HP_frdyi_df_bgo_erase (flash_hp_instance_ctrl_t *p_ctrl, flash_callback_args_t *p_cb_data)
{
    flash_block_info_t block_info = {0};
    bool operation_complete = false;

    gp_flash_parameters->current_count++;
    if (gp_flash_parameters->current_count < gp_flash_parameters->total_count)
    {
        /*If current mode is Data Flash PE, increment to the next block starting address
         * by adding 64 (DF Block Size) else decrement to the next flash block start address*/
        if (p_ctrl->p_reg->FENTRYR == FENTRYR_DF_PE_MODE)
        {
            gp_flash_parameters->dest_addr += g_flash_data_region.p_block_array->block_size;
        }
        else if (p_ctrl->p_reg->FENTRYR == FENTRYR_CF_PE_MODE)
        {
            /* Get the block information about this address */
            if ((flash_get_block_info(gp_flash_parameters->dest_addr, &block_info)) != true)
            {
                /* Should not get a failure for getting address info...*/
                HW_FLASH_HP_reset(p_ctrl);
                p_cb_data->event = FLASH_EVENT_ERR_FAILURE;
                return(operation_complete);
            }

            gp_flash_parameters->dest_addr += block_info.block_size;
        }

        /*Set block start address*/
        p_ctrl->p_reg->FSADDR   = gp_flash_parameters->dest_addr;

        /*Issue two part Block Erase commands*/
        *g_pfcu_cmd_area = FLASH_FACI_CMD_BLOCK_ERASE;
        *g_pfcu_cmd_area = FLASH_FACI_CMD_FINAL;
    }
    /*If all blocks are erased*/
    else
    {
        p_cb_data->event = FLASH_EVENT_ERASE_COMPLETE;
        operation_complete = true;
    }
    return(operation_complete);
}


/** If BGO is being used then we require both interrupts to be enabled (RDY and ERR). If either one
 *  is not enabled then don't generate any ISR routines */
/*******************************************************************************************************************//**
 * @brief  FLASH error interrupt routine.
 *
 * @details This function implements the FLASH error isr. The function clears the interrupt request source on entry
 *          populates the callback structure with the FLASH_IRQ_EVENT_ERR_ECC event, and providing
 *          a callback routine has been provided, calls the callback function with the event. <br>
 *
 * @retval        none
 **********************************************************************************************************************/
void fcu_fiferr_isr (void)
{
    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE
    flash_callback_args_t cb_data;

    ssp_vector_info_t * p_vector_info = NULL;
    R_SSP_VectorInfoGet(R_SSP_CurrentIrqGet(), &p_vector_info);
    flash_hp_instance_ctrl_t * p_ctrl = (flash_hp_instance_ctrl_t *) *(p_vector_info->pp_ctrl);
    R_FACI_Type * p_faci_reg = p_ctrl->p_reg;

    /* The flash access error interrupt register has fired. */
    /** Check for the data flash memory access violation flag. */
    if (1U == p_faci_reg->FASTAT_b.DFAE)
    {
        cb_data.event = FLASH_EVENT_ERR_DF_ACCESS;
    }
    /** Check for the code flash memory access violation flag. */
    else if (1U == p_faci_reg->FASTAT_b.CFAE)
    {
        cb_data.event = FLASH_EVENT_ERR_CF_ACCESS;
    }
#ifndef FLASH_HP_VERSION_PHASE_2
    /** Check for the 1-bit error correction flag during reading. */
    else if (1U == p_faci_reg->FASTAT_b.ECRCT)
    {
        cb_data.event = FLASH_EVENT_ERR_ONE_BIT;
    }
#endif
    /** Check if the command Lock bit is set. */
    else if (1U == p_faci_reg->FASTAT_b.CMDLK)
    {
    /* S5D9 does not implement the FPESTAT register */
#if defined(FLASH_HP_VERSION_PHASE_2)
        if ((p_faci_reg->FSTATR_b.PRGERR) || (p_faci_reg->FSTATR_b.ERSERR))
        {
            cb_data.event = FLASH_EVENT_ERR_FAILURE;
        }
#else
        if ((FPESTAT_NON_LOCK_BIT_PGM_ERROR & p_faci_reg->FPESTAT)
            && ((p_faci_reg->FSTATR_b.PRGERR) || (p_faci_reg->FSTATR_b.ERSERR)))
        {
            cb_data.event = FLASH_EVENT_ERR_FAILURE;
        }
#endif
        else
        {
            cb_data.event = FLASH_EVENT_ERR_CMD_LOCKED;
        }
    }
    else
    {
        cb_data.event = FLASH_EVENT_ERR_FAILURE;
    }

    /*Reset the FCU: This will stop any existing processes and exit PE mode*/
    HW_FLASH_HP_reset(p_ctrl);
    flash_ReleaseState();

    /** Insure that if we do get a Rdy interrupt subsequent to this error interrupt, that
     *  we don't try to proceed with the operation in progress */
    gp_flash_parameters->current_operation = FLASH_OPERATION_FCU_INIT;

    /** Clear the Ready Interrupt Request */
    R_BSP_IrqStatusClear(p_ctrl->irq);

    /** Clear any pending Rdy interrupt in NVIC */
    NVIC_ClearPendingIRQ(p_ctrl->irq);

    /** Clear the Error Interrupt Request */
    R_BSP_IrqStatusClear(p_ctrl->err_irq);

    /** Call the user callback if configured. */
    if (NULL != p_ctrl->p_callback)
    {
        p_ctrl->p_callback(&cb_data);
    }

    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
}    /* End of function fcu_fiferr_isr() */


/*******************************************************************************************************************//**
 * @brief  FLASH ready interrupt routine.
 *
 * @details This function implements the FLASH ready isr. The function clears the interrupt request source on entry
 *          populates the callback structure with the relevant event, and providing
 *          a callback routine has been provided, calls the callback function with the event. <br>
 *
 * @retval        none
 **********************************************************************************************************************/
void fcu_frdyi_isr (void)
{
    SF_CONTEXT_SAVE
    bool operation_completed = false;

    /*Wait counter used for DBFULL flag*/
    flash_callback_args_t cb_data;

    ssp_vector_info_t * p_vector_info = NULL;
    R_SSP_VectorInfoGet(R_SSP_CurrentIrqGet(), &p_vector_info);
    flash_hp_instance_ctrl_t * p_ctrl = (flash_hp_instance_ctrl_t *) *(p_vector_info->pp_ctrl);
    R_FACI_Type * p_faci_reg = p_ctrl->p_reg;

    /** Clear the Interrupt Request*/
    R_BSP_IrqStatusClear(p_ctrl->irq);

    /* A reset of the FACI with a BGO operation in progress may still generate a single interrupt
     * subsequent to the reset. We want to ignore that */
    /** Continue the current operation. If unknown operation set callback event to failure. */
    if (FLASH_OPERATION_FCU_RESET == gp_flash_parameters->current_operation)
    {
        operation_completed = true;
        cb_data.event = FLASH_EVENT_ERR_FAILURE;
    }
    else if (FLASH_OPERATION_DF_BGO_WRITE == gp_flash_parameters->current_operation)
    {
        operation_completed = HW_FLASH_HP_frdyi_df_bgo_write(p_ctrl, &cb_data);
    }
    else if ((FLASH_OPERATION_DF_BGO_ERASE == gp_flash_parameters->current_operation))
    {
        operation_completed = HW_FLASH_HP_frdyi_df_bgo_erase(p_ctrl, &cb_data);
    }
    else if (FLASH_OPERATION_DF_BGO_BLANKCHECK == gp_flash_parameters->current_operation)
    {
        operation_completed = true;     // Blank check is a single operation
        if (p_faci_reg->FBCSTAT == 0x01UL)
        {
            cb_data.event = FLASH_EVENT_NOT_BLANK;
        }
        else
        {
            cb_data.event = FLASH_EVENT_BLANK;
        }
    }
    else
    {
        /* This case could only be reached by a memory corruption of some type. */
        cb_data.event = FLASH_EVENT_ERR_FAILURE;
    }

    /** If the current operation has completed exit pe mode, release the software lock and call the user callback if used. */
    if (operation_completed == true)
    {
        /* finished current operation. Exit P/E mode*/
        HW_FLASH_HP_pe_mode_exit(p_ctrl);

        /*Release lock and Set current state to Idle*/
        flash_ReleaseState();
        gp_flash_parameters->current_operation = FLASH_OPERATION_IDLE;

        if (NULL != p_ctrl->p_callback)
        {
            /** Set data to identify callback to user, then call user callback. */
            p_ctrl->p_callback(&cb_data);
        }
    }

    SF_CONTEXT_RESTORE
} /* End of function fcu_frdyi_isr() */

/*******************************************************************************************************************//**
 * @brief   This function switches the peripheral to P/E mode for Data Flash.
 * @param[in]   p_ctrl : Pointer to the Flash control block.
 * @retval SSP_SUCCESS           Successfully entered Data Flash P/E mode.
 * @retval SSP_ERR_PE_FAILURE    Failed to enter Data Flash P/E mode.
 *
 **********************************************************************************************************************/
static ssp_err_t enter_pe_df_mode(flash_hp_instance_ctrl_t * const p_ctrl)
{
    ssp_err_t err = SSP_SUCCESS;
    R_FACI_Type * p_faci_reg = (R_FACI_Type *) p_ctrl->p_reg;

    /* Timeout counter. */
    volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

    /** If BGO mode is enabled and interrupts are being used then enable interrupts. */
    if (gp_flash_parameters->bgo_enabled_df == true)
    {
        if (SSP_INVALID_VECTOR != p_ctrl->irq)
        {
            NVIC_EnableIRQ(p_ctrl->irq);           // We are supporting Flash Rdy interrupts for Data Flash operations
        }
        if (SSP_INVALID_VECTOR != p_ctrl->err_irq)
        {
            NVIC_EnableIRQ(p_ctrl->err_irq);       // We are supporting Flash Err interrupts for Data Flash operations
        }
    }
    /** Enter Data Flash PE mode. */
    p_faci_reg->FENTRYR = FENTRYR_TRANSITION_TO_DF_PE;  // Transition to DF P/E mode

    /** Wait for the operation to complete or timeout. If timeout return error. */
    /* Read FENTRYR until it has been set to 0x0080 indicating that we have successfully entered P/E mode.*/
    while (FENTRYR_DF_PE_MODE != p_faci_reg->FENTRYR)
    {
        /* Wait until FENTRYR is 0x0080 unless timeout occurs. */
        if (wait_cnt <= (uint32_t)0)
        {
            /* if FENTRYR is not set after max timeout return an error. */
            return SSP_ERR_PE_FAILURE;
        }
        wait_cnt--;
    }

    return err;
}

#if (FLASH_CFG_PARAM_CODE_FLASH_PROGRAMMING_ENABLE == 1)
/*******************************************************************************************************************//**
 * @brief   This function switches the peripheral to P/E mode for Code Flash.
 * @param[in]   p_ctrl : Pointer to the Flash control block.
 * @retval SSP_SUCCESS           Successfully entered Code Flash P/E mode.
 * @retval SSP_ERR_PE_FAILURE    Failed to enter Code Flash P/E mode.
 *
 **********************************************************************************************************************/
static ssp_err_t enter_pe_cf_mode(flash_hp_instance_ctrl_t * const p_ctrl)
{
    ssp_err_t err = SSP_SUCCESS;
    R_FACI_Type * p_faci_reg = (R_FACI_Type *) p_ctrl->p_reg;

    /* Timeout counter. */
    volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

    /** While the Flash API is in use we will disable the FLash Cache. */
    p_ctrl->cache_state = BSP_CACHE_STATE_OFF;
    R_BSP_CacheOff(&p_ctrl->cache_state);

    /** If interrupts are being used then enable interrupts. */
    if (SSP_INVALID_VECTOR != p_ctrl->irq)
    {
        NVIC_DisableIRQ(p_ctrl->irq);           // We are not supporting Flash Rdy interrupts for Code Flash operations
    }
    if (SSP_INVALID_VECTOR != p_ctrl->err_irq)
    {
        NVIC_DisableIRQ(p_ctrl->err_irq);       // We are not supporting Flash Err interrupts for Code Flash operations
    }

    /** Enter code flash PE mode */
    p_faci_reg->FENTRYR = FENTRYR_TRANSITION_TO_CF_PE;

    /** Wait for the operation to complete or timeout. If timeout return error. */
    /* Read FENTRYR until it has been set to 0x0001 indicating that we have successfully entered CF P/E mode.*/
    while (FENTRYR_CF_PE_MODE != p_faci_reg->FENTRYR)
    {
        /* Wait until FENTRYR is 0x0001UL unless timeout occurs. */
        if (wait_cnt <= (uint32_t)0)
        {
        /* if FENTRYR is not set after max timeout, SSP_ERR_PE_FAILURE*/
        err = SSP_ERR_PE_FAILURE;
        }
        wait_cnt--;
    }
    return err;
}
#endif

#if defined(__GNUC__)
#pragma GCC pop_options
#endif

/*******************************************************************************************************************//**
 * @} (end defgroup FLASH_RV40F)
 **********************************************************************************************************************/
