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

extern gdt_preprint
extern gdt_postprint
gdt_load:
    call gdt_preprint
    cli
    lgdt [gdt_desc]
    call reload_segmentation_regs
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

    ; TODO: WILL NEED ADDITIONAL TWO ENTRIES
    ; WHEN USERLAND IS IMPLEMENTED!
gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

reload_segmentation_regs:
    ; bits 0 and 1 are the ring
    ; bit 2 is 0 for GDT, 1 for LDT
    ; segment index starts at bit 3
    ; sets CS for all code that follows
    jmp 0x08:.reload_seg
.reload_seg:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

extern idt_preprint
extern idt_postprint
idt_load:
    call idt_preprint
    cli
    lidt [idt_desc]
    call idt_postprint

idt_start:
    ; something
idt_end:

idt_desc:
    dw idt_end - idt_start - 1
    dd idt_start

extern populate_cr3
extern paging_preprint
extern paging_postprint
paging_enable:
    call paging_preprint
    call populate_cr3
    mov cr3, eax
    mov eax, cr4
    ; disable PAE and PSE;
    ; PSE enables 4 MiB pages
    and eax, 0xffffffcf
    mov cr4, eax
    mov eax, cr0
    ; enable paging
    or eax, 0x80000000
    ; disable supervisor write protect
    and eax, 0xfffeffff
    mov cr0, eax
    call paging_postprint

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
    ;call idt_load

    ;call paging_enable

    call kernel_main

    cli
.shoeop_halt:
    hlt
    jmp .shoeop_halt
