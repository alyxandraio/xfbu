BUILD_DIR=build
ASM=nasm
CC=clang
LD=ld.lld
LIBGCC_PATH=/home/alyxandra/opt/cross/lib/gcc/i686-elf/15.2.0

export FAT
export ASM
export CC
export LD
export LIBGCC_PATH

# floppy: xfbu_1440kb.img

.PHONY: all iso clean libkernel bootloader shoeop xfbu build

all: iso

iso: xfbu.iso

build: clean $(BUILD_DIR)/limine libkernel bootloader xfbu

clean:
	rm -f limine/limine
	rm -f xfbu.iso
	rm -rf build/
	rm -rf iso_root/
	rm -rf sources/shoeop/build/
	rm -rf sources/libkernel/build/
	rm -rf sources/xfbu/build/

$(BUILD_DIR)/limine: xfbu
	$(MAKE) -C limine/
	mv limine/limine $(BUILD_DIR)/limine

xfbu.iso: clean $(BUILD_DIR)/limine libkernel bootloader xfbu
	rm -rf iso_root
	mkdir -p iso_root/boot/limine
	mkdir -p iso_root/EFI/BOOT
	cp -v build/xfbu.elf iso_root/boot/
	mv iso_root/boot/xfbu.elf iso_root/boot/xfbu
	cp -v limine.conf iso_root/boot/limine
	cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine/
	cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT
	xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o xfbu.iso
	$(BUILD_DIR)/limine bios-install xfbu.iso

bootloader: shoeop

libkernel: clean
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/libkernel/ BUILD_DIR=$(abspath $(BUILD_DIR))

shoeop: clean
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/shoeop/ BUILD_DIR=$(abspath $(BUILD_DIR))

xfbu: libkernel shoeop
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/xfbu/ BUILD_DIR=$(abspath $(BUILD_DIR))
