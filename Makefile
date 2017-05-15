CC = i686-elf-gcc -Wall -Wextra -Werror -ffreestanding
AS = i686-elf-as

C_SOURCES = $(wildcard *.c)
AS_SOURCES = $(wildcard *.s)
C_OBJECTS = ${C_SOURCES:.c=.o}
AS_OBJECTS = ${AS_SOURCES:.s=.o}
OBJECTS = $(C_OBJECTS) $(AS_OBJECTS)
LINKER_FILE = linker.ld
OUTPUT_IMAGE = musikernel.img
OUTPUT_ISO = musikernel.iso
GRUB_CONFIG = grub.cfg
ISO_DIR = iso

.PHONY: clean

$(OUTPUT_IMAGE): $(LINKER_FILE) $(OBJECTS)
	$(CC) -T $(LINKER_FILE) -o $(OUTPUT_IMAGE) -nostdlib $(OBJECTS) -lgcc

$(OUTPUT_ISO): $(ISO_DIR)
	grub-mkrescue -o $(OUTPUT_ISO) $(ISO_DIR)

$(ISO_DIR): $(OUTPUT_IMAGE) $(GRUB_CONFIG)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(OUTPUT_IMAGE) $(ISO_DIR)/boot
	cp $(GRUB_CONFIG) $(ISO_DIR)/boot/grub

$(C_OBJECTS): %.o: %.c
	$(CC) -c $< -o $@

$(ASSEMBLY_OBJECTS): %.o: %.s
	$(AS) $< -o $@

clean:
	rm -f *.o *.bin *.iso
	rm -rf $(ISO_DIR)
