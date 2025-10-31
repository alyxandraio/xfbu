#include <libkernel/util.h>
#include <libkernel/asm.h>

void io_wait(void) {
    outb(0x80, 0);
}
