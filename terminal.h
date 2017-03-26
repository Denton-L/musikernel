#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
inline uint16_t vga_entry(unsigned char c, uint8_t color);
void terminal_setcolor(uint8_t color);
uint16_t terminal_getentryat(size_t x, size_t y);
void terminal_putentryat(uint16_t entry, size_t x, size_t y);
void terminal_scroll(size_t lines);
void terminal_putchar(char c);
void terminal_writestring(const char *str);
void terminal_clear();
void terminal_initialize();

#endif
