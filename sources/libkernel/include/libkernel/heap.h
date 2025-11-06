#ifndef __LIBKERNEL_HEAP_H
#define __LIBKERNEL_HEAP_H

#include <libkernel/array.h>

#include <libkernel/libc/stdbool.h>
#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

// TODO: semaphore lock or something like that to
// prevent threads from invalidating our state

extern const size_t heap_size;
extern void* heap_ptr;
extern size_t heap_vector;

extern size_t internal_heap_vector;

extern vplist_t* alloc_pool;
extern sizelist_t* alloc_pool_lengths;
extern const size_t alloc_pool_size;

extern sizelist_t* alloc_vectors;
extern sizelist_t* free_vectors;
extern const size_t alloc_vectors_size;
extern const size_t free_vectors_size;

extern size_t largest_free_region_index;
extern size_t largest_free_region_size;

extern bool heap_valid;

#endif
