_CC=i686-elf-gcc

ARCH?=i386

TARGET= ${ARCH}-pc-none-bin

_CF= -I kernel/inc
_EF= -serial stdio -net none -m 2M
NAME= r0

run: clean kernel.bin
	qemu-system-${ARCH} ${_EF} -kernel kernel.bin

kernel.bin: boot.o kernel.o
	ld -m elf_i386 -T linker.ld -o $@ $^

boot.o:
	nasm -f elf32 kernel/boot.asm -o $@

kernel.o:
	${_CC} -c -o $@ ${_CF} kernel/main.c

clean:
	rm -rf *.bin *.o *.iso