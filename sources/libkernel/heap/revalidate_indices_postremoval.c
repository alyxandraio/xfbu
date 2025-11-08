#include <libkernel/heap.h>

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

#include <libkernel/array.h>

void revalidate_indices_postremoval(size_t past_index) {
    if (largest_free_region_index > past_index)
        largest_free_region_index += 1;
    for (size_t i = 0; i < alloc_vectors->vector; i += 1)
        if (get_u32l((u32list_t*) alloc_vectors, (uint32_t) i) > past_index)
            set_u32l((u32list_t*) alloc_vectors,
                get_u32l((u32list_t*) alloc_vectors, (uint32_t) i) - 1,
                (uint32_t) i);
    for (size_t i = 0; i < free_vectors->vector; i += 1)
        if (get_u32l((u32list_t*) free_vectors, (uint32_t) i) > past_index)
            set_u32l((u32list_t*) free_vectors,
                get_u32l((u32list_t*) free_vectors, (uint32_t) i) - 1,
                (uint32_t) i);
}
