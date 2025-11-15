#ifndef __LIBKERNEL_STDLIB_H
#define __LIBKERNEL_STDLIB_H 1

#ifdef __XFBU_ARCH_I686

#include <libkernel/libc/sys/cdefs.h>

#include <libkernel/libc/stddef.h>

__attribute__((__noreturn__)) void abort(void);
void* malloc(size_t);
void free(void*);

#elifdef __XFBU_ARCH_ARM64_IPHONEOS
#include <stdlib.h>
#else
#error
#endif

#endif
