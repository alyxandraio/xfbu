#ifndef __LIBKERNEL_STDDEF_H
#define __LIBKERNEL_STDDEF_H 1

#define _NULL (void*)0
#define NULL _NULL
#define offsetof(T, member) ((_Sizet)&((T*)0)->member)

#ifndef _SIZET
#define _SIZET 1
typedef unsigned int size_t;
#endif

#ifndef _WCHART
#define _WCHART 1
typedef unsigned short wchar_t;
#endif

typedef int ptrdiff_t;

#endif
