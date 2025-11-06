#ifndef __LIBKERNEL_U32LIST_H
#define __LIBKERNEL_U32LIST_H 1

struct u32list {
    uint32_t* c_array;
    size_t length;
    size_t vector;
};

typedef struct u32list u32list_t;

// INFO: CALLER's responsibility to `free_u32l`
u32list_t* new_u32l(size_t);
void append_u32l(u32list_t*, uint32_t);
void remove_u32l(u32list_t*, uint32_t, int);
void remove_at_u32l(u32list_t*, size_t);
void insert_u32l(u32list_t*, uint32_t, size_t);
void pop_u32l(u32list_t*);
void set_u32l(u32list_t*, uint32_t, size_t);
uint32_t get_u32l(u32list_t*, size_t);
size_t count_u32l(u32list_t*);
size_t allocd_u32l(u32list_t*);
void free_u32l(u32list_t*);
size_t unsafefind_u32l(u32list_t*, uint32_t);
void push_u32l(u32list_t*, uint32_t);

#endif
