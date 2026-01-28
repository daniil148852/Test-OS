#ifndef BUTTON_H
#define BUTTON_H

#include "lib/types.h"

struct button {
    int x, y, w, h;
    char label[24];
    int pressed;
    void (*on_click)(void);
};

void button_init(struct button* btn, int x, int y, int w, int h, const char* label, void (*callback)(void));
void button_draw(struct button* btn);
int button_hit_test(struct button* btn, int x, int y);

#endif
