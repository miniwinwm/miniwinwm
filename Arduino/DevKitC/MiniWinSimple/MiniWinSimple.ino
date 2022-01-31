 #include "src/miniwin.h"
#include "src/app.h"

void setup() 
{
  app_init();
  mw_init();
}

void loop() 
{ 
  /* do miniwin message processing */
  (void)mw_process_message();
}
