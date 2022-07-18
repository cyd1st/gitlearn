#include <stdio.h>

int func(char *str, int *arr)
{

}
int main()
{
    int a = 0;


    char temp[100] = "aaaaaaaaaaaaaaaaaa";
    // char str[] = {",asd,ff"};
    char str[100] = "11,22,33,44,55,asd,ff";
    char str2[100] = {0};
    // while (sscanf(str, "%s,%s", temp, str) == 2) {
    //     printf("2-");
    // }
    int ret = sscanf(str, "%s,%d", temp, &a);
    printf("ret = %d\n", ret);

    printf("temp = %s\nstr = %s\na = %d\n", temp, str, a);
    return 0;
}