[bits 32]

global reg_eip
reg_eip:
    call $+5
    pop eax
    ret
