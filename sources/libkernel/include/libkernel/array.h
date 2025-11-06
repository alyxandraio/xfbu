#ifndef __LIBKERNEL_ARRAY_H
#define __LIBKERNEL_ARRAY_H 1

typedef (uint32_t*) u32list_t;

void append_u32l(u32list_t, uint32_t);
void remove_u32l(u32list_t, uint32_t, size_t);
void remove_at_u32l(u32list_t, size_t);
void insert_u32l(u32list_t, uint32_t, size_t);
void pop_u32l(u32list_t, size_t);
void set_u32l(u32list_t, uint32_t, size_t);
uint32_t get_u32l(u32list_t, size_t);

#endif
