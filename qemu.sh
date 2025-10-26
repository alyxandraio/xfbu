#!/bin/sh
set -e
. ./iso.sh

mv xfbu.iso xfbu-temp.iso
./clean.sh
mv xfbu-temp.iso xfbu.iso

qemu-system-$(./target-triplet-to-arch.sh $HOST) \
	-cdrom xfbu.iso \
	-serial stdio \
	-s
