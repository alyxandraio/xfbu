#include <libkernel/array.h>

#include <xfbu/panic.h>

void append_u32l(u32list_t* list, uint32_t u32) {
    if (list->vector >= list->length)
        panic("__append_u32l: list overflow");
    list->c_array[list->vector] = u32;
    list->vector += 1;
}
