#include <libkernel/serial.h>
#include <libkernel/util.h>

void init_serial(uint32_t baud) {
    if (serial_initialized == true) return;

    const uint16_t COM1 = io_port_COM1();

    outb(COM1 + 3, 0x00);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);

    uint16_t divisor = (uint16_t) (115200 / baud);
    outb(COM1 + 0, divisor & 0xFF);
    outb(COM1 + 1, (divisor >> 8) & 0xFF);

    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);

    serial_initialized = true;
}
