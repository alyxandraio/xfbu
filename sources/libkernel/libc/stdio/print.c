#include <libkernel/libc/stdio.h>

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdbool.h>
#include <libkernel/libc/string.h>

bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < length; i++)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}
