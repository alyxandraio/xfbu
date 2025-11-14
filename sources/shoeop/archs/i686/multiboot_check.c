#include <libkernel/multiboot.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

void multiboot_check(uint32_t magic) {
    const char* s1 = ":: multiboot magic comparison...";
    // carriage return required;
    // newline helper only present on printf
    const char* s2 = " OK\r\n";
    const char* s3 = " FAIL\r\n";
    print(s1, strlen(s1));
    if (magic == MULTIBOOT_RX_MAGIC) {
        multiboot_valid = true;
        print(s2, strlen(s2));
    } else {
        print(s3, strlen(s3));
        abort();
    }
}
