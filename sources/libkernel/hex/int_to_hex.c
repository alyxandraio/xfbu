#include <libkernel/hex.h>

void int_to_hex(uint32_t num, char* str) {
    uint8_t leading = (uint8_t) ((num >> 24) & 0xFF);
    uint8_t mleading = (uint8_t) ((num >> 16) & 0xFF);
    uint8_t mtrailing = (uint8_t) ((num >> 8) & 0xFF);
    uint8_t trailing = (uint8_t) (num & 0xFF);
    str[0] = leading_4bits_hex(leading);
    str[1] = trailing_4bits_hex(leading);
    str[2] = leading_4bits_hex(mleading);
    str[3] = trailing_4bits_hex(mleading);
    str[4] = leading_4bits_hex(mtrailing);
    str[5] = trailing_4bits_hex(mtrailing);
    str[6] = leading_4bits_hex(trailing);
    str[7] = trailing_4bits_hex(trailing);
    str[8] = '\0';
}
