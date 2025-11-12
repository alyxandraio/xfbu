BUILD_DIR?=build
LIB_DIR?=../libkernel/include

ASM=nasm
ASMFLAGS=-f elf

LIBGCC_PATH?=/home/alyxandra/opt/cross/lib/gcc/i686-elf/15.2.0
CC=clang
CFLAGS=-target i686-none-elf -ffreestanding -nostdlib -std=c99 -fno-omit-frame-pointer -g -I ../libkernel/include -I ./include

LD=ld.lld
LDFLAGS=-m elf_i386 -T i386.ld -nostdlib
# -L $(LIBGCC_PATH)

HEADERS_C:=$(shell find . -type f -name '*.h' -print)
SOURCES_C:=$(shell find . -type f -name '*.c' -print)
SOURCES_ASM:=$(shell find . -type f -name '*.asm' -print)

OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/xfbu/c/%.o, $(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/xfbu/asm/%.o, $(SOURCES_ASM))
OBJECTS_LIBKERNEL:=$(shell find $(BUILD_DIR)/libkernel/. -type f -name '*.o' -print)
OBJECTS_SHOEOP:=$(shell find $(BUILD_DIR)/shoeop/. -type f -name '*.o' -print)

.PHONY: kernel

kernel: $(BUILD_DIR)/xfbu.elf

$(BUILD_DIR)/xfbu/c/%.o: %.c $(HEADERS_C)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	llvm-objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/xfbu/asm/%.o: %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) -o $@ $<
	llvm-objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/xfbu.elf: $(OBJECTS_ASM) $(OBJECTS_C)
	$(LD) $(LDFLAGS) -o $@ $^ $(OBJECTS_LIBKERNEL) $(OBJECTS_SHOEOP) -Map $(BUILD_DIR)/xfbu.map
