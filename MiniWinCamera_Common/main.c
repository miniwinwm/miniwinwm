#include "main.h"
#include "miniwin.h"
#include "app.h"

int main(void)
{
	app_init();
	mw_init();

	while (true)
	{
		app_main_loop_process();
		(void)mw_process_message();
	}
}
