#include "terminal.h"

#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t terminal_column;
static size_t terminal_row;
static uint8_t terminal_color;
static volatile uint16_t *terminal_buffer = (uint16_t *) 0xB8000;

inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char c, uint8_t color) {
	return (uint16_t) c | (uint16_t) color << 8;
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(uint16_t entry, size_t x, size_t y) {
	terminal_buffer[y * VGA_WIDTH + x] = entry;
}

void terminal_putchar(char c) {
	switch (c) {
		case '\n':
			terminal_column = 0;
			if (++terminal_row >= VGA_HEIGHT)
				terminal_row = 0;
			break;
		default:
			terminal_putentryat(vga_entry(c, terminal_color), terminal_column, terminal_row);
			if (++terminal_column >= VGA_WIDTH) {
				terminal_column = 0;
				if (++terminal_row >= VGA_HEIGHT)
					terminal_row = 0;
			}
			break;
	}
}

void terminal_writestring(const char *str) {
	size_t index = 0;
	while (str[index])
		terminal_putchar(str[index++]);
}

void terminal_clear() {
	const uint16_t blank = vga_entry(' ', terminal_color);
	size_t index;

	terminal_column = 0;
	terminal_row = 0;

	for (index = VGA_WIDTH * VGA_HEIGHT - 1; index >= 0; index--)
		terminal_buffer[index] = blank;
}

void terminal_initialize() {
	terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
	terminal_clear();
}
