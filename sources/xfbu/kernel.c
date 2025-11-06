#include <xfbu/kernel.h>

#include <libkernel/multiboot.h>
#include <libkernel/asm.h>
#include <libkernel/bda.h>
#include <libkernel/hex.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/stdio.h>

void kernel_main(void) {
    bool flags_bit_0 = mbi->flags | 0b00000001;
    printf(":: mbi->mem_* valid? %b\n", flags_bit_0);
    printf(":: mbi->mem_lower = 0x%X\n", mbi->mem_lower);
    printf(":: mbi->mem_upper = 0x%X\n", mbi->mem_upper);
    char* s1 = malloc(13);
    char* s2 = malloc(27);
    printf(":: malloc test 0x%p 0x%p\n", (void*) s1, (void*) s2);
    printf(":: mbi 0x%p\n", (void*) mbi);
    printf(":: testing kernel panic routine...\n");
    abort();
}
