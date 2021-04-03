See https://miniwinwm.wixsite.com/miniwinwm for an overview.

Documentation is in the MiniWin/docs folder above.

The source code tree is quite complicated so is explained here:

Renesas: This contains project files and application code specific to example applications that run on Renesas processors (currently RX65N) and are built using the Renesas e2 Studio IDE and the Renesas RX-CC or GCC-RX compilers. Under this folder is a sub-folder for each targeted Renesas processor/compiler, RX65N or RX65N_GCC and under each of these a further sub-folder for each application example. In these folders are e2 Studio project files and the start-up code for that application. Under the src folder are source files that are both application and hardware variant specific. In the root folder for each RX-CC compiler project is a .scfg file used to configure the hardware.

Espressif: This contains project files and application code specific to example applications that run on ESP32 processors and are built using the ESP supplied IDF build system. Under this folder is a sub-folder for each targeted ESP32 development board (DevKitC). Under this folder is a further sub-folder for each application example. In these folders are the main and the component CMake files, the SDK configuration file for that application and under the main folder source files that are both application and hardware variant specific. ESP32 applications do not use a main.c file but instead have a similar app_main.c file, found under the main folder.

NXP: This contains project files, BSP and application code specific to example applications that run on NXP processors and are built using the NXP MCUXpresso IDE. Under this folder is a sub-folder for each targeted NXP processor (LPC54628). Under this folder are further sub-folder for each application example. In these folders are MCUXpresso project files, the required BSP for that application and under the src folder source files that are both application and hardware variant specific.

ST:  This contains project files, BSP and application code specific to example applications that run on ST processors and are built using the STM32CubeIDE. Under this folder are 2 sub-folders for each targeted processor (STM32F407 ands STM32F429). Under these folders are further sub-folder for each application example. In these folders are STM32CubeIDE project files, the required BSP for that application and under the src folder source files that are both application and hardware variant specific.

Microchip:  This contains project files and application code specific to example applications that run on Microchip processors and are built using the MPLAB X. Under this folder are 2 sub-folders for each targeted processor (PIC32MX470F512H and PIC32MZ2048EFM100). Under these folders are further sub-folder for each application example. In these folders are MPLAB X project files, the required BSP for that application and under the src folder source files that are both application and hardware variant specific.

RaspberryPi: This contains project files and application code specific to example applications that run on Raspberry Pi boards and are built using make and GCC natively on the Raspberry Pi. Under this folder are sub-folders for each targeted board (Zero W). Under this folder is a further sub-folder for each application example. This contains project files that are built using make and GCC. In Raspberry Pi OS GCC will always be available. 

Simulation: This contains project files for example applications that are built to run on a computer as a simulation rather than on embedded hardware. Under this folder are sub-folders for each targeted simulation platform (Windows and Linux). Under these folders are further sub-folder for each application example. These sub-folders each contain a makefile/nmakefile to build the example application using GCC/Visual Studio CL. 

MiniWin: This contains the MiniWin embedded window manager source code which is common to all example applications for all platforms and processors. It contains the following sub-folders:

bitmaps	                    Bitmaps and their C99 file encodings used by MiniWin 
dialogs	                    Standard dialogs provided by MiniWin
docs	  	                  All documentation
gl		                      The graphics library incorporated in MiniWin including fonts
hal	                        The hardware abstraction layer of drivers for all the currently supported processors and platforms
templates	                  Templates of required application files
ui	                        Standard user interface controls. User code can add to this for further controls if required
	
Folder hal contains source files common to all hal implementations and then further source files in sub-folder for different currently supported platforms and processors. Each set of drivers for a particular target builds only for that target. Other different target files compile to nothing through the use of #defines.

In addition the following source files are in the MiniWin folder:

calibrate.h/c			          Third party touch screen calibration routines
miniwin_debug.h/c			      Implementation of assert functionality, debug build only
miniwin_message_queue.h/c	  Simple message queue code for MiniWin messages
miniwin_settings.h/c		    Simple non-volatile storage routines for settings
miniwin_touch.h/c			      Interface between touch driver code under hal and the touch client code in MiniWin
miniwin_tree_container.h/c	Tree container storage utility
miniwin_utilities.h/c		    Generic utility routines
miniwin.h/c				          The main window manager code

MiniWinTest_Common: This contains application source files for the comprehensive MiniWinTest example that are common to all platform/processor variants. 

MiniWinSimple_Common: This contains the application example source files described later in this document. 

MiniWinFixedWindows_Common: As above but for the fixed windows example project. 

MiniWinRoot_Common: As above but for the root window example project. 

MiniWinFile_Common: As above but for the file example project. 

MiniWinTTFonts_Common: As above but for the TrueType font rendering example project. 

MiniWinFreeRTOS: As above but for the FreeRTOS integration example project. 

MiniWinCamera: As above but for the video camera integration example project.

Tools: This contains the utility applications that are part of MiniWin that are built for Linux or Windows using GCC. This folder contains the following sub-folders:

BMPConv24Colour: This is a command line utility for converting a Windows 24 bit per pixel .bmp file to a 3 bytes per per pixel C99 source file. It uses EasyBMP.

BMPConvMono: This is a command line utility for converting a Windows 2 bit per pixel .bmp file to an 8 pixels per byte C99 source file. It uses EasyBMP.

CodeGen: This contains the MiniWin code generator utility. It is described later in this document.

FontEncoder: This is a command line utility for converting a TrueType font file to a run-length encoded C99 source file. It comes as part of the mcufonts library.

EasyBMP: This is source code for a third party Windows .bmp file handling library. It is used by the utility applications, not MiniWin.
