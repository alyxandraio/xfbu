#include <libkernel/array.h>

#include <xfbu/panic.h>

void remove_at_u32l(u32list_t* list, size_t index) {
    if (index >= list->vector)
        panic_noheap("__remove_at_u32l: out of bounds");
    if (index == list->vector - 1) {
        pop_u32l(list);
        return;
    }
    list->c_array[index] = 0;
    if (list->vector == 1) {
        list->vector = 0;
        return;
    }
    if (list->vector == 2) {
        switch (index) {
            case 0:
                list->c_array[0] = list->c_array[1];
                list->c_array[1] = 0;
                list->vector = 1;
                break;
            case 1:
                list->c_array[1] = 0;
                list->vector = 1;
                break;
            default:
                panic_noheap("__remove_at_u32l: weird state");
        }
        return;
    }
    if (index == list->vector - 2) {
        list->c_array[index] = list->c_array[index + 1];
        pop_u32l(list);
        return;
    }
    for (int i = index; i < list->vector - 2; i += 1)
        list->c_array[i] = list->c_array[i + 1];
    list->vector -= 1;
}
