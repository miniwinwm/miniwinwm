#include "miniwin_thread.h"
#include "miniwin.h"
#include "app.h"

/* MiniWin Thread entry function */
void miniwin_thread_entry(void)
{
    /* initialize non-miniwin parts of the application */
    app_init();

    /* initialize miniwin */
    mw_init();

    while (true)
    {
        /* do non-miniwin parts of application main loop processing */
        app_main_loop_process();

        /* do miniwin message processing */
        (void)mw_process_message();

        tx_thread_sleep (1);
    }
}
