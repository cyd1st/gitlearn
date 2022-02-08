#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 20
#define PREFIX_NAME "prefix"

int func1(const char *str)
{
    char cName[SIZE] = { 0 };
    if (strncmp(PREFIX_NAME, str, sizeof(PREFIX_NAME)) != 0) {
        if (strncpy(cName, str, sizeof(cName) - 1) < 0) {
            printf("Failed strncpy_s");
            return false;
        }
    }else if (snprintf(cName, SIZE, PREFIX_NAME".%s", str) == -1) {
        printf("Failed snprintf_s");
        return false;
    }

    printf("cName = %s\n", cName);

    return 0;
}

int main()
{
    func1("testtesttesttesttest");
    return 0;
}