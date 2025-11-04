#include <libkernel/util.h>

#include <string.h>

void str_trim_leading_zeroes(char* str) {
    int trim = 0;
    while (str[trim] == '0')
        trim += 1;
    for (int i = trim; i < strlen(str); i += 1)
        str[i - trim] = str[i];
    str[strlen(str) - trim] = '\0';
}
