#include <stdio.h>

#define XNAME(n) (x ## n)
#define PRINT_XN(n) printf("x"#n" = %d\n", XNAME(n))

int main(void)
{
    int a = 100;
    int XNAME(a) = 100;
    PRINT_XN(a);
    return 0;
}