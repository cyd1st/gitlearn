#include <stdio.h>

void foo() { printf("Function foo at: %p\n", foo); }

int global = 42;

int main()
{
    printf("Main function at: %p\n", main);
    printf("Global variable at: %p\n", &global);
    foo();
    return 0;
}