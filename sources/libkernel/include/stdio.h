#ifndef __LIBKERNEL_STDIO_H
#define __LIBKERNEL_STDIO_H 1

#include <sys/cdefs.h>
#include <stddef.h>
#include <stdbool.h>
#include <yvals.h>

#define NULL _NULL
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2
#define BUFSIZ 512
#define EOF -1
// #define FILENAME_MAX _FNAMAX
// #define FOPEN_MAX _FOPMAX
// #define L_tmpnam _TNAMAX
#define TMP_MAX 32
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
// #define stdin _Files[0]
// #define stdout _Files[1]
// #define stderr _Files[2]

int putchar(int);
int puts(const char*);

bool print(const char*, size_t);
int printf(const char* __restrict, ...);

#endif
