[bits 32]

gdtr dw 0
     dd 0

global gdtr_load
gdtr_load:
    mov ax, [esp + 4]
    mov [gdtr], ax
    mov eax, [esp + 8]
    mov [gdtr + 2], eax
    lgdt [gdtr]
    ret
