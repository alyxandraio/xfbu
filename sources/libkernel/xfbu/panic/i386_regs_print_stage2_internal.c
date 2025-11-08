#include <libkernel/xfbu/panic.h>

#include <libkernel/arch/i386/registers.h>
#include <libkernel/xfbu/info.h>
#include <libkernel/multiboot.h>
#include <libkernel/memory.h>
#include <libkernel/heap.h>
#include <libkernel/asm.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdio.h>

extern void i386_regs_print_stage2_internal_heap_invalid(const i386_registers_t);

// probably asking for trouble with this one
extern void stack_bottom(void);
extern void stack_top(void);

void i386_regs_print_stage2_internal(const i386_registers_t regs) {
    if (!heap_valid) {
        i386_regs_print_stage2_internal_heap_invalid(regs);
        return;
    }

    printf("cpu state:\n");
    printf("    eax: 0x%X    ebx: 0x%X    ecx: 0x%X    edx: 0x%X\n", regs.eax, regs.ebx, regs.ecx, regs.edx);
    printf("    esi: 0x%X    edi: 0x%X    ebp: 0x%X    eip: 0x%X\n", regs.esi, regs.edi, regs.ebp, regs.eip);
    printf("     cs: 0x....%W     ds: 0x....%W     es: 0x....%W     fs: 0x....%W\n", regs.cs, regs.ds, regs.es, regs.fs);
    printf("     gs: 0x....%W     ss: 0x....%W    cr0: 0x%X    cr2: 0x%X\n", regs.gs, regs.ss, regs.cr0, regs.cr2);
    printf("    cr3: 0x%X    cr4: 0x%X    dr0: 0x%X    dr1: 0x%X\n", regs.cr3, regs.cr4, regs.dr0, regs.dr1);
    printf("    dr2: 0x%X    dr3: 0x%X    dr6: 0x%X    dr7: 0x%X\n", regs.dr2, regs.dr3, regs.dr6, regs.dr7);

    printf("kernel stack:\n");

    const uint8_t* stack_start = (const uint8_t*) (uintptr_t) &stack_bottom;
    const uint8_t* stack_end = (const uint8_t*) (uintptr_t) &stack_top;

    size_t stack_size = ((size_t) stack_end) - ((size_t) stack_start);
    size_t stack_used = ((size_t) stack_end) - regs.esp;

    printf("    bottom        esp           top\n");
    printf("    0x%p    0x%X    0x%p\n", (void*) stack_start, regs.esp, (void*) stack_end);
    printf("    %u bytes used / %u bytes total\n", stack_used, stack_size);
    printf("    0x%x bytes used / 0x%x bytes total\n", stack_used, stack_size);

    printf("memory breakdown:\n");

    size_t memory_used = memory_used_bytes();
    size_t memory_total = memory_total_bytes();

    // bytes -> KiB
    memory_used /= 1024;
    // bytes -> MiB
    memory_total /= 1024 * 1024;
    // calculation is 1.125 MiB short of true physmem size
    memory_total += 1;

    // 640 KiB -> 1 MiB
    size_t hw_rsrvd = 0x00060000;
    // 0 bytes -> 4 KiB
    hw_rsrvd += 0x1000;
    // multiboot_info_t width
    hw_rsrvd += sizeof(multiboot_info_t);
    // bytes -> KiB
    hw_rsrvd /= 1024;

    // kernel executable size set by Make
    size_t krnl_exec = XFBU_BINARY_SIZE;
    // bytes -> KiB
    krnl_exec /= 1024;

    stack_used = (size_t) stack_end - reg_esp();

    size_t heap_used = 0;
    heap_used += alloc_pool->vector;
    heap_used += alloc_pool_lengths->vector;
    heap_used += alloc_vectors->vector;
    heap_used += free_vectors->vector;
    heap_used += heap_vector - internal_heap_vector;

    printf("    hardware reserved\n");
    printf("    %u KiB / %u MiB\n", hw_rsrvd, memory_total);
    printf("    kernel executable\n");
    printf("    %u KiB / %u MiB\n", krnl_exec, memory_total);
    printf("    stack memory\n");
    printf("    %u bytes / %u MiB\n", stack_used, memory_total);
    printf("    heap memory\n");
    printf("    %u bytes / %u MiB\n", heap_used, memory_total);
    printf("    composite\n");
    printf("    %u KiB / %u MiB\n", memory_used, memory_total);

    printf("kernel information:\n");
    printf("    XFBU kernel version %s\n", XFBU_VERSION);
    printf("    Compiled by %s on %s\n", XFBU_COMPILER, XFBU_COMPILATION_DATE);
}
