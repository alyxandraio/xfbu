#include <xfbu/panic.h>

#include <libkernel/heap.h>

__attribute__((__noreturn__))
void panic_noheap(const char* s) {
    heap_valid = false;
    panic(s);
    __builtin_unreachable();
}
