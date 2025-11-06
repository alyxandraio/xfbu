#ifndef __LIBKERNEL_VPLIST_H
#define __LIBKERNEL_VPLIST_H 1

struct vplist {
    void** c_array;
    size_t length;
    size_t vector;
};

typedef struct vplist vplist_t;

#endif
