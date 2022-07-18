#include <stdio.h>

#define PSQR(x) printf("the square of "#x" is %d.\n", ((x) * (x)))

int main(void)
{
    int a = 10;
    PSQR(a);
    PSQR(100 + 100);
    PSQR(PSQR(a));  // 576

    return 0;
}