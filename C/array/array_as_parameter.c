#include <stdio.h>

int func(char str[128])
{
    str[1] = 'E';
    return 0;
}

int main()
{
    char str[128] = "hello world";
    func(str);

    printf("%s\n", str);

    return 0;
}