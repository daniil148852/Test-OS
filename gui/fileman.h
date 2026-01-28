#ifndef FILEMAN_H
#define FILEMAN_H

#include "gui/window.h"

void fileman_init(struct window* win);
void fileman_draw(struct window* win);
void fileman_click(struct window* win, int x, int y);

#endif
