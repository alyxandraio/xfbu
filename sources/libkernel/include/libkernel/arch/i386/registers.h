#ifndef __LIBKERNEL_ARCH_I386_REGISTERS_H
#define __LIBKERNEL_ARCH_I386_REGISTERS_H 1

#include <libkernel/libc/stdint.h>

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

#endif
