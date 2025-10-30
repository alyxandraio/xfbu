#include <libkernel/serial.h>
#include <libkernel/util.h>

void serial_rx(char* c, bool* success) {
    if (success != 0) *success = true;
    if (serial_initialized == false) init_serial(BAUD_FALLBACK);
    const uint16_t COM1 = io_port_COM1();
    if ((inb(COM1 + 5) & 0x01) == 0 && success != 0) *success = false;
    *c = (char) inb(COM1);
}
