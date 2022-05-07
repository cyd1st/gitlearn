#include <stdio.h>

int func(char str[][128])
{
    str[1][1] = 'E';
    return 0;
}

int main()
{
    char str[5][128] = {"dajiahao", "caishi", "zhendehao"};
    func(str);

    for (int i = 0; i < 5; i++) {
        printf("%s\n", str[i]);
    }

    return 0;
}