#include <libkernel/serial.h>
#include <libkernel/util.h>

void serial_tx(uint8_t c) {
    if (serial_initialized == false) init_serial(BAUD_FALLBACK);
    const uint16_t COM1 = io_port_COM1();
    while ((inb(COM1 + 5) & 0x20) == 0);
    outb(COM1, c);
}
