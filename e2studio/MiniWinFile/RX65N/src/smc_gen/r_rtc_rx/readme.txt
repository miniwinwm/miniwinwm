PLEASE REFER TO THE APPLICATION NOTE FOR THIS DRIVER FOR MORE INFORMATION

r_rtc_rx
=========

Overview
--------
This Real-Time Clock (RTC) driver supports 24-hr (versus 12-hour am/pm) and calendar 
count (versus binary count) operation. Functions include setting of the date/time,
setting and enabling alarms, counters, periodic interrupts, and an output clock.
The Capture facility is supported for the RX230, RX231, RX64M, RX71M etc.
Recovery from software standby mode can be performed by an alarm interrupt or 
periodic interrupt. 

Features
--------
* 1-Hz and 64-Hz(RX11x, RX23x, RX64M, RX71M etc.) clock output.
* Periodic interrupts from .5Hz to 256Hz
* Alarm Interrupts
* 3 independent timestamp capture pins 


File Structure
--------------
r_rtc_rx
+-- readme.txt
+-- r_rtc_rx_if.h
|
+---doc
|   |
|   +---en
|   |   r01an1817ej{VERSION_NUMBER}-rx.pdf
|   |
|   +---ja
|       r01an1817jj{VERSION_NUMBER}-rx.pdf
|
+---ref
|    +-- r_rtc_rx_config_reference.h
|
+---src
     +-- r_rtc_rx.c
     +-- r_rtc_rx_private.h
     +-- r_rtc_rx_hw.c


r_config
+-- r_rtc_rx_config.h

r_rtc_rx.ftl
