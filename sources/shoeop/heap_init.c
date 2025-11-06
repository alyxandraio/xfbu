#include <libkernel/multiboot.h>
#include <libkernel/heap.h>
#include <libkernel/asm.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

void heap_init(void) {
    if (!multiboot_valid)
        abort();
    const char* s1 = ":: heap initialisation...";
    const char* s2 = " FAIL\r\n";
    // OK string not needed; printf will work if init passes
    print(s1, strlen(s1));
    // 0x00100000 = 1M/1024K;
    // mem_upper is the amount of physical RAM
    // past 1M in kibibytes (kiB), hence the
    // multiplication by 0x0400;
    // the heap grows into higher memory,
    // so subtract its size
    heap_ptr = (void*) (0x00100000 + (mbi->mem_upper * 0x0400) - heap_size);
    // reverse original '>' comparator to '<=' to turn into a guard
    if (mbi->mem_upper * 0x0400 <= heap_size + 0x00400000) {
        print(s2, strlen(s2));
        abort();
    }

    // TODO: once interrupts are implemented,
    // turn interrupts back on at the end of the function
    asm_cli();
    heap_valid = true;
    alloc_pool = (vplist_t*) new_u32l(alloc_pool_size);
    alloc_pool_lengths = (sizelist_t*) new_u32l(alloc_pool_size);
    alloc_vectors = (sizelist_t*) new_u32l(alloc_vectors_size);
    free_vectors = (sizelist_t*) new_u32l(free_vectors_size);

    if (!alloc_pool || !alloc_pool_lengths
        ||!alloc_vectors || !free_vectors) {
        heap_valid = false;
        print(s2, strlen(s2));
        abort();
    }
    printf(" OK\n");
    internal_heap_vector = heap_vector;
}
