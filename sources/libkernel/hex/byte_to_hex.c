#include <libkernel/hex.h>

void byte_to_hex(uint8_t num, char* str) {
    str[0] = leading_4bits_hex(num);
    str[1] = trailing_4bits_hex(num);
    str[2] = '\0';
}
