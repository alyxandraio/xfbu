#include <libkernel/hex.h>

char trailing_4bits_hex(uint8_t hex) {
    return trailing_4bits_hex_rightshift(hex, 0);
}
