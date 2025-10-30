BUILD_DIR?=build

LIBGCC_PATH=/home/alyxandra/opt/cross/lib/gcc/i686-elf/15.2.0
CC=/home/alyxandra/opt/cross/bin/i686-elf-gcc
CFLAGS=-ffreestanding -nostdlib -std=c99 -g -I ./include -I $(abspath $(LIBGCC_PATH))

SOURCES_C:=$(shell find . -type f -name '*.c' -print)
OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/libkernel/%.o, $(SOURCES_C))

libkernel: $(OBJECTS_C)

$(BUILD_DIR)/libkernel/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
