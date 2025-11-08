#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/stdio.h>

#include <libkernel/asm.h>

#include <xfbu/panic.h>

// libc abort is not normally non-returning,
// but kernelspace abort runs panic, which is
// non-returning; userspace libc abort will return
__attribute__((__noreturn__))
void abort(void) {
    panic("__abort: kernel SIGABRT");
    asm_hlt();
    while (1);
    __builtin_unreachable();
}
