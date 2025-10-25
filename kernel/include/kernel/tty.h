#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

void tinit(void);
void tputchar(char c);
void twrite(const char* data, size_t size);
void twrites(const char* data);

void tsetcolor(uint8_t color);
void tputentryat(unsigned char c, uint8_t color, size_t x, size_t y);

#endif
