#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#include <libkernel/hex.h>
#include <libkernel/util.h>

extern void printf_ubasehelper(uint32_t, char*, uint32_t, int);

int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;
        if (format[0] == '%') {
            switch (format[1]) {
                case '%':
                    if (!print(format, 1))
                        return -1;
                    written += 1;
                    break;
                case 'c':
                    char c = (char) va_arg(parameters, int);
                    if (!maxrem)
                        return -1;
                    if (!print(&c, 1))
                        return -1;
                    written += 1;
                    break;
                case 's':
                    const char* str = va_arg(parameters, const char*);
                    size_t len = strlen(str);
                    if (maxrem < len)
                        return -1;
                    if (!print(str, len))
                        return -1;
                    written += len;
                    break;
                case 'x':
                    uint32_t num = va_arg(parameters, int);
                    char buf[9];
                    int_to_hex(num, buf);
                    str_trim_leading_zeroes(buf);
                    size_t buflen = strlen(buf);
                    if (maxrem < buflen)
                        return -1;
                    if (!print(buf, buflen))
                        return -1;
                    written += buflen;
                    break;
                case 'p':
                    uintptr_t ptr = (uintptr_t) va_arg(parameters, void*);
                    char p_buf[9];
                    int_to_hex((uint32_t) ptr, p_buf);
                    // str_trim_leading_zeroes(p_buf);
                    size_t p_buflen = strlen(p_buf);
                    if (maxrem < p_buflen)
                        return -1;
                    if (!print(p_buf, p_buflen))
                        return -1;
                    written += p_buflen;
                    break;
                case 'X':
                    uint32_t X_num = va_arg(parameters, int);
                    char X_buf[9];
                    int_to_hex(X_num, X_buf);
                    // str_trim_leading_zeroes(X_buf);
                    size_t X_buflen = strlen(X_buf);
                    if (maxrem < X_buflen)
                        return -1;
                    if (!print(X_buf, X_buflen))
                        return -1;
                    written += X_buflen;
                    break;
                case 'u':
                    uint32_t u_num = va_arg(parameters, int);
                    const uint8_t width = 11;
                    char u_buf[width];
                    for (int i = 0; i < width; i++)
                        u_buf[i] = '\0';
                    printf_ubasehelper(u_num, u_buf, 10, 0);
                    int nullb = strlen(u_buf);
                    char u_buf_reversed[width];
                    for (int i = 1; i <= nullb; i++)
                        u_buf_reversed[nullb-i] = u_buf[i-1];
                    u_buf_reversed[nullb] = '\0';
                    if (maxrem < nullb)
                        return -1;
                    if (!print(u_buf_reversed, nullb))
                        return -1;
                    written += nullb;
                    break;
            }
            format += 2;
            continue;
        }

        // guarantees no access to `format[-1]` unless the behavior is defined
        if (format[0] == '\n' && (written == 0 || format[-1] != '\r')) {
            const char* str = "\r\n";
            const size_t len = strlen(str);
            if (maxrem < len)
                return -1;
            if (!print(str, len))
                return -1;
            format += len / 2;
            written += len;
            continue;
        }


        size_t amount = 1;
        while (format[amount] && format[amount] != '%')
            amount++;
        if (maxrem < amount)
            return -1;
        if (!print(format, amount))
            return -1;
        format += amount;
        written += amount;
    }

    va_end(parameters);
    return written;
}
