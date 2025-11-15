#include <libkernel/xfbu/panic.h>

#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

#include <libkernel/archs/i686/multiboot.h>
#include <libkernel/asm.h>

void print_stack_trace(void) {
    size_t* ebp = (size_t*) reg_ebp();
    printf("stack trace:\n");
    for (size_t depth = 0; ebp && depth < 64; depth += 1) {
        size_t offset;
        size_t* returnaddr = (size_t*) ebp[1];
        char* symbol = symbol_lookup(returnaddr, &offset);
        if (strcmp(symbol, "") == 0)
            symbol = "__unknown";
        printf("    %s+0x%x\n", symbol, offset);

        size_t* recursed_ebp = (size_t*) ebp[0];
        if (recursed_ebp <= ebp)
            break;
        ebp = recursed_ebp;
    }
}
