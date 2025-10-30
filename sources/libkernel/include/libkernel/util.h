#ifndef __LIBKERNEL_UTIL_H
#define __LIBKERNEL_UTIL_H 1

#include <stdint.h>

uint16_t io_port_COM1(void);
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);

// char trailing_4bits_hex_rightshift(uint8_t hex, uint8_t shift);
// char trailing_4bits_hex(uint8_t hex);
// char leading_4bits_hex(uint8_t hex);
// void byte_to_hex(uint8_t num, char* result1, char* result2);
// void short_to_hex(uint16_t num, char* result1, char* result2, char* result3, char* result4);

#endif
