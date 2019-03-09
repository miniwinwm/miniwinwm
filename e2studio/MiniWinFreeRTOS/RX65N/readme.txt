After generating driver/BSP code from the supplied MiniWinFreeRTOS_RX65N.cfg
configuration file the following configuration change needs to be made that
currently the e2studio configurator user interface does not support (even 
though a comment says that it does).

In file...

	src\smc_gen\r_bsp_config.h
	
change this line...

	#define BSP_CFG_RTOS_USED               (0) // <-- Updated by GUI. Do not edit this value manually
	
to this...

	#define BSP_CFG_RTOS_USED               (1) // <-- Not updated by GUI. Edit this value manually
