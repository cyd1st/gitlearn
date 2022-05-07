#include <stdio.h>

int main()
{
    int i = 0;
    while (i < 10) {
        // static int a = i;  // compile failed. i is not constant.
        static int a = 1;
        printf("%d : a = %d\n", i++, a++);
    }

    // printf("a = %d\n", a);  // compile failed. a undeclared.
    int a = 100;  // compile success.
    printf("a = %d\n", a);
    return 0;
}