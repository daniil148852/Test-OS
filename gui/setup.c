#include "gui/setup.h"
#include "gui/gui.h"
#include "gui/button.h"
#include "drivers/vga.h"
#include "drivers/mouse.h"
#include "drivers/keyboard.h"
#include "lib/string.h"

static int setup_complete = 0;
static char username[16] = "User";

static void on_finish(void) {
    setup_complete = 1;
}

void setup_show(void) {
    struct button btn_finish;
    button_init(&btn_finish, 120, 150, 80, 20, "Finish", on_finish);
    
    int prev_buttons = 0;
    
    while (!setup_complete) {
        vga_clear(COLOR_BLUE);
        
        vga_fillrect(40, 30, 240, 150, COLOR_LGRAY);
        vga_rect(40, 30, 240, 150, COLOR_BLACK);
        vga_fillrect(40, 30, 240, 14, COLOR_BLUE);
        vga_print(44, 32, "Initial Setup", COLOR_WHITE);
        
        vga_print(60, 55, "Welcome to MiniOS Setup", COLOR_BLACK);
        
        vga_print(60, 80, "Username:", COLOR_BLACK);
        vga_fillrect(60, 92, 120, 14, COLOR_WHITE);
        vga_rect(60, 92, 120, 14, COLOR_BLACK);
        vga_print(64, 95, username, COLOR_BLACK);
        
        vga_print(60, 115, "Theme: Classic Blue", COLOR_DGRAY);
        
        button_draw(&btn_finish);
        
        gui_draw_cursor(mouse_get_x(), mouse_get_y());
        vga_swap();
        
        int buttons = mouse_get_buttons();
        int mx = mouse_get_x();
        int my = mouse_get_y();
        
        if ((buttons & 1) && !(prev_buttons & 1)) {
            if (button_hit_test(&btn_finish, mx, my)) {
                btn_finish.pressed = 1;
                if (btn_finish.on_click) btn_finish.on_click();
            }
        }
        
        if (!(buttons & 1)) {
            btn_finish.pressed = 0;
        }
        
        if (keyboard_haskey()) {
            char c = keyboard_getchar();
            int len = strlen(username);
            if (c == '\b' && len > 0) {
                username[len - 1] = '\0';
            } else if (c >= ' ' && c <= '~' && len < 14) {
                username[len] = c;
                username[len + 1] = '\0';
            }
        }
        
        prev_buttons = buttons;
    }
}

int setup_is_complete(void) {
    return setup_complete;
}
