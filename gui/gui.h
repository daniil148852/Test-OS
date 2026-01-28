#ifndef GUI_H
#define GUI_H

#include <stdint.h>

#define GUI_STATE_WELCOME  0
#define GUI_STATE_SETUP    1
#define GUI_STATE_DESKTOP  2
#define GUI_STATE_SETTINGS 3
#define GUI_STATE_FILEMAN  4

void gui_set_state(int state);
int gui_get_state(void);
void gui_draw_cursor(int x, int y);

#endif
