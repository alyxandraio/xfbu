BUILD_DIR?=build

LIBGCC_PATH=/home/alyxandra/opt/cross/lib/gcc/i686-elf/15.2.0
CC=/home/alyxandra/opt/cross/bin/i686-elf-gcc
CFLAGS=-ffreestanding -nostdlib -std=c99 -g -I ./include -I $(abspath $(LIBGCC_PATH))

ASM?=nasm
ASMFLAGS=-f elf

SOURCES_C:=$(shell find . -type f -name '*.c' -print)
OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/libkernel/c/%.o, $(SOURCES_C))

SOURCES_ASM:=$(shell find . -type f -name '*.asm' -print)
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/libkernel/asm/%.o, $(SOURCES_ASM))

libkernel: $(OBJECTS_C) $(OBJECTS_ASM)

$(BUILD_DIR)/libkernel/c/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/libkernel/asm/%.o: %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) -o $@ $<
	objcopy --prefix-symbols=__ $@
