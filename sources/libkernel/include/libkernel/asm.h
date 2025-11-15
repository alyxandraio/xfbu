#ifndef __LIBKERNEL_ASM_H
#define __LIBKERNEL_ASM_H

#if defined(__XFBU_ARCH_I686)

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

uint8_t inb(uint16_t);
void outb(uint16_t, uint8_t);

void asm_cli(void);
void asm_hlt(void);

size_t reg_eax(void);
size_t reg_ebx(void);
size_t reg_ecx(void);
size_t reg_edx(void);
size_t reg_esi(void);
size_t reg_edi(void);
size_t reg_esp(void);
size_t reg_ebp(void);
size_t reg_eip(void);
size_t reg_eflags(void);
uint16_t reg_cs(void);
uint16_t reg_ds(void);
uint16_t reg_es(void);
uint16_t reg_fs(void);
uint16_t reg_gs(void);
uint16_t reg_ss(void);
size_t reg_cr0(void);
size_t reg_cr2(void);
size_t reg_cr3(void);
size_t reg_cr4(void);
size_t reg_dr0(void);
size_t reg_dr1(void);
size_t reg_dr2(void);
size_t reg_dr3(void);
size_t reg_dr6(void);
size_t reg_dr7(void);

#elif defined(__XFBU_ARCH_ARM64_IPHONEOS)
// nothing for now ...
#else
#error
#endif

#endif
