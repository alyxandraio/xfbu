#include <libkernel/libc/stdlib.h>

#include <libkernel/heap.h>

void free(void* ptr) {
    if (!heap_valid)
        abort();
}
