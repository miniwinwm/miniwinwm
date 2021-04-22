#include <asf.h>
#include "conf_usb_host.h"
#include "string.h"
#if 0
static char test_file_name[] = {"0:uhi_msc_ttt.txt"};

int main(void)
{
	FATFS fs; 
	FIL file_object;
	sysclk_init();
	board_init();
	uhc_start();

	while (true) 
	{
		// Mount drive
		memset(&fs, 0, sizeof(FATFS));
		if (f_mount(LUN_ID_USB, &fs) == FR_INVALID_DRIVE) 
		{
			while(1);
		}
				
		test_file_name[0] = LUN_ID_USB + '0';
		if (f_open(&file_object, (char const *)test_file_name, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) 
		{
			continue;
		}
		
		f_puts("Test UHI MSC\n", &file_object);
		f_close(&file_object);
		
		while(1);
	}
}

#endif



