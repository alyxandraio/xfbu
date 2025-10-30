#include <libkernel/serial.h>

void fuzz_serial(void) {
    uint32_t i = 0;
    while (1) {
        char c = (char) (i % 256);
        serial_tx(c);
        i += 1;
        if (i > 1000000) i = 0;
    }
}
