[bits 32]

global reg_eflags
reg_eflags:
    pushf
    pop eax
    ret
