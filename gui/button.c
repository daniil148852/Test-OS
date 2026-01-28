#include "gui/button.h"
#include "drivers/vga.h"
#include "lib/string.h"

void button_init(struct button* btn, int x, int y, int w, int h, const char* label, void (*callback)(void)) {
    btn->x = x;
    btn->y = y;
    btn->w = w;
    btn->h = h;
    strncpy(btn->label, label, 23);
    btn->pressed = 0;
    btn->on_click = callback;
}

void button_draw(struct button* btn) {
    uint8_t bg = btn->pressed ? COLOR_DGRAY : COLOR_LGRAY;
    
    vga_fillrect(btn->x, btn->y, btn->w, btn->h, bg);
    vga_rect(btn->x, btn->y, btn->w, btn->h, COLOR_BLACK);
    
    if (!btn->pressed) {
        for (int i = 0; i < btn->w - 1; i++) {
            vga_putpixel(btn->x + i, btn->y, COLOR_WHITE);
        }
        for (int i = 0; i < btn->h - 1; i++) {
            vga_putpixel(btn->x, btn->y + i, COLOR_WHITE);
        }
    }
    
    int text_x = btn->x + (btn->w - (int)strlen(btn->label) * 8) / 2;
    int text_y = btn->y + (btn->h - 8) / 2;
    vga_print(text_x, text_y, btn->label, COLOR_BLACK);
}

int button_hit_test(struct button* btn, int x, int y) {
    return x >= btn->x && x < btn->x + btn->w &&
           y >= btn->y && y < btn->y + btn->h;
}
