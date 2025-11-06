#ifndef __LIBKERNEL_ARRAY_H
#define __LIBKERNEL_ARRAY_H 1

#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdlib.h>
#include <libkernel/libc/stdint.h>

// *list_t types guarantee no gaps in the
// underlying structure residing in memory,
// loosely similar to __attribute__((packed))

#include <libkernel/array/u32list.h>
#include <libkernel/array/vplist.h>
#include <libkernel/array/vpplist.h>
#include <libkernel/array/sizelist.h>

#endif
