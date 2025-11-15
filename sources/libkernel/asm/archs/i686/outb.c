#include <libkernel/asm.h>

#include <libkernel/libc/stdint.h>

void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}
