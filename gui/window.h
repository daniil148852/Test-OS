#ifndef WINDOW_H
#define WINDOW_H

#include "lib/types.h"

#define MAX_WINDOWS 8

struct window {
    int x, y, w, h;
    char title[32];
    int visible;
    int active;
    void (*draw)(struct window*);
    void (*on_click)(struct window*, int, int);
};

void window_init(struct window* win, int x, int y, int w, int h, const char* title);
void window_draw(struct window* win);
int window_hit_test(struct window* win, int x, int y);
int window_hit_close(struct window* win, int x, int y);

#endif
