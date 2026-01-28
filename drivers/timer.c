#include "drivers/timer.h"
#include "drivers/ports.h"

static volatile uint32_t ticks = 0;

void timer_init(void) {
    uint32_t divisor = 1193180 / 100;
    
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}

void timer_handler(void) {
    ticks++;
    outb(0x20, 0x20);
}

uint32_t timer_get_ticks(void) {
    return ticks;
}
