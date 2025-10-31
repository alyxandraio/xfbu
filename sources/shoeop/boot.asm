ALIGNMENT equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ ALIGNMENT | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384                      ; 16KiB stack; resb = skip bytes
stack_top:

section .text
global xfbu_start
extern kernel_main
xfbu_start:
    mov esp, stack_top
    push ebx
    push eax
    call kernel_main
    add esp, 8
    cli
halt:
    hlt
    jmp halt
