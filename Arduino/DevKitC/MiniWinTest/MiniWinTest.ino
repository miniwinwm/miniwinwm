#include "src/miniwin.h"

void setup() 
{
  mw_init();
}

void loop() 
{ 
  /* do miniwin message processing */
  (void)mw_process_message();
}
