/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "pin_mux.h"

#define IOCON_PIO_DIGITAL_EN        0x0100u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC2               0x02u   /*!< Selects pin function 2 */
#define IOCON_PIO_INPFILT_OFF       0x0200u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_FAST         0x0400u   /*!< Fast mode, slew rate control is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in port 2 */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in port 2 */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in port 2 */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in port 2 */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in port 2 */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in port 2 */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in port 2 */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in port 2 */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in port 3 */
#define PORT2_IDX                        2u   /*!< Port index */
#define PORT3_IDX                        3u   /*!< Port index */

void BOARD_InitPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    const uint32_t port2_pin10_config = (/* Pin is configured as SD_CARD_DET_N */
      									 IOCON_PIO_FUNC2 |      
										 /* No addition pin function */                                  
      									 IOCON_PIO_MODE_INACT |       
										 /* Input function is not inverted */                            
      									 IOCON_PIO_INV_DI |                
										 /* Enables digital function */                       
      									 IOCON_PIO_DIGITAL_EN |          
										 /* Input filter disabled */                         
      									 IOCON_PIO_INPFILT_OFF |    
										 /* Standard mode, output slew rate control is enabled */                              
      									 IOCON_PIO_SLEW_STANDARD |    
										 /* Open drain is disabled */                            
      									 IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT2 PIN10 (coords: P1) is configured as SD_CARD_DET_N */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN10_IDX, port2_pin10_config); 

    const uint32_t port2_pin3_config = (/* Pin is configured as SD_CLK */			
      									 IOCON_PIO_FUNC2 |        
										 /* No addition pin function */                                
      									 IOCON_PIO_MODE_INACT |       
										 /* Input function is not inverted */                            
      									 IOCON_PIO_INV_DI |          
										 /* Enables digital function */                             
      									 IOCON_PIO_DIGITAL_EN |           
										 /* Input filter disabled */                        
      									 IOCON_PIO_INPFILT_OFF |             
										 /* Fast mode, slew rate control is disabled */                     
      									 IOCON_PIO_SLEW_FAST |      
										 /* Open drain is disabled */                              
      									 IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT2 PIN3 (coords: B1) is configured as SD_CLK */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN3_IDX, port2_pin3_config); 
    
	const uint32_t port2_pin4_config = (/* Pin is configured as SD_CMD */
      									 IOCON_PIO_FUNC2 |    
                						 /* No addition pin function */                    
      									 IOCON_PIO_MODE_INACT |                                   
										 /* Input function is not inverted */
      									 IOCON_PIO_INV_DI |        
                               			 /* Enables digital function */
      									 IOCON_PIO_DIGITAL_EN |     
                              			 /* Input filter disabled */
      									 IOCON_PIO_INPFILT_OFF |  
                                		 /* Fast mode, slew rate control is disabled */
      									 IOCON_PIO_SLEW_FAST |      
                              			 /* Open drain is disabled */
      									 IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT2 PIN4 (coords: D3) is configured as SD_CMD */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN4_IDX, port2_pin4_config); 

    const uint32_t port2_pin5_config = (/* Pin is configured as SD_POW_EN */
      									 IOCON_PIO_FUNC2 |       
                                 		 /* No addition pin function */
      									 IOCON_PIO_MODE_INACT |     
                              			 /* Input function is not inverted */
      									 IOCON_PIO_INV_DI |       
                              			 /* Enables digital function */  
      									 IOCON_PIO_DIGITAL_EN | 
                                  		 /* Input filter disabled */
      									 IOCON_PIO_INPFILT_OFF |           
                       					 /* Standard mode, output slew rate control is enabled */
      									 IOCON_PIO_SLEW_STANDARD |       
                         				 /* Open drain is disabled */
      									 IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT2 PIN5 (coords: C1) is configured as SD_POW_EN */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN5_IDX, port2_pin5_config); 

    const uint32_t port2_pin6_config = (/* Pin is configured as SD_D(0) */
      								  	 IOCON_PIO_FUNC2 |   
                         				 /* No addition pin function */            
      									 IOCON_PIO_MODE_INACT |  
                                 		 /* Input function is not inverted */
      									 IOCON_PIO_INV_DI |  
                                      	 /* Enables digital function */
      									 IOCON_PIO_DIGITAL_EN |      
                            			 /* Input filter disabled */
      									 IOCON_PIO_INPFILT_OFF |        
                          				 /* Fast mode, slew rate control is disabled */
      									 IOCON_PIO_SLEW_FAST |   
                                 		 /* Open drain is disabled */
      									 IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT2 PIN6 (coords: F3) is configured as SD_D(0) */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN6_IDX, port2_pin6_config); 

    const uint32_t port2_pin7_config = (/* Pin is configured as SD_D(1) */
      									 IOCON_PIO_FUNC2 |        
                                		 /* No addition pin function */
      									 IOCON_PIO_MODE_INACT | 
                                  		 /* Input function is not inverted */
      									 IOCON_PIO_INV_DI |  
                                      	 /* Enables digital function */
      									 IOCON_PIO_DIGITAL_EN |      
                            			 /* Input filter disabled */
      									 IOCON_PIO_INPFILT_OFF |       
                           				 /* Fast mode, slew rate control is disabled */
      									 IOCON_PIO_SLEW_FAST |        
                            			 /* Open drain is disabled */
      									 IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT2 PIN7 (coords: J2) is configured as SD_D(1) */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN7_IDX, port2_pin7_config); 

    const uint32_t port2_pin8_config = (/* Pin is configured as SD_D(2) */
      									IOCON_PIO_FUNC2 |  
										/* No addition pin function */
      									IOCON_PIO_MODE_INACT |   
                                      	/* Input function is not inverted */
      									IOCON_PIO_INV_DI |       
                                		/* Enables digital function */
      									IOCON_PIO_DIGITAL_EN |   
                                		/* Input filter disabled */
      									IOCON_PIO_INPFILT_OFF | 
                                		/* Fast mode, slew rate control is disabled */
      									IOCON_PIO_SLEW_FAST |   
                                        /* Open drain is disabled */
      									IOCON_PIO_OPENDRAIN_DI                                   
    								   );
	/* PORT2 PIN8 (coords: F4) is configured as SD_D(2) */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN8_IDX, port2_pin8_config); 

    const uint32_t port2_pin9_config = (/* Pin is configured as SD_D(3) */
      									IOCON_PIO_FUNC2 |       
                                 		/* No addition pin function */
      									IOCON_PIO_MODE_INACT |         
                          				/* Input function is not inverted */
      									IOCON_PIO_INV_DI |    
                                   		/* Enables digital function */
      									IOCON_PIO_DIGITAL_EN |   
                                		/* Input filter disabled */
      									IOCON_PIO_INPFILT_OFF |          
                        				/* Fast mode, slew rate control is disabled */
      									IOCON_PIO_SLEW_FAST |    
                                		/* Open drain is disabled */
      									IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT2 PIN9 (coords: K2) is configured as SD_D(3) */
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN9_IDX, port2_pin9_config); 

    const uint32_t port3_pin15_config = (/* Pin is configured as SD_WR_PRT */
      									 IOCON_PIO_FUNC2 |   
                                     	 /* No addition pin function */
      									 IOCON_PIO_MODE_INACT |    
                               			 /* Input function is not inverted */
      									 IOCON_PIO_INV_DI |     
                                  		 /* Enables digital function */
      									 IOCON_PIO_DIGITAL_EN |    
                               			 /* Input filter disabled */
      									 IOCON_PIO_INPFILT_OFF |          
                        				 /* Standard mode, output slew rate control is enabled */
      									 IOCON_PIO_SLEW_STANDARD |      
                          				 /* Open drain is disabled */
      									 IOCON_PIO_OPENDRAIN_DI                                   
    									);
	/* PORT3 PIN15 (coords: D2) is configured as SD_WR_PRT */
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN15_IDX, port3_pin15_config); 

    const uint32_t port3_pin23_config = (/* Pin is configured as FC2_CTS_SDA_SSEL0 */
                                         IOCON_PIO_FUNC1 |
                                         /* I2C mode */
                                         IOCON_PIO_I2CSLEW_I2C |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* High drive: 20 mA */
                                         IOCON_PIO_I2CDRIVE_HIGH |
                                         /* I2C 50 ns glitch filter enabled */
                                         IOCON_PIO_I2CFILTER_EN);
     /* PORT3 PIN23 (coords: C2) is configured as FC2_CTS_SDA_SSEL0 */
     IOCON_PinMuxSet(IOCON, 3U, 23U, port3_pin23_config);

     const uint32_t port3_pin24_config = (/* Pin is configured as FC2_RTS_SCL_SSEL1 */
                                          IOCON_PIO_FUNC1 |
                                          /* I2C mode */
                                          IOCON_PIO_I2CSLEW_I2C |
                                          /* Input function is not inverted */
                                          IOCON_PIO_INV_DI |
                                          /* Enables digital function */
                                          IOCON_PIO_DIGITAL_EN |
                                          /* Input filter disabled */
                                          IOCON_PIO_INPFILT_OFF |
                                          /* High drive: 20 mA */
                                          IOCON_PIO_I2CDRIVE_HIGH |
                                          /* I2C 50 ns glitch filter enabled */
                                          IOCON_PIO_I2CFILTER_EN);
     /* PORT3 PIN24 (coords: E2) is configured as FC2_RTS_SCL_SSEL1 */
     IOCON_PinMuxSet(IOCON, 3U, 24U, port3_pin24_config);

    const uint32_t port3_pin31_config = (
    									 IOCON_PIO_FUNC2 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    IOCON_PinMuxSet(IOCON, 3U, 31U, port3_pin31_config);

    const uint32_t port0_pin15_config = (/* Pin is configured as EMC_WEN */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN15 (coords: L4) is configured as EMC_WEN */
    IOCON_PinMuxSet(IOCON, 0U, 15U, port0_pin15_config);

    const uint32_t port0_pin18_config = (/* Pin is configured as EMC_A(0) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN18 (coords: C14) is configured as EMC_A(0) */
    IOCON_PinMuxSet(IOCON, 0U, 18U, port0_pin18_config);

    const uint32_t port0_pin19_config = (/* Pin is configured as EMC_A(1) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN19 (coords: C6) is configured as EMC_A(1) */
    IOCON_PinMuxSet(IOCON, 0U, 19U, port0_pin19_config);

    const uint32_t port0_pin2_config = (/* Pin is configured as EMC_D(0) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN2 (coords: E9) is configured as EMC_D(0) */
    IOCON_PinMuxSet(IOCON, 0U, 2U, port0_pin2_config);

    const uint32_t port0_pin20_config = (/* Pin is configured as EMC_A(2) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN20 (coords: D13) is configured as EMC_A(2) */
    IOCON_PinMuxSet(IOCON, 0U, 20U, port0_pin20_config);

    const uint32_t port0_pin21_config = (/* Pin is configured as EMC_A(3) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN21 (coords: C13) is configured as EMC_A(3) */
    IOCON_PinMuxSet(IOCON, 0U, 21U, port0_pin21_config);

    const uint32_t port0_pin3_config = (/* Pin is configured as EMC_D(1) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN3 (coords: A10) is configured as EMC_D(1) */
    IOCON_PinMuxSet(IOCON, 0U, 3U, port0_pin3_config);

    const uint32_t port0_pin30_config = (/* Pin is configured as FC0_TXD_SCL_MISO */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN30 (coords: A2) is configured as FC0_TXD_SCL_MISO */
    IOCON_PinMuxSet(IOCON, 0U, 30U, port0_pin30_config);

    const uint32_t port0_pin4_config = (/* Pin is configured as EMC_D(2) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN4 (coords: C8) is configured as EMC_D(2) */
    IOCON_PinMuxSet(IOCON, 0U, 4U, port0_pin4_config);

    const uint32_t port0_pin5_config = (/* Pin is configured as EMC_D(3) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN5 (coords: E7) is configured as EMC_D(3) */
    IOCON_PinMuxSet(IOCON, 0U, 5U, port0_pin5_config);

    const uint32_t port0_pin6_config = (/* Pin is configured as EMC_D(4) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN6 (coords: A5) is configured as EMC_D(4) */
    IOCON_PinMuxSet(IOCON, 0U, 6U, port0_pin6_config);

    const uint32_t port0_pin7_config = (/* Pin is configured as EMC_D(5) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN7 (coords: H12) is configured as EMC_D(5) */
    IOCON_PinMuxSet(IOCON, 0U, 7U, port0_pin7_config);

    const uint32_t port0_pin8_config = (/* Pin is configured as EMC_D(6) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN8 (coords: H10) is configured as EMC_D(6) */
    IOCON_PinMuxSet(IOCON, 0U, 8U, port0_pin8_config);

    const uint32_t port0_pin9_config = (/* Pin is configured as EMC_D(7) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN9 (coords: G12) is configured as EMC_D(7) */
    IOCON_PinMuxSet(IOCON, 0U, 9U, port0_pin9_config);

    const uint32_t port1_pin10_config = (/* Pin is configured as EMC_RASN */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN10 (coords: N9) is configured as EMC_RASN */
    IOCON_PinMuxSet(IOCON, 1U, 10U, port1_pin10_config);

    const uint32_t port1_pin11_config = (/* Pin is configured as EMC_CLK(0) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN11 (coords: B4) is configured as EMC_CLK(0) */
    IOCON_PinMuxSet(IOCON, 1U, 11U, port1_pin11_config);

    const uint32_t port1_pin12_config = (/* Pin is configured as EMC_DYCSN(0) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN12 (coords: K9) is configured as EMC_DYCSN(0) */
    IOCON_PinMuxSet(IOCON, 1U, 12U, port1_pin12_config);

    const uint32_t port1_pin13_config = (/* Pin is configured as EMC_DQM(0) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN13 (coords: G10) is configured as EMC_DQM(0) */
    IOCON_PinMuxSet(IOCON, 1U, 13U, port1_pin13_config);

    const uint32_t port1_pin14_config = (/* Pin is configured as EMC_DQM(1) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN14 (coords: C12) is configured as EMC_DQM(1) */
    IOCON_PinMuxSet(IOCON, 1U, 14U, port1_pin14_config);

    const uint32_t port1_pin15_config = (/* Pin is configured as EMC_CKE(0) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN15 (coords: A11) is configured as EMC_CKE(0) */
    IOCON_PinMuxSet(IOCON, 1U, 15U, port1_pin15_config);

    const uint32_t port1_pin16_config = (/* Pin is configured as EMC_A(10) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN16 (coords: B7) is configured as EMC_A(10) */
    IOCON_PinMuxSet(IOCON, 1U, 16U, port1_pin16_config);

    const uint32_t port1_pin19_config = (/* Pin is configured as EMC_D(8) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN19 (coords: L1) is configured as EMC_D(8) */
    IOCON_PinMuxSet(IOCON, 1U, 19U, port1_pin19_config);

    const uint32_t port1_pin20_config = (/* Pin is configured as EMC_D(9) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN20 (coords: M1) is configured as EMC_D(9) */
    IOCON_PinMuxSet(IOCON, 1U, 20U, port1_pin20_config);

    const uint32_t port1_pin21_config = (/* Pin is configured as EMC_D(10) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN21 (coords: N8) is configured as EMC_D(10) */
    IOCON_PinMuxSet(IOCON, 1U, 21U, port1_pin21_config);

    const uint32_t port1_pin23_config = (/* Pin is configured as EMC_A(11) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN23 (coords: M10) is configured as EMC_A(11) */
    IOCON_PinMuxSet(IOCON, 1U, 23U, port1_pin23_config);

    const uint32_t port1_pin24_config = (/* Pin is configured as EMC_A(12) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN24 (coords: N14) is configured as EMC_A(12) */
    IOCON_PinMuxSet(IOCON, 1U, 24U, port1_pin24_config);

    const uint32_t port1_pin25_config = (/* Pin is configured as EMC_A(13) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN25 (coords: M12) is configured as EMC_A(13) */
    IOCON_PinMuxSet(IOCON, 1U, 25U, port1_pin25_config);

    const uint32_t port1_pin26_config = (/* Pin is configured as EMC_A(8) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN26 (coords: J10) is configured as EMC_A(8) */
    IOCON_PinMuxSet(IOCON, 1U, 26U, port1_pin26_config);

    const uint32_t port1_pin27_config = (/* Pin is configured as EMC_A(9) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN27 (coords: F10) is configured as EMC_A(9) */
    IOCON_PinMuxSet(IOCON, 1U, 27U, port1_pin27_config);

    const uint32_t port1_pin28_config = (/* Pin is configured as EMC_D(12) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN28 (coords: E12) is configured as EMC_D(12) */
    IOCON_PinMuxSet(IOCON, 1U, 28U, port1_pin28_config);

    const uint32_t port1_pin29_config = (/* Pin is configured as EMC_D(13) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN29 (coords: C11) is configured as EMC_D(13) */
    IOCON_PinMuxSet(IOCON, 1U, 29U, port1_pin29_config);

    const uint32_t port1_pin30_config = (/* Pin is configured as EMC_D(14) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN30 (coords: A8) is configured as EMC_D(14) */
    IOCON_PinMuxSet(IOCON, 1U, 30U, port1_pin30_config);

    const uint32_t port1_pin31_config = (/* Pin is configured as EMC_D(15) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN31 (coords: C5) is configured as EMC_D(15) */
    IOCON_PinMuxSet(IOCON, 1U, 31U, port1_pin31_config);

    const uint32_t port1_pin4_config = (/* Pin is configured as EMC_D(11) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN4 (coords: D4) is configured as EMC_D(11) */
    IOCON_PinMuxSet(IOCON, 1U, 4U, port1_pin4_config);

    const uint32_t port1_pin5_config = (/* Pin is configured as EMC_A(4) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN5 (coords: E4) is configured as EMC_A(4) */
    IOCON_PinMuxSet(IOCON, 1U, 5U, port1_pin5_config);

    const uint32_t port1_pin6_config = (/* Pin is configured as EMC_A(5) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN6 (coords: G4) is configured as EMC_A(5) */
    IOCON_PinMuxSet(IOCON, 1U, 6U, port1_pin6_config);

    const uint32_t port1_pin7_config = (/* Pin is configured as EMC_A(6) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN7 (coords: N1) is configured as EMC_A(6) */
    IOCON_PinMuxSet(IOCON, 1U, 7U, port1_pin7_config);

    const uint32_t port1_pin8_config = (/* Pin is configured as EMC_A(7) */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN8 (coords: P8) is configured as EMC_A(7) */
    IOCON_PinMuxSet(IOCON, 1U, 8U, port1_pin8_config);

    const uint32_t port1_pin9_config = (/* Pin is configured as EMC_CASN */
                                        IOCON_PIO_FUNC6 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Fast mode, slew rate control is disabled */
                                        IOCON_PIO_SLEW_FAST |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN9 (coords: K6) is configured as EMC_CASN */
    IOCON_PinMuxSet(IOCON, 1U, 9U, port1_pin9_config);

    const uint32_t port3_pin25_config = (/* Pin is configured as EMC_A(14) */
                                         IOCON_PIO_FUNC6 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Fast mode, slew rate control is disabled */
                                         IOCON_PIO_SLEW_FAST |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN25 (coords: P9) is configured as EMC_A(14) */
    IOCON_PinMuxSet(IOCON, 3U, 25U, port3_pin25_config);

    const uint32_t port0_pin29_config = (/* Pin is configured as FC0_RXD_SDA_MOSI */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN29 (coords: B13) is configured as FC0_RXD_SDA_MOSI */
    IOCON_PinMuxSet(IOCON, 0U, 29U, port0_pin29_config);

    const uint32_t port2_pin11_config = (/* Pin is configured as LCD_PWR */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN11 (coords: K3) is configured as LCD_PWR */
    IOCON_PinMuxSet(IOCON, 2U, 11U, port2_pin11_config);

    const uint32_t port2_pin13_config = (/* Pin is configured as LCD_DCLK */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN13 (coords: P7) is configured as LCD_DCLK */
    IOCON_PinMuxSet(IOCON, 2U, 13U, port2_pin13_config);

    const uint32_t port2_pin14_config = (/* Pin is configured as LCD_FP */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN14 (coords: L7) is configured as LCD_FP */
    IOCON_PinMuxSet(IOCON, 2U, 14U, port2_pin14_config);

    const uint32_t port2_pin15_config = (/* Pin is configured as LCD_AC */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN15 (coords: M8) is configured as LCD_AC */
    IOCON_PinMuxSet(IOCON, 2U, 15U, port2_pin15_config);

    const uint32_t port2_pin16_config = (/* Pin is configured as LCD_LP */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN16 (coords: L8) is configured as LCD_LP */
    IOCON_PinMuxSet(IOCON, 2U, 16U, port2_pin16_config);

    const uint32_t port2_pin21_config = (/* Pin is configured as LCD_VD(3) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN21 (coords: L10) is configured as LCD_VD(3) */
    IOCON_PinMuxSet(IOCON, 2U, 21U, port2_pin21_config);

    const uint32_t port2_pin22_config = (/* Pin is configured as LCD_VD(4) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN22 (coords: K10) is configured as LCD_VD(4) */
    IOCON_PinMuxSet(IOCON, 2U, 22U, port2_pin22_config);

    const uint32_t port2_pin23_config = (/* Pin is configured as LCD_VD(5) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN23 (coords: M14) is configured as LCD_VD(5) */
    IOCON_PinMuxSet(IOCON, 2U, 23U, port2_pin23_config);

    const uint32_t port2_pin24_config = (/* Pin is configured as LCD_VD(6) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN24 (coords: K14) is configured as LCD_VD(6) */
    IOCON_PinMuxSet(IOCON, 2U, 24U, port2_pin24_config);

    const uint32_t port2_pin25_config = (/* Pin is configured as LCD_VD(7) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN25 (coords: J11) is configured as LCD_VD(7) */
    IOCON_PinMuxSet(IOCON, 2U, 25U, port2_pin25_config);

    const uint32_t port2_pin28_config = (/* Pin is configured as LCD_VD(10) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN28 (coords: G13) is configured as LCD_VD(10) */
    IOCON_PinMuxSet(IOCON, 2U, 28U, port2_pin28_config);

    const uint32_t port2_pin29_config = (/* Pin is configured as LCD_VD(11) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN29 (coords: G11) is configured as LCD_VD(11) */
    IOCON_PinMuxSet(IOCON, 2U, 29U, port2_pin29_config);

    const uint32_t port2_pin30_config = (/* Pin is configured as LCD_VD(12) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN30 (coords: F12) is configured as LCD_VD(12) */
    IOCON_PinMuxSet(IOCON, 2U, 30U, port2_pin30_config);

    const uint32_t port2_pin31_config = (/* Pin is configured as LCD_VD(13) */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT2 PIN31 (coords: D14) is configured as LCD_VD(13) */
    IOCON_PinMuxSet(IOCON, 2U, 31U, port2_pin31_config);

    const uint32_t port3_pin0_config = (/* Pin is configured as LCD_VD(14) */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN0 (coords: D12) is configured as LCD_VD(14) */
    IOCON_PinMuxSet(IOCON, 3U, 0U, port3_pin0_config);

    const uint32_t port3_pin1_config = (/* Pin is configured as LCD_VD(15) */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN1 (coords: D11) is configured as LCD_VD(15) */
    IOCON_PinMuxSet(IOCON, 3U, 1U, port3_pin1_config);

    const uint32_t port3_pin5_config = (/* Pin is configured as LCD_VD(19) */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN5 (coords: B10) is configured as LCD_VD(19) */
    IOCON_PinMuxSet(IOCON, 3U, 5U, port3_pin5_config);

    const uint32_t port3_pin6_config = (/* Pin is configured as LCD_VD(20) */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN6 (coords: C9) is configured as LCD_VD(20) */
    IOCON_PinMuxSet(IOCON, 3U, 6U, port3_pin6_config);

    const uint32_t port3_pin7_config = (/* Pin is configured as LCD_VD(21) */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN7 (coords: B8) is configured as LCD_VD(21) */
    IOCON_PinMuxSet(IOCON, 3U, 7U, port3_pin7_config);

    const uint32_t port3_pin8_config = (/* Pin is configured as LCD_VD(22) */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN8 (coords: A7) is configured as LCD_VD(22) */
    IOCON_PinMuxSet(IOCON, 3U, 8U, port3_pin8_config);

    const uint32_t port3_pin9_config = (/* Pin is configured as LCD_VD(23) */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT3 PIN9 (coords: C7) is configured as LCD_VD(23) */
    IOCON_PinMuxSet(IOCON, 3U, 9U, port3_pin9_config);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
