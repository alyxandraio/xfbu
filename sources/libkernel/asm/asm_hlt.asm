[bits 32]

global asm_hlt
asm_hlt:
    hlt
    jmp asm_hlt
    ret
