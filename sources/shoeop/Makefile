BUILD_DIR?=build

ASM?=nasm
ASMFLAGS=-f elf

stage1: $(BUILD_DIR)/shoeop.o

$(BUILD_DIR)/shoeop.o: boot.asm
	$(ASM) boot.asm $(ASMFLAGS) -o $(BUILD_DIR)/shoeop.o
