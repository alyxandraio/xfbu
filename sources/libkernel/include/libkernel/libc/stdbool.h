#ifndef __LIBKERNEL_STDBOOL_H
#define __LIBKERNEL_STDBOOL_H 1

#ifdef __XFBU_ARCH_I686

#define __bool_true_false_are_defined 1

#define bool _Bool
#define true 1
#define false 0

#elifdef __XFBU_ARCH_ARM64_IPHONEOS
#include <stdbool.h>
#else
#error
#endif

#endif
