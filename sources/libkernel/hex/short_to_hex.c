#include <libkernel/hex.h>

void short_to_hex(uint16_t num, char* str) {
    uint8_t leading = (uint8_t) ((num >> 8) & 0xFF);
    uint8_t trailing = (uint8_t) (num & 0xFF);
    str[0] = leading_4bits_hex(leading);
    str[1] = trailing_4bits_hex(leading);
    str[2] = leading_4bits_hex(trailing);
    str[3] = trailing_4bits_hex(trailing);
    str[4] = '\0';
}
