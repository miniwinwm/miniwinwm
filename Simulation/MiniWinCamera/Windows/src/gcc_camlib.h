#ifndef GCC_CAMLIB_H
#define GCC_CAMLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void* gcc_camlib_t;

gcc_camlib_t gcc_camlib_init(void);
void gcc_camlib_capture(gcc_camlib_t gcc_camlib);
void gcc_camlib_draw(gcc_camlib_t gcc_camlib, HDC hdc);
void gcc_camlib_destroy(gcc_camlib_t gcc_camlib);
uint16_t *gcc_camlib_get_frame(gcc_camlib_t gcc_camlib);

#ifdef __cplusplus
}
#endif

#endif
