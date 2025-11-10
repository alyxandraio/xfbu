#include <libkernel/array.h>

#include <xfbu/panic.h>

void insert_u32l(u32list_t* list, uint32_t u32, size_t index) {
    if (index > list->vector)
        panic_noheap("__insert_u32l: out of bounds");
    if (list->vector == list->length)
        panic_noheap("__insert_u32l: list overflow");
    if (index == list->vector) {
        append_u32l(list, u32);
        return;
    }
    for (int i = list->vector; i > index; i -= 1)
        list->c_array[i] = list->c_array[i - 1];
    list->c_array[index] = u32;
    list->vector += 1;
}
