#include <libkernel/libc/string.h>

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

int strncmp(const char* s1, const char* s2, size_t n) {
    for (; 0 < n; ++s1, ++s2, --n)
        if (*s1 != *s2)
            return ((*(uint8_t*)s1 < *(uint8_t*)s2) ? -1 : +1);
        else if (*s1 == '\0')
            return 0;
    return 0;
}
