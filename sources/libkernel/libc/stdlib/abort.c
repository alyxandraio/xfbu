#include <stdio.h>
#include <stdlib.h>

#include <libkernel/xfbu/panic.h>
#include <libkernel/asm.h>

void abort(void) {
    // if we're in kernel space ...
    panic();
}
