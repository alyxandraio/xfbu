#include <libkernel/xfbu/panic.h>

extern void asm_i386_regs_print_helper(void);

void i386_regs_print(void) {
    asm_i386_regs_print_helper();
}
