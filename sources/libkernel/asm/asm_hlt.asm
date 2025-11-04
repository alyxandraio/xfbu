[bits 32]

global asm_hlt
asm_hlt:
    cli
.asm_hlt_internal:
    hlt
    jmp .asm_hlt_internal
    ret
