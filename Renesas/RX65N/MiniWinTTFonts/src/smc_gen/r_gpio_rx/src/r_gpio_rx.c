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
* Copyright (C) 2013-2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx.c
* Description  : General Purpose Input/Output driver for RX MCUs.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 17.07.2013 1.00    First Release
*         : 21.11.2014 1.40    Added support for RX113
*         : 02.09.2015 1.50    Added support for RX71M
*         :                    Modified R_GPIO_PinControl to accept GPIO_CMD_DSCR_ENABLE/_DISABLE commands.
*         : 01.10.2016 2.10    Added support for RX65N
*         :                    Modified R_GPIO_PinControl to accept GPIO_CMD_DSCR2_ENABLE/_DISABLE commands.
*         : 19.12.2016 2.20    Added support for RX24U, RX24T(512KB)
*         : 21.07.2017 2.30    Added support for RX65N-2M, RX130-512KB.
*         : 28.09.2018 2.40    Added support for RX66T.
*                              Update according to GSCE Code Checker
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
/* Public interface header file for this package. */
#include "r_gpio_rx_if.h"
/* Configuration for this package. */
#include "r_gpio_rx_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Different pin output options. */
typedef enum
{
    GPIO_PIN_OUT_CMOS              = 0,
    GPIO_PIN_OUT_OPEN_DRAIN_N_CHAN = 1,
    GPIO_PIN_OUT_OPEN_DRAIN_P_CHAN = 2
} gpio_pin_output_t;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
uint8_t volatile * gpio_port_addr_get(uint8_t volatile * base_addr, uint16_t index);
bool               gpio_pin_function_check(uint8_t const * check_array, uint8_t port_number, uint8_t pin_number);
void               gpio_set_output_type(gpio_port_pin_t pin, gpio_pin_output_t out_type);

#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
    extern const uint8_t g_gpio_open_drain_n_support[];
    extern const uint8_t g_gpio_open_drain_p_support[];
    extern const uint8_t g_gpio_pull_up_support[];
    #if defined (GPIO_DSCR_IS_SUPPORTED)
        extern const uint8_t g_gpio_dscr_support[];
    #endif
    #if defined (GPIO_DSCR2_IS_SUPPORTED)
        extern const uint8_t g_gpio_dscr2_support[];
    #endif
#endif


/***********************************************************************************************************************
* Function Name: R_GPIO_PortWrite
* Description  : Writes the levels of all pins on a port.
* Arguments    : port -
*                    Which port to write to.
*                value -
*                    The value to write to the port. Each bit corresponds to a pin on the port (e.g. bit 0 of value
*                    will be written to pin 0 on supplied port)
* Return Value : none
***********************************************************************************************************************/
void R_GPIO_PortWrite (gpio_port_t port, uint8_t value)
{
    uint8_t volatile * podr;

    /* PODR register addresses are incremental in memory starting with PORT0.PODR. Even if a port is not available
     * on this MCU, the address is reserved. */
    /* Get register address. */
    podr = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_OUTPUT, (uint16_t)port);

    /* Write to the selected port. */
    *podr = value;
} /* End of function R_GPIO_PortWrite */

/***********************************************************************************************************************
* Function Name: R_GPIO_PortRead
* Description  : Reads the levels of all pins on a port.
* Arguments    : port -
*                    Which port to read.
* Return Value : Value of the port
***********************************************************************************************************************/
uint8_t R_GPIO_PortRead (gpio_port_t port)
{
    /* PIDR register addresses are incremental in memory starting with PORT0.PIDR. Even if a port is not available
     * on this MCU, the address is reserved. */

    /* Read the selected port. */
    return *gpio_port_addr_get(GPIO_PRV_BASE_ADDR_INPUT, (uint16_t)port);
} /* End of function R_GPIO_PortRead */

