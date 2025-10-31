#include <libkernel/multiboot.h>
#include <libkernel/xfbu.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void multiboot_check(uint32_t magic) {
    printf(":: multiboot magic comparison...");
    if (magic == MULTIBOOT_RX_MAGIC)
        printf(" OK\n");
    else {
        printf(" FAIL\n");
        abort();
    }
}

void kernel_main(uint32_t magic, uint32_t mbptr) {
    printf("XFBU kernel v%s\n", XFBU_VERSION);
    multiboot_check(magic);
}
