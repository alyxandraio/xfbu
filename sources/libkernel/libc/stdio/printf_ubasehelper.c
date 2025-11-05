#include <stdio.h>

#include <stdint.h>

// pass zero to pass_zero (go figure)
void printf_ubasehelper(uint32_t u, char* s, uint32_t base, int pass_zero) {
    s[pass_zero] = '0' + (u % base);
    if (u >= base)
        printf_ubasehelper(u / 10, s, base, ++pass_zero);
}
