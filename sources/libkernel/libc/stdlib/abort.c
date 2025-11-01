#include <stdio.h>
#include <stdlib.h>

#include <libkernel/asm.h>

__attribute__((__noreturn__))
void abort(void) {
    printf(":: xfbu kernel panic! halt.\r\n");
    asm_hlt();
    while (1);
    __builtin_unreachable();
}
