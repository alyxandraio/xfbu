[bits 32]

%macro PUSH_REGS 0

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ebp

    call $+5
    pop eax
    push eax

    pushfd

    push cs
    push ds
    push es
    push fs
    push gs
    push ss

    mov eax, cr0
    push eax
    mov eax, cr2
    push eax
    mov eax, cr3
    push eax
    mov eax, cr4
    push eax

    mov eax, dr0
    push eax
    mov eax, dr1
    push eax
    mov eax, dr2
    push eax
    mov eax, dr3
    push eax
    mov eax, dr6
    push eax
    mov eax, dr7
    push eax

    lea eax, [esp]
    push eax

%endmacro

global asm_i386_regs_print_helper
extern i386_regs_print_stage2_internal
asm_i386_regs_print_helper:
    cli

    PUSH_REGS
    call i386_regs_print_stage2_internal
    add esp, 104

    ret
