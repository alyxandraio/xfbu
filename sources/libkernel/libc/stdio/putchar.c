#include <libkernel/libc/stdio.h>

#include <libkernel/serial.h>

int putchar(int ci) {
    uint8_t c = ci;
    serial_tx(c);
}
