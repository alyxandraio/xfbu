#!/bin/sh
set -e
. ./clean.sh
. ./build.sh

rm -rf iso_root

mkdir -p iso_root/boot/limine
mkdir -p iso_root/EFI/BOOT

cp -v sysroot/boot/xfbu.kernel iso_root/boot/
mv iso_root/boot/xfbu.kernel iso_root/boot/xfbu
cp -v limine.conf iso_root/boot/limine

cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine/
cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/
xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
  -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
  -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
  -efi-boot-part --efi-boot-image --protective-msdos-label \
  iso_root -o xfbu.iso
./limine/limine bios-install xfbu.iso
