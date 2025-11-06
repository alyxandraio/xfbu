#ifndef __LIBKERNEL_HEAP_H
#define __LIBKERNEL_HEAP_H

#include <libkernel/libc/stdbool.h>
#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

// TODO: semaphore lock or something like that to
// prevent threads from invalidating our state

extern const size_t heap_size;
extern void* heap_ptr;
extern size_t heap_vector;

extern void** alloc_pool;
extern size_t* alloc_pool_lengths;
extern size_t alloc_pool_count;
extern const size_t alloc_pool_size;

extern size_t* alloc_vectors;
extern size_t* free_vectors;
extern size_t alloc_vectors_count;
extern size_t free_vectors_count;
extern const size_t alloc_vectors_size;
extern const size_t free_vectors_size;

extern size_t largest_free_region_index;
extern size_t largest_free_region_size;

extern bool heap_valid;

#endif
