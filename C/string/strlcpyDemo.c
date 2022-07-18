/*
strlcpy from bsd, not be included in ANSI.
before compiling:
    1. apt-get install libbsd-dev
    2. gcc strlcpyDemo.c -o test -Wall -lbsd
*/

#include <stdio.h>
#include <string.h>
#include <bsd/string.h>

int main(void)
{
    char dest[20] = { 0 };
    char src[10] = "123456789";

    strlcpy(dest, src, sizeof(dest));

    printf("dest = %s\n", dest);  // dest = 123456789
    printf("sizeof(dest) = %ld\n", sizeof(dest));  // sizeof(dest) = 20

    return 0;
}