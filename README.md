<p align="center">
<img src="https://static.wixstatic.com/media/850cc4_b160987cf0174eba9a19a07ac7d762d0~mv2.jpg/v1/fill/w_83,h_116,al_c,lg_1,q_80/850cc4_b160987cf0174eba9a19a07ac7d762d0~mv2.webp">
</p>
<H1 align="center">MiniWin Embedded Window Manager</H1>
<p align="center">
<img width=220 height=300 src="https://static.wixstatic.com/media/850cc4_e428c1ec6cca4e57b05be59c98ab1b0a~mv2.jpg/v1/fill/w_305,h_403,al_c,lg_1,q_80/m.webp">
</p>
MiniWin is a generic open source overlapped window manager for small embedded systems with a touch screen. It is written in compliant C99 and is easily portable. The hardware interface is separated out into a small hardware abstraction layer making the rest of the system re-targetable to a wide variety of processors. MiniWin will run easily on ARM Cortex M0 or above, PIC32 or Renesas RX processors. MiniWin has a simple easy to understand API giving access to fully overlapped windows. The standard look and feel is easy to customize to your needs. Included with MiniWin are two sets of standard controls in standard and large sizes and a growing library of standard dialogs windows. All code developed for MiniWin and MiniWin generated code is MISRA 2012 'required' compliant.

<H2>Who is MiniWin for?</H2>
<ul>
<li>Open source projects that need a quick-start user interface
<li>Small commercial products that do not have the budget to buy a window manager or the manpower to develop one
<li>Hardware constrained devices that have limited resources but also have limited requirements
<li>Student projects that can build on the supplied example code 
<li>Developers who want a quick-start user interface without the need for extensive driver development effort
</ul>

<H2>Features</H2>
<ul>
<li>Written specifically for small embedded systems with a LCD display and a touch screen
<li>Apart from a small hardware abstraction layer, platform independent
<li>Supports multiple overlapped windows with Z ordering
<li>Supports display rotation
<li>Incorporates a flexible graphics library
<li>Comes with a 2 sets of user interface controls - standard size for use with a touch screen and stylus, and large size for touch screen with finger input.
<li>Includes a set of standard dialogs that need no further code written to use.
<li>No dynamic memory used - all data structures allocated at compile time
<li>Two different sized standard bitmapped fonts included - fixed width and proportional - and 4 further optional bitmapped fonts. Any bitmapped font can be plotted in 4 rotations.
<li>TrueType font rendering support allowing you to to render justified, kerned, anti-aliased text on screen using a TrueType font of your choice.
<li>A clean easy to use API
<li>Comprehensive documentation and example code
<li>Runs in bare metal systems or within a single thread of a RTOS.
<li>Example projects showing FatFS (with USB host or SD interface), FreeRTOS integration, and TrueType font rendering.
<li>Requires minimal memory.
<li>Compiles without warning with GCC, clang, CL, XC32 or CC-RX
<li>Doxygen documentation for every function and type
<li>In-built touch screen calibration capability the first time the window manager is started.
<li>Code generator to create all your windows and controls from a simple configuration file in JSON format.
<li>Windows and Linux simulations allow for rapid user interface code development before hardware is available and without time consuming reflashing.
</ul>

<H2>User Interface Controls</H2>
<p align="center">
<img width=220 height=300 src="https://static.wixstatic.com/media/850cc4_c5cc29edd5e7471098f7f8cd3dc69bd7~mv2.jpg/v1/fill/w_299,h_403,al_c,lg_1,q_80/m.webp">
</p>
<ul>
<li>Button
<li>Check box
<li>List box with optional icons
<li>Radio buttons
<li>Menu bar
<li>Text label
<li>Progress bar
<li>Horizontal scroll bar
<li>Vertical scroll bar
<li>Multi-directional arrow buttons
<li>Numeric keypad
<li>ASCII keyboard
<li>TrueType text box with rendering of justified kerned anti-aliased text.
<li>Multiple tabs
<li>Expandable tree
</ul>
These are the standard ones. You can easily add more.

