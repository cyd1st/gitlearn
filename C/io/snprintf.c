#include <stdio.h>
#define BUFF_SIZE 11
int main() 
{
    unsigned short a = 1234;
    unsigned int size = 11;
    char buff[BUFF_SIZE] = {0};

    unsigned long ret = snprintf(buff, size, "%010x", a);
    //printf("char buff[size] = %c\n", buff[size]);
    //printf("char buff[size+1] = %c\n", buff[size+1]);
    //printf("int buff[size-1] = %d\n", buff[size-1]);
    printf("ret = %ld\n", ret);
    printf("buff = %s\n", buff);
    return 0;
}