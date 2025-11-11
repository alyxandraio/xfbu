#include <libkernel/paging.h>

#include <libkernel/libc/stdint.h>

uint32_t** page_directory = (uint32_t**) 0;
