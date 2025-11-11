#include <xfbu/kernel.h>

#include <xfbu/panic.h>

#include <libkernel/xfbu/info.h>
#include <libkernel/multiboot.h>
#include <libkernel/asm.h>
#include <libkernel/bda.h>
#include <libkernel/hex.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/stdio.h>

void kernel_main(void) {
    bool flags_bit_0 = mbi->flags | 0b00000001;
    bool flags_bit_4 = mbi->flags | 0b00010000;
    bool flags_bit_5 = mbi->flags | 0b00100000;
    printf(":: kernel size = %u KiB\n", XFBU_BINARY_SIZE / 1024);
    printf(":: cr0 = 0x%X\n", reg_cr0());
    printf(":: testing kernel panic routine...\n");
    panic("__kernel_main: test of `__panic` function for demonstrative purposes");
}
