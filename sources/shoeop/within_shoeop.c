#include <shoeop/shoeop.h>

bool within_shoeop_process = false;

void set_within_shoeop(void) { within_shoeop_process = true; }
void reset_within_shoeop(void) { within_shoeop_process = false; }
