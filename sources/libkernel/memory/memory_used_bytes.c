#include <libkernel/memory.h>

#include <libkernel/libc/stddef.h>

#include <libkernel/xfbu/info.h>
#include <libkernel/multiboot.h>
#include <libkernel/memory.h>
#include <libkernel/heap.h>
#include <libkernel/asm.h>

extern uint8_t stack_top[];

size_t memory_used_bytes(void) {
    size_t memory = 0;
    // 0 bytes -> 4 KiB
    // first page (page 0) reserved to ensure
    // null pointer dereferences either resolve
    // to null or trigger a page fault
    memory += 0x1000;
    // add width of `mbi` structure
    if (mbi >= 0x1000
        || mbi < 0x1000 - sizeof(multiboot_info_t)) {
        memory += sizeof(multiboot_info_t);
        goto no_overlap;
    }
    // if location 0x1000 is within `mbi`,
    // adjust the used memory counter accordingly
    memory += (size_t) (mbi + sizeof(multiboot_info_t) - 0x1000);
    no_overlap:
    // 640 KiB -> 1 MiB
    // hardware reserved
    memory += 0x00060000;
    // add kernel executable size
    // TODO: determine the kernel size
    // from the symbol table somehow
    memory += XFBU_BINARY_SIZE == 0 ? 1024 * 1024 : XFBU_BINARY_SIZE;
    // add heap size
    memory += alloc_pool->vector;
    memory += alloc_pool_lengths->vector;
    memory += alloc_vectors->vector;
    memory += free_vectors->vector;
    memory += heap_vector - internal_heap_vector;
    // add used stack memory
    const uint8_t* stack_end = (const uint8_t*) (uintptr_t) &stack_top[0];
    memory += (size_t) stack_end - reg_esp();
    return memory;
}
