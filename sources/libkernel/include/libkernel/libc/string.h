#ifndef __LIBKERNEL_STRING_H
#define __LIBKERNEL_STRING_H 1

#ifdef __XFBU_ARCH_I686

#include <libkernel/libc/sys/cdefs.h>

#include <libkernel/libc/stddef.h>

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);
char* strcpy(char*, const char*);
char* strncpy(char*, const char*, size_t);
int strcmp(const char*, const char*);
int strncmp(const char*, const char*, size_t);

#elifdef __XFBU_ARCH_ARM64_IPHONEOS
#include <string.h>
#else
#error
#endif

#endif
