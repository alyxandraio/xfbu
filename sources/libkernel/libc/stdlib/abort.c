#include <stdio.h>
#include <stdlib.h>

static inline void cpu_halt(void) {
    __asm__ __volatile__ ("hlt" : : : "memory");
}

__attribute__((__noreturn__))
void abort(void) {
    printf("xfbu kernel panic! halt.\n");
    cpu_halt();
    while (1);
    __builtin_unreachable();
}
