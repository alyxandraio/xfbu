#include <xfbu/kernel.h>

#include <xfbu/panic.h>

#include <libkernel/archs/i686/multiboot.h>
#include <libkernel/archs/i686/bda.h>
#include <libkernel/xfbu/info.h>
#include <libkernel/asm.h>
#include <libkernel/hex.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/stdio.h>

void kernel_main(void) {
    void* paging_test_ptr = malloc(0xc43);
    printf(":: malloc/paging test 0x%p\n", paging_test_ptr);
    free(paging_test_ptr);
    printf(":: testing kernel panic routine...\n");
    panic("__kernel_main: test of `__panic` function for demonstrative purposes");
}
