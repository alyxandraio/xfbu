#include <libkernel/archs/i686/bda.h>
#include <libkernel/xfbu/info.h>
#include <libkernel/util.h>
#include <libkernel/hex.h>

#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

void xfbu_header_tx(void) {
    char com1_hex_str[5];
    short_to_hex(com1_io_port(), com1_hex_str);
    str_trim_leading_zeroes(com1_hex_str);
    const char* s1 = "\r\n";
    const char* s2 = "XFBU kernel v";
    const char* s3 = XFBU_VERSION;
    const char* s4 = " (com1@";
    const char* s5 = com1_hex_str;
    const char* s6 = "h)";
    const char* s7 = s1;

    print(s1, strlen(s1));
    print(s2, strlen(s2));
    print(s3, strlen(s3));
    print(s4, strlen(s4));
    print(s5, strlen(s5));
    print(s6, strlen(s6));
    print(s7, strlen(s7));
}
