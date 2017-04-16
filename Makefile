CC = i686-elf-gcc -Wall -Wextra -Werror -ffreestanding
AS = i686-elf-as

linker_file = linker.ld
assembly_objects = boot.o
c_objects = sys.o string.o terminal.o musikernel.o
objects = $(assembly_objects) $(c_objects)
output_image = musikernel.img
output_iso = musikernel.iso
grub_config = grub.cfg
iso_dir = iso

.PHONY: clean

$(output_image): $(linker_file) $(objects)
	$(CC) -T $(linker_file) -o $(output_image) -nostdlib $(objects) -lgcc

$(output_iso): $(iso_dir)
	grub-mkrescue -o $(output_iso) $(iso_dir)

$(iso_dir): $(output_image) $(grub_config)
	mkdir -p $(iso_dir)/boot/grub
	cp $(output_image) $(iso_dir)/boot
	cp $(grub_config) $(iso_dir)/boot/grub

$(c_objects): %.o: %.c
	$(CC) -c $< -o $@

$(assembly_objects): %.o: %.s
	$(AS) $< -o $@

clean:
	rm -f *.o *.bin *.iso
	rm -rf $(iso_dir)
