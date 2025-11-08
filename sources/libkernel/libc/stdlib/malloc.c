#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/limits.h>
#include <libkernel/libc/stdio.h>

#include <libkernel/multiboot.h>
#include <libkernel/array.h>
#include <libkernel/heap.h>

#include <xfbu/panic.h>

extern void* malloc_helper(size_t);

// INFO: WHEN YOU REMOVE OR INSERT INTO ALLOC_POOL,
// ALLOC_VECTORS AND FREE_VECTORS ABOVE
// THE INDEX AND THE LARGEST_FREE_REGION_*
// GLOBALS BECOME INVALID !!

// best memory allocator implementation 100% working 2025 /s
void* malloc(size_t bytes) {
    if (!heap_valid)
        panic("__malloc: heap invalid");
    if (alloc_pool->vector >= alloc_pool->length - 1)
        panic("__malloc: allocation pool full");
    if (bytes == 0)
        panic("__malloc: cannot pass 0");
    if (largest_free_region_size == bytes) {
        void* heap_mem = (void*) get_u32l((u32list_t*) alloc_pool,
            (size_t) get_u32l((u32list_t*) free_vectors, largest_free_region_index));
        append_u32l((u32list_t*) alloc_vectors,
            get_u32l((u32list_t*) free_vectors, largest_free_region_index));
        remove_at_u32l((u32list_t*) free_vectors, largest_free_region_index);

        if (free_vectors->vector == 0) {
            largest_free_region_index = UINT_MAX;
            largest_free_region_size = 0;
            return heap_mem;
        }

        push_u32l((u32list_t*) alloc_pool_lengths, 0);
        size_t max_index = alloc_pool_lengths->vector - 1;
        // skip the final free_vectors element, our dummy 0 entry
        for (size_t i = 0; i < free_vectors->vector - 1; i += 1)
            if (get_u32l((u32list_t*) alloc_pool_lengths, get_u32l((u32list_t*) free_vectors, i)) > get_u32l((u32list_t*) alloc_pool_lengths, max_index))
                max_index = i;
        if (max_index == alloc_pool_lengths->vector - 1)
            panic("__malloc: did not find free region of memory larger than 0");
        pop_u32l((u32list_t*) alloc_pool_lengths);
        largest_free_region_index = max_index;
        largest_free_region_size = get_u32l((u32list_t*) alloc_pool_lengths, max_index);
        return heap_mem;
    }
    if (largest_free_region_size > bytes) {
        void* heap_mem = (void*) get_u32l((u32list_t*) alloc_pool,
            (size_t) get_u32l((u32list_t*) free_vectors, largest_free_region_index));
        void* newly_freed = heap_mem + bytes;
        append_u32l((u32list_t*) alloc_vectors,
            get_u32l((u32list_t*) free_vectors, largest_free_region_index));
        set_u32l((u32list_t*) free_vectors,
            (uint32_t) newly_freed, largest_free_region_index);
        set_u32l((u32list_t*) alloc_pool_lengths,
            (uint32_t) bytes, get_u32l((u32list_t*) alloc_vectors, largest_free_region_index));
        insert_u32l((u32list_t*) alloc_pool,
            (uint32_t) newly_freed, largest_free_region_index + 1);
        insert_u32l((u32list_t*) alloc_pool_lengths,
            largest_free_region_size - bytes, largest_free_region_index + 1);
        revalidate_indices_postinsertion(largest_free_region_index + 1);

        push_u32l((u32list_t*) alloc_pool_lengths, 0);
        size_t max_index = alloc_pool_lengths->vector - 1;
        for (size_t i = 0; i < free_vectors->vector - 1; i += 1)
            if (get_u32l((u32list_t*) alloc_pool_lengths, get_u32l((u32list_t*) free_vectors, i)) > get_u32l((u32list_t*) alloc_pool_lengths, max_index))
                max_index = i;
        if (max_index == alloc_pool_lengths->vector - 1)
            panic("__malloc: did not find free region of memory larger than 0");
        pop_u32l((u32list_t*) alloc_pool_lengths);
        largest_free_region_index = max_index;
        largest_free_region_size = get_u32l((u32list_t*) alloc_pool_lengths, max_index);
        return heap_mem;
    }
    return malloc_helper(bytes);
}
