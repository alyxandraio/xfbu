#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/limits.h>

#include <libkernel/multiboot.h>
#include <libkernel/heap.h>

// best malloc implementation 100% working 2025
void* malloc(size_t bytes) {
    if (!heap_valid)
        abort();
    if (alloc_pool_count >= (alloc_pool_size / sizeof(void*)) - 1)
        abort();
    if (free_vectors_count == 0
        || largest_free_region_index == UINT_MAX
        || !largest_free_region_size) {
        void* heap_mem = heap_ptr + heap_vector;
        heap_vector += bytes;
        alloc_pool[alloc_pool_count] = heap_mem;
        alloc_pool_lengths[alloc_pool_count] = bytes;
        alloc_vectors[alloc_vectors_count++] = alloc_pool_count++;
        return heap_mem;
    }
    if (largest_free_region_size == bytes) {
        void* heap_mem = alloc_pool[largest_free_region_index];
        // TODO: FINISH!
    }
}
