#include <stdio.h>
#include <stdlib.h>

void C()
{
    printf("jump to C.\n");
    exit(-1);
}

void B()
{
    long *p = NULL;
    p = (long *)&p;
    *(p + 3) = (long)C; // 不同设备平台 + 的数字不同
}

void A() { B(); }

int main()
{
    A();
    return 0;
}

// result:
// jump to C.