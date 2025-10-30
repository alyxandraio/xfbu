#include <stdio.h>
#include <stdlib.h>

static inline void cpu_halt(void) {
    __asm__ __volatile__ ("hlt" : : : "memory");
}

__attribute__((__noreturn__))
void abort(void) {
    puts("xfbu: panic!\n");
    cpu_halt();
    while (1);
    __builtin_unreachable();
}
