#include <xfbu/panic.h>

__attribute__((__noreturn__))
void panic_failout(const char* s) {
    printf(" FAIL\n");
    panic(s);
    while (1);
    __builtin_unreachable();
}
