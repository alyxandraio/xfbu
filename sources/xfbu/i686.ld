OUTPUT_FORMAT("elf32-i386")
ENTRY(__xfbu_entry)
XFBU_VMA      = 0xC0000000;
XFBU_PHYSADDR = 0x00100000;
SECTIONS {
    . = 0x00100000;
    __xfbu_start = .;

    .text : AT(0x100000) {
        *(.multiboot)
        *(.text)
    }

    .rodata : ALIGN(4096) {
        *(.rodata)
    }

    .data : ALIGN(4096) {
        *(.data)
    }

    .bss (NOLOAD) : {
        *(COMMON)
        *(.bss)
    }

    __xfbu_end = .;
    PROVIDE(__xfbu_size = __xfbu_end - __xfbu_start);
}
