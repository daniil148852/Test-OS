#include "drivers/mouse.h"
#include "drivers/ports.h"
#include "drivers/vga.h"

static int mouse_x = 160;
static int mouse_y = 100;
static int mouse_buttons = 0;
static uint8_t mouse_cycle = 0;
static int8_t mouse_bytes[3];

static void mouse_wait(int type) {
    int timeout = 100000;
    if (type == 0) {
        while (timeout--) {
            if ((inb(0x64) & 1) == 1) return;
        }
    } else {
        while (timeout--) {
            if ((inb(0x64) & 2) == 0) return;
        }
    }
}

static void mouse_write(uint8_t data) {
    mouse_wait(1);
    outb(0x64, 0xD4);
    mouse_wait(1);
    outb(0x60, data);
}

static uint8_t mouse_read(void) {
    mouse_wait(0);
    return inb(0x60);
}

void mouse_init(void) {
    mouse_wait(1);
    outb(0x64, 0xA8);
    
    mouse_wait(1);
    outb(0x64, 0x20);
    mouse_wait(0);
    uint8_t status = inb(0x60) | 2;
    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, status);
    
    mouse_write(0xF6);
    mouse_read();
    
    mouse_write(0xF4);
    mouse_read();
}

void mouse_handler(void) {
    uint8_t data = inb(0x60);
    
    switch (mouse_cycle) {
        case 0:
            mouse_bytes[0] = data;
            if (data & 0x08) mouse_cycle++;
            break;
        case 1:
            mouse_bytes[1] = data;
            mouse_cycle++;
            break;
        case 2:
            mouse_bytes[2] = data;
            mouse_cycle = 0;
            
            mouse_buttons = mouse_bytes[0] & 0x07;
            mouse_x += mouse_bytes[1];
            mouse_y -= mouse_bytes[2];
            
            if (mouse_x < 0) mouse_x = 0;
            if (mouse_x >= VGA_WIDTH) mouse_x = VGA_WIDTH - 1;
            if (mouse_y < 0) mouse_y = 0;
            if (mouse_y >= VGA_HEIGHT) mouse_y = VGA_HEIGHT - 1;
            break;
    }
    
    outb(0x20, 0x20);
    outb(0xA0, 0x20);
}

int mouse_get_x(void) { return mouse_x; }
int mouse_get_y(void) { return mouse_y; }
int mouse_get_buttons(void) { return mouse_buttons; }
