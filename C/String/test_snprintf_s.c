/*
how to print string with string macro.
input format: prefix.xxx or xxx
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 30
#define PREFIX_NAME "prefix"
#define CONST_PREFIX_NAME "const.prefix"

int func1(const char *str)
{
    char cName[SIZE] = { 0 };
    if (strncmp(PREFIX_NAME, str, sizeof(PREFIX_NAME) - 1) == 0) {
        if (snprintf(cName, SIZE, "const.%s", str) == -1) {
            printf("Failed strncpy_s");
            return false;
        }
    } else if (snprintf(cName, SIZE, CONST_PREFIX_NAME".%s", str) == -1) {
        printf("Failed snprintf_s");
        return false;
    }

    printf("cName = %s\n", cName);

    return 0;
}

int main()
{
    func1("test");
    return 0;
}