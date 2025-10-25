#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/vga.h>

static bool serial_initialized = false;

static inline uint16_t io_port_COM1(void) {
	volatile uint16_t* bda = (volatile uint16_t*) 0x0400;
	return *bda;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void io_wait(void) { outb(0x80, 0); } // wait 1 to 4 μs (jank and imprecise)

void disable_cursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

static void init_serial(uint32_t baud) {
	if (serial_initialized == true) return;

	const uint16_t COM1 = io_port_COM1();

	outb(COM1 + 3, 0x00);
	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x80);

	uint16_t divisor = (uint16_t) (115200 / baud);
	outb(COM1 + 0, divisor & 0xFF);
	outb(COM1 + 1, (divisor >> 8) & 0xFF);

	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x03);
	outb(COM1 + 2, 0xC7);
	outb(COM1 + 4, 0x0B);

	serial_initialized = true;
}

void serial_rx(char* c, bool* success) {
	if (success != 0) *success = true;
	if (serial_initialized == false) init_serial(115200);
	const uint16_t COM1 = io_port_COM1();
	if ((inb(COM1 + 5) & 0x01) == 0 && success != 0) *success = false;
	*c = (char) inb(COM1);
}

void serial_tx(uint8_t c) {
	if (serial_initialized == false) init_serial(115200);
	const uint16_t COM1 = io_port_COM1();
	while ((inb(COM1 + 5) & 0x20) == 0);
	outb(COM1, c);
}

void macaroni_prototype(void) {
	tputentryat(' ', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 0, 24);
	tputentryat('m', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 1, 24);
	tputentryat('a', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 2, 24);
	tputentryat('c', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 3, 24);
	tputentryat('a', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 4, 24);
	tputentryat('r', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 5, 24);
	tputentryat('o', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 6, 24);
	tputentryat('n', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 7, 24);
	tputentryat('i', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 8, 24);
	tputentryat(' ', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 9, 24);
	tputentryat('p', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 10, 24);
	tputentryat('r', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 11, 24);
	tputentryat('o', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 12, 24);
	tputentryat('t', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 13, 24);
	tputentryat('o', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 14, 24);
	tputentryat('t', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 15, 24);
	tputentryat('y', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 16, 24);
	tputentryat('p', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 17, 24);
	tputentryat('e', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 18, 24);
	tputentryat('!', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), 19, 24);
	for (int i = 20; i < 80; i++) {
		tputentryat(' ', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY), i, 24);
	}
}

void xfbu_prompt(int row) {
	tputentryat('x', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 0, row);
	tputentryat('f', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 1, row);
	tputentryat('b', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 2, row);
	tputentryat('u', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 3, row);
	tputentryat(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 4, row);
	tputentryat('%', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 5, row);
	tputentryat(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 6, row);
}

void fail_serial(int row) {
	tputentryat('C', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 1, row);
	tputentryat('O', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 2, row);
	tputentryat('M', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 3, row);
	tputentryat('1', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 4, row);
	tputentryat(' ', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 5, row);
	tputentryat('F', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 6, row);
	tputentryat('A', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 7, row);
	tputentryat('I', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 8, row);
	tputentryat('L', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 9, row);
	
}

char trailing_4bits_hex_rightshift(uint8_t hex, uint8_t shift) {
	uint8_t num = (hex >> shift) & 0x0F;
	
	switch (num) { // kill me
		case 0x0:
			return '0';
		case 0x1:
			return '1';
		case 0x2:
			return '2';
		case 0x3:
			return '3';
		case 0x4:
			return '4';
		case 0x5:
			return '5';
		case 0x6:
			return '6';
		case 0x7:
			return '7';
		case 0x8:
			return '8';
		case 0x9:
			return '9';
		case 0xa:
			return 'a';
		case 0xb:
			return 'b';
		case 0xc:
			return 'c';
		case 0xd:
			return 'd';
		case 0xe:
			return 'e';
		case 0xf:
			return 'f';
		default:
			// should be logically impossible
			// something is fucked if we get here
			return 'X';
	}
}

char trailing_4bits_hex(uint8_t hex) { return trailing_4bits_hex_rightshift(hex, 0); }

char leading_4bits_hex(uint8_t hex) { return trailing_4bits_hex_rightshift(hex, 4); }

void byte_to_hex(uint8_t num, char* result1, char* result2) {
	*result1 = leading_4bits_hex(num);
	*result2 = trailing_4bits_hex(num);
}

void short_to_hex(uint16_t num, char* result1, char* result2, char* result3, char* result4) {
	uint8_t leading = (uint8_t) ((num >> 8) & 0xFF);
	uint8_t trailing = (uint8_t) (num & 0xFF);
	byte_to_hex(leading, result1, result2);
	byte_to_hex(trailing, result3, result4);
}

void print_COM1_io_port(void) {
	char result1, result2, result3, result4;
	uint16_t com1_port = io_port_COM1();
	if (com1_port == 0x3f8) update_cursor(3, 3);
	short_to_hex(com1_port, &result1, &result2, &result3, &result4);

	tputentryat('C', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 59, 23);
	tputentryat('O', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 60, 23);
	tputentryat('M', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 61, 23);
	tputentryat('1', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 62, 23);
	tputentryat(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 63, 23);
	tputentryat('I', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 64, 23);
	tputentryat('/', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 65, 23);
	tputentryat('O', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 66, 23);
	tputentryat(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 67, 23);
	tputentryat('p', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 68, 23);
	tputentryat('o', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 69, 23);
	tputentryat('r', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 70, 23);
	tputentryat('t', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 71, 23);
	tputentryat(':', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 72, 23);
	tputentryat(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 73, 23);
	tputentryat('0', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 74, 23);
	tputentryat('x', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 75, 23);
	tputentryat(result1, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 76, 23);
	tputentryat(result2, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 77, 23);
	tputentryat(result3, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 78, 23);
	tputentryat(result4, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK), 79, 23);
}

void fuzz_COM1(void) {
	uint32_t i = 0;
	while (1) {
		char c = (char) (i % 256);
		serial_tx(c);
		i += 1;
		if (i > 1000000) i = 0;
	}
}

void kernel_main(void) {}
