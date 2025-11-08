#include <libkernel/array.h>

#include <xfbu/panic.h>

// INFO: caller MUST be certain that `u32` is a member of `list`
size_t unsafefind_u32l(u32list_t* list, uint32_t u32) {
    for (size_t i = 0; i < list->vector; i += 1)
        if (get_u32l(list, i) == u32)
            return i;
    panic("__unsafefind_u32l: `u32` not a member of list");
}
