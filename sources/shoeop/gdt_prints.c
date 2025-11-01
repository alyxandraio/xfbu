#include <stdio.h>

void gdt_preprint(void) {
    printf(":: initialising GDT...");
}

void gdt_postprint(void) {
    printf(" OK\r\n");
}
