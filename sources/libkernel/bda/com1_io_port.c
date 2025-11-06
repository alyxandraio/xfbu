#include <libkernel/bda.h>

#include <libkernel/libc/stdint.h>

uint16_t com1_io_port(void) {
    volatile uint16_t* bda_com1 = (volatile uint16_t*) 0x0400;
    return *bda_com1;
}
