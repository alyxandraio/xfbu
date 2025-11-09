#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

#include <libkernel/array.h>
#include <libkernel/heap.h>
#include <libkernel/hex.h>

void* malloc_helper(size_t bytes) {
    void* heap_mem = heap_ptr + heap_vector;
    heap_vector += bytes;

    append_u32l((u32list_t*) alloc_pool, (uint32_t) heap_mem);
    append_u32l((u32list_t*) alloc_pool_lengths, (uint32_t) bytes);
    append_u32l((u32list_t*) alloc_vectors, (uint32_t) (alloc_pool->vector - 1));

    return heap_mem;
}

