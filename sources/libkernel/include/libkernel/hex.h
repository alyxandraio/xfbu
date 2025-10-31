#ifndef __LIBKERNEL_HEX_H
#define __LIBKERNEL_HEX_H

#include <stdint.h>

char trailing_4bits_hex_rightshift(uint8_t, uint8_t);
char trailing_4bits_hex(uint8_t);
char leading_4bits_hex(uint8_t);
void byte_to_hex(uint8_t, char*); // char* argument must be 3 bytes wide
void short_to_hex(uint16_t, char*); // char* argument must be 5 bytes wide
void int_to_hex(uint32_t, char*); // char* argument must be 9 bytes wide

#endif
