#include <stdio.h>

unsigned long fact(int n)
{
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 1;
    }

    return n * fact(n - 1);
}

unsigned long fact_tail(int n, unsigned long a)
{
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n == 1) {
        return a;
    }

    return fact_tail(n - 1, n * a);
}

int main()
{
    int a;
    unsigned long b;

    scanf("%d", &a);
    b = fact(a);
    printf("%d! = %lu\n", a, b);
    b = fact_tail(a, 1);
    printf("%d! = %lu\n", a, b);

    return 0;
}