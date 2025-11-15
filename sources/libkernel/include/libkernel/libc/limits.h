#ifndef __LIBKERNEL_LIMITS_H
#define __LIBKERNEL_LIMITS_H

#if defined(__XFBU_ARCH_I686)

#include <libkernel/libc/yvals.h>

#define CHAR_BIT 8
#define CHAR_MAX 127
#define CHAR_MIN -128
#define UCHAR_MAX 255

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define UINT_MAX 4294967295

// #define MB_LEN_MAX _MBMAX

#define SCHAR_MAX 127
#define SCHAR_MIN -128

#define SHRT_MAX 32767
#define SHRT_MIN -32768
#define USHRT_MAX 65535

#elif defined(__XFBU_ARCH_ARM64_IPHONEOS)
#include <limits.h>
#else
#error
#endif

#endif
