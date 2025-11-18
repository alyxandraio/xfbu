#include <libkernel/libc/stdio.h>

#include <shoeop/shoeop.h>

void idt_preprint(void) {
    within_shoeop_process = true;
    printf(":: enabling interrupts...");
}

void idt_postprint(void) {
    printf(" OK\n");
    within_shoeop_process = false;
}
