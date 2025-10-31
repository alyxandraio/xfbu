BUILD_DIR?=build
LIB_DIR?=../libkernel/include

ASM=nasm
ASMFLAGS=-f elf

LIBGCC_PATH?=/home/alyxandra/opt/cross/lib/gcc/i686-elf/15.2.0
CC=/home/alyxandra/opt/cross/bin/i686-elf-gcc
CFLAGS=-ffreestanding -nostdlib -std=c99 -g -I ../libkernel/include -I ./include -I $(abspath $(LIB_DIR))

LD=/home/alyxandra/opt/cross/bin/i686-elf-ld
LDFLAGS=-T linker-i386.ld -nostdlib -L $(LIBGCC_PATH)

HEADERS_C:=$(shell find . -type f -name '*.h' -print)
SOURCES_C:=$(shell find . -type f -name '*.c' -print)
SOURCES_ASM:=$(shell find . -type f -name '*.asm' -print)

OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/xfbu/c/%.o, $(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/xfbu/asm/%.o, $(SOURCES_ASM))
OBJECTS_LIBKERNEL:=$(shell find $(BUILD_DIR)/libkernel/. -type f -name '*.o' -print)
OBJECTS_SHOEOP=$(BUILD_DIR)/shoeop.o

.PHONY: kernel

kernel: $(BUILD_DIR)/xfbu.bin

$(BUILD_DIR)/xfbu/c/%.o: %.c $(HEADERS_C)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/xfbu/asm/%.o: %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) -o $@ $<
	objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/xfbu.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	$(LD) $(LDFLAGS) -o $@ $^ $(OBJECTS_LIBKERNEL) $(OBJECTS_SHOEOP) -lgcc -Map $(BUILD_DIR)/xfbu.map
