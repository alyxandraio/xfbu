#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

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
            }
            format += 2;
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
