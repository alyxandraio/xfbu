#ifndef __LIBKERNEL_STDLIB_H
#define __LIBKERNEL_STDLIB_H 1

#include <libkernel/libc/sys/cdefs.h>

#include <libkernel/libc/stddef.h>

__attribute__((__noreturn__)) void abort(void);
void* malloc(size_t);
void free(void*);

#endif
