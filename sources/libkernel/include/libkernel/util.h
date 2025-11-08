#ifndef __LIBKERNEL_UTIL_H
#define __LIBKERNEL_UTIL_H 1

#include <libkernel/libc/stdint.h>

void io_wait(void);
void str_trim_leading_zeroes(char*);
void convert_u32_str_noheap(char**, uint32_t, uint32_t);

#endif