/***********************************************************************************************************************
* Function Name: R_GPIO_PortDirectionSet
* Description  : Sets multiple pins on a port to inputs or outputs at once. Each bit in the mask parameter corresponds
*                to a pin on the port. For example, bit 7 of mask corresponds to pin 7, bit 6 corresponds to pin 6,
*                and so forth. If a bit is set to 1 then the corresponding pin will be changed to an input or output
*                as specified by the dir parameter. If a bit is set to 0 then the direction of the pin will not
*                be changed.
* Arguments    : port -
*                    Which port to read.
*                dir
*                    Which direction to use.
*                mask
*                    Mask of which pins to set to change. 1 = set direction, 0 = do not change.
* Return Value : none
***********************************************************************************************************************/
void R_GPIO_PortDirectionSet (gpio_port_t port, gpio_dir_t dir, uint8_t mask)
{
    uint8_t volatile * pdr;

    /* PDR register addresses are incremental in memory starting with PORT0.PDR. Even if a port is not available
     * on this MCU, the address is reserved. */
    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_DIRECTION, (uint16_t)port);

    /* Write to the selected register. & or | based on direction. */
    if (GPIO_DIRECTION_INPUT == dir)
    {
        /* Set value to port */
        *pdr = (uint8_t)((*pdr) & (~mask));
    }
    else
    {
        /* Set value to port */
        *pdr = (uint8_t)((*pdr) | mask);
    }
} /* End of function R_GPIO_PortDirectionSet */

/***********************************************************************************************************************
* Function Name: R_GPIO_PinWrite
* Description  : Sets the level of a pin.
* Arguments    : pin -
*                    Which pin to use.
*                level
*                    What level to the pin to.
* Return Value : none
***********************************************************************************************************************/
void R_GPIO_PinWrite (gpio_port_pin_t pin, gpio_level_t level)
{
    uint8_t volatile * podr;

    /* PODR register addresses are incremental in memory starting with PORT0.PODR. Even if a port is not available
     * on this MCU, the address is reserved. */
    /* Get register address. */
    podr = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_OUTPUT, (uint16_t)pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_LEVEL_LOW == level)
    {
        /* Set value to port */
        *podr = (uint8_t)((*podr) & (~(1 << (pin & 0x00FFu))));
    }
    else
    {
        /* Set value to port */
        *podr = (uint8_t)((*podr) | (1 << (pin & 0x00FFu)));
    }
} /* End of function R_GPIO_PinWrite */

/***********************************************************************************************************************
* Function Name: R_GPIO_PinRead
* Description  : Reads the level of a pin.
* Arguments    : pin -
*                    Which pin to read.
* Return Value : Level of the pin.
***********************************************************************************************************************/
gpio_level_t R_GPIO_PinRead (gpio_port_pin_t pin)
{
    uint8_t volatile * pidr;

    /* PIDR register addresses are incremental in memory starting with PORT0.PODR. Even if a port is not available
     * on this MCU, the address is reserved. */
    /* Get register address. */
    pidr = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_INPUT, (uint16_t)pin);

    /* Mask to get the individual bit. */
    if (((*pidr) & (1 << (pin & 0x00FFu))) != 0)
    {
        return GPIO_LEVEL_HIGH;
    }
    else
    {
        return GPIO_LEVEL_LOW;
    }
} /* End of function R_GPIO_PinRead */

/***********************************************************************************************************************
* Function Name: R_GPIO_PinDirectionSet
* Description  : Sets the direction of a pin.
* Arguments    : pin -
*                    Which pin to use
*                dir -
*                    Direction to set the pin to. Options are GPIO_DIRECTION_INPUT or GPIO_DIRECTION_OUTPUT.
* Return Value : none
***********************************************************************************************************************/
void R_GPIO_PinDirectionSet (gpio_port_pin_t pin, gpio_dir_t dir)
{
    uint8_t volatile * pdr;

    /* PDR register addresses are incremental in memory starting with PORT0.PDR. Even if a port is not available
     * on this MCU, the address is reserved. */
    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_DIRECTION, (uint16_t)pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_DIRECTION_INPUT == dir)
    {
        /* Casting port address to uint8_t type
         * and set value to port address */
        *pdr = (uint8_t)((*pdr) & (~(1 << (pin & 0x00FFu))));
    }
    else
    {
        /* Casting port address to uint8_t type
         * and set value to port address */
        *pdr = (uint8_t)((*pdr) | (1 << (pin & 0x00FFu)));
    }
} /* End of function R_GPIO_PinDirectionSet */

