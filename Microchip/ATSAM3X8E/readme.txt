File|New Project|GCC C ASF Board Project
Name MiniWinSimple
Folder miniwinwm/Microchip/ATSAM3X8E
Create Directory for Solution unticked
OK
Device Family SAM3X
Choose ATSAM3X8E
Choose Arduino Due/X - ATSAM3X8E
OK
In ASF Wizard Project choose MiniWinSimple
Select SPI - Serial Peripheral Interface (driver), Add
Select TC - Timer Counter (driver), Add
Select TC - Timer Counter (driver), Add
Select Serial I/O - Host (component) usb, Add
Select Delay routines (service), Add
Select Flash - SAM Flash Service API (service), Add
Apply
Select project src folder, add app.c & app.h
Add
Tool|Options|Projects|Miscellaneous|File Management set Copy file to project when adding existing file to False
Add a dummy .gitignore file to any folder created as a placeholder for external files that are added but not copied from MiniWin folder structure
Add miniwin folder path
Add MiniWinSimple_Common folder path