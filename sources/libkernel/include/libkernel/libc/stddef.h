#ifndef __LIBKERNEL_STDDEF_H
#define __LIBKERNEL_STDDEF_H 1

#include <libkernel/libc/yvals.h>

#define NULL _NULL
#define offsetof(T, member) ((_Sizet)&((T*)0)->member)

#ifndef _SIZET
#define _SIZET 1
typedef _Sizet size_t;
#endif

#ifndef _WCHART
#define _WCHART 1
typedef _Wchart wchar_t;
#endif

typedef _Ptrdifft ptrdiff_t;

#endif
