#include "kernel/memory.h"

#define HEAP_START 0x200000
#define HEAP_SIZE  0x100000

static uint8_t* heap_ptr = (uint8_t*)HEAP_START;
static uint8_t* heap_end = (uint8_t*)(HEAP_START + HEAP_SIZE);

void memory_init(void) {
    heap_ptr = (uint8_t*)HEAP_START;
}

void* kmalloc(size_t size) {
    if (heap_ptr + size > heap_end) {
        return NULL;
    }
    void* ptr = heap_ptr;
    heap_ptr += size;
    heap_ptr = (uint8_t*)(((uint32_t)heap_ptr + 3) & ~3);
    return ptr;
}

void kfree(void* ptr) {
    (void)ptr;
}
