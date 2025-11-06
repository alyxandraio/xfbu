#include <libkernel/array.h>

// 'push' makes more sense as a verb
// to use in some circumstances
void push_u32l(u32list_t* list, uint32_t u32) {
    append_u32l(list, u32);
}
