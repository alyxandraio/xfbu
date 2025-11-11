[bits 32]

global reg_dr6
reg_dr6:
    mov eax, dr6
    ret
