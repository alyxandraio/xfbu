#include <libkernel/libc/stdio.h>

#include <shoeop/shoeop.h>

void gdt_preprint(void) {
    within_shoeop_process = true;
    printf(":: enabling segmentation...");
}

void gdt_postprint(void) {
    printf(" OK\n");
    within_shoeop_process = false;
}
