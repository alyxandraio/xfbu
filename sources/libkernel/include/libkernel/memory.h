#ifndef __LIBKERNEL_MEMORY_H
#define __LIBKERNEL_MEMORY_H 1

#include <libkernel/libc/stddef.h>

size_t memory_total_bytes(void);
size_t memory_used_bytes(void);

#endif
