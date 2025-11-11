#include <libkernel/heap.h>

#include <libkernel/libc/sys/malloc.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

#include <libkernel/paging.h>

#include <xfbu/panic.h>

size_t populate_cr3(void) {
    size_t heap_end = (size_t) heap_ptr + heap_vector;
    size_t needed = 0x1000 - (heap_end % 0x1000);
    forcibly_advance_vector = true;
    void* temp_alloc = malloc(needed);
    void* page_dir = malloc(4096);
    void* identity_map = malloc(4096);
    void* kernel_map = malloc(4096);
    forcibly_advance_vector = false;
    free(temp_alloc);
    if (page_dir + 4096 != identity_map || page_dir + 8192 != kernel_map) {
        printf(" FAIL\n");
        panic("__populate_cr3: paging entries are not contiguous");
    }
    // since all 3 pointers are contiguous, we can
    // memset starting at the first pointer with
    // enough iterations to populate all 3 memory regions
    memset(page_dir, 0, 4096 * 3);
    if ((size_t) page_dir % 0x1000 != 0) {
        printf(" FAIL\n");
        panic("__populate_cr3: page directory physaddr not divisible by 0x1000");
    }
    page_directory = (uint32_t**) page_dir;
    return (size_t) page_directory;
}
