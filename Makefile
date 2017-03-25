CC = i686-elf-gcc -Wall -ffreestanding
AS = i686-elf-as

linker_file = linker.ld
assembly_objects = boot.o
c_objects = string.o terminal.o musikernel.o
objects = $(assembly_objects) $(c_objects)
output_image = musikernel.bin

.PHONY: clean

$(output_image) : $(linker_file) $(objects)
	$(CC) -T $(linker_file) -o $(output_image) -nostdlib $(objects) -lgcc

$(c_objects): %.o: %.c
	$(CC) -c $< -o $@

$(assembly_objects): %.o: %.s
	$(AS) $< -o $@

clean:
	rm -f *.o *.bin
