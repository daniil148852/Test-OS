#ifndef MOUSE_H
#define MOUSE_H

#include "lib/types.h"

void mouse_init(void);
void mouse_handler(void);
int mouse_get_x(void);
int mouse_get_y(void);
int mouse_get_buttons(void);

#endif
