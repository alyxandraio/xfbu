#include <libkernel/array.h>

void set_u32l(u32list_t* list, uint32_t u32, size_t index) {
    // normally would be '>=', however,
    // an index that's out of bounds by +1
    // is valid due to its equivalency to
    // an `append_u32l` operation
    if (index > list->vector)
        abort();
    list->c_array[index] = u32;
    if (index == list->vector) {
        if (list->vector == list->length)
            abort();
        list->vector += 1;
    }
}
