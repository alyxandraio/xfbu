#include <libkernel/array.h>

u32list_t* new_u32l(size_t length) {
    u32list_t* list = (u32list_t*) malloc(sizeof(u32list_t));
    list->c_array = (uint32_t*) malloc(length * sizeof(uint32_t));
    list->length = length;
    list->vector = 0;
    return list;
}
