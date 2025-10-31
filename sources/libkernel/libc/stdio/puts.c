#include <stdio.h>

int puts(const char* s) {
    while (*s) {
        unsigned char c = *s++;
        putchar(c);
    }
    putchar('\r');
    return putchar('\n');
}
