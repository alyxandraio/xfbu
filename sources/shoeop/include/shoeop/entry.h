#ifndef __SHOEOP_ENTRY_H
#define __SHOEOP_ENTRY_H 1

#if defined(__XFBU_ARCH_I686)
#include <shoeop/archs/i686/entry.h>
#elif defined(__XFBU_ARCH_ARM64_IPHONEOS)
#include <shoeop/archs/arm64-iphoneos/entry.h>
#else
#error
#endif

#endif
