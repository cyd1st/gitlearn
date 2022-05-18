#include <stdio.h>
// #define MACRO_TEST

int main(void)
{
    #ifdef MACRO_TEST
    printf("test1\n");
    #error "MACRO_TEST has been defined."
    #else
    printf("test2\n");
    #endif

    return 0;
}

