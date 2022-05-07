#include <stdio.h>

int func(int **str)
{
    *str = NULL;
    return 0;
}

int main()
{
    int a = 100;
    int *str = &a;
    func(&str);

    printf("%d\n", *str);

    return 0;
}