#include <libkernel/array.h>

#include <xfbu/panic.h>

void pop_u32l(u32list_t* list) {
    if (list->vector == 0)
        panic("__pop_u32l: list empty");
    list->c_array[list->vector - 1] = 0;
    list->vector -= 1;
}
