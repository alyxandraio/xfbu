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

.PHONY: all iso i686 arm64-iphoneos clean libkernel_i686 bootloader_i686 shoeop_i686 xfbu_i686 libkernel_arm64-iphoneos bootloader_arm64-iphoneos shoeop_arm64-iphoneos xfbu_arm64-iphoneos

all:
	@echo "must specify target"

iso: xfbu.iso

i686: clean $(BUILD_DIR)/limine xfbu_i686

arm64-iphoneos: clean xfbu_arm64-iphoneos

clean:
	rm -f limine/limine
	rm -f xfbu.iso
	rm -rf build/
	rm -rf iso_root/
	rm -rf sources/shoeop/build/
	rm -rf sources/libkernel/build/
	rm -rf sources/xfbu/build/
	$(MAKE) -C pongoOS/newlib/ clean

$(BUILD_DIR)/limine:
	$(MAKE) -C limine/
	mkdir -p $(BUILD_DIR)
	mv limine/limine $(BUILD_DIR)/limine

xfbu.iso: clean $(BUILD_DIR)/limine libkernel_i686 bootloader_i686 xfbu_i686
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

bootloader_i686: shoeop_i686

libkernel_i686: clean
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/libkernel/ -f Makefile.i686 BUILD_DIR=$(abspath $(BUILD_DIR))

shoeop_i686: clean
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/shoeop/ -f Makefile.i686 BUILD_DIR=$(abspath $(BUILD_DIR))

xfbu_i686: libkernel_i686 bootloader_i686
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/xfbu/ -f Makefile.i686 BUILD_DIR=$(abspath $(BUILD_DIR))

bootloader_arm64-iphoneos: shoeop_arm64-iphoneos

libkernel_arm64-iphoneos: clean
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/libkernel/ -f Makefile.arm64-iphoneos BUILD_DIR=$(abspath $(BUILD_DIR))

shoeop_arm64-iphoneos: clean
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/shoeop/ -f Makefile.arm64-iphoneos BUILD_DIR=$(abspath $(BUILD_DIR))

xfbu_arm64-iphoneos: libkernel_arm64-iphoneos bootloader_arm64-iphoneos pongo_arm64-iphoneos
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C sources/xfbu/ -f Makefile.arm64-iphoneos BUILD_DIR=$(abspath $(BUILD_DIR))

pongo_arm64-iphoneos: clean libkernel_arm64-iphoneos shoeop_arm64-iphoneos
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C pongoOS/
