#ifndef SETTINGS_H
#define SETTINGS_H

#include "gui/window.h"

void settings_init(struct window* win);
void settings_draw(struct window* win);
void settings_click(struct window* win, int x, int y);

#endif
