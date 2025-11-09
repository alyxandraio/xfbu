#include <libkernel/array.h>

#include <libkernel/heap.h>

#include <xfbu/panic.h>

uint32_t get_u32l(u32list_t* list, size_t index) {
    if (index >= list->vector) {
        panic("__get_u32l: out of bounds");
    }
    return list->c_array[index];
}
