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

    const char* s1 = "before:\r\n";
    const char* s2 = "after:\r\n";
    char s3[9];
    char s4[9];
    char s5[9];
    char s6[9];
    const char* s7 = "\r\n";
    int_to_hex(alloc_pool->vector, &s3[0]);
    int_to_hex(alloc_pool_lengths->vector, &s4[0]);
    append_u32l((u32list_t*) alloc_pool, (uint32_t) heap_mem);
    append_u32l((u32list_t*) alloc_pool_lengths, (uint32_t) bytes);
    append_u32l((u32list_t*) alloc_vectors, (uint32_t) (alloc_pool->vector - 1));
    int_to_hex(alloc_pool->vector, &s5[0]);
    int_to_hex(alloc_pool_lengths->vector, &s6[0]);

    print(s1, strlen(s1));
    print(s3, strlen(s3));
    print(s7, strlen(s7));
    print(s4, strlen(s4));
    print(s7, strlen(s7));
    print(s2, strlen(s2));
    print(s5, strlen(s5));
    print(s7, strlen(s7));
    print(s6, strlen(s6));
    print(s7, strlen(s7));
    print(s7, strlen(s7));

    return heap_mem;
}

