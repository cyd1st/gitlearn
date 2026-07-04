#include <stdalign.h>
#include <stdio.h>

struct Test {
    char x;
    int y;
    double z;
};

int main()
{
    printf("alignof(struct Test) = %ld\n", alignof(struct Test));
    return 0;
}