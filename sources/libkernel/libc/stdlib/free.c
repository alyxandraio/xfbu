#include <libkernel/libc/stdlib.h>

#include <libkernel/libc/limits.h>
#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

#include <libkernel/array.h>
#include <libkernel/heap.h>
#include <libkernel/hex.h>

#include <xfbu/panic.h>

void free(void* ptr) {
    if (!heap_valid)
        panic("__free: heap invalid");
    if (ptr < (void*) 0x1000)
        panic("__free: `ptr` within page 0");
    if (alloc_pool->vector >= alloc_pool->length - 1)
        panic("__free: allocation pool full");

    // `unsafefind_u32l` triggers a kernel panic if `ptr` is not a member of `alloc_pool`
    size_t pool_idx = (size_t) unsafefind_u32l((u32list_t*) alloc_pool, (uint32_t) ptr);
    size_t avec_idx = (size_t) unsafefind_u32l((u32list_t*) alloc_vectors, (uint32_t) pool_idx);

    size_t leading_idx = UINT_MAX;
    size_t trailing_idx = UINT_MAX;
    char s1[9];
    char s2[9];
    char s3[9];
    const char* s4 = "\r\n";
    int_to_hex(alloc_pool->vector, &s1[0]);
    int_to_hex(alloc_pool_lengths->vector, &s2[0]);
    int_to_hex(pool_idx, &s3[0]);
    print(s4, strlen(s4));
    print(s1, strlen(s1));
    print(s4, strlen(s4));
    print(s2, strlen(s2));
    print(s4, strlen(s4));
    print(s3, strlen(s3));
    print(s4, strlen(s4));
    size_t ptr_bytes = (size_t) get_u32l((u32list_t*) alloc_pool_lengths, pool_idx);
    for (size_t i = 0; i < free_vectors->vector; i += 1) {
        size_t idx = (size_t) get_u32l((u32list_t*) free_vectors, i);
        void* mem = (void*) get_u32l((u32list_t*) alloc_pool, idx);
        size_t bytes = (size_t) get_u32l((u32list_t*) alloc_pool_lengths, idx);

        // mutually exclusive
        if (mem + bytes == ptr)
            leading_idx = idx;
        if (ptr + ptr_bytes == mem)
            trailing_idx = idx;
    }
    if (leading_idx != UINT_MAX && trailing_idx != UINT_MAX) {
        // set the length of the leading allocation to
        // the sum of the lengths of all 3 allocations
        size_t leading_len = (size_t) get_u32l((u32list_t*) alloc_pool_lengths,
            get_u32l((u32list_t*) free_vectors, leading_idx));
        size_t trailing_len = (size_t) get_u32l((u32list_t*) alloc_pool_lengths,
            get_u32l((u32list_t*) free_vectors, trailing_idx));
        set_u32l((u32list_t*) alloc_pool_lengths,
            leading_len + ptr_bytes + trailing_len,
            get_u32l((u32list_t*) free_vectors, leading_idx));
        // remove trailing ptr and `ptr` from alloc_pool
        remove_at_u32l((u32list_t*) alloc_pool, pool_idx);
        remove_at_u32l((u32list_t*) alloc_pool_lengths, pool_idx);
        revalidate_indices_postremoval(pool_idx);
        remove_at_u32l((u32list_t*) alloc_pool,
            get_u32l((u32list_t*) free_vectors, trailing_idx));
        remove_at_u32l((u32list_t*) alloc_pool_lengths,
            get_u32l((u32list_t*) free_vectors, trailing_idx));
        revalidate_indices_postremoval((size_t) get_u32l((u32list_t*) free_vectors, trailing_idx));
        // remove `ptr` from alloc_vectors;
        // remove trailing free region from `free_vectors`,
        // remember that the leading region now includes all 3 regions
        remove_at_u32l((u32list_t*) alloc_vectors, avec_idx);
        remove_at_u32l((u32list_t*) free_vectors, trailing_idx);
        goto find_largest_free_region;
    }
    // last check skips this section,
    // so these are guaranteed not to run if
    // both variables are not UINT_MAX
    if (leading_idx != UINT_MAX) {
        size_t leading_len = (size_t) get_u32l((u32list_t*) alloc_pool_lengths,
            get_u32l((u32list_t*) free_vectors, leading_idx));
        set_u32l((u32list_t*) alloc_pool_lengths,
            leading_len + ptr_bytes,
            get_u32l((u32list_t*) free_vectors, leading_idx));
        remove_at_u32l((u32list_t*) alloc_pool, pool_idx);
        remove_at_u32l((u32list_t*) alloc_pool_lengths, pool_idx);
        revalidate_indices_postremoval(pool_idx);
        remove_at_u32l((u32list_t*) alloc_vectors, avec_idx);
        goto find_largest_free_region;
    }
    // no adjacent free memory :(
    remove_at_u32l((u32list_t*) alloc_vectors, avec_idx);
    append_u32l((u32list_t*) free_vectors, pool_idx);
    if (ptr_bytes > largest_free_region_size) {
        largest_free_region_size = ptr_bytes;
        largest_free_region_index = pool_idx;
    }

    find_largest_free_region:
    push_u32l((u32list_t*) alloc_pool_lengths, 0);
    size_t max_index = alloc_pool_lengths->vector - 1;
    for (size_t i = 0; i < free_vectors->vector - 1; i += 1)
        if (get_u32l((u32list_t*) alloc_pool_lengths, get_u32l((u32list_t*) free_vectors, i)) > get_u32l((u32list_t*) alloc_pool_lengths, max_index))
            max_index = i;
    if (max_index == alloc_pool_lengths->vector - 1)
        panic("__free: did not find free region of memory larger than 0");
    pop_u32l((u32list_t*) alloc_pool_lengths);
    largest_free_region_index = max_index;
    largest_free_region_size = get_u32l((u32list_t*) alloc_pool_lengths, max_index);
}
