#include <stdio.h>

int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};

    printf("a\t= %p\n", a);
    printf("&a\t= %p\n", &a);

    printf("a+1\t= %p\n", (a+1));
    printf("&a+1\t= %p\n", (&a + 1));

    return 0;
}