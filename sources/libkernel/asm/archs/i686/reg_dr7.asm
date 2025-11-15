[bits 32]

global reg_dr7
reg_dr7:
    mov eax, dr7
    ret
