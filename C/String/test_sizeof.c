#include <stdio.h>
#include <string.h>

int main()
{
    char *str1 = "hello";
    char str2[6] = "hello";
    char str3[10] = { 0 };
    int a = (int)sizeof(str1);
    int b = (int)strlen(str1);
    int c = (int)sizeof(str2);
    int d = (int)strlen(str2);
    int e = (int)sizeof(str3);
    int f = (int)strlen(str3);

    printf("sizeof(str1) = %d, strlen(str1) = %d\n", a, b);
    printf("sizeof(str2) = %d, strlen(str2) = %d\n", c, d);
    printf("sizeof(str3) = %d, strlen(str3) = %d\n", e, f);


    return 0;
}
/*
sizeof(str1) = 8, strlen(str1) = 5
sizeof(str2) = 6, strlen(str2) = 5
sizeof(str3) = 10, strlen(str3) = 0
*/