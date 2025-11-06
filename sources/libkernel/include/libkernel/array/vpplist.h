#ifndef __LIBKERNEL_VPPLIST_H
#define __LIBKERNEL_VPPLIST_H 1

struct vpplist {
    void*** c_array;
    size_t length;
    size_t vector;
};

typedef struct vpplist vpplist_t;

#endif
