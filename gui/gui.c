#include "gui/gui.h"
#include "drivers/vga.h"

static int current_state = GUI_STATE_WELCOME;

void gui_set_state(int state) {
    current_state = state;
}

int gui_get_state(void) {
    return current_state;
}

void gui_draw_cursor(int x, int y) {
    // Arrow cursor
    for (int i = 0; i < 10; i++) {
        vga_putpixel(x, y + i, COLOR_WHITE);
    }
    for (int i = 0; i < 6; i++) {
        vga_putpixel(x + i, y + i, COLOR_WHITE);
    }
    vga_putpixel(x + 1, y + 6, COLOR_WHITE);
    vga_putpixel(x + 2, y + 7, COLOR_WHITE);
    vga_putpixel(x + 3, y + 8, COLOR_WHITE);
}
