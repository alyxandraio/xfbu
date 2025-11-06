#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/limits.h>

#include <libkernel/multiboot.h>
#include <libkernel/array.h>
#include <libkernel/heap.h>

void* malloc_helper(size_t bytes) {
    void* heap_mem = heap_ptr + heap_vector;
    heap_vector += bytes;

    append_u32l((u32list_t*) alloc_vectors, alloc_pool->vector);
    append_u32l((u32list_t*) alloc_pool, (uint32_t) heap_mem);
    append_u32l((u32list_t*) alloc_pool_lengths, bytes);

    return heap_mem;
}

// best memory allocator implementation 100% working 2025 /s
void* malloc(size_t bytes) {
    if (!heap_valid)
        abort();
    if (alloc_pool->vector >= alloc_pool->length - 1)
        abort();
    if (bytes == 0)
        abort();
    if (largest_free_region_size == bytes) {
        void* heap_mem = (void*) get_u32l((u32list_t*) alloc_pool,
            (size_t) get_u32l((u32list_t*) free_vectors, largest_free_region_index));
        append_u32l((u32list_t*) alloc_vectors,
            get_u32l((u32list_t*) free_vectors, largest_free_region_index));
        remove_at_u32l((u32list_t*) free_vectors, largest_free_region_index);

        push_u32l((u32list_t*) alloc_pool_lengths, 0);
        size_t max_index = alloc_pool_lengths->vector - 1;
        // skip the final free_vectors element, our dummy 0 entry
        for (size_t i = 0; i < free_vectors->vector - 1; i += 1)
            if (get_u32l((u32list_t*) alloc_pool_lengths, get_u32l((u32list_t*) free_vectors, i)) > get_u32l((u32list_t*) alloc_pool_lengths, max_index))
                max_index = i;
        if (max_index == alloc_pool_lengths->vector - 1)
            abort();
        pop_u32l((u32list_t*) alloc_pool_lengths);
        largest_free_region_index = max_index;
        largest_free_region_size = get_u32l((u32list_t*) alloc_pool_lengths, max_index);
        return heap_mem;
    }
    if (largest_free_region_size > bytes) {
        // TODO: FINISH!
    }
    return malloc_helper(bytes);
}
