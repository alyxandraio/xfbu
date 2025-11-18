#ifndef __SHOEOP_SHOEOP_H
#define __SHOEOP_SHOEOP_H 1

#include <libkernel/libc/stdbool.h>

extern bool within_shoeop_process;

void set_within_shoeop(void);
void reset_within_shoeop(void);

#endif
