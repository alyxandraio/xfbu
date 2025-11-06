#include <libkernel/memory.h>

#include <libkernel/libc/stddef.h>

#include <libkernel/multiboot.h>
#include <libkernel/heap.h>

size_t memory_total_bytes(void) {
    if (!heap_valid || !multiboot_valid)
        abort();
    if (mbi->flags & 1 == 0)
        abort();
    size_t memory = 0;
    // 0 bytes -> 640 KiB
    memory += mbi->mem_lower * 0x0400;
    // 640 KiB -> 1 MiB
    memory += 0x00060000;
    // 1 MiB -> end of physical memory
    memory += mbi->mem_upper * 0x0400;
    return memory;
}
