[bits 32]

global reg_cr3
reg_cr3:
    mov eax, cr3
    ret
