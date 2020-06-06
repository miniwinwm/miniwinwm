#ifndef CAMLIB_H_
#define CAMLIB_H_

void camlib_init(void);
uint16_t *camlib_get_frame(void);
void camlib_capture(void);

#endif
