#include <xfbu/kernel.h>

#include <libkernel/multiboot.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void multiboot_check(uint32_t magic) {
    printf(":: multiboot magic comparison...");
    if (magic == MULTIBOOT_RX_MAGIC)
        printf(" OK\r\n");
    else {
        printf(" FAIL\r\n");
        abort();
    }
}
