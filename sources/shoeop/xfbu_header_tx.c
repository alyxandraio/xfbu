#include <libkernel/xfbu/version.h>
#include <libkernel/shoeop.h>
#include <libkernel/hex.h>
#include <libkernel/bda.h>

#include <stdio.h>

void xfbu_header_tx(void) {
    char com1_hex_str[5]; // really should be using malloc here
    short_to_hex(com1_io_port(), com1_hex_str);
    str_trim_leading_zeroes(com1_hex_str);

    printf("\r\nXFBU kernel v%s (com1@%sh)\r\n", XFBU_VERSION, com1_hex_str);
}
