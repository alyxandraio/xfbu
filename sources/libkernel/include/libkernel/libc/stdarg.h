#ifndef __LIBKERNEL_STDARG_H
#define __LIBKERNEL_STDARG_H

#include <libkernel/libc/yvals.h>

typedef char* va_list;

#define va_arg(ap, T) (*(T*)(((ap) += _Bnd(T, _AUPBND)) - _Bnd(T, _ADNBND)))
#define va_end(ap) (void)0
#define va_start(ap, A) (void)((ap) = (char*) &A + _Bnd(A, _AUPBND))
#define _Bnd(X, bnd) (sizeof(X) + bnd & ~(bnd))

#endif
