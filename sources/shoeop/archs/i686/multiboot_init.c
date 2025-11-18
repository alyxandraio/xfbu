#include <libkernel/archs/i686/multiboot.h>

#include <shoeop/shoeop.h>

#include <libkernel/libc/stdint.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/string.h>
#include <libkernel/libc/stdio.h>

void multiboot_init(uint32_t mbaddr) {
    within_shoeop_process = true;
    if (!multiboot_valid)
        abort();
    const char* s1 = ":: multiboot initialisation...";
    const char* s2 = " OK\r\n";
    print(s1, strlen(s1));
    mbi = (multiboot_info_t*) (uintptr_t) mbaddr;
    // TODO: sanity bounds checking on mbaddr
    // to make sure its location checks out and
    // conforms to the GNU Multiboot specification
    if (mbi)
        print(s2, strlen(s2));
    else {
        multiboot_valid = false;
        abort();
    }
    within_shoeop_process = false;
}
