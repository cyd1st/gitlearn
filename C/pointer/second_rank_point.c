#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func(char (**output)[64])
{
    char (*out)[64] = malloc(64 * 10);
    *output = out;
    strcpy(*out++, "hello");
    strcpy(*out++, "world");
    strcpy(*out++, "你好");
    strcpy(*out++, "世界");
}

int main()
{
    char (*output)[64] = NULL;
    func(&output);
    printf("%s\n", *output++); // hello
    printf("%s\n", *output++); // world
    printf("%s\n", *output++); // 你好
    printf("%s\n", *output++); // 世界

    return 0;
}
