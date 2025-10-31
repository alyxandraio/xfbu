#ifndef __XFBU_GDT_H
#define __XFBU_GDT_H

#include <stdint.h>

extern void gdtr_load(uint16_t, uint32_t);

#endif
