/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** ThreadX Component                                                     */
/**                                                                       */
/**   Port Specific                                                       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** This file selects ThreadX port specific information based on the MCU  */
/** and compiler selected.                                                */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#ifndef TX_PORT_H_TOP_LEVEL
#define TX_PORT_H_TOP_LEVEL

#define TX_INCLUDE_USER_DEFINE_FILE
#if   defined(__IAR_SYSTEMS_ICC__)
    #if   (__CORE__ == __ARM7EM__)
        #include "./cm4_iar/tx_port.h"
    #elif (__CORE__ == __ARM6M__)
        #include "./cm0plus_iar/tx_port.h"
    #elif (__CORE__ == __ARM8M_BASELINE__)
        #include "./cm23_iar/tx_port.h"
    #else
        #warning Unsupported Architecture
    #endif
#elif defined(__GNUC__)
    #if   __ARM_ARCH_7EM__
        #include "./cm4_gcc/tx_port.h"
    #elif __ARM_ARCH_6M__
        #include "./cm0plus_gcc/tx_port.h"
    #elif __ARM_ARCH_8M_BASE__
        #include "./cm23_gcc/tx_port.h"
    #else
        #warning Unsupported Architecture
    #endif
#else
    #warning Unsupported compiler
#endif

#if   defined(__IAR_SYSTEMS_ICC__)
#define TX_FUNCTION_NAKED __stackless
#elif defined(__GNUC__)
#define TX_FUNCTION_NAKED __attribute__((naked))
#else
    #warning Unsupported compiler
#endif

#endif /* TX_PORT_H_TOP_LEVEL */
