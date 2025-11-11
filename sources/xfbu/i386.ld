OUTPUT_FORMAT("elf32-i386")
ENTRY(__xfbu_entry)
XFBU_VMA      = 0xC0000000;
XFBU_PHYSADDR = 0x00100000;
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
