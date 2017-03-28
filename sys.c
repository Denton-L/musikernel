#include "sys.h"

void halt() {
	asm volatile ("hlt");
}
