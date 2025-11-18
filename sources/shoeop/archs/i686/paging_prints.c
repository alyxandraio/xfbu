#include <libkernel/libc/stdio.h>

#include <shoeop/shoeop.h>

void paging_preprint(void) {
    within_shoeop_process = true;
    printf(":: enabling paging...");
}

void paging_postprint(void) {
    printf(" OK\n");
    within_shoeop_process = false;
}
