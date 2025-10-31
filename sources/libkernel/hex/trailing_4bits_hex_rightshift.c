#include <libkernel/hex.h>

char trailing_4bits_hex_rightshift(uint8_t hex, uint8_t shift) {
    uint8_t num = (hex >> shift) & 0x0F;

    switch (num) {
        case 0x0:
            return '0';
        case 0x1:
            return '1';
        case 0x2:
            return '2';
        case 0x3:
            return '3';
        case 0x4:
            return '4';
        case 0x5:
            return '5';
        case 0x6:
            return '6';
        case 0x7:
            return '7';
        case 0x8:
            return '8';
        case 0x9:
            return '9';
        case 0xa:
            return 'a';
        case 0xb:
            return 'b';
        case 0xc:
            return 'c';
        case 0xd:
            return 'd';
        case 0xe:
            return 'e';
        case 0xf:
            return 'f';
        default:
            // something is fucked if we get here
            return 'X';
    }
}
