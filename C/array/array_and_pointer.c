#include <stdio.h>

void Array1()
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};

    // values of a and &a are same
    printf("a\t= %p\n", a); // 0x7ffdd4b1b9c0
    printf("&a\t= %p\n", &a); // 0x7ffdd4b1b9c0

    // but what a and &a point to is different
    printf("a+1\t= %p\n", (a+1)); // 0x7ffdd4b1b9c4
    printf("&a+1\t= %p\n", (&a + 1)); // 0x7ffdd4b1b9e8
}

void Array2()
{
    int a[][3] = {
        {1,2,3}, 
        {4,5,6},
        {7,8,9}};
    
    printf("a\t= %p\n", a);           // 0x7ffce8402c20
    printf("&a\t= %p\n", &a);
    printf("a[0]\t= %p\n", &a[0]);
    printf("&a[0]\t= %p\n", &a[0][0]);

    printf("a + 1\t= %p\n", a + 1);   // 0x7ffce8402c2c
    printf("&a + 1\t= %p\n", &a + 1); // 0x7ffce8402c44

    printf("a[0] + 1\t= %p\n", a[0] + 1);   // 0x7ffce8402c24
    printf("&a[0] + 1\t= %p\n", &a[0] + 1); // 0x7ffce8402c2c

    // int c = {};
    int d = {1+2};
    int e = {2,};
    int f = {2,3};
    printf("%d %d %d", d, e, f);
}

int main()
{
    Array1();
    printf("---------\n");
    Array2();

    return 0;
}