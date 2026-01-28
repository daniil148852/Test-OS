#include "gui/window.h"
#include "drivers/vga.h"
#include "lib/string.h"

void window_init(struct window* win, int x, int y, int w, int h, const char* title) {
    win->x = x;
    win->y = y;
    win->w = w;
    win->h = h;
    strncpy(win->title, title, 31);
    win->visible = 1;
    win->active = 0;
    win->draw = NULL;
    win->on_click = NULL;
}

void window_draw(struct window* win) {
    if (!win->visible) return;
    
    vga_fillrect(win->x + 3, win->y + 3, win->w, win->h, COLOR_DGRAY);
    vga_fillrect(win->x, win->y, win->w, win->h, COLOR_LGRAY);
    
    uint8_t title_color = win->active ? COLOR_BLUE : COLOR_DGRAY;
    vga_fillrect(win->x, win->y, win->w, 12, title_color);
    vga_print(win->x + 4, win->y + 2, win->title, COLOR_WHITE);
    
    vga_fillrect(win->x + win->w - 12, win->y + 1, 10, 10, COLOR_RED);
    vga_print(win->x + win->w - 10, win->y + 2, "X", COLOR_WHITE);
    
    vga_rect(win->x, win->y, win->w, win->h, COLOR_BLACK);
    
    if (win->draw) {
        win->draw(win);
    }
}

int window_hit_test(struct window* win, int x, int y) {
    return win->visible && 
           x >= win->x && x < win->x + win->w &&
           y >= win->y && y < win->y + win->h;
}

int window_hit_close(struct window* win, int x, int y) {
    return x >= win->x + win->w - 12 && x < win->x + win->w - 2 &&
           y >= win->y + 1 && y < win->y + 11;
}
