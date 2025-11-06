#include <libkernel/array.h>

void remove_u32l(u32list_t* list, uint32_t u32, int limit) {
    size_t found = 0;
    for (int index = 0; index < list->vector && found < limit; index += 1) {
        if (list->c_array[index] == u32) {
            remove_at_u32l(list, index);
            found += 1;
        }
    }
}
