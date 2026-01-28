#ifndef VGA_H
#define VGA_H

#include "lib/types.h"

#define VGA_WIDTH  320
#define VGA_HEIGHT 200

#define COLOR_BLACK     0
#define COLOR_BLUE      1
#define COLOR_GREEN     2
#define COLOR_CYAN      3
#define COLOR_RED       4
#define COLOR_MAGENTA   5
#define COLOR_BROWN     6
#define COLOR_LGRAY     7
#define COLOR_DGRAY     8
#define COLOR_LBLUE     9
#define COLOR_LGREEN    10
#define COLOR_LCYAN     11
#define COLOR_LRED      12
#define COLOR_LMAGENTA  13
#define COLOR_YELLOW    14
#define COLOR_WHITE     15

void vga_init(void);
void vga_putpixel(int x, int y, uint8_t color);
void vga_clear(uint8_t color);
void vga_fillrect(int x, int y, int w, int h, uint8_t color);
void vga_rect(int x, int y, int w, int h, uint8_t color);
void vga_putchar(int x, int y, char c, uint8_t color);
void vga_print(int x, int y, const char* str, uint8_t color);
void vga_swap(void);

#endif
