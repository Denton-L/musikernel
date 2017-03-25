AS=i686-elf-as

.PHONY: all clean

all: boot.o

boot.o: boot.s
	$(AS) boot.s -o boot.o

clean:
	rm *.o
