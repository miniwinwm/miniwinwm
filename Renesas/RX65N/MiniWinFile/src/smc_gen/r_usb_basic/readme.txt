PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_usb_basic
=======================

Document Number 
---------------
R01AN2025EJ
R01AN2025JJ

Version
-------
v1.24

Overview
--------
USB Basic Host and Peripheral Driver

Features
--------
* Can operate in either host or peripheral mode.
* Device connect/disconnect, suspend/resume, and USB bus reset processing.
* Control transfer on pipe 0.
* Data transfer on pipes 1 to 9. (bulk or interrupt transfer: CPU access/DTC or DMA access)

Supported MCUs
--------------
* RX64M Group
* RX71M Group
* RX63N Group
* RX65N Group

Boards Tested On
----------------
* RSKRX64M
* RSKRX71M
* RSKRX63N
* RSKRX65N
* RSKRX65N_2MB
 
Limitations
-----------

Peripherals Used Directly
-------------------------


Required Packages
-----------------
* r_bsp


How to add to your project
--------------------------

Toolchain(s) Used
-----------------
* Renesas RX v.3.01.00

File Structure
--------------
r_usb_basic
|   readme.txt
|   r_usb_basic_if.h
|
+---doc
|     \en
|     |   r01an2025ej0124_usb.pdf
|     \jp
|         r01an2025jj0124_usb.pdf
|
+---ref
|       r_usb_config_reference.h
|
\---src
     +---driver
     |      +---inc
     |            r_usb_basic_define.h
     |            r_usb_extern.h
     |            r_usb_typedef.h
     |            r_usb_cstd_rtos.h
     |
     |      r_usb_cdataio.c
     |      r_usb_clibusbip.c
     |      r_usb_hbc.c
     |      r_usb_hcontrolrw.c
     |      r_usb_hdriver.c
     |      r_usb_hhubsys.c
     |      r_usb_hintfifo.c
     |      r_usb_hinthandler_usbip0.c
     |      r_usb_hinthandler_usbip1.c
     |      r_usb_hlibusbip.c
     |      r_usb_hmanager.c
     |      r_usb_hscheduler.c
     |      r_usb_hsignal.c
     |      r_usb_hstdfunction.c
     |      r_usb_cstd_rtos.c
     |      r_usb_pbc.c
     |      r_usb_pcontrolrw.c
     |      r_usb_pdriver.c
     |      r_usb_pintfifo.c
     |      r_usb_pinthandler_usbip0.c
     |      r_usb_plibusbip.c
     |      r_usb_psignal.c
     |      r_usb_pstdfunction.c
     |      r_usb_pstdrequest.c
     |      r_usb_usbif_api.c
     |            
     \---hw
           +---inc
                  r_usb_bitdefine.h
                  r_usb_dmac.h
                  r_usb_reg_access.h
                  
           r_usb_creg_abs.c
           r_usb_creg_access.c
           r_usb_dma.c
           r_usb_hostelectrical.c
           r_usb_hreg_abs.c
           r_usb_hreg_access.c
           r_usb_preg_abs.c
           r_usb_preg_access.c
           r_usb_rx_mcu.c
