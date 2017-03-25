CC = i686-elf-gcc -Wall -ffreestanding -c
AS = i686-elf-as

assembly_objects = boot.o
c_objects = string.o terminal.o

.PHONY: all clean

all: $(assembly_objects) $(c_objects)

$(c_objects): %.o: %.c
	$(CC) $< -o $@

$(assembly_objects): %.o: %.s
	$(AS) $< -o $@

clean:
	rm *.o
