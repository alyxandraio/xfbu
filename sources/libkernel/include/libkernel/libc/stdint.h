#ifndef __LIBKERNEL_STDINT_H
#define __LIBKERNEL_STDINT_H 1

#if defined(__XFBU_ARCH_I686)

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed int intptr_t;
typedef unsigned int uintptr_t;

#elif defined(__XFBU_ARCH_ARM64_IPHONEOS)
#include <stdint.h>
#else
#error
#endif

#endif
