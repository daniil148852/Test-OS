#include "gui/fileman.h"
#include "gui/button.h"
#include "drivers/vga.h"
#include "fs/fs.h"
#include "lib/string.h"

static char file_list[MAX_FILES][MAX_FILENAME];
static int file_count = 0;
static int selected_file = -1;
static char file_content[256];
static int viewing_content = 0;

static struct button btn_new;
static struct button btn_view;
static struct button btn_back;

static void on_new(void) {
    static int file_num = 1;
    char name[MAX_FILENAME];
    strcpy(name, "newfile");
    char num[4];
    itoa(file_num++, num);
    int len = strlen(name);
    strncpy(name + len, num, MAX_FILENAME - len - 1);
    strncpy(name + strlen(name), ".txt", MAX_FILENAME - strlen(name) - 1);
    fs_create(name);
    fs_write(name, "New file content", 16);
}

static void on_view(void) {
    if (selected_file >= 0 && selected_file < file_count) {
        memset(file_content, 0, sizeof(file_content));
        fs_read(file_list[selected_file], file_content, 255);
        viewing_content = 1;
    }
}

static void on_back(void) {
    viewing_content = 0;
    selected_file = -1;
}

void fileman_init(struct window* win) {
    button_init(&btn_new, win->x + 10, win->y + win->h - 25, 50, 16, "New", on_new);
    button_init(&btn_view, win->x + 70, win->y + win->h - 25, 50, 16, "View", on_view);
    button_init(&btn_back, win->x + 130, win->y + win->h - 25, 50, 16, "Back", on_back);
    win->draw = fileman_draw;
    win->on_click = fileman_click;
}

void fileman_draw(struct window* win) {
    btn_new.x = win->x + 10;
    btn_new.y = win->y + win->h - 25;
    btn_view.x = win->x + 70;
    btn_view.y = win->y + win->h - 25;
    btn_back.x = win->x + 130;
    btn_back.y = win->y + win->h - 25;
    
    if (viewing_content) {
        vga_print(win->x + 10, win->y + 18, "File Content:", COLOR_BLACK);
        vga_fillrect(win->x + 5, win->y + 30, win->w - 10, win->h - 65, COLOR_WHITE);
        
        int y = win->y + 35;
        int x = win->x + 10;
        for (int i = 0; file_content[i] && y < win->y + win->h - 40; i++) {
            if (file_content[i] == '\n') {
                y += 10;
                x = win->x + 10;
            } else {
                vga_putchar(x, y, file_content[i], COLOR_BLACK);
                x += 8;
                if (x > win->x + win->w - 15) {
                    y += 10;
                    x = win->x + 10;
                }
            }
        }
        button_draw(&btn_back);
    } else {
        file_count = fs_list(file_list, MAX_FILES);
        
        vga_print(win->x + 10, win->y + 18, "Files:", COLOR_BLACK);
        
        for (int i = 0; i < file_count && i < 6; i++) {
            int y = win->y + 32 + i * 14;
            uint8_t bg = (i == selected_file) ? COLOR_BLUE : COLOR_WHITE;
            uint8_t fg = (i == selected_file) ? COLOR_WHITE : COLOR_BLACK;
            
            vga_fillrect(win->x + 10, y, win->w - 20, 12, bg);
            vga_print(win->x + 14, y + 2, file_list[i], fg);
        }
        
        button_draw(&btn_new);
        button_draw(&btn_view);
    }
}

void fileman_click(struct window* win, int x, int y) {
    if (viewing_content) {
        if (button_hit_test(&btn_back, x, y) && btn_back.on_click) {
            btn_back.on_click();
        }
        return;
    }
    
    // Check file list clicks
    for (int i = 0; i < file_count && i < 6; i++) {
        int fy = win->y + 32 + i * 14;
        if (x >= win->x + 10 && x < win->x + win->w - 10 &&
            y >= fy && y < fy + 12) {
            selected_file = i;
            return;
        }
    }
    
    if (button_hit_test(&btn_new, x, y) && btn_new.on_click) {
        btn_new.on_click();
    }
    if (button_hit_test(&btn_view, x, y) && btn_view.on_click) {
        btn_view.on_click();
    }
}
