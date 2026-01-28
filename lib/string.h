#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

void* memset(void* ptr, int value, size_t num);
void* memcpy(void* dest, const void* src, size_t num);
int strcmp(const char* s1, const char* s2);
char* strncpy(char* dest, const char* src, size_t n);
size_t strlen(const char* str);
char* strcpy(char* dest, const char* src);
void itoa(int num, char* str);

#endif
