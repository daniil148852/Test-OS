#include "gui/settings.h"
#include "gui/button.h"
#include "drivers/vga.h"
#include "lib/string.h"

static struct button btn_theme1;
static struct button btn_theme2;
static int current_theme = 0;

static void set_theme1(void) { current_theme = 0; }
static void set_theme2(void) { current_theme = 1; }

void settings_init(struct window* win) {
    button_init(&btn_theme1, win->x + 20, win->y + 50, 60, 16, "Blue", set_theme1);
    button_init(&btn_theme2, win->x + 90, win->y + 50, 60, 16, "Green", set_theme2);
    win->draw = settings_draw;
    win->on_click = settings_click;
}

void settings_draw(struct window* win) {
    vga_print(win->x + 10, win->y + 20, "System Settings", COLOR_BLACK);
    vga_print(win->x + 10, win->y + 35, "Theme:", COLOR_DGRAY);
    
    btn_theme1.x = win->x + 20;
    btn_theme1.y = win->y + 50;
    btn_theme2.x = win->x + 90;
    btn_theme2.y = win->y + 50;
    
    btn_theme1.pressed = (current_theme == 0);
    btn_theme2.pressed = (current_theme == 1);
    
    button_draw(&btn_theme1);
    button_draw(&btn_theme2);
    
    vga_print(win->x + 10, win->y + 80, "Memory: 128 MB", COLOR_DGRAY);
    vga_print(win->x + 10, win->y + 95, "Version: 1.0", COLOR_DGRAY);
}

void settings_click(struct window* win, int x, int y) {
    (void)win;
    if (button_hit_test(&btn_theme1, x, y) && btn_theme1.on_click) {
        btn_theme1.on_click();
    }
    if (button_hit_test(&btn_theme2, x, y) && btn_theme2.on_click) {
        btn_theme2.on_click();
    }
}

int settings_get_theme(void) {
    return current_theme;
}
