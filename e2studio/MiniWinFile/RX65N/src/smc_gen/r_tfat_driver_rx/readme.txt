PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_tfat_driver_rx
=========

Document Number
---------------
R20AN0335JJ0104-RX-TFAT
R20AN0335EJ0104-RX-TFAT

Version
-------
v1.04

Overview
--------
This memory driver interface connects TFAT library and Device Drivers(USB etc).
TFAT library is a FAT file system which just requres small memory.
TFAT library is based on FatFs.
<br/>
Please refer to the
 https://www.renesas.com/mw/tfat

Features
--------
* This memory driver interface connects TFAT library and Device Drivers(USB etc).


Supported MCUs
--------------
* RX family

Boards Tested On
----------------
* RSKRX111
* RSKRX113
* RSKRX64M
* RSKRX71M
* RSKRX63N
* RSKRX231
* RSKRX65N

Limitations
-----------
None

Peripherals Used Directly
-------------------------
None

Required Packages
-----------------
r_sys_timer

How to add to your project
--------------------------
This module must be added to each project in which it is used.
Renesas recommends using "Smart Configurator" described in (1) or (3).
However, "Smart Configurator" only supports some RX devices.
Please use the methods of (2) or (4) for unsupported RX devices.

(1) Adding the FIT module to your project using "Smart Configurator" in e2 studio
By using the "Smart Configurator" in e2 studio, 
the FIT module is automatically added to your project.
Refer to "Renesas e2 studio Smart Configurator User Guide (R20AN0451)" for details.

(2) Adding the FIT module to your project using "FIT Configurator" in e2 studio
By using the "FIT Configurator" in e2 studio,
the FIT module is automatically added to your project.
Refer to "Adding Firmware Integration Technology Modules to Projects (R01AN1723)" for details.

(3) Adding the FIT module to your project using "Smart Configurator" on CS+
By using the "Smart Configurator Standalone version" in CS+,
the FIT module is automatically added to your project.
Refer to "Renesas e2 studio Smart Configurator User Guide (R20AN0451)" for details.

(4) Adding the FIT module to your project in CS+
In CS+, please manually add the FIT module to your project.
Refer to "Adding Firmware Integration Technology Modules to CS+ Projects (R01AN1826)" for details.

Toolchain(s) Used
-----------------
* Renesas RX V.2.08.00

File Structure
--------------
r_config
    r_tfat_driver_rx_config.h

r_tfat_driver_rx
|   readme.txt
|   r_tfat_driver_rx_if.h
|
+---doc
|   |
|   +---en
|   |   r20an0335ej0104-rx-tfat.pdf
|   +---ja
|       r20an0335jj0104-rx-tfat.pdf
+---src
|   |   r_tfat_drv_if.c
|   |   r_tfat_drv_if_dev.h
|   |
|   +---device
|       |
|       +---sdmem
|       |      r_tfat_drv_if_sdmem.c
|       +---usb
|       |      r_tfat_drv_if_usb.c
|       +---usb_mini
|              r_tfat_drv_if_usb_mini.c
|
+---ref
          r_tfat_driver_rx_config_reference.h

