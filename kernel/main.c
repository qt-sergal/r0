
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <io/com.h>

__attribute__((interrupt)) void generic_exception_handler(struct interrupt_frame *frame)
{
    serial_write_string(COM1, "Interrupt occured\n");
}

int kmain() {
    serial_init(COM1);
    // NULL descriptor
    set_gdt_entry(0, 0, 0, 0, 0);

    // Code segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    install_gdt(3);
    for (s32 i = 0; i < 32; ++i) {
        set_idt_entry(i, generic_exception_handler);
    }
    remap_pic(32, 47);
    install_idt();
    asm("sti");
    return 0;
}