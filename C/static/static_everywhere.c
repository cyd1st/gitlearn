#include <stdio.h>

static int a = 1;  // complie success.
int main()
{
    // static int a = 1; // complie failed.
    int a = a;
    printf("a = %d\n", a);
    return 0;
}