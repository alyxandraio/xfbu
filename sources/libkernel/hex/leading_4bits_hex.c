#include <libkernel/hex.h>

char leading_4bits_hex(uint8_t hex) {
    return trailing_4bits_hex_rightshift(hex, 4);
}
