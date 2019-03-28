This demonstration shows how to integrate FatFS with a SD card and a
reader connected to the Pmod connector on the Renesas Envision Kit (CN14).

A SD Card reader with SPI connections that can be driven with a 3.3V power 
supply is needed. These are available on EBay for Arduino projects for less
than $5.

The following connections are needed. See connections.jpg in this folder.

Pmod CN14	SD Card Reader (function)
1		CS/		(chip select active low)
2		MOSI		(master out save in)
3		MISO		(master in slave out)
4		SCK		(SPI clock)
5		GND		(power supply ground)
6		+3.3V		(power supply 3.3V supply) 

Stack space has been increased from the default 256 bytes to 1024 bytes.