<H2>MiniWin Windows</H2>
<p align="center">
<img width=220 height=300 src="https://static.wixstatic.com/media/850cc4_2c5ff55e1a274f989fe4d419d92a3a76~mv2.jpg/v1/fill/w_301,h_400,al_c,lg_1,q_80/m.webp">
</p>
<ul>
<li>Optional title bar, menu bar, title and border
<li>Overlapped with unique Z order
<li>Movable
<li>Resizable
<li>Maximise, minimise, resize and close icons
<li>Minimizable to icon on desktop
<li>Customizable desktop colour or bitmap
<li>Can have a single system modal window
<li>Window-aware graphics library for drawing in a window
<li>Standard or large sized features
</ul>

Of course, you don't have to use overlapped windows at all. If you want fixed dedicated areas of the display with each area being responsive to user input and having its own message and paint functions, that's possible too. Any window can be created with no border or title bar, and like this it's fixed on the screen.

<H2>Standard Dialogs</H2>
<p align="center">
<img width=220 height=300 src="https://static.wixstatic.com/media/850cc4_aff09112ff6b402eb40826c030b0836e~mv2.jpg/v1/fill/w_345,h_463,al_c,lg_1,q_80/l.webp">
</p>
MiniWin includes a collection of pre-defined standard dialogs. You don't have to do any window definition or coding to use these, just call the utility function to get it displayed. Each dialog can have its appearance controlled from the utility function parameters, for example the message to display in the message box dialogs and the text shown in the title bar.
<br><br>
<ul>
<li>Single button message box
<li>Double button message box
<li>Time chooser
<li>Date chooser
<li>Text entry dialog
<li>Number entry dialog
<li>File or folder chooser dialog
</ul>

<H2>Quick Start Guide</H2>

See https://miniwinwm.wixsite.com/miniwinwm/quick-start-guide for a quick start guide using STM32CubeIDE.

<H2>Documentation</H2>

See https://github.com/miniwinwm/miniwinwm/blob/master/MiniWin/docs/MiniWin.pdf for extensive documentation.

<H2>Window Management API</H2>

See https://miniwinwm.wixsite.com/miniwinwm/window-management-api for an overview of the window management API.

<H2>Developer Utility Applications</H2>
MiniWin includes the following utility applications with source code which can be built for Windows or Linux from source:
<br><br>
<ul>
<li>Converter for monochrome bitmap files in .bmp format to C99 source code.
<li>Converter for 24 bit colour bitmap files in .bmp format to C99 source code.
<li>Converter for TrueType font files to run-length encoded C99 source file for a single point size
<li>Code generator to create your window and control code from a JSON format configuration file.
</ul>

<H2>Drivers and Examples</H2>
<p align="center">
<img width=220 height=300 src="https://static.wixstatic.com/media/850cc4_29133360d31b454c8bd257c9cf7584db~mv2.jpg/v1/fill/w_345,h_463,al_c,lg_1,q_80/m.webp">
</p>
MiniWin comes with all source for the window manager, graphics library and user interface components. It also comes with 8 example projects - a simple getting started example, a non-overlapped fixed windows example, an example that integrates a USB pen drive or SD card to read and show text and image files, an example integrated with FreeRTOS, a TrueType font demonstration, an example showing root window capabilities, a project showing usage of all MiniWin's user interface components and a project that interfaces with a video camera showing a video stream in a MiniWin window. MiniWin comes with 13 HAL layer samples:
<br><br>
<ul>
<li>STM32F4DISCOVERY board using an ILI9341 driven QVGA LCD with touch screen
<li>ESP32 based DevKitC board using an ILI9341 driven QVGA LCD with touch screen built using ESP32-IDF
<li>ESP32 based DevKitC board using an ILI9341 driven QVGA LCD with touch screen built using Arduino IDE
<li>STM32F429I-DISC1 board with built in QVGA LCD with touch screen
<li>NXP 54628 board with built in WQVGA LCD and touch screen
<li>Renesas Envision Kit board running RX65N processor with built in WQVGA LCD with touch screen built with CC-RX
<li>Renesas Envision Kit board running RX65N processor with built in WQVGA LCD with touch screen built with GCC-RX
<li>Microchip PIC32MX board using an ILI9341 driven QVGA LCD with touch screen
<li>Microchip PIC32MZ board using an ILI9341 driven QVGA LCD with touch screen
<li>Raspberry Pi Zero W board using an ILI9341 driven QVGA LCD with touch screen
<li>Linux simulator built with GCC or clang
<li>Windows simulator built with GCC or clang under MSYS2
<li>Windows simulator built with Visual Studio CL
</ul>
Sample simulation projects are built using standalone gmake makefiles with GCC or clang for Windows and Linux or Microsoft Visual Studio CL compiler via nmake makefiles for Windows. Eclipse project files are provided for the Windows and Linux simulation projects. Build/project files are provided for all examples.
<br><br>
MiniWin has the ability to debug on Windows or Linux running the simulators. Develop your embedded part of your application on target, but do the user interface development part on the simulators on Windows or Linux. This allows much quicker debugging than flashing to target every time you make a change. 

