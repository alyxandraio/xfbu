#include <libkernel/util.h>

#include <libkernel/libc/string.h>

extern void printf_ubasehelper(uint32_t, char*, uint32_t, int);

// INFO: assumes at least 11 bytes are allocated at `s`
void convert_u32_str_noheap(char** s, uint32_t u32, uint32_t base) {
    for (int i = 0; i < 11; i += 1)
        *s[i] = '\0';
    printf_ubasehelper(u32, *s, base, 0);
    int nullb = strlen(*s);
    char s_reversed[11];
    for (int i = 1; i <= nullb; i += 1)
        s_reversed[nullb-i] = *s[i-1];
    s_reversed[nullb] = '\0';
    *s = &s_reversed[0];
}
