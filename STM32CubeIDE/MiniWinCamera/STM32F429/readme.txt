This example allows the output from a cheap OV7670 camera to be displayed in
a MiniWin window. The camera grabs images at QVGA 320 x 240 pixels in RGB565 
format which is downsized to QQVGA 160 x 120 pixels in RGB565 then displayed
in a window at that resolution in MiniWin's standard colour format of RGB888.

The STM32F429 processor has a camera parallel interface peripheral but it is 
not possible to use it because of clashes with the touchscreen, LCD and SDRAM
pins on the STM32F429I-DISC1 board. Therefore the camera is bit banged to read 
the image data. This is not ideal but is the only method possible within the 
hardware constraints of the board. This method limits maximum frame rate to 
approximately 12 per second.

Because of the tight timings when bit banging image data from a video camera
the camlib code has to disable interrupts globally. This is also a not ideal 
but is necessary to avoid missing data. While the camlib is reading an image 
the MiniWin internal timer will not be increasing making the MiniWin timers
inaccurate.

These are the connections required between the OV7670 camera and the board:

OV7670		STM32F429I-DISC1

3.3V		3V
DGND		GND
SCL			PB6
SDA			PB7
VS			PC11
HS			PA5
PLK			PB4
XLK			PF6
D7			PG9
D6			PE6
D5			PE5
D4			PE4
D3			PE3
D2			PE2
D1			PG3
D0			PG2
RET			NC	
PWDN		NC

The camlib library uses the following resources:

GPIO pins on port A:	PA5
GPIO pins on port C:	PC11
GPIO pins on port E:	PE2, PE3, PE4, PE5, PE6
GPIO pins on port G:	PG2, PG3, PG9

160 * 120 * 2 bytes of RAM

TIM10 and TIM1OC channel 1 on PF6

I2C1 on PB6 and PB7 during call of library function camlib_init().


