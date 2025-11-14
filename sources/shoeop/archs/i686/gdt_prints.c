#include <libkernel/libc/stdio.h>

void gdt_preprint(void) {
    printf(":: enabling segmentation...");
}

void gdt_postprint(void) {
    printf(" OK\n");
}
