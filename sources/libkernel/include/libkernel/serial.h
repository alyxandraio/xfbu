#ifndef __LIBKERNEL_SERIAL_H
#define __LIBKERNEL_SERIAL_H 1

#include <stdint.h>
#include <stdbool.h>

extern bool serial_initialized;
extern const uint32_t BAUD_FALLBACK;

void init_serial(uint32_t baud);
void serial_rx(char* c, bool* success);
void serial_tx(uint8_t c);

void fuzz_serial(void); // non-returning

#endif
