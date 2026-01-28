#include "gui/desktop.h"
#include "gui/gui.h"
#include "gui/window.h"
#include "gui/button.h"
#include "gui/settings.h"
#include "gui/fileman.h"
#include "gui/setup.h"
#include "drivers/vga.h"
#include "drivers/mouse.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"
#include "lib/string.h"

static struct window win_settings;
static struct window win_fileman;
static struct button btn_settings;
static struct button btn_files;
static struct button btn_start;

static int show_start_menu = 0;
static int prev_buttons = 0;
static int first_run = 1;

static void open_settings(void) {
    win_settings.visible = 1;
    win_settings.active = 1;
    win_fileman.active = 0;
    show_start_menu = 0;
}

static void open_files(void) {
    win_fileman.visible = 1;
    win_fileman.active = 1;
    win_settings.active = 0;
    show_start_menu = 0;
}

static void toggle_start(void) {
    show_start_menu = !show_start_menu;
}

void desktop_init(void) {
    if (first_run) {
        setup_show();
        first_run = 0;
    }
    
    window_init(&win_settings, 50, 30, 170, 120, "Settings");
    win_settings.visible = 0;
    settings_init(&win_settings);
    
    window_init(&win_fileman, 80, 40, 180, 140, "Files");
    win_fileman.visible = 0;
    fileman_init(&win_fileman);
    
    button_init(&btn_start, 2, VGA_HEIGHT - 18, 50, 16, "Start", toggle_start);
    button_init(&btn_settings, 10, VGA_HEIGHT - 75, 70, 16, "Settings", open_settings);
    button_init(&btn_files, 10, VGA_HEIGHT - 55, 70, 16, "Files", open_files);
}

static void draw_desktop(void) {
    vga_clear(COLOR_CYAN);
    
    vga_fillrect(10, 10, 40, 35, COLOR_LGRAY);
    vga_rect(10, 10, 40, 35, COLOR_BLACK);
    vga_print(12, 15, "File", COLOR_BLACK);
    vga_print(7, 48, "Files", COLOR_WHITE);
    
    vga_fillrect(10, 70, 40, 35, COLOR_LGRAY);
    vga_rect(10, 70, 40, 35, COLOR_BLACK);
    vga_print(15, 78, "Cfg", COLOR_BLACK);
    vga_print(2, 108, "Settings", COLOR_WHITE);
    
    vga_fillrect(0, VGA_HEIGHT - 20, VGA_WIDTH, 20, COLOR_LGRAY);
    vga_rect(0, VGA_HEIGHT - 20, VGA_WIDTH, 20, COLOR_DGRAY);
    
    button_draw(&btn_start);
    
    uint32_t ticks = timer_get_ticks();
    int seconds = (ticks / 100) % 60;
    int minutes = (ticks / 6000) % 60;
    char time_str[8];
    time_str[0] = '0' + (minutes / 10);
    time_str[1] = '0' + (minutes % 10);
    time_str[2] = ':';
    time_str[3] = '0' + (seconds / 10);
    time_str[4] = '0' + (seconds % 10);
    time_str[5] = '\0';
    vga_print(VGA_WIDTH - 50, VGA_HEIGHT - 14, time_str, COLOR_BLACK);
    
    if (show_start_menu) {
        vga_fillrect(2, VGA_HEIGHT - 95, 85, 75, COLOR_LGRAY);
        vga_rect(2, VGA_HEIGHT - 95, 85, 75, COLOR_BLACK);
        vga_fillrect(2, VGA_HEIGHT - 95, 85, 14, COLOR_BLUE);
        vga_print(6, VGA_HEIGHT - 93, "MiniOS", COLOR_WHITE);
        
        button_draw(&btn_settings);
        button_draw(&btn_files);
    }
    
    window_draw(&win_settings);
    window_draw(&win_fileman);
}

void desktop_update(void) {
    int mx = mouse_get_x();
    int my = mouse_get_y();
    int buttons = mouse_get_buttons();
    
    draw_desktop();
    gui_draw_cursor(mx, my);
    vga_swap();
    
    if ((buttons & 1) && !(prev_buttons & 1)) {
        if (button_hit_test(&btn_start, mx, my)) {
            if (btn_start.on_click) btn_start.on_click();
        }
        else if (show_start_menu) {
            if (button_hit_test(&btn_settings, mx, my) && btn_settings.on_click) {
                btn_settings.on_click();
            }
            if (button_hit_test(&btn_files, mx, my) && btn_files.on_click) {
                btn_files.on_click();
            }
        }
        else if (mx >= 10 && mx < 50 && my >= 10 && my < 55) {
            open_files();
        }
        else if (mx >= 10 && mx < 50 && my >= 70 && my < 115) {
            open_settings();
        }
        else if (window_hit_test(&win_settings, mx, my)) {
            if (window_hit_close(&win_settings, mx, my)) {
                win_settings.visible = 0;
            } else {
                win_settings.active = 1;
                win_fileman.active = 0;
                if (win_settings.on_click) {
                    win_settings.on_click(&win_settings, mx, my);
                }
            }
        }
        else if (window_hit_test(&win_fileman, mx, my)) {
            if (window_hit_close(&win_fileman, mx, my)) {
                win_fileman.visible = 0;
            } else {
                win_fileman.active = 1;
                win_settings.active = 0;
                if (win_fileman.on_click) {
                    win_fileman.on_click(&win_fileman, mx, my);
                }
            }
        }
        else {
            show_start_menu = 0;
        }
    }
    
    prev_buttons = buttons;
}
