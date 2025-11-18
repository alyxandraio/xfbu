#include <libkernel/heap.h>

#include <libkernel/libc/sys/malloc.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

#include <libkernel/archs/i686/multiboot.h>
#include <libkernel/archs/i686/paging.h>

#include <xfbu/panic.h>

void virtual_map_4mib_aligned(uint16_t index_4mib, )

void identity_map_4mib_aligned(uint16_t index_4mib) {
    if (index_4mib > 1023)
        panic("__identity_map_4mib_aligned: page dir index out of bounds");
    size_t heap_end = (size_t) (heap_ptr + heap_vector);
    size_t needed = 0x1000 - (heap_end % 0x1000);
    forcibly_advance_vector = true;
    void* temp_alloc = (void*) 0;
    if (needed > 0)
        temp_alloc = malloc(needed);
    uint32_t* identity_map = (uint32_t*) malloc(0x1000);
    forcibly_advance_vector = false;
    if (needed > 0)
        free(temp_alloc);
    if (identity_map % 0x1000 != 0 || heap_vector % 0x1000 != 0)
        panic_failout("__identity_map_4mib_aligned: invalid heap allocation");

    memset(identity_map, 0, 0x1000);
    page_directory[index_4mib] = (uint32_t**) identity_map;
    // present; write enabled; supervisor; 4KiB pages
    page_directory[index_4mib] &= 0xffffff43;
    const size_t four_mib = 4096 * 1024;
    size_t lower_bound = index_4mib * four_mib;
    // size_t upper_bound = lower_bound + four_mib;
    for (size_t index = 0; index < 1024; index += 1) {
        identity_map[index] = (uint32_t*) (0x1000*index + lower_bound);
        // present; write enabled; supervisor; non-global
        identity_map[index] &= 0xfffffe03;
    }
}

size_t populate_cr3(void) {
    size_t heap_end = (size_t) (heap_ptr + heap_vector);
    size_t needed = 0x1000 - (heap_end % 0x1000);
    forcibly_advance_vector = true;
    void* temp_alloc = malloc(needed);
    uint32_t*** page_dir = (uint32_t***) malloc(0x1000);
    forcibly_advance_vector = false;
    free(temp_alloc);
    if (page_dir % 0x1000 != 0 || heap_vector % 0x1000 != 0)
        panic_failout("__populate_cr3: invalid heap allocation");

    page_directory = page_dir;
    memset(page_directory, 0, 0x1000);

    for (size_t index = 0; index < 128; index += 1)
        identity_map_4mib_aligned(index);

    return (size_t) page_directory;
}
