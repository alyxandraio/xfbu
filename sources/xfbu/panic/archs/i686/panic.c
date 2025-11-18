#include <xfbu/panic.h>

#include <shoeop/shoeop.h>

#include <libkernel/xfbu/panic.h>
#include <libkernel/asm.h>

#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

// INFO: do not include a final newline
// or carriage return (or both) in `s`
// unless a trailing whitespace line is desired
__attribute__((__noreturn__))
void panic(const char* s) {
    asm_cli();
    const char* s1 = "\r\npanic!\r\ncaller ";
    const char* s2 = "\r\n";
    const char* s3 = "\r\nhalt.\r\n";
    const char* s4 = " FAIL\r\n";
    if (within_shoeop_process)
        print(s4, strlen(s4));
    within_shoeop_process = false;
    print(s1, strlen(s1));
    if (s != (char*) 0)
        print(s, strlen(s));
    print(s2, strlen(s2));
    i686_regs_print();
    print(s3, strlen(s3));
    asm_hlt();
    while (1);
    __builtin_unreachable();
}