<H2>Graphics Library</H2>
MiniWin comes with a standard graphics library supporting the normal lines, bitmapped and TrueType font rendering, bitmaps and shapes as well as polygon and shape rotation. It includes simple patterned lines and texture fills.
<br><br>
All graphics library drawing routines are window aware - you do not have to worry about where your window is, if it is overlapped or partly off screen. You just draw to a window's client area regardless using the client area as your frame of reference. MiniWin performs all window offset translations and clipping required. You will never end up drawing outside of your window or scribbling somewhere you shouldn't.

<H2>Customisability</H2>
Because MiniWin is open source its look and feel is fully customisable. Don't like the look of a user interface component? Simple. Modify its paint function and draw it how you want it to look.

<H2>Window Paint Algorithm</H2>
MiniWin uses a paint algorithm that is optimised for use on a system without any off-screen shadow buffers for its windows, i.e. all writes to the display memory via the graphics library are shown immediately on the display. To avoid flickering each part of the display is written to only once for each repaint request regardless of how overlapped the windows are. The paint algorithm used is the singly-combined sorted intersections algorithm.

<H2>Source Tree</H2>
The source code tree is quite complicated so is explained here:
<br><br>
<b>Arduino:</b> This contains project files and application code specific to example applications that run on Arduino boards (currently ESP32 based DevKitC) and are built using the Arduino IDE. Under this folder is a sub-folder for each targeted Arduino board, DevKitC, and under each of this a further sub-folder for each application example. In these folders are a setup.bat file which must be run before the Arduino IDE is started, hardware configuration code needed by the example application in the app folder, and the Arduino IDE .ino file. When the setup.bat file is run a src directory is created that creates hard links to the source and header files in the MiniWin folder structure. This src folder can be safely deleted as it only contains links created by the setup.bat file.<br><br>

<b>Atmel:</b> This contains project files and application code specific to example applications that run on Microchip/Atmel processors and are built using the Microchip/Atmel Studio. Under this folder are sub-folders for each targeted processor (ATSAM3X8E). Under these folders are further sub-folder for each application example. In these folders are Microchip/Atmel Studio project files, the required BSP for that application and under the src folder source files that are both application and hardware variant specific.

<b>Renesas:</b> This contains project files and application code specific to example applications that run on Renesas processors (currently RX65N) and are built using the Renesas e2 Studio IDE and the Renesas RX-CC or GCC-RX compilers. Under this folder is a sub-folder for each targeted Renesas processor/compiler, RX65N or RX65N_GCC, and under each of these a further sub-folder for each application example. In these folders are e2 Studio project files and the start-up code for that application. Under the src folder are source files that are both application and hardware variant specific. In the root folder for each RX-CC compiler project is a .scfg file used to configure the hardware.

<b>Espressif:</b> This contains project files and application code specific to example applications that run on ESP32 processors and are built using the ESP supplied IDF build system. Under this folder is a sub-folder for each targeted ESP32 development board (DevKitC). Under this folder is a further sub-folder for each application example. In these folders are the main and the component CMake files, the SDK configuration file for that application and under the main folder source files that are both application and hardware variant specific. 

<b>NXP:</b> This contains project files, BSP and application code specific to example applications that run on NXP processors and are built using the NXP MCUXpresso IDE. Under this folder is a sub-folder for each targeted NXP processor (LPC54628). Under this folder are further sub-folder for each application example. In these folders are MCUXpresso project files, the required BSP for that application and under the src folder source files that are both application and hardware variant specific.

<b>ST:</b> This contains project files, BSP and application code specific to example applications that run on ST processors and are built using the STM32CubeIDE. Under this folder are 2 sub-folders for each targeted processor (STM32F407 ands STM32F429). Under these folders are further sub-folder for each application example. In these folders are STM32CubeIDE project files, the required BSP for that application and under the src folder source files that are both application and hardware variant specific.

