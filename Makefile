CC = i686-elf-gcc -Wall -Wextra -Werror -ffreestanding
AS = i686-elf-as

linker_file = linker.ld
assembly_objects = boot.o
c_objects = sys.o string.o terminal.o musikernel.o
objects = $(assembly_objects) $(c_objects)
output_binary = musikernel.bin
output_iso = musikernel.iso
grub_config = grub.cfg
iso_dir = iso

.PHONY: cd clean

$(output_binary) : $(linker_file) $(objects)
	$(CC) -T $(linker_file) -o $(output_binary) -nostdlib $(objects) -lgcc

cd : $(output_iso)

$(output_iso) : $(iso_dir)
	grub-mkrescue -o $(output_iso) $(iso_dir)

$(iso_dir) : $(output_binary) $(grub_config)
	mkdir -p $(iso_dir)/boot/grub
	cp $(output_binary) $(iso_dir)/boot
	cp $(grub_config) $(iso_dir)/boot/grub

$(c_objects): %.o: %.c
	$(CC) -c $< -o $@

$(assembly_objects): %.o: %.s
	$(AS) $< -o $@

clean:
	rm -f *.o *.bin *.iso
	rm -rf $(iso_dir)
