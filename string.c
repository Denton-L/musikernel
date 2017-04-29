#include "string.h"

#include <stddef.h>

size_t strlen(const char *str) {
	size_t len = 0;
	while (str[len])
		++len;
	return len;
}

void *memset(void *ptr, int value, size_t num) {
	unsigned char real_value = (unsigned char) value;
	char *real_ptr = (char *) ptr;

	while (num > 0)
		real_ptr[--num] = real_value;

	return ptr;
}
