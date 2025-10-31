#include <libkernel/serial.h>
#include <libkernel/bda.h>
#include <libkernel/asm.h>

void serial_tx(uint8_t c) {
    if (serial_initialized == false) init_serial(BAUD_FALLBACK);
    const uint16_t COM1 = com1_io_port();
    while ((inb(COM1 + 5) & 0x20) == 0);
    outb(COM1, c);
}
