#include <stdio.h>
#include <string.h>
int main()
{
    char str[501] = {0};
    int count[128] = {0};
    int num = 0, temp = 0;
    scanf("%s", str);

    for (int i = 0; i < strlen(str); i++) {
        temp = (int)str[i];
        count[temp]++;
    }
    for (int i = 0; i < 128; i++) {
        if (count[i] > 0) {
            num++;
        }
    }
    printf("%d", num);
    return 0;
}