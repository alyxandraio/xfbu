BUILD_DIR?=build

LIBGCC_PATH=/home/alyxandra/opt/cross/lib/gcc/i686-elf/15.2.0
CC=clang
CFLAGS=-target i686-none-elf -ffreestanding -nostdlib -std=c99 -fno-omit-frame-pointer -g -I ./include -I ../xfbu/include

ASM?=nasm
ASMFLAGS=-f elf

SOURCES_C:=$(shell find . -type f -name '*.c' -print)
OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/libkernel/c/%.o, $(SOURCES_C))

SOURCES_ASM:=$(shell find . -type f -name '*.asm' -print)
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/libkernel/asm/%.o, $(SOURCES_ASM))

NOW:=$(shell date '+%Y-%m-%d %H:%M:%S')
CCVERSION:=$(shell $(CC) --version | head -n1| cut -d' ' -f1-3)
XFBU_COMPILER:=$(shell find . -type f -name 'xfbu_compiler.c' -print)
XFBU_COMPILATION_DATE:=$(shell find . -type f -name 'xfbu_compilation_date.c' -print)
XFBU_BINARY_SIZE:=$(shell find . -type f -name 'xfbu_binary_size.c' -print)

.PHONY: libkernel compilerinforeplace

libkernel: $(OBJECTS_C) $(OBJECTS_ASM)

compilerinforeplace:
	sed -i '4s/.*/const char* XFBU_COMPILER = "$(CCVERSION)";/' $(XFBU_COMPILER)
	sed -i '4s/.*/const char* XFBU_COMPILATION_DATE = "$(NOW)";/' $(XFBU_COMPILATION_DATE)

$(BUILD_DIR)/libkernel/c/%.o: %.c compilerinforeplace
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	llvm-objcopy --prefix-symbols=__ $@

$(BUILD_DIR)/libkernel/asm/%.o: %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) -o $@ $<
	llvm-objcopy --prefix-symbols=__ $@
