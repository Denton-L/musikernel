#include "terminal.h"
#include "sys.h"

void main() {
	int i;
	char c = 'a';
	int count = 500;
	terminal_initialize();
	while (count--) {
		if (c == 'z' + 1) {
			c = 'a';
		}
		terminal_putchar(c++);
		for (i = 0; i < 100000; i++)
			;
	}
	halt();
}
