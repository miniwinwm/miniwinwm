This example allows the output from a cheap OV7670 camera to be displayed in
a MiniWin window. The camera grabs images at QVGA 320 x 240 pixels in RGB565 
format which is downsized to QQVGA 160 x 120 pixels in RGB565 then displayed
in a window at that resolution in MiniWin's standard colour format of RGB888.

The STM32F409 processor has a camera parallel interface peripheral but it is 
not used to keep the code the same as the STM43F429 example. Therefore the 
camera is bit banged to read the image data. This method limits maximum frame 
capture rate to approximately 12 per second, ehcih is far greater than the
simple bitmap plotting routine in the LCD driver can draw the images.

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
VS			PC0
HS			PC3
PLK			PC1
XLK			PB8
D7			PA7
D6			PA6
D5			PA5
D4			PA4
D3			PA3
D2			PA2
D1			PA1
D0			PA0
RET			NC	
PWDN		NC

The camlib library uses the following resources:

GPIO pins on port A:	PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7 
GPIO pins on port C:	PC, PC1, PC3

160 * 120 * 2 bytes of RAM

TIM10 and TIM1OC channel 1 on PB8

I2C1 on PB6 and PB7 during call of library function camlib_init().


