#include <libkernel/xfbu/panic.h>

#include <libkernel/xfbu/info.h>
#include <libkernel/memory.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdio.h>

struct i386_registers {
    uint32_t esp;

    uint32_t dr7;
    uint32_t dr6;
    uint32_t dr3;
    uint32_t dr2;
    uint32_t dr1;
    uint32_t dr0;

    uint32_t cr4;
    uint32_t cr3;
    uint32_t cr2;
    uint32_t cr0;

    uint32_t ss;
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;
    uint32_t cs;

    uint32_t eflags;

    uint32_t eip;

    uint32_t ebp;
    uint32_t edi;
    uint32_t esi;
    uint32_t edx;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t eax;
};

typedef struct i386_registers i386_registers_t;

// probably asking for trouble with this one
extern void stack_bottom(void);
extern void stack_top(void);

void i386_regs_print_stage2_internal(const i386_registers_t regs) {
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

    uintptr_t stack_size = ((uintptr_t) stack_end) - ((uintptr_t) stack_start);
    uintptr_t stack_used = ((uintptr_t) stack_end) - ((uintptr_t) regs.esp);

    printf("    bottom        esp           top\n");
    printf("    0x%p    0x%X    0x%p\n", (void*) stack_start, regs.esp, (void*) stack_end);
    printf("    %u bytes used / %u bytes total\n", stack_used, stack_size);
    printf("    0x%x bytes used / 0x%x bytes total\n", stack_used, stack_size);

    printf("memory usage:\n");

    size_t memory_used = memory_used_bytes();
    size_t memory_total = memory_total_bytes();

    memory_used /= 1024;
    memory_total /= 1024 * 1024;

    printf("    %u KiB / %u MiB\n", memory_used, memory_total + 1);

    printf("kernel information:\n");
    printf("    XFBU kernel version %s\n", XFBU_VERSION);
    printf("    Compiled by %s on %s\n", XFBU_COMPILER, XFBU_COMPILATION_DATE);
}
