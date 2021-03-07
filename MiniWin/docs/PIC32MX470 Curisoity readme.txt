How to configure the hardware from scratch in Harmony 3
-------------------------------------------------------

Tool|Options|Plugins
Set Window Manager to Native Netbeans
OK
File|New Project
In Choose Project select Microchip Embedded in Categories and 32-bit MPLAB Hamony 3 Project in Projects
Next
Next
In Name and Location set Location to C:\Users\John\Desktop\P1, Folder to P1, Name to P1
Next
In Configuration Settings choose PIC32MX in Device Family and PIC32MX470F512H in Target Device
Finish
Launch
MHC|Tools|Clock Configuration
Select Clock Diagram tab
Set FNOSC to PRIPLL
Set Primary Oscillator to 20,000,000
Set Enable POSCMOD to HS
In System PLL set FPLLIDIV to DIV_4
In Project Graph select System
Open Device & Project Configuration|PIC32MX470F512H Device Configuration|DEVCFG0
Set In-Circuit Emulator/Debugger Communication Channel Select Bit (ICESEL) to ICS_PGx2
In Project Configuration untick Generate Main Source File
MHC|Tools|Pin Configuration
Select Pin Diagram tab
In Pin Settings set pin 64 RE4 to Custom Name=LED1, Function=GPIO, Direction=Out, Latch=Low
In Pin Settings set pin 54 RD6 to Custom Name=S1, Function=GPIO, Direction=In
From Available Components drag TMR|TMR2 to Project Graph
Select TMR2
In Configuration Options set Select Prescalar to 1:64
Set Timer Period to 50
From Available Components drag CORE_TIMER|CORE_TIMER
From Available Components drag NVM|NVM
From Available Components drag SPI|SPI2
From Configuration Options for SPI2 untick Enable Interrupts, Baud Rate=12,000,000, Master Mode Slave Select Enable to disabled
From Pin Diagram set pin 5 to SDI2, pin 6 to SDO2, pin 4 to SCK2
In Pin Settings set pin 8 RG9 to Custom Name=TS_CS, Function=GPIO, Direction=Out, Latch=High
In Pin Settings set pin 42 RD8 to Custom Name=TS_IRQ, Function=GPIO, Direction=In
In Pin Settings set pin 24 RB11 to Custom Name=LCD_DC, Function=GPIO, Direction=Out, Latch=Low
In Pin Settings set pin 30 RB15 to Custom Name=LCD_RESET, Function=GPIO, Direction=Out, Latch=High
In Pin Settings set pin 46 RD0 to Custom Name=LCD_CS, Function=GPIO, Direction=Out, Latch=High
MHC|Generate Code


How to create a new MiniWin project in MPLAB10 using a previously exported Harmony3 hardware configuration
----------------------------------------------------------------------------------------------------------

File|New Project
In Categories Microchip Embedded then in Projects 32-bit MPLAB Harmony 3 Project, Next
Next
Location C:\Users\John\Desktop\workspace\miniwinwm\MPLABX\MiniWinNewProject\PIC32MX470F512H, Folder MiniWinNewProject, Name MiniWinNewProject, Next
In Configuration Settings choose PIC32MX in Device Family and PIC32MX470F512H in Target Device
Finish
Launch
MHC|Import
Browse to MiniWinConfig, select export.mhc, Open
MHC|Generate Code, Generate
MHC|Exit
Copy miniwinwm\MPLABX\MiniWinSimple\PIC32MX470F512H\src folder to same place in new project
In Projects tab right click on Source Files and Add Existing Items from Folders
Add Folder
Browse to miniwinwm folder and select MiniWin folder
Select
Add Folder
Browse to miniwinwm folder and select MiniWinNewProject_Common folder
Select
Add Folder
Browse to miniwinwm\MPLABX\MiniWinNewProject\PIC32MX470F512H folder and select src folder
Select
Add
In Projects tab right click MiniWinNewProject and select Properties
Under Conf: [default] Compiler Toolchain: XC32 select latest XC32 compiler
In Categories open Conf: [default], XC32 (Global Options), xc32-gcc, Option categories: General
In Option Categories choose Preprocessing and messages
In Preprocessor macros click... and add PIC32MX470F512H, OK
In Include directories click ...
Add paths...miniwinwm\MiniWin, miniwinwm\MiniWinMiniWinNewProject_Common, miniwinwm\MPLABX\MiniWinMiniWinNewProject\PIC32MX470F512H\src,
	miniwinwm\MiniWin\gl\fonts\truetype\mcufont
In Categories open Conf: [default], XC32 (Global Options), xc32-ld, Option categories: General
In Additional driver options: add -mreserve=prog@0x1D07F000:0x1D07FFFF
OK
Copy 2 .gitignore files from exisiting project before adding to git