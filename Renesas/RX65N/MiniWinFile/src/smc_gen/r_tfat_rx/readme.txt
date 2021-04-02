PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_tfat_rx
=========

Document Number
---------------
R20AN0038JJ0304-RX-TFAT
R20AN0038EJ0304-RX-TFAT

Version
-------
v3.04

Overview
--------
TFAT library is a FAT file system which just requres small memory.
TFAT library is based on FatFs.

Please refer to the 
http://www.renesas.com/mw/tfat
http://japan.renesas.com/mw/tfat

These configuration options can be found in "r_config\r_tfat_rx_config.h". 
An original copy of the configuration file is stored in 
"r_tfat_rx\ref\r_tfat_rx_config_reference.h".


Features
--------
* TFAT library is a FAT file system which just requres small memory.

Supported MCUs
--------------
* RX family

Boards Tested On
----------------
* RSKRX71M
* RSKRX64M
* RSKRX63N
* RSKRX62N
* RSKRX610
* RSKRX231
* RSKRX210
* RSKRX113
* RSKRX111
* RSKRX65N

Limitations
-----------
None

Peripherals Used Directly
-------------------------
None

Required Packages
-----------------
None

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
* Renesas RXC V.2.05.00 or upper

File Structure
--------------
r_tfat_rx
|   readme.txt
|   r_tfat_lib.h
|
+---doc
|   |
|   +---ja
|   |         r20uw0078jj0301_tfat.pdf
|   |         r20an0038jj0304-rx-tfat.pdf
|   +---en
|             r20uw0078ej0301_tfat.pdf
|             r20an0038ej0304-rx-tfat.pdf
|
+---lib
|         r_mw_version.h
|         r_stdint.h
|         tfat_rx200_big.lib
|         tfat_rx200_little.lib
|         tfat_rx600_big.lib
|         tfat_rx600_little.lib
|
+---FITDemos
|   |
|   +---rx65n_1mb_rsk_sdcard_fat_sample
|   +---rx65n_1mb_rsk_usb_fat_sample
|   +---rx231_rsk_usb_fat_sample
|
+---ref
          r_tfat_rx_config_reference.h

r_config
    r_tfat_rx_config.h