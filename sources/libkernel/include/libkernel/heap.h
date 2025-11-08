#ifndef __LIBKERNEL_HEAP_H
#define __LIBKERNEL_HEAP_H

#include <libkernel/array.h>

#include <libkernel/libc/stdbool.h>
#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

void revalidate_indices_postinsertion(size_t);
void revalidate_indices_postremoval(size_t);

// TODO: semaphore lock or something like that to
// prevent threads from invalidating our state

extern const size_t heap_size;
extern void* heap_ptr;
extern size_t heap_vector;

extern size_t internal_heap_vector;

// list of pointers into currently
// allocated regions of heap memory
extern vplist_t* alloc_pool;
// stores many bytes are allocated at the
// same index into `alloc_pool`
extern sizelist_t* alloc_pool_lengths;
extern const size_t alloc_pool_size;

// indices into `alloc_pool` and
// `alloc_pool_lengths` for currently
// allocated regions of the heap
// TODO: rename to `alloc_indices` project-wide
extern sizelist_t* alloc_vectors;
// likewise, indices into `alloc_pool`
// and `alloc_pool_lengths` for freed
// regions of the heap
// TODO: rename to `free_indices` project-wide
extern sizelist_t* free_vectors;
extern const size_t alloc_vectors_size;
extern const size_t free_vectors_size;

extern size_t largest_free_region_index;
extern size_t largest_free_region_size;

extern bool heap_valid;

#endif
