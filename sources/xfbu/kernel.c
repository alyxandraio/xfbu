#include <libkernel/multiboot.h>
#include <libkernel/asm.h>
#include <libkernel/bda.h>
#include <libkernel/hex.h>

#include <xfbu/kernel.h>
#include <xfbu/version.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void kernel_main(uint32_t magic, uint32_t mbptr) {
    uint16_t com1_device = com1_io_port();
    char com1_hex_str[5]; // really should be using malloc here
    short_to_hex(com1_device, com1_hex_str);
    str_trim_leading_zeroes(com1_hex_str);

    printf("XFBU kernel v%s (com1@%sh)\n", XFBU_VERSION, com1_hex_str);
    multiboot_check(magic);

    asm_cli();
}
