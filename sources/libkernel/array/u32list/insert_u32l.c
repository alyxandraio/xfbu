#include <libkernel/array.h>

void insert_u32l(u32list_t* list, uint32_t u32, size_t index) {
    if (index > list->vector)
        abort();
    if (list->vector == list->length)
        abort();
    if (index == list->vector) {
        append_u32l(list, u32);
        return;
    }
    list->vector += 1;
    for (int i = list->vector - 1; i > index; i -= 1)
        list->c_array[i] = list->c_array[i - 1];
    list->c_array[index] = u32;
}
