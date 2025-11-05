#include <xfbu/kernel.h>

#include <libkernel/multiboot.h>
#include <libkernel/asm.h>
#include <libkernel/bda.h>
#include <libkernel/hex.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void kernel_main(uint32_t mbaddr) {
    multiboot_info_t* mbi = (multiboot_info_t*) (uintptr_t) mbaddr;

}
