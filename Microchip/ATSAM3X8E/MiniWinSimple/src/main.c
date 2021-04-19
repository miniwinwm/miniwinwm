
#include <asf.h>
#include <stdio.h>
#include "app.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_non_vol.h"
#include "hal/hal_touch.h"

void send_buf(char *buf);

void send_buf(char *buf)
{
	int i = 0;
	
	while (buf[i])
	{
		stdio_usb_putchar(NULL, buf[i]);
		i++;
	}
}


int main (void)
{
	app_init();
	
	mw_hal_timer_init();
	
	stdio_usb_init();
	stdio_usb_enable();	
	
	float td[4]={0.1f,1.1f,3.1f,6.6f};
	float td2[4];
	char buf[100];
	
	mw_hal_delay_ms(4000);
		
	mw_hal_non_vol_save((uint8_t*)&td[0], 16);
	mw_hal_non_vol_load((uint8_t*)&td2[0],16);
	sprintf(buf, "%f %f %f %f\n\r", td[0], td[1], td[2], td[3]);
	send_buf(buf);
	sprintf(buf, "%f %f %f %f\n\r", td2[0], td2[1], td2[2], td2[3]);
	send_buf(buf);
	
	mw_hal_touch_init();

	while(1)
	{
		if (ioport_get_pin_level(PIO_PD1_IDX))
		{
			sprintf(buf, "u\n\r");
		}
		else
		{
			uint16_t x, y;
			mw_hal_touch_get_point(&x, &y);
			sprintf(buf, "x=%hu, y=%hu\n\r", x, y);
		}
		send_buf(buf);
		
		mw_hal_delay_ms(250);
	}
}
