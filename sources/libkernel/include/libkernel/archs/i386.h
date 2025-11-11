#ifndef __LIBKERNEL_ARCHS_I386_H
#define __LIBKERNEL_ARCHS_I386_H 1

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
    uint16_t gs;
    uint16_t fs;
    uint16_t es;
    uint16_t ds;
    uint16_t cs;

    uint32_t eflags;

    uint32_t eip;

    uint32_t ebp;
    uint32_t edi;
    uint32_t esi;
    uint32_t edx;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t eax;
} __attribute__((packed));

struct i386_nlist {
    uint32_t strtable_offset;
    uint8_t type;
    uint8_t other;
    uint16_t desc;
    uint32_t value;
};

typedef struct i386_registers i386_registers_t;
typedef struct i386_nlist nlist32_t;

#endif
