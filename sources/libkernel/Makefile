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

NOW:=$(shell date '+%Y-%m-%d %H:%M:%S')
CCVERSION:=$(shell $(CC) --version | head -n1)
XFBU_COMPILER:=$(shell find . -type f -name 'xfbu_compiler.c' -print)
XFBU_COMPILATION_DATE:=$(shell find . -type f -name 'xfbu_compilation_date.c' -print)
XFBU_BINARY_SIZE:=$(shell find . -type f -name 'xfbu_binary_size.c' -print)

.PHONY: libkernel compilerinforeplace

libkernel: $(OBJECTS_C) $(OBJECTS_ASM)

../xfbu/.xfbu_binary_size:
	echo '0' > $@

compilerinforeplace: ../xfbu/.xfbu_binary_size
	sed -i '4s/.*/const char* XFBU_COMPILER = "$(CCVERSION)";/' $(XFBU_COMPILER)
	sed -i '4s/.*/const char* XFBU_COMPILATION_DATE = "$(NOW)";/' $(XFBU_COMPILATION_DATE)
	sed -i '6s/.*/const size_t XFBU_BINARY_SIZE = $(shell cat ../xfbu/.xfbu_binary_size);/' $(XFBU_BINARY_SIZE)

$(BUILD_DIR)/libkernel/c/%.o: %.c compilerinforeplace
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/libkernel/asm/%.o: %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) -o $@ $<
	objcopy --prefix-symbols=__ $@
