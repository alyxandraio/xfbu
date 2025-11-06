#include <libkernel/libc/stdio.h>

void gdt_preprint(void) {
    printf(":: GDT initialisation...");
}

void gdt_postprint(void) {
    printf(" OK\n");
}
