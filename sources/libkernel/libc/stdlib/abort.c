#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/stdio.h>

#include <libkernel/xfbu/panic.h>
#include <libkernel/asm.h>

void abort(void) {
    // if we're in kernel space ...
    panic();
}