/***********************************************************************************************************************
* Function Name: R_GPIO_PinControl
* Description  : Provides access to various other pin functions and settings.
* Arguments    : pin -
*                    Which pin to use
*                cmd -
*                    Which command to perform on pin.
* Return Value : GPIO_SUCCESS -
*                    Command executed successfully.
*                GPIO_ERR_INVALID_MODE -
*                    Pin does not support requested mode.
*                GPIO_ERR_INVALID_CMD -
*                    Command that was input is not supported.
***********************************************************************************************************************/
gpio_err_t R_GPIO_PinControl (gpio_port_pin_t pin, gpio_cmd_t cmd)
{
    gpio_err_t         err;
    uint8_t volatile * addr;
    uint8_t            pin_number;

#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
    uint8_t port_number;

    /* Get port number */
    port_number = (uint8_t)(pin >> 8);
#endif

    err = GPIO_SUCCESS;

    /* Get pin number */
    pin_number = (uint8_t)(pin & 0x00FFu);

    switch (cmd)
    {

#if defined (GPIO_DSCR_IS_SUPPORTED)
        case GPIO_CMD_DSCR_ENABLE:
        {
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_dscr_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
#endif
            /* Get pin's address */
            addr = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_DSCR, (uint16_t)pin);

            /* Get value at pin's address */
           *addr   = (uint8_t)((*addr) | (1 << pin_number));
        break;
        }
        case GPIO_CMD_DSCR_DISABLE:
        {
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_dscr_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
#endif
            /* Get pin's address */
            addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_DSCR, (uint16_t)pin);

            /* Get value at pin's address */
            *addr   = (uint8_t)((*addr) & (~(1 << pin_number)));
        break;
        }
#endif  /* GPIO_DSCR_IS_SUPPORTED */
#if defined (GPIO_DSCR2_IS_SUPPORTED)
        case GPIO_CMD_DSCR2_ENABLE:
        {
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_dscr2_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
#endif
            /* Get pin's address */
            addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_DSCR2, (uint16_t)pin);

            /* Set value to pin */
            *addr   = (uint8_t)((*addr) | (1 << pin_number));
        break;
        }

        case GPIO_CMD_DSCR2_DISABLE:
        {
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_dscr2_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
#endif
            /* Get pin's address */
            addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_DSCR2, (uint16_t)pin);

            /* Set value to pin */
            *addr   = (uint8_t)((*addr) & (~(1 << pin_number)));
        break;
        }
#endif  /* GPIO_DSCR2_IS_SUPPORTED */
        case GPIO_CMD_ASSIGN_TO_GPIO:
        {
            /* Get pin's address */
            addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_MODE, (uint16_t)pin);

            /* Set value to pin */
            *addr  = (uint8_t)((*addr) & (~(1 << pin_number)));
        break;
        }

        case GPIO_CMD_ASSIGN_TO_PERIPHERAL:
        {
            /* Get pin's address */
            addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_MODE, (uint16_t)pin);

            /* Set value to pin */
            *addr  = (uint8_t)((*addr) | (1 << pin_number));
        break;
        }

        case GPIO_CMD_IN_PULL_UP_DISABLE:
        {
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_pull_up_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
#endif
            /* Get pin's address */
            addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_PULL_UP, (uint16_t)pin);

            /* Set value to pin */
            *addr  = (uint8_t)((*addr) & (~(1 << pin_number)));
        break;
        }

        case GPIO_CMD_IN_PULL_UP_ENABLE:
        {
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_pull_up_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
#endif
            /* Get pin's address */
            addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_PULL_UP, (uint16_t)pin);

            /* Set value to pin */
            *addr  = (uint8_t)((*addr) | (1 << pin_number));
        break;
        }

        case GPIO_CMD_OUT_CMOS:
        {
            gpio_set_output_type(pin, GPIO_PIN_OUT_CMOS);

        break;
        }

        case GPIO_CMD_OUT_OPEN_DRAIN_N_CHAN:
        {
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_open_drain_n_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
#endif

            gpio_set_output_type(pin, GPIO_PIN_OUT_OPEN_DRAIN_N_CHAN);

        break;
        }
        case GPIO_CMD_OUT_OPEN_DRAIN_P_CHAN:
        #if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
            if (false == gpio_pin_function_check(&g_gpio_open_drain_p_support[0], port_number, pin_number))
            {
                err = GPIO_ERR_INVALID_MODE;
                break;
            }
        #endif
            gpio_set_output_type(pin, GPIO_PIN_OUT_OPEN_DRAIN_P_CHAN);

        break;

        default:
        {
            err = GPIO_ERR_INVALID_CMD;
        break;
        }
    }

    return err;
} /* End of function R_GPIO_PinControl */

