[bits 32]

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
align 4096
global stack_bottom
global stack_top

stack_bottom:
resb 65536                      ; 64KiB stack; resb = skip bytes
stack_top:

section .text

global gdt_load
extern gdt_preprint
extern gdt_postprint
gdt_load:
    call gdt_preprint
    cli
    lgdt [gdt_desc]
    call gdt_postprint
    ret

gdt_start:
    dq 0                        ; entry 0: null descriptor

    ; entry 1: 32-bit protected mode 4GiB ring 0 code segment
    dw 0FFFFh                   ; trailing 16 bits on 20-bit limit
    dw 0                        ; first word in base
    db 0                        ; next byte in base
    db 10011010b                ; access byte; ring 0 code segment
    db 11001111b                ; 4-bit granularity and first 4 bits of limit
    db 0                        ; last byte in base

    ; entry 2: 32-bit protected mode 4GiB ring 0 data segment
    dw 0FFFFh                   ; trailing 16 bits on 20-bit limit
    dw 0                        ; first word in base
    db 0                        ; next byte in base
    db 10010010b                ; access byte; ring 0 data segment
    db 11001111b                ; 4-bit granularity and first 4 bits of limit
    db 0                        ; last byte in base
gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

global xfbu_entry
extern xfbu_header_tx
extern multiboot_check
extern multiboot_init
extern heap_init
extern kernel_main
xfbu_entry:
    mov esp, stack_top

    push eax
    mov eax, 3405691582
    mov dr0, eax
    mov eax, 3735928559
    mov dr1, eax

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    call xfbu_header_tx
    pop eax

    push eax
    call multiboot_check
    add esp, 4

    push ebx
    call multiboot_init
    add esp, 4

    call heap_init

    call gdt_load

    call kernel_main

    cli
.shoeop_halt:
    hlt
    jmp .shoeop_halt
