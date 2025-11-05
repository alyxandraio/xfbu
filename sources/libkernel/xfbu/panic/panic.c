#include <libkernel/xfbu/panic.h>

#include <libkernel/asm.h>

#include <stdio.h>

__attribute__((__noreturn__))
void panic(void) {
    asm_cli();
    printf("\npanic!\n");
    i386_regs_print();
    printf("\nhalt.\n");
    asm_hlt();
    while (1);
    __builtin_unreachable();
}
