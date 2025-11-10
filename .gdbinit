set architecture i386
set osabi none
set disassembly-flavor intel
target remote :1234
set pagination off
display/i $pc
