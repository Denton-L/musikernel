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

uint16_t terminal_getentryat(size_t x, size_t y) {
	return terminal_buffer[y * VGA_WIDTH + x];
}

void terminal_putentryat(uint16_t entry, size_t x, size_t y) {
	terminal_buffer[y * VGA_WIDTH + x] = entry;
}

void terminal_scroll(size_t lines) {
	const uint16_t blank = vga_entry(' ', terminal_color);
	size_t column;
	size_t row;

	for (row = 0; row + lines < VGA_HEIGHT; row++) {
		for (column = 0; column < VGA_WIDTH; column++)
			terminal_putentryat(terminal_getentryat(column, row + lines), column, row);
	}
	for (; row < VGA_HEIGHT; row++) {
		for (column = 0; column < VGA_WIDTH; column++)
			terminal_putentryat(blank, column, row);
	}
}

static void terminal_newline() {
	terminal_column = 0;
	if (++terminal_row >= VGA_HEIGHT) {
		terminal_row = VGA_HEIGHT - 1;
		terminal_scroll(1);
	}
}

void terminal_putchar(char c) {
	switch (c) {
		case '\n':
			terminal_newline();
			break;
		default:
			terminal_putentryat(vga_entry(c, terminal_color), terminal_column, terminal_row);
			if (++terminal_column >= VGA_WIDTH)
				terminal_newline();
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

	for (index = 0; index < VGA_WIDTH * VGA_HEIGHT; index++)
		terminal_buffer[index] = blank;
}

void terminal_initialize() {
	terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
	terminal_clear();
}
