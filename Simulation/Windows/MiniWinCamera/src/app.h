#ifndef APP_H
#define APP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <windows.h>

extern HWND hwnd;
extern bool mouse_down;
extern SHORT mx;
extern SHORT my;

void app_init(void);
void app_main_loop_process(void);

#ifdef __cplusplus
}
#endif

#endif
