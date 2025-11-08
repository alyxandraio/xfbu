#include <libkernel/xfbu/panic.h>

#include <libkernel/arch/i386/registers.h>
#include <libkernel/xfbu/info.h>
#include <libkernel/memory.h>
#include <libkernel/heap.h>
#include <libkernel/asm.h>
#include <libkernel/hex.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

// do not do this i beg of you
extern void stack_bottom(void);
extern void stack_top(void);

void i386_regs_print_stage2_internal_heap_invalid(const i386_registers_t regs) {
    if (heap_valid)
        abort();

    const char* s1 = "cpu state:\r\n    eax: 0x";
    const char* s2 = "    ebx: 0x";
    const char* s3 = "    ecx: 0x";
    const char* s4 = "    edx: 0x";
    const char* s5 = "\r\n    esi: 0x";
    const char* s6 = "    edi: 0x";
    const char* s7 = "    ebp: 0x";
    const char* s8 = "    eip: 0x";
    const char* s9 = "\r\n    cs: 0x....";
    const char* s10 = "    ds: 0x....";
    const char* s11 = "    es: 0x....";
    const char* s12 = "    fs: 0x....";
    const char* s13 = "\r\n    gs: 0x....";
    const char* s14 = "    ss: 0x....";
    const char* s15 = "    cr0: 0x";
    const char* s16 = "    cr2: 0x";
    const char* s17 = "\r\n    cr3: 0x";
    const char* s18 = "    cr4: 0x";
    const char* s19 = "    dr0: 0x";
    const char* s20 = "    dr1: 0x";
    const char* s21 = "\r\n    dr2: 0x";
    const char* s22 = "    dr3: 0x";
    const char* s23 = "    dr6: 0x";
    const char* s24 = "    dr7: 0x";
    const char* s25 = "\r\nkernel stack:\r\n";
    const char* s26 = "    bottom        esp           top\r\n    0x";
    const char* s27 = "    0x";
    const char* s28 = "\r\n    ";
    const char* s29 = " bytes used / ";
    const char* s30 = " bytes total\r\n    0x";
    const char* s31 = " bytes used / 0x";
    const char* s32 = " bytes total\r\nmemory usage:\r\n    ";
    const char* s33 = " KiB / ";
    const char* s34 = " MiB\r\nkernel information:\r\n    XFBU kernel version ";
    const char* s35 = "\r\n    Compiled by ";
    const char* s36 = " on ";
    const char* s37 = "\r\n";

    const uint8_t* stack_start = (const uint8_t*) (uintptr_t) &stack_bottom;
    const uint8_t* stack_end = (const uint8_t*) (uintptr_t) &stack_top;

    char eaxh[9];
    char ebxh[9];
    char ecxh[9];
    char edxh[9];
    char esih[9];
    char edih[9];
    char ebph[9];
    char eiph[9];
    char eflagsh[9];
    char csh[5];
    char dsh[5];
    char esh[5];
    char fsh[5];
    char gsh[5];
    char ssh[5];
    char cr0h[9];
    char cr2h[9];
    char cr3h[9];
    char cr4h[9];
    char dr0h[9];
    char dr1h[9];
    char dr2h[9];
    char dr3h[9];
    char dr6h[9];
    char dr7h[9];
    char esph[9];
    char stack_bottomh[9];
    char stack_toph[9];
    char stack_bottom_bytes_base10[11];
    char stack_top_bytes_base10[11];
    char stack_bottom_bytesh[9];
    char stack_top_bytesh[9];
    char memory_used_kib_base10[11];
    char memory_total_mib_base10[11];

    size_t stack_size = ((size_t) stack_end) - ((size_t) stack_start);
    size_t stack_used = ((size_t) stack_end) - reg_esp();

    size_t memory_used = memory_used_bytes() / 1024;
    size_t memory_total = memory_total_bytes() / (1024 * 1024);

    int_to_hex(regs.eax, eaxh);
    int_to_hex(regs.ebx, ebxh);
    int_to_hex(regs.ecx, ecxh);
    int_to_hex(regs.edx, edxh);
    int_to_hex(regs.esi, esih);
    int_to_hex(regs.edi, edih);
    int_to_hex(regs.ebp, ebph);
    int_to_hex(regs.eip, eiph);
    int_to_hex(regs.eflags, eflagsh);
    short_to_hex(regs.cs, csh);
    short_to_hex(regs.ds, dsh);

    print(s1, strlen(s1));
}
