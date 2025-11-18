// #include <shoeop/entry.h>

#include <libkernel/libc/stdbool.h>
#include <libkernel/libc/stddef.h>
#include <libkernel/libc/stdint.h>

#include <pongo/pongo.h>

#include <fuse/fuse_private.h>
#include <dt/dt_private.h>
#include <framebuffer/fb.h>
#include <recfg/recfg_soc.h>

extern boot_args* gBootArgs;
extern uint64_t gPongoSlide;
extern uint64_t gTopOfKernelData;
extern void* gEntryPoint;
extern uint64_t gIOBase;
extern char* gDevType;
extern uint32_t socnum;
extern uint32_t* gFramebuffer;
extern uint32_t* gFramebufferCopy;
extern char soc_name[9];
extern void lowlevel_set_identity(void);
extern void set_exception_stack_core0(void);
extern void gpio_early_init(void);
extern void serial_pinmux_init(void);
extern void serial_early_init(void);
extern void pongo_reinstall_vbar(void);
extern void vm_init(void);
extern void screen_init(void);
//extern void screen_invert(void);
inline void xfbu_entry_arm64_iphoneos(uint64_t* kernel_args, void* entrypt) {
    screen_invert();
    while (1);
    //panic("abort()");
    gBootArgs = (boot_args*) kernel_args;
    gTopOfKernelData = gBootArgs->topOfKernelData;
    gEntryPoint = entrypt;
    lowlevel_setup(gBootArgs->physBase & 0x7ffffffff, gBootArgs->memSize);
    rebase_pc(gPongoSlide);
    set_exception_stack_core0();

    extern char preemption_over;
    preemption_over = 1;
    dt_init((void*) ((uint64_t)gBootArgs->deviceTreeP - gBootArgs->virtBase + gBootArgs->physBase - 0x800000000 + kCacheableView), gBootArgs->deviceTreeLength);
    gIOBase = dt_get_u64("/arm-io", "ranges", 1);
    map_full_ram(gBootArgs->physBase & 0x7ffffffff, gBootArgs->memSize);
    gDevType = dt_get_prop("/arm-io", "device_type", NULL);
    size_t len = strlen(gDevType) - 3;
    len = len < 8 ? len : 8;
    strncpy(soc_name, gDevType, len);
    // compare ...
    socnum = 0x8015;
    fuse_init();
    gpio_early_init();
    serial_pinmux_init();
    serial_early_init();
    set_vbar_el1((uint64_t) &exception_vector);
    vm_init();

    uint32_t row_pixels = gBootArgs->Video.v_rowBytes >> 2;
    uint16_t width = gBootArgs->Video.v_width;
    uint16_t height = gBootArgs->Video.v_height;
    uint64_t fbbase = gBootArgs->Video.v_baseAddr;
    uint64_t fbsize = height * row_pixels * 4;
    uint64_t fboff;
    if (is_16k()) {
        fboff = fbbase & 0x3fffULL;
        fbsize = (fbsize + fboff + 0x3fffULL) & ~0x3fffULL;
    } else {
        fboff = fbbase & 0xfffULL;
        fbsize = (fbsize + fboff + 0xfffULL) & ~0xfffULL;
    }
    map_range(0xfb0000000ULL, fbbase - fboff, fbsize, 3, 1, true);
    gFramebuffer = (uint32_t*) (0xfb0000000ULL + fboff);
    gFramebufferCopy = (uint32_t*) alloc_contig(fbsize);
    memcpy(gFramebufferCopy, gFramebuffer, fbsize);
    cache_clean(gFramebuffer, height * row_pixels * 4);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            gFramebuffer[x + y * row_pixels] ^= 0xffffffff;
            gFramebufferCopy[x + y * row_pixels] ^= 0xffffffff;
        }
    }
    cache_clean(gFramebuffer, height * row_pixels * 4);

    lowlevel_set_identity();
    rebase_pc(-gPongoSlide);
    set_exception_stack_core0();
    gFramebuffer = (uint32_t*) gBootArgs->Video.v_baseAddr;
    lowlevel_cleanup();
    gBootArgs->topOfKernelData = gTopOfKernelData;
    while (1);
}
