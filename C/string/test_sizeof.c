/*
test the size of string poniter and variable.
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char *str1 = "hello";
    char str2[6] = "hello";
    char str3[10] = "12345";
    int a = (int)sizeof(str1);
    int b = (int)strlen(str1);
    int c = (int)sizeof(str2);
    int d = (int)strlen(str2);
    int e = (int)sizeof(str3);
    int f = (int)strlen(str3);
// if index out of range
    char ch = str2[7];
    printf("ch = %c\n", ch);

    printf("sizeof(str1) = %d, strlen(str1) = %d\n", a, b);
    printf("sizeof(str2) = %d, strlen(str2) = %d\n", c, d);
    printf("sizeof(str3) = %d, strlen(str3) = %d\n", e, f);


    return 0;
}
/*
sizeof(str1) = 8, strlen(str1) = 5
sizeof(str2) = 6, strlen(str2) = 5
sizeof(str3) = 10, strlen(str3) = 5
*/

/*
sizeof is the key word of c language, not a function. That means the size of 
"sizeof(xx)" was determined at the time of compilation. It returns the size of
each variable. And there is no variable named "str".
*/