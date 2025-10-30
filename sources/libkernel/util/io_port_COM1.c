#include <libkernel/util.h>

uint16_t io_port_COM1(void) {
    volatile uint16_t* bda = (volatile uint16_t*) 0x0400;
    return *bda;
}
