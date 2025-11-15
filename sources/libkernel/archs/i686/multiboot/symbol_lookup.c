#include <libkernel/archs/i686/multiboot.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdio.h>


#include <libkernel/archs/i686/i686.h>

#include <xfbu/panic.h>

// TODO: figure out why this never returns a valid symbol string
const char* symbol_lookup(size_t* physaddr, size_t* offset) {
    if (!(mbi->flags & 1 << 5))
        return (const char*) 0;
    multiboot_aout_symbol_table_t aout = mbi->u.aout_sym;
    nlist32_t* symtable = (nlist32_t*) (uintptr_t) aout.addr;
    char* strtable = (char*) (uintptr_t) (aout.addr + aout.tabsize);
    uint32_t num_symbols = aout.tabsize / sizeof(nlist32_t);

    nlist32_t* best = (nlist32_t*) 0;
    for (size_t i = 0; i < num_symbols; i += 1) {
        nlist32_t* list = &symtable[i];
        if ((list->value > (size_t) physaddr))
            continue;
        if (!best || list->value > best->value)
            best = list;
    }

    if (!best)
        panic("__symbol_lookup: could not find symbol");
    if (offset)
       *offset = (size_t) (physaddr - best->value);
    return (const char*) (strtable + best->strtable_offset);
}
