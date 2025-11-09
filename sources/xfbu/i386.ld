ENTRY(__xfbu_entry)
SECTIONS {
    . = 1M;
    __xfbu_start = .;

    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }
    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }
    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }
    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }

    __xfbu_end = .;
    PROVIDE(__xfbu_size = __xfbu_end - __xfbu_start);
}
