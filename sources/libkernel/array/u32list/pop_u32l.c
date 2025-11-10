#include <libkernel/array.h>

#include <xfbu/panic.h>

void pop_u32l(u32list_t* list) {
    if (list->vector == 0)
        panic_noheap("__pop_u32l: list empty");
    list->vector -= 1;
    list->c_array[list->vector] = 0;
}
