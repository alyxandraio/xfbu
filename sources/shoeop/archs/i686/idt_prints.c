#include <libkernel/libc/stdio.h>

void idt_preprint(void) {
    printf(":: enabling interrupts...");
}

void idt_postprint(void) {
    printf(" OK\n");
}
