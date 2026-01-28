#include "kernel/gdt.h"
#include "kernel/idt.h"
#include "kernel/irq.h"
#include "kernel/memory.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/timer.h"
#include "fs/fs.h"
#include "gui/desktop.h"
#include "gui/welcome.h"

static int first_boot = 1;

void kernel_main(void) {
    gdt_init();
    idt_init();
    irq_init();
    memory_init();
    
    vga_init();
    timer_init();
    keyboard_init();
    mouse_init();
    
    fs_init();
    
    // Create default files
    fs_create("readme.txt");
    fs_write("readme.txt", "Welcome to MiniOS!\nThis is a simple operating system.", 54);
    fs_create("notes.txt");
    fs_write("notes.txt", "My notes file", 13);
    
    if (first_boot) {
        welcome_show();
        first_boot = 0;
    }
    
    desktop_init();
    
    while (1) {
        desktop_update();
        __asm__ volatile("hlt");
    }
}
