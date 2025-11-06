#include <libkernel/array.h>

void append_u32l(u32list_t* list, uint32_t u32) {
    if (list->vector >= list->length)
        abort();
    list->c_array[list->vector++] = u32;
}
