#include "gui/welcome.h"
#include "drivers/vga.h"
#include "drivers/timer.h"

void welcome_show(void) {
    vga_clear(COLOR_BLUE);
    
    // Logo area
    vga_fillrect(100, 50, 120, 40, COLOR_CYAN);
    vga_rect(100, 50, 120, 40, COLOR_WHITE);
    vga_print(120, 65, "MiniOS", COLOR_WHITE);
    
    vga_print(90, 100, "Welcome to MiniOS!", COLOR_WHITE);
    vga_print(70, 120, "Initializing system...", COLOR_LGRAY);
    
    vga_swap();
    
    // Progress bar
    for (int i = 0; i < 100; i++) {
        vga_fillrect(60 + i * 2, 150, 2, 16, COLOR_GREEN);
        vga_rect(60, 150, 200, 16, COLOR_WHITE);
        vga_swap();
        
        uint32_t start = timer_get_ticks();
        while (timer_get_ticks() - start < 2);
    }
    
    vga_print(80, 175, "Press any key...", COLOR_YELLOW);
    vga_swap();
    
    uint32_t start = timer_get_ticks();
    while (timer_get_ticks() - start < 200);
}
