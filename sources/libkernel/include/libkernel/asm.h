#ifndef __LIBKERNEL_ASM_H
#define __LIBKERNEL_ASM_H

#include <libkernel/libc/stdint.h>

uint8_t inb(uint16_t);
void outb(uint16_t, uint8_t);

void asm_cli(void);
void asm_hlt(void);

#endif
