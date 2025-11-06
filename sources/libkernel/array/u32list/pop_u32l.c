#include <libkernel/array.h>

void pop_u32l(u32list_t* list) {
    if (list->vector == 0)
        abort();
    list->c_array[list->vector - 1] = 0;
    list->vector -= 1;
}
