CC=i686-elf-gcc -Wall -ffreestanding
AS=i686-elf-as

.PHONY: all clean

all: boot.o string.o

string.o: string.c
	$(CC) -c string.c -o string.o

boot.o: boot.s
	$(AS) boot.s -o boot.o

clean:
	rm *.o
