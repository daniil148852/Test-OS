#ifndef MEMORY_H
#define MEMORY_H

#include "lib/types.h"

void memory_init(void);
void* kmalloc(size_t size);
void kfree(void* ptr);

#endif
