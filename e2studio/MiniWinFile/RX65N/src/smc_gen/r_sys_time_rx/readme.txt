PLEASE REFER TO THE APPLICATION NOTE FOR THIS DRIVER FOR MORE INFORMATION

r_sys_time_rx
========

Overview
--------------------------------------------------------------------------------
The r_sys_time_rx module has a system timer structure and simple-scheduler.
Configuration options can be found in 
"\r_config\r_sys_time_rx_config.h". An original copy of the configuration file 
is stored in "r_sys_time_rx\ref\r_sys_time_rx_config_reference.h".


Features
--------
* All RX MCUs are supported.

File Structure
--------------
r_sci_rx
|   readme.txt
|   r_sys_time_rx_if.h
|
+---doc
|   +---ja
|   |    r01anxxxxjj{VERSION_NUMBER}-rx.pdf
|   +---en
|        r01anxxxxej{VERSION_NUMBER}-rx.pdf
|
+---ref
|       r_sys_timer_rx_config_reference.h
|
+---src
    |   r_sys_timer_rx.c
    |   r_sys_timer_rx_private.h
r_config
    r_sys_time_rx_config.h

