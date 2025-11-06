#include <libkernel/array.h>

#include <libkernel/libc/stdlib.h>

void free_u32l(u32list_t* list) {
    free(list->c_array);
    free(list);
}

