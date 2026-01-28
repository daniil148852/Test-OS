#include "drivers/keyboard.h"
#include "drivers/ports.h"

static char key_buffer[256];
static int key_head = 0;
static int key_tail = 0;

static const char scancode_ascii[] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,
    '*',0,' '
};

void keyboard_init(void) {
    key_head = 0;
    key_tail = 0;
}

void keyboard_handler(void) {
    uint8_t scancode = inb(0x60);
    
    if (scancode < sizeof(scancode_ascii) && !(scancode & 0x80)) {
        char c = scancode_ascii[scancode];
        if (c) {
            key_buffer[key_head] = c;
            key_head = (key_head + 1) % 256;
        }
    }
    
    outb(0x20, 0x20);
}

int keyboard_haskey(void) {
    return key_head != key_tail;
}

char keyboard_getchar(void) {
    if (key_head == key_tail) return 0;
    char c = key_buffer[key_tail];
    key_tail = (key_tail + 1) % 256;
    return c;
}
