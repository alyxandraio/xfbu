#include <libkernel/array.h>

#include <xfbu/panic.h>

void set_u32l(u32list_t* list, uint32_t u32, size_t index) {
    // normally would be '>=', however,
    // an index that's out of bounds by +1
    // is valid due to its equivalency to
    // an `append_u32l` operation
    if (index > list->vector)
        panic("__set_u32l: out of bounds");
    list->c_array[index] = u32;
    if (index == list->vector) {
        if (list->vector == list->length)
            panic("__set_u32l: out of bounds access");
        list->vector += 1;
    }
}
