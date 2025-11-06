#include <libkernel/array.h>

uint32_t get_u32l(u32list_t* list, size_t index) {
    if (index >= list->vector)
        abort();
    return list->c_array[index];
}