/***********************************************************************************************************************
* Function Name: R_GPIO_GetVersion
* Description  : Returns the current version of this module. The version number is encoded where the top 2 bytes are the
*                major version number and the bottom 2 bytes are the minor version number. For example, Version 4.25
*                would be returned as 0x00040019.
* Arguments    : none
* Return Value : Version of this module.
***********************************************************************************************************************/
#pragma inline(R_GPIO_GetVersion)
uint32_t R_GPIO_GetVersion (void)
{
    /* These version macros are defined in r_gpio_rx_if.h. */
    return ((((uint32_t)GPIO_RX_VERSION_MAJOR) << 16) | (uint32_t)GPIO_RX_VERSION_MINOR);
} /* End of function R_GPIO_GetVersion */

/***********************************************************************************************************************
* Function Name: gpio_port_addr_get
* Description  : Get the address for a port register based on a base port register address.
* Arguments    : base_addr -
*                    First port register of this type (e.g. &PORT0.PODR.BYTE)
*                index -
*                    Index off the base. (e.g. for PORT4 it would be 0x0400)
* Return Value : Address of the register that was requested
***********************************************************************************************************************/
#pragma inline(gpio_port_addr_get)
uint8_t volatile * gpio_port_addr_get (uint8_t volatile * base_addr, uint16_t index)
{
    /* Add port number to 'index' to correct register. */
    return (uint8_t volatile *)((((uint32_t)index >> 8) & 0x000000FFuL) + (uint32_t)base_addr);
} /* End of function gpio_port_addr_get */

#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
/***********************************************************************************************************************
* Function Name: gpio_pin_function_check
* Description  : Checks to see if a pin supports a certain function.
* Arguments    : check_array -
*                    Which support array to use.
*                port_number -
*                    Which port to use.
*                pin_number -
*                    Which pin to use.
* Return Value : true -
*                    Functionality is supported on this pin.
*                false -
*                    Functionality is not supported on this pin.
***********************************************************************************************************************/
#pragma inline(gpio_pin_function_check)
bool gpio_pin_function_check (uint8_t const * check_array, uint8_t port_number, uint8_t pin_number)
{
    if ((check_array[port_number] & (1 << pin_number)) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
} /* End of function gpio_pin_function_check */
#endif

/***********************************************************************************************************************
* Function Name: gpio_set_output_type
* Description  : Configures pin output type (e.g. CMOS, open-drain)
* Arguments    : pin -
*                    Which pin to change output type for
*                out_type -
*                    What output type to use for this pin
* Return Value : None
***********************************************************************************************************************/
void gpio_set_output_type (gpio_port_pin_t pin, gpio_pin_output_t out_type)
{
    uint8_t volatile * addr;
    uint8_t            pin_number;
    uint8_t            bit_offset;

    /* Get pin number */
    pin_number = (uint8_t)(pin & 0x00FFu);

    /* 'pin' is multiplied by 2 because the ODR0 and ODR1 registers are staggered. This means that PORT0.ODR0
     * and PORT1.ODR0 are separated by 2 bytes instead of 1 as with the other port registers. */
    addr   = gpio_port_addr_get(GPIO_PRV_BASE_ADDR_OUT_TYPE, (uint16_t)(((uint16_t)pin)*2));

    /* ODR bit fields are 2-bits a piece. This means bits 0-3 are in the 1st byte (ODR0) and bits 4-7 are in
     * the 2nd byte (ODR1).
     */
    if (pin_number > 3)
    {
        /* Bit field is in ODR1. Increment address by 1 for ODR1 register for this port. */
        addr += 1;

        /* Subtract 4 from pin number since pins 4-7 are stored in ODR1 which is an 8-bit register.
         * Multiple pin number by 2 since each pin is represented by 2 bits.
         */
        bit_offset = (uint8_t)((pin_number - 4) * 2);
    }
    else
    {
        /* Multiple pin number by 2 since each pin is represented by 2 bits. */
        bit_offset = (uint8_t)(pin_number * 2);
    }

    /* Clear the bits we intend to change. */
    *addr = (uint8_t)((*addr) & (~(3 << bit_offset)));

    /* Set the bits again if needed. */
    *addr = (uint8_t)((*addr) | (((uint8_t)out_type) << bit_offset));
} /* End of function gpio_set_output_type */
