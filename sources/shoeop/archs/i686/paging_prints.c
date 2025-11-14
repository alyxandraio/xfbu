#include <libkernel/libc/stdio.h>

void paging_preprint(void) {
    printf(":: enabling paging...");
}

void paging_postprint(void) {
    printf(" OK\n");
}
