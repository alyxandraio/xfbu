#include <libkernel/array.h>

void remove_at_u32l(u32list_t* list, size_t index) {
    if (index >= list->vector)
        abort();
    for (int i = index; index < list->vector - 1; i += 1)
        list->c_array[i] = list->c_array[i + 1];
    list->vector -= 1;
}
