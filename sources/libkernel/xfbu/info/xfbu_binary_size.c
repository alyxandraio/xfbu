#include <libkernel/xfbu/info.h>

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

extern uint8_t xfbu_size[];

const size_t XFBU_BINARY_SIZE = (size_t) &xfbu_size;
