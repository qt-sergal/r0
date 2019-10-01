CC= clang-8

ARCH?=i386

TARGET= ${ARCH}-pc-none-bin

KERNEL_CF= ${CF} -I kernel/inc -target ${TARGET}
CF= -nostdlib -ffreestanding
EF= -serial stdio -net none -m 2M
NAME= r0

run: clean kernel.bin
	qemu-system-${ARCH} ${EF} -kernel kernel.bin

boot.o:
	nasm -f elf32 kernel/boot.s -o $@

kernel.bin: boot.o
	${CC} -T linker.ld -o $@ ${KERNEL_CF} $^ kernel/main.c

clean:
	rm -rf *.bin *.o *.iso