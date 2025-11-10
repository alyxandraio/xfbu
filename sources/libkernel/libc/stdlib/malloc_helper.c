#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

#include <libkernel/array.h>
#include <libkernel/heap.h>
#include <libkernel/hex.h>

#include <xfbu/panic.h>

void* malloc_helper(size_t bytes) {
    void* heap_mem = heap_ptr + heap_vector;

    append_u32l((u32list_t*) alloc_pool, (uint32_t) heap_mem);
    append_u32l((u32list_t*) alloc_pool_lengths, (uint32_t) bytes);
    append_u32l((u32list_t*) alloc_vectors, (uint32_t) (alloc_pool->vector - 1));

    if (get_u32l((u32list_t*) alloc_pool,
        get_u32l((u32list_t*) alloc_vectors, alloc_vectors->vector - 1))
        != heap_mem)
        panic_noheap("__malloc_helper: unusual state 0");
    if (get_u32l((u32list_t*) alloc_pool_lengths,
        get_u32l((u32list_t*) alloc_vectors, alloc_vectors->vector - 1))
        != bytes)
        panic_noheap("__malloc_helper: unusual state 1");

    heap_vector += bytes;
    return heap_mem;
}