<b>Microchip:</b> This contains project files and application code specific to example applications that run on Microchip processors and are built using the MPLAB X. Under this folder are 2 sub-folders for each targeted processor (PIC32MX470F512H and PIC32MZ2048EFM100). Under these folders are further sub-folder for each application example. In these folders are MPLAB X project files, the required BSP for that application and under the src folder source files that are both application and hardware variant specific.

<b>RaspberryPi:</b> This contains project files and application code specific to example applications that run on Raspberry Pi boards and are built using make and GCC natively on the Raspberry Pi. Under this folder are sub-folders for each targeted board (Zero W and Pico). Under this folder is a further sub-folder for each application example. This contains project files that are built using make and GCC. In Raspberry Pi OS GCC will always be available. 

<b>Simulation:</b> This contains project files for example applications that are built to run on a computer as a simulation rather than on embedded hardware. Under this folder are sub-folders for each targeted simulation platform (Windows and Linux). Under these folders are further sub-folder for each application example. These sub-folders each contain a makefile/nmakefile to build the example application using GCC/Visual Studio CL. 

<b>MiniWin:</b> This contains the MiniWin embedded window manager source code which is common to all example applications for all platforms and processors. It contains the following sub-folders:

<b>bitmaps:</b> Bitmaps and their C99 file encodings used by MiniWin <br>
<b>dialogs:</b> Standard dialogs provided by MiniWin<br>
<b>docs:</b> All documentation<br>
<b>gl:</b> The graphics library incorporated in MiniWin including fonts<br>
<b>hal:</b> The hardware abstraction layer of drivers for all the currently supported processors and platforms<br>
<b>templates:</b> Templates of required application files<br>
<b>ui:</b> Standard user interface controls. User code can add to this for further controls if required<br>
<b>hal:</b> Source files common to all hal implementations and then further source files in sub-folder for different currently supported platforms and processors. Each set of drivers for a particular target builds only for that target. Other different target files compile to nothing through the use of #defines.

In addition the following source files are in the MiniWin folder:

calibrate.h/c:			          Third party touch screen calibration routines<br>
miniwin_debug.h/c:			      Implementation of assert functionality, debug build only<br>
miniwin_message_queue.h/c:	  Simple message queue code for MiniWin messages<br>
miniwin_settings.h/c:		    Simple non-volatile storage routines for settings<br>
miniwin_touch.h/c:			      Interface between touch driver code under hal and the touch client code in MiniWin<br>
miniwin_tree_container.h/c:	Tree container storage utility<br>
miniwin_utilities.h/c:		    Generic utility routines<br>
miniwin.h/c:				          The main window manager code<br>

<b>MiniWinTest_Common:</b> This contains application source files for the comprehensive MiniWinTest example that are common to all platform/processor variants. 

<b>MiniWinSimple_Common:</b> This contains the application example source files described later in this document. 

<b>MiniWinFixedWindows_Common:</b> As above but for the fixed windows example project. 

<b>MiniWinRoot_Common:</b> As above but for the root window example project. 

<b>MiniWinFile_Common:</b> As above but for the file example project. 

<b>MiniWinTTFonts_Common:</b> As above but for the TrueType font rendering example project. 

<b>MiniWinFreeRTOS:</b> As above but for the FreeRTOS integration example project. 

<b>MiniWinCamera:</b> As above but for the video camera integration example project.

<b>Tools:</b> This contains the utility applications that are part of MiniWin that are built for Linux or Windows using GCC. This folder contains the following sub-folders:

<b>BMPConv24Colour:</b> This is a command line utility for converting a Windows 24 bit per pixel .bmp file to a 3 bytes per per pixel C99 source file. It uses EasyBMP.

<b>BMPConvMono:</b> This is a command line utility for converting a Windows 2 bit per pixel .bmp file to an 8 pixels per byte C99 source file. It uses EasyBMP.

<b>CodeGen:</b> This contains the MiniWin code generator utility. It is described later in this document.

<b>FontEncoder:</b> This is a command line utility for converting a TrueType font file to a run-length encoded C99 source file. It comes as part of the mcufonts library.

<b>EasyBMP:</b> This is source code for a third party Windows .bmp file handling library. It is used by the utility applications, not MiniWin.
