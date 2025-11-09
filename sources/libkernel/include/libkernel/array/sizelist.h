#ifndef __LIBKERNEL_SIZELIST_H
#define __LIBKERNEL_SIZELIST_H 1

struct sizelist {
    size_t* c_array;
    size_t length;
    size_t vector;
};

typedef struct sizelist sizelist_t;

#endif
