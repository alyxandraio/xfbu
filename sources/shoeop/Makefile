BUILD_DIR?=build

ASM?=nasm
ASMFLAGS=-f elf

LIBGCC_PATH?=/home/alyxandra/opt/cross/lib/gcc/i686-elf/15.2.0
CC=/home/alyxandra/opt/cross/bin/i686-elf-gcc
CFLAGS=-ffreestanding -nostdlib -std=c99 -g -I ../libkernel/include -I $(abspath $(LIBGCC_PATH))

HEADERS_C:=$(shell find . -type f -name '*.h' -print)
SOURCES_C:=$(shell find . -type f -name '*.c' -print)
SOURCES_ASM:=$(shell find . -type f -name '*.asm' -print)

OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/shoeop/c/%.o, $(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/shoeop/asm/%.o, $(SOURCES_ASM))
OBJECTS_LIBKERNEL:=$(shell find $(BUILD_DIR)/libkernel/. -type f -name '*.o' -print)

.PHONY: stage1 all

all: stage1

stage1: $(OBJECTS_ASM) $(OBJECTS_C)

$(BUILD_DIR)/shoeop/c/%.o: %.c $(HEADERS_C)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/shoeop/asm/%.o: %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) -o $@ $<
	objcopy --prefix-symbols=__ $@
