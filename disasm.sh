#!/bin/sh
set -e
. ./build.sh

objdump -d sysroot/boot/xfbu.kernel | less

./clean.sh
